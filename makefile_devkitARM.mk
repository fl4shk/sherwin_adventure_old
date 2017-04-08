# This file is part of Sherwin's Adventure.
#  
# Copyright 2015-2017 Andrew Clark (FL4SHK).
# 
# Sherwin's Adventure is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
# 
# Sherwin's Adventure is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


# In both this makefile (makefile_devkitARM.mk) and the makefile for
# updated GCC (makefile_for_non_dka_gcc.mk), the contents after the
# creation of the LD_FLAGS variable are supposed to be the same.


# These directories specify where source code files are located.
# Edit these variables if more directories are needed.
# Separate each entry by spaces.


# Directories containing music files in .bin form
MUSIC_DIRS:=src/audio

# ARM or THUMB Mode C++ Code
CXX_DIRS:=$(CURDIR) src src/borrowed_stuff src/general_utility_stuff \
	src/game_engine_stuff src/game_engine_stuff/block_stuff \
	src/game_engine_stuff/level_stuff src/game_engine_stuff/sprite_stuff \
	src/game_engine_stuff/sprite_stuff/specific_sprites \
	src/gba_specific_stuff src/test_level src/audio src/gfx \

# ARM or THUMB Mode ASM Code
S_DIRS:=$(CXX_DIRS)


# End of source directory variables


# This compiler prefix is ARM-specific
COMP_PREFIX:=$(DEVKITARM)/bin/arm-none-eabi-

# The linker script
LD_SCRIPT:=linkscript.ld

# Linker flags
COMMON_LD_FLAGS:=-mthumb --specs=nosys.specs -L$(DEVKITPRO)/libgba/lib -T $(LD_SCRIPT) -Wl,--entry=_start2 -lgcc -lc -lstdc++ -lmm




ALWAYS_DEBUG_SUFFIX:=_debug


# Comment out or un-comment out the next line to enable debugging stuff to
# be generated
DEBUG:=yeah do debug

# Optimization levels
#DEBUG_OPTIMIZATION_LEVEL:=-O0
#DEBUG_OPTIMIZATION_LEVEL:=-O1
DEBUG_OPTIMIZATION_LEVEL:=-Og 
#DEBUG_OPTIMIZATION_LEVEL:=-O2
#DEBUG_OPTIMIZATION_LEVEL:=-O3

#REGULAR_OPTIMIZATION_LEVEL:=-O1 
REGULAR_OPTIMIZATION_LEVEL:=-O2
#REGULAR_OPTIMIZATION_LEVEL:=-O3


# Compilers, assemblers, and the linker
CXX:=$(COMP_PREFIX)g++
AS:=$(COMP_PREFIX)as 
LD:=$(COMP_PREFIX)g++ 
OBJDUMP:=$(COMP_PREFIX)objdump
OBJCOPY:=$(COMP_PREFIX)objcopy

# CXX_FLAGS and GLOBAL_BASE_FLAGS are appended to later
CXX_FLAGS:=-std=c++17 -Wall $(THUMB_BASE_FLAGS) 
S_FLAGS:=-mcpu=arm7tdmi -mthumb -mthumb-interwork
GLOBAL_BASE_FLAGS:=-mcpu=arm7tdmi -mtune=arm7tdmi \
	-I$(DEVKITPRO)/libgba/include -nostartfiles \
	-fno-rtti -ffast-math -fno-threadsafe-statics


ifdef DEBUG
	EXTRA_DEBUG_FLAGS:=-g 
	DEBUG_FLAGS:=-gdwarf-3 $(EXTRA_DEBUG_FLAGS)
	
	OPTIMIZATION_LEVEL:=$(DEBUG_OPTIMIZATION_LEVEL)
	
	# Only do profiling stuff when debugging stuff is enabled
	EXTRA_LD_FLAGS:=$(PROFILE_FLAGS) $(DEBUG_FLAGS)
	
	DEBUG_SUFFIX:=$(ALWAYS_DEBUG_SUFFIX)
else
	OPTIMIZATION_LEVEL:=$(REGULAR_OPTIMIZATION_LEVEL)
endif


# This is likely specific to *nix... but then again, the entire makefile is
# probably specific to *nix!
PROJ:=$(shell basename $(CURDIR))$(DEBUG_SUFFIX)

VERBOSE_ASM_FLAG:=
#VERBOSE_ASM_FLAG:=-fverbose-asm


# The final GLOBAL_BASE_FLAGS
GLOBAL_BASE_FLAGS:=$(GLOBAL_BASE_FLAGS) $(OPTIMIZATION_LEVEL)  $(EXTRA_DEBUG_FLAGS)


# Thumb/ARM compiler flags
THUMB_BASE_FLAGS:=$(GLOBAL_BASE_FLAGS) -mthumb -mthumb-interwork

# The final CXX_FLAGS
CXX_FLAGS:=$(CXX_FLAGS) $(THUMB_BASE_FLAGS) 









LD_FLAGS:=$(COMMON_LD_FLAGS) $(EXTRA_LD_FLAGS)


# Generated directories
OBJDIR:=objs$(DEBUG_SUFFIX)
ASMOUTDIR:=asmouts$(DEBUG_SUFFIX)
DEPDIR:=deps$(DEBUG_SUFFIX)
OBJDIR_TEMP:=objs_temp$(DEBUG_SUFFIX)
OBJDIR_DIS:=objs_dis$(DEBUG_SUFFIX)
PREPROCDIR:=preprocs$(DEBUG_SUFFIX)



