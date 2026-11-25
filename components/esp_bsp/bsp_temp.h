#ifndef __BSP_TEMP_H__
#define __BSP_TEMP_H__

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t bsp_temp_init(void);
esp_err_t bsp_temp_get_celsius(float *celsius);

#ifdef __cplusplus
}
#endif

#endif