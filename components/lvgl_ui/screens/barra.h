#ifndef __BARRA_H__
#define __BARRA_H__

#include "screens.h"

/* Barra de navegacion de abajo. Se crea UNA sola vez sobre lv_layer_top(),
 * una capa que LVGL dibuja encima de cualquier pantalla: asi aparece en las
 * tres sin repetirla (un objeto LVGL solo puede estar en un lugar). */
void barra_crear(void);

/* Pinta de rojo el boton de la pantalla activa */
void barra_marcar(ui_screens_t pantalla);

#endif