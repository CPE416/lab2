#include <stdio.h>

// Custum delay lib
#include "delay.h"
#include "hardware.h"

// Custum delay lib
#include "delay.h"

#define THRESHOLD 120
void pid_control(pid _pid);
void insert_error(pid _pid, int _error);
void print_pid(struct pid _pid);

int main(void)
{
	init();
	u08 _error[5] = {0,0,0,0,0};
	struct pid _pid = {_error, 2, 0, 0};
	while(1){
		pid_control(_pid);
		print_pid(_pid);
		delay_ms(100);
	}
}
// Error 
void pid_control(pid _pid){
	int actual = 0;
	int output;
	u08 right = poll_analog_pin(LINE_SENSOR_RIGHT);
	u08 left = poll_analog_pin(LINE_SENSOR_LEFT);
	if(right > THRESHOLD){
		actual += 1;
	}
	if(left > THRESHOLD){
		actual -= 1;
	}
	insert_error(_pid, actual);
	output = _pid.error[0] * _pid.pterm;
}

void insert_error(pid _pid, int _error){
	u08 i = 3;
	while(i > -1){
		_pid.error[i] = _pid.error[i+1]
	}
	_pid.error[0] = _error;
}

struct pid 
{ 
   u08 error[5];
   u08 p_term;
   u08 i_term;
   u08 d_term;
};

void print_pid(struct pid _pid){
	print_4(_pid.error[0], _pid.p_term, _pid.i_term, _pid.d_term);
}

