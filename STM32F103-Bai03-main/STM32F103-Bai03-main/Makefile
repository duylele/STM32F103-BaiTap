
TARGET   = blink
BUILD_DIR = build


PREFIX   = arm-none-eabi-
CC       = $(PREFIX)gcc
AS       = $(PREFIX)gcc -x assembler-with-cpp
OBJCOPY  = $(PREFIX)objcopy
OBJDUMP  = $(PREFIX)objdump
SZ       = $(PREFIX)size

C_SOURCES = \
main.c

ASM_SOURCES = \
startup.s

# --- CẤU HÌNH BIÊN DỊCH (FLAGS) ---
MCU      = -mcpu=cortex-m3 -mthumb

# C Flags (Tối ưu hóa, cảnh báo, tùy chọn bare-metal)
CFLAGS   = $(MCU) -O0 -Wall -fdata-sections -ffunction-sections -ffreestanding -nostdlib

# Linker Script & Linker Flags
LDSCRIPT = stm32f103.ld
LDFLAGS  = $(MCU) -T$(LDSCRIPT) -nostdlib -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# --- DANH SÁCH FILE OBJECT (.o) ---
OBJECTS  = $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/, $(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# --- CÁC QUY TẮC (RULES) ---

# Target mặc định
all: $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex
	@echo "\n=== KÍCH THƯỚC BỘ NHỚ CỦA CHƯƠNG TRÌNH ==="
	$(SZ) $(BUILD_DIR)/$(TARGET).elf

# Biên dịch file .c sang .o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

# Biên dịch file .s sang .o
$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

# Liên kết (Link) các file .o thành .elf
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

# Chuyển .elf sang .bin
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O binary $< $@

# Chuyển .elf sang .hex
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O ihex $< $@

# Tạo thư mục build nếu chưa có
$(BUILD_DIR):
	mkdir -p $@

# Nạp code bằng ST-Link
flash: $(BUILD_DIR)/$(TARGET).bin
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x08000000

# Xóa các file trung gian
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean flash
