/*
 * condition_flag.h
 *
 *  Created on: Apr 15, 2026
 *      Authors: lucas
 */

#ifndef INC_CONDITION_FLAG_H_
#define INC_CONDITION_FLAG_H_

typedef enum {
	START,
	STOP
}Startstopflag;


void Reset_Flag_key1();
void Set_Flag_key1();
Startstopflag condition_check_key1();


void Reset_Flag_key2();
void Set_Flag_key2();
Startstopflag condition_check_key2();

#endif /* INC_CONDITION_FLAG_H_ */
