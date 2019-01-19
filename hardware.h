#ifndef HARDWARE_H
#define HARDWARE_H

void init_led(u08 num){
	digital_dir(num, 1);
}

void led_high(u08 num){
	digital_out(num, 1);
}

void led_low(u08 num){
	digital_out(num, 0);
}


void process_data(u08 *data, u08 *vals){


    // switch (MODE){
    //     case MODE_2A:
    //         break;
    //     case MODE_2B:
    //         break;
    //     case MODE_3A:
    //         break;
    //     case MODE_3B:
    //         break;
    // }
    
    // data[0] = map_motor_value(vals[0]);
    // data[1] = map_motor_value(vals[1]);


    data[0] = vals[0];
    data[1] = vals[1];
}

void set_motors(u08 *data){
    set_servo(MOTOR_1, data[0]);
    set_servo(MOTOR_2, data[1]);
}

#endif
