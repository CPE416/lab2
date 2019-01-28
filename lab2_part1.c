// Name:  Jared Peter-Contesse & Spencer Shaw
// Lab 2 Part 1
// Description: 

#include <stdio.h>

// Custum delay lib
#include "delay.h"
#include "hardware.h"

// Settings
#define DELAY_MS 200 // Delay time for loop
#define DELTA_INIT 4 // Braitenberg mode

int main(void)
{
    init();
    motor(0, 0);
    motor(1, 0);

    int speed = 0;
    int delta = DELTA_INIT;
    while (1)   
    {
        motor(0, speed);
        motor(1, speed);

        print_1(speed);
        delay_ms(DELAY_MS);
        speed = speed + delta;
        if ((speed > 96) || (speed < -96)){
            // speed = speed - (speed % 100);
            delta = 0 - delta;
        }
    }
    return 27;
}
