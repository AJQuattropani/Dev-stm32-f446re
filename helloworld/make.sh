arm-none-eabi-gcc main.c startup.c -T link.ld -o stm32mc_img.elf -mcpu=cortex-m4 -mthumb -nostdlib
