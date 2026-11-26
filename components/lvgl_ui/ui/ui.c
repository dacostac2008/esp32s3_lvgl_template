#include "ui.h"

lv_obj_t *ui_scrHome;
lv_obj_t *ui_lblEstado;
lv_obj_t *ui_btnActualizar;
lv_obj_t *ui_arcBattery;
lv_obj_t *ui_lblBattery;
lv_obj_t *ui_lblTemp;
lv_obj_t *ui_lblUptime;

lv_obj_t *ui_scrSystem;
lv_obj_t *ui_lblChip;
lv_obj_t *ui_lblCpu;
lv_obj_t *ui_lblFlash;
lv_obj_t *ui_lblIdf;
lv_obj_t *ui_lblHeap;
lv_obj_t *ui_lblHeapMin;
lv_obj_t *ui_btnResetMin;

lv_obj_t *ui_scrSettings;
lv_obj_t *ui_sldBrillo;
lv_obj_t *ui_lblBrillo;
lv_obj_t *ui_swApagado;
lv_obj_t *ui_lblCompilado;
lv_obj_t *ui_btnRestaurar;

/* ---------------- piezas que se repiten ---------------- */

static lv_obj_t *crear_pantalla(const char *titulo)
{
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(scr, lv_color_hex(COLOR_FONDO), 0);

    lv_obj_t *lbl = lv_label_create(scr);
    lv_label_set_text(lbl, titulo);
    lv_obj_set_style_text_color(lbl, lv_color_hex(COLOR_ROJO), 0);
    lv_obj_align(lbl, LV_ALIGN_TOP_LEFT, 10, 8);
    return scr;
}

