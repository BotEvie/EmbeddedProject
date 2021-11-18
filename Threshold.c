// This state machine takes a value from the accelerometer, and converts said value to an arbitrary number depending on the range of the value.
// It then tests the arbitrary number with reference to max to determine if we are accelerating in a similar fashion to an edge detector.
// Once it has been decided that max acceleration has been reached, we output the max value recorded to an external queue.

/*
Copyright 2021 Erich Vernon

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.
*/

#include <stdint.h>
#include "queue.h"


void update_threshold_value(uint8_t toast[3], uint8_t *value);
void threshold_compare(queue_t *accel_queue, queue_t *value_queue);

// Tested output accelerometer system total = T.O.A.S.T.

void update_threshold_value(uint8_t toast[3], uint8_t *value)
{
	uint8_t max;
	// The recieved value is in two's complement, so we change it back to standard binary.
	for( int i = 0; i<3; i++)
	{
		toast[i] = ~((toast[i])-1);
		toast[i] = (toast[i] > 0)? toast[i]: -(toast[i]);
		if(toast[i] > max){ max = toast[i];}
	}

	if(max > 190){ *value = 3; }
	else if(max > 125){ *value = 2; }
	else if(max > 90){ *value = 1; }
	else{ *value = 0; }
}


// full state machine
void threshold_compare(queue_t *accel_queue, queue_t *value_queue)
{
	static int threshold_state;	// current state
	static int threshold_max;	// highest recorded value during a spike
	uint8_t value = 0;
	uint8_t xyz[3];
	
	uint32_t interruptible = __get_primask();
	__disable_irq();
	for(int i=0; i< 3; i++)
	{
		pop(accel_queue, &(xyz[i]));
	}
		
	update_threshold_value(xyz, &value);
		/* state: Motion the box is undergoing. Has 4 seperate values.
			0: box is not accelerating.
			1: box may be accelerating, wait for another reading.
			2: box is accelerating. Start recording values to find max.
			3: box may have fallen below threshold. Await further input to confirm. Push max to queue if falling.
			*4: Wait for acceleration spike to fully end. Stay here until it ends. WARNING: This has not been tested and can be removed for "tested" functionality.
		*/	
		switch(threshold_state)
		{
			case (0) : if(value > 0){ threshold_state = 1; threshold_max = 0; }	// From rest to next state if value is non-zero.
				break;
			case (1) : if(value > 0){ threshold_state = 2; threshold_max = value; }	// Confirmed acceleration
				else{ threshold_state = 0; }					// False alarm, just noise... probably.
				break;
			case (2) : if(value < threshold_max){ threshold_state = 3; }		// Value less than than max. Maybe falling so advance to state three.
    				 if(threshold_max < value) {threshold_max = value;}		// Max less than value. Store value as max and hold state.
    				break;
    			case (3) : if(value < threshold_max){ threshold_state = 4; push(value_queue, (uint8_t)threshold_max); threshold_max=0; }		// if value below max again spike is probably falling so push then clear max.
    				if(value > threshold_max){ threshold_state = 2; threshold_max = value; } 		// if value higher than max, spike still rising, record new value as max and retern to state 2.
    				break;
    	    		case (4) : if (value != 0) { threshold_state = 4; }					// We will wait for the spike to end.
				    else if (value == 0 && threshold_max !=0) { threshold_state = 4; threshold_max = value; }			// Maybe we stopped accelerating.	
				    else if (value == 0 && threshold_max == 0) { threshold_state = 0; }			// Yep! Stopped. Go on back to the start.
				    break;
			default : threshold_state = 0;
		}
	__set_primask(interuptible);
}
