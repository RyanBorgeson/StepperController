/**
 * global.h
 * Includes external dependencies, defines stepper controller
 * constants, and variables.
 * @author Ryan Borgeson, Tyler Beard, and Zach Wassink
 * @date 7/5/2018
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdlib.h>
#include <string.h>
#include "msp.h"
#include "driverlib/MSP432P4xx/driverlib.h"

#include "modules/uart.h"
#include "modules/systick.h"
#include "modules/drive.h"

/* Base time delay in milliseconds */
#define BASE_SPEED          40
/* Delay update frequency */
#define STEPS_PER           10
/* Size of command buffer */
#define CMD_BUFFER_SIZE     100

/* Allocate space to store entered commands */
char * cmdBuffer;

/* Has a command been entered */
uint8_t cmdFlag;

/* Stepper speed */
int step_speed;

/* Stepper direction */
int step_dir;


#endif
