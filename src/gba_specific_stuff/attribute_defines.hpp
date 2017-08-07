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


// #defines for UNITIALIZED global variables That go into EWRAM, IWRAM,
// and SRAM
#define _BSS section(".bss")

// BSS linker overlay
#define _BSS0 section(".bss0")
#define _BSS1 section(".bss1")
#define _BSS2 section(".bss2")
#define _BSS3 section(".bss3")
#define _BSS4 section(".bss4")
#define _BSS5 section(".bss5")
#define _BSS6 section(".bss6")
#define _BSS7 section(".bss7")


// Specific uses of the BSS linker overlay
#define _TITLE_SCREEN_BSS _BSS0
#define _IN_LEVEL_BSS _BSS1
#define _OVERWORLD_BSS _BSS2


#define _IWRAM_BSS section(".iwram_bss")
#define _SRAM section(".sram")


// #defines for putting stuff in the code (sections for EWRAM and IWRAM)
#define _EWRAM_CODE section(".ewram_code")
#define _IWRAM_CODE section(".iwram_code")


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
