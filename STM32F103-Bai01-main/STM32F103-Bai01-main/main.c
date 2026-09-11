
#include <stdint.h>



#define RCC_BASE        0x40021000UL
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))



#define GPIOC_BASE      0x40011000UL

#define GPIOC_CRH       (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))


#define SYST_CSR        (*(volatile uint32_t *)0xE000E010UL)
#define SYST_RVR        (*(volatile uint32_t *)0xE000E014UL)
#define SYST_CVR        (*(volatile uint32_t *)0xE000E018UL)



#define BLINK_DELAY_MS  1000

volatile uint32_t ms_tick = 0;




void SysTick_Handler(void)
{
    ms_tick++;
}




void delay_ms(uint32_t ms)
{
    uint32_t start = ms_tick;

    while ((ms_tick - start) < ms)
    {
       
    }
}



void GPIOC_Init(void)
{
   
    RCC_APB2ENR |= (1 << 4);



    GPIOC_CRH &= ~(0xFUL << 20);
    GPIOC_CRH |=  (0x2UL << 20);


  
    GPIOC_ODR |= (1 << 13);
}




void SysTick_Init(void)
{


    SYST_RVR = 8000 - 1;

    SYST_CVR = 0;




    SYST_CSR = (1 << 2) |
               (1 << 1) |
               (1 << 0);
}



int main(void)
{
    GPIOC_Init();

    SysTick_Init();

    while (1)
    {
        delay_ms(BLINK_DELAY_MS);


        GPIOC_ODR ^= (1 << 13);
    }

    return 0;
}
