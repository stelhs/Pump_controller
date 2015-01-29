/*
 * machine.h
 *
 *  Created on: 26.01.2014
 *      Author: Michail Kurochkin
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include "types.h"

/**
 * Возможные состояние прибора
 */
enum machine_states
{
	STOPED,      //!< Остановлен
	POWER,//!< Запущен, и подано питание
	WAITING,     //!< В ожидании интервала повтора подачи питания
};

/**
 * Режимы редактирования параметров
 */
enum edit_mode
{
	NONE,           //!< Ничего не редактируется в данный момент
	POWER_INTERVAL, //!< Редактируется время подачи питания
	REPEAT_INTERVAL,//!< Редактируется интервал подачи питания
};


struct machine
{
	enum machine_states state; // состояние системы
	s16 power_interval; // Интервал подачи питания в часах
	s16 waiting_interval; // Интервал повтора подачи питания в днях
	u32 power_interval_sec; // Интервал подачи питания в секундах
	u32 waiting_interval_sec; // Интервал повтора подачи питания в секундах
	u32 power_time; // Сколько времени прошло с момента подачи питания в секундах
	u32 waiting_time; // Сколько времени прошло в ожидании повтора в секундах
	enum edit_mode edit_mode; // режим редактирования параметра
};
extern struct machine Machine;

/**
 * Структура данных энергонезависимой памяти
 * Служит для возврата состояния системы после сбоя
 */
struct nonvolatile_status
{
	struct machine machine;
	u16 crc16;
};



/**
 * Структура таймеров для аппаратуры
 */
struct hw_timers
{
	t_counter sec; // Отсчет интервала приблизительно равного секунде
};
extern struct hw_timers Hw_timers;


/**
 * Структура таймеров основной логики ПО
 */
struct machine_timers
{
	t_counter edit_timeout; // Счетчик таймаута на выход из режима редактирования
	t_counter display_status_refresh; // Счетчик таймаута на обновление информации о остатке времени работы того или иного режима
};
extern struct machine_timers Machine_timers;


void store_state(void);
int restore_state(void);
void update_machine_timer(u32 sec);

#endif /* MACHINE_H_ */
