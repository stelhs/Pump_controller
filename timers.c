/*
 * timers.c
 * Функции для работы с пользовательскими таймерами
 * Принцип работы простой:
 * 		Определяется массив переменный типа t_counter, где каждая переменная является счетчиком
 * 		Для того чтобы запустить таймер, необходимо в соответвующуюю переменную записать значение таймаута
 * 		По истечению заданного таймаута, переменная установится в 1. После обработки какх либо событий
 * 		по истечению этого таймаута, переменную необходимо обнулить.
 *
 *  Created on: 31.05.2011
 *      Author: Michail Kurochkin
 */

#include <avr/io.h>
#include <math.h>
#include "lcd.h"
#include "timers.h"
#include "machine.h"

/**
 * Функция должна встраиваться в обработчик системного таймера
 * @param list_timers - список таймеров
 */
void
dec_timers(struct list_timers *list_timers) // Данная функция встраивается в обработчик таймера и обслуживает все таймеры
{
    int count = list_timers->count;

    for (; count > 0; --count)
        if (((t_counter *) list_timers->timers)[count - 1] > 1)
            ((t_counter *) list_timers->timers)[count - 1]--;
}

/// Формируем список наборов таймеров
volatile struct list_timers All_timer_counters[] = { { .timers =
        (t_counter *) &Hw_timers, /// Набор счетчиков для работы аппаратных средств
        .count = sizeof(Hw_timers) / sizeof(t_counter), /// Количество счетчиков в наборе
        }, { .timers = (t_counter *) &Machine_timers, /// Набор счетчиков для работы основного ПО
                .count = sizeof(Machine_timers) / sizeof(t_counter), }, {
                .timers = (t_counter *) &LCD_timers, /// Набор счетчиков для работы LCD
                .count = sizeof(LCD_timers) / sizeof(t_counter), }, { /// Конец списка наборов
        .timers = 0, .count = 0, } };

/**
 * Инициализация таймера 2
 */
inline void
timer2_init(void)
{
    OCR2 = TIMER2_DELAY;
    TCCR2 = 0b011;
    TIFR |= OCF2;
    TIMSK |= _BV(OCIE2);
}


