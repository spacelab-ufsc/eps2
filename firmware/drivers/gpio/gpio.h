/*
 * gpio.h
 * 
 * Copyright (C) 2019, SpaceLab.
 * 
 * This file is part of EPS 2.0.
 * 
 * EPS 2.0 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * EPS 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with EPS 2.0. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief GPIO driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/24
 * 
 * \defgroup gpio GPIO
 * \ingroup drivers
 * \{
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <stdbool.h>

#define GPIO_MODULE_NAME    "GPIO"

#define GPIO_STATE_HIGH     (true)
#define GPIO_STATE_LOW      (false)

/**
 * \brief GPIO pins.
 */
typedef enum
{
    GPIO_PIN_0=0,           /**< GPIO pin 0. */
    GPIO_PIN_1,             /**< GPIO pin 1. */
    GPIO_PIN_2,             /**< GPIO pin 2. */
    GPIO_PIN_3,             /**< GPIO pin 3. */
    GPIO_PIN_4,             /**< GPIO pin 4. */
    GPIO_PIN_5,             /**< GPIO pin 5. */
    GPIO_PIN_6,             /**< GPIO pin 6. */
    GPIO_PIN_7,             /**< GPIO pin 7. */
    GPIO_PIN_8,             /**< GPIO pin 8. */
    GPIO_PIN_9,             /**< GPIO pin 9. */
    GPIO_PIN_10,            /**< GPIO pin 10. */
    GPIO_PIN_11,            /**< GPIO pin 11. */
    GPIO_PIN_12,            /**< GPIO pin 12. */
    GPIO_PIN_13,            /**< GPIO pin 13. */
    GPIO_PIN_14,            /**< GPIO pin 14. */
    GPIO_PIN_15,            /**< GPIO pin 15. */
    GPIO_PIN_16,            /**< GPIO pin 16. */
    GPIO_PIN_17,            /**< GPIO pin 17. */
    GPIO_PIN_18,            /**< GPIO pin 18. */
    GPIO_PIN_19,            /**< GPIO pin 19. */
    GPIO_PIN_20,            /**< GPIO pin 20. */
    GPIO_PIN_21,            /**< GPIO pin 21. */
    GPIO_PIN_22,            /**< GPIO pin 22. */
    GPIO_PIN_23,            /**< GPIO pin 23. */
    GPIO_PIN_24,            /**< GPIO pin 24. */
    GPIO_PIN_25,            /**< GPIO pin 25. */
    GPIO_PIN_26,            /**< GPIO pin 26. */
    GPIO_PIN_27,            /**< GPIO pin 27. */
    GPIO_PIN_28,            /**< GPIO pin 28. */
    GPIO_PIN_29,            /**< GPIO pin 29. */
    GPIO_PIN_30,            /**< GPIO pin 30. */
    GPIO_PIN_31,            /**< GPIO pin 31. */
    GPIO_PIN_32,            /**< GPIO pin 32. */
    GPIO_PIN_33,            /**< GPIO pin 33. */
    GPIO_PIN_34,            /**< GPIO pin 34. */
    GPIO_PIN_35,            /**< GPIO pin 35. */
    GPIO_PIN_36,            /**< GPIO pin 36. */
    GPIO_PIN_37,            /**< GPIO pin 37. */
    GPIO_PIN_38,            /**< GPIO pin 38. */
    GPIO_PIN_39,            /**< GPIO pin 39. */
    GPIO_PIN_40,            /**< GPIO pin 40. */
    GPIO_PIN_41,            /**< GPIO pin 41. */
    GPIO_PIN_42,            /**< GPIO pin 42. */
    GPIO_PIN_43,            /**< GPIO pin 43. */
    GPIO_PIN_44,            /**< GPIO pin 44. */
    GPIO_PIN_45,            /**< GPIO pin 45. */
    GPIO_PIN_46,            /**< GPIO pin 46. */
    GPIO_PIN_47,            /**< GPIO pin 47. */
    GPIO_PIN_48,            /**< GPIO pin 48. */
    GPIO_PIN_49,            /**< GPIO pin 49. */
    GPIO_PIN_50,            /**< GPIO pin 50. */
    GPIO_PIN_51,            /**< GPIO pin 51. */
    GPIO_PIN_52,            /**< GPIO pin 52. */
    GPIO_PIN_53,            /**< GPIO pin 53. */
    GPIO_PIN_54,            /**< GPIO pin 54. */
    GPIO_PIN_55,            /**< GPIO pin 55. */
    GPIO_PIN_56,            /**< GPIO pin 56. */
    GPIO_PIN_57,            /**< GPIO pin 57. */
    GPIO_PIN_58,            /**< GPIO pin 58. */
    GPIO_PIN_59,            /**< GPIO pin 59. */
    GPIO_PIN_60,            /**< GPIO pin 60. */
    GPIO_PIN_61,            /**< GPIO pin 61. */
    GPIO_PIN_62,            /**< GPIO pin 62. */
    GPIO_PIN_63,            /**< GPIO pin 63. */
    GPIO_PIN_64,            /**< GPIO pin 64. */
    GPIO_PIN_65,            /**< GPIO pin 65. */
    GPIO_PIN_66,            /**< GPIO pin 66. */
    GPIO_PIN_67,            /**< GPIO pin 67. */
    GPIO_PIN_68,            /**< GPIO pin 68. */
    GPIO_PIN_69             /**< GPIO pin 69. */
} gpio_pins_e;

/**
 * \brief GPIO modes.
 */
typedef enum
{
    GPIO_MODE_OUTPUT=0,     /**< GPIO as output. */
    GPIO_MODE_INPUT         /**< GPIO as input. */
} gpio_modes_e;

/**
 * \brief GPIO pin configuration.
 */
typedef struct
{
    uint8_t mode;
} gpio_config_t;

/**
 * \brief GPIO pin.
 */
typedef uint8_t gpio_pin_t;

/**
 * \brief Initialization routine of a GPIO pin.
 *
 * \param[in] pin is the GPIO pin to initialize.
 *
 * \param[in] config is the configuration to initialize the GPIO pin.
 *
 * \return The status/error code.
 */
int gpio_init(gpio_pin_t pin, gpio_config_t config);

/**
 * \brief Sets the state of a given output GPIO pin.
 *
 * \param[in] pin is the GPIO pin to set the state.
 *
 * \param[in] level is the new state of the given GPIO pin. It can be:
 * \parblock
 *      - GPIO_STATE_HIGH
 *      - GPIO_STATE_LOW
 *      .
 * \endparblock
 *
 * \return The status/error code.
 */
int gpio_set_state(gpio_pin_t pin, bool state);

/**
 * \brief Gets the state of a given input GPIO pin.
 *
 * \param[in] pin is the the GPIO pin to get the state.
 *
 * \return The GPIO pin state. It can be:
 * \parblock
 *      - GPIO_STATE_HIGH
 *      - GPIO_STATE_LOW
 *      - -1 on error
 *      .
 * \endparblock
 */
int gpio_get_state(gpio_pin_t pin);

/**
 * \brief Toggles the staate of a GPIO pin.
 *
 * \param[in] pin is the the GPIO pin to get the state.
 *
 * \return The status/error code.
 */
int gpio_toggle(gpio_pin_t pin);

#endif /* GPIO_H_ */

/** \} End of gpio group */
