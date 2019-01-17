// Name:  Jared Peter-Contesse & Spencer Shaw
// Lab 2 Part 1
// Description: 

#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Custum delay lib
#include "delay.h"

// Settings
#define DELAY_MS 50// Delay time for loop
#define MODE MODE_2A // Braitenberg mode

// Pin map
#define LIGHT_SENSOR_1_PIN 0
#define LIGHT_SENSOR_2_PIN 1
#define MOTOR_1 0
#define MOTOR_2 1


#define MODE_2A 0
#define MODE_2B 1
#define MODE_3A 2
#define MODE_3B 3

void init_motors();
void read_data(u08 *vals);
void process_data(u08 *data, u08 *vals);
u08 map_motor_value(int val);
void set_motors(u08 *data);

int main(void)
{
    init(); // Init board
    u08 vals[] = {0, 0}; // Data retrieve from lgith sensors
    u08 data[] = {0, 0}; 
    // Place text at start of buffer
    // sprintf(buffer, "416");

    // Main loop
    while (1)
    {
        read_data(vals);
        process_data(data, vals);
        set_motors(buffer, data);
        delay_ms(DELAY_MS);
    }
    return 1;
}

void read_data(u08 *vals){
    vals[0] = analog(LIGHT_SENSOR_1_PIN);
    vals[1] = analog(LIGHT_SENSOR_2_PIN);
}

void process_data(u08 *data, u08 vals){

    switch (MODE){
        case MODE_2A:
            break;
        case MODE_2B:
            break;
        case MODE_3A:
            break;
        case MODE_3B:
            break;
    }
    
    data[0] = map_motor_value(vals[0]);
    data[1] = map_motor_value(vals[1]);
}

void set_motors(u08 *data){
    set_servo(MOTOR_1, data[0]);
    set_servo(MOTOR_2, data[1]);
}