# Edit these variables if more directories are needed.
# Separate each entry by spaces.

# Directories containing music files in .bin form
MUSIC_DIRS=src/audio

# THUMB Mode C++ Code
CXX_DIRS=$(CURDIR) src src/game_engine_stuff src/game_engine_stuff/block_stuff src/game_engine_stuff/level_stuff src/game_engine_stuff/sprite_stuff src/gba_specific_stuff src/test_level src/audio src/gfx

# ARM Mode C++ Code
ARM_CXX_DIRS=$(CXX_DIRS)


# ARM or THUMB Mode ASM Code
S_DIRS=$(CXX_DIRS)



# End of directory variables



# This is likely specific to *nix... but then again, the entire makefile is
# probably specific to *nix!
PROJ=$(shell basename $(CURDIR))

# The music file's basename
MUSIC_FILE_BASENAME=practice_17



# This compiler prefix is ARM-specific
#COMP_PREFIX=$(DEVKITARM)/bin/arm-none-eabi-
COMP_PREFIX=arm-none-eabi-


# Compilers, assemblers, and the linker
#CC=$(COMP_PREFIX)gcc
CXX=$(COMP_PREFIX)g++
AS=$(COMP_PREFIX)as
#AS=$(COMP_PREFIX)gcc
#LD=$(COMP_PREFIX)ld
LD=$(COMP_PREFIX)g++
#LD=$(COMP_PREFIX)gcc
OBJDUMP=$(COMP_PREFIX)objdump
OBJCOPY=$(COMP_PREFIX)objcopy


# The linker script
LD_SCRIPT=linkscript.ld

VERBOSE_ASM_FLAG=
#VERBOSE_ASM_FLAG=-fverbose-asm



#DEBUG=yeah do debug

# Optimization levels
#DEBUG_OPTIMIZATION_LEVEL=-O1
DEBUG_OPTIMIZATION_LEVEL=-Og
#DEBUG_OPTIMIZATION_LEVEL=-O2

REGULAR_OPTIMIZATION_LEVEL=-O2
#REGULAR_OPTIMIZATION_LEVEL=-O3

GLOBAL_BASE_FLAGS:=-mcpu=arm7tdmi -mtune=arm7tdmi -I$(DEVKITPRO)/libgba/include -nostartfiles \
	-fno-exceptions -fno-rtti 

ifdef DEBUG
	##DEBUG_FLAGS=-gdwarf-2 -ggdb -gstrict-dwarf -g
	DEBUG_FLAGS=-gdwarf-3 -g
	
	GLOBAL_BASE_FLAGS:=$(GLOBAL_BASE_FLAGS) $(DEBUG_OPTIMIZATION_LEVEL) -g
else
	GLOBAL_BASE_FLAGS:=$(GLOBAL_BASE_FLAGS) $(REGULAR_OPTIMIZATION_LEVEL)
endif


# Thumb/ARM compiler flags
THUMB_BASE_FLAGS=$(GLOBAL_BASE_FLAGS) -mthumb -mthumb-interwork
ARM_BASE_FLAGS=$(GLOBAL_BASE_FLAGS) -marm -mthumb-interwork


# Eventually I'll use -std=c++17
CXX_FLAGS=-std=c++14 $(THUMB_BASE_FLAGS) -D __thumb__  -Wall
ARM_CXX_FLAGS=-std=c++14 $(ARM_BASE_FLAGS)  -Wall
S_FLAGS=-mcpu=arm7tdmi -mthumb -mthumb-interwork



