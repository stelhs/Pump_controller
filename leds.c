#include "types.h"
#include "leds.h"
#include "gpio.h"

static struct // Структура для работы со светодиодами
{
    struct led *leds; // Указатель на массив светодиодов
} Lib_leds;

static void
led_set_state(struct led *led, u8 mode) // Включить или выключить светодиод
{
    gpio_set_state(led->gpio, mode);
    led->state = mode;
}

void
leds_update(void)
{
    struct led *led;
    for (led = leds; led->gpio != NULL; led++) {
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
leds_init(struct led *leds)
{
    Lib_leds.leds = leds;
    struct led *led;
    for (led = leds; led->gpio != NULL; led++) {
        gpio_set_direction(led->gpio, GPIO_OUTPUT);
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

    led_set_state(led, mode);
    led->interval1 = interval1;
    led->interval2 = interval2;
    led->blink_timer = interval1;
}

