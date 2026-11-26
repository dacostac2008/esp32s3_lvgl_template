#ifndef __BSP_BOTON_H__
#define __BSP_BOTON_H__

#include "esp_err.h"
#include "iot_button.h"

/* Boton BOOT de la placa: GPIO0, vale 0 cuando esta apretado */
#define BSP_BOTON_GPIO          0
#define BSP_BOTON_NIVEL_ACTIVO  0

#ifdef __cplusplus
extern "C" {
#endif

/* Crea el boton con el componente espressif/button (ya filtra los rebotes) */
esp_err_t bsp_boton_init(void);

/* "Control remoto" del boton, para registrarle funciones (NULL si no se inicio) */
button_handle_t bsp_boton_handle(void);

#ifdef __cplusplus
}
#endif

#endif