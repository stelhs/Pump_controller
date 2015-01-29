#include "types.h"
#include "leds.h"

static struct // Структура для работы со светодиодами
{
    struct led *leds; // Указатель на массив светодиодов
    u8 count; // Количество светодиодов в массиве
} Lib_leds;

static void
turn_led(struct led *led, u8 mode) // Включить или выключить светодиод
{
    if (mode) // Если светодиод нужно зажечь
        led->port[0] |= (1 << led->pin);
    else
        // или потушить
        led->port[0] &= ~(1 << led->pin);

    led->state = mode;
}

void
update_leds(void)
{
    u8 i;
    for (i = 0; i < Lib_leds.count; i++) {
        struct led *led = Lib_leds.leds + i;

        if (led->blink_timer > 1)
            led->blink_timer--;

        if (led->blink_timer > 1 || led->interval1 == 0)
            continue;

        if (led->state) // Изменяем состояние светодиода
        {
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
init_leds(struct led *leds, u8 count)
{
    u8 i;
    Lib_leds.leds = leds;
    Lib_leds.count = count;
    for (i = 0; i < count; i++) {
        struct led *led = Lib_leds.leds + i;

        led->port_dir[0] |= (1 << led->pin); // Устанавливаем все порты на выход
        led->blink_timer = 0;
        led->interval1 = 0;
        led->interval2 = 0;
        turn_led(led, 0);
    }
}

void
set_led_state(u8 num, u8 mode, t_counter interval1, t_counter interval2) // Установить состояние светодиода
{
    struct led *led = Lib_leds.leds + num;

    if (interval2 == 0)
        interval2 = interval1;

    turn_led(led, mode);
    led->interval1 = interval1;
    led->interval2 = interval2;
    led->blink_timer = interval1;
}

