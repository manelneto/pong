#ifndef _SPRITE_VIEW_H_
#define _SPRITE_VIEW_H_

#include "../model/sprite.h"

int draw_sprite(Sprite *sprite, uint16_t x, uint16_t y);

int draw_times(uint16_t, uint16_t y);

int draw_digit(uint8_t digit, uint16_t x, uint16_t y);

int draw_number(uint32_t number, uint16_t x, uint16_t y);

#endif /* _SPRITE_VIEW_H_ */
