/*
 * uart.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Ryan
 */

#ifndef UART_H_
#define UART_H_

#include "global.h"

void UART_Send(char c);

void UART_SendString(char * c);

void EUSCIA0_IRQHandler(void);

void UART0_init(void);


#endif /* UART_H_ */
