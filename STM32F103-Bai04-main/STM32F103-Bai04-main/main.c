#define RCC_APB2ENR  (*((volatile unsigned int *)0x40021018))
#define GPIOA_CRL    (*((volatile unsigned int *)0x40010800))
#define GPIOA_IDR    (*((volatile unsigned int *)0x40010808))
#define GPIOA_ODR    (*((volatile unsigned int *)0x4001080C))

#define GPIOC_CRH    (*((volatile unsigned int *)0x40011004))
#define GPIOC_ODR    (*((volatile unsigned int *)0x4001100C))

void delay(volatile unsigned int time) {
    while (time--);
}

int main(void) {

    RCC_APB2ENR |= (1 << 2) | (1 << 4);


    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

   
    GPIOA_CRL &= ~(0xF << 0);
    GPIOA_CRL |=  (0x8 << 0);
    GPIOA_ODR |=  (1 << 0); // Kéo Pull-up cho PA0 (mặc định mức HIGH)

 
    GPIOC_ODR |= (1 << 13);

    int prev_state = 1;

    while (1) {
        int current_state = (GPIOA_IDR & (1 << 0)) ? 1 : 0;

        if (prev_state == 1 && current_state == 0) {
            delay(50000); 
            if (!(GPIOA_IDR & (1 << 0))) {
              
                while (!(GPIOA_IDR & (1 << 0)));
                delay(50000); 
                
       
                GPIOC_ODR ^= (1 << 13);
            }
        }
        prev_state = current_state;
    }
}
