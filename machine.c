/*
 * eeprom.c
 *
 *  Created on: 29.01.2014
 *      Author: Michail Kurochkin
 */

#include <avr/eeprom.h>
#include "types.h"
#include "timers.h"
#include "machine.h"
#include "init_hw.h"
#include "modes.h"

/**
 * Объект включает в себя все таймеры необходимые
 * для работы аппаратуры и драйверов
 */
struct hw_timers Hw_timers;

/**
 * Объект основной структуры машины состояния прибора
 */
struct machine Machine;

/**
 * Объект включает в себя все таймеры необходимые
 * для работы с основной логикой
 */
struct machine_timers Machine_timers;

