// initionalization of things

#include <stm32l053xx.h>
#include <stdint.h>

void init_spi(void);
void init_all(void);
void init_gpio(void);
void init_DAC(void);
void init_timer2(void);


void init_spi()
{ // accelerometer uses spi or I2C and I don't really know how to use I2C
	
	
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
{// DAC'ing to the speaker
	
}

void init_timer2()
{//timer 2 is used as the trigger for the interupt of the ADC
	//TODO: timing specifications
}









void init_all()
{
	
}