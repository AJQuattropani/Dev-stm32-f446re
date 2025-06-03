require("lspconfig").clangd.setup({
  cmd = {
  "/usr/bin/gcc",
  "-m32",
  --"--target=arm-arm-none-eabi",
  --"/usr/bin/arm-none-eabi-gcc",
  "-v",
  --"-T link.ld",
  --"-o stm32mc_img.elf",
  --"-mcpu=cortex-m4",
  --"-mthumb",
  }
})
