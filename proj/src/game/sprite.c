#include <lcom/lcf.h>

#include "sprite.h"

Sprite* construct_sprite(xpm_map_t xpm) {
    Sprite *sprite = (Sprite *) malloc(sizeof(Sprite));
    
    if (!sprite) {
        printf("%s: malloc() error\n", __func__);
        return NULL;
    }

    xpm_image_t image;
    sprite->colors = (uint32_t *) xpm_load(xpm, XPM_8_8_8_8, &image);
    
    if (!sprite->colors){
        free(sprite);
        printf("%s: xpm_load(xpm, XPM_8_8_8, &image) error\n", __func__);
        return NULL;
    }

    sprite->height = image.height;
    sprite->width = image.width;

    return sprite;
}

int draw_sprite(Sprite *sprite, uint16_t x, uint16_t y) {
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t color;
    for (uint16_t h = 0; h < height; h++)
        for (uint16_t w = 0; w < width; w++) {
            color = sprite->colors[w + h * width];
            if (color == 0xFFFFFE) continue;
            if (vg_draw_pixel(x + w, y + h, color)) {
                printf("%s: vg_draw_pixel(x + w: %d, y + h: %d, color: 0x%x) error\n", __func__, x + w, y + h, color);
                return 1;
            }
        }
    return 0;
}

void destroy_sprite(Sprite *sprite) {
    if (sprite) {
        if (sprite->colors)
            free(sprite->colors);
        free(sprite);
    }
}
