#include "main.h"

#include <stdio.h>
#include "gpio.h"
#include "usart.h"
#include "clock.h"
#include "button.h"

extern volatile uint32_t ticks;
void main(void)
{
  ENABLE_GPIO_A;
  ENABLE_GPIO_B;
  ENABLE_GPIO_C;
  DUMMY_READ_FROM(RCC->AHB1ENR);

  GP_REG_SET(GPIOA->MODER, GP_OUT, GPIO_MODER_MODER5_Pos);
  GP_REG_SET(GPIOA->MODER, GP_OUT, GPIO_MODER_MODER8_Pos);
  GP_REG_SET(GPIOB->MODER, GP_OUT, GPIO_MODER_MODER5_Pos);
  // button at PC13 enabled as input
  GP_REG_SET(GPIOC->MODER, GP_IN, GPIO_MODER_MODER13_Pos);

  user_button_init();

  usart_init(USART2);

  configure_clock();
  SystemCoreClockUpdate();
  SysTick_Config(100000); // 10,000,000 / 100,000 = 1
  NVIC_EnableIRQ(EXTI15_10_IRQn); // enable callback for button EXTI13 PC13

  __enable_irq();

  while (1)
  {
    //EXTI->SWIER |= EXTI_SWIER_SWIER13_Msk; // blink LED by calling interrupt via software

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


