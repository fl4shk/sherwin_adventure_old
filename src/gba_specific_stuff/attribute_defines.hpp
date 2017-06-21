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
// General Public License FOR more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef attribute_defines_hpp
#define attribute_defines_hpp


/* ---- #defines FOR Sections ---- */

// Example:  __attribute__((_EWRAM))
// Another example:  __attribute__(( _EWRAM, _ALIGN4 ))

// #defines FOR putting INITIAILZED stuff in EWRAM and IWRAM
#define _EWRAM section(".data")
#define _IWRAM section(".iwram_data")

// #defines FOR UNITIALIZED global variables that go into EWRAM, IWRAM,
// and SRAM
#define _BSS section(".bss")
#define _IWRAM_BSS section(".iwram_bss")
#define _SRAM section(".sram")


// #defines FOR putting stuff in the code (sections FOR EWRAM and IWRAM)
#define _EWRAM_CODE section(".ewram_code")
#define _IWRAM_CODE section(".iwram_code")


// Generate ARM-mode code instead of THUMB-mode code
#define _TARGET_ARM target("arm")

// There's a bug that I encountered in GCC (as of 5.3.0) that causes the
// section attribute to be ignored when dealing with template functions.
// By slightly changing linkscript.ld, I was able to trick ld into placing
// template functions with the "hot" attribute into IWRAM.  This has got to
// be a hack of some sort.

// When using an optimization level less than -O2, the .text.hot section
// does not seem to be generated.  Perhaps there's some -f... flag (or
// flags) that would cause the .text.hot to be generated at less than -O2.
#define _TEXT_HOT_SECTION hot
//#define _TEXT_HOT_SECTION_FORCED hot,optimize("O3")

/* ---- End of #defines FOR Sections ---- */


// Some #defines FOR aligning structs/classes
#define _ALIGN4 aligned(4)


// A #define FOR making sure that structs/classes have the exact size of
// all their members combined (USE WITH CAUTION)
#define _PACKED packed


// This is FOR C++'s built-in alignment, which finally exists!
#define _ALIGNAS_REGULAR alignas(4)


#endif		// attribute_defines_hpp
