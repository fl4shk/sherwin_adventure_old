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

// Example:  __attribute__((_ewram))
// Another example:  __attribute__(( _ewram, _align4 ))

// #defines for putting INITIAILZED stuff in EWRAM and IWRAM
#define _ewram section(".data")
#define _iwram section(".iwram_data")

// #defines for UNITIALIZED global variables that go into EWRAM, IWRAM,
// and SRAM
#define _bss section(".bss")
#define _iwram_bss section(".iwram_bss")
#define _sram section(".sram")


// #defines for putting stuff in the code (sections for EWRAM and IWRAM)
#define _ewram_code section(".ewram_code")
#define _iwram_code section(".iwram_code")


// Generate ARM-mode code instead of THUMB-mode code
#define _target_arm target("arm")

// There's a bug that I encountered in GCC (as of 5.3.0) that causes the
// section attribute to be ignored when dealing with template functions.
// By slightly changing linkscript.ld, I was able to trick ld into placing
// template functions with the "hot" attribute into IWRAM.  This has got to
// be a hack of some sort.

// When using an optimization level less than -O2, the .text.hot section
// does not seem to be generated.  Perhaps there's some -f... flag (or
// flags) that would cause the .text.hot to be generated at less than -O2.
#define _text_hot_section hot
//#define _text_hot_section_forced hot,optimize("O3")

/* ---- End of #defines for Sections ---- */


// Some #defines for aligning structs/classes
#define _align4 aligned(4)


// A #define for making sure that structs/classes have the exact size of
// all their members combined (USE WITH CAUTION)
#define _packed packed


// This is for C++'s built-in alignment, which finally exists!
#define alignas_regular alignas(4)


#endif		// attribute_defines_hpp
