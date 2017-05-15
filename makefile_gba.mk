# These directories specify where source code files are located.
# Edit these variables if more directories are needed.  
# Separate each entry by spaces.
SHARED_SRC_DIRS:=src src/borrowed_stuff src/general_utility_stuff \
	src/game_engine_stuff src/game_engine_stuff/block_stuff \
	src/game_engine_stuff/block_stuff/specific_blocks \
	src/game_engine_stuff/level_stuff src/game_engine_stuff/sprite_stuff \
	src/game_engine_stuff/sprite_stuff/specific_sprites \
	src/gba_specific_stuff src/test_level src/audio src/gfx
BINARY_DIRS:=src/audio
CXX_DIRS:=$(SHARED_SRC_DIRS)
S_DIRS:=$(SHARED_SRC_DIRS)

# End of source directories


# Comment out or un-comment out the next line to enable debugging stuff to
# be generated
DEBUG:=yeah do debug

#DEBUG_OPTIMIZATION_LEVEL:=-O0
DEBUG_OPTIMIZATION_LEVEL:=-Og
REGULAR_OPTIMIZATION_LEVEL:=-O2

ALWAYS_DEBUG_SUFFIX:=_debug
ifdef DEBUG
	DEBUG_SUFFIX:=$(ALWAYS_DEBUG_SUFFIX)
endif

# This is the name of the output file.  Change this if needed!
PROJ:=$(shell basename $(CURDIR))$(DEBUG_SUFFIX)


# This is used for do_asmouts
VERBOSE_ASM_FLAG:=
#VERBOSE_ASM_FLAG:=-fverbose-asm

PREFIX:=$(DEVKITARM)/bin/arm-none-eabi-

# Compilers and initial compiler flags
CXX:=$(PREFIX)g++
CXX_FLAGS:=$(CXX_FLAGS) -std=c++17 -Wall

AS:=$(PREFIX)as

OBJDUMP:=$(PREFIX)objdump
OBJCOPY:=$(PREFIX)objcopy
LD:=$(CXX)

# Initial linker flags
LD_FLAGS:=$(LD_FLAGS) -lm



ifdef DEBUG
	EXTRA_DEBUG_FLAGS:=-g
	DEBUG_FLAGS:=-gdwarf-3 $(EXTRA_DEBUG_FLAGS)
	EXTRA_LD_FLAGS:=$(DEBUG_FLAGS)
	OPTIMIZATION_LEVEL:=$(DEBUG_OPTIMIZATION_LEVEL)
else
	OPTIMIZATION_LEVEL:=$(REGULAR_OPTIMIZATION_LEVEL)
endif

EXTRA_BASE_FLAGS:=-mcpu=arm7tdmi -mtune=arm7tdmi -mthumb \
	-mthumb-interwork \
	-fno-threadsafe-statics -nostartfiles
#EXTRA_BASE_FLAGS:=-mcpu=arm7tdmi -mtune=arm7tdmi -marm \
#	-mthumb-interwork \
#	-fno-threadsafe-statics -nostartfiles

EXTRA_LD_FLAGS:=$(EXTRA_LD_FLAGS) -mthumb --specs=nosys.specs -lm \
	-lgcc -lc -lstdc++
LD_SCRIPT:=linkscript.ld
COMMON_LD_FLAGS:=$(COMMON_LD_FLAGS) -L$(DEVKITPRO)/libgba/lib \
	-T $(LD_SCRIPT) -Wl,--entry=_start2 -lmm

DISASSEMBLE_BASE_FLAGS:=-marm7tdmi



FINAL_BASE_FLAGS:=$(OPTIMIZATION_LEVEL) \
	$(EXTRA_BASE_FLAGS) $(EXTRA_DEBUG_FLAGS)
FINAL_BASE_FLAGS:=-I$(DEVKITPRO)/libgba/include $(FINAL_BASE_FLAGS)

# Final compiler and linker flags
CXX_FLAGS:=$(CXX_FLAGS) $(FINAL_BASE_FLAGS)
LD_FLAGS:=$(LD_FLAGS) $(EXTRA_LD_FLAGS) $(COMMON_LD_FLAGS)




