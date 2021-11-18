//Nathan Matthews
//
//Play sound to speaker using PWM.
//

/*
Copyright 2021 Nathan Matthews

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.
*/

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
	TIM22->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1
	| TIM_CCMR1_OC1PE; 
	TIM22->CCER |= TIM_CCER_CC1E; 
	TIM22->CR1 |= TIM_CR1_CMS_0 | TIM_CR1_CEN;                    //CEN bit turns on the counter to start the sound
	TIM22->EGR |= TIM_EGR_UG; 
}

void sound_off(){
	TIM22->CCER &=  ~(TIM_CCER_CC1E_Msk);                                 //CEN bit turns off the counter to stop the sound
}

//PA6 is configured to TIM22 in init_everything task
//These 2 functions should be called with different triggers.
//One function enables the PWM, one disables.
