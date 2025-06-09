# Dev-stm32-f446re

## Build:

Requires arm-none-eabi-gcc for cross-compilation and linking.
1. Clone the repository:
``git clone --recurse-submodules git@github.com:AJQuattropani/Dev-stm32-f446re.git``
2. Switch to local branch associated with the project:
``cd git checkout STM32-DEV``
3. Run `make` in project root directory.
  ||  QUICK DEPLOY: `make flash` to build AND deploy to connected device.
  ||  Note: Run `bear -- make` to with bear installed to update `compile_commands.json`
  ||  CLEAN: To remove build files, run `make clean`

## Deploy:
Requires OpenOCD to deploy.
1. Connect STM32-F446RE NUCLEO to a USB port.
2. In the `/deploy` directory, run `/deploy.sh`
3. The light near the USB-B input should flash red and green, and the program should begin to run.

## TODO:
- Test temperature sensor on board at I2C.
- Implement LED flash with button ISR.

CURRENT PROGRAM IS BASED ON:
https://kleinembedded.com/stm32-without-cubeide-part-3-the-bare-necessities/
with differences resulting from differences in board

# Longerm Goal:
To program this board as an input/output device of an STM32MP157D-DK1, with the latter handling network communication to allow for remote control of the device.
Specifically, the current idea is to create a morse code translator from packets containing text coming from other devices, and converting morse code input from a board button to text.

