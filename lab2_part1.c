// Name:  Jared Peter-Contesse & Spencer Shaw
// Lab 2 Part 1
// Description: 

#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Custum delay lib
#include "delay.h"
#include "hardware.h"

// Settings
#define DELAY_MS 100 // Delay time for loop
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

void read_data(u08 *vals);
void process_data(u08 *data, u08 *vals);
u08 map_motor_value(int val);
void set_motors(u08 *data);
void print_data(u08 *vals, u08 *data);

int main(void)
{
    init(); // Init board
    init_servo();


    u08 vals[] = {0, 0}; // Data retrieve from lgith sensors
    u08 data[] = {0, 0}; 
    // Place text at start of buffer
    // sprintf(buffer, "416");

    // Main loop
    while (1)
    {
        read_data(vals);
        process_data(data, vals);
    print_data(vals, data);
    if(motors_running){
        set_motors(data);}
        delay_ms(DELAY_MS);
    }
    return 1;
}

void read_data(u08 *vals){
    // vals[0] = analog(LIGHT_SENSOR_1_PIN);
    // vals[1] = analog(LIGHT_SENSOR_2_PIN);

    vals[0] = vals[0] + 1;
    vals[1] = vals[1] + 1;
}

void  print_data(u08 *vals, u08 *data){
    clear_screen();
    lcd_cursor(0, 0);
    print_num(vals[0]);
    lcd_cursor(4, 0);
    print_num(data[0]);
    lcd_cursor(0, 1);
    print_num(vals[1]);
    lcd_cursor(4, 1);
    print_num(data[1]);
    
}