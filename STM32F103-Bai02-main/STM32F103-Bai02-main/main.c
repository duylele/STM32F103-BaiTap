#include <stdint.h>

// Địa chỉ thanh ghi RCC
#define RCC_BASE        0x40021000
#define RCC_APB2ENR     (*((volatile uint32_t *)(RCC_BASE + 0x18)))

// Địa chỉ thanh ghi GPIOA
#define GPIOA_BASE      0x40010800
#define GPIOA_CRL       (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR       (*((volatile uint32_t *)(GPIOA_BASE + 0x0C)))

// Hàm delay đơn giản
void delay_ms(volatile uint32_t count) {
    for (volatile uint32_t i = 0; i < count * 1000; i++) {
        __asm__("nop");
    }
}

int main(void) {
    // 1. Bật clock cho GPIOA (Bit 2 trong RCC_APB2ENR)
    RCC_APB2ENR |= (1 << 2);

    // 2. Cấu hình PA0 -> PA7 làm Output Push-Pull 2MHz (CRL = 0x22222222)
    GPIOA_CRL = 0x22222222;

    while (1) {
        // Chạy từ trái sang phải (PA0 -> PA7)
        for (int i = 0; i < 8; i++) {
            GPIOA_ODR = (1 << i);
            delay_ms(200);
        }

        // Đảo chiều chạy từ phải sang trái (PA6 xuống PA1)
        for (int i = 6; i > 0; i--) {
            GPIOA_ODR = (1 << i);
            delay_ms(200);
        }
    }

    return 0;
}
