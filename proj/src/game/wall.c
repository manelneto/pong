#include <lcom/lcf.h>

#include "wall.h"

Wall* construct_wall(uint16_t x, uint16_t yi, uint16_t yf) {
    Wall* wall = (Wall*) malloc(sizeof(Wall));

    if (!wall) {
        printf("%s: malloc() error\n", __func__);
        return NULL;
    }

    wall->x = x;
    wall->yi = yi;
    wall->yf = yf;

    return wall;
}

void destroy_wall(Wall *wall) {
    if (wall)
        free(wall);
}
