//Nathan Matthews
//
//Play sound to speaker using PWM.
//


#include <stdio.h>
#include <stdlib.h>
#include "stm32l053xx.h"


void sound_on(void);
void sound_off (void);

//Functions alternate whether channel 1 for TIM22 is active or inactive

void sound_on(){
	TIM22->CCER |= TIM_CCER_CC1E; 
}

void sound_off(){
	TIM22->CCER &=  ~(TIM_CCER_CC1E_Msk);                                 
}

//PA6 is configured to TIM22 in init_everything task
//These 2 functions should be called with different triggers.
//One function enables the PWM, one disables.
