/**
 * systick.c
 * Sets up the SysTick and SysTick delay functionality in
 * the microcontroller.
 * @author Ryan Borgeson, Tyler Beard, and Zach Wassink
 * @date 7/5/2018
 */
#include "systick.h"

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
    SysTick->LOAD = ((Delay*2000) - 1);
     // Any write to CVR clears it and COUNTFLAG in CSR
    SysTick->VAL = 0;
    // Wait for flag to be SET (Timeout happened)
    while((SysTick -> CTRL & 0x00010000) == 0);
}
