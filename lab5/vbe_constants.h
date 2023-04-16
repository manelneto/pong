#ifndef _LCOM_VBE_H_
#define _LCOM_VBE_H_

#include <lcom/lcf.h>

/** @defgroup VBE VBE
 * @{
 *
 * Constants for using VBE
 */

#define VBE_INTNO  0x10 /**< @brief software interrupt instruction */
#define VBE_REG_AH 0x4F /**< @brief AH register value */

/* VBE return codes */

#define VBE_FUNCTION_SUPPORTED_AL   0x4F /**< @brief value of the AL register if the function called is supported */
#define VBE_FUNCTION_SUCCESS_AH     0x00 /**< @brief value of the AH register if the function completed successfully */
#define VBE_FUNCTION_FAILED_AH      0x01 /**< @brief value of the AH register if the function call failed */
#define VBE_FUNCTION_UNSUPPORTED_AH 0x02 /**< @brief value of the AH register if the function is not supported in current HW configuration */
#define VBE_FUNCTION_INVALID_AH     0x03 /**< @brief value of the AH register if the function is invalid in current video mode */

/* VBE functions */

#define VBE_RETURN_CONTROLLER_INFO 0x00 /**< @brief function to return the capabilites of the controller - must provide address for returned info in registers ES:DI */
#define VBE_RETURN_MODE_INFO       0x01 /**< @brief function to return VBE mode information - mode is passed on CX and must provide address for returned info in registers ES:DI */
#define VBE_SET_MODE               0x02 /**< @brief function to initialize the controller and set a video mode - mode is passed in register BX, which should have bit 14 set */

/* OTHER */

#define VBE_SET_LINEAR_MODE        BIT(14) /**< @brief set the linear frame buffer model */
#define VBE_RETURN_TO_TEXT_MODE_AH 0x00    /**< @brief value to set the AH register to return to text mode */
#define VBE_RETURN_TO_TEXT_MODE_AL 0x03    /**< @brief value to set the AL register to return to text mode */
#define VBE_INDEXED_COLOR_MODE     0x105   /**< @brief indexed color mode */

/**@}*/

#endif /* _LCOM_VBE_H */
