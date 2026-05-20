/*
 * condition_flag.c
 *
 *  Created on: May 4, 2026
 *      Author: lucas
 */

#include "condition_flag.h"

//Definindo a flag como variável global
Startstopflag Flag_adc  = STOP;

/**
  * @brief Levanta a Flag da conversão adc
  * @param None
  * @retval None
  */
void Set_Flag_adc()
{
	Flag_adc = START;
}

/**
  * @brief Abaixa a Flag da conversão adc
  * @param None
  * @retval None
  */
void Reset_Flag_adc()
{
	Flag_adc = STOP;
}

/**
  * @brief Retorna o status da Flag da conversão adc
  * @param None
  * @retval None
  */
Startstopflag condition_check_adc()
{
	return(Flag_adc);
}


