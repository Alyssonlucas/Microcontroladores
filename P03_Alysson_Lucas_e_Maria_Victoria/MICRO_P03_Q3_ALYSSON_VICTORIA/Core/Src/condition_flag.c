/*
 * condition_flag.c
 *
 *  Created on: Apr 15, 2026
 *      Author: lucas
 */

#include "condition_flag.h"

//Definindo as nossas flags como variáveis globais
Startstopflag Flagkey1  = STOP,Flagkey2 = STOP;

/**
  * @brief Levanta a Flag do Botão SW1
  * @param None
  * @retval None
  */
void Set_Flag_key1()
{
	Flagkey1 = START;
}

/**
  * @brief Abaixa a Flag do Botão SW1
  * @param None
  * @retval None
  */
void Reset_Flag_key1()
{
	Flagkey1 = STOP;
}

/**
  * @brief Retorna o status da Flag do Botão SW1
  * @param None
  * @retval None
  */
Startstopflag condition_check_key1()
{
	return(Flagkey1);
}
/**
  * @brief Levanta a Flag do Botão SW2
  * @param None
  * @retval None
  */
void Set_Flag_key2()
{
	Flagkey2 = START;
}

/**
  * @brief Abaixa a Flag do Botão SW2
  * @param None
  * @retval None
  */
void Reset_Flag_key2()
{
	Flagkey2 = STOP;
}

/**
  * @brief Retorna o status da Flag do Botão SW2
  * @param None
  * @retval None
  */
Startstopflag condition_check_key2()
{
	return(Flagkey2);
}