# Generated directories
OBJDIR:=objs$(DEBUG_SUFFIX)
ASMOUTDIR:=asmouts$(DEBUG_SUFFIX)
DEPDIR:=deps$(DEBUG_SUFFIX)

# Directories to search, specified at the top of this file
export VPATH	:=	\
	$(foreach DIR,$(BINARY_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(CXX_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(S_DIRS),$(CURDIR)/$(DIR)) \

BIN_SOURCES:=$(foreach DIR,$(BINARY_DIRS),$(notdir $(wildcard $(DIR)/*.bin)))
BIN_OFILES:=$(BIN_SOURCES:%.bin=$(OBJDIR)/%.o) 
BIN_PFILES:=$(BIN_SOURCES:%.bin=$(DEPDIR)/%.P) 
 


CXX_SOURCES:=$(foreach DIR,$(CXX_DIRS),$(notdir $(wildcard $(DIR)/*.cpp)))
CXX_OFILES:=$(CXX_SOURCES:%.cpp=$(OBJDIR)/%.o) 
CXX_PFILES:=$(CXX_SOURCES:%.cpp=$(DEPDIR)/%.P) 
 
# Assembly source code generated by gcc/g++
CXX_ASMOUTS:=$(CXX_SOURCES:%.cpp=$(ASMOUTDIR)/%.s)


S_SOURCES:=$(foreach DIR,$(S_DIRS),$(notdir $(wildcard $(DIR)/*.s)))
S_OFILES:=$(S_SOURCES:%.s=$(OBJDIR)/%.o) 
S_PFILES:=$(S_SOURCES:%.s=$(DEPDIR)/%.P) 
 

# Compiler-generated files
# OFILES are object code files (extension .o)
OFILES:=$(BIN_OFILES) $(CXX_OFILES) $(S_OFILES) 
# PFILES are used for automatic dependency generation
PFILES:=$(BIN_PFILES) $(CXX_PFILES) $(S_PFILES) 
ASMOUTS:=$(CXX_ASMOUTS) $(C_ASMOUTS)



all : all_pre $(OFILES)
	$(LD) $(OBJDIR)/*.o -o $(PROJ).elf $(LD_FLAGS) -Wl,-M > linker_map.txt
	$(OBJCOPY) -O binary -S -g -R .iwram -R .sram $(PROJ).elf $(PROJ).gba
	./do_gbafix.sh

# all_objs is ENTIRELY optional.
all_objs : all_pre $(OFILES)
	@#

do_asmouts : all_pre all_pre_asmout $(ASMOUTS)
	@#

all_pre :
	mkdir -p $(OBJDIR) $(DEPDIR)

all_pre_asmout :
	mkdir -p $(ASMOUTDIR)

$(BIN_OFILES) : $(OBJDIR)/%.o : %.bin
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

#¯\(°_o)/¯

.PHONY : clean
clean :
	rm -rfv $(OBJDIR) $(DEPDIR) $(ASMOUTDIR) $(PREPROCDIR) $(PROJ) tags *.taghl gmon.out

# Flags for make disassemble*
DISASSEMBLE_FLAGS:=$(DISASSEMBLE_BASE_FLAGS) -C -d 
DISASSEMBLE_ALL_FLAGS:=$(DISASSEMBLE_BASE_FLAGS) -C -D 

DISASSEMBLE_2_FLAGS:=$(DISASSEMBLE_BASE_FLAGS) -C -S -l -d 
DISASSEMBLE_ALL_2_FLAGS:=$(DISASSEMBLE_BASE_FLAGS) -C -S -l -D 

.PHONY : disassemble
disassemble :
	$(OBJDUMP) $(DISASSEMBLE_FLAGS) $(PROJ)

.PHONY : disassemble_all
disassemble_all :
	$(OBJDUMP) $(DISASSEMBLE_ALL_FLAGS) $(PROJ)


.PHONY : disassemble_2
disassemble_2 :
	$(OBJDUMP) $(DISASSEMBLE_2_FLAGS) $(PROJ)

.PHONY : disassemble_all_2
disassemble_all_2 :
	$(OBJDUMP) $(DISASSEMBLE_ALL_2_FLAGS) $(PROJ)
