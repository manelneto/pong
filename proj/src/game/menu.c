#include <lcom/lcf.h>

#include "menu.h"

#include "button.h"

static Button *play = NULL;
static Button *quit = NULL;

int menu_start(uint16_t xResolution, uint16_t yResolution) {
  play = construct_button(xResolution/3, yResolution/5, xResolution/3, yResolution/5);
  if (!play) {
    printf("%s: construct_button(%d, %d, %d, %d) error\n", __func__, xResolution/3, yResolution/5, xResolution/3, yResolution/5);
    return 1;
  }

  quit = construct_button(xResolution/3, 3 * yResolution/5, xResolution/3, yResolution/5);
  if (!quit) {
    printf("%s: construct_button(%d, %d, %d, %d) error\n", __func__, xResolution/3, 3 * yResolution/5, xResolution/3, yResolution/5);
    return 1;
  }

  return 0;
}

void menu_draw() {
  draw_button(play);
  draw_button(quit);
}

void menu_end() {
  destroy_button(play);
  destroy_button(quit);
}

/*Sprite *button;



void construct_menu() {
    button = construct_sprite((xpm_map_t) start_xpm);
}

int draw_menu() {
    uint16_t height = button->height;
    uint16_t width = button->width;
    uint32_t current_color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        current_color = button->colors[w + h*width];
        if (vg_draw_pixel(w, h, current_color) != 0) printf("bug");
        printf("painted (%d, %d) with 0x%x\n", w, h, current_color);
      }
    }
    return 0; 
}*/
