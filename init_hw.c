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

/**
 * Список всех использующихся GPIO
 */
enum mcu_gpios {
    MCU_GPIO_LED_COLD,        //!< MCU_GPIO_LED_COLD
    MCU_GPIO_LED_HOT,         //!< MCU_GPIO_LED_HOT
    MCU_GPIO_PUMP,            //!< MCU_GPIO_PUMP
    MCU_GPIO_FLOW_SENSOR_COLD,//!< MCU_GPIO_FLOW_SENSOR_COLD
    MCU_GPIO_FLOW_SENSOR_HOT  //!< MCU_GPIO_FLOW_SENSOR_HOT
};

/**
 * Конфигурирование всех GPIO
 */
static struct gpio gpio_list[] = {
        { // MCU_GPIO_LED_COLD
            .direction_addr = (u8 *) &DDRB,
            .port_addr = (u8 *) &PORTB,
            .pin = 1,
            .direction = GPIO_OUTPUT,
            .output_state = 0
        },
        { // MCU_GPIO_LED_HOT
            .direction_addr = (u8 *) &DDRB,
            .port_addr = (u8 *) &PORTB,
            .pin = 2,
            .direction = GPIO_OUTPUT,
            .output_state = 0
        },
        { // MCU_GPIO_PUMP
            .direction_addr = (u8 *) &DDRA,
            .port_addr = (u8 *) &PORTA,
            .pin = 4,
            .direction = GPIO_OUTPUT,
            .output_state = 0
        },
        { // MCU_GPIO_FLOW_SENSOR_COLD
            .direction_addr = (u8 *) &DDRD,
            .port_addr = (u8 *) &PORTD,
            .pin = 2,
            .direction = GPIO_INPUT,
        },
        { // MCU_GPIO_FLOW_SENSOR_HOT
            .direction_addr = (u8 *) &DDRD,
            .port_addr = (u8 *) &PORTD,
            .pin = 3,
            .direction = GPIO_INPUT,
        },
        { // Завершающий элемент
            .direction_addr = NULL,
            .port_addr = NULL,
        },
};


static struct led leds_list[] = {
    {
        .gpio = &gpio_list[MCU_GPIO_LED_COLD]
    },
    {
        .gpio = &gpio_list[MCU_GPIO_LED_HOT]
    },
    {
        .gpio = NULL
    }
};


/**
 * Включить или выключить питание насоса
 * @param state - 1- вкл, 0 - выкл
 */
void
pump_set_state(u8 mode)
{
    gpio_set_state(&gpio_list[MCU_GPIO_PUMP], mode);
}

/**
 * Инициализация датчиков потока холодной и горячей воды
 */
static void
flow_contols_init()
{
    EICRA |= _BV(ISC01);
    EICRA |= _BV(ISC11);
    EIMSK |= _BV(INT0);

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
    gpio_init_list(gpio_list);
    usart_init();
    timer2_init();
    flow_contols_init();
    leds_init(leds_list);
    Hw_timers.sec = 1001;
    //wdt_enable(WDTO_2S); // Включаем вэтчдог
    sei();
}

