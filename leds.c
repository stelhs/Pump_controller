#include "types.h"
#include "leds.h"
#include "gpio.h"

static struct // Структура для работы со светодиодами
{
    struct led *leds; // Указатель на массив светодиодов
    u8 count; // Количество светодиодов в массиве
} Lib_leds;

static void
turn_led(struct led *led, u8 mode) // Включить или выключить светодиод
{
    gpio_set_state(led->gpio, mode);
    led->state = mode;
}

void
leds_update(void)
{
    u8 i;
    for (i = 0; i < Lib_leds.count; i++) {
        struct led *led = Lib_leds.leds + i;

        if (led->blink_timer > 1)
            led->blink_timer--;

        if (led->blink_timer > 1 || led->interval1 == 0)
            continue;

        if (led->state) {
            turn_led(led, 0);
            led->blink_timer = led->interval2; // Заряжаем таймер значением interval1
        }
        else {
            turn_led(led, 1);
            led->blink_timer = led->interval1; // Заряжаем таймер значением interval2
        }
    }
}

void
leds_init(struct led *leds, u8 count)
{
    u8 i;
    Lib_leds.leds = leds;
    Lib_leds.count = count;
    for (i = 0; i < count; i++) {
        struct led *led = Lib_leds.leds + i;

        gpio_set_direction(led->gpio, 0);
        led->blink_timer = 0;
        led->interval1 = 0;
        led->interval2 = 0;
        turn_led(led, 0);
    }
}

void
leds_set_state(u8 num, u8 mode, t_counter interval1, t_counter interval2) // Установить состояние светодиода
{
    struct led *led = Lib_leds.leds + num;

    if (interval2 == 0)
        interval2 = interval1;

    turn_led(led, mode);
    led->interval1 = interval1;
    led->interval2 = interval2;
    led->blink_timer = interval1;
}

