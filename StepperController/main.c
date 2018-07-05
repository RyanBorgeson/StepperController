/**
 * Project 2 - Stepper Controller
 * A program designed to take the desired speed and direction from
 * the user and adjust the stepper motor's acceleration and deceleration
 * to generate a smooth waveform to drive the stepper motor.
 * @author Ryan Borgeson, Tyler Beard, and Zach Wassink
 * @date 7/5/2018
 */

#include "main.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	// Setup
    MAP_Interrupt_enableMaster();
    SysTick_Init();
    UART0_init();

    // Allocate memory for the controller command buffer
    cmdBuffer = (char *)calloc(CMD_BUFFER_SIZE, sizeof(char));

    // Set command flag
    cmdFlag = 0;

    step_speed = 1;
    step_dir = 1;

    UART_SendString("--- Stepper Controller ---\n\r");
    UART_SendString("speed=[1,2,3,4]\n\r");
    UART_SendString("direction=[0=stop,1=forward,2=reverse]\n\r");

    // Set each port to an output.
    P4->DIR = 0b00111100;

    while(1) {
        // Determines if a command has been entered
        if (cmdFlag) {
            cmdFlag = 0;
            on_commandEntered();
        }

        // Drive stepper as desired
        waveDrive();
    }
}
