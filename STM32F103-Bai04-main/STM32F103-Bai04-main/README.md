# BÀI TẬP 4-STM32F103
## Yêu cầu bài tập
- **Vi điều khiển:** STM32F103C8T6 (Cortex-M3).
- **Môi trường:** Linux (Ubuntu), biên dịch bằng `arm-none-eabi-gcc`, nạp bằng `st-flash`.
- **Yêu cầu:** 
  - Lập trình cấu hình thanh ghi thuần (không dùng thư viện HAL/STD).
  - Cấu hình chân **PA0** làm Input đọc trạng thái Nút nhấn.
  - Cấu hình chân **PC13** làm Output điều khiển LED tích hợp.
  - Khi nhấn rồi nhả nút (tương tác điều khiển nút nguồn), LED đảo trạng thái (ON/OFF). Khi nhả nút, trạng thái LED được giữ nguyên.
## Cấu trúc dự án
- `main.c`: Mã nguồn chính cấu hình các thanh ghi RCC, GPIOA, GPIOC và thuật toán debounce chống dội nút.
- `startup.s`: File khởi tạo Vector Table và Reset Handler.
- `stm32f103.ld`: Linker script định nghĩa vùng nhớ FLASH (64KB) và RAM (20KB).
- `Makefile`: Kịch bản tự động biên dịch và nạp code xuống bo mạch.
## Biên dịch và Nạp code
```bash
make clean
make
make flash
