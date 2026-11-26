#include "ui.h"

/* Colores de ESP Dashboard */
#define COLOR_FONDO     0x121212
#define COLOR_TARJETA   0x1F1F1F
#define COLOR_ROJO      0xE53935
#define COLOR_GRIS      0x9E9E9E

lv_obj_t *ui_scrSplash;
lv_obj_t *ui_lblAppName;
lv_obj_t *ui_lblLoading;

lv_obj_t *ui_scrHome;
lv_obj_t *ui_arcBattery;
lv_obj_t *ui_lblBattery;
lv_obj_t *ui_lblTemp;
lv_obj_t *ui_lblUptime;

/* Crea una pantalla vacia con el fondo oscuro */
static lv_obj_t *crear_pantalla(void)
{
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(scr, lv_color_hex(COLOR_FONDO), 0);
    return scr;
}

/* Crea una tarjeta con un titulo chico arriba y devuelve el label del valor */
static lv_obj_t *crear_tarjeta(lv_obj_t *padre, lv_align_t lado, lv_coord_t x, const char *titulo)
{
    lv_obj_t *tarjeta = lv_obj_create(padre);
    lv_obj_set_size(tarjeta, 145, 72);
    lv_obj_align(tarjeta, lado, x, -8);
    lv_obj_clear_flag(tarjeta, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(tarjeta, lv_color_hex(COLOR_TARJETA), 0);
    lv_obj_set_style_border_color(tarjeta, lv_color_hex(COLOR_ROJO), 0);
    lv_obj_set_style_border_width(tarjeta, 1, 0);

    lv_obj_t *lbl_titulo = lv_label_create(tarjeta);
    lv_label_set_text(lbl_titulo, titulo);
    lv_obj_set_style_text_color(lbl_titulo, lv_color_hex(COLOR_GRIS), 0);
    lv_obj_align(lbl_titulo, LV_ALIGN_TOP_MID, 0, -6);

    lv_obj_t *lbl_valor = lv_label_create(tarjeta);
    lv_obj_set_style_text_font(lbl_valor, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(lbl_valor, lv_color_white(), 0);
    lv_obj_align(lbl_valor, LV_ALIGN_BOTTOM_MID, 0, 4);
    return lbl_valor;
}

static void crear_splash(void)
{
    ui_scrSplash = crear_pantalla();

    ui_lblAppName = lv_label_create(ui_scrSplash);
    lv_label_set_text(ui_lblAppName, "ESP Dashboard");
    lv_obj_set_style_text_font(ui_lblAppName, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_color(ui_lblAppName, lv_color_hex(COLOR_ROJO), 0);
    lv_obj_align(ui_lblAppName, LV_ALIGN_CENTER, 0, -20);

    ui_lblLoading = lv_label_create(ui_scrSplash);
    lv_label_set_text(ui_lblLoading, "Iniciando");
    lv_obj_set_style_text_color(ui_lblLoading, lv_color_white(), 0);
    lv_obj_set_width(ui_lblLoading, 90);   /* ancho fijo: los puntos no mueven el texto */
    lv_obj_align(ui_lblLoading, LV_ALIGN_CENTER, 10, 20);
}

static void crear_home(void)
{
    ui_scrHome = crear_pantalla();

    /* Arco de bateria: grande, arriba y al centro, solo para mostrar */
    ui_arcBattery = lv_arc_create(ui_scrHome);
    lv_obj_set_size(ui_arcBattery, 140, 140);
    lv_obj_align(ui_arcBattery, LV_ALIGN_TOP_MID, 0, 6);
    lv_arc_set_range(ui_arcBattery, 0, 100);
    lv_arc_set_value(ui_arcBattery, 0);
    lv_obj_remove_style(ui_arcBattery, NULL, LV_PART_KNOB);   /* sin perilla */
    lv_obj_clear_flag(ui_arcBattery, LV_OBJ_FLAG_CLICKABLE);  /* no se arrastra */
    lv_obj_set_style_arc_color(ui_arcBattery, lv_color_hex(COLOR_TARJETA), LV_PART_MAIN);
    lv_obj_set_style_arc_color(ui_arcBattery, lv_color_hex(COLOR_ROJO), LV_PART_INDICATOR);

    ui_lblBattery = lv_label_create(ui_arcBattery);
    lv_label_set_text(ui_lblBattery, "--%");
    lv_obj_set_style_text_font(ui_lblBattery, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_color(ui_lblBattery, lv_color_white(), 0);
    lv_obj_center(ui_lblBattery);

    ui_lblTemp = crear_tarjeta(ui_scrHome, LV_ALIGN_BOTTOM_LEFT, 8, "Temperatura");
    lv_label_set_text(ui_lblTemp, "-- C");

    ui_lblUptime = crear_tarjeta(ui_scrHome, LV_ALIGN_BOTTOM_RIGHT, -8, "Encendido");
    lv_label_set_text(ui_lblUptime, "00:00:00");
}

void ui_init(void)
{
    crear_splash();
    crear_home();
    lv_disp_load_scr(ui_scrSplash);
}