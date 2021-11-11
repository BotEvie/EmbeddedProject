/* Erich Vernon
	Acceleration threshold statemachine
	
*/

#include <stdint.h>

int update_threshold_value(uint8_t *toast);
void threshold_fsm(int *accel_queue, int *value_queue);

// Tested output accelerometer system total = T.O.A.S.T.
// Done: change this to accept and test an array of 3 integers. Find and return the highest value of acceleration.
int update_threshold_value(uint8_t *toast)
{
	for(int i=0; i<(sizeof(toast)/sizeof(toast[0])); i++)
	{
		if(toast[i] > value){ value = toast[i]; }
	}	

	
	// Higher numbers indicate higher acceleration
  	value = (value > 0)? value: -value;
	if(toast > 100){ value = 3; }
	if(toast > 50){ value = 2; }
	if(toast > 15){ value = 1; }
	else{ value = 0; }
  	return value;
}



void threshold_fsm(int *accel_queue, int *value_queue)
{
	volatile int threshold_state;
	volatile int threshold_max;
	int value = 0;
	int data[3];
	
	// TODO: get acceleration data from external queue. Assign it to data and feed to update_threshold_value()
	// int data[3] = pop(accel_queue_head, queue_tail);?
	value = update_threshold_value(data);
		
	/* state: Motion the box is undergoing. Has 4 seperate values.
	 	0: box is not accelerating.
		1: box may be accelerating, wait for another reading.
	 	2: box is accelerating. Start recording values to find max.
		3: box may have decelarated below threshold. Await further input to confirm.
		
	Something to Note: 
		This statemachine will not allow output until the object has stopped or 
		until acceleration has dropped to a low enough point. I can see about fixing this
		in a later iteration but this will do for now.
		
	TODO: update this to compare the value to max rather than a fixed value.
	This will give us a peak value and allow us to determine that the acceleration spike is falling, and
	fix the problem of no output until no acceleration.
	*/	
	switch(state)
	{
		case (0) : if(value > 0){ state = 1; max = 0; }		// 
			break;
		case (1) : if(value > 0){ state = 2; max = value; }	//
			else{ state = 0; }			//
			break;
		case (2) : if(value < max){ state = 3; }
			 if(max < value) {max = value;}		
			break;
		case (3) : if(value < max){ state = 0; /*TODO: output max to external IPC here. (push(value_queue_head))? */   }
			if(value > max){ state = 2; max = value; }
			break;
		default : state = 0;
	}
	
}

