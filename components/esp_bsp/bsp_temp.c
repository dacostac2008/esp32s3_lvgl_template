#include "bsp_temp.h"
#include "driver/temperature_sensor.h"

// "Control remoto" del sensor: lo da install() y se usa para leer
static temperature_sensor_handle_t s_sensor = NULL;

esp_err_t bsp_temp_init(void)
{
    // Rango esperado de temperatura del chip, en grados
    temperature_sensor_config_t config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(-10, 80);

    esp_err_t err = temperature_sensor_install(&config, &s_sensor);
    if (err != ESP_OK) {
        return err;
    }
    return temperature_sensor_enable(s_sensor);
}

esp_err_t bsp_temp_get_celsius(float *celsius)
{
    // Si nunca se llamó a init, no hay sensor para leer
    if (s_sensor == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return temperature_sensor_get_celsius(s_sensor, celsius);
}