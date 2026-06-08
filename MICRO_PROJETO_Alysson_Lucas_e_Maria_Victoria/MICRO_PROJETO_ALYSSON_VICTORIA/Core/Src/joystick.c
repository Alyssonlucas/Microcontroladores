/*
 * joystick.c
 *
 *  Created on: Jun 4, 2026
 *      Author: mvict
 */


#include "joystick.h"

// Buffer protegido (Background)
static volatile uint16_t adc_buffer[ADC_BUF_LEN];

void Joystick_Init_DMA(ADC_HandleTypeDef *hadc) {

    // Inicia o ADC com DMA (A linha que você desejava usar)
    HAL_ADC_Start_DMA(hadc, (uint32_t*)adc_buffer, ADC_BUF_LEN);

}

uint16_t Joystick_GetX(void) {
    return adc_buffer[0]; // Rank 1 configurado na main
}

uint16_t Joystick_GetY(void) {
    return adc_buffer[1]; // Rank 2 configurado na main
}

Joystick_Dir Joystick_GetDirection(void) {
    uint16_t x = Joystick_GetX();
    uint16_t y = Joystick_GetY();

    // 1. Zona Morta (Centro)
    if (x > (2048 - 300) && x < (2048 + 300) &&
        y > (2048 - 300) && y < (2048 + 300))
    {
        return JOY_CENTER;
    }

    // 2. Verificação das DIAGONAIS (Prioridade alta - Limiares menores)
    else if (x > 2800 && y > 2800) { return JOY_UP_RIGHT; }
    else if (x > 2800 && y < 1200) { return JOY_UP_LEFT; }
    else if (x < 1200 && y > 2800) { return JOY_DOWN_RIGHT; }
    else if (x < 1200 && y < 1200) { return JOY_DOWN_LEFT; }

    // 3. Verificação das DIREÇÕES SIMPLES (Limiares mais extremos)
    else if (x > 3500) { return JOY_UP; }
    else if (x < 500)  { return JOY_DOWN; }
    else if (y < 500)  { return JOY_LEFT; }
    else if (y > 3500) { return JOY_RIGHT; }

    // 4. Fallback (Caso o joystick esteja fora da zona morta mas não atinja os extremos)
    else { return JOY_CENTER; }
}
