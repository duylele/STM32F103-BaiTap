CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -Wall -ffreestanding -nostdlib
LDFLAGS = -T stm32f103.ld -nostdlib -Wl,--gc-sections

all: blink.elf blink.bin

blink.elf: main.o startup.o
	$(CC) $(CFLAGS) $(LDFLAGS) main.o startup.o -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $@

startup.o: startup.s
	$(CC) $(CFLAGS) -c startup.s -o $@

blink.bin: blink.elf
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -f *.o *.elf *.bin

flash: blink.bin
	st-flash write blink.bin 0x8000000

.PHONY: all clean flash
