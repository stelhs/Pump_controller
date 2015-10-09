/*
 * init.h
 *
 *  Created on: 11.02.2012
 *      Author: Michail Kurochkin
 */

#ifndef INIT_H_
#define INIT_H_

#include "gpio.h"
#include "types.h"

void
init_hw(void);

enum list_leds {
    LED_COLD_WATER,
    LED_HOT_WATER,
};

#define CLEAR_WATCHDOG() { asm("wdr"); }

/**
 * Список всех использующихся GPIO
 */
enum mcu_gpios {
    MCU_GPIO_LED_COLD,        //!< MCU_GPIO_LED_COLD
    MCU_GPIO_LED_HOT,         //!< MCU_GPIO_LED_HOT
    MCU_GPIO_PUMP,            //!< MCU_GPIO_PUMP
    MCU_GPIO_FLOW_SENSOR_COLD,//!< MCU_GPIO_FLOW_SENSOR_COLD
    MCU_GPIO_FLOW_SENSOR_HOT  //!< MCU_GPIO_FLOW_SENSOR_HOT
};

extern struct gpio gpio_list[];

#endif /* INIT_H_ */
