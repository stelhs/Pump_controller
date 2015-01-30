/*
 * controls.c
 *
 *  Created on: 25.01.2014
 *      Author: Michail Kurochkin
 */
#include <avr/interrupt.h>
#include "timers.h"
#include "machine.h"
#include "leds.h"
#include "config.h"

/**
 * Обработчик универсального таймера
 * работающего с частотой 1000Hz
 */
SIGNAL(SIG_OUTPUT_COMPARE2)
{
    volatile struct list_timers *timers;

    // Перебираем список наборов таймеров
    for (timers = All_timer_counters; timers[0].count; timers++)
        dec_timers((struct list_timers *) timers); // и инкрементируем каждый набор

    if (Hw_timers.sec == 1) {
        //update_machine_timer(1);
        Hw_timers.sec = 1001;
    }

    leds_update();
}


/**
 * Обработчик сигнала с датчика потока холодной воды
 */
SIGNAL(SIG_INTERRUPT0)
{


}


/**
 * Обработчик сигнала с датчика потока горячей воды
 */
SIGNAL(SIG_INTERRUPT1)
{


}


