#include <lcom/lcf.h>

#include "sprite.h"

Sprite* construct_sprite(xpm_map_t xpm) {
    Sprite *sprite = (Sprite *) malloc(sizeof(Sprite));
    
    if (!sprite) {
        printf("%s: malloc() error\n", __func__);
        return NULL;
    }

    xpm_image_t image;
    sprite->colors = (uint32_t *) xpm_load(xpm, XPM_8_8_8, &image);
    
    if (!sprite->colors){
        free(sprite);
        printf("%s: xpm_load(xpm, XPM_8_8_8, &image) error\n", __func__);
        return NULL;
    }

    sprite->height = image.height;
    sprite->width = image.width;

    return sprite;
}

void destroy_sprite(Sprite *sprite) {
    if (sprite) {
        if (sprite->colors)
            free(sprite->colors);
        free(sprite);
    }
}
