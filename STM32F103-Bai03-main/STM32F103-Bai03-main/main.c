#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)

#define AFIO_MAPR   (*(volatile uint32_t *)0x40010004)

#define GPIOA_CRL   (*(volatile uint32_t *)0x40010800)
#define GPIOA_CRH   (*(volatile uint32_t *)0x40010804)
#define GPIOA_IDR   (*(volatile uint32_t *)0x40010808)
#define GPIOA_ODR   (*(volatile uint32_t *)0x4001080C)

void SysTick_Handler(void) 
{
}

int main(void)
{
  
    RCC_APB2ENR |= (1 << 0);   // AFIO
    RCC_APB2ENR |= (1 << 2);   // GPIOA

    AFIO_MAPR &= ~(7 << 24);
    AFIO_MAPR |=  (4 << 24);


    GPIOA_CRL = 0x88888888;


    GPIOA_CRH = 0x22222222;


    GPIOA_ODR |= 0x00FF;

    while (1)
    {
        uint8_t input_val = (uint8_t)(GPIOA_IDR & 0x00FF);


        uint8_t inverted_val = ~input_val;

   
        GPIOA_ODR = (GPIOA_ODR & 0x00FF) | ((uint32_t)inverted_val << 8);
    }
}
