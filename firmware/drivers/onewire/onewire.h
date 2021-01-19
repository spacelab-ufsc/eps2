/*
 * onewire.h
 * 
 * Copyright (C) 2020, SpaceLab.
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
 * \brief OneWire driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * 
 * \version 0.1.2
 * 
 * \date 2021/01/17
 * 
 * \defgroup onewire OneWire
 * \ingroup drivers
 * \{
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <stdint.h>

#include <drivers/gpio/gpio.h>

/**
 * \brief OneWire ports.
 */
typedef enum
{
    ONEWIRE_PORT_0=0,           /**< OneWire port 0. */
    ONEWIRE_PORT_1,             /**< OneWire port 1. */
    ONEWIRE_PORT_2,             /**< OneWire port 2. */
    ONEWIRE_PORT_3,             /**< OneWire port 3. */
    ONEWIRE_PORT_4,             /**< OneWire port 4. */
    ONEWIRE_PORT_5,             /**< OneWire port 5. */
    ONEWIRE_PORT_6,             /**< OneWire port 6. */
    ONEWIRE_PORT_7,             /**< OneWire port 7. */
    ONEWIRE_PORT_8,             /**< OneWire port 8. */
    ONEWIRE_PORT_9,             /**< OneWire port 9. */
    ONEWIRE_PORT_10,            /**< OneWire port 10. */
    ONEWIRE_PORT_11,            /**< OneWire port 11. */
    ONEWIRE_PORT_12,            /**< OneWire port 12. */
    ONEWIRE_PORT_13,            /**< OneWire port 13. */
    ONEWIRE_PORT_14,            /**< OneWire port 14. */
    ONEWIRE_PORT_15,            /**< OneWire port 15. */
    ONEWIRE_PORT_16,            /**< OneWire port 16. */
    ONEWIRE_PORT_17,            /**< OneWire port 17. */
    ONEWIRE_PORT_18,            /**< OneWire port 18. */
    ONEWIRE_PORT_19,            /**< OneWire port 19. */
    ONEWIRE_PORT_20,            /**< OneWire port 20. */
    ONEWIRE_PORT_21,            /**< OneWire port 21. */
    ONEWIRE_PORT_22,            /**< OneWire port 22. */
    ONEWIRE_PORT_23,            /**< OneWire port 23. */
    ONEWIRE_PORT_24,            /**< OneWire port 24. */
    ONEWIRE_PORT_25,            /**< OneWire port 25. */
    ONEWIRE_PORT_26,            /**< OneWire port 26. */
    ONEWIRE_PORT_27,            /**< OneWire port 27. */
    ONEWIRE_PORT_28,            /**< OneWire port 28. */
    ONEWIRE_PORT_29,            /**< OneWire port 29. */
    ONEWIRE_PORT_30,            /**< OneWire port 30. */
    ONEWIRE_PORT_31,            /**< OneWire port 31. */
    ONEWIRE_PORT_32,            /**< OneWire port 32. */
    ONEWIRE_PORT_33,            /**< OneWire port 33. */
    ONEWIRE_PORT_34,            /**< OneWire port 34. */
    ONEWIRE_PORT_35,            /**< OneWire port 35. */
    ONEWIRE_PORT_36,            /**< OneWire port 36. */
    ONEWIRE_PORT_37,            /**< OneWire port 37. */
    ONEWIRE_PORT_38,            /**< OneWire port 38. */
    ONEWIRE_PORT_39,            /**< OneWire port 39. */
    ONEWIRE_PORT_40,            /**< OneWire port 40. */
    ONEWIRE_PORT_41,            /**< OneWire port 41. */
    ONEWIRE_PORT_42,            /**< OneWire port 42. */
    ONEWIRE_PORT_43,            /**< OneWire port 43. */
    ONEWIRE_PORT_44,            /**< OneWire port 44. */
    ONEWIRE_PORT_45,            /**< OneWire port 45. */
    ONEWIRE_PORT_46,            /**< OneWire port 46. */
    ONEWIRE_PORT_47,            /**< OneWire port 47. */
    ONEWIRE_PORT_48,            /**< OneWire port 48. */
    ONEWIRE_PORT_49,            /**< OneWire port 49. */
    ONEWIRE_PORT_50,            /**< OneWire port 50. */
    ONEWIRE_PORT_51,            /**< OneWire port 51. */
    ONEWIRE_PORT_52,            /**< OneWire port 52. */
    ONEWIRE_PORT_53,            /**< OneWire port 53. */
    ONEWIRE_PORT_54,            /**< OneWire port 54. */
    ONEWIRE_PORT_55,            /**< OneWire port 55. */
    ONEWIRE_PORT_56,            /**< OneWire port 56. */
    ONEWIRE_PORT_57,            /**< OneWire port 57. */
    ONEWIRE_PORT_58,            /**< OneWire port 58. */
    ONEWIRE_PORT_59,            /**< OneWire port 59. */
    ONEWIRE_PORT_60,            /**< OneWire port 60. */
    ONEWIRE_PORT_61,            /**< OneWire port 61. */
    ONEWIRE_PORT_62,            /**< OneWire port 62. */
    ONEWIRE_PORT_63,            /**< OneWire port 63. */
    ONEWIRE_PORT_64,            /**< OneWire port 64. */
    ONEWIRE_PORT_65,            /**< OneWire port 65. */
    ONEWIRE_PORT_66,            /**< OneWire port 66. */
    ONEWIRE_PORT_67,            /**< OneWire port 67. */
    ONEWIRE_PORT_68,            /**< OneWire port 68. */
    ONEWIRE_PORT_69             /**< OneWire port 69. */
} onewire_ports_e;

/**
 * \brief OneWire port type.
 */
typedef gpio_pin_t onewire_port_t;

/**
 * \brief OneWire address type.
 */
typedef uint8_t onewire_adr_t;

/**
 * \brief OneWire port initialization.
 *
 * \param[in] port is the OneWire port to initialize.
 *
 * \return The status/error code.
 */
int onewire_init(onewire_port_t port);

/**
 * \brief generates reset on a OneWire line.
 *
 * \param[in] port is the OneWire port to reset.
 *
 * \return 0 if device is present, 1 if not present.
 */
int onewire_reset(onewire_port_t port);

/**
 * \brief Writes a bit on the OneWire line.
 *
 * \param[in] port is the OneWire port to write.
 *
 * \param[in] bit is the bit that will be written
 *
 * \return The status/error code.
 */
int onewire_write_bit(onewire_port_t port, int bit);

/**
 * \brief Writes data on the OneWire line.
 *
 * \param[in] port is the OneWire port to write.
 *
 * \param[in,out] data is the data to write to the OneWire line.
 *
 * \param[in] len is the number of bytes to write.
 *
 * \return The status/error code.
 */
int onewire_write_byte(onewire_port_t port, uint8_t *data, uint16_t len);

/**
 * \brief Reads OneWire bit from OneWire slave.
 *
 * \param[in] port is the OneWire port to read.
 *
 * \return The bit read.
 */
int onewire_read_bit(onewire_port_t port);

/**
 * \brief Reads data from the OneWire line.
 *
 * \param[in] port is the OneWire port to read.
 *
 * \param[in,out] data is a pointer to store read data.
 *
 * \param[in] len is the number of bytes to read.
 *
 * \return The status/error code.
 */
int onewire_read_byte(onewire_port_t port, uint8_t *data, uint16_t len);

#endif /* ONEWIRE_H_ */

/** \} End of onewire group */
