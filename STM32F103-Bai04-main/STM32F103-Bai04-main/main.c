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
    // 1. Bật clock cho GPIOA (bit 2) và GPIOC (bit 4)
    RCC_APB2ENR |= (1 << 2) | (1 << 4);

    // 2. Cấu hình PC13 làm Output Push-Pull 2MHz (CNF13 = 00, MODE13 = 10)
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    // 3. Cấu hình PA0 làm Input Pull-up (CNF0 = 10, MODE0 = 00)
    GPIOA_CRL &= ~(0xF << 0);
    GPIOA_CRL |=  (0x8 << 0);
    GPIOA_ODR |=  (1 << 0); // Kéo Pull-up cho PA0 (mặc định mức HIGH)

    // Ban đầu tắt LED (PC13 tích cực mức LOW, ghi 1 là tắt)
    GPIOC_ODR |= (1 << 13);

    int prev_state = 1;

    while (1) {
        int current_state = (GPIOA_IDR & (1 << 0)) ? 1 : 0;

        // Nhận biết sự kiện nhấn nút (chuyển từ HIGH -> LOW)
        if (prev_state == 1 && current_state == 0) {
            delay(50000); // Debounce (chống dội nút)
            if (!(GPIOA_IDR & (1 << 0))) {
                // Chờ người dùng nhả nút ra hoàn toàn
                while (!(GPIOA_IDR & (1 << 0)));
                delay(50000); // Debounce khi nhả
                
                // Đảo trạng thái LED PC13
                GPIOC_ODR ^= (1 << 13);
            }
        }
        prev_state = current_state;
    }
}
