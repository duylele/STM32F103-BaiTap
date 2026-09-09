.syntax unified
.cpu cortex-m3
.thumb

.global g_pfnVectors
.global Reset_Handler

/* Dữ liệu định nghĩa vị trí đỉnh Stack và con trỏ Reset */
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
    .word   0x20005000          /* Top of Stack (SRAM 20KB) */
    .word   Reset_Handler       /* Reset Handler */

.section .text.Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* Gọi hàm main trong main.c */
    bl      main
    /* Vòng lặp vô tận nếu main thoát */
Default_Loop:
    b       Default_Loop
.size Reset_Handler, .-Reset_Handler

