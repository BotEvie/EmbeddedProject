//Nathan Matthews
//
//Play sound to speaker using DAC.
//

#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header



#include "stm32l053xx.h"


//Using PWM instead of DAC now

int main(void)
{
	RCC-> IOPENR |= RCC_IOPENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE0_Msk;
	GPIOA->MODER |= 2 << GPIO_MODER_MODE0_Pos;
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL0_Msk);
	GPIOA->AFR[0] |= 2 << GPIO_AFRL_AFSEL0_Pos;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->PSC = 100; /* (1) */ // Prescale divider
	TIM2->ARR = 8; /* (2) */  // TOP
	TIM2->CCR1 = 7; /* (3) */   // MATCH
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1
	| TIM_CCMR1_OC1PE; /* (4) */
	TIM2->CCER |= TIM_CCER_CC1E; /* (5) */
	TIM2->CR1 |= TIM_CR1_CMS_0 | TIM_CR1_CEN; /* (6) */
	TIM2->EGR |= TIM_EGR_UG; /* (7) */
	
	while (1){
		for (volatile uint32_t n = 0; n < 12345; n++){}
	}
}


//Plays sound at 1325 Hz

//Need to configure the PWM on TIM22
//Need to trigger PWM on input from queue
//Implement these into functions without main. Accepts value from queue.

