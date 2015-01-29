/*
 * timers.h
 *	Функции работы с пользовательскими таймерами
 *  Created on: 31.05.2011
 *      Author: Michail Kurochkin
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "types.h"

/**
 * Структура описывающая набор таймеров
 */
struct list_timers {
    t_counter *timers; /// // В массиве таймеров обязательно чтобы все поля структуры были единого размера типа t_counter
    int count; /// Количество таймеров в массиве
};
extern volatile struct list_timers All_timer_counters[];

void
dec_timers(struct list_timers *list_timers);

// конфигурация таймера 2: частота 1000Hz
#define TIMER2_DELAY (u8)((u32)F_CPU / 1000 / (2 * 32) - 1)
void
init_timer2(void);
