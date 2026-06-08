/*
 * joystick.h
 *
 *  Created on: Jun 4, 2026
 *      Author: mvict
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include "stm32f1xx_hal.h"

#define ADC_BUF_LEN 2 // Eixo X (Rank 1) e Eixo Y (Rank 2)

// Protótipos
void Joystick_Init_DMA(ADC_HandleTypeDef *hadc);
uint16_t Joystick_GetX(void);
uint16_t Joystick_GetY(void);

// Mantemos a função de direção, mas agora ela lerá do buffer
typedef enum {
	JOY_CENTER=0,
	JOY_UP,
	JOY_DOWN,
	JOY_LEFT,
	JOY_RIGHT,
	JOY_UP_RIGHT,
	JOY_UP_LEFT,
	JOY_DOWN_RIGHT,
	JOY_DOWN_LEFT
} Joystick_Dir;

Joystick_Dir Joystick_GetDirection(void);

#endif /* INC_JOYSTICK_H_ */
