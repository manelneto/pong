#ifndef _VIDEO_GR_H_
#define _VIDEO_GR_H_

#include <stdbool.h>
#include <stdint.h>

#include <lcom/vbe.h>

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for using the video card in graphics mode
 */

/**
 * @brief Struct for RGB color components
*/
typedef struct {
  uint8_t red;   /*!< red component (R) */
  uint8_t green; /*!< green component (G) */
  uint8_t blue;  /*!< blue component (B) */
} rgb_8_8_8_t;

/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired graphics mode using a linear frame buffer, maps VRAM to the process' address space and initializes static global variables with the resolution of the screen, and the color depth (i.e the no. of bits per pixel).
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *(vg_init)(uint16_t mode);

/**
 * @brief Returns the RGB color components of a color
 * 
 * @param color color to convert to RGB
 * @return RGB color components of the color
*/
rgb_8_8_8_t (vg_get_colors)(uint32_t color);

/**
 * @brief Returns the color enconding of RGB color components
 * 
 * @param colors RGB color components to encode
 * @return Color enconding of the RGB color components
*/
uint32_t (vg_get_color)(rgb_8_8_8_t colors);

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
 * @brief Draws a horizontal line by changing the video RAM
 * 
 * Draws a horizontal line with the specified length and color, starting at the specified coordinates.
 * 
 * The x coordinates start at 0 and increase from left to right.
 * The y coordinates start at 0 and increase from top to bottom.
 * 
 * @param x horizontal coordinate of the initial point
 * @param y vertical coordinate of the initial point
 * @param len line's length in pixels
 * @param color color to set the pixel
 * @param addr virtual address of the VRAM location with the initial point
 * @return Return 0 on success and non-zero otherwise
 */

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a filled rectangle by changing the video RAM
 *
 * Draws a filled rectangle with the specified width, height and color starting at the specified coordinates.
 *
 * The x coordinates start at 0 and increase from left to right.
 * The y coordinates start at 0 and increase from top to bottom.
 * 
 * @param x	horizontal coordinate of the rectangle's top-left vertex
 * @param y	vertical coordinate of the rectangle's top-left vertex
 * @param width	 rectangle's width in pixels
 * @param height rectangle's height in pixels
 * @param color	color to set the pixel
 * 
 * @return Return 0 on success and non-zero otherwise
 */
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Draws a Pixmap on the screen at specified coordinates
 * 
 * @param x horizontal coordinate of upper-left corner, starts at 0 (leftmost pixel)
 * @param y vertical coordinate of upper-left corner, starts at 0 (top pixel)
 * @param image address of the image to draw
 * @return Return 0 upon success and non-zero otherwise
*/
int (vg_draw_pixmap)(uint16_t x, uint16_t y, xpm_image_t *image);

/**
 * @brief Resets the color of the screen pixels inside the specified area
 * 
 * @param xi x-coordinates of the upper-left corner
 * @param yi y-coordinates of the upper-left corner
 * @param xf x-coordinates of the bottom-right corner
 * @param yf y-coordinates of the bottom-right corner
 * @return Return 0 upon success and non-zero otherwise
*/
int (vg_clean)(uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf);

/**@}*/

#endif /* _VIDEO_GR_H_ */
