ALWAYS_DEBUG_SUFFIX:=_debug

# Comment out or un-comment out the next line to enable profiling stuff to
# be generated
#PROFILE:=yeah do profile

ifdef PROFILE
	PROFILE_FLAGS:=-pg
endif


# Comment out or un-comment out the next line to enable the use of
# arm-none-eabi-gcc and friends for building (mainly intended to be used
# to examine compiler output because I understand ARM7TDMI assembly better than
# any other assembly language, including x86-64 assembly).
#DO_ARM:=yeah do arm



# Comment out or un-comment out the next line to enable debugging stuff to
# be generated
#DEBUG:=yeah do debug

#DEBUG_OPTIMIZATION_LEVEL:=-O0
#DEBUG_OPTIMIZATION_LEVEL:=-Og
DEBUG_OPTIMIZATION_LEVEL:=-O2
#DEBUG_OPTIMIZATION_LEVEL:=-O3

#REGULAR_OPTIMIZATION_LEVEL:=-O1
REGULAR_OPTIMIZATION_LEVEL:=-O2
#REGULAR_OPTIMIZATION_LEVEL:=-O3


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


# Compilers, assemblers, and the linker
ifdef DO_ARM
	PREFIX:=arm-none-eabi-
	EXTRA_BASE_FLAGS:=-mcpu=arm7tdmi -mtune=arm7tdmi -mthumb \
		-mthumb-interwork
else
	PREFIX:=
	EXTRA_BASE_FLAGS:=
endif

CXX:=$(PREFIX)g++
CC:=$(PREFIX)gcc
AS:=$(PREFIX)as
NS:=nasm
LD:=$(PREFIX)g++



## Old debug BASE_FLAGS
##BASE_FLAGS:=-masm=intel -march=native -Wall $(DEBUG_OPTIMIZATION_LEVEL) -g
##BASE_FLAGS:=-masm=intel -Wall $(DEBUG_OPTIMIZATION_LEVEL) -g
#BASE_FLAGS:=$(BASE_FLAGS) $(DEBUG_OPTIMIZATION_LEVEL) $(EXTRA_DEBUG_FLAGS)

## Old regular BASE_FLAGS
##BASE_FLAGS:=-masm=intel -march=native -Wall $(REGULAR_OPTIMIZATION_LEVEL)
##BASE_FLAGS:=-masm=intel -Wall $(REGULAR_OPTIMIZATION_LEVEL)
#BASE_FLAGS:=$(BASE_FLAGS) $(REGULAR_OPTIMIZATION_LEVEL)


## Don't copy this exact thing to every other makefile
#BASE_FLAGS:=-march=native -Wall $(PROFILE_FLAGS)

BASE_FLAGS:=-Wall $(OPTIMIZATION_LEVEL) $(PROFILE_FLAGS) \
	$(EXTRA_BASE_FLAGS) $(EXTRA_DEBUG_FLAGS)



# Compiler, assembler, and linker flags
CXX_FLAGS:=-std=c++17 $(BASE_FLAGS)
C_FLAGS:=-std=c11 $(BASE_FLAGS)
S_FLAGS:=-mnaked-reg #-msyntax=intel
NS_FLAGS:=-f elf64

LD_FLAGS:=-lm $(EXTRA_LD_FLAGS)




# These directories specify where source code files are located.
# Edit these variables if more directories are needed.  Order is C++, C, (GNU) ASM, NASM.
# Separate each entry by spaces.
CXX_DIRS:=$(CURDIR) src
C_DIRS:=$(CXX_DIRS)
S_DIRS:=$(CXX_DIRS) 

# NASM Source Directories
# Note:  NS is a prefix for NASM in all cases
NS_DIRS:=$(CXX_DIRS) 

# End of source directories



# Generated directories
OBJDIR:=objs$(DEBUG_SUFFIX)
ASMOUTDIR:=asmouts$(DEBUG_SUFFIX)
DEPDIR:=deps$(DEBUG_SUFFIX)
OBJDIR_TEMP:=objs_temp$(DEBUG_SUFFIX)
PREPROCDIR:=preprocs$(DEBUG_SUFFIX)


