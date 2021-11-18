// Reads the sensor because I can't read
// puts into queue for other tasks
// returns because, "I gotta go fast" 
// -Ricky Bobby



#include <stm32l053xx.h>
#include <stdint.h>
#include "queued.h"



void spiing_r(uint16_t data, queue_t *q0);
void spiing_w(uint16_t data);
//extern bool push(queue_t *q0, uint16_t data);
void x_y_z_r(queue_t *q0);


void spiing_r (uint16_t data_out, queue_t * q0)
{				//reading the accelerometer
 	static uint16_t n;
  	//currently fake reading
	if (0 == n){n += 1;}
  	else if (n >= 127){ n = 0;}

  	//uint16_t data_in = n & data_out;
    	uint16_t data_in = n;
	
	//PB12 goes low in ODR
	//GPIOB->ODR &= ~(1u << 12);
	//sending register location
	//SPI2->DR |= data_out;
	//MISO puts data in SPI DR then to queue
	//uint16_t data_in = ((SPI2->DR) & 0x000F); 
	push(q0,data_in);
	//wait for SPI to finish getting data
	//for(volatile int32_t n = 0; n < 3; n++){}
	//while(SPI2->SR & SPI_SR_BSY){}
	//PB12 goes high in ODR
	//GPIOB->ODR |= 1 << 12;
		
	n+=3;
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

void x_y_z_r(queue_t *q0)
{ //needs to read all 3 before 39 us
	//should take < 8 us to make a read for 8bit read from accel
	
	//x axis read
	//spiing_r(0x09);
	spiing_r(0x00,q0);
	//y axis read
	//spiing_r(0x0B);
	spiing_r(0x00,q0);
	//z axis read
	//spiing_r(0x0D);
	spiing_r(0x6A,q0);
	// reseting the timer flag cause we done
	TIM2->SR |= TIM_SR_UIF_Msk << TIM_SR_UIF_Pos;
	
}
