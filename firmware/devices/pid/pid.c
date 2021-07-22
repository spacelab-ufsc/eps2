/*
 * pid.c
 *
 * Copyright (C) 2021, SpaceLab.
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
 * \brief PID device implementation.
 *
 * \author João Cláudio <joaoclaudiobarcellos@gmail.com>
 *
 * \version 0.1.3
 *
 * \date 2021/02/10
 *
 * \addtogroup pid
 * \{
 */

#include "pid.h"

void PID_init() {

    pid_controller.integrator = 0;
    pid_controller.prevError  = 0;

    pid_controller.differentiator  = 0;
    pid_controller.prevMeasurement = 0;

    pid_controller.out = 0;

}

float PIDController_Update(float setpoint, float measurement) {

    /*
    * Error signal
    */
    float error = setpoint - measurement;


    /*
    * Proportional
    * p[n]=Kp*e[n]
    */
    float proportional = Kp*error;


    /*
    * Integral
    * i[n]= ((Ki*T)/2)*(e[n]-e[n-1])+i[n-1]
    */
    pid_controller.integrator += 0.5f * Ki * pid_controller.T * (error + pid_controller.prevError);

    /* Anti-wind-up via integrator clamping */
    if (pid_controller.integrator > pid_controller.limMaxInt) {

        pid_controller.integrator = pid_controller.limMaxInt;

    } else if (pid_controller.integrator < pid_controller.limMinInt) {

        pid_controller.integrator = pid_controller.limMinInt;

    }


    /*
    * Derivative (band-limited differentiator)
    * d[n]=(2*Kd*(e[n]-e[n-1])+(2*tau-T)*d[n-1])/(2*tau+T)
    */

    pid_controller.differentiator = -(2.0f * Kd * (measurement - pid_controller.prevMeasurement)   /* Note: derivative on measurement, therefore minus sign in front of equation! */
                        + (2.0f * pid_controller.tau - pid_controller.T) * pid_controller.differentiator)
                        / (2.0f * pid_controller.tau + pid_controller.T);


    /*
    * Compute output and apply limits
    * out[n]=p[n]+i[n]+d[n]
    */
    pid_controller.out = proportional + pid_controller.integrator + pid_controller.differentiator;

    if (pid_controller.out > pid_controller.limMax) {

        pid_controller.out = pid_controller.limMax;

    } else if (pid_controller.out < pid_controller.limMin) {

        pid_controller.out = pid_controller.limMin;

    }

    /* Store error and measurement for later use */
    pid_controller.prevError       = error;
    pid_controller.prevMeasurement = measurement;

    /* Return controller output */
    return pid_controller.out;

}





