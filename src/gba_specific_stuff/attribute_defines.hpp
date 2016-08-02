// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


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

/* ---- End of #defines for Sections ---- */


// A #define for aligning structs/classes
#define _align4 aligned(4)


// A #define for making sure that structs/classes have the exact size of
// all their members combined (USE WITH CAUTION)
#define _packed packed


#define alignas4 alignas(4)


#endif		// attribute_defines_hpp
