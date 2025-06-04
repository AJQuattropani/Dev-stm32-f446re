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

CFLAGS := -mcpu=cortex-m4 -mthumb -Wall -nostdlib -Wno-unused-but-set-variable -Wno-main
LDFLAGS := -T $(SRCDIR)/link.ld -nostdlib

.PHONY: all clean
all: $(ELF) $(DEPOUT)

$(DEPOUT): $(DEPSRC)
	cp -u $(DEPSRC) $(DEPOUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJ) | $(OUTDIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) -rv $(OUTDIR) $(OBJDIR)

