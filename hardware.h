#ifndef HARDWARE_H
#define HARDWARE_H

#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Pin map
#define LIGHT_SENSOR_PIN_RIGHT 0
#define LIGHT_SENSOR_PIN_LEFT 1
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1


void init_led(u08 num){
	digital_dir(num, 1);
}

void led_high(u08 num){
	digital_out(num, 1);
}

void led_low(u08 num){
	digital_out(num, 0);
}

void read_light_sensor(u08 *vals){
    vals[MOTOR_LEFT] = analog(LIGHT_SENSOR_PIN_LEFT);
    vals[MOTOR_RIGHT] = analog(LIGHT_SENSOR_PIN_RIGHT);

    // vals[0] = vals[0] + 1;
    // vals[1] = vals[1] + 1;
}

void motor(u08 num, u08 speed){
    if (num == MOTOR_RIGHT){

        set_servo(MOTOR_RIGHT, ((speed) * 0.3333 ) + 127);
    }
    set_servo(MOTOR_LEFT, (0 - speed * 0.3333 ) + 127);
}

void set_motors(u08 *data){
    motor(MOTOR_LEFT, data[0]);
    motor(MOTOR_RIGHT, data[1]);
}

void print_4(u08 a, u08 b, u08 c, u08 d){
    clear_screen();
    lcd_cursor(0, 0);
    print_num(a);
    lcd_cursor(4, 0);
    print_num(b);
    lcd_cursor(0, 1);
    print_num(c);
    lcd_cursor(4, 1);
    print_num(d);
    
}
void print_2(u08 a, u08 b){
    clear_screen();
    lcd_cursor(0, 0);
    print_num(a);
    lcd_cursor(0, 1);
    print_num(b); 
}
void print_1(u08 a){
    clear_screen();
    lcd_cursor(0, 0);
    print_num(a);
}

#endif
