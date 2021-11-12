/* Erich Vernon
	Acceleration threshold statemachine
	
*/

#include <stdint.h>
#include "queue.h"


int update_threshold_value(uint8_t toast);
void threshold_fsm(queue_t *accel_queue, queue_t *value_queue);

// Tested output accelerometer system total = T.O.A.S.T.
// 
int update_threshold_value(uint8_t toast, uint8_t *value)
{
	
	// Higher numbers indicate higher acceleration, these are just random values with no real rhyme or reason
  	*value = (*value > 0)? *value: -(*value);
	if(toast > 100){ *value = 3; }
	if(toast > 50){ *value = 2; }
	if(toast > 15){ *value = 1; }
	else{ *value = 0; }
}


// full state machine
void threshold_fsm(queue_t *accel_queue, queue_t *value_queue)
{
	volatile int threshold_state;	// current state
	volatile int threshold_max;	// highest recorded value this spike
	uint8_t value = 0;
	uint8_t data=0;
	
	pop(accel_queue, &data);
	value = update_threshold_value(data);
		
	/* state: Motion the box is undergoing. Has 4 seperate values.
	 	0: box is not accelerating.
		1: box may be accelerating, wait for another reading.
	 	2: box is accelerating. Start recording values to find max.
		3: box may have decelarated below threshold. Await further input to confirm.
	*/	
	switch(threshold_state)
	{
		case (0) : if(value > 0){ threshold_state = 1; threshold_max = 0; }		
			break;
		case (1) : if(value > 0){ threshold_state = 2; threshold_max = value; }	
			else{ threshold_state = 0; }			
			break;
		case (2) : if(value < threshold_max){ threshold_state = 3; }
			 if(threshold_max < value) {threshold_max = value;}		
			break;
		case (3) : if(value < threshold_max){ threshold_state = 0; push(value_queue, threshold_max); }
			if(value > threshold_max){ threshold_state = 2; threshold_max = value; }
			break;
		default : state = 0;
	}
	
}

