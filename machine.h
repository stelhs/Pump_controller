/*
 * machine.h
 *
 *  Created on: 26.01.2014
 *      Author: Michail Kurochkin
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include "types.h"


struct machine {
};
extern struct machine Machine;

/**
 * Структура таймеров для аппаратуры
 */
struct hw_timers {
    t_counter sec; // Отсчет интервала приблизительно равного секунде
};
extern struct hw_timers Hw_timers;

/**
 * Структура таймеров основной логики ПО
 */
struct machine_timers {
//    t_counter edit_timeout; // Счетчик таймаута на выход из режима редактирования
};
extern struct machine_timers Machine_timers;

#endif /* MACHINE_H_ */
