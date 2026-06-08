/*
 * buzzer.c
 *
 *  Created on: Jun 7, 2026
 *      Author: mvict
 */


#include "buzzer.h"

static TIM_HandleTypeDef *htim_buzzer;

void Buzzer_Init(TIM_HandleTypeDef *htim) {
    htim_buzzer = htim;
    // Inicia o Timer 3 no Canal 3 no modo PWM
    HAL_TIM_PWM_Start(htim_buzzer, TIM_CHANNEL_4);

    // Começa com o buzzer desligado (Duty Cycle = 0)
    Buzzer_Stop();
}

void Buzzer_PlayTone(uint16_t frequency) {
    if (frequency == 0) {
        Buzzer_Stop();
        return;
    }

    // Com Clock = 72MHz e Prescaler = 3599, o timer conta a 20.000 Hz.
    // O novo período (ARR) será: (20000 / Frequência) - 1
    uint32_t new_arr = (1000000 / frequency) - 1;

    // Altera a frequência (Tom)
    __HAL_TIM_SET_AUTORELOAD(htim_buzzer, new_arr);
    //new_arr = ciclo de trabalho
    __HAL_TIM_SET_COMPARE(htim_buzzer, TIM_CHANNEL_4, (new_arr / 100));
}

void Buzzer_Stop(void) {
    // Zera o Duty Cycle para silenciar o buzzer
    __HAL_TIM_SET_COMPARE(htim_buzzer, TIM_CHANNEL_4, 0);
}
