TOOLCHAIN := $(DEVKITARM)
ifneq (,$(wildcard $(TOOLCHAIN)/base_tools))
include $(TOOLCHAIN)/base_tools
else
export PATH := $(TOOLCHAIN)/bin:$(PATH)
PREFIX := arm-none-eabi-
OBJCOPY := $(PREFIX)objcopy
export AS := $(PREFIX)as
endif

export CPP := $(PREFIX)cpp
export LD := $(PREFIX)ld

ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
endif

#### Tools ####
SHELL     := /bin/bash -o pipefail
SHA1    := $(shell { command -v sha1sum || command -v shasum; } 2>/dev/null) -c
SCANINC := tools/scaninc/scaninc$(EXE)
FIX     := tools/gbafix/gbafix$(EXE)

#### Target Info ####
BUILD_NAME := hm4

TITLE       := HARVESTMOGBA
GAME_CODE   := A4NE
MAKER_CODE  := E9
REVISION    := 0


#### Build Files ####

CC1      := tools/agbcc/bin/agbcc$(EXE)
CC1_OLD  := tools/agbcc/bin/old_agbcc$(EXE)

CPPFLAGS := -I tools/agbcc/include -I tools/agbcc -iquote include -Wno-trigraphs
CFLAGS   := -mthumb-interwork -Wimplicit -Wparentheses -Werror -O2 -fhex-asm
ASFLAGS  := -mcpu=arm7tdmi

C_SUBDIR = src
ASM_SUBDIR = asm
DATA_ASM_SUBDIR = data
BUILD_DIR = build


C_BUILDDIR = $(BUILD_DIR)/$(C_SUBDIR)
ASM_BUILDDIR = $(BUILD_DIR)/$(ASM_SUBDIR)
DATA_ASM_BUILDDIR = $(BUILD_DIR)/$(DATA_ASM_SUBDIR)


#### Files/Directories ####

ROM       := $(BUILD_NAME).gba
ELF       := $(ROM:.gba=.elf)
MAP       := $(ROM:%.gba=%.map)
LDSCRIPT  := ldscript.txt

C_SRCS := $(wildcard $(C_SUBDIR)/*.c $(C_SUBDIR)/*/*.c $(C_SUBDIR)/*/*/*.c)
C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(C_SRCS))

ASM_SRCS := $(wildcard $(ASM_SUBDIR)/*.s)
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(ASM_BUILDDIR)/%.o,$(ASM_SRCS))

DATA_ASM_SRCS := $(wildcard $(DATA_ASM_SUBDIR)/*.s)
DATA_ASM_OBJS := $(patsubst $(DATA_ASM_SUBDIR)/%.s,$(DATA_ASM_BUILDDIR)/%.o,$(DATA_ASM_SRCS))

ALL_OBJS := $(C_OBJS) $(C_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS)

SUBDIRS := $(sort $(dir $(ALL_OBJS)))


#### Recipes ####
.PHONY: rom clean compare tools

rom: tools $(ROM)

clean:
	rm -f $(ROM) $(ELF) $(MAP) 
	rm -r $(BUILD_DIR)/

compare: rom
	$(SHA1) $(BUILD_NAME).sha1

tools:
	make -C tools/gbafix
	make -C tools/scaninc

silent:
	@:


$(shell mkdir -p $(SUBDIRS))

$(ROM): $(ELF)
	$(OBJCOPY) -O binary --pad-to 0x4800000 $< $@
	$(FIX) $@ -p -t"$(TITLE)" -c$(GAME_CODE) -m$(MAKER_CODE) -r$(REVISION) --silent

$(ELF): $(ALL_OBJS) $(LDSCRIPT)
	cd $(BUILD_DIR) && $(LD) -T ../$(LDSCRIPT) -Map ../$(MAP) -o ../$@

$(C_BUILDDIR)/%.o: $(C_SUBDIR)/%.c
	$(CPP) $(CPPFLAGS) $< -o $(C_BUILDDIR)/$*.i
	$(CC1) $(CFLAGS) $(C_BUILDDIR)/$*.i -o $(C_BUILDDIR)/$*.s
	echo -e ".text\n\t.align\t2, 0\n" >> $(C_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) $(C_BUILDDIR)/$*.s -o $@ 

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

$(DATA_ASM_BUILDDIR)/%.o: $(DATA_ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

%.s: ;
%.png: ;
%.pal: ;
%.aif: ;

%.1bpp: %.png  ; $(GFX) $< $@
%.4bpp: %.png  ; $(GFX) $< $@
%.8bpp: %.png  ; $(GFX) $< $@
%.gbapal: %.pal ; $(GFX) $< $@
%.gbapal: %.png ; $(GFX) $< $@
%.lz: % ; $(GFX) $< $@
%.rl: % ; $(GFX) $< $@
