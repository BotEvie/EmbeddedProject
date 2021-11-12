//Nathan Matthews
//
//Play sound to speaker using DAC.
//

#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx.h"                  // Device header



void init_DAC(void);
void init_timer(void);
void init_pa4(void);

void init_DAC(){
	
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;   	    //Supply clock to DAC
	
	DAC->CR &= ~DAC_CR_WAVE1_Msk;
	DAC->CR |= 2 << DAC_CR_WAVE1_Pos;           //Generate trinagle sound wave
	
	DAC->CR &= ~DAC_CR_MAMP1_Msk;
	DAC->CR |= 9 << DAC_CR_MAMP1_Pos;           //Triangle has amplitude of 1023
	
	DAC->CR &= ~DAC_CR_BOFF1_Msk;
	DAC->CR |= 1 << DAC_CR_BOFF1_Pos;           //Output buffer enable to avoid external op amp
	
	DAC->CR &= ~DAC_CR_TEN1_Msk;
	DAC->CR |= 1 << DAC_CR_TEN1_Pos;            //Trigger enable to allow a triangle wave 
	
	DAC->CR &= ~DAC_CR_TSEL1_Msk;
	DAC->CR |= 6 << DAC_CR_TSEL1_Pos;	    //Trigger on an timer 6
	
	DAC->CR &= ~DAC_CR_EN1_Msk;										
	DAC->CR |= 1 << DAC_CR_EN1_Pos;	            //Enable DAC on channel 1
	
}

void init_timer(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	
	TIM6->CR1 &= ~TIM_CR1_CEN_Msk;
	TIM6->CR1 |= 1 << TIM_CR1_CEN_Pos;
}

void init_pa4(){
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE4_Msk;
  GPIOA->MODER |= 1 << GPIO_MODER_MODE4_Pos;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
  GPIOA->MODER |= 1 << GPIO_MODER_MODE5_Pos;
}

int main(void){
	init_pa4();
	init_DAC();
	init_timer();
	
	while(1){
		
	}
}
