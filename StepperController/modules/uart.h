/**
 * uart.h
 * Drivers for UART to send and receive data and set up
 * UART interrupts.
 * @author Ryan Borgeson, Tyler Beard, and Zach Wassink
 * @date 7/5/2018
 */

#ifndef MODULES_UART_H_
#define MODULES_UART_H_

#include "global.h"

/**
 * UART0_init
 * Initializes and sets up the UART peripheral using the
 * eUSCIA_0 module. Enables interrupts.
 */
void UART0_init(void);

/**
 * UART_Send
 * Places one character or byte into the TX buffer and sends
 * the character over UART.
 * @param c ASCII Character to send.
 */
void UART_Send(char c);

/**
 * UART_SendString
 * Sends a string of characters over UART.
 * @param c Pointer to an array of characters.
 */
void UART_SendString(char * c);

/**
 * EUSCIA0_IRQHandler
 * Handles an interrupt on the EUSCIA0 module. Specifically, we
 * are interested in the interrupt triggered by a character be
 * received in the RX buffer. This occurs when a user enters a
 * character in the terminal.
 */
void EUSCIA0_IRQHandler(void);

/**
 * on_commandEntered
 * When a command is by the user, the command is parsed. Typically,
 * this would be used to update speed or direction.
 */
void on_commandEntered(void);


#endif
