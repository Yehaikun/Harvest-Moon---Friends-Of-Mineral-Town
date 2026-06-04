.SUFFIXES:

# ==================
# = PROJECT CONFIG =
# ==================

BUILD_NAME := fomt

INCLUDE_DIRS := \
  tools/agbcc/include \
  tools/libagbc++ \
  tools/libsix/include

SRC_DIR = src
ASM_DIR = asm
DATA_ASM_DIR = asm/data
BUILD_DIR = build

# ====================
# = TOOL DEFINITIONS =
# ====================

TOOLCHAIN ?= $(DEVKITARM)

ifneq (,$(TOOLCHAIN))
  export PATH := $(TOOLCHAIN)/bin:$(PATH)
endif

PREFIX := arm-none-eabi-

export OBJCOPY := $(PREFIX)objcopy
export AS := $(PREFIX)as
export CPP := $(PREFIX)cpp
export LD := $(PREFIX)ld
export STRIP := $(PREFIX)strip

ifeq ($(OS),Windows_NT)
  EXE := .exe
else
  EXE :=
endif

CC1      := tools/agbcc/bin/agbcc$(EXE)
CC1PLUS  := tools/agbcc/bin/agbcp$(EXE)

OLD_CC1  := tools/agbcc/bin/old_agbcc$(EXE)

MARY ?= ../stanhash_mary/target/release/mary
MARY_LIB := mary_scripts/lib_fomt.txt

SCRIPT_PATCHES := 167:scripts/script_167.mary
SCRIPT_PATCH_SOURCES := scripts/script_167.mary
WARP_INDEX := docs/generated/warp_index.tsv
SCRIPT_XREF_INDEX := docs/generated/script_xref_index.tsv
WARP_TRIGGER_CANDIDATES := docs/generated/warp_trigger_candidates.tsv
ROM_WARP_REF_INDEX := docs/generated/rom_warp_ref_index.tsv
SCRIPT_TABLE_080F1FC0 := docs/generated/script_table_080F1FC0.tsv

# ================
# = BUILD CONFIG =
# ================

INCFLAGS     := $(foreach dir, $(INCLUDE_DIRS), -I "$(dir)")

CPPFLAGS := $(INCFLAGS) -iquote . -iquote include -Wno-trigraphs -fno-exceptions
CFLAGS   := -g -mthumb-interwork -Wimplicit -Wparentheses -Werror -O2 -fhex-asm
CXXFLAGS := -quiet -fno-exceptions -fno-rtti -fvtable-thunks $(CFLAGS)
ASFLAGS  := $(INCFLAGS) -I . -I include -mcpu=arm7tdmi

ROM := $(BUILD_NAME).gba
ELF := $(ROM:.gba=.elf)
MAP := $(ROM:.gba=.map)
LDS := $(BUILD_NAME).lds

