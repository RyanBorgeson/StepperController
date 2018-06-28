/*
 * uart.c
 *
 *  Created on: Jun 28, 2018
 *      Author: Ryan
 */
#include "uart.h"

void UART_Send(char c) {
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
    EUSCI_A0->TXBUF = c;
}

void UART_SendString(char * c) {
    int i = 0;
    for (i = 0; i < strlen(c); i++) {
        UART_Send(c[i]);
    }
}


void EUSCIA0_IRQHandler(void) {
    // Check to see if a byte has been received
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG) {
        char rxBuf = EUSCI_A0->RXBUF;

        // Handle carriage return
        if (rxBuf == 0x0D) {
            cmdFlag = 1;
        } else {
            strcat(cmdBuffer, &rxBuf);
            EUSCI_A0->TXBUF = rxBuf;
        }
    }
    EUSCI_A0->IFG = EUSCI_A_IFG_TXIFG;
}

void UART0_init(void) {
    // Configure UART pins
    P1->SEL0 |= BIT2 | BIT3;

    // Configure UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST | EUSCI_A_CTLW0_SSEL__SMCLK;
    EUSCI_A0->MCTLW &= ~EUSCI_A_MCTLW_OS16;
    EUSCI_A0->BRW = 312;
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

    // Receive interrupt enable
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE | EUSCI_A_IE_STTIE;
    EUSCI_A0->IFG = EUSCI_A_IFG_TXIFG;

    // Enable the EUSCI_A0 general interrupt
    Interrupt_enableInterrupt(INT_EUSCIA0);
}
