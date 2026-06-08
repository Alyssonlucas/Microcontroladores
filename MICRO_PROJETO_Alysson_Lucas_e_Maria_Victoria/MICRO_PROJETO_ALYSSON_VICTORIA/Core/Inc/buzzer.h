/*
 * buzzer.h
 *
 *  Created on: Jun 7, 2026
 *      Author: mvict
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdint.h>           // Adicione esta linha para reconhecer o uint16_t
#include "stm32f1xx_hal.h"    // Adicione esta linha para reconhecer o TIM_HandleTypeDef e as macros

// Protótipos das funções
void Buzzer_Init(TIM_HandleTypeDef *htim);
void Buzzer_PlayTone(uint16_t frequency);
void Buzzer_Stop(void);

#endif /* INC_BUZZER_H_ */
