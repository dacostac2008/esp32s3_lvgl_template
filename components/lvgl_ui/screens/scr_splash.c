#include "scr_splash.h"
#include "screens.h"
#include "ui.h"
#include "bsp_lvgl.h"
#include "esp_log.h"

static const char *TAG = "scr_splash";

/* LVGL llama a esta funcion en cada cuadro de la animacion de puntos.
 * "value" va de 0 a 4; con "% 4" queda 0, 1, 2 o 3 = cantidad de puntos. */
static void puntos_cb(void *obj, int32_t value)
{
    static const char *textos[] = {
        "Iniciando",
        "Iniciando.",
        "Iniciando..",
        "Iniciando..."
    };
    lv_label_set_text((lv_obj_t *)obj, textos[value % 4]);
}

/* Se ejecuta cuando tocan cualquier parte de la pantalla del splash */
static void al_tocar(lv_event_t *e)
{
    (void)e;
    ui_screens_navigate(SCREEN_HOME);
}

void scr_splash_prepare(void)
{
    /* "Cuando toquen la pantalla del splash, ejecuta al_tocar" */
    lv_obj_add_event_cb(ui_scrSplash, al_tocar, LV_EVENT_CLICKED, NULL);
    ESP_LOGD(TAG, "prepare");
}

void scr_splash_init(void)
{
    /* 1) La pantalla se enciende de a poco: de 0 a 100 en 800 ms */
    bsp_lvgl_backlight_fade(0, 100, 800);

    /* 2) Animacion de los puntos, repitiendose para siempre */
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, ui_lblLoading);
    lv_anim_set_exec_cb(&a, puntos_cb);
    lv_anim_set_values(&a, 0, 4);
    lv_anim_set_time(&a, 1600);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

void scr_splash_uninit(void)
{
    /* Al salir del splash, frenamos la animacion de los puntos */
    lv_anim_del(ui_lblLoading, puntos_cb);
}

void scr_splash_step(void)
{
}