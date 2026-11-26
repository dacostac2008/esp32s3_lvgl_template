#include "barra.h"
#include "ui.h"

/* Textos de los botones, en el mismo orden que la lista de screens.h */
static const char *textos[SCREEN_MAX] = {
    [SCREEN_HOME]     = LV_SYMBOL_HOME " Inicio",
    [SCREEN_SYSTEM]   = LV_SYMBOL_LIST " Sistema",
    [SCREEN_SETTINGS] = LV_SYMBOL_SETTINGS " Ajustes",
};

static lv_obj_t *botones[SCREEN_MAX];

/* Al tocar un boton: ir a la pantalla que tiene guardada en user_data */
static void al_tocar_boton(lv_event_t *e)
{
    ui_screens_t destino = (ui_screens_t)(uintptr_t)lv_event_get_user_data(e);
    ui_screens_navigate(destino);
}

void barra_crear(void)
{
    lv_obj_t *barra = lv_obj_create(lv_layer_top());
    lv_obj_set_size(barra, LV_PCT(100), UI_ALTO_BARRA);
    lv_obj_align(barra, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_flag(barra, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(barra, 0, 0);
    lv_obj_set_style_border_width(barra, 0, 0);
    lv_obj_set_style_pad_all(barra, 4, 0);
    lv_obj_set_style_bg_color(barra, lv_color_hex(COLOR_TARJETA), 0);
    /* Los botones uno al lado del otro, repartidos parejo */
    lv_obj_set_flex_flow(barra, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(barra, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    for (int i = 0; i < SCREEN_MAX; i++) {
        lv_obj_t *btn = lv_btn_create(barra);
        lv_obj_set_size(btn, 98, UI_ALTO_BARRA - 8);
        lv_obj_set_style_shadow_width(btn, 0, 0);
        /* Normal: transparente. Marcado (CHECKED): rojo */
        lv_obj_set_style_bg_opa(btn, LV_OPA_TRANSP, LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(btn, lv_color_hex(COLOR_ROJO), LV_STATE_CHECKED);

        lv_obj_t *lbl = lv_label_create(btn);
        lv_label_set_text(lbl, textos[i]);
        lv_obj_center(lbl);

        /* Cada boton guarda a que pantalla lleva (en user_data) */
        lv_obj_add_event_cb(btn, al_tocar_boton, LV_EVENT_CLICKED, (void *)(uintptr_t)i);
        botones[i] = btn;
    }
}

void barra_marcar(ui_screens_t pantalla)
{
    for (int i = 0; i < SCREEN_MAX; i++) {
        if (i == (int)pantalla) {
            lv_obj_add_state(botones[i], LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(botones[i], LV_STATE_CHECKED);
        }
    }
}