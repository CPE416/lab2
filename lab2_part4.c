#include <stdio.h>

// Custum delay lib
#include "delay.h"
#include "hardware.h"

// Custum delay lib
#include "delay.h"

#define THRESHOLD 180
#define BASE_MOTOR_SPEED 20
#define P_TERM 20
#define I_TERM 0
#define D_TERM 10
#define ERROR_CHECK_DELAY 100

typedef struct pid 
{ 
   int *error;
   u08 p_term;
   u08 i_term;
   u08 d_term;
}pid;


void pid_control(pid *_pid);
void insert_error(pid *_pid, int _error);
int calc_derivative(pid *_pid);

int main(void)
{
	init();
	set_motors(0, 0);

	clear_screen();
	print_string("Press B1");

	int _error[5] = {0,0,0,0,0};
	struct pid _pid = {_error, P_TERM, I_TERM, D_TERM};
	while((get_btn() == 0) | (get_btn2() == 0)){
		delay_ms(1);
	}

	clear_screen();

	while(1){
		pid_control(&_pid);
		delay_ms(ERROR_CHECK_DELAY);
	}
}
// Error 
void pid_control(pid *_pid){
	int actual = 0;
	int output;
	int derivative;
	u08 left_motor = BASE_MOTOR_SPEED;
	u08 right_motor = BASE_MOTOR_SPEED;
	u08 right = poll_analog_pin(LINE_SENSOR_RIGHT);
	u08 left = poll_analog_pin(LINE_SENSOR_LEFT);

	if(right > THRESHOLD){
		actual += 1;
	}
	if(left > THRESHOLD){
		actual -= 1;
	}
	insert_error(_pid, actual);

	output = _pid->error[0] * _pid->p_term;
	derivative = calc_derivative(_pid) * _pid->d_term;
	
	left_motor += output;
	right_motor -= output;

	left_motor += derivative;
	right_motor -= derivative;

	print_4(left, left_motor, right, right_motor);

	set_motors(left_motor, right_motor);
}

//Inserts most recent term and removes last term
void insert_error(pid *_pid, int _error){
	u08 i = 3;
	while(i < 4){
		_pid->error[i] = _pid->error[i+1];
		i--;
	}
	_pid->error[0] = _error;
}

// Prints some values from a PID struct to the LCD
void print_pid(struct pid _pid){
	print_4(_pid.error[0], _pid.p_term, _pid.i_term, _pid.d_term);
}

//Calculates the derivative term based off past error values
int calc_derivative(pid *_pid){
	int derivative = 0;
	u08 i = 4;
	while(i < 4){
		derivative += _pid->error[i];
		i--;
	}
	derivative = derivative/5;
	return derivative;
}

