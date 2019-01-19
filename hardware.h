#ifndef HARDWARE_H
#define HARDWARE_H


#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Pin map
#define LIGHT_SENSOR_1_PIN 0
#define LIGHT_SENSOR_2_PIN 1
#define MOTOR_1 0
#define MOTOR_2 1


void init_led(u08 num){
	digital_dir(num, 1);
}

void led_high(u08 num){
	digital_out(num, 1);
}

void led_low(u08 num){
	digital_out(num, 0);
}

void read_light_sensor(int *vals){
    // vals[0] = analog(LIGHT_SENSOR_1_PIN);
    // vals[1] = analog(LIGHT_SENSOR_2_PIN);

    vals[0] = vals[0] + 1;
    vals[1] = vals[1] + 1;
}

void process_data(u08 *data, int *vals){
	// Takes values from -100 to 100 and maps to 97 to 

    data[0] = (vals[0] * 0.3333) + 127;
    data[1] = 127 - (vals[1] * 0.3333);
}

void set_motors(u08 *data){
    set_servo(MOTOR_1, data[0]);
    set_servo(MOTOR_2, data[1]);
}

#endif
