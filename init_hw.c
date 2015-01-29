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


static struct led leds[] = {
    {
        .port_dir = (u8 *) &DDRB,
        .port = (u8 *) &PORTB,
        .pin = 1,
    },
    {
        .port_dir = (u8 *) &DDRB,
        .port = (u8 *) &PORTB,
        .pin = 2,
    },
};

/**
 * Инициализация всех выходов на реле
 */
static void
init_relays(void)
{
    DDRA |= _BV(PA4);

    PORTA &= ~_BV(PA4);
}

/**
 * Включить или выключить питание насоса
 * @param state - 1- вкл, 0 - выкл
 */
void
turn_pump(u8 state)
{
    if (state)
        PORTA |= _BV(PA4);
    else
        PORTA &= ~_BV(PA4);
}

/**
 * Инициализация датчиков потока холодной и горячей воды
 */
void
init_flow_contols()
{
    DDRD &= ~_BV(PD2);
    PORTD |= _BV(PD2);
    EICRA |= _BV(ISC01);
    EICRA |= _BV(ISC11);
    EIMSK |= _BV(INT0);

    DDRD &= ~_BV(PD3); \
    PORTD |= _BV(PD3); \
    EICRA |= _BV(ISC01); \
    EICRA |= _BV(ISC11); \
    EIMSK |= _BV(INT1); \
}


/**
 * Инициализация аппаратной части
 */
void
init_hw(void)
{
    usart_init();
    init_relays();
    init_timer2();
    init_flow_contols();
    init_leds(leds, ARRAY_SIZE(leds));
    Hw_timers.sec = 1001;
    //wdt_enable(WDTO_2S); // Включаем вэтчдог
    sei();
}

