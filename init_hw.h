/*
 * init.h
 *
 *  Created on: 11.02.2012
 *      Author: Michail Kurochkin
 */

#ifndef INIT_H_
#define INIT_H_

#include "types.h"
#include "buttons.h"

void init_hw(void);
void turn_ext_power(u8 state);


// Описание кнопок и входных сигналов
enum list_buttons
{
	BUTT_MODE,
	BUTT_DOWN,
	BUTT_UP	,
	BUTT_START,
};
extern volatile struct button Inputs[];

enum list_leds
{
	LED_MODE,
};

#define CLEAR_WATCHDOG() { asm("wdr"); }

#endif /* INIT_H_ */
