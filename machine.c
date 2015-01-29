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



/**
 * Call-back функция обновления счетчиков времени
 * работы режима POWER и WAITING
 * @param $sec
 */
void update_machine_timer(u32 sec)
{
	switch (Machine.state)
	{
		case STOPED:
			return;

		case POWER:
			Machine.power_time += sec;
			break;

		case WAITING:
			Machine.waiting_time += sec;
			break;
	}
}



/**
 * Безопасная запись в EEPROM. Пишутся только изменившиеся ячейки.
 * @param source - адрес откуда записать данные
 * @param dest - адрес в EEPROM куда записать данные
 * @param len - количество байт данных для записи
 */
static void safe_eeprom_write_block(u8 *source, u8 *dest, u16 size)
{
	u16 i = 0;

	for(i = 0; i < size; i++)
		if(source[i] != eeprom_read_byte(dest + i))
		{
			CLEAR_WATCHDOG();
			eeprom_write_byte(dest + i, source[i]);
		}
}

/**
 * Расчет контрольной суммы CRC-16 CCITT
 * @param buf - Буффер который необходимо подсчитать
 * @param size - размер буфера
 * @return
 */
static u16 crc16(u8 *buf, u16 size)
{
    u16 crc = 0xFFFF;
    u8 i;

    while( size-- )
    {
        crc ^= *buf++ << 8;

        for(i = 0; i < 8; i++)
        	crc = crc & 0x8000 ? ( crc << 1 ) ^ 0x1021 : crc << 1;
    }

    return crc;
}



/**
 * Сохранить состояние всей системы
 * в энергонезависимую память
 */
void store_state(void)
{
	struct nonvolatile_status stat;
	stat.machine = Machine;

	stat.crc16 = crc16((u8 *)&stat.machine, sizeof (struct machine));
	safe_eeprom_write_block((u8 *)&stat, 0, sizeof stat);
}



/**
 * Восстановить состояние всей системы
 * из энергонезависимой памяти
 */
int restore_state(void)
{
	u16 calc_crc;
	struct nonvolatile_status stat;

	eeprom_read_block((u8 *)&stat, 0, sizeof stat);
	calc_crc = crc16((u8 *)&stat.machine, sizeof (struct machine));
	if (calc_crc != stat.crc16)
		return 1;

	stat.machine.edit_mode = NONE;

	switch (stat.machine.state)
	{
		case STOPED:
			machine_stop();
			break;

		case POWER:
			machine_run();
			break;

		case WAITING:
			machine_goto_waiting();
			break;
	}

	Machine = stat.machine;
	display_status(0);

	return 0;
}




