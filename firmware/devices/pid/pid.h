/*
 * voltage_sensor.h
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
 * \brief Voltage sensor device definition.
 *
 * \author João Cláudio <joaoclaudiobarcellos@gmail.com>
 *
 * \version 0.1.3
 *
 * \date 2021/07/07
 *
 * \defgroup pid PID
 * \ingroup devices
 * \{
 */

#ifndef PID_H_
#define PID_H_

#include <stdint.h>
#include <stdbool.h>

#define PID_MODULE_NAME        "PID"

#define Kp 1
#define Ki 1
#define Kd 1

typedef struct {
    /* Derivative low-pass filter time constant */
    float tau;

    /* Output limits */
    float limMin;
    float limMax;

    /* Integrator limits */
    float limMinInt;
    float limMaxInt;

    /* Sample time (in seconds) */
    float T;

    /* Controller "memory" */
    float integrator;
    float prevError;            /* Required for integrator */
    float differentiator;
    float prevMeasurement;      /* Required for differentiator */

    /* Controller output */
    float out;

} pid_controller_t;

pid_controller_t pid_controller;

void  PID_init();
float PIDController_Update(float setpoint, float measurement);



#endif /* PID_H_ */

/** \} End of pid group */
