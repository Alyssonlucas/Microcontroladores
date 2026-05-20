/*
 * usb_flags.c
 *
 *  Created on: May 18, 2026
 *      Author: lucas
 */

#include "usb_flags.h"

//Definindo a flag como variável global
Startstopflag Flag_USB  = STOP;

/**
  * @brief Levanta a Flag da conversão adc
  * @param None
  * @retval None
  */
void Set_Flag_USB()
{
	Flag_USB = START;
}

/**
  * @brief Abaixa a Flag da conversão adc
  * @param None
  * @retval None
  */
void Reset_Flag_USB()
{
	Flag_USB = STOP;
}

/**
  * @brief Retorna o status da Flag da conversão adc
  * @param None
  * @retval None
  */
Startstopflag condition_check_USB()
{
	return(Flag_USB);
}



