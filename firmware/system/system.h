/*
 * system.h
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
 * \brief System layer definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/22
 * 
 * \defgroup system System
 * \{
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>

#include "clocks.h"

/**
 * \brief Hardware versions.
 */
typedef enum
{
    HW_VERSION_0=0,                 /**< Hardware version 0. */
    HW_VERSION_1,                   /**< Hardware version 1. */
    HW_VERSION_2,                   /**< Hardware version 2. */
    HW_VERSION_3,                   /**< Hardware version 3. */
    HW_VERSION_UNKNOWN=UINT8_MAX    /**< Hardware version unknown. */
} hw_version_e;

/**
 * \brief System time type.
 */
typedef uint32_t sys_time_t;

/**
 * \brief Hardware version.
 */
typedef uint8_t sys_hw_version_t;

/**
 * \brief System reset.
 *
 * \return None.
 */
void system_reset(void);

/**
 * \brief Gets the last reset cause code.
 *
 * This function reads the value of the reset interrupt vector (SYSRSTIV).
 *
 * \see SLAU208P - MSP430x5xx and MSP430x6xx Family User's Guide. Table 1-26. SYSRSTIV Register Description. Page 96.
 *
 * \return The last reset cause value. It can be:
 * \parblock
 *      -\b 0x00 = No interrupt pending
 *      -\b 0x02 = Brownout (BOR)
 *      -\b 0x04 = RST/NMI (BOR)
 *      -\b 0x06 = PMMSWBOR (BOR)
 *      -\b 0x08 = Wakeup from LPMx.5 (BOR)
 *      -\b 0x0A = Security violation (BOR)
 *      -\b 0x0C = SVSL (POR)
 *      -\b 0x0E = SVSH (POR)
 *      -\b 0x10 = SVML_OVP (POR)
 *      -\b 0x12 = SVMH_OVP (POR)
 *      -\b 0x14 = PMMSWPOR (POR)
 *      -\b 0x16 = WDT time out (PUC)
 *      -\b 0x18 = WDT password violation (PUC)
 *      -\b 0x1A = Flash password violation (PUC)
 *      -\b 0x1C = Reserved
 *      -\b 0x1E = PERF peripheral/configuration area fetch (PUC)
 *      -\b 0x20 = PMM password violation (PUC)
 *      -\b 0x22 to 0x3E = Reserved
 *      .
 * \endparblock
 */
uint8_t system_get_reset_cause(void);

/**
 * \brief Sets the system time.
 *
 * \param[in] tm is the new system time value.
 *
 * \return None.
 */
void system_set_time(sys_time_t tm);

/**
 * \brief Increments the system time.
 *
 * \return None.
 */
void system_increment_time(void);

/**
 * \brief Gets the system time.
 *
 * \return The current system time.
 */
sys_time_t system_get_time(void);

/**
 * \brief Gets the current hardware version.
 *
 * This funciton reads the state of the versioning GPIO pins.
 *
 * \return The current hardware version. It can be:
 * \parblock
 *      -\b HW_VERSION_0
 *      -\b HW_VERSION_1
 *      -\b HW_VERSION_2
 *      -\b HW_VERSION_3
 *      -\b HW_VERSION_UNKNOWN
 *      .
 * \endparblock
 */
sys_hw_version_t system_get_hw_version();

#endif /* SYSTEM_H_ */

/** \} End of system group */
