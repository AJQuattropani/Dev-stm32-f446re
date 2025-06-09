#include "usart.h"

void usart_init(USART_TypeDef *usart) {
  /* Enable USART2 clock */
  RCC->APB1ENR |= (1 << RCC_APB1ENR_USART2EN_Pos);
  // do two dummy reads after enabling
  volatile uint32_t dummy;
  dummy = RCC->APB1ENR;
  dummy = RCC->APB1ENR;

  /* Enable GPIOA clock*/
  RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN);
  // do dummy reads after enabling periph clock

  /* Set pa2 and pa3 to alt func*/
  GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
  GPIOA->MODER |= (0b10 << GPIO_MODER_MODE2_Pos) | (0b10 << GPIO_MODER_MODE3_Pos);

  // USART2 is Alternate Function 7
  // table 10 page 41 of datasheet
  GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3);
  GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos);

  // default config: 1 start bit, 8 data bits, no stop bits, no parity bit
  // USART2->BRR = 434; // 115200 baud @ 50 MHz APB1 clock and 16x oversampling
  // DIV = 50 MHz / (16 * 115200) * 2^4
  // 24.4.4 reference manual
  const int baud_rate = 115200;
  const int sample_rate = 16;
  const int clock_speed_mhz = 16; //50; // MODIFY THIS.
  const int clock_speed_hz = clock_speed_mhz * 1000000;
  USART2->BRR = ((clock_speed_hz) / (sample_rate * baud_rate)) * (1 << 4);
  USART2->CR1 |= USART_CR1_UE | USART_CR1_TE; // USART enable and transmitter enable

}

void usart_write(USART_TypeDef *usart, char c) {
  usart->DR = c; // write to data register
  while (!(usart->SR & USART_SR_TC))
    ; // transmission complete flag in stat register
  // check DMA
}
