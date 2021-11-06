/* Erich Vernon
	Acceleration threshold statemachine
	
*/

#include <stm32l053xx.h>
#include <stdint.h>

void update_threshold_value(int toast);
void threshold_fsm(int value);


// 
// Value 3 is more acceleration (higher voltage input)
// 
// +- 16384 is max value 
//
// x = (x > 0)? x: -x;
//
//

// Tested output accelerometer system total = T.O.A.S.T.
// TODO: change this to accept and test an array of 3 integers. Then return the highest value.
void update_threshold_value(int toast)
{
  	toast = (toast > 0)? toast: -toast;
  
	if(toast > 12000) { value = 3; }
	if(toast > 8000){ value = 2; }
	if(toast > 4000){ value = 1; }
	else{ value = 0; }
  	return value;
}

void threshold_fsm()
{
	static int state;
	static int value;
	static int max;
	int data[3];
	
	// TODO: get acceleration data from external queue. Assign it to data and feed to update_threshold_value()
	value = update_threshold_value(toast);
		
	/* state: Motion the box is undergoing. Has 4 seperate values.
	 	0: box is not accelerating.
		1: box may be accelerating, wait for another reading.
	 	2: box is accelerating. Start recording values to find max.
		3: box may have decelarated below threshold. Await further input to confirm.		
	*/	
	switch(state)
	{
		case (0) : if(value > 0){ state = 1; max = 0; }
			break;
		case (1) : if(value > 0){ state = 2; max = value;}
			if(value < 0){ state = 0; }	
			break;
		case (2) : if(value < 0){ state = 3; if(max < value) {max = value;} }
			break;
		case (3) : if(value < 0){ state = 0; //TODO: output max to external IPC here  }
			if(value > 0){ state = 2; if(max < value) {max = value;} }
			break;
		default : state = 0;
	}
	
}

