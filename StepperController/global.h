/*
 * global.h
 *
 *  Created on: Jun 28, 2018
 *      Author: Ryan
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


#include "msp.h"
#include "driverlib.h"

#define CMD_BUFFER_SIZE 100

struct ControllerConfig {
    int speed;
    int direction;
};

struct ControllerConfig * controllerConfig;

/* Allocate space to store entered commands */
char * cmdBuffer;

/* Has a command been entered */
uint8_t cmdFlag;


#endif /* GLOBAL_H_ */
