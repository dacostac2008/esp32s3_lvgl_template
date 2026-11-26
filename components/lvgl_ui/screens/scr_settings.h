#ifndef __SCR_SETTINGS_H__
#define __SCR_SETTINGS_H__

/* prepare(): una vez al arrancar  | init(): al entrar a la pantalla
 * uninit():  al salir             | step(): cada ~20 ms mientras esta activa */
void scr_settings_prepare(void);
void scr_settings_init(void);
void scr_settings_uninit(void);
void scr_settings_step(void);

#endif
