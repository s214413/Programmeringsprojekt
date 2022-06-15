#include "stm32f30x_conf.h" // STM32 config
#include "control.h"
#include "timer.h"




void timer2() {
	RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
	TIM2->CR1 = 0x0000; // Configure timer 2
	TIM2->ARR = 639999; // Set reload value to 639999
	TIM2->PSC = 0x0000; // Set prescale value
	TIM2->DIER |= 0x0001; 	// Enable timer 2 interrupts

	NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
	NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt

	TIM2->CR1 = 0x0001; // Enable timer 2
}

void clockstop(){
	TIM2->CR1 |= 0x0000;
	NVIC_DisableIRQ(TIM2_IRQn);
}

void clockstart(){
	TIM2->CR1 = 0x0001;
	NVIC_EnableIRQ(TIM2_IRQn);
}


