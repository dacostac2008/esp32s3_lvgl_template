#include "scr_settings.h"
#include "screens.h"
#include "screens_timeout.h"
#include "ui.h"
#include "bsp_display.h"
#include "esp_log.h"

static const char *TAG = "scr_settings";

#define APAGADO_MS          30000   /* 30 segundos sin tocar = pantalla apagada */
#define BRILLO_DE_FABRICA   100

/* ---------------- brillo ---------------- */

static void poner_brillo(int32_t porcentaje)
{
    bsp_display_set_brightness((uint8_t)porcentaje);
    lv_label_set_text_fmt(ui_lblBrillo, "%d%%", (int)porcentaje);
}

/* Se ejecuta mientras se arrastra el slider: el brillo cambia en vivo */
static void al_mover_slider(lv_event_t *e)
{
    (void)e;
    poner_brillo(lv_slider_get_value(ui_sldBrillo));
}

/* ---------------- apagado automatico ---------------- */

static void poner_apagado(bool activado)
{
    disp_timeout_set_off_ms(activado ? APAGADO_MS : TIMEOUT_NEVER);
}

static void al_cambiar_switch(lv_event_t *e)
{
    (void)e;
    poner_apagado(lv_obj_has_state(ui_swApagado, LV_STATE_CHECKED));
}

/* ---------------- restaurar ---------------- */

static void al_tocar_restaurar(lv_event_t *e)
{
    (void)e;
    /* Mover el slider o el switch por codigo NO dispara sus eventos,
     * por eso ademas de moverlos aplicamos los valores a mano. */
    lv_slider_set_value(ui_sldBrillo, BRILLO_DE_FABRICA, LV_ANIM_ON);
    poner_brillo(BRILLO_DE_FABRICA);

    lv_obj_clear_state(ui_swApagado, LV_STATE_CHECKED);
    poner_apagado(false);
}

/* ---------------------------------------------- */

void scr_settings_prepare(void)
{
    lv_obj_add_event_cb(ui_sldBrillo, al_mover_slider, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_swApagado, al_cambiar_switch, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_btnRestaurar, al_tocar_restaurar, LV_EVENT_CLICKED, NULL);

    /* __DATE__ y __TIME__ los completa el compilador con la fecha de hoy */
    lv_label_set_text(ui_lblCompilado, "Compilado: " __DATE__ " " __TIME__);
    ESP_LOGD(TAG, "prepare");
}

void scr_settings_init(void)
{
    /* Al entrar, el slider muestra el brillo que hay de verdad */
    int32_t actual = bsp_display_get_brightness();
    lv_slider_set_value(ui_sldBrillo, actual, LV_ANIM_OFF);
    lv_label_set_text_fmt(ui_lblBrillo, "%d%%", (int)actual);
}

void scr_settings_uninit(void)
{
}

void scr_settings_step(void)
{
}