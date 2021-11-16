//authors: Dru Walkowski

//TODO: copyright 

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
		 	__diable_irq();
			sound_on();		 // also determines how loud
			sleepytime();		 // puts to sleep until we slowly empty the queue
		 	__set_primask(interuptible);
		}           
		        
		
	}

}
