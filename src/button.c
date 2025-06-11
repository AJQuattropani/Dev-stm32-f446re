#include "button.h"

void user_button_init() {
  ENABLE_IRQ_CLOCK;
  // set exti line 13 to read from PC13
  SYSCFG->EXTICR[3] &= ~(SYSCFG_EXTICR4_EXTI13_Msk); // wipe bits responsible for EXTI13
  SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR4_EXTI13_PC); // set EXTI13 to use PC (13)

  EXTI->IMR |= EXTI_IMR_MR13_Msk; // enable exti 13
  EXTI->RTSR |= EXTI_RTSR_TR13_Msk; // trigger on rising edge.
  EXTI->FTSR |= EXTI_FTSR_TR13_Msk; // trigger on falling edge
  


}


