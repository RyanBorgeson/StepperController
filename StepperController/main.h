/*
 * main.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Ryan
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "global.h"

void UART0_init(void);

void UART_SendString(char * c);

void SysTick_delay(uint16_t Delay);

void SysTick_Init(void);


#endif /* MAIN_H_ */