# Linker flags
# This is the LD_FLAGS for non-devkitARM GCC
LD_FLAGS=--specs=nosys.specs -lgcc -lc -lstdc++ $(EXTRA_LD_FLAGS) -L$(DEVKITPRO)/libgba/lib -T $(LD_SCRIPT) -Wl,--entry=_start2 `$(CXX) -print-file-name=thumb/libgcc.a` `$(CXX) -print-file-name=thumb/libc.a` `$(CXX) -print-file-name=thumb/libstdc++.a` -lmm $(DEBUG_FLAGS)
#LD_FLAGS=--specs=nosys.specs -lgcc -lc -lstdc++ $(EXTRA_LD_FLAGS) -L$(DEVKITPRO)/libgba/lib -T $(LD_SCRIPT) -Wl,--entry=_start2 `$(CC) -print-file-name=thumb/libgcc.a` `$(CC) -print-file-name=thumb/libc.a` `$(CC) -print-file-name=thumb/libstdc++.a` -lmm $(DEBUG_FLAGS) -g

#LD_FLAGS=--specs=nosys.specs -nostartfiles -lgcc -lc -lstdc++ $(EXTRA_LD_FLAGS) -L$(DEVKITPRO)/libgba/lib -T $(LD_SCRIPT) `$(CC) -print-file-name=thumb/libgcc.a` `$(CC) -print-file-name=thumb/libc.a` `$(CC) -print-file-name=thumb/libstdc++.a` -lmm $(DEBUG_FLAGS)
#LD_FLAGS=--specs=nosys.specs -lgcc -lc -lstdc++ $(EXTRA_LD_FLAGS) -L$(DEVKITPRO)/libgba/lib -T $(LD_SCRIPT) `$(CC) -print-file-name=thumb/libgcc.a` `$(CC) -print-file-name=thumb/libc.a` `$(CC) -print-file-name=thumb/libstdc++.a` -lmm $(DEBUG_FLAGS)



# Generated directories
OBJDIR=objs
ASMOUTDIR=asmouts
DEPDIR=deps
OBJDIR_TEMP=objs_temp
OBJDIR_DIS=objs_dis

# Flags for make disassemble*
DISASSEMBLE_FLAGS=-marm7tdmi -C -d 
DISASSEMBLE_ALL_FLAGS=-marm7tdmi -C -D 

DISASSEMBLE_2_FLAGS=-marm7tdmi -C -S -l -d 
DISASSEMBLE_ALL_2_FLAGS=-marm7tdmi -C -S -l -D 

DISASSEMBLE_3_FLAGS=$(DISASSEMBLE_FLAGS)
DISASSEMBLE_ALL_3_FLAGS=$(DISASSEMBLE_ALL_FLAGS)

DISASSEMBLE_4_FLAGS=$(DISASSEMBLE_2_FLAGS)
DISASSEMBLE_ALL_4_FLAGS=$(DISASSEMBLE_ALL_2_FLAGS)




