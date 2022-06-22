void clockstop() {
	TIM2->CR1 |= 0x0000;
	NVIC_DisableIRQ(TIM2_IRQn);
}

void clockstart() {
	TIM2->CR1 = 0x0001;
	NVIC_EnableIRQ(TIM2_IRQn);
}
