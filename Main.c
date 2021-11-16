//authors: Dru Walkowski

//TODO: copyright 

#include <stm32l053xx.h>
#include <stdint.h>
#include "init_everything.c"
#include "accel_read.c"
#include "playsound.c"

//function calls (update as needed)

//accelerometer read function and the trigger is a timer interupt from TIM2
extern void x_y_z_r(void);
//TODO: threshold_compare fnc and trigger
extern trigger_2();
extern void threshold_compare(void);
//TODO: sound_on fnc and trigger (NATE)
extern trigger_3();
extern void sound_on(void);
//TODO: sound_off fnc and trigger (NATE)
extern trigger_4();
extern void sound_off(void);
//TODO: sleepytime fnc and trigger
extern trigger_5(); //if queue is full interupt (THIS MIGHT BE HARD)
extern void sleepytime(void);
//TODO: init fnc's
extern void init_all(void);



int main(void)
{
	//TODO: intitionalization functions (DRU)
	init_all();
	//TODO: queue init
	
	while(1)
	{
		
		if(TIM_SR_UIF == 1){x_y_z_r();}
		if(trigger_2()){threshold_compare();}   // semaphore for compare value
		if(trigger_3()){sound_on();}          // also determines how loud
		if(trigger_4()){sound_off();}
		if(trigger_5()){sleepytime();}          // puts to sleep until we slowly empty the queue
		
	}

}
