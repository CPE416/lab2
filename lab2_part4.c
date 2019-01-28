#include <stdio.h>

// Custum delay lib
#include "delay.h"
#include "hardware.h"

// Custum delay lib
#include "delay.h"

#define THRESHOLD 120

void pid_control(pid _pid);
void insert_error(pid _pid, int _error);
int calc_derivative(pid _pid);

struct pid 
{ 
   u08 *error;
   u08 p_term;
   u08 i_term;
   u08 d_term;
}pid;


int main(void)
{
	init();
	u08 _error[5] = {0,0,0,0,0};
	struct pid _pid = {_error, 2, 0, 0};
	while(get_btn()){
		delay_ms(1);
	}
	while(1){
		pid_control(_pid);
		delay_ms(100);
	}
}
// Error 
void pid_control(pid _pid){
	int actual = 0;
	int output;
	int derivative;
	u08 left_motor = 50;
	u08 right_motor = 50;
	u08 right = poll_analog_pin(LINE_SENSOR_RIGHT);
	u08 left = poll_analog_pin(LINE_SENSOR_LEFT);
	if(right > THRESHOLD){
		actual += 1;
	}
	if(left > THRESHOLD){
		actual -= 1;
	}
	insert_error(_pid, actual);
	output = _pid.error[0] * _pid.p_term;
	derivative = calc_derivative(_pid) * _pid.d_term;
	if(output < 0){
		left_motor += output;
		right_motor -= output;
	}else{
		left_motor -= output;
		right_motor += output;
	}

}

//Inserts most recent term and removes last term
void insert_error(pid _pid, int _error){
	u08 i = 3;
	while(i > -1){
		_pid.error[i] = _pid.error[i+1];
		i--;
	}
	_pid.error[0] = _error;
}

//Calculates the derivative term based off past error values
int calc_derivative(pid _pid){
	int derivative = 0;
	u08 i = 4;
	while(i > -1){
		derivative += _pid.error[i];
		i--;
	}
	derivative = derivative/5;
	return derivative;
}