# Source code files
CXX_SOURCES:=$(foreach DIR,$(CXX_DIRS),$(notdir $(wildcard $(DIR)/*.cpp)))
C_SOURCES:=$(foreach DIR,$(C_DIRS),$(notdir $(wildcard $(DIR)/*.c)))
S_SOURCES:=$(foreach DIR,$(S_DIRS),$(notdir $(wildcard $(DIR)/*.s)))
NS_SOURCES:=$(foreach DIR,$(S_DIRS),$(notdir $(wildcard $(DIR)/*.nasm)))


# Directories to search, specified above
export VPATH	:=	$(foreach DIR,$(CXX_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(C_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(S_DIRS),$(CURDIR)/$(DIR)) \
	$(foreach DIR,$(NS_DIRS),$(CURDIR)/$(DIR))


# Object code files
# CXX_OFILES:=$(patsubst %.cpp,$(OBJDIR)/%.o,$(CXX_SOURCES))
# S_OFILES:=$(patsubst %.s,$(OBJDIR)/%.o,$(S_SOURCES))
# NS_OFILES:=$(patsubst %.nasm,$(OBJDIR)/%.o,$(NS_SOURCES))
CXX_OFILES:=$(CXX_SOURCES:%.cpp=$(OBJDIR)/%.o)
C_OFILES:=$(C_SOURCES:%.c=$(OBJDIR)/%.o)
S_OFILES:=$(S_SOURCES:%.s=$(OBJDIR)/%.o)
NS_OFILES:=$(NS_SOURCES:%.nasm=$(OBJDIR)/%.o)
OFILES:=$(CXX_OFILES) $(C_OFILES) $(S_OFILES) $(NS_OFILES)

# Automatically-Generated Dependency Files
# CXX_PFILES:=$(patsubst %.cpp,$(DEPDIR)/%.P,$(CXX_SOURCES))
# S_PFILES:=$(patsubst %.s,$(DEPDIR)/%.P,$(S_SOURCES))
# NS_PFILES:=$(patsubst %.nasm,$(DEPDIR)/%.P,$(NS_SOURCES))
CXX_PFILES:=$(CXX_SOURCES:%.cpp=$(DEPDIR)/%.P)
C_PFILES:=$(C_SOURCES:%.c=$(DEPDIR)/%.P)
S_PFILES:=$(S_SOURCES:%.s=$(DEPDIR)/%.P)
NS_PFILES:=$(NS_SOURCES:%.nasm=$(DEPDIR)/%.P)
PFILES:=$(CXX_PFILES) $(C_PFILES) $(S_PFILES) $(NS_PFILES)


# This is for cleaning object files with no source.
# CXX_OFILES_TEMP:=$(patsubst %.cpp,$(OBJDIR_TEMP)/%.o,$(CXX_SOURCES))
# S_OFILES_TEMP:=$(patsubst %.s,$(OBJDIR_TEMP)/%.o,$(S_SOURCES))
# NS_OFILES_TEMP:=$(patsubst %.nasm,$(OBJDIR_TEMP)/%.o,$(NS_SOURCES))
CXX_OFILES_TEMP:=$(CXX_SOURCES:%.cpp=$(OBJDIR_TEMP)/%.o)
C_OFILES_TEMP:=$(C_SOURCES:%.c=$(OBJDIR_TEMP)/%.o)
S_OFILES_TEMP:=$(S_SOURCES:%.s=$(OBJDIR_TEMP)/%.o)
NS_OFILES_TEMP:=$(NS_SOURCES:%.nasm=$(OBJDIR_TEMP)/%.o)
OFILES_TEMP:=$(CXX_OFILES_TEMP) $(C_OFILES_TEMP) $(S_OFILES_TEMP) $(NS_OFILES_TEMP)


# Assembly source code generated by gcc/g++
#CXX_ASMOUTS:=$(patsubst %.cpp,$(ASMOUTDIR)/%.s,$(CXX_SOURCES))
CXX_ASMOUTS:=$(CXX_SOURCES:%.cpp=$(ASMOUTDIR)/%.s)
ASMOUTS:=$(CXX_ASMOUTS)


# Preprocessed output of only C++ files
#CXX_EFILES:=$(patsubst %.cpp,$(PREPROCDIR)/%.E,$(CXX_SOURCES))
CXX_EFILES:=$(CXX_SOURCES:%.cpp=$(PREPROCDIR)/%.E)
EFILES:=$(CXX_EFILES)



all : all_pre $(OFILES)
	$(LD) $(OBJDIR)/*.o -o $(PROJ).elf $(LD_FLAGS)

# all_objs is ENTIRELY optional.
all_objs : all_pre $(OFILES)
	@#

do_asmouts : all_pre all_pre_asmout $(ASMOUTS)
	@#

all_pre :
	mkdir -p $(OBJDIR) $(DEPDIR)

all_pre_asmout :
	mkdir -p $(ASMOUTDIR)

# This sed script is basically a hack.
sed_script:=$(shell echo "sed -e 's/\#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/'")









# Here's where things get really messy.
$(CXX_OFILES) : $(OBJDIR)/%.o : %.cpp
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
	@$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(OBJDIR)/$*.d

$(C_OFILES) : $(OBJDIR)/%.o : %.c
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CC) $(C_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
	@$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(OBJDIR)/$*.d

# For NASM sources, the dependency generation is somewhat different from
# that of C/C++ sources.
$(NS_OFILES) : $(OBJDIR)/%.o : %.nasm
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Assembling...."
	$(NS) $(NS_FLAGS) $< -o $@ -MD $(DEPDIR)/$*.P


# $(S_OFILES) : $(OBJDIR)/%.o : %.s
# 	@#echo "Generating dependency information for "$@"...."
# 	@echo $@" was updated or has no object file.  (Re)Assembling...."
# 	$(AS) $(S_FLAGS) -MD $(OBJDIR)/$*.d -c $< -o $@
# 	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
# 	@$(sed_script) < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
# 	@rm -f $(OBJDIR)/$*.d
$(S_OFILES) : $(OBJDIR)/%.o : %.s
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Assembling...."
	$(AS) $(S_FLAGS) -MD $(OBJDIR)/$*.d -c $< -o $
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
	rm -rfv $(OBJDIR) $(DEPDIR) $(ASMOUTDIR) $(PREPROCDIR) $(PROJ) tags *.taghl gmon.out *_lut_*.hexdump *_lut_*.bin *.elf

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


