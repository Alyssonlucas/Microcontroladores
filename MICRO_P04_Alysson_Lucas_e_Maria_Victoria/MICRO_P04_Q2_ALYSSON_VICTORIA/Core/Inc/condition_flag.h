/*
 * codition_flag.h
 *
 *  Created on: May 4, 2026
 *      Author: lucas
 */

#ifndef INC_CONDITION_FLAG_H_
#define INC_CONDITION_FLAG_H_

typedef enum {
	START,
	STOP
}Startstopflag;


void Reset_Flag_adc();
void Set_Flag_adc();
Startstopflag condition_check_adc();

#endif /* INC_CONDITION_FLAG_H_ */
