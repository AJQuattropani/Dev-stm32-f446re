CC=arm-none-eabi-gcc

DEPLOY := deploy.sh

OUTDIR := ./deploy
SRCDIR := ./src
OBJDIR := ./intermediate

ELF := $(OUTDIR)/stm32mc_img.elf
DEPOUT := $(OUTDIR)/$(DEPLOY)

SRC := $(wildcard $(SRCDIR)/*.c)
DEPSRC := $(SRCDIR)/$(DEPLOY)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

VENDOR := ./vendor
CMSIS := $(VENDOR)/CMSIS
STM32F4 := $(CMSIS)/Device/ST/STM32F4

SYS_FILE := system_stm32f4xx
STM32F4_SYS := $(STM32F4)/Source/Templates/$(SYS_FILE).c

ARM_INC := $(CMSIS)/CMSIS/Core/Include
STM32F4_INC := $(STM32F4)/Include/

ARM_NONE_STDLIB := /usr/arm-none-eabi/include/

CFLAGS := -mcpu=cortex-m4 \
	  -mthumb \
	  --specs=nano.specs -Wall \
	  -Wno-unused-but-set-variable \
	  -Wno-main \
	  -Wno-main-return-type \
	  --save-temps 

CPPFLAGS := -DSTM32F446xx \
	    -I$(ARM_INC) \
	    -I$(STM32F4_INC) \
	    -I$(ARM_NONE_STDLIB) \


LINKER_SCRIPT := $(SRCDIR)/link.ld
LDFLAGS := -T $(LINKER_SCRIPT) -u _printf_float 

.PHONY: all clean
all: $(ELF) $(DEPOUT)

$(DEPOUT): $(DEPSRC)
	cp -u $(DEPSRC) $(DEPOUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/$(SYS_FILE).o: $(STM32F4_SYS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(OBJDIR)/$(SYS_FILE).o

$(ELF): $(OBJ) $(OBJDIR)/$(SYS_FILE).o | $(OUTDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

PROGRAMMER := openocd
PROGRAMMER_FLAGS := -f interface/stlink-v2-1.cfg -f target/stm32f4x.cfg

flash: $(ELF)
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $(ELF) verify reset exit"

clean:
	$(RM) -rv $(OUTDIR) $(OBJDIR)

