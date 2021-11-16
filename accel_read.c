// Reads the sensor because I can't read
// puts into queue for other tasks
// returns because, "I gotta go fast" 
// -Ricky Bobby



#include <stm32l053xx.h>
#include <stdint.h>
#include "queue.c"

extern void init_adc(void);
void spiing_r(uint8_t data);
void spiing_w(uint16_t data);
extern bool push(queue_t *q0, uint8_t data);
void x_y_z_r(void);


void spiing_r(uint8_t data_out)
{//reading the accelerometer
	//currently fake reading
	
	uint8_t data_in = rand & data_out;
	
	//PB12 goes low in ODR
	//GPIOB->ODR &= ~(1u << 12);
	//sending register location
	//SPI2->DR |= data_out;
	//MISO puts data in SPI DR then to queue
	//uint8_t data_in = ((SPI2->DR) & 0x000F); 
	push(&yeet_queue,data_in);
	//wait for SPI to finish getting data
	//for(volatile int32_t n = 0; n < 3; n++){}
	//while(SPI2->SR & SPI_SR_BSY){}
	//PB12 goes high in ODR
	//GPIOB->ODR |= 1 << 12;
}



void spiing_w(uint16_t data_out)
{//writing to the accelerometer
	
	//PB12 goes low in ODR
	GPIOB->ODR &= ~(1u <<12);
	//MOSI pulls data from SPI DR
	SPI2->DR |= 8 >> (data_out & 0xFF00);
	//wait for SPI to finish sending data
	//for(volatile int32_t n = 0; n < 3; n++){}
	while(SPI1->SR & SPI_SR_BSY){}
	//PB12 goes high in ODR
	GPIOB->ODR |= 1 << 12;
	
	//PB12 goes low in ODR
	GPIOB->ODR &= ~(1u <<12);
	//second half of data
	SPI2->DR |= data_out & 0x00FF;
	//wait for SPI to finish sending data
	//for(volatile int32_t n = 0; n < 3; n++){}
	while(SPI1->SR & SPI_SR_BSY){}
	//PB12 goes high in ODR
	GPIOB->ODR |= 1 << 12;
}

void x_y_z_r()
{ //needs to read all 3 before 39 us
	//should take < 8 us to make a read for 8bit read from accel
	
	//x axis read
	//spiing_r(0x09);
	spiing_r(0x00)
	//y axis read
	spiing_r(0x00);
	//z axis read
	spiing_r(0x6A);
	// reseting the timer flag cause we done
	TIM2->SR |= TIM_SR_UIF_Msk << TIM_SR_UIF_Pos;
	
}

