/*
 * init.c
 *
 *  Created on: 11.02.2012
 *      Author: Michail Kurochkin
 */

#include <avr/wdt.h>
#include <avr/interrupt.h>
#include "timers.h"
#include "machine.h"
#include "buttons.h"
#include "serial.h"
#include "timers.h"
#include "lcd.h"
#include "leds.h"
#include "config.h"


// Инициализация кнопок
volatile struct button Inputs[] =
{
	{ // Mode
		.button_port = (void *)&PINC,
		.button_pin = PINC2,
		.enable_dbl_click = 0,
	},
	{ // Down
		.button_port = (void *)&PINC,
		.button_pin = PINC3,
		.enable_dbl_click = 0,
	},
	{ // UP
		.button_port = (void *)&PINC,
		.button_pin = PINC4,
		.enable_dbl_click = 0,
	},
	{ // Start
		.button_port = (void *)&PINC,
		.button_pin = PINC5,
		.enable_dbl_click = 0,
	},
};


struct lib_button Buttons_and_inputs_info =
{
	.contact_bounse = 3,
	.time_multiplier = 300,
	.max_delay_one_click = 1000,
	.buttons = (struct button *)Inputs,
	.count_buttons = ARRAY_SIZE(Inputs),
};


static struct led leds[] = // Структура описывающая все светодиоды
{
	{
		.port_dir = (u8 *)&DDRB,
		.port = (u8 *)&PORTB,
		.pin = 0,
	},
};

/**
 * Инициализация всех выходов на реле
 */
static void init_relays(void)
{
	DDRC |= _BV(PC1);

	PORTC &= ~_BV(PC1);
}


/**
 * Инициализация всех органов управления,
 * и всех портов на которые подключенны различные датчики
 */
static void init_input_controls(void)
{
	DDRC &= ~_BV(PC2);
	DDRC &= ~_BV(PC3);
	DDRC &= ~_BV(PC4);
	DDRC &= ~_BV(PC5);

	PORTC |= _BV(PC2);
	PORTC |= _BV(PC3);
	PORTC |= _BV(PC4);
	PORTC |= _BV(PC5);

	init_lib_button(&Buttons_and_inputs_info);
}


/**
 * Включить или выключить питание на розетки
 * @param state - 1- вкл, 0 - выкл
 */
void turn_ext_power(u8 state)
{
	if(state)
		PORTC |= _BV(PC1);
	else
		PORTC &= ~_BV(PC1);
}


/**
 * Инициализация аппаратной части
 */
void init_hw(void)
{
	usart_Init();
	init_input_controls();
	init_relays();
	init_timer2();
	lcd_init();
	init_leds(leds, ARRAY_SIZE(leds));
	Hw_timers.sec = 1001;
	//wdt_enable(WDTO_2S); // Включаем вэтчдог
	sei();
}

