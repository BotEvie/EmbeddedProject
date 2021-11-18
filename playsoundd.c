//Nathan Matthews
//
//Play sound to speaker using PWM.
//

#include <stdio.h>
#include <stdlib.h>
#include "stm32l053xx.h"


void sound_on(void);
void sound_off (void);

void sound_on(){
	RCC->APB2ENR |= RCC_APB2ENR_TIM22EN;
	TIM22->PSC = 100;                                              // Prescale to make 1325 Hz
	TIM22->ARR = 8;                                                
	TIM22->CCR1 = 7;                                             
	TIM22->CCMR1 |= 6 << TIM_CCMR1_OC1M_Pos;
	TIM22->CCMR1 |= 1 << TIM_CCMR1_OC1PE; 
	TIM22->CCER |= 1 << TIM_CCER_CC1E; 
	TIM22->CR1 |= 1 << TIM_CR1_CMS_Pos; 
	TIM22->CR1 |= 1 << TIM_CR1_CEN;                    //CEN bit turns on the counter to start the sound
	TIM22->EGR |= 1 << TIM_EGR_UG; 
	
	for(volatile int32_t n = 0; n < 7000; n++){}
}

void sound_off(){
	TIM22->CCER &=  ~(TIM_CCER_CC1E_Msk);                                   //CEN bit turns off the counter to stop the sound
}

//PA6 is configured to TIM22 in init_everything task
//These 2 functions should be called with different triggers.
//One function enables the PWM, one disables.
