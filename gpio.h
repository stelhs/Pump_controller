#ifndef LED_LIB_H
#define LED_LIB_H

#include "types.h"

struct gpio {
    u8 *direction;
    u8 *port;
    u8 pin;
    u8 output_state :1; // Установленное состояние порта
};

// Установить состояние светодиода
// interval1 и interval2 это время горения и время негорения светодиода
static void
gpio_set_state(struct gpio *gpio, u8 mode)

static void
gpio_set_direction(struct gpio *gpio, u8 mode);

#endif
