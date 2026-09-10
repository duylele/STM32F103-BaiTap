# Bài tập 03: Đọc dữ liệu PA0-PA7 và xuất đảo dữ liệu ra PA8-PA15 (Register-level)

## Yêu cầu bài tập

- Vi điều khiển: STM32F103C8T6 (Cortex-M3).
- Môi trường: Linux (Ubuntu), biên dịch bằng `arm-none-eabi-gcc`, nạp bằng `st-flash`.
- Yêu cầu:
  - Lập trình cấu hình thanh ghi thuần (không dùng thư viện HAL/STD).
  - Cấu hình chân PA0-PA7 làm Input đọc trạng thái Nút nhấn.
  - Cấu hình chân PA8-PA15 làm Output điều khiển LED.
  - Đọc dữ liệu từ PA0-PA7 sau đó đảo dữ liệu (từ 0 thành 1, từ 1 thành 0), rồi ghi vào LED tại PA8-PA15.

## Cấu trúc dự án

- `main.c` : Mã nguồn chính cấu hình các thanh ghi RCC, GPIOA và thuật toán đọc đảo dữ liệu nút nhấn xuất ra LED.
- `startup.s` : File khởi tạo Vector Table và Reset Handler.
- `stm32f103.ld` : Linker script định nghĩa vùng nhớ FLASH (64KB) và RAM (20KB).
- `Makefile` : Kịch bản tự động biên dịch và nạp code xuống bo mạch.

## Biên dịch và Nạp code

```bash
make clean
make
make flash
