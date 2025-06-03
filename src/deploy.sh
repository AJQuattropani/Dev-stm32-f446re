arm-none-eabi-gcc main.c startup.c -T link.ld -o stm32mc_img.elf -mcpu=cortex-m4 -mthumb -nostdlib
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program stm32mc_img.elf verify reset exit"
