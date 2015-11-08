# Edit these variables if more directories are needed.
# Separate each entry by spaces.


# THUMB Mode C++ Code
CXX_DIRS=$(CURDIR) src src/game_engine_stuff src/game_engine_stuff/block_stuff src/game_engine_stuff/level_stuff src/game_engine_stuff/sprite_stuff src/gba_specific_stuff src/test_level src/audio src/gfx

# THUMB Mode C Code
C_DIRS=$(CXX_DIRS)

# ARM Mode C++ Code
ARM_CXX_DIRS=$(CXX_DIRS)

# ARM Mode C Code
ARM_C_DIRS=$(CXX_DIRS)


# ARM or THUMB Mode ASM Code
S_DIRS=$(CXX_DIRS)



PROJ=$(shell basename $(CURDIR))

# The music file's basename
MUSIC_FILE_BASENAME=practice_13



# This compiler prefix is ARM-specific
#COMP_PREFIX=$(DEVKITARM)/bin/arm-none-eabi-
COMP_PREFIX=arm-none-eabi-


CC=$(COMP_PREFIX)gcc
CXX=$(COMP_PREFIX)g++
AS=$(COMP_PREFIX)as
#AS=$(COMP_PREFIX)gcc
#LD=$(COMP_PREFIX)ld
#LD=$(COMP_PREFIX)g++
LD=$(COMP_PREFIX)gcc
OBJDUMP=$(COMP_PREFIX)objdump
OBJCOPY=$(COMP_PREFIX)objcopy


LD_SCRIPT=linkscript.ld



#DEBUG_FLAGS=-gdwarf-2 -ggdb -gstrict-dwarf

GLOBAL_BASE_FLAGS=-mcpu=arm7tdmi -mtune=arm7tdmi -I./maxmod/include

THUMB_BASE_FLAGS=$(GLOBAL_BASE_FLAGS) -mthumb -mthumb-interwork
ARM_BASE_FLAGS=$(GLOBAL_BASE_FLAGS) -marm -mthumb-interwork


CXX_FLAGS=-std=c++14 $(THUMB_BASE_FLAGS) -O3 -D __thumb__  #-Wall
C_FLAGS=-std=c11 $(THUMB_BASE_FLAGS) -O3 -D __thumb__ -Wall

ARM_CXX_FLAGS=-std=c++14 $(ARM_BASE_FLAGS) -O3  -Wall
ARM_C_FLAGS=-std=c11 $(ARM_BASE_FLAGS) -O3 -Wall

S_FLAGS=-mcpu=arm7tdmi -mthumb -mthumb-interwork

# This is the LD_FLAGS for non-devkitARM GCC
LD_FLAGS=--specs=nosys.specs $(EXTRA_LD_FLAGS) -L./maxmod/lib -T $(LD_SCRIPT) -Wl,--entry=_start2 `$(CC) -print-file-name=thumb/libgcc.a` `$(CC) -print-file-name=thumb/libc.a` `$(CC) -print-file-name=thumb/libstdc++.a` -lgcc -lc -lstdc++ -lmm $(DEBUG_FLAGS)

# This is the LD_FLAGS for devkitARM
#LD_FLAGS=$(EXTRA_LD_FLAGS) -L./maxmod/lib -T $(LD_SCRIPT) -Wl,--entry=_start2 -lrdimon -lrdpmon -lmm -lgcc -lc -lstdc++ $(DEBUG_FLAGS)


OBJDIR=objs
ASMOUTDIR=asmouts
DEPDIR=deps
OBJDIR_TEMP=objs_temp


