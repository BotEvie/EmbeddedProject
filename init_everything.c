// initionalization of things

#include <stm32l053xx.h>
#include <stdint.h>

void init_adc(void);
void init_all(void);
void init_gpio(void);
void init_DAC(void);
void init_timer2(void);

// initionalization of the ADC we only have to run this bitch once
void init_adc()
{
	//turn das clock on
	RCC->AHBENR |= RCC_APB2ENR_ADCEN;
	
	//TODO:
	
		
	//trigger for adc to TRG3 TIM2_CH4 011 on rising edge
	ADC1->CFGR1 |= 1 << ADC_CFGR1_EXTEN_Pos;
	ADC1->CFGR1 |= 3 << ADC_CFGR1_EXTSEL_Pos;
	//channel selection chsel
	ADC1->CHSELR |= 1 << ADC_CHSELR_CHSEL0_Pos;
	ADC1->CHSELR |= 1 << ADC_CHSELR_CHSEL1_Pos;
	ADC1->CHSELR |= 1 << ADC_CHSELR_CHSEL2_Pos;
	//discontinuous mode
	ADC1->CFGR1 |= 1u << ADC_CFGR1_DISCEN_Pos;
	
	
	// calibration
	ADC1->CR |= 1u << ADC_CR_ADCAL_Pos;
	while (ADC_CR_ADCAL & ~(ADC_ISR_EOCAL))
	{}
	// aden=0 & dmaen=0, set adcal= 1, wait for eocal= 1 or adcal= 0
	
	
	// to turn on adc
	ADC1->CR |= 1u << ADC_CR_ADEN_Pos;
	while (ADC_ISR_ADRDY == 0)
	{}
	//adrdy bit to 1, set aden = 1 in adc_cr, wait for adrdy bit in adc_isr is high
}

void init_gpio()
{
	//GPIO clock A, B, C, E
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	//RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	//RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
	//RCC->IOPENR |= RCC_IOPENR_GPIOHEN;
	
	//PA 0 for first ADC (add fnc)
	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk);
	//GPIOA->MODER |= 1 << GPIO_MODER_MODE0_Pos;
	
	//PA 1 for second ADC (add fnc)
	GPIOA->MODER &= ~(GPIO_MODER_MODE1_Msk);
	//GPIOA->MODER |= 1 << GPIO_MODER_MODE1_Pos;
	
	//PA 2 for third ADC (add fnc)
	GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk);
	//GPIOA->MODER |= 1 << GPIO_MODER_MODE2_Pos;
	
	//PA 4 for DAC (only DAC output)(add fnc)
	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk);
	//GPIOA->MODER |= 1 << GPIO_MODER_MODE4_Pos;
	
}

void init_DAC()
{
	
}

void init_timer2()
{//timer 2 is used as the trigger for the interupt of the ADC
	
}









void init_all()
{
	
}