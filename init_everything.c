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
	
	RCC->APB2ENR |= 1 << (RCC_APB2ENR_SPI1EN_Pos);
	//bit 11, 8-bit package
	//bit 9= 1, ssm
	//bit 8= 1, ssi
	//bit 7= 0, MSB first
	//bit 6= 1, SPI on
	//bits[5:3], 11MHz max on data transfer
	//bit 2= 1, MOSI first will eventually change to slave
	//bit 1= 1, CPOL
	//bit 0= 1, CPHA
	SPI2->CR1 |= 1 << (SPI_CR1_DFF_Pos);
	SPI2->CR1 &= ~(7u << (SPI_CR1_BR_Pos));
	SPI2->CR1 |= 1 << (SPI_CR1_SSM_Pos);
	SPI2->CR1 |= 1 << (SPI_CR1_SSI_Pos);
	SPI2->CR1 |= 1 << (SPI_CR1_MSTR_Pos);
	SPI2->CR1 |= 1 << (SPI_CR1_SPE_Pos);
	SPI2->CR1 |= 1 << (SPI_CR1_CPOL_Pos);
	SPI2->CR1 |= 1 << (SPI_CR1_CPHA_Pos);
	
}

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