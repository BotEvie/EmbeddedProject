//authors: Dru Walkowski

//TODO: copyright 

#include <stm32l053xx.h>
#include <stdint.h>
#include "init_everything.c"

//function calls (update as needed)

//TODO: ADC_read fnc and its trigger (DRU)
extern void ADC_read(void);
//TODO: threshold_compare fnc and trigger
extern trigger_2();
extern void threshold_compare(void);
//TODO: play_sound fnc and trigger (NATE)
extern trigger_3();
extern void play_sound(void);
//TODO: change_sound fnc and trigger (NATE)
extern trigger_4();
extern void change_sound(void);
//TODO: sleepytime fnc and trigger
extern trigger_5(); //if queue is full interupt (THIS MIGHT BE HARD)
extern void sleepytime(void);
//TODO: init fnc's
extern void init_all(void);


int main(void)
{
	//TODO: intitionalization functions (DRU)
	//TODO: queue init
	
	while(1)
	{
		
		if(trigger_1()){ADC_read();}
		if(trigger_2()){threshold_compare();}   // semaphore for compare value
		if(trigger_3()){play_sound();}          // also determines how loud
		if(trigger_4()){change_sound();}
		if(trigger_5()){sleepytime();}          // puts to sleep until we slowly empty the queue
		
	}

}