/*
 * flag.c
 *
 *  Created on: Jun 8, 2026
 *      Author: lucas
 */
#include "flag.h"

//Definindo as nossas flags como variáveis globais
Startstopflag Flagkey  = STOP;

/**
  * @brief Levanta a Flag do Botão Joystick
  * @param None
  * @retval None
  */
void Set_Flag_key()
{
	Flagkey = START;
}

/**
  * @brief Abaixa a Flag do Botão Joystick
  * @param None
  * @retval None
  */
void Reset_Flag_key()
{
	Flagkey = STOP;
}

/**
  * @brief Retorna o status da Flag do Botão Joystick
  * @param None
  * @retval None
  */
Startstopflag condition_check_key()
{
	return(Flagkey);
}
