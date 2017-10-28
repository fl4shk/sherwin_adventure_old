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

#include "../general_utility_stuff/misc_types.hpp"
#include "../namespace_using.hpp"


// Generate ARM-mode code instead of THUMB-mode code
#define _target_arm target("arm")

// There's a bug That I encountered in GCC (as of 5.3.0) That causes the
// section attribute To be ignored when dealing with template functions.
// By slightly changing linkscript.ld, I was able To trick ld into placing
// template functions with the "hot" attribute into IWRAM.  This has got To
// be a hack of some sort.

// When using an optimization Level less than -O2, the .text.hot section
// does not seem To be generated.  Perhaps there's some -f... flag (or
// flags) That would cause the .text.hot To be generated at less than -O2.
#define _text_hot_section hot
//#define _text_hot_section_forced hot,optimize("O3")

/* ---- End of #defines for Sections ---- */


// Some #defines for aligning structs/classes
#define _align4 aligned(4)


// A #define for making sure That structs/classes have the exact size of
// all their members combined (USE WITH CAUTION)
#define _packed packed


// This Is for C++'s built-in alignment, which finally Exists!
#define _alignas_regular alignas(4)




/* ---- #defines for Sections ---- */

// Example:  __attribute__((_EWRAM))
// Another example:  __attribute__((_EWRAM, _align4))

// #defines for putting INITIAILZED stuff in EWRAM and IWRAM
#define _ewram section(".data")
#define _iwram section(".iwram_data")


#define PPCAT_NX(a, b) a ## b
#define PPCAT(a, b) PPCAT_NX(a, b)
#define STRINGIZE_NX(a) #a
#define STRINGIZE(a) STRINGIZE_NX(a)

// EWRAM data linker overlay
#define _EWRAM_OVERLAY(num) section(STRINGIZE(PPCAT(.data, num)))
#define _EWRAM_OVERLAY_SECTION_SIZE(num) \
	PPCAT(PPCAT(__data,num),_section_size)
#define _EXPOSE_EWRAM_OVERLAY_SECTION_SIZE(num) \
extern "C" const size_t _EWRAM_OVERLAY_SECTION_SIZE(num);

// IWRAM data linker overlay
#define _IWRAM_OVERLAY(num) section(STRINGIZE(PPCAT(.iwram_data, num)))
#define _IWRAM_OVERLAY_SECTION_SIZE(num) \
	PPCAT(PPCAT(__iwram_data,num),_section_size)
#define _EXPOSE_IWRAM_OVERLAY_SECTION_SIZE(num) \
extern "C" const size_t _IWRAM_OVERLAY_SECTION_SIZE(num);



// #defines for UNITIALIZED global variables That go into EWRAM, IWRAM,
// and SRAM
#define _bss section(".bss")


// BSS linker overlay
//#define _BSS_OVERLAY(num) section(".bss" #num)
#define _BSS_OVERLAY(num) section(STRINGIZE(PPCAT(.bss,num)))
#define _BSS_OVERLAY_SECTION_SIZE(num) \
	PPCAT(PPCAT(__bss,num),_section_size)
#define _EXPOSE_BSS_OVERLAY_SECTION_SIZE(num) \
extern "C" const size_t _BSS_OVERLAY_SECTION_SIZE(num);



#define _iwram_bss section(".iwram_bss")


// IWRAM BSS linker overlay
#define _IWRAM_BSS_OVERLAY(num) section(STRINGIZE(PPCAT(.iwram_bss,num)))
#define _IWRAM_BSS_OVERLAY_SECTION_SIZE(num) \
	PPCAT(PPCAT(__iwram_bss,num),_section_size)
#define _EXPOSE_IWRAM_BSS_OVERLAY_SECTION_SIZE(num) \
extern "C" const size_t _IWRAM_BSS_OVERLAY_SECTION_SIZE(num);


// Cart RAM
#define _sram section(".sram")

// SRAM linker overlay (potentially not necessary at all)
#define _SRAM_OVERLAY(num) section(STRINGIZE(PPCAT(.sram, num)))
#define _SRAM_OVERLAY_SECTION_SIZE(num) \
	PPCAT(PPCAT(__sram,num),_section_size)
#define _EXPOSE_SRAM_OVERLAY_SECTION_SIZE(num) \
extern "C" const size_t _SRAM_OVERLAY_SECTION_SIZE(num);


// #defines for putting stuff in the code (sections for EWRAM and IWRAM)
#define _ewram_code section(".ewram_code")
#define _iwram_code section(".iwram_code")


// EWRAM CODE linker overlay (potentially not necessary at all)
#define _EWRAM_CODE_OVERLAY(num) section(STRINGIZE(PPCAT(.ewram_code, \
	num)))
