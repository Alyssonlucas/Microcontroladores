/*
 * rgb_led.c
 *
 *  Created on: Jun 3, 2026
 *      Author: mvict
 */


#include "rgb_led.h"


// Variável estática para proteger o acesso ao Timer (encapsulamento)
static TIM_HandleTypeDef *htim_led;

void RGB_Init(TIM_HandleTypeDef *htim) {
    htim_led = htim;
    // Inicia o PWM em cada canal (Canais 1, 2 e 3 conforme seu main.c)
    HAL_TIM_PWM_Start(htim_led, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(htim_led, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(htim_led, TIM_CHANNEL_3);
}

void RGB_SetColor(uint16_t red, uint16_t green, uint16_t blue) {
    // Modulariza o trecho que estava no superloop do main.c [4]
    __HAL_TIM_SET_COMPARE(htim_led, TIM_CHANNEL_1, red);
    __HAL_TIM_SET_COMPARE(htim_led, TIM_CHANNEL_2, green);
    __HAL_TIM_SET_COMPARE(htim_led, TIM_CHANNEL_3, blue);
}

void RGB_TurnOff(void) {
    RGB_SetColor(0, 0, 0);
}

void RGB_Sequence(uint32_t time_now, uint32_t *temp_colors) {

	if((time_now-*temp_colors) <= 500){
		RGB_SetColor(1000, 0, 0); // Vermelho
	}else if((time_now-*temp_colors)<= 1000){
		RGB_SetColor(0, 1000, 0); // verde
	}else if((time_now-*temp_colors)<= 1500){
		RGB_SetColor(0, 0, 1000); // azul
	}else if((time_now-*temp_colors)<= 2000){
		RGB_SetColor(1000, 500, 0); // amarelo
	}else if((time_now-*temp_colors)<= 2500){
		RGB_SetColor(200, 0, 1000); // roxinho
	}else if((time_now-*temp_colors)<= 3000){
		RGB_SetColor(0, 1000, 1000); // ciano
	}else if((time_now-*temp_colors)<= 3500){
		RGB_SetColor(1000, 1000, 1000); // branco
	}else if((time_now-*temp_colors)<= 5000){
		RGB_SetColor(1000, 0, 300);  //rosa pink
	}else if((time_now-*temp_colors)<= 6000){
		*temp_colors=time_now;
	}
}
