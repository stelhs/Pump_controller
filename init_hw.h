/*
 * init.h
 *
 *  Created on: 11.02.2012
 *      Author: Michail Kurochkin
 */

#ifndef INIT_H_
#define INIT_H_

#include "types.h"

void
init_hw(void);
void
pump_set_state(u8 state);

enum list_leds {
    LED_COLD_WATER,
    LED_HOT_WATER,
};

#define CLEAR_WATCHDOG() { asm("wdr"); }

#endif /* INIT_H_ */
