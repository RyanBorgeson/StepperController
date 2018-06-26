#include "msp.h"
#include "driverlib.h"

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	int delay = 10;

        SysTick_Init();
        UART0_init();

        UART_SendString("--- Stepper Controller ---");

        // Set each port to an output.
        P4->OUT |= (BIT2 | BIT3 | BIT4 | BIT5);

        while(1) {


                P4->OUT |= BIT2 | BIT5;
                P4->DIR &= ~(BIT3 | BIT4);
                SysTick_delay(delay);
                P4->DIR |= BIT4 | BIT5;
                P4->DIR &= ~(BIT2 | BIT3);
                SysTick_delay(delay);
                P4->DIR |= BIT3 | BIT4;
                P4->DIR &= ~(BIT2 | BIT5);
                SysTick_delay(delay);
                P4->DIR |= BIT2 | BIT3;
                P4->DIR &= ~(BIT4 | BIT5);
                SysTick_delay(delay);
                P4->DIR |= BIT2 | BIT5;
                P4->DIR &= ~(BIT3 | BIT4);
                SysTick_delay(delay);
                P4->DIR |= BIT4 | BIT5;
                P4->DIR &= ~(BIT2 | BIT3);
                SysTick_delay(delay);
                P4->DIR |= BIT3 | BIT4;
                P4->DIR &= ~(BIT2 | BIT5);
                SysTick_delay(delay);
                P4->DIR |= BIT2 | BIT3;
                P4->DIR &= ~(BIT4 | BIT5);
                SysTick_delay(delay);

        }

        // Disable the outputs to conserve power.
        P4->DIR &= ~(BIT2 | BIT3);
        P4->DIR &= ~(BIT4 | BIT5);
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

void UART0_init(void) {


    // Configure UART pins
    P1->SEL0 |= BIT2 | BIT3;

    // Configure UART
    EUSCI_A0->CTLW0 |= 0x0001 | EUSCI_B_CTLW0_SSEL__SMCLK;
    EUSCI_A0->MCTLW &= ~0x0001;
    EUSCI_A0->BRW = 312;
    EUSCI_A0->CTLW0 &= ~0x0001;

}