/* Tarjeta con titulo chico arriba; devuelve el label del valor */
static lv_obj_t *crear_tarjeta(lv_obj_t *padre, lv_coord_t x, lv_coord_t y, const char *titulo)
{
    lv_obj_t *tarjeta = lv_obj_create(padre);
    lv_obj_set_size(tarjeta, 145, 56);
    lv_obj_set_pos(tarjeta, x, y);
    lv_obj_clear_flag(tarjeta, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(tarjeta, 4, 0);
    lv_obj_set_style_bg_color(tarjeta, lv_color_hex(COLOR_TARJETA), 0);
    lv_obj_set_style_border_color(tarjeta, lv_color_hex(COLOR_ROJO), 0);
    lv_obj_set_style_border_width(tarjeta, 1, 0);

    lv_obj_t *lbl_titulo = lv_label_create(tarjeta);
    lv_label_set_text(lbl_titulo, titulo);
    lv_obj_set_style_text_color(lbl_titulo, lv_color_hex(COLOR_GRIS), 0);
    lv_obj_align(lbl_titulo, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *lbl_valor = lv_label_create(tarjeta);
    lv_obj_set_style_text_font(lbl_valor, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(lbl_valor, lv_color_white(), 0);
    lv_obj_align(lbl_valor, LV_ALIGN_BOTTOM_MID, 0, 0);
    return lbl_valor;
}

/* Boton rojo abajo a la derecha (encima de la barra) */
static lv_obj_t *crear_boton(lv_obj_t *padre, const char *texto)
{
    lv_obj_t *btn = lv_btn_create(padre);
    lv_obj_set_size(btn, 140, 34);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_RIGHT, -10, -(UI_ALTO_BARRA + 8));
    lv_obj_set_style_bg_color(btn, lv_color_hex(COLOR_ROJO), 0);

    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, texto);
    lv_obj_center(lbl);
    return btn;
}

/* Fila "Titulo ......... valor" dentro de un panel; devuelve el valor */
static lv_obj_t *crear_fila(lv_obj_t *panel, int fila, const char *titulo)
{
    lv_obj_t *lbl_titulo = lv_label_create(panel);
    lv_label_set_text(lbl_titulo, titulo);
    lv_obj_set_style_text_color(lbl_titulo, lv_color_hex(COLOR_GRIS), 0);
    lv_obj_set_pos(lbl_titulo, 0, fila * 18);

    lv_obj_t *lbl_valor = lv_label_create(panel);
    lv_label_set_text(lbl_valor, "-");
    lv_obj_set_style_text_color(lbl_valor, lv_color_white(), 0);
    lv_obj_align(lbl_valor, LV_ALIGN_TOP_RIGHT, 0, fila * 18);
    return lbl_valor;
}

/* ---------------- pantallas ---------------- */

static void crear_home(void)
{
    ui_scrHome = crear_pantalla("Inicio");

    /* Indicador de estado (el color lo pone scr_home.c) */
    ui_lblEstado = lv_label_create(ui_scrHome);
    lv_label_set_text(ui_lblEstado, "...");
    lv_obj_set_style_text_color(ui_lblEstado, lv_color_white(), 0);
    lv_obj_align(ui_lblEstado, LV_ALIGN_TOP_LEFT, 10, 30);

    /* Boton para actualizar a mano (arriba a la derecha) */
    ui_btnActualizar = lv_btn_create(ui_scrHome);
    lv_obj_set_size(ui_btnActualizar, 40, 40);
    lv_obj_align(ui_btnActualizar, LV_ALIGN_TOP_RIGHT, -10, 8);
    lv_obj_set_style_bg_color(ui_btnActualizar, lv_color_hex(COLOR_ROJO), 0);
    lv_obj_t *icono = lv_label_create(ui_btnActualizar);
    lv_label_set_text(icono, LV_SYMBOL_REFRESH);
    lv_obj_center(icono);

    /* Arco de bateria arriba al centro */
    ui_arcBattery = lv_arc_create(ui_scrHome);
    lv_obj_set_size(ui_arcBattery, 104, 104);
    lv_obj_align(ui_arcBattery, LV_ALIGN_TOP_MID, 0, 4);
    lv_arc_set_range(ui_arcBattery, 0, 100);
    lv_arc_set_value(ui_arcBattery, 0);
    lv_obj_remove_style(ui_arcBattery, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(ui_arcBattery, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_width(ui_arcBattery, 10, LV_PART_MAIN);
    lv_obj_set_style_arc_width(ui_arcBattery, 10, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(ui_arcBattery, lv_color_hex(COLOR_TARJETA), LV_PART_MAIN);
    lv_obj_set_style_arc_color(ui_arcBattery, lv_color_hex(COLOR_ROJO), LV_PART_INDICATOR);

    ui_lblBattery = lv_label_create(ui_arcBattery);
    lv_label_set_text(ui_lblBattery, "--%");
    lv_obj_set_style_text_font(ui_lblBattery, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(ui_lblBattery, lv_color_white(), 0);
    lv_obj_center(ui_lblBattery);

    /* Dos tarjetas abajo, encima de la barra */
    ui_lblTemp = crear_tarjeta(ui_scrHome, 10, 136, "Temperatura");
    lv_label_set_text(ui_lblTemp, "-- C");
    ui_lblUptime = crear_tarjeta(ui_scrHome, 165, 136, "Encendido");
    lv_label_set_text(ui_lblUptime, "00:00:00");
}

static void crear_system(void)
{
    ui_scrSystem = crear_pantalla("Sistema");

    lv_obj_t *panel = lv_obj_create(ui_scrSystem);
    lv_obj_set_size(panel, 300, 6 * 18 + 16);
    lv_obj_align(panel, LV_ALIGN_TOP_MID, 0, 30);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(panel, 8, 0);
    lv_obj_set_style_bg_color(panel, lv_color_hex(COLOR_TARJETA), 0);
    lv_obj_set_style_border_width(panel, 0, 0);

    ui_lblChip    = crear_fila(panel, 0, "Chip");
    ui_lblCpu     = crear_fila(panel, 1, "CPU");
    ui_lblFlash   = crear_fila(panel, 2, "Flash");
    ui_lblIdf     = crear_fila(panel, 3, "ESP-IDF");
    ui_lblHeap    = crear_fila(panel, 4, "Memoria libre");
    ui_lblHeapMin = crear_fila(panel, 5, "Memoria minima");

    ui_btnResetMin = crear_boton(ui_scrSystem, LV_SYMBOL_LOOP " Reset minimo");
}

static void crear_settings(void)
{
    ui_scrSettings = crear_pantalla("Ajustes");

    lv_obj_t *lbl = lv_label_create(ui_scrSettings);
    lv_label_set_text(lbl, "Brillo");
    lv_obj_set_style_text_color(lbl, lv_color_white(), 0);
    lv_obj_set_pos(lbl, 10, 44);

    ui_sldBrillo = lv_slider_create(ui_scrSettings);
    lv_obj_set_size(ui_sldBrillo, 170, 10);
    lv_obj_set_pos(ui_sldBrillo, 80, 48);
    lv_slider_set_range(ui_sldBrillo, 5, 100);    /* minimo 5: que nunca quede negra */
    lv_slider_set_value(ui_sldBrillo, 100, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(ui_sldBrillo, lv_color_hex(COLOR_TARJETA), LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui_sldBrillo, lv_color_hex(COLOR_ROJO), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(ui_sldBrillo, lv_color_hex(COLOR_ROJO), LV_PART_KNOB);

    ui_lblBrillo = lv_label_create(ui_scrSettings);
    lv_label_set_text(ui_lblBrillo, "100%");
    lv_obj_set_style_text_color(ui_lblBrillo, lv_color_white(), 0);
    lv_obj_align(ui_lblBrillo, LV_ALIGN_TOP_RIGHT, -10, 44);

    lbl = lv_label_create(ui_scrSettings);
    lv_label_set_text(lbl, "Apagar pantalla (30 s)");
    lv_obj_set_style_text_color(lbl, lv_color_white(), 0);
    lv_obj_set_pos(lbl, 10, 86);

    ui_swApagado = lv_switch_create(ui_scrSettings);
    lv_obj_set_size(ui_swApagado, 50, 26);
    lv_obj_align(ui_swApagado, LV_ALIGN_TOP_RIGHT, -10, 80);
    lv_obj_set_style_bg_color(ui_swApagado, lv_color_hex(COLOR_ROJO), LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_lblCompilado = lv_label_create(ui_scrSettings);
    lv_label_set_text(ui_lblCompilado, "Compilado: -");
    lv_obj_set_style_text_color(ui_lblCompilado, lv_color_hex(COLOR_GRIS), 0);
    lv_obj_set_pos(ui_lblCompilado, 10, 124);

    ui_btnRestaurar = crear_boton(ui_scrSettings, LV_SYMBOL_REFRESH " Restaurar");
}

void ui_init(void)
{
    crear_home();
    crear_system();
    crear_settings();
    lv_disp_load_scr(ui_scrHome);
}