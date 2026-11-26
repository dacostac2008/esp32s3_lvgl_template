#include "entrada.h"
#include "screens.h"
#include "screens_update.h"
#include "ui.h"
#include "bsp_boton.h"

static lv_group_t *s_grupo = NULL;
static bool s_enter_pendiente = false;

/* OJO: corre en la tarea del componente button, NO en LVGL.
 * Por eso no toca nada de lv_*: solo deja el pedido en la cola. */
static void al_click_fisico(void *boton, void *datos)
{
    (void)boton;
    (void)datos;
    ui_update_cmd(UI_UPDATE_BOTON_FISICO, NULL);
}

/* Teclado virtual: LVGL lo lee todo el tiempo. Si hay un ENTER pendiente
 * lo reporta apretado una vez y despues suelto -> eso es un click. */
static void leer_teclado(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    (void)drv;
    data->key = LV_KEY_ENTER;
    if (s_enter_pendiente) {
        s_enter_pendiente = false;
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void entrada_iniciar(void)
{
    s_grupo = lv_group_create();

    static lv_indev_drv_t teclado;
    lv_indev_drv_init(&teclado);
    teclado.type = LV_INDEV_TYPE_KEYPAD;
    teclado.read_cb = leer_teclado;
    lv_indev_t *indev = lv_indev_drv_register(&teclado);
    lv_indev_set_group(indev, s_grupo);

    button_handle_t boton = bsp_boton_handle();
    if (boton != NULL) {
        iot_button_register_cb(boton, BUTTON_SINGLE_CLICK, NULL, al_click_fisico, NULL);
    }
}

void entrada_apretar(void)
{
    /* Que boton aprieta el boton fisico en cada pantalla */
    lv_obj_t *destino = NULL;
    switch (ui_screens_get_current()) {
        case SCREEN_HOME:     destino = ui_btnActualizar; break;
        case SCREEN_SYSTEM:   destino = ui_btnResetMin;   break;
        case SCREEN_SETTINGS: destino = ui_btnRestaurar;  break;
        default: return;
    }

    lv_group_remove_all_objs(s_grupo);
    lv_group_add_obj(s_grupo, destino);
    lv_group_focus_obj(destino);
    s_enter_pendiente = true;
}