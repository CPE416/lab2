// Name:  Jared Peter-Contesse & Spencer Shaw
// Lab 2 Part 1
// Description: 


// Custum delay lib
#include "delay.h"
#include "hardware.h"

// Settings
#define DELAY_MS 200 // Delay time for loop

#define MODE_2A 1 
#define MODE_2B 0

#define LIGHT_MIN 200

void process_data_mode_a(u08* vals, u08* data);
void process_data_mode_b(u08* vals, u08* data);
u08 map_light_to_motor(u08 data);
u08 set_mode(u08 mode);

int main(void)
{
    init(); // Init board
    motor(0, 0);
    motor(1, 0);

    u08 mode = set_mode(MODE_2A);
    u08 vals[] = {0, 0}; // Data retrieve from lgith sensors
    u08 data[] = {0, 0}; 
    // Place text at start of buffer
    // sprintf(buffer, "416");

    // Main loop
    while (1)
    {
        read_light_sensor(vals);

        switch (mode){
            case MODE_2A:
                process_data_mode_a(vals, data);
                break;
            case MODE_2B:  
                process_data_mode_b(vals, data);
                break;
        }

        print_4(vals[0], data[0], vals[1], data[1]);
        
        set_motors(data);

        delay_ms(DELAY_MS);

        mode = set_mode(mode);
    }
    return 1;
}

void process_data_mode_a(u08* vals, u08* data){
    data[0] = map_light_to_motor(vals[0]);
    data[1] = map_light_to_motor(vals[1]);
}

void process_data_mode_b(u08* vals, u08* data){
    data[0] = map_light_to_motor(vals[1]);
    data[1] = map_light_to_motor(vals[0]);
}

u08 map_light_to_motor(u08 val){
    if (val < LIGHT_MIN){
        val = 0;
    }else{
        val = val - LIGHT_MIN;
    } 
    u08 data = (val);
    if (data > 100){
        data = 0;
    }
    return data;
}

u08 set_mode(u08 mode){
    u08 pressed = get_btn();
    if(pressed){
        if (mode == MODE_2A){
            led_off(0);
            led_on(1);
            return MODE_2B;
        } else{
            led_off(1);
            led_on(0);
            return MODE_2A;
        }
    }
    return mode;
}
