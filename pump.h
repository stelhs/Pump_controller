/*
 * pump.h
 *
 *  Created on: 30 янв. 2015 г.
 *      Author: Michail Kurochkin
 */
#ifndef PUMP_H_
#define PUMP_H_

/**
 * Структура таймеров основной логики ПО
 */
struct pump_timers {
    t_counter power_off; // Счетчик таймаута на выключение насоса
};
extern struct pump_timers Pump_timers;


#endif /* PUMP_H_ */
