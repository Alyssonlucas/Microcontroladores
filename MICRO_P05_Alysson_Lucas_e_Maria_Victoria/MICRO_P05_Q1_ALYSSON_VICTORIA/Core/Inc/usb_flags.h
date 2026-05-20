/*
 * usb_flags.h
 *
 *  Created on: May 18, 2026
 *      Author: lucas
 */

#ifndef INC_USB_FLAG_H_
#define INC_USB_FLAG_H_

typedef enum {
	START,
	STOP
}Startstopflag;

void Reset_Flag_USB();
void Set_Flag_USB();
Startstopflag condition_check_USB();

#endif /* INC_CONDITION_FLAG_H_ */
