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
void
gpio_set_direction(struct gpio *gpio, enum gpio_direction dir)
{
    if (dir)
        gpio->direction_addr[0] |= (1 << gpio->pin);
    else
        gpio->direction_addr[0] &= ~(1 << gpio->pin);
    gpio->direction = dir;
}

/**
 * Установить состояние выхода порта PGIO
 * @param gpio - PGIO порт
 * @param mode - ON или OFF
 */
void
gpio_set_state(struct gpio *gpio, u8 mode)
{
    if (mode)
        gpio->port_addr[0] |= (1 << gpio->pin);
    else
        gpio->port_addr[0] &= ~(1 << gpio->pin);

    gpio->output_state = mode;
}

/**
 * Инициализация списка GPIO портов
 * @param gpio_list
 */
void
gpio_init_list(struct gpio *gpio_list)
{
    struct gpio *gpio;
    for (gpio = gpio_list; gpio->direction_addr != NULL; gpio++) {
        gpio_set_direction(gpio, gpio->direction);
        gpio_set_state(gpio, gpio->output_state);
    }
}
