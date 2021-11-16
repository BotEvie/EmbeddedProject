//authors: Dru Walkowski


/*
Copyright 2021 Dru Walkowski

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.
*/


#include <stm32l053xx.h>
#include <stdint.h>
#include "init_everything.c"
#include "accel_read.c"
#include "playsound.c"
#include "queue.c"

//function calls (update as needed)

//accelerometer read function and the trigger is a timer interupt from TIM2
extern void x_y_z_r(void);
//threshold_compare fnc and trigger
//trigger is from yeet_queue
extern bool cq_stuff(queue_t *q0);
extern void threshold_compare(void);
//sound_on fnc and trigger (NATE)
//trigger is cq_stuff, but with highest queue
extern void sound_on(void);
//TODO: sleepytime fnc
extern void sleepytime(void);
//TOD0: init fnc's
extern void init_all(void);



int main(void)
{
	//TODO: intitionalization functions (DRU)
	init_all();
	//TODO: queue init
	
	
	while(1)
	{
		
		if(TIM_SR_UIF == 1){x_y_z_r();}
		if(cq_stuff(&yeet_queue) == true){threshold_compare();}   // semaphore for compare value
		// bleow tasks are sequential, but different authors
		// after playing sound we are using sleepytime as alt. schedule
		// sleepytime only runs above 2 tasks until yeet_queue is empty
		if(cq_stuff(&highest) == true)
		{	uint32_t interruptible = __get_primask();
		 	__disable_irq();
			sound_on();		 // also determines how loud
			sleepytime();		 // puts to sleep until we slowly empty the queue
		 	__set_primask(interuptible);
		}           
		        
		
	}

}