# Source code files
MUSIC_BINFILES=$(foreach DIR,$(MUSIC_DIRS),$(notdir $(wildcard $(DIR)/*.bin)))
CXX_SOURCES=$(foreach DIR,$(CXX_DIRS),$(notdir $(wildcard $(DIR)/*.thumb.cpp)))
ARM_CXX_SOURCES=$(foreach DIR,$(ARM_CXX_DIRS), \
	$(notdir $(wildcard $(DIR)/*.arm.cpp)))
S_SOURCES=$(foreach DIR,$(S_DIRS),$(notdir $(wildcard $(DIR)/*.s)))


# Directories to search, specified at the top of this makefile
export VPATH	:=	$(foreach DIR,$(MUSIC_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(CXX_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(ARM_CXX_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(S_DIRS),$(CURDIR)/$(DIR)) \


# Object code files
MUSIC_OFILES=$(patsubst %.bin,$(OBJDIR)/%.bin.o,$(MUSIC_BINFILES))
CXX_OFILES=$(patsubst %.thumb.cpp,$(OBJDIR)/%.thumb.o,$(CXX_SOURCES))
ARM_CXX_OFILES=$(patsubst %.arm.cpp,$(OBJDIR)/%.arm.o,$(ARM_CXX_SOURCES))
S_OFILES=$(patsubst %.s,$(OBJDIR)/%.o,$(S_SOURCES))


#OFILES=$(MUSIC_FILE_BASENAME).bin.o $(CXX_OFILES) \
#	$(ARM_CXX_OFILES) $(S_OFILES)
OFILES=$(MUSIC_OFILES) $(CXX_OFILES) $(ARM_CXX_OFILES) $(S_OFILES) 


# Automatically-Generated Dependency Files
CXX_PFILES=$(patsubst %.thumb.cpp,$(DEPDIR)/%.thumb.P,$(CXX_SOURCES))
ARM_CXX_PFILES=$(patsubst %.arm.cpp,$(DEPDIR)/%.arm.P,$(ARM_CXX_SOURCES))
S_PFILES=$(patsubst %.s,$(DEPDIR)/%.P,$(S_SOURCES))
PFILES=$(CXX_PFILES) $(ARM_CXX_PFILES)  \
	$(S_PFILES)


# This is for cleaning object files with no source.
MUSIC_OFILES_TEMP=$(patsubst %.bin,$(OBJDIR_TEMP)/%.bin.o,$(MUSIC_BINFILES))
CXX_OFILES_TEMP=$(patsubst %.thumb.cpp,$(OBJDIR_TEMP)/%.thumb.o,$(CXX_SOURCES))
ARM_CXX_OFILES_TEMP=$(patsubst %.arm.cpp,$(OBJDIR_TEMP)/%.arm.o,$(ARM_CXX_SOURCES))
S_OFILES_TEMP=$(patsubst %.s,$(OBJDIR_TEMP)/%.o,$(S_SOURCES))
OFILES_TEMP=$(MUSIC_OFILES_TEMP) $(CXX_OFILES_TEMP) \
	$(ARM_CXX_OFILES_TEMP) $(S_OFILES_TEMP)



#MUSIC_OFILES_DIS=$(patsubst %.bin,$(OBJDIR_DIS)/%.bin.armasm,$(MUSIC_BINFILES))
#CXX_OFILES_DIS=$(patsubst %.thumb.cpp,$(OBJDIR_DIS)/%.thumb.armasm,$(CXX_SOURCES))
#ARM_CXX_OFILES_DIS=$(patsubst %.arm.cpp,$(OBJDIR_DIS)/%.arm.armasm,$(ARM_CXX_SOURCES))
#S_OFILES_DIS=$(patsubst %.s,$(OBJDIR_DIS)/%.armasm,$(S_SOURCES))
#OFILES_DIS=$(MUSIC_OFILES_DIS) $(CXX_OFILES_DIS) \
#	$(ARM_CXX_OFILES_DIS) $(S_OFILES_DIS)



# Assembly source code generated by gcc/g++
CXX_ASMOUTS=$(patsubst %.thumb.cpp,$(ASMOUTDIR)/%.thumb.s,$(CXX_SOURCES))
ARM_CXX_ASMOUTS=$(patsubst %.arm.cpp,$(ASMOUTDIR)/%.arm.s,$(ARM_CXX_SOURCES))
ASMOUTS=$(CXX_ASMOUTS) $(ARM_CXX_ASMOUTS)


# Preprocessed output of only C++ files
CXX_EFILES=$(patsubst %.thumb.cpp,$(PREPROCDIR)/%.thumb.E,$(CXX_SOURCES))
ARM_CXX_EFILES=$(patsubst %.arm.cpp,$(PREPROCDIR)/%.arm.E,$(ARM_CXX_SOURCES))
EFILES=$(CXX_EFILES) $(ARM_CXX_EFILES)



all : all_pre $(OFILES)
	@echo
	$(LD) $(OBJDIR)/*.o -o $(PROJ).elf $(LD_FLAGS) -Wl,-M > linker_map.txt
	$(OBJCOPY) -O binary -R .iwram -R .sram $(PROJ).elf $(PROJ).gba
	./do_gbafix.sh

all_objs : all_pre $(OFILES)
	@#

do_asmouts : all_pre all_pre_asmout $(ASMOUTS)
	@#

#debug : all_pre $(OFILES)
#	$(LD) $(OBJDIR)/*.o -o $(PROJ).elf $(LD_FLAGS) -g
#	$(OBJCOPY) -O binary $(PROJ).elf $(PROJ).gba

all_pre :
	mkdir -p $(OBJDIR) $(DEPDIR)

all_pre_asmout :
	mkdir -p $(ASMOUTDIR)

#$(MUSIC_FILE_BASENAME).bin.o :
#	util/bin2o_gba.sh src/audio/$(MUSIC_FILE_BASENAME).bin
#	mv src/audio/$(MUSIC_FILE_BASENAME).bin.o objs
#$(MUSIC_FILE_BASENAME).bin.o : $(MUSIC_FILE_BASENAME).bin
#	util/bin2o_gba.sh src/audio/$(MUSIC_FILE_BASENAME).bin objs/$(MUSIC_FILE_BASENAME).bin.o

$(MUSIC_OFILES) : $(OBJDIR)/%.bin.o : %.bin
	util/bin2o_gba.sh $< $@


# This sed script is basically a hack for dependency generation stuff.
sed_script:=$(shell echo "sed -e 's/\#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/'")

# Here's where things get really messy.  Oh if only GNU Make had functions
# somehow... perhaps I should be using mktemp for a generated shell script!
$(CXX_OFILES) : $(OBJDIR)/%.thumb.o : %.thumb.cpp
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.thumb.d $(DEPDIR)/$*.thumb.P
	@$(sed_script) < $(OBJDIR)/$*.thumb.d >> $(DEPDIR)/$*.thumb.P
	@rm -f $(OBJDIR)/$*.thumb.d



$(ARM_CXX_OFILES) : $(OBJDIR)/%.arm.o : %.arm.cpp
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CXX) $(ARM_CXX_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.arm.d $(DEPDIR)/$*.arm.P
	@$(sed_script) < $(OBJDIR)/$*.arm.d >> $(DEPDIR)/$*.arm.P
	@rm -f $(OBJDIR)/$*.arm.d



$(S_OFILES) : $(OBJDIR)/%.o : %.s
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(AS) $(S_FLAGS) -MD $(OBJDIR)/$*.d -c $< -o $@
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
	@$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(OBJDIR)/$*.d





# Here we have stuff for outputting assembly source code instead of an object file.
$(CXX_ASMOUTS) : $(ASMOUTDIR)/%.thumb.s : %.thumb.cpp
	@#$(CXX) $(CXX_FLAGS) -MMD -S -fverbose-asm $< -o $@
	@#$(CXX) $(CXX_FLAGS) -MMD -S $< -o $@
	$(CXX) $(CXX_FLAGS) -MMD -S $(VERBOSE_ASM_FLAG) $< -o $@
	@cp $(ASMOUTDIR)/$*.thumb.d $(DEPDIR)/$*.thumb.P
	@$(sed_script) < $(ASMOUTDIR)/$*.thumb.d >> $(DEPDIR)/$*.thumb.P
	@rm -f $(ASMOUTDIR)/$*.thumb.d



# Here we have stuff for outputting assembly source code instead of an object file.
$(ARM_CXX_ASMOUTS) : $(ASMOUTDIR)/%.arm.s : %.arm.cpp
	@#$(CXX) $(ARM_CXX_FLAGS) -MMD -S -fverbose-asm $< -o $@
	@#$(CXX) $(ARM_CXX_FLAGS) -MMD -S $< -o $@
	$(CXX) $(ARM_CXX_FLAGS) -MMD -S $(VERBOSE_ASM_FLAG) $< -o $@
	@cp $(ASMOUTDIR)/$*.arm.d $(DEPDIR)/$*.arm.P
	@$(sed_script) < $(ASMOUTDIR)/$*.arm.d >> $(DEPDIR)/$*.arm.P
	@rm -f $(ASMOUTDIR)/$*.arm.d



-include $(PFILES)



only_preprocess : only_preprocess_pre $(EFILES)
	@#

only_preprocess_pre : 
	mkdir -p $(PREPROCDIR)


$(CXX_EFILES) : $(PREPROCDIR)/%.thumb.E : %.thumb.cpp
	$(CXX) $(CXX_FLAGS) -E $< -o $@

$(ARM_CXX_EFILES) : $(PREPROCDIR)/%.arm.E : %.arm.cpp
	$(CXX) $(ARM_CXX_FLAGS) -E $< -o $@



#¯\(°_o)/¯

.PHONY : clean
clean :
	rm -rfv $(ASMOUTDIR) $(OBJDIR) $(OBJDIR_DIS) $(DEPDIR) $(PREPROCDIR) linker_map.txt $(PROJ).elf $(PROJ).gba 

.PHONY : clean_objs_with_no_source
clean_objs_with_no_source :
	@mkdir -p $(OBJDIR_TEMP)
	@#ls $(OBJDIR)
	@echo "Removing object files that don't have corresponding source files...."
	@for objfile in $(OFILES); \
	do \
		if [ -f $$objfile ]; \
		then \
			mv $$objfile $(OBJDIR_TEMP); \
		fi; \
	done;
	@#ls $(OBJDIR_TEMP)
	@rm -rf $(OBJDIR)
	@mkdir -p $(OBJDIR)
	@for objfile in $(OFILES_TEMP); \
	do \
		if [ -f $$objfile ]; \
		then \
			mv $$objfile $(OBJDIR); \
		fi; \
	done;
	@#ls $(OBJDIR)
	@rmdir $(OBJDIR_TEMP)
	
	
	
	@#rm -rfv $(OBJDIR_TEMP)


.PHONY : disassemble
disassemble :
	$(OBJDUMP) $(DISASSEMBLE_FLAGS) $(PROJ).elf

.PHONY : disassemble_all
disassemble_all :
	$(OBJDUMP) $(DISASSEMBLE_ALL_FLAGS) $(PROJ).elf


.PHONY : disassemble_2
disassemble_2 :
	$(OBJDUMP) $(DISASSEMBLE_2_FLAGS) $(PROJ).elf

.PHONY : disassemble_all_2
disassemble_all_2 :
	$(OBJDUMP) $(DISASSEMBLE_ALL_2_FLAGS) $(PROJ).elf



.PHONY : disassemble_3
disassemble_3 :
	@mkdir -p $(OBJDIR_DIS)
	@for objfile in $(OBJDIR)/*.o; \
	do \
		out=`basename $$objfile`;\
		if [ -f $$objfile ]; \
		then \
			$(OBJDUMP) $(DISASSEMBLE_3_FLAGS) $$objfile \
				> $(OBJDIR_DIS)/$$out.armasm; \
		fi; \
	done;


.PHONY : disassemble_all_3
disassemble_all_3 :
	@mkdir -p $(OBJDIR_DIS)
	@for objfile in $(OBJDIR)/*.o; \
	do \
		out=`basename $$objfile`;\
		if [ -f $$objfile ]; \
		then \
			$(OBJDUMP) $(DISASSEMBLE_ALL_3_FLAGS) $$objfile \
				> $(OBJDIR_DIS)/$$out.armasm; \
		fi; \
	done;


.PHONY : disassemble_4
disassemble_4 :
	@mkdir -p $(OBJDIR_DIS)
	@for objfile in $(OBJDIR)/*.o; \
	do \
		out=`basename $$objfile`;\
		if [ -f $$objfile ]; \
		then \
			$(OBJDUMP) $(DISASSEMBLE_4_FLAGS) $$objfile \
				> $(OBJDIR_DIS)/$$out.armasm; \
		fi; \
	done;


.PHONY : disassemble_all_4
disassemble_all_4 :
	@mkdir -p $(OBJDIR_DIS)
	@for objfile in $(OBJDIR)/*.o; \
	do \
		out=`basename $$objfile`;\
		if [ -f $$objfile ]; \
		then \
			$(OBJDUMP) $(DISASSEMBLE_ALL_4_FLAGS) $$objfile \
				> $(OBJDIR_DIS)/$$out.armasm; \
		fi; \
	done;
