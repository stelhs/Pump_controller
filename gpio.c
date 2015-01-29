#include "types.h"
#include "gpio.h"

static struct
{
    struct gpio *gpio_array; // Указатель на массив портов
    u8 count; // Количество портов в массиве
} Lib_gpio;

/**
 * Установить режим GPIO
 * @param gpio - GPIO порт
 * @param mode - 0-вход, 1-выход
 */
static void
gpio_set_direction(struct gpio *gpio, u8 mode)
{
    if (mode)
        gpio->direction[0] |= (1 << gpio->pin);
    else
        gpio->direction[0] &= ~(1 << gpio->pin);
}

/**
 * // установить состояние выхода порта PGIO
 * @param gpio - PGIO порт
 * @param mode - ON или OFF
 */
static void
gpio_set_state(struct gpio *gpio, u8 mode)
{
    if (mode)
        gpio->port[0] |= (1 << gpio->pin);
    else
        gpio->port[0] &= ~(1 << gpio->pin);

    gpio->output_state = mode;
}

