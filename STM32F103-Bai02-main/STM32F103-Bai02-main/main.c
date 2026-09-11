#include <stdint.h>


#define RCC_BASE        0x40021000
#define RCC_APB2ENR     (*((volatile uint32_t *)(RCC_BASE + 0x18)))


#define GPIOA_BASE      0x40010800
#define GPIOA_CRL       (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR       (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))


void delay_ms(volatile uint32_t count) {
    for (volatile uint32_t i = 0; i < count * 1000; i++) {
        __asm__("nop");
    }
}

int main(void) {
   
    RCC_APB2ENR |= (1 << 2);

   
    GPIOA_CRL = 0x22222222;

    while (1) {
  
        for (int i = 0; i < 8; i++) {
            GPIOA_ODR = (1 << i);
            delay_ms(200);
        }

       
        for (int i = 6; i > 0; i--) {
            GPIOA_ODR = (1 << i);
            delay_ms(200);
        }
    }

    return 0;
}
