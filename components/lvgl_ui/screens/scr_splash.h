#ifndef __SCR_SPLASH_H__
#define __SCR_SPLASH_H__

/* Controlador de la pantalla de inicio (splash).
 * prepare(): una vez al arrancar  | init(): al entrar a la pantalla
 * uninit():  al salir             | step(): cada ~20 ms mientras esta activa */
void scr_splash_prepare(void);
void scr_splash_init(void);
void scr_splash_uninit(void);
void scr_splash_step(void);

#endif