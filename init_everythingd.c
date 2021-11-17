// initionalization of things

#include <stm32l053xx.h>
#include <stdint.h>

// don't need these when files are merged
//void init_spi(void);
void init_all(void);
void init_gpio(void);
void init_timer(void);
void init_accel(void);
extern void spiing_w(uint16_t data);


void init_spi()
{ // accelerometer uses spi or I2C and I don't really know how to use I2C
	
	RCC->APB1ENR |= 1 << (RCC_APB1ENR_SPI2EN_Pos);
	//bit 11, 8-bit package
	//bit 9= 1, ssm
	//bit 8= 1, ssi
	//bit 7= 0, MSB first
	//bit 6= 1, SPI on
	//bits[5:3], 11MHz max on data transfer
	//bit 2= 1, MOSI first will eventually change to slave
	//bit 1= 0, CPOL rests low
	//bit 0= 0, CPHA rising edge start
	SPI2->CR1 |= 1 << (SPI_CR1_DFF_Pos);
	SPI2->CR1 &= (4u << (SPI_CR1_BR_Pos));
	SPI2->CR1 |= 1 << (SPI_CR1_SSM_Pos);
	SPI2->CR1 |= 1 << (SPI_CR1_SSI_Pos);
	SPI2->CR1 |= 1 << (SPI_CR1_MSTR_Pos);
	SPI2->CR1 |= 1 << (SPI_CR1_SPE_Pos);
	
	
}
/*
void init_accel()
{//setting up control registers and stuff
	//first two registers need init before turning on
	
	//INC1 setting physical interupts to 0x00
	//see if following line breaks what I want it to do
	//spiing_w(0x2200);
	
	//setting output data rate
	//deadline 39 us
	spiing_w(0x214F);
	//turing on accelerometer
	spiing_w(0x1BC0);
}
*/
void init_gpio()
{
	//GPIO clock A, B, C, H
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	//RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
	//RCC->IOPENR |= RCC_IOPENR_GPIOHEN;
	
	// PB12, setting the select line as an output
	GPIOB->MODER &= ~(GPIO_MODER_MODE12_Msk);
	GPIOB->MODER |= 1 << (GPIO_MODER_MODE12_Pos);
	
	//PB13 set to alternate function (2), SPI clk
	GPIOB->MODER &= ~(GPIO_MODER_MODE13_Msk);
	GPIOB->MODER |= 2 << (GPIO_MODER_MODE13_Pos);
	
	//PB14 set to alt input (2), MISO
	GPIOB->MODER &= ~(GPIO_MODER_MODE14_Msk);
	GPIOB->MODER |= 2 << (GPIO_MODER_MODE14_Pos);
	
	//PB15 set to alt output (2), MOSI
	GPIOB->MODER &= ~(GPIO_MODER_MODE15_Msk);
	GPIOB->MODER |= 2u << (GPIO_MODER_MODE15_Pos);
	
	//PA 6 for tim22 PWM for sound
	GPIOA->MODER &= ~GPIO_MODER_MODE6_Msk;
	GPIOA->MODER |= 2 << GPIO_MODER_MODE6_Pos;
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL6_Msk);
	GPIOA->AFR[0] |= 5 << GPIO_AFRL_AFSEL6_Pos;
	
}


void init_timer()
{ //timer 2 is used as the trigger for the interupt of the SPI read
	
	RCC->APB1ENR |= 1 << RCC_APB1ENR_TIM2EN_Pos;
	// TOP = 623, 39us
	TIM2->ARR |= 0x026F;
	// overflow trigger for interupt only
	TIM2->CR1 |= 1 << TIM_CR1_URS_Pos;
	
	//timer 6 for DAC
	//RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	//TIM6->CR1 &= ~TIM_CR1_CEN_Msk;
	
	
	// start timer(s)
	TIM2->CR1 |= 1 << TIM_CR1_CEN_Pos;
	// turns on later for PWM
	//TIM6->CR1 |= 1 << TIM_CR1_CEN_Pos;
}


void init_all()
{
	init_gpio();
	init_spi();
	//init_accel();
	
	// timer init needs to be last 
	// once started its go time home girl
	init_timer();
}