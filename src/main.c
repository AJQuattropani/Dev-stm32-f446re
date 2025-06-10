#include "main.h"

extern volatile uint32_t ticks;
void main(void)
{
  //configure_clock();
  SystemCoreClockUpdate();

  RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos); // sets the bit to enable GPIOA

  RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOBEN_Pos); // sets the bit to enable GPIOB
  volatile uint32_t dummy;
  dummy = RCC->AHB1ENR;
  dummy = RCC->AHB1ENR;

  // sets GPIOA to turn pin 5, pin 8 to output
  GPIOA->MODER |= (0b01 << GPIO_MODER_MODER5_Pos);
  GPIOA->MODER |= (0b01 << GPIO_MODER_MODER8_Pos);

  GPIOB->MODER |= (0b01 << GPIO_MODER_MODER5_Pos);

  SysTick_Config(100000); // 10,000,000 / 100,000 = 1
  __enable_irq();

  usart_init(USART2);

  while (1)
  {
    printf("[%.3f] Hello, World!\r\n", (float)ticks/1000.0);

    GPIOA->ODR ^= (1 << EXT_LED_PIN);
    GPIOA->ODR ^= (1 << LED_PIN); // flip bit 5 of the GPIOA out data register

    GPIOB->ODR ^= (1 << EXT_LED_PINB); // flip bit 5 of the GPIOB out data register

    //for (uint32_t i = 0; i < 1000000/2; i++); // busy wait
    delay_ms(50);
    
    GPIOA->ODR ^= (1 << LED_PIN); // flip bit 5 of the GPIOA out data register
    //for (uint32_t i = 0; i < 1000000/2; i++); // busy wait
    delay_ms(10);

    GPIOA->ODR ^= (1 << LED_PIN); // flip bit 5 of the GPIOA out data register
    
    //for (uint32_t i = 0; i < 1000000/8; i++); // busy wait
    delay_ms(50);

    GPIOA->ODR ^= (1 << LED_PIN); // flip bit 5 of the GPIOA out data register
    //for (uint32_t i = 0; i < 1000000/8; i++); // busy wait
    delay_ms(10);
  }

}