CXX_SOURCES=$(foreach DIR,$(CXX_DIRS),$(notdir $(wildcard $(DIR)/*.thumb.cpp)))
C_SOURCES=$(foreach DIR,$(C_DIRS),$(notdir $(wildcard $(DIR)/*.thumb.c)))

ARM_CXX_SOURCES=$(foreach DIR,$(ARM_CXX_DIRS), \
	$(notdir $(wildcard $(DIR)/*.arm.cpp)))
ARM_C_SOURCES=$(foreach DIR,$(ARM_C_DIRS),$(notdir $(wildcard $(DIR)/*.arm.c)))

S_SOURCES=$(foreach DIR,$(S_DIRS),$(notdir $(wildcard $(DIR)/*.s)))

export VPATH	:=	$(foreach DIR,$(CXX_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(C_DIRS),$(CURDIR)/$(DIR)) \
	\
	$(foreach DIR,$(ARM_CXX_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(ARM_C_DIRS),$(CURDIR)/$(DIR)) \
	\
	$(foreach DIR,$(S_DIRS),$(CURDIR)/$(DIR)) \


# Object code files
CXX_OFILES=$(patsubst %.thumb.cpp,$(OBJDIR)/%.thumb.o,$(CXX_SOURCES))
C_OFILES=$(patsubst %.thumb.c,$(OBJDIR)/%.thumb.o,$(C_SOURCES))

ARM_CXX_OFILES=$(patsubst %.arm.cpp,$(OBJDIR)/%.arm.o,$(ARM_CXX_SOURCES))
ARM_C_OFILES=$(patsubst %.arm.c,$(OBJDIR)/%.arm.o,$(ARM_C_SOURCES))

S_OFILES=$(patsubst %.s,$(OBJDIR)/%.o,$(S_SOURCES))
OFILES=$(MUSIC_FILE_BASENAME).bin.o $(CXX_OFILES) $(C_OFILES) \
	$(ARM_CXX_OFILES) $(ARM_C_OFILES) $(S_OFILES) 


# Automatically-Generated Dependency Files
CXX_PFILES=$(patsubst %.thumb.cpp,$(DEPDIR)/%.thumb.P,$(CXX_SOURCES))
C_PFILES=$(patsubst %.thumb.c,$(DEPDIR)/%.thumb.P,$(C_SOURCES))

ARM_CXX_PFILES=$(patsubst %.arm.cpp,$(DEPDIR)/%.arm.P,$(ARM_CXX_SOURCES))
ARM_C_PFILES=$(patsubst %.arm.c,$(DEPDIR)/%.arm.P,$(ARM_C_SOURCES))

S_PFILES=$(patsubst %.s,$(DEPDIR)/%.P,$(S_SOURCES))
PFILES=$(CXX_PFILES) $(C_PFILES) $(ARM_CXX_PFILES) $(ARM_C_PFILES) \
	$(S_PFILES)


# This is for cleaning object files with no source.
CXX_OFILES_TEMP=$(patsubst %.thumb.cpp,$(OBJDIR_TEMP)/%.thumb.o,$(CXX_SOURCES))
C_OFILES_TEMP=$(patsubst %.thumb.c,$(OBJDIR_TEMP)/%.thumb.o,$(C_SOURCES))

ARM_CXX_OFILES_TEMP=$(patsubst %.arm.cpp,$(OBJDIR_TEMP)/%.arm.o,$(ARM_CXX_SOURCES))
ARM_C_OFILES_TEMP=$(patsubst %.arm.c,$(OBJDIR_TEMP)/%.arm.o,$(ARM_C_SOURCES))

S_OFILES_TEMP=$(patsubst %.s,$(OBJDIR_TEMP)/%.o,$(S_SOURCES))
OFILES_TEMP=$(CXX_OFILES_TEMP) $(C_OFILES_TEMP) $(ARM_CXX_OFILES_TEMP) \
	$(ARM_C_OFILES_TEMP) $(S_OFILES_TEMP)


# Assembly source code generated by gcc/g++
CXX_ASMOUTS=$(patsubst %.thumb.cpp,$(ASMOUTDIR)/%.thumb.s,$(CXX_SOURCES))
C_ASMOUTS=$(patsubst %.thumb.c,$(ASMOUTDIR)/%.thumb.s,$(C_SOURCES))

ARM_CXX_ASMOUTS=$(patsubst %.arm.cpp,$(ASMOUTDIR)/%.arm.s,$(ARM_CXX_SOURCES))
ARM_C_ASMOUTS=$(patsubst %.arm.c,$(ASMOUTDIR)/%.arm.s,$(ARM_C_SOURCES))

ASMOUTS=$(CXX_ASMOUTS) $(C_ASMOUTS) $(ARM_CXX_ASMOUTS) $(ARM_C_ASMOUTS)



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

$(MUSIC_FILE_BASENAME).bin.o :
	util/bin2o_gba.sh src/audio/$(MUSIC_FILE_BASENAME).bin
	mv src/audio/$(MUSIC_FILE_BASENAME).bin.o objs



$(CXX_OFILES) : $(OBJDIR)/%.thumb.o : %.thumb.cpp
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.thumb.d $(DEPDIR)/$*.thumb.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.thumb.d >> $(DEPDIR)/$*.thumb.P
	@rm -f $(OBJDIR)/$*.thumb.d

$(C_OFILES) : $(OBJDIR)/%.thumb.o : %.thumb.c
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CC) $(C_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.thumb.d $(DEPDIR)/$*.thumb.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.thumb.d >> $(DEPDIR)/$*.thumb.P
	@rm -f $(OBJDIR)/$*.thumb.d


$(ARM_CXX_OFILES) : $(OBJDIR)/%.arm.o : %.arm.cpp
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CXX) $(ARM_CXX_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.arm.d $(DEPDIR)/$*.arm.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.arm.d >> $(DEPDIR)/$*.arm.P
	@rm -f $(OBJDIR)/$*.arm.d

$(ARM_C_OFILES) : $(OBJDIR)/%.arm.o : %.arm.c
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CC) $(ARM_C_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.arm.d $(DEPDIR)/$*.arm.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.arm.d >> $(DEPDIR)/$*.arm.P
	@rm -f $(OBJDIR)/$*.arm.d


$(S_OFILES) : $(OBJDIR)/%.o : %.s
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(AS) $(S_FLAGS) -MD $(OBJDIR)/$*.d -c $< -o $@
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(OBJDIR)/$*.d





# Here we have stuff for outputting assembly source code instead of an object file.
$(C_ASMOUTS) : $(ASMOUTDIR)/%.thumb.s : %.thumb.c
	$(CC) $(C_FLAGS) -MMD -S -fverbose-asm $< -o $@
	@cp $(ASMOUTDIR)/$*.thumb.d $(DEPDIR)/$*.thumb.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(ASMOUTDIR)/$*.thumb.d >> $(DEPDIR)/$*.thumb.P
	@rm -f $(ASMOUTDIR)/$*.thumb.d
	

# See above comment.
$(CXX_ASMOUTS) : $(ASMOUTDIR)/%.thumb.s : %.thumb.cpp
	$(CXX) $(CXX_FLAGS) -MMD -S -fverbose-asm $< -o $@
	@cp $(ASMOUTDIR)/$*.thumb.d $(DEPDIR)/$*.thumb.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(ASMOUTDIR)/$*.thumb.d >> $(DEPDIR)/$*.thumb.P
	@rm -f $(ASMOUTDIR)/$*.thumb.d


# Here we have stuff for outputting assembly source code instead of an object file.
$(ARM_C_ASMOUTS) : $(ASMOUTDIR)/%.arm.s : %.arm.c
	$(CC) $(ARM_C_FLAGS) -MMD -S -fverbose-asm $< -o $@
	@cp $(ASMOUTDIR)/$*.arm.d $(DEPDIR)/$*.arm.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(ASMOUTDIR)/$*.arm.d >> $(DEPDIR)/$*.arm.P
	@rm -f $(ASMOUTDIR)/$*.arm.d
	

# See above comment.
$(ARM_CXX_ASMOUTS) : $(ASMOUTDIR)/%.arm.s : %.arm.cpp
	$(CXX) $(ARM_CXX_FLAGS) -MMD -S -fverbose-asm $< -o $@
	@cp $(ASMOUTDIR)/$*.arm.d $(DEPDIR)/$*.arm.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(ASMOUTDIR)/$*.arm.d >> $(DEPDIR)/$*.arm.P
	@rm -f $(ASMOUTDIR)/$*.arm.d



-include $(PFILES)


#¯\(°_o)/¯

.PHONY : clean
clean :
	rm -rfv $(ASMOUTDIR) $(OBJDIR) $(DEPDIR) linker_map.txt $(PROJ).elf $(PROJ).gba 

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
	arm-none-eabi-objdump -marm7tdmi -d $(PROJ).elf

.PHONY : disassemble_all
disassemble_all :
	arm-none-eabi-objdump -marm7tdmi -D $(PROJ).elf


.PHONY : disassemble_2
disassemble_2 :
	arm-none-eabi-objdump -marm7tdmi -C -S -d $(PROJ).elf

.PHONY : disassemble_all_2
disassemble_all_2 :
	arm-none-eabi-objdump -marm7tdmi -C -S -D $(PROJ).elf
