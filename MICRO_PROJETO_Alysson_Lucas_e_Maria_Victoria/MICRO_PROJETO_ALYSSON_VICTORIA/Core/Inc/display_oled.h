/*
 * display_oled.h
 *
 * Created on: Jun 4, 2026
 * Author: mvict
 */

#ifndef INC_DISPLAY_OLED_H_
#define INC_DISPLAY_OLED_H_

#include "stm32f1xx_hal.h"

#define SSD1306_I2C_ADDR  0x78 // Endereço I2C padrão para o SSD1306 (7-bit 0x3C deslocado para 0x78)
#define OLED_WIDTH        128
#define OLED_HEIGHT       64

// Protótipos das funções públicas
void OLED_Init(I2C_HandleTypeDef *hi2c);
void OLED_Clear(void);
void OLED_Update(void);
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color);

// Novas funções para textos
void OLED_DrawChar(uint8_t x, uint8_t y, char c);
void OLED_DrawString(uint8_t x, uint8_t y, char* str);

void OLED_ShowLevel(uint8_t level);
void OLED_GameOver(void);

#endif /* INC_DISPLAY_OLED_H_ */
