//authors: Dru Walkowski

//TODO: copyright 

#include <stm32l053xx.h>
#include <stdint.h>
#include <stdbool.h>
/*
#include "init_everythingd.c"
#include "accel_readd.c"
#include "playsoundd.c"
#include "queued.c"
#include "thresholdd.c"
*/
#include "queued.h"


extern void update_threshold_value(uint8_t toast, uint8_t *value);
extern void threshold_compare(queue_t *accel_queue, queue_t *value_queue);
extern void spiing_r(int data, queue_t *q0);
extern void spiing_w(uint16_t data);
extern void x_y_z_r(queue_t *q0);
extern void init_all(void);
extern void init_gpio(void);
extern void init_timer(void);
extern void init_accel(void);
extern void sound_on(void);
extern void sound_off (void);
extern bool cq_full(queue_t *q0);
extern bool cq_stuff(queue_t *q0);



void sleepytime(queue_t *q0, queue_t *q1);



// queues
queue_t yeet_queue;
queue_t highest;
queue_t killer;


void sleepytime(queue_t *q0, queue_t *q1)
{
	sound_off();
	
	while(true == cq_stuff(q0))
	{// empty the queue
		
		threshold_compare(q0, q1);
		threshold_compare(q0, q1);
		threshold_compare(q0, q1);
	}
}



int main(void)
{
	//all initialization fncs
	init_all();
	
	// queue init
	init_queue(&yeet_queue, 30);
	init_queue(&highest, 2);
	init_queue(&killer, 2);
	
	while(1)
	{
		
		if(TIM_SR_UIF == 1){x_y_z_r(&yeet_queue);}
		if(cq_stuff(&yeet_queue)){threshold_compare(&yeet_queue, &highest);}   // semaphore for compare value
		// bleow tasks are sequential, but different authors
		// after playing sound we are using sleepytime as alt. schedule
		// sleepytime only runs above 2 tasks until yeet_queue is empty
		if(cq_stuff(&highest) == true)
		{	uint32_t interruptible = __get_PRIMASK();
		 	__disable_irq();
			sound_on();		 // also determines how loud
			sleepytime(&yeet_queue, &killer);		 // puts to sleep until we slowly empty the queue
		 	__set_PRIMASK(interruptible);
		}           
		  
		
	}

}

