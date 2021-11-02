/* Erich Vernon
	Acceleration threshold statemachine
	
*/

#include <stm32l053xx.h>
#include <stdint.h>

void update_threshold_value(int toast, int value);
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
void update_threshold_value(int toast, int value)
{
  	toast = (toast > 0)? toast: -toast;
  
	if(toast > 12000) { value = 3; }
	if(toast > 8000){ value = 2; }
	if(toast > 4000){ value = 1; }
	else{ value = 0; }
  
}

void threshold_fsm()
{
	static int last_value;
	static int value;
	switch(last_value)
	{
		case(0){ if(value == 0){}
				if(value > 0){}

				
    }
		case(1){ if(value > 1){}
				if(value < 1){}
				

		}
		case(2){ if(value > 2){}
				if(value < 2){}


		}
		case(3){ if(value > 3){}
				if(value < 3){}


		}
		default: last_value = value;
	}
	
}

