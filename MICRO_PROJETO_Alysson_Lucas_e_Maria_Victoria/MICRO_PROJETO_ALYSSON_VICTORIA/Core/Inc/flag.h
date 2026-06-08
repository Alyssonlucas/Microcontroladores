/*
 * flag.h
 *
 *  Created on: Jun 8, 2026
 *      Author: lucas
 */

#ifndef INC_FLAG_H_
#define INC_FLAG_H_

//definindo um tipo de numeração
typedef enum {
	START,
	STOP
}Startstopflag;

//prototipação das funções
void Reset_Flag_key();
void Set_Flag_key();
Startstopflag condition_check_key();


#endif /* INC_FLAG_H_ */
