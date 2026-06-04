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

BASEROM := baserom.gba
BASEROM_SHA1 := a2fc3574f0a65a4fcf7682fb274b9d7eebdef963

MARY ?= ../stanhash_mary/target/release/mary
MARY_LIB := mary_scripts/lib_fomt.txt

SCRIPT_PATCHES_STABLE := \
  167:scripts/script_167.mary

SCRIPT_PATCHES_EXPERIMENTAL := \
  1011:scripts/script_1011.mary \
  1005:scripts/script_1005.mary \
  1018:scripts/script_1018.mary \
  1002:scripts/script_1002.mary \
  1003:scripts/script_1003.mary \
  1014:scripts/script_1014.mary \
  1016:scripts/script_1016.mary \
  1027:scripts/script_1027.mary

SCRIPT_PATCHES := $(SCRIPT_PATCHES_STABLE)
SCRIPT_PATCH_SOURCES := \
  $(foreach p,$(SCRIPT_PATCHES),$(word 2,$(subst :, ,$(p))))
WARP_INDEX := docs/generated/warp_index.tsv
SCRIPT_XREF_INDEX := docs/generated/script_xref_index.tsv
WARP_TRIGGER_CANDIDATES := docs/generated/warp_trigger_candidates.tsv
ROM_WARP_REF_INDEX := docs/generated/rom_warp_ref_index.tsv
SCRIPT_TABLE_080F1FC0 := docs/generated/script_table_080F1FC0.tsv
MAP_DATA_TABLE := docs/generated/map_data_table.tsv
MAP_MASTER_INDEX := docs/generated/map_master_index.tsv
COLLISION_CANDIDATE_DIR := docs/generated/collision

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

check-baserom:
	@test -f "$(BASEROM)" || { echo "❌ $(BASEROM) not found — place the original ROM in the root directory"; exit 1; }
	@printf '%s  %s\n' "$(BASEROM_SHA1)" "$(BASEROM)" | sha1sum -c - || { echo "❌ $(BASEROM) SHA1 mismatch — expected $(BASEROM_SHA1)"; exit 1; }
	@echo "✅ baserom OK: $(BASEROM) ($(BASEROM_SHA1))"

.PHONY: check-baserom

compare: $(ROM)
	sha1sum -c $(BUILD_NAME).sha1

.PHONY: compare

# ROM from ELF
%.gba: %.elf $(SCRIPT_PATCH_SOURCES) tools/patch_script.py tools/script_slot.py
	$(OBJCOPY) -O binary $< $@
	@set -e; for patch in $(SCRIPT_PATCHES); do \
		id=$${patch%%:*}; \
		src=$${patch#*:}; \
		python3 tools/patch_script.py --script-id $$id --source $$src --rom-in $@ --rom-out $@ --mary "$(MARY)"; \
	done

check-script-patches: $(ROM)
	@offset=$$(python3 tools/script_slot.py $(ROM) --map $(MAP) --script-id 167 --field rom_offset); \
	$(MARY) decompile $(ROM) $(MARY_LIB) --offset $$offset -o /tmp/fomt_script_167_check.mary
	@grep -q "Proc016(8, 236, 411)" /tmp/fomt_script_167_check.mary
	@grep -q "SetEntityPosition(0, 236, 411, 1)" /tmp/fomt_script_167_check.mary
	@echo "script patch OK: script_167 chicken coop -> goddess pond"

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

$(MAP_DATA_TABLE): tools/decode_map_data_table.py baserom.gba include/decomp/entities.hh
	python3 tools/decode_map_data_table.py --rom baserom.gba --output $@

map-data-table: $(MAP_DATA_TABLE)

.PHONY: map-data-table

$(MAP_MASTER_INDEX): tools/generate_map_master_index.py $(WARP_INDEX) $(MAP_DATA_TABLE) include/decomp/entities.hh
	python3 tools/generate_map_master_index.py --map-data $(MAP_DATA_TABLE) --output $@

map-master-index: $(MAP_MASTER_INDEX)

.PHONY: map-master-index

collision-candidate-farm: baserom.gba tools/map_collision.py
	python3 tools/map_collision.py export-candidate --rom baserom.gba --map-id 2 --out-dir $(COLLISION_CANDIDATE_DIR)

collision-scan-popuri: baserom.gba tools/map_collision.py
	python3 tools/map_collision.py scan-popuri --rom baserom.gba --start 0x80000 --end 0x300000 --sizes 4096,4112 --output $(COLLISION_CANDIDATE_DIR)/popuri_4096_4112_scan.tsv

.PHONY: collision-candidate-farm collision-scan-popuri

# ELF
$(ELF): $(ALL_OBJS) $(LDS)
	@echo "LD $(LDS) $(ALL_OBJS:$(BUILD_DIR)/%=%)"
	@cd $(BUILD_DIR) && $(LD) -T ../$(LDS) -Map ../$(MAP) -L../tools/agbcc/lib $(ALL_OBJS:$(BUILD_DIR)/%=%) -lgcc -lc -o ../$@
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
$(BUILD_DIR)/src/libc_string.o: CFLAGS += -fno-builtin
$(BUILD_DIR)/src/strlen_stratum.o: CFLAGS += -fno-builtin
$(BUILD_DIR)/src/memcmp_stratum.o: CFLAGS += -fno-builtin
$(BUILD_DIR)/src/memcpy_stratum.o: CFLAGS += -fno-builtin
$(BUILD_DIR)/src/memmove_stratum.o: CFLAGS += -fno-builtin
$(BUILD_DIR)/src/memset_stratum.o: CFLAGS += -fno-builtin
$(BUILD_DIR)/src/strcat_stratum.o: CFLAGS += -fno-builtin
$(BUILD_DIR)/src/strcpy_stratum.o: CFLAGS += -fno-builtin

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
check-indexes: $(WARP_INDEX) $(SCRIPT_XREF_INDEX) $(WARP_TRIGGER_CANDIDATES) $(ROM_WARP_REF_INDEX) $(SCRIPT_TABLE_080F1FC0) $(MAP_DATA_TABLE) $(MAP_MASTER_INDEX)
	@echo "All index files OK"

.PHONY: check-indexes

# Run all Phase 4 checks
check-all: check-mary pre-build-check check-script-patches check-indexes
	@echo "All checks passed"

.PHONY: check-all
