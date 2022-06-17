#include "stm32f30x_conf.h" // STM32 config
#include "stdint.h"
#include "stdio.h"
#include "control.h"

void initJoystick() {
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

	// Set pin PA4 to input
	GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

	// Set pin PB0 to input
	GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PB5 to input
	GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// Set pin PC0 to input
	GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

	// Set pin PC1 to input
	GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)
}

uint16_t readJoystick() {
	uint16_t valPA4 = GPIOA->IDR & (0x0001 << 4); //Read from pin PA4

	if (valPA4>0){
		return(1);//PA4 is up, and should return 1
	}

	uint16_t valPB0 = GPIOB->IDR & (0x0001 << 0); //Read from pin PA4

	if (valPB0>0){
		return(2);//PB0 is down, and should return 2
	}


	uint16_t valPB5 = GPIOB->IDR & (0x0001 << 5); //Read from pin PA4

	if (valPB5>0){
		return(16);//PB0 is center, and should return 16
	}


	uint16_t valPC0 = GPIOC->IDR & (0x0001 << 0); //Read from pin PC0

	if (valPC0>0){
		return(8);//PB0 is right, and should return 8
	}


	uint16_t valPC1 = GPIOC->IDR & (0x0001 << 1); //Read from pin PC1

	if (valPC1>0){
		return(4);//PC1 is left, and should return 4
	}
}

void initPot() {
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

	// Set pin PA0 to input
	GPIOA->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)


	// Set pin PA1 to input
	GPIOA->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOA->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)


}

void calibrate(){
	RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
	RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

	ADC1->CR = 0x00000000; // Clear CR register
	ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
	ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds
	ADC1->CR |= 0x80000000; // Start ADC1 calibration
	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while
	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
	while (!(ADC1->ISR & 0x00000001)); // Wait until ready
}

int16_t setPot(int8_t channel){
	int16_t x;

	if (channel==1){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);

		ADC_StartConversion(ADC1); // Start ADC read
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

		x = ADC_GetConversionValue(ADC1); // Read the ADC value
	}
	else if (channel==2){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);

		ADC_StartConversion(ADC1); // Start ADC read
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

		x = ADC_GetConversionValue(ADC1); // Read the ADC value
	}

	return x;
}

void initLed(){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

	// Set pin PA9 to output (blue)
	GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
	GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
	GPIOA->OTYPER &= ~(0x0001 << (9 * 1)); // Clear output type register
	GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
	GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)


	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B

	// Set pin PB4 to output (red)
	GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
	GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
	GPIOB->OTYPER &= ~(0x0001 << (4 * 1)); // Clear output type register
	GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
	GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// Set pin PC7 to output (green)
	GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
	GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
	GPIOC->OTYPER &= ~(0x0001 << (7 * 1)); // Clear output type register
	GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
	GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
}


void setLed(uint8_t red, uint8_t green, uint8_t blue) {

	if (blue < 1) {
		GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high
	}
	else if (blue > 0){
		GPIOA->ODR &=~ (0x0001 << 9);
	}

	if (red < 1) {
		GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high
	}
	else if (red > 0){
		GPIOB->ODR &=~ (0x0001 << 4);
	}


	if (green < 1) {
		GPIOC->ODR |= (0x0001 << 7); //Set pin PB4 to high
	}
	else if (green > 0){
		GPIOC->ODR &=~ (0x0001 << 7);
	}
}

void joyLed() {
	if (readJoystick()==1){
		setLed(1, 0, 0); //When joystick is up, led=red
	}
	else if (readJoystick()==2){
		setLed(0, 1, 0); //When joystick is down, led=green
	}
	else if (readJoystick()==4){
		setLed(0, 0, 1); //When joystick is left, led=blue
	}
	else if (readJoystick()==8){
		setLed(1, 1, 0); //When joystick is right, led=yellow
	}
	else if (readJoystick()==16){
		setLed(1, 1, 1); //When joystick is center, led=white
	}
	else {
		setLed(0, 0, 0); //Turn off led when joystick is non of above
	}

}

void init2Axis() {
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// Set pin PC2 to input
	GPIOC->MODER &= ~(0x00000003 << (2 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (2 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (2 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (2 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)


	// Set pin PC3 to input
	GPIOC->MODER &= ~(0x00000003 << (3 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (3 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (3 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (3 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}

int16_t set2Axis(int8_t channel) {
	int16_t x;

	if (channel==1){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_1Cycles5);

		ADC_StartConversion(ADC1); // Start ADC read
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

		x = ADC_GetConversionValue(ADC1); // Read the ADC value
	}
	else if (channel==2){
		ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_1Cycles5);

		ADC_StartConversion(ADC1); // Start ADC read
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

		x = ADC_GetConversionValue(ADC1); // Read the ADC value
	}

	return x;
}

void initButton() {
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// Set pin PC10 to input
	GPIOC->MODER &= ~(0x00000003 << (10 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (10 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (10 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (10 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)


	// Set pin PC11 to input
	GPIOC->MODER &= ~(0x00000003 << (11 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000000 << (11 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIOC->PUPDR &= ~(0x00000003 << (11 * 2)); // Clear push/pull register
	GPIOC->PUPDR |= (0x00000002 << (11 * 2)); // Set push/pull register (0x00 -No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}

int8_t setButton() {
	uint16_t valPC10 = GPIOC->IDR & (0x0001 << 10); //Read from pin PC10

	if (valPC10>0){
		return(10);//PC10 should return 10, when pressed down
	}

	uint16_t valPC11 = GPIOC->IDR & (0x0001 << 11); //Read from pin PC10

	if (valPC11>0){
		return(11);//PC11 should return 11, when pressed down
	}
}

