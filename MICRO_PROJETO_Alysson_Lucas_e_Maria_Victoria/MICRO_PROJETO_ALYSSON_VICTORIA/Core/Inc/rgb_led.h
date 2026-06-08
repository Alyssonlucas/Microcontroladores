/*
 * rgb_led.h
 *
 *  Created on: Jun 3, 2026
 *      Author: mvict
 */

#ifndef INC_RGB_LED_H_
#define INC_RGB_LED_H_

#include "stm32f1xx_hal.h" // Biblioteca HAL para a BluePill

// Definicoes de Cores (Valores de 0 a 100 para o ciclo de trabalho PWM)
typedef struct {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
} RGB_Color;

// Prototipos das Funcoes
void RGB_Init(TIM_HandleTypeDef *htim); // Inicializa e vincula o Timer
void RGB_SetColor(uint16_t red, uint16_t green, uint16_t blue); // Define a cor
void RGB_TurnOff(void);
void RGB_Sequence(uint32_t time_now, uint32_t *temp_colors);

#endif /* INC_RGB_LED_H_ */
