#ifndef _MENU_H_
#define _MENU_H_

/** @defgroup menu menu
 * @{
 * 
 * Functions related to the menu
*/

/**
 * 
*/
int menu_start(uint16_t xResolution, uint16_t yResolution);

/**
 * 
*/
void menu_draw();

/**
 * 
*/
void menu_timer_ih();

/**
 * 
*/
void menu_keyboard_ih();

/**
 * 
*/
void menu_mouse_ih();

/**
 * 
*/
void menu_end();


/**@}*/

#endif /* _MENU_H_ */
