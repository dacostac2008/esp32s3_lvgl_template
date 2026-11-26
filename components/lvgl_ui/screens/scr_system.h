#ifndef __SCR_SYSTEM_H__
#define __SCR_SYSTEM_H__

/* prepare(): una vez al arrancar  | init(): al entrar a la pantalla
 * uninit():  al salir             | step(): cada ~20 ms mientras esta activa */
void scr_system_prepare(void);
void scr_system_init(void);
void scr_system_uninit(void);
void scr_system_step(void);

#endif
