// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef attribute_defines_hpp
#define attribute_defines_hpp


/* ---- #defines for Sections ---- */

// Example:  __attribute__((_EWRAM))
// Another example:  __attribute__((_EWRAM, _ALIGN4))

// #defines for putting INITIAILZED stuff in EWRAM and IWRAM
#define _EWRAM section(".data")
#define _IWRAM section(".iwram_data")


#define PPCAT_NX(a, b) a ## b
#define PPCAT(a, b) PPCAT_NX(a, b)
#define STRINGIZE_NX(a) #a
#define STRINGIZE(a) STRINGIZE_NX(a)

// EWRAM data linker overlay
#define _EWRAM_OVERLAY(num) section(STRINGIZE(PPCAT(.data, num)))

// IWRAM data linker overlay
#define _IWRAM_OVERLAY(num) section(STRINGIZE(PPCAT(.iwram_data, num)))



// #defines for UNITIALIZED global variables That go into EWRAM, IWRAM,
// and SRAM
#define _BSS section(".bss")


// BSS linker overlay
//#define _BSS_OVERLAY(num) section(".bss" #num)
#define _BSS_OVERLAY(num) section(STRINGIZE(PPCAT(.bss,num)))




#define _IWRAM_BSS section(".iwram_bss")


// IWRAM BSS linker overlay
#define _IWRAM_BSS_OVERLAY(num) section(STRINGIZE(PPCAT(.iwram_bss,num)))


#define _SRAM section(".sram")


// #defines for putting stuff in the code (sections for EWRAM and IWRAM)
#define _EWRAM_CODE section(".ewram_code")
#define _IWRAM_CODE section(".iwram_code")


// EWRAM CODE linker overlay
#define _EWRAM_CODE_OVERLAY(num) section(STRINGIZE(PPCAT(.ewram_code, \
	num)))

// IWRAM CODE linker overlay
#define _IWRAM_CODE_OVERLAY(num) section(STRINGIZE(PPCAT(.iwram_code, \
	num)))



// Linker overlay stuffs
#define _TITLE_SCREEN_OVERLAY_NUM 0
#define _OVERWORLD_OVERLAY_NUM 1
#define _IN_LEVEL_OVERLAY_NUM 2



#define _TITLE_SCREEN_EWRAM _EWRAM_OVERLAY(_TITLE_SCREEN_OVERLAY_NUM)
#define _TITLE_SCREEN_IWRAM _IWRAM_OVERLAY(_TITLE_SCREEN_OVERLAY_NUM)
#define _TITLE_SCREEN_BSS _BSS_OVERLAY(_TITLE_SCREEN_OVERLAY_NUM)
#define _TITLE_SCREEN_IWRAM_BSS \
	_IWRAM_BSS_OVERLAY(_TITLE_SCREEN_OVERLAY_NUM)
#define _TITLE_SCREEN_EWRAM_CODE \
	_EWRAM_CODE_OVERLAY(_TITLE_SCREEN_OVERLAY_NUM)
#define _TITLE_SCREEN_IWRAM_CODE \
	_IWRAM_CODE_OVERLAY(_TITLE_SCREEN_OVERLAY_NUM)


#define _OVERWORLD_EWRAM _EWRAM_OVERLAY(_OVERWORLD_OVERLAY_NUM)
#define _OVERWORLD_IWRAM _IWRAM_OVERLAY(_OVERWORLD_OVERLAY_NUM)
#define _OVERWORLD_BSS _BSS_OVERLAY(_OVERWORLD_OVERLAY_NUM)
#define _OVERWORLD_IWRAM_BSS \
	_IWRAM_BSS_OVERLAY(_OVERWORLD_OVERLAY_NUM)
#define _OVERWORLD_EWRAM_CODE \
	_EWRAM_CODE_OVERLAY(_OVERWORLD_OVERLAY_NUM)
#define _OVERWORLD_IWRAM_CODE \
	_IWRAM_CODE_OVERLAY(_OVERWORLD_OVERLAY_NUM)


#define _IN_LEVEL_EWRAM _EWRAM_OVERLAY(_IN_LEVEL_OVERLAY_NUM)
#define _IN_LEVEL_IWRAM _IWRAM_OVERLAY(_IN_LEVEL_OVERLAY_NUM)
#define _IN_LEVEL_BSS _BSS_OVERLAY(_IN_LEVEL_OVERLAY_NUM)
#define _IN_LEVEL_IWRAM_BSS \
	_IWRAM_BSS_OVERLAY(_IN_LEVEL_OVERLAY_NUM)
#define _IN_LEVEL_EWRAM_CODE \
	_EWRAM_CODE_OVERLAY(_IN_LEVEL_OVERLAY_NUM)
#define _IN_LEVEL_IWRAM_CODE \
	_IWRAM_CODE_OVERLAY(_IN_LEVEL_OVERLAY_NUM)




// Generate ARM-mode code instead of THUMB-mode code
#define _TARGET_ARM target("arm")

// There's a bug That I encountered in GCC (as of 5.3.0) That causes the
// section attribute To be ignored when dealing with template functions.
// By slightly changing linkscript.ld, I was able To trick ld into placing
// template functions with the "hot" attribute into IWRAM.  This has got To
// be a hack of some sort.

// When using an optimization Level less than -O2, the .text.hot section
// does not seem To be generated.  Perhaps there's some -f... flag (or
// flags) That would cause the .text.hot To be generated at less than -O2.
#define _TEXT_HOT_SECTION hot
//#define _TEXT_HOT_SECTION_forCED hot,optimize("O3")

/* ---- End of #defines for Sections ---- */


// Some #defines for aligning structs/classes
#define _ALIGN4 aligned(4)


// A #define for making sure That structs/classes have the exact size of
// all their members combined (USE WITH CAUTION)
#define _PACKED packed


// This Is for C++'s built-in alignment, which finally Exists!
#define _ALIGNAS_REGULAR alignas(4)


#endif		// attribute_defines_hpp
