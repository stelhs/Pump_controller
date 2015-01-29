/*
 * config.h
 *
 *  Created on: 25.01.2014
 *      Author: Michail Kurochkin
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define LCD_REFRASH_PERIOD 10

// Таймаут на редактирование параметров
#define EDIT_TIMEOUT_PERIOD 5000

// Частота обновления информации на экране в режимах POWER и WAITING
#define DISPLAY_REMAINDER_PERIOD 1000

// Частота мигания экрана
#define DISPLAY_BLINK_PERIOD 300

// Адреса в EEPROM для сохранения различных данных
#define EEPROM_ERRORS_OFFSET 0 // Адрес начиная с которого сохраняются ошибки системы
#define EEPROM_SETTINGS_OFFSET 300 // Адрес начиная с которого сохраняются установки системы


#endif /* CONFIG_H_ */