# Source code files 
MUSIC_BINFILES:=$(foreach DIR,$(MUSIC_DIRS),$(notdir $(wildcard $(DIR)/*.bin))) 
CXX_SOURCES:=$(foreach DIR,$(CXX_DIRS),$(notdir $(wildcard $(DIR)/*.cpp)))
S_SOURCES:=$(foreach DIR,$(S_DIRS),$(notdir $(wildcard $(DIR)/*.s)))


# Directories to search, specified above 
export VPATH	:=	$(foreach DIR,$(MUSIC_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(CXX_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(S_DIRS),$(CURDIR)/$(DIR))


# Object code files 
MUSIC_OFILES:=$(MUSIC_BINFILES:%.bin=$(OBJDIR)/%.bin.o) 
CXX_OFILES:=$(CXX_SOURCES:%.cpp=$(OBJDIR)/%.o)
S_OFILES:=$(S_SOURCES:%.s=$(OBJDIR)/%.o) 
OFILES:=$(MUSIC_OFILES) $(CXX_OFILES) $(ARM_CXX_OFILES) $(S_OFILES) 


# Automatically-Generated Dependency Files  
CXX_PFILES:=$(CXX_SOURCES:%.cpp=$(DEPDIR)/%.P)
S_PFILES:=$(S_SOURCES:%.s=$(DEPDIR)/%.P)
PFILES:=$(CXX_PFILES) $(ARM_CXX_PFILES)  \
	$(S_PFILES)


# This is for cleaning object files with no source.  
MUSIC_OFILES_TEMP:=$(MUSIC_BINFILES:%.bin=$(OBJDIR_TEMP)/%.bin.o) 
CXX_OFILES_TEMP:=$(CXX_SOURCES:%.cpp=$(OBJDIR_TEMP)/%.o)
S_OFILES_TEMP:=$(S_SOURCES:%.s=$(OBJDIR_TEMP)/%.o)
OFILES_TEMP:=$(MUSIC_OFILES_TEMP) $(CXX_OFILES_TEMP) \
	$(S_OFILES_TEMP)






# Assembly source code generated by gcc/g++  
CXX_ASMOUTS:=$(CXX_SOURCES:%.cpp=$(ASMOUTDIR)/%.s)
ASMOUTS:=$(CXX_ASMOUTS) $(ARM_CXX_ASMOUTS)


# Preprocessed output of only C++ files  
CXX_EFILES:=$(CXX_SOURCES:%.cpp=$(PREPROCDIR)/%.E)
EFILES:=$(CXX_EFILES) $(ARM_CXX_EFILES)



all : all_pre $(OFILES)
	@echo
	$(LD) $(OBJDIR)/*.o -o $(PROJ).elf $(LD_FLAGS) -Wl,-M > linker_map.txt 
	$(OBJCOPY) -O binary -S -g -R .iwram -R .sram $(PROJ).elf $(PROJ).gba 
	./do_gbafix.sh

all_objs : all_pre $(OFILES)
	@#

do_asmouts : all_pre all_pre_asmout $(ASMOUTS)
	@#



all_pre :
	mkdir -p $(OBJDIR) $(DEPDIR)

all_pre_asmout :
	mkdir -p $(ASMOUTDIR)



$(MUSIC_OFILES) : $(OBJDIR)/%.bin.o : %.bin
	util/bin2o_gba.sh $< $@


# This sed script is basically a hack for dependency generation stuff.
sed_script:=$(shell echo "sed -e 's/\#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/'")





# Here's where things get really messy.  
$(CXX_OFILES) : $(OBJDIR)/%.o : %.cpp
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
	@$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(OBJDIR)/$*.d





# Yeah, Assembly is *TOTALLY* a High Level Language.  Good job naming that.
# (Yes, I wrote both this comment and the makefile GPP "source").
$(S_OFILES) : $(OBJDIR)/%.o : %.s
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Assembling...."
	$(AS) $(S_FLAGS) -MD $(OBJDIR)/$*.d -c $< -o $@
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
	@$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(OBJDIR)/$*.d



# Here we have stuff for outputting assembly source code instead of an object file.  
$(CXX_ASMOUTS) : $(ASMOUTDIR)/%.s : %.cpp
	@#$(CXX) $(CXX_FLAGS) -MMD -S -fverbose-asm $< -o $@
	@#$(CXX) $(CXX_FLAGS) -MMD -S $< -o $@
	$(CXX) $(CXX_FLAGS) -MMD -S $(VERBOSE_ASM_FLAG) $< -o $@
	@cp $(ASMOUTDIR)/$*.d $(DEPDIR)/$*.P
	@$(sed_script) < $(ASMOUTDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(ASMOUTDIR)/$*.d






-include $(PFILES)



only_preprocess : only_preprocess_pre $(EFILES)
	@#

only_preprocess_pre : 
	mkdir -p $(PREPROCDIR)




$(CXX_EFILES) : $(PREPROCDIR)/%.E : %.cpp
	$(CXX) $(CXX_FLAGS) -E $< -o $@



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



# Flags for make disassemble*
DISASSEMBLE_FLAGS:=-marm7tdmi -C -d 
DISASSEMBLE_ALL_FLAGS:=-marm7tdmi -C -D 

DISASSEMBLE_2_FLAGS:=-marm7tdmi -C -S -l -d 
DISASSEMBLE_ALL_2_FLAGS:=-marm7tdmi -C -S -l -D 

DISASSEMBLE_3_FLAGS:=$(DISASSEMBLE_FLAGS)
DISASSEMBLE_ALL_3_FLAGS:=$(DISASSEMBLE_ALL_FLAGS)

DISASSEMBLE_4_FLAGS:=$(DISASSEMBLE_2_FLAGS)
DISASSEMBLE_ALL_4_FLAGS:=$(DISASSEMBLE_ALL_2_FLAGS)


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
