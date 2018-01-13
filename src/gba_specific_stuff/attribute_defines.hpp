// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andrew Clark (FL4SHK).
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


#ifndef gba_specific_stuff__slash__attribute_defines_hpp
#define gba_specific_stuff__slash__attribute_defines_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "../namespace_using.hpp"


// Generate ARM-mode code instead of THUMB-mode code
#define _target_arm gnu::target("arm")

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
//#define _align4 gnu::aligned(4)


// A #define for making sure That structs/classes have the exact size of
// all their members combined (USE WITH CAUTION)
#define _packed gnu::packed


// This Is for C++'s built-in alignment, which finally Exists!
#define _alignas_regular alignas(4)




/* ---- #defines for Sections ---- */

// Example:  [[_ewram]]

// #defines for putting INITIAILZED stuff in EWRAM and IWRAM
#define _ewram gnu::section(".data")
#define _iwram gnu::section(".iwram_data")


// #defines for UNITIALIZED global variables That go into EWRAM, IWRAM,
// and SRAM
#define _bss gnu::section(".bss")

#define _iwram_bss gnu::section(".iwram_bss")


// Cart RAM
#define _sram gnu::section(".sram")


// #defines for putting stuff in the code (sections for EWRAM and IWRAM)
#define _ewram_code gnu::section(".ewram_code")
#define _iwram_code gnu::section(".iwram_code")


#include "overlay_boilerplate_defines.hpp"


// Linker overlay stuffs
#define _OVERLAY_NUM_STARTUP 0
#define _OVERLAY_NUM_TITLE_SCREEN 1
#define _OVERLAY_NUM_OVERWORLD_LOAD 2
#define _OVERLAY_NUM_IN_OVERWORLD 3
#define _OVERLAY_NUM_LEVEL_LOAD 4
#define _OVERLAY_NUM_IN_LEVEL 5
//#define _CREDITS_LOAD_OVERLAY_NUM 7
//#define _CREDITS_OVERLAY_NUM 8

namespace sherwin_adventure
{
namespace game_engine
{

enum class OverlayNum : size_t
{
	Startup = _OVERLAY_NUM_STARTUP,
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
#define _startup_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_STARTUP)
#define _startup_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_STARTUP)
#define _startup_bss _BSS_OVERLAY(_OVERLAY_NUM_STARTUP)
#define _startup_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_STARTUP)
#define _startup_sram _SRAM_OVERLAY(_OVERLAY_NUM_STARTUP)
#define _startup_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_STARTUP)
#define _startup_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_STARTUP)

_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_STARTUP)
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_STARTUP)
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_STARTUP)
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_STARTUP)
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_STARTUP)
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_STARTUP)
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_STARTUP)





// These are what will actually be used
#define _title_screen_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_bss _BSS_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_sram _SRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
#define _title_screen_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)

_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)





// These are what will actually be used
#define _overworld_load_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_bss _BSS_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_sram _SRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
#define _overworld_load_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)

_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)





// These are what will actually be used
#define _in_overworld_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_bss _BSS_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_sram _SRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
#define _in_overworld_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)

_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)




// These are what will actually be used
#define _level_load_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_bss _BSS_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_sram _SRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
#define _level_load_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)

_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)






// These are what will actually be used
#define _in_level_ewram _EWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_iwram _IWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_bss _BSS_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_iwram_bss \
	_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_sram _SRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_ewram_code \
	_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
#define _in_level_iwram_code \
	_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_LEVEL)

_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_LEVEL)
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_LEVEL)


#endif		// gba_specific_stuff__slash__attribute_defines_hpp
