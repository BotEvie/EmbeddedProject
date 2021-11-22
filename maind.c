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


extern void update_threshold_value(uint16_t toast, uint16_t *value);
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
queue_t n;


void sleepytime(queue_t *q0, queue_t *q1)
{	push(&killer, 0x01);
	uint16_t num;
	pop(&n,&num);
	if(num >= 12345u)
	{
		sound_off();
		while(true == cq_stuff(q0))
		{// empty the queue
			
			if(num == 1)
			{	uint16_t garbage;
				pop(q0, &garbage);
				pop(q0, &garbage);
				pop(q0, &garbage);
				pop(q0, &garbage);
				pop(q0, &garbage);
				pop(q0, &garbage);
				pop(q0, &garbage);
				pop(q0, &garbage);
				pop(q0, &garbage);
		
				pop(&killer, 0x00);
			}
			num--;
			//push(&n,num);
		}
		pop(&n,&num);
	}
	num+=3;
	push(&n,num);
}



int main(void)
{
	//all initialization fncs
	init_all();
	
	// queue init
	init_queue(&yeet_queue, 30);
	init_queue(&highest, 2);
	init_queue(&killer, 1);
	init_queue(&n, 1);
	
	while(1)
	{
		
		if((TIM_SR_UIF == 1) && !(cq_stuff(&killer))){x_y_z_r(&yeet_queue);}
		if((cq_stuff(&yeet_queue)) && !(cq_stuff(&killer))){threshold_compare(&yeet_queue, &highest);}   // semaphore for compare value
		// bleow tasks are sequential, but different authors
		// after playing sound we are using sleepytime as alt. schedule
		// sleepytime only runs above 2 tasks until yeet_queue is empty
		if(cq_stuff(&highest) | cq_stuff(&killer))
		{	uint32_t interruptible = __get_PRIMASK();
		 	__disable_irq();
			if(cq_stuff(&killer) == false){sound_on();}		 // also determines how loud
			sleepytime(&yeet_queue, &killer);		 // puts to sleep until we slowly empty the queue
		 	__set_PRIMASK(interruptible);
		}           
		  
		
	}

}

