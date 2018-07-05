/**
 * drive.c
 * Drives the stepper motor. Implements acceleration and
 * deceleration.
 * @author Ryan Borgeson, Tyler Beard, and Zach Wassink
 * @date 7/5/2018
 */

#include "drive.h"


void waveDrive(void) {
    static int count = 1;
    static int delay_count = 0;
    static int delay = BASE_SPEED;
    static int current_dir = 0;

    switch(count){
        case 1:
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
            break;
        case 2:
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
            break;
        case 3:
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
            break;
        case 4:
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
            break;
        default:
            break;
    }

    if(delay >= BASE_SPEED) current_dir = step_dir;

    if(++delay_count >= STEPS_PER) delay_count = 0;

    if(!delay_count){ // Update delay
        if((current_dir == step_dir) && (delay > (BASE_SPEED/step_speed))) delay--;
        else if((current_dir != step_dir) || (delay < (BASE_SPEED/step_speed))) delay++;
    }

    if(current_dir != 0) SysTick_delay(delay); // Delay, speed

    if(current_dir == 1) count++; // Phase shift based on direction
    else if(current_dir == 2) count--;

    if(count == 5) count = 1; // Phase cycle
    else if(count == 0) count = 4;
}
