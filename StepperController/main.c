#include "msp.h"
#include <stdlib.h>
#include <string.h>
#include "driverlib.h"
#include "main.h"

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	// Setup
    MAP_Interrupt_enableMaster();
    SysTick_Init();
    UART0_init();

    // Allocate memory for the controller configuration
    controllerConfig = (struct ControllerConfig *)calloc(1, sizeof(struct ControllerConfig));

	int delay = 10;

    UART_SendString("--- Stepper Controller ---\n\r");
    UART_SendString("speed=[1,2,3,4]\n\r");
    UART_SendString("direction=[forward,reverse]\n\r");

    // Set each port to an output.
    P4->DIR = 0b00111100;

    while(1) {

            P4->OUT |= BIT2 | BIT5;
            P4->OUT &= ~(BIT3 | BIT4);
            SysTick_delay(delay);
            P4->OUT |= BIT4 | BIT5;
            P4->OUT &= ~(BIT2 | BIT3);
            SysTick_delay(delay);
            P4->OUT |= BIT3 | BIT4;
            P4->OUT &= ~(BIT2 | BIT5);
            SysTick_delay(delay);
            P4->OUT |= BIT2 | BIT3;
            P4->OUT &= ~(BIT4 | BIT5);
            SysTick_delay(delay);
            P4->OUT |= BIT2 | BIT5;
            P4->OUT &= ~(BIT3 | BIT4);
            SysTick_delay(delay);
            P4->OUT |= BIT4 | BIT5;
            P4->OUT &= ~(BIT2 | BIT3);
            SysTick_delay(delay);
            P4->OUT |= BIT3 | BIT4;
            P4->OUT &= ~(BIT2 | BIT5);
            SysTick_delay(delay);
            P4->OUT |= BIT2 | BIT3;
            P4->OUT &= ~(BIT4 | BIT5);
            SysTick_delay(delay);

    }
}

void SysTick_Init(void)
{
    // Disable SysTick during setup
    SysTick->CTRL = 0;
    // Maximum reload value
    SysTick->LOAD = 0x00FFFFFF;
    // Any write to current value clears it
    SysTick->VAL = 0;
    // Enable SysTick, CPU clk, no interrupts
    SysTick->CTRL = 0x00000005;
}

void SysTick_delay(uint16_t Delay)
{
    // Load value will also depend on MCLK clock frequency.
    SysTick->LOAD = ((Delay*48000) - 1);
     // Any write to CVR clears it and COUNTFLAG in CSR
    SysTick->VAL = 0;
    // Wait for flag to be SET (Timeout happened)
    while((SysTick -> CTRL & 0x00010000) == 0);
}

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
            UART_SendString("\n\r");
        } else {
            EUSCI_A0->TXBUF = EUSCI_A0->RXBUF;
        }
    }
    EUSCI_A0->IFG = 0x0000 | EUSCI_A_IFG_TXIFG;
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
    EUSCI_A0->IFG = 0x0000 | EUSCI_A_IFG_TXIFG;

    // Enable the EUSCI_A0 general interrupt
    Interrupt_enableInterrupt(INT_EUSCIA0);
}
