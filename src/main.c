#include "main.h"

#include <stdio.h>
#include "gpio.h"
#include "usart.h"
#include "clock.h"

extern volatile uint32_t ticks;
void main(void)
{
  //configure_clock();
  SystemCoreClockUpdate();

  ENABLE_GPIO_A;
  ENABLE_GPIO_B;

  DUMMY_READ_FROM(RCC->AHB1ENR);

  GP_REG_SET(GPIOA->MODER, GP_OUT, GPIO_MODER_MODER5_Pos);
  GP_REG_SET(GPIOA->MODER, GP_OUT, GPIO_MODER_MODER8_Pos);
  GP_REG_SET(GPIOB->MODER, GP_OUT, GPIO_MODER_MODER5_Pos);

  SysTick_Config(100000); // 10,000,000 / 100,000 = 1
  __enable_irq();

  usart_init(USART2);

  while (1)
  {
    printf("[%.3f] Hello, World!\r\n", (float)ticks/1000.0);

    GP_REG_TGB(GPIOA->ODR, LED_PIN);
    GP_REG_TGB(GPIOA->ODR, EXT_LED_PIN);
    GP_REG_TGB(GPIOB->ODR, EXT_LED_PINB);

    delay_ms(50);
    
    GP_REG_TGB(GPIOA->ODR, LED_PIN);
    delay_ms(10);

    GP_REG_TGB(GPIOA->ODR, LED_PIN);
    
    delay_ms(50);

    GP_REG_TGB(GPIOA->ODR, LED_PIN);
    delay_ms(10);
  }

}

