// Reads the sensor because I can't read
// puts into queue for other tasks
// returns because, "I gotta go fast" 
// -Ricky Bobby

/*
Copyright 2021 Dru Walkowski

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.
*/


#include <stm32l053xx.h>
#include <stdint.h>
#include "queue.c"

extern void init_adc(void);
void spiing_r(uint8_t data);
void spiing_w(uint16_t data);
extern bool push(queue_t *q0, uint8_t data);
void x_y_z_r(void);


void spiing_r(uint8_t data_out)
{	//reading the accelerometer
 	static uint16_t n;
  	//currently fake reading
	if (0 == n){n += 1;}
  	else if (n >= 12){ n = 0;}

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
		
	n+=1;
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

