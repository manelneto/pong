#include <lcom/lcf.h>

#include "sprite_view.h"

#include "../controller/video.h"

int draw_sprite(Sprite *sprite, uint16_t x, uint16_t y) {
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t color;
    for (uint16_t h = 0; h < height; h++)
        for (uint16_t w = 0; w < width; w++) {
            color = sprite->colors[w + h * width];
            if (color == 0xFFFFFE) continue; // TRANSPARENT
            if (video_draw_pixel(x + w, y + h, color)) {
                printf("%s: video_draw_pixel(x + w: %d, y + h: %d, color: 0x%x) error\n", __func__, x + w, y + h, color);
                return 1;
            }
        }
    return 0;
}
