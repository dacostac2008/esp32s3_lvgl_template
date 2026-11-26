#include "scr_system.h"
#include "screens.h"
#include "ui.h"
#include "esp_log.h"
#include "esp_system.h"       /* memoria libre y version de ESP-IDF */
#include "esp_chip_info.h"    /* modelo, nucleos y revision del chip */
#include "esp_flash.h"        /* tamano de la memoria flash */
#include "sdkconfig.h"        /* frecuencia de la CPU configurada */

static const char *TAG = "scr_system";

static lv_timer_t *s_timer = NULL;

/* Memoria libre mas baja que vimos desde el arranque (o desde el reset) */
static uint32_t s_memoria_minima = UINT32_MAX;

/* Bytes -> "312.4 KB" (sin %f: pasamos a decimas de KB) */
static void mostrar_kb(lv_obj_t *label, uint32_t bytes)
{
    uint32_t decimas = bytes * 10 / 1024;
    lv_label_set_text_fmt(label, "%u.%u KB", (unsigned)(decimas / 10), (unsigned)(decimas % 10));
}

/* Datos que no cambian: se cargan una sola vez */
static void cargar_datos_fijos(void)
{
    esp_chip_info_t chip;
    esp_chip_info(&chip);
    /* revision viene como 2 = v0.2, 101 = v1.1 */
    lv_label_set_text_fmt(ui_lblChip, "ESP32-S3 v%d.%d, %d nucleos",
                          chip.revision / 100, chip.revision % 100, chip.cores);

    lv_label_set_text_fmt(ui_lblCpu, "%d MHz", CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ);

    uint32_t flash = 0;
    if (esp_flash_get_size(NULL, &flash) == ESP_OK) {
        lv_label_set_text_fmt(ui_lblFlash, "%u MB", (unsigned)(flash / (1024 * 1024)));
    }

    lv_label_set_text(ui_lblIdf, esp_get_idf_version());
}

/* Datos que cambian: la memoria libre (y su minimo) */
static void actualizar_memoria(void)
{
    uint32_t libre = esp_get_free_heap_size();
    if (libre < s_memoria_minima) {
        s_memoria_minima = libre;
    }
    mostrar_kb(ui_lblHeap, libre);
    mostrar_kb(ui_lblHeapMin, s_memoria_minima);
}

static void al_pasar_un_segundo(lv_timer_t *t)
{
    (void)t;
    actualizar_memoria();
}

/* Boton "Reset minimo": el minimo vuelve a empezar desde el valor actual */
static void al_tocar_reset(lv_event_t *e)
{
    (void)e;
    s_memoria_minima = esp_get_free_heap_size();
    mostrar_kb(ui_lblHeapMin, s_memoria_minima);
}

void scr_system_prepare(void)
{
    cargar_datos_fijos();
    lv_obj_add_event_cb(ui_btnResetMin, al_tocar_reset, LV_EVENT_CLICKED, NULL);

    s_timer = lv_timer_create(al_pasar_un_segundo, 1000, NULL);
    lv_timer_pause(s_timer);
    ESP_LOGD(TAG, "prepare");
}

void scr_system_init(void)
{
    actualizar_memoria();
    lv_timer_resume(s_timer);
}

void scr_system_uninit(void)
{
    lv_timer_pause(s_timer);
}

void scr_system_step(void)
{
}