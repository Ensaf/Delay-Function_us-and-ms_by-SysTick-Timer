/*  Author : Ensaf Atef Hassan
**
**  Date   :30/4/2016

*/

#include "stm32f10x.h"
volatile uint32_t msTicks;                            /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;                        /* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE static void Delayms (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}

//uint32_t y=x/1000;
__INLINE static void Delayus (uint32_t y) {
	 y=y/1000;
	uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < y);
}

/*------------------------------------------------------------------------------
  configer LED pins
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Config(void) {

  RCC->APB2ENR |=  1 <<  3;                     /* Enable GPIOB clock          */
  GPIOB->CRH    = 0x33333333;                   /* Configure the GPIO for LEDs */
}

/*------------------------------------------------------------------------------
  Switch on LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_On (uint32_t led) {

  GPIOB->BSRR = (led);                          /* Turn On  LED */
}

/*------------------------------------------------------------------------------
  Switch off LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Off (uint32_t led) {

  GPIOB->BRR  = (led);                          /* Turn Off LED */
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {

  if (SysTick_Config(SystemCoreClock / 1000)) { /* Setup SysTick Timer for 1 msec interrupts  */
    while (1);                                  /* Capture error */
  }

  LED_Config();

  while(1) {
    LED_On (0x100);                             /* Turn on the LED. */
    Delayus (1000000);                                /* delay  100 Msec */
    LED_Off (0x100);                            /* Turn off the LED. */
    Delayus (1000000);                                /* delay  100 Msec */
  }

}
