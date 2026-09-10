# BÀI TẬP 2-STM32F103

## Yêu cầu bài tập

- **Vi điều khiển:** STM32F103C8T6 (Cortex-M3).
- **Môi trường:** Linux (Ubuntu), biên dịch bằng `arm-none-eabi-gcc`, nạp bằng `st-flash`.
- **Yêu cầu:**
  - Lập trình cấu hình thanh ghi thuần (không dùng thư viện HAL/STD).
  - Cấu hình 8 chân từ PA0-PA7 ở chế độ Output.
  - Viết chương trình điều khiển cho 01 LED sáng thực hiện chạy từ trái sang phải. Khi đến hết bên phải thì đảo chiều chạy từ phải sang trái.
  - Lặp lại chu trình này.

## Các file

- `main.c`: Mã nguồn chính cấu hình các thanh ghi RCC, GPIOA và thuật toán dịch bit điều khiển LED đảo chiều.
- `startup.s`: File khởi tạo Vector Table và Reset Handler.
- `stm32f103.ld`: Linker script định nghĩa vùng nhớ FLASH (64KB) và RAM (20KB).
- `Makefile`: Kịch bản tự động biên dịch và nạp code xuống bo mạch.

## Biên dịch và Nạp code

```bash
make clean
make
make flash
