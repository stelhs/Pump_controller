/*
 * pump.c
 *
 *  Created on: 30 янв. 2015 г.
 *      Author: Michail Kurochkin
 */

#include "types.h"
#include "config.h"
#include "gpio.h"
#include "pump.h"
#include "init_hw.h"

/**
 * Объект включает в себя все таймеры необходимые
 * для работы с основной логикой
 */
struct pump_timers Pump_timers;


/**
 * Включить или выключить питание насоса
 * @param state - 1- вкл, 0 - выклtn
 */
static void
pump_set_state(u8 mode)
{
    gpio_set_state(&gpio_list[MCU_GPIO_PUMP], mode);
}


void
pump_on(void)
{
    pump_set_state(ON);
    Pump_timers.power_off = CONFIG_PUMP_TIMEOUT;
}

void
check_pump(void)
{
    if (Pump_timers.power_off > 1)
        return;

    pump_set_state(OFF);
    Pump_timers.power_off = 0;
}
