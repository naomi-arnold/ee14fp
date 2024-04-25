#include "Joystick.h"
#include "LED.h"
#include "stm32l476xx.h"

void Joystick_Initalize(void) {
	
	LED_Init();
	Red_LED_On();
	// Enable PA.0 to input mode (0b00)
	GPIOA->MODER &= ~GPIO_MODER_MODE0;
	
		//Enable PA.1 to input mode (0b00)
	GPIOA->MODER &= ~ GPIO_MODER_MODE1;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE2;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE3;
	
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	
	//set pup data for 0
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
	//set the pull up resistor
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1;
	
	
	//clear pull up data for 1
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1;
	//set the pull up resistor
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD1_1;
	
	//set pup data for 2
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2;
	//set the pull up resistor
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_1;
	//set pup data for 3
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3;
	//set the pull up resistor
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_1;
	
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
	//set the pull up resistor
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD5_1;
	// Enable SYSCFG clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	// Select PA.0 as the trigger source of EXTI 0
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	
	//select PA.1 as the trigger source of EXTI 1
	
	SYSCFG->EXTICR[0] &= ~ SYSCFG_EXTICR1_EXTI1;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;
	
	//select PA.2 as the trigger source of EXTI 2
	SYSCFG->EXTICR[0] &= ~ SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;
	
	SYSCFG->EXTICR[0] &= ~ SYSCFG_EXTICR1_EXTI3;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;
	
	SYSCFG->EXTICR[1] &= ~ SYSCFG_EXTICR2_EXTI5;
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI5_PA;
	
	// Enable rising edge trigger for EXTI0
	// Rising trigger selection register (RSTR)
	// 0 = disabled, 1 = enabled
	EXTI->RTSR1 |= EXTI_RTSR1_RT0;
	//enable rising edge for EXTIO 1
	EXTI->RTSR1 |= EXTI_RTSR1_RT1;
	//enable rising edge for EXTIO2
	EXTI->RTSR1 |= EXTI_RTSR1_RT2;
	
	EXTI->RTSR1 |= EXTI_RTSR1_RT3;
	
	EXTI->RTSR1 |= EXTI_RTSR1_RT5;
	
	// Disable falling edge trigger for EXTI0
	// Fallting trigger selection register (FSTR)
	// 0 = disabled, 1 = enabled
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT0;
	
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT1;
	//disable falling edge for EXTI2
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT2;
	
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT3;
	
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT5;
	
	// Enable EXTI 0 interrupt
	// Interupt mask register: 0 = disabled, 1 = enabled
	EXTI->IMR1 |= EXTI_IMR1_IM0;
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM5;
	
	NVIC_SetPriority(EXTI0_IRQn, 2);
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	NVIC_SetPriority(EXTI1_IRQn, 2);
	NVIC_EnableIRQ(EXTI1_IRQn);
	
	
	NVIC_SetPriority(EXTI2_IRQn, 2);
	NVIC_EnableIRQ(EXTI2_IRQn);
	
	NVIC_SetPriority(EXTI3_IRQn, 2);
	NVIC_EnableIRQ(EXTI3_IRQn);
	
	NVIC_SetPriority(EXTI9_5_IRQn, 2);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void EXTI0_IRQHandler(void) {
	// Check for EXTI0 interrupt flag
	if ((EXTI->PR1 & EXTI_PR1_PIF0) == EXTI_PR1_PIF0) {
		Green_LED_Toggle();
		// Clear interrupt pending request
		EXTI->PR1 |= EXTI_PR1_PIF0;
	}
	
}

void EXTI1_IRQHandler(void) {
	// Check for EXTI1 interrupt flag
	if ((EXTI->PR1 & EXTI_PR1_PIF1) == EXTI_PR1_PIF1) {
	Red_LED_Toggle();
		
		// Clear interrupt pending request
		EXTI->PR1 |= EXTI_PR1_PIF1;
	}
	
}

void EXTI2_IRQHandler(void) {
	// Check for EXTI1 interrupt flag
	if ((EXTI->PR1 & EXTI_PR1_PIF2) == EXTI_PR1_PIF2) {
	Red_LED_Toggle();
		
		// Clear interrupt pending request
		EXTI->PR1 |= EXTI_PR1_PIF2;
	}
	
}

void EXTI3_IRQHandler(void) {
	// Check for EXTI1 interrupt flag
	if ((EXTI->PR1 & EXTI_PR1_PIF3) == EXTI_PR1_PIF3) {
		Red_LED_Toggle();
		
		// Clear interrupt pending request
		EXTI->PR1 |= EXTI_PR1_PIF3;
	}
	
}


	
void EXTI9_5_IRQHandler(void) {
	// Check for EXTI1 interrupt flag
	if ((EXTI->PR1 & EXTI_PR1_PIF5) == EXTI_PR1_PIF5) {
		Red_LED_Toggle();
		
		// Clear interrupt pending request
		EXTI->PR1 |= EXTI_PR1_PIF5;
	}
	
}




