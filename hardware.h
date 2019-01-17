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

#endif
