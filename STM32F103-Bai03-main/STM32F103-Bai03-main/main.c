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
    /* Bật clock AFIO + GPIOA */
    RCC_APB2ENR |= (1 << 0);   // AFIO
    RCC_APB2ENR |= (1 << 2);   // GPIOA

    /* Tắt JTAG + SWD để PA13, PA14, PA15 thành GPIO thông thường */
    AFIO_MAPR &= ~(7 << 24);
    AFIO_MAPR |=  (4 << 24);

    /* PA0 - PA7: Input Pull-up/Pull-down */
    GPIOA_CRL = 0x88888888;

    /* PA8 - PA15: Output Push-Pull 2MHz */
    GPIOA_CRH = 0x22222222;

    /* Kích hoạt Pull-up cho PA0 - PA7 */
    GPIOA_ODR |= 0x00FF;

    while (1)
    {
        // 1. Đọc 8-bit đầu vào từ PA0 đến PA7 (thanh ghi IDR)
        uint8_t input_val = (uint8_t)(GPIOA_IDR & 0x00FF);

        // 2. Đảo dữ liệu (0 thành 1, 1 thành 0) bằng phép toán NOT (~)
        uint8_t inverted_val = ~input_val;

        // 3. Xóa dữ liệu cũ ở PA8-PA15 và ghi giá trị đã đảo vào PA8-PA15
        GPIOA_ODR = (GPIOA_ODR & 0x00FF) | ((uint32_t)inverted_val << 8);
    }
}
