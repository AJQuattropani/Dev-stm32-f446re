#include "main.h"

#include <stdio.h>
#include "gpio.h"
#include "usart.h"
#include "clock.h"

extern volatile uint32_t ticks;
void main(void)
{
  configure_clock();
  SystemCoreClockUpdate();

  ENABLE_GPIO_A;
  ENABLE_GPIO_B;
  ENABLE_GPIO_C;

  DUMMY_READ_FROM(RCC->AHB1ENR);

  GP_REG_SET(GPIOA->MODER, GP_OUT, GPIO_MODER_MODER5_Pos);
  GP_REG_SET(GPIOA->MODER, GP_OUT, GPIO_MODER_MODER8_Pos);
  GP_REG_SET(GPIOB->MODER, GP_OUT, GPIO_MODER_MODER5_Pos);
  GP_REG_SET(GPIOC->MODER, GP_IN, GPIO_MODER_MODER13_Pos);

  SysTick_Config(100000); // 10,000,000 / 100,000 = 1
  __enable_irq();

// Enable IRQ Clock
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_Msk;
//#define RCC_APB2ENR_SYSCFGEN_Msk           (0x1UL << RCC_APB2ENR_SYSCFGEN_Pos)  /*!< 0x00004000 */
  DUMMY_READ_FROM(RCC->APB2ENR);

  //SYSCFG->EXTICR[3] &= (SYSCFG_EXTICR4_EXTI13_PC << SYSCFG_EXTICR4_EXTI13_Pos);
  // set exti line 13 to read from PC13
  //SYSCFG->EXTICR[3] &= 0xFF0F; // wipe bits responsible for EXTI13
  SYSCFG->EXTICR[3] &= ~(SYSCFG_EXTICR4_EXTI13_Msk); // wipe bits responsible for EXTI13
  SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR4_EXTI13_PC); // set EXTI13 to use PC (13)

  EXTI->IMR |= EXTI_IMR_MR13_Msk; // enable exti 13
  
  // 1. Configure as interrupt line 13, enable
  // 1a. Programming the two trigger registers with desired edge detection
  EXTI->RTSR |= EXTI_RTSR_TR13_Msk; // trigger on rising edge.
  EXTI->FTSR |= EXTI_FTSR_TR13_Msk; // trigger on falling edge
  // 2a. Write a "1" to corresponding bit in EXT_IMR (interrupt mask register)
  // do I need to read from this?
  //
  // 3. Reset pending bit (?)
  __disable_irq();
  NVIC_EnableIRQ(EXTI15_10_IRQn);

  __enable_irq();

  usart_init(USART2);

  while (1)
  {
    // BUTTON IS PC13
    #define BUTTON_PIN 13
    //if (!(GPIOC->IDR & (1 << BUTTON_PIN))) {
      //GP_REG_TGB(GPIOB->ODR, EXT_LED_PINB); // toggle LED
    //}

    EXTI->SWIER |= EXTI_SWIER_SWIER1_Msk;

    printf("[%.3f] Hello, World!\r\n", (float)ticks/1000.0);

    GP_REG_TGB(GPIOA->ODR, LED_PIN);
    GP_REG_TGB(GPIOA->ODR, EXT_LED_PIN);

    delay_ms(500);
    
    GP_REG_TGB(GPIOA->ODR, LED_PIN);
    delay_ms(100);

    GP_REG_TGB(GPIOA->ODR, LED_PIN);
    
    delay_ms(500);

    GP_REG_TGB(GPIOA->ODR, LED_PIN);
    delay_ms(100);
  }

}

void button_extern_handler(void) {

    GP_REG_TGB(GPIOB->ODR, EXT_LED_PINB); // toggle LED
    EXTI->PR |= EXTI_PR_PR0_Msk; // unset Pending Request
}


