#include "scr_home.h"
#include "screens.h"
#include "ui.h"
#include "bsp_battery.h"
#include "bsp_temp.h"
#include "esp_timer.h"
#include "esp_log.h"

static const char *TAG = "scr_home";

/* Timer que actualiza los datos una vez por segundo */
static lv_timer_t *s_timer = NULL;

/* Convierte el voltaje de la bateria (Li-ion) a porcentaje:
 * 3.3 V o menos = 0 %, 4.2 V o mas = 100 % */
static int voltaje_a_porcentaje(float volts)
{
    if (volts <= 3.3f) return 0;
    if (volts >= 4.2f) return 100;
    return (int)((volts - 3.3f) * 100.0f / (4.2f - 3.3f));
}

static void actualizar_bateria(void)
{
    float volts = 0.0f;
    bsp_battery_get_voltage(&volts, NULL);

    if (volts < 2.5f) {            /* sin bateria conectada (solo USB) */
        lv_arc_set_value(ui_arcBattery, 0);
        lv_label_set_text(ui_lblBattery, "--%");
        return;
    }
    int pct = voltaje_a_porcentaje(volts);
    lv_arc_set_value(ui_arcBattery, pct);
    lv_label_set_text_fmt(ui_lblBattery, "%d%%", pct);
}

static void actualizar_temperatura(void)
{
    float celsius = 0.0f;
    if (bsp_temp_get_celsius(&celsius) != ESP_OK) {
        lv_label_set_text(ui_lblTemp, "-- C");
        return;
    }
    /* Sin %f: pasamos a decimas (41.3 -> 413) y separamos 41 y 3 */
    int decimas = (int)(celsius * 10);
    lv_label_set_text_fmt(ui_lblTemp, "%d.%d C", decimas / 10, decimas % 10);
}
static void actualizar_tiempo(void)
{
    /* esp_timer_get_time() da los microsegundos desde que arranco la placa */
    uint32_t total = (uint32_t)(esp_timer_get_time() / 1000000);
    uint32_t horas    = total / 3600;
    uint32_t minutos  = (total / 60) % 60;
    uint32_t segundos = total % 60;
    lv_label_set_text_fmt(ui_lblUptime, "%02u:%02u:%02u",
                          (unsigned)horas, (unsigned)minutos, (unsigned)segundos);
}
/* Todo lo que se actualiza cada segundo */
static void actualizar_datos(void)
{
    actualizar_bateria();
    actualizar_temperatura();
    actualizar_tiempo();
}
/* LVGL llama a esta funcion cada vez que pasa 1 segundo */
static void al_pasar_un_segundo(lv_timer_t *t)
{
    (void)t;
    actualizar_datos();
}

void scr_home_prepare(void)
{
    /* Se crea una sola vez y queda en pausa hasta que se entre a Home */
    s_timer = lv_timer_create(al_pasar_un_segundo, 1000, NULL);
    lv_timer_pause(s_timer);
    ESP_LOGD(TAG, "prepare");
}

void scr_home_init(void)
{
    actualizar_datos();            /* datos apenas se entra, sin esperar 1 s */
    lv_timer_resume(s_timer);
}

void scr_home_uninit(void)
{
    lv_timer_pause(s_timer);       /* fuera de Home no hace falta leer nada */
}

void scr_home_step(void)
{
}