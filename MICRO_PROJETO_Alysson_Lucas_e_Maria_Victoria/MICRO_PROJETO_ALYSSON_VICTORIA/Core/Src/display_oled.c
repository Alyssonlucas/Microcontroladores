/*
 * display_oled.c
 *
 * Created on: Jun 4, 2026
 * Author: mvict
 */

#include "display_oled.h"
#include "fonts.h"
#include <string.h>
#include <stdio.h> // Necessário para usar o sprintf no ShowLevel

// Variáveis estáticas para encapsulamento (Proteção de Variáveis)
static I2C_HandleTypeDef *hi2c_oled;

static uint8_t OLED_Buffer[1024];

// Função privada para envio de comandos
static void OLED_SendCommand(uint8_t cmd) {
    HAL_I2C_Mem_Write(hi2c_oled, SSD1306_I2C_ADDR, 0x00, 1, &cmd, 1, 10);
}

// Inicialização baseada no fluxograma do Application Note
void OLED_Init(I2C_HandleTypeDef *hi2c) {
    hi2c_oled = hi2c;

    OLED_SendCommand(0xAE); // Display OFF

    // --- CORREÇÃO: Configuração do Memory Addressing Mode ---
    OLED_SendCommand(0x20); // Set Memory Addressing Mode
    OLED_SendCommand(0x00); // 0x00 = Horizontal Addressing Mode
    // --------------------------------------------------------

    OLED_SendCommand(0xD5); OLED_SendCommand(0x80); // Define a velocidade/taxa de atualização
    OLED_SendCommand(0xA8); OLED_SendCommand(0x3F); // Proporção de multiplexação
    OLED_SendCommand(0xD3); OLED_SendCommand(0x00); // Deslocamento da tela
    OLED_SendCommand(0x40); // Topo da RAM
    OLED_SendCommand(0x8D); OLED_SendCommand(0x14); // Habilita Charge Pump
    OLED_SendCommand(0xA1); // Segment Re-map (Inverte colunas)
    OLED_SendCommand(0xC8); // COM Output Scan Direction (Inverte linhas)
    OLED_SendCommand(0xDA); OLED_SendCommand(0x12); // Mapeamento sequencial/alternado
    OLED_SendCommand(0x81); OLED_SendCommand(0x7F); // Brilho/contraste
    OLED_SendCommand(0xA4); // Mostrar RAM
    OLED_SendCommand(0xA6); // Modo normal de cor
    OLED_SendCommand(0xAF); // Display ON

    OLED_Clear();
    OLED_Update();
}

void OLED_Clear(void) {
    memset(OLED_Buffer, 0x00, sizeof(OLED_Buffer));
}

void OLED_Update(void) {
    // 1. Configura os limites das colunas (0 a 127)
    OLED_SendCommand(0x21);
    OLED_SendCommand(0x00);
    OLED_SendCommand(0x7F);

    // 2. Configura os limites das páginas/linhas (0 a 7)
    OLED_SendCommand(0x22);
    OLED_SendCommand(0x00);
    OLED_SendCommand(0x07);

    // --- MELHORIA: Uso de DMA para não travar o Superloop ---
    HAL_I2C_Mem_Write_DMA(hi2c_oled, SSD1306_I2C_ADDR, 0x40, 1, OLED_Buffer, 1024);
}

void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color) {
    if(x >= OLED_WIDTH || y >= OLED_HEIGHT) return;

    if(color == 1) {
        OLED_Buffer[x + (y / 8) * OLED_WIDTH] |= (1 << (y % 8));
    } else {
        OLED_Buffer[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
    }
}

// --- NOVAS FUNÇÕES DE TEXTO ---

void OLED_DrawChar(uint8_t x, uint8_t y, char c) {
    // Filtra apenas caracteres ASCII imprimíveis suportados pela nossa tabela (32 a 122)
    if (c < 32 || c > 122) return;

    uint8_t font_index = c - 32;

    for (uint8_t i = 0; i < 5; i++) { // Varre as 5 colunas do caractere
        uint8_t line = Font5x7[font_index][i];
        for (uint8_t j = 0; j < 8; j++) { // Varre os 8 bits de cada coluna (linhas)
            if (line & (1 << j)) {
                OLED_DrawPixel(x + i, y + j, 1);
            } else {
                OLED_DrawPixel(x + i, y + j, 0);
            }
        }
    }
}

void OLED_DrawString(uint8_t x, uint8_t y, char* str) {
    while (*str) {
        OLED_DrawChar(x, y, *str);
        x += 6; // Avança 5 pixels da letra + 1 pixel de espaçamento

        // Quebra de linha automática se passar do final da tela
        if (x >= OLED_WIDTH - 5) {
            x = 0;
            y += 10;
        }
        str++;
    }
}

void OLED_ShowLevel(uint8_t level) {
    // Exemplo prático de como a função funcionará:
    char buffer[16];
    sprintf(buffer, "Nivel: %d", level);
    OLED_DrawString(10, 10, buffer);
    OLED_Update(); // Só atualiza a tela quando a informação mudar

}

void OLED_GameOver(void) {
    OLED_Clear();
    // Exemplo prático de como a função funcionará:

    OLED_DrawString(30, 30, "GAME OVER");
    OLED_Update();

}
