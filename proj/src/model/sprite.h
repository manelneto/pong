#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../controller/video.h"

/**
 * @brief Struct for the sprite
*/
typedef struct {
    uint16_t height;
    uint16_t width;
    uint32_t *colors;
} Sprite;

/**
 * 
*/
Sprite* construct_sprite(xpm_map_t xpm);

/**
 * 
*/
void destroy_sprite(Sprite *sprite);

#endif /* _SPRITE_H_ */