#define _EWRAM_CODE_OVERLAY_SECTION_SIZE(num) \
	PPCAT(PPCAT(__ewram_code,num),_section_size)
#define _EXPOSE_EWRAM_CODE_OVERLAY_SECTION_SIZE(num) \
extern "C" const size_t _EWRAM_CODE_OVERLAY_SECTION_SIZE(num);

// IWRAM CODE linker overlay
#define _IWRAM_CODE_OVERLAY(num) section(STRINGIZE(PPCAT(.iwram_code, \
	num)))
#define _IWRAM_CODE_OVERLAY_SECTION_SIZE(num) \
	PPCAT(PPCAT(__iwram_code,num),_section_size)
#define _EXPOSE_IWRAM_CODE_OVERLAY_SECTION_SIZE(num) \
extern "C" const size_t _IWRAM_CODE_OVERLAY_SECTION_SIZE(num);



// Linker overlay stuffs
#define _OVERLAY_NUM_TITLE_SCREEN 0
#define _OVERLAY_NUM_OVERWORLD_LOAD 1
#define _OVERLAY_NUM_IN_OVERWORLD 2
#define _OVERLAY_NUM_LEVEL_LOAD 3
#define _OVERLAY_NUM_IN_LEVEL 4
//#define _CREDITS_LOAD_OVERLAY_NUM 5
//#define _CREDITS_OVERLAY_NUM 6

namespace sherwin_adventure
{
namespace overlay
{

enum class OverlayNum : u32
{
	TitleScreen = _OVERLAY_NUM_TITLE_SCREEN,
	OverworldLoad = _OVERLAY_NUM_OVERWORLD_LOAD,
	InOverworld = _OVERLAY_NUM_IN_OVERWORLD,
	LevelLoad = _OVERLAY_NUM_LEVEL_LOAD,
	InLevel = _OVERLAY_NUM_IN_LEVEL,


	// Size
	Lim
};

}
}



// These are what will actually be used
#define _title_screen_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_ewram_section_size \
	_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)

#define _title_screen_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_iwram_section_size \
	_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)

#define _title_screen_bss _BSS_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_bss_section_size \
	_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)

#define _title_screen_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_iwram_bss_section_size \
	_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)

#define _title_screen_sram _SRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_sram_section_size \
	_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)

#define _title_screen_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_ewram_code_section_size \
	_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)

#define _title_screen_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_iwram_code_section_size \
	_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_TITLE_SCREEN)




#define _overworld_load_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_ewram_section_size \
	_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _overworld_load_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_iwram_section_size \
	_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _overworld_load_bss _BSS_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_bss_section_size \
	_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _overworld_load_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_iwram_bss_section_size \
	_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _overworld_load_sram _SRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_sram_section_size \
	_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _overworld_load_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_ewram_code_section_size \
	_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _overworld_load_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_iwram_code_section_size \
	_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_OVERWORLD_LOAD)




//#define _overworld_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_ewram_section_size \
	_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)

#define _in_overworld_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_iwram_section_size \
	_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)

#define _in_overworld_bss _BSS_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_bss_section_size \
	_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)

#define _in_overworld_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_iwram_bss_section_size \
	_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)

#define _in_overworld_sram _SRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_sram_section_size \
	_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)

#define _in_overworld_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_ewram_code_section_size \
	_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)

#define _in_overworld_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_iwram_code_section_size \
	_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_OVERWORLD)


//#define _level_load_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_ewram_section_size \
	_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)

#define _level_load_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_iwram_section_size \
	_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)

#define _level_load_bss _BSS_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_bss_section_size \
	_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)

#define _level_load_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_iwram_bss_section_size \
	_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)

#define _level_load_sram _SRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_sram_section_size \
	_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)

#define _level_load_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_ewram_code_section_size \
	_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)

#define _level_load_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_iwram_code_section_size \
	_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_LEVEL_LOAD)


//#define _in_level_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_ewram_section_size \
	_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_EWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)

#define _in_level_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_iwram_section_size \
	_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_IWRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)

#define _in_level_bss _BSS_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_bss_section_size \
	_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)

#define _in_level_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_iwram_bss_section_size \
	_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_IWRAM_BSS_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)

#define _in_level_sram _SRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_sram_section_size \
	_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_SRAM_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)

#define _in_level_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_ewram_code_section_size \
	_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_EWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)

#define _in_level_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_iwram_code_section_size \
	_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_IWRAM_CODE_OVERLAY_SECTION_SIZE(_OVERLAY_NUM_IN_LEVEL)


#endif		// attribute_defines_hpp
