#ifndef LED_LIB_H
#define LED_LIB_H

#include "gpio.h"
#include "types.h"

struct led {
    struct gpio gpio;
    u8 state :1; // Текущее состояние светодиода
    t_counter blink_timer; // Таймер для мигания
    t_counter interval1; // Установленный интервал мигания, 0 - немигать
    t_counter interval2; // Установленный интервал мигания, 0 - мигать с равными интервалами interval1
};

void
leds_update(void);
void
leds_init(struct led *leds, u8 count);

// Установить состояние светодиода
// interval1 и interval2 это время горения и время негорения светодиода
void
leds_set_state(u8 num, u8 mode, t_counter interval1, t_counter interval2);

#endif
