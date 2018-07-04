
#include <stdlib.h>
#include <string.h>
#include "global.h"
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
    cmdBuffer = (char *)calloc(CMD_BUFFER_SIZE, sizeof(char));

    // Set command flag
    cmdFlag = 0;

	int delay = 10;

    UART_SendString("--- Stepper Controller ---\n\r");
    UART_SendString("speed=[1,2,3,4]\n\r");
    UART_SendString("direction=[1=forward,2=reverse]\n\r");

    // Set each port to an output.
    P4->DIR = 0b00111100;

    while(1) {
        // Determines if a command has been entered
        if (cmdFlag) {
            cmdFlag = 0;
            on_commandEntered();
        }

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

void on_commandEntered(void) {
    UART_SendString("\n\r");
    char * delimiter = strchr(cmdBuffer, '=');

    // TODO: Parse command
    if (delimiter != NULL) {
        char * pValue = delimiter + 1;
        char cmd[20];
        strncpy(cmd, cmdBuffer, pValue - cmdBuffer - 1);

        // Process command
        if (strncmp(cmd, "speed", 5) == 0) {
            UART_SendString("Stepper speed is now: ");
            UART_SendString(pValue);
            UART_SendString("\n\r");

            controllerConfig->speed = atoi(pValue);

        } else if (strncmp(cmd, "direction", 9) == 0) {
            UART_SendString("Stepper direction is now: ");
            UART_SendString(pValue);
            UART_SendString("\n\r");

            controllerConfig->direction = atoi(pValue);
        } else {
            UART_SendString("Command does not exist.");
            UART_SendString("\n\r");
        }
    } else {
        UART_SendString("Command does not exist.");
        UART_SendString("\n\r");
    }

    // Clear command buffer
    free(cmdBuffer);
    cmdBuffer = (char *)calloc(CMD_BUFFER_SIZE, sizeof(char));
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



