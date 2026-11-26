#include "bsp_boton.h"
#include "button_gpio.h"

static button_handle_t s_boton = NULL;

esp_err_t bsp_boton_init(void)
{
    /* Tiempos en 0 = los valores por defecto del componente */
    const button_config_t config = {
        .long_press_time = 0,
        .short_press_time = 0,
    };
    const button_gpio_config_t gpio = {
        .gpio_num = BSP_BOTON_GPIO,
        .active_level = BSP_BOTON_NIVEL_ACTIVO,
    };
    return iot_button_new_gpio_device(&config, &gpio, &s_boton);
}

button_handle_t bsp_boton_handle(void)
{
    return s_boton;
}