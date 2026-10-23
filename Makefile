# Street Fighter III New Generation - CPS3 program ROM (same steps as build.bat)
BIN = bin
PYTHON ?= python
# the group rules below come before `all`
.DEFAULT_GOAL := all
# relative: SHC refuses an SHC_LIB longer than 116 characters
export SHC_LIB ?= bin
export SHC_TMP ?= C:\TEMP

# the compiler revision that built New Generation (see README.md, Compiler)
export MDL_MUL_CONST = 15
export XJUMP_2I = 62
export MDL_IV_AUTOINC = 1
export MDL_MOD_CONST = 3
export MDL_IMM_REG = 255
export MDL_EQ_CONST = 3
export MDL_TEMP_EXPR = 1
export MDL_GCSE = 26
export GEN_STORE_RHS_INDEX = 1
export GEN_LAST_IDX = 4
export ASM_CALL_SLACK = 6
export MDL_IV_START0 = 6
export MDL_IV_ADDR = 1
export PEP_SWITCH_END = 3
export MDL_IV = 31
export MDL_IV_WEB_ORDER = 1
export PEP_RETURN_EXIT = 1

CFLAGS = -cpu=sh2 -division=cpu -endian=big -pic=0 -extra=m=8,a=8 -nortnext -include=include
OPT = -optimize=1 -speed

# modules compiled with other options (units.txt in the development tree)
OPT0_PSYS = coin_chute coin_sw coin_sw_2 colortest cram_bank eeprom family fifo iotest_out meta_col_bcd poly_que simmram_slot \
	soundtest spr_list spr_pool spr_pool_2 sys_config sys_config_2 sys_config_3 sys_test sys_test_2 sys_test_2a sys_test_2b sys_test_2c \
	sys_test_3 sys_test_4 sys_test_5 textsound
$(OPT0_PSYS:%=obj/%.obj): OPT = -optimize=0 -nospeed -section=program=PSYS
$(OPT0_PSYS:%=obj/%.obj): export GEN_NARROW_CONST = 0

SPEED_CONSTTBL = Com_Pl EFF55 EFF61 EFF62 EFF69 EFF71 EFF72 EFF74 EFF85 EFF86 EFFD6 Eff93 \
	Eff95 Game_Main Manage RANKING appear bg000 bgst000 bgst010 bgst020 bgst030 bgst040 bgst050 \
	bgst070 bgst090 bgst100 bgst110 bgst140 bgst150 bgst160 bgst170 color3rd demo00 demo02_code eff20 \
	eff56 effe6 effe9 efff5 efff7 effg8 effh5 end_1 end_10 end_11 end_2 end_3 \
	end_4 end_5 end_7 end_8 end_9 end_main game_config_main lose_pl sel_flow sel_tech tate00 win_pl
$(SPEED_CONSTTBL:%=obj/%.obj): OPT = -optimize=1 -speed -section=const=CTBL

SPEED_NOINLINE = EFF25 EFF70 EFF98 EFFD5 EffD8 Entry Entry_dbg continue count plcntset_2 sc_sub_2 sc_sub_3 \
	sc_trans se_2 ta_sub
$(SPEED_NOINLINE:%=obj/%.obj): OPT = -optimize=1 -speed -noinline

SPEED_NOINLINE_CONSTTBL = CMD_MAIN SYS_sub eff36 eff94 end_main_c entry_2 game_config_en game_config_jp manage_2 sel_pl sel_pl_x3 win_2
$(SPEED_NOINLINE_CONSTTBL:%=obj/%.obj): OPT = -optimize=1 -speed -noinline -section=const=CTBL

SPEED_NOINLINE_CONSTTBL_PSYS = textsound_2
$(SPEED_NOINLINE_CONSTTBL_PSYS:%=obj/%.obj): OPT = -optimize=1 -speed -noinline -section=program=PSYS,const=CTBL

SPEED_NOINLINE_PSYS = textsound_3
$(SPEED_NOINLINE_PSYS:%=obj/%.obj): OPT = -optimize=1 -speed -noinline -section=program=PSYS

SPEED_PSYS = meta_col_lib meta_col_mem meta_col_strcpy scrn_ctrl sound_status sound_voice
$(SPEED_PSYS:%=obj/%.obj): OPT = -optimize=1 -speed -section=program=PSYS

SPEED_STABLE_PSYS = sound_voice_3
$(SPEED_STABLE_PSYS:%=obj/%.obj): OPT = -optimize=1 -speed -section=program=PSYS
$(SPEED_STABLE_PSYS:%=obj/%.obj): export PEP_AUTOINC = 0
$(SPEED_STABLE_PSYS:%=obj/%.obj): export ASM_READY_WAVES = 1

# tables between the code objects of P: their constant data as code (tools/incode.py)
INCODE = asstbl buttobi etc exchange gauge
$(INCODE:%=obj/%.obj): obj/%.obj: data/%.c | obj
	@echo $<
	@mkdir -p "$(SHC_TMP)/$(*F)"; SHC_TMP='$(SHC_TMP)\$(*F)' \
		$(BIN)/shc.exe $(call win,$<) $(CFLAGS) -optimize=1 -speed -section=const=P -code=asmcode -object=$(call win,$(@:.obj=.src)) >$(@:.obj=.log) 2>&1; \
		r=$$?; rm -rf "$(SHC_TMP)/$(*F)"; grep ') : ' $(@:.obj=.log); rm -f $(@:.obj=.log); [ $$r = 0 ]
	$(PYTHON) tools/incode.py $(@:.obj=.src) P
	$(BIN)/asmsh.exe $(call win,$(@:.obj=.src)) -object=$(call win,$@)

# tables between the code objects of PSYS: their constant data as code (tools/incode.py)
INCODE_PSYS = sound_voice_tbl sys_font textsound_tbl
$(INCODE_PSYS:%=obj/%.obj): obj/%.obj: data/%.c | obj
	@echo $<
	@mkdir -p "$(SHC_TMP)/$(*F)"; SHC_TMP='$(SHC_TMP)\$(*F)' \
		$(BIN)/shc.exe $(call win,$<) $(CFLAGS) -optimize=1 -speed -section=const=PSYS -code=asmcode -object=$(call win,$(@:.obj=.src)) >$(@:.obj=.log) 2>&1; \
		r=$$?; rm -rf "$(SHC_TMP)/$(*F)"; grep ') : ' $(@:.obj=.log); rm -f $(@:.obj=.log); [ $$r = 0 ]
	$(PYTHON) tools/incode.py $(@:.obj=.src) PSYS
	$(BIN)/asmsh.exe $(call win,$(@:.obj=.src)) -object=$(call win,$@)

# the link order is sfn.sub's
SRCS = $(wildcard src/*.c src/*.src data/*.c data/*.src lib/*.src)
OBJS = $(patsubst %,obj/%.obj,$(basename $(notdir $(SRCS))))
vpath %.c src data
vpath %.src src data lib

# the tools take Windows paths (asmsh reads / as an option)
win = '$(subst /,\,$1)'

all: build/prog.bin

# the compiler writes its internal tables to stdout: keep them in a log, show its messages. Each compile gets
# its own temporary directory: two compilers sharing one fail with an internal error under make -j
obj/%.obj: %.c | obj
	@echo $<
	@mkdir -p "$(SHC_TMP)/$(*F)"; SHC_TMP='$(SHC_TMP)\$(*F)' \
		$(BIN)/shc.exe $(call win,$<) $(CFLAGS) $(OPT) -object=$(call win,$@) >$(@:.obj=.log) 2>&1; \
		r=$$?; rm -rf "$(SHC_TMP)/$(*F)"; grep ') : ' $(@:.obj=.log); rm -f $(@:.obj=.log); [ $$r = 0 ]

obj/%.obj: %.src | obj
	$(BIN)/asmsh.exe $(call win,$<) -object=$(call win,$@)

# shc writes no dependency lists, so a header change rebuilds everything
$(OBJS): $(wildcard include/*.h)

obj:
	mkdir -p obj "$(SHC_TMP)"

sfn.abs: $(OBJS) sfn.sub
	$(BIN)/lnk.exe -subcommand=sfn.sub

sfn.bin: sfn.abs
	$(BIN)/rof2bin.exe -s=06000000 -e=06800000 -v=FF sfn.abs

build/rom_pieces.bin: $(wildcard rom/*.zip) tools/rom_pieces.tsv
	@mkdir -p build
	$(PYTHON) tools/cps3rom1.py extract rom $@

build/prog.bin: sfn.bin build/rom_pieces.bin tools/gaps.tsv
	$(PYTHON) tools/cps3rom1.py pack sfn.bin build/rom_pieces.bin rom build

clean:
	rm -rf obj build sfn.abs sfn.map sfn.bin

.PHONY: all clean
