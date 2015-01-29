/*
 * controls.c
 *
 *  Created on: 25.01.2014
 *      Author: Michail Kurochkin
 */
#include <avr/interrupt.h>
#include "timers.h"
#include "machine.h"
#include "buttons.h"
#include "leds.h"
#include "lcd.h"
#include "modes.h"
#include "config.h"

/**
 * Обработчик универсального таймера
 * работающего с частотой 1000Hz
 */
SIGNAL(SIG_OUTPUT_COMPARE2)
{
	volatile struct list_timers *timers;

	// Перебираем список наборов таймеров
	for(timers = All_timer_counters; timers[0].count; timers++)
		dec_timers((struct list_timers *)timers); // и инкрементируем каждый набор

	// Обновляем значения таймеров для работы логики опроса состояния кнопок
	change_timer_buttons();

	lcd_refrash();

	if(Hw_timers.sec == 1)
	{
		update_machine_timer(1);
		Hw_timers.sec = 1001;
	}

	update_leds();
}



