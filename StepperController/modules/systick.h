/**
 * systick.c
 * Sets up the SysTick and SysTick delay functionality in
 * the microcontroller.
 * @author Ryan Borgeson, Tyler Beard, and Zach Wassink
 * @date 7/5/2018
 */

#ifndef MODULES_SYSTICK_H_
#define MODULES_SYSTICK_H_

#include "global.h"

/**
 * SysTick_Init
 * Initializes and setups up the SysTick delay timer.
 */
void SysTick_Init(void);

/**
 * SysTick_delay
 * Actually executes the delay specified by the user using
 * the systick timer.
 */
void SysTick_delay(uint16_t Delay);


#endif