C_SRCS := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/rt/*.c)
C_OBJS := $(C_SRCS:%.c=$(BUILD_DIR)/%.o)

CXX_SRCS := $(wildcard $(SRC_DIR)/*.cc $(SRC_DIR)/rt/*.cc)
CXX_OBJS := $(CXX_SRCS:%.cc=$(BUILD_DIR)/%.o)

ASM_SRCS := $(wildcard $(SRC_DIR)/*.s $(ASM_DIR)/*.s)
ASM_OBJS := $(ASM_SRCS:%.s=$(BUILD_DIR)/%.o)

DATA_ASM_SRCS := $(wildcard $(DATA_ASM_DIR)/*.s)
DATA_ASM_OBJS := $(DATA_ASM_SRCS:%.s=$(BUILD_DIR)/%.o)

ALL_OBJS := $(C_OBJS) $(CXX_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS)
ALL_DEPS := $(ALL_OBJS:%.o=%.d)

SUBDIRS := $(sort $(dir $(ALL_OBJS)))
$(shell mkdir -p $(SUBDIRS))

# ===========
# = RECIPES =
# ===========

all: $(ROM)

.PHONY: all

check-mary:
	@test -x "$(MARY)" || { echo "missing mary compiler: $(MARY)"; echo "build it with: cd ../stanhash_mary && cargo build --release"; exit 1; }
	@$(MARY) compile --help >/dev/null
	@$(CPP) -P scripts/script_1017.mary | $(MARY) compile -o /tmp/fomt_check_mary_script_1017.c
	@test -s /tmp/fomt_check_mary_script_1017.c
	@echo "mary OK: $(MARY)"

.PHONY: check-mary

compare: $(ROM)
	sha1sum -c $(BUILD_NAME).sha1

.PHONY: compare

# ROM from ELF
%.gba: %.elf $(SCRIPT_PATCH_SOURCES) tools/patch_script.py tools/script_slot.py
	$(OBJCOPY) -O binary $< $@
	@for patch in $(SCRIPT_PATCHES); do \
		id=$${patch%%:*}; \
		src=$${patch#*:}; \
		python3 tools/patch_script.py --script-id $$id --source $$src --rom-in $@ --rom-out $@ --mary "$(MARY)"; \
	done

check-script-patches: $(ROM)
	@$(MARY) decompile $(ROM) $(MARY_LIB) --script-id 167 -o /tmp/fomt_script_167_check.mary
	@grep -q "Proc016(1, 24, 280)" /tmp/fomt_script_167_check.mary
	@grep -q "SetEntityPosition(0, 24, 280, 3)" /tmp/fomt_script_167_check.mary
	@echo "script patch OK: script_167 chicken coop -> beach"

.PHONY: check-script-patches

$(WARP_INDEX): tools/scan_warps.py include/decomp/entities.hh $(wildcard scripts/script_*.mary)
	python3 tools/scan_warps.py --output $@

warp-index: $(WARP_INDEX)

.PHONY: warp-index

$(SCRIPT_XREF_INDEX) $(WARP_TRIGGER_CANDIDATES): tools/scan_script_xrefs.py $(WARP_INDEX) $(wildcard scripts/script_*.mary)
	python3 tools/scan_script_xrefs.py --output $(SCRIPT_XREF_INDEX) --warp-output $(WARP_TRIGGER_CANDIDATES)

script-xref-index: $(SCRIPT_XREF_INDEX) $(WARP_TRIGGER_CANDIDATES)

.PHONY: script-xref-index

$(ROM_WARP_REF_INDEX): tools/scan_rom_script_refs.py tools/script_slot.py $(WARP_INDEX) baserom.gba $(wildcard asm/data/*.s)
	python3 tools/scan_rom_script_refs.py --output $@

rom-warp-ref-index: $(ROM_WARP_REF_INDEX)

.PHONY: rom-warp-ref-index

$(SCRIPT_TABLE_080F1FC0): tools/decode_script_table.py baserom.gba
	python3 tools/decode_script_table.py --offset 0xF1FC0 --size 0x84C --output $@

script-table-index: $(SCRIPT_TABLE_080F1FC0)

.PHONY: script-table-index

# ELF
$(ELF): $(ALL_OBJS) $(LDS)
	@echo "LD $(LDS) $(ALL_OBJS:$(BUILD_DIR)/%=%)"
	@cd $(BUILD_DIR) && $(LD) -T ../$(LDS) -Map ../$(MAP) -L../tools/agbcc/lib -lgcc -lc $(ALL_OBJS:$(BUILD_DIR)/%=%) -o ../$@
	@$(STRIP) -N .gcc2_compiled. $(ELF)

# C dependency file
$(BUILD_DIR)/%.d: %.c
	@$(CPP) $(CPPFLAGS) $< -o $@ -MM -MG -MT $@ -MT $(BUILD_DIR)/$*.o

# C object
$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)/%.d
	@echo "CC $<"
	@$(CPP) $(CPPFLAGS) $< | $(CC1) $(CFLAGS) -o $(BUILD_DIR)/$*.s
	@tools/scripts/align_sections.sh $(BUILD_DIR)/$*.s
	@$(AS) $(ASFLAGS) $(BUILD_DIR)/$*.s -o $@ 

# C++ dependency file
$(BUILD_DIR)/%.d: %.cc
	@$(CPP) $(CPPFLAGS) $< -o $@ -MM -MG -MT $@ -MT $(BUILD_DIR)/$*.o

# C++ object
$(BUILD_DIR)/%.o: %.cc $(BUILD_DIR)/%.d
	@echo "CP $<"
	@$(CPP) $(CPPFLAGS) $< | ($(CC1PLUS) $(CXXFLAGS) -o $(BUILD_DIR)/$*.s || false)
	@tools/scripts/align_sections.sh $(BUILD_DIR)/$*.s
	@$(AS) $(ASFLAGS) $(BUILD_DIR)/$*.s -o $@

# ASM dependency file (dummy, generated with the object)
$(BUILD_DIR)/%.d: $(BUILD_DIR)/%.o
	@touch $@

# ASM object
$(BUILD_DIR)/%.o: %.s
	@echo "AS $<"
	@$(AS) $(ASFLAGS) $< -o $@ --MD $(BUILD_DIR)/$*.d

# overrides for matching
$(BUILD_DIR)/src/m4a.o: CC1 := $(OLD_CC1)

clean:
	@echo "RM $(ROM) $(ELF) $(MAP) $(BUILD_DIR)"
	@rm -f $(ROM) $(ELF) $(MAP) 
	@rm -r $(BUILD_DIR)/

.PHONY: clean

ifneq (clean,$(MAKECMDGOALS))
-include $(ALL_DEPS)
.PRECIOUS: $(BUILD_DIR)/%.d
endif

# -------------------------------------------------------------------
# Phase 4: Pre-build validation & data integrity checks
# -------------------------------------------------------------------

PRE_BUILD_CHECKS := tools/pre_build_checks.py

# Validate patched script sizes before building
pre-build-check: $(SCRIPT_PATCH_SOURCES) baserom.gba $(PRE_BUILD_CHECKS)
	python3 $(PRE_BUILD_CHECKS) --rom baserom.gba --patches "$(SCRIPT_PATCHES)"

.PHONY: pre-build-check

# Verify all generated index files exist
check-indexes: $(WARP_INDEX) $(SCRIPT_XREF_INDEX) $(WARP_TRIGGER_CANDIDATES) $(ROM_WARP_REF_INDEX) $(SCRIPT_TABLE_080F1FC0)
	@echo "All index files OK"

.PHONY: check-indexes

# Run all Phase 4 checks
check-all: check-mary pre-build-check check-script-patches check-indexes
	@echo "All checks passed"

.PHONY: check-all
