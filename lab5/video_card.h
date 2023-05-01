#ifndef __VIDEO_CARD_H
#define __VIDEO_CARD_H

#include <lcom/video_gr.h>

/** @defgroup video card video card
 * @{
 *
 * Functions for using the video card
 */

extern vbe_mode_info_t vmi_p;

/**
 * @brief Struct for RGB color components
*/
typedef struct {
  uint8_t red;   /*!< red component (R) */
  uint8_t green; /*!< green component (G) */
  uint8_t blue;  /*!< blue component (B) */
} rgb_8_8_8_t;

/**
 * @brief Draws (paints) a pixel by changing the video RAM
 * 
 * @param x horizontal coordinate of the pixel
 * @param y vertical coordinate of the pixel
 * @param color color to set the pixel
 * @return Return 0 upon success and non-zero otherwise
*/
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Normalizes the color (resets useless bits)
 * 
 * @param color color to normalize
 * @return Return the color normalized (with useless bits set to 0)
*/
uint32_t (vc_normalize_color)(uint32_t color);

/**
 * @brief Returns the RGB color components of a color
 * 
 * @param color color to convert to RGB
 * @return Returns the RGB color components of the color
*/
rgb_8_8_8_t (vc_get_colors)(uint32_t color);

/**
 * @brief Returns the color enconding of RGB color components
 * 
 * @param colors RGB color components to encode
 * @return Returns the color enconding of the RGB color components
*/
uint32_t (vc_get_color)(rgb_8_8_8_t colors);

/**
 * @brief Draws a rectangle-based colored pattern.
 * 
 * @param mode VBE graphics mode to use 
 * @param no_rectangles number of rectangles in each of the horizontal and vertical direction
 * @param first color to be used in the first rectangle (the rectangle at the top-left corner of the screen)
 * @param step difference between the values of the R/G component in adjacent rectangles in the same row/column
 * @return Return 0 upon success and non-zero otherwise
*/
int (vc_draw_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);

/**
 * @brief Draws a Pixmap on the screen at specified coordinates
 * 
 * @param x horizontal coordinate of upper-left corner, starts at 0 (leftmost pixel)
 * @param y vertical coordinate of upper-left corner, starts at 0 (top pixel)
 * @param image address of the image to draw
 * @return Return 0 upon success and non-zero otherwise
*/
int (vc_draw_pixmap)(uint16_t x, uint16_t y, xpm_image_t *image);

/**
 * @brief Resets the color of the screen pixels inside the specified area
 * 
 * @param xi x-coordinates of the upper-left corner
 * @param yi y-coordinates of the upper-left corner
 * @param xf x-coordinates of the bottom-right corner
 * @param yf y-coordinates of the bottom-right corner
 * @return Return 0 upon success and non-zero otherwise
*/
int (vc_clean)(uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf);

#endif /* __VIDEO_CARD_H */
