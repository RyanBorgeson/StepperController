/**
 * uart.c
 * Drivers for UART to send and receive data and set up
 * UART interrupts.
 * @author Ryan Borgeson, Tyler Beard, and Zach Wassink
 * @date 7/5/2018
 */
#include "uart.h"


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

void UART_Send(char c) {
    // Wait for TX Flag to be cleared
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

void on_commandEntered(void) {
    UART_SendString("\n\r");
    char * delimiter = strchr(cmdBuffer, '=');

    if (delimiter != NULL) {
        char * pValue = delimiter + 1;
        char cmd[20];
        strncpy(cmd, cmdBuffer, pValue - cmdBuffer - 1);

        // Process command
        if (strncmp(cmd, "speed", 5) == 0) {
            UART_SendString("Stepper speed is now: ");
            UART_SendString(pValue);
            step_speed = atoi(pValue);
            UART_SendString("\n\r");
        } else if (strncmp(cmd, "direction", 9) == 0) {
            UART_SendString("Stepper direction is now: ");
            UART_SendString(pValue);
            step_dir = atoi(pValue);
            UART_SendString("\n\r");
        } else {
            UART_SendString("Command does not exist.");
            UART_SendString("\n\r");
        }
    }

    // Clear command buffer
    free(cmdBuffer);
    cmdBuffer = (char *)calloc(CMD_BUFFER_SIZE, sizeof(char));
}
