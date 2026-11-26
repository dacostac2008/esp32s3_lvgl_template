#ifndef __ENTRADA_H__
#define __ENTRADA_H__

/*
 * Boton fisico (BOOT) como entrada de LVGL.
 *
 * Camino de un click:
 *   1. El componente espressif/button detecta el click en SU propia tarea,
 *      que NO es la de LVGL -> ahi solo se encola UI_UPDATE_BOTON_FISICO
 *      con ui_update_cmd(). Nada de lv_*.
 *   2. El timer de LVGL vacia la cola y llama a entrada_apretar(), que ya
 *      corre dentro de LVGL.
 *   3. entrada_apretar() enfoca en el grupo (lv_group) el boton de la
 *      pantalla activa y "aprieta" ENTER en un teclado virtual (lv_indev).
 *   4. LVGL le manda LV_EVENT_CLICKED a ese boton, como si lo tocaran.
 */

/* Crea el teclado virtual y el grupo, y escucha el boton fisico */
void entrada_iniciar(void);

/* Hace click en el boton de accion de la pantalla activa (solo desde LVGL) */
void entrada_apretar(void);

#endif