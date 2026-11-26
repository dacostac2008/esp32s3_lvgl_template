#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/* UI de "ESP Dashboard": solo crea los widgets (como un export de
 * SquareLine). Los eventos y los datos van en components/lvgl_ui/screens/. */
void ui_init(void);

/* Pantalla de inicio */
extern lv_obj_t *ui_scrSplash;
extern lv_obj_t *ui_lblAppName;
extern lv_obj_t *ui_lblLoading;

/* Pantalla principal */
extern lv_obj_t *ui_scrHome;
extern lv_obj_t *ui_arcBattery;
extern lv_obj_t *ui_lblBattery;
extern lv_obj_t *ui_lblTemp;
extern lv_obj_t *ui_lblUptime;

#ifdef __cplusplus
}
#endif

#endif