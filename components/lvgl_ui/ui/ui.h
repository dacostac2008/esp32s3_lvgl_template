#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/* UI de "ESP Dashboard" (Asignacion 2): solo crea los widgets, como un
 * export de SquareLine. Los eventos y los datos van en screens/.
 * Las pantallas dejan libres los ultimos UI_ALTO_BARRA px: ahi va la barra
 * de navegacion, que se crea por codigo en screens/barra.c */
#define UI_ALTO_BARRA   40

#define COLOR_FONDO     0x121212
#define COLOR_TARJETA   0x1F1F1F
#define COLOR_ROJO      0xE53935
#define COLOR_GRIS      0x9E9E9E

void ui_init(void);

/* Pantalla Inicio */
extern lv_obj_t *ui_scrHome;
extern lv_obj_t *ui_lblEstado;
extern lv_obj_t *ui_btnActualizar;
extern lv_obj_t *ui_arcBattery;
extern lv_obj_t *ui_lblBattery;
extern lv_obj_t *ui_lblTemp;
extern lv_obj_t *ui_lblUptime;

/* Pantalla Sistema */
extern lv_obj_t *ui_scrSystem;
extern lv_obj_t *ui_lblChip;
extern lv_obj_t *ui_lblCpu;
extern lv_obj_t *ui_lblFlash;
extern lv_obj_t *ui_lblIdf;
extern lv_obj_t *ui_lblHeap;
extern lv_obj_t *ui_lblHeapMin;
extern lv_obj_t *ui_btnResetMin;

/* Pantalla Ajustes */
extern lv_obj_t *ui_scrSettings;
extern lv_obj_t *ui_sldBrillo;
extern lv_obj_t *ui_lblBrillo;
extern lv_obj_t *ui_swApagado;
extern lv_obj_t *ui_lblCompilado;
extern lv_obj_t *ui_btnRestaurar;

#ifdef __cplusplus
}
#endif

#endif