// Name:  Jared Peter-Contesse & Spencer Shaw
// Lab 2 Part 1
// Description: 


// Custum delay lib
#include "delay.h"
#include "hardware.h"

// Settings
#define DELAY_MS 200 // Delay time for loop
#define MODE MODE_2A // Braitenberg mode


#define MODE_2A 0
#define MODE_2B 1
#define MODE_3A 2
#define MODE_3B 3

#define TRUE 1
#define FALSE 0

void print_data(int *vals, u08 *data);

int main(void)
{
    init(); // Init board
    init_servo();

    u08 motors_running = TRUE;
    int vals[] = {0, 0}; // Data retrieve from lgith sensors
    u08 data[] = {0, 0}; 
    // Place text at start of buffer
    // sprintf(buffer, "416");

    // Main loop
    while (1)
    {
     read_light_sensor(vals);
        process_data(data, vals);
    print_data(vals, data);
    if(motors_running){
        set_motors(data);}
        delay_ms(DELAY_MS);
    }
    if(get_btn()){
        motors_running = ! motors_running;
    }
    return 1;
}


void  print_data(int *vals, u08 *data){
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