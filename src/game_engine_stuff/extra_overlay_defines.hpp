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


#ifndef game_engine_stuff__slash__extra_overlay_defines_hpp
#define game_engine_stuff__slash__extra_overlay_defines_hpp


// For OverlayLoader::load()
#define _TITLE_SCREEN_EWRAM_SECTION_ROM_START \
	(&_EWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_EWRAM_SECTION_EWRAM_START \
	(&_EWRAM_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_EWRAM_SECTION_END \
	(&_EWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_TITLE_SCREEN))
_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)

#define _TITLE_SCREEN_IWRAM_SECTION_ROM_START \
	(&_IWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_IWRAM_SECTION_IWRAM_START \
	(&_IWRAM_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_IWRAM_SECTION_END \
	(&_IWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_TITLE_SCREEN))
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)

#define _TITLE_SCREEN_BSS_SECTION_START \
	(&_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_BSS_SECTION_END \
	(&_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_TITLE_SCREEN))
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)

#define _TITLE_SCREEN_IWRAM_BSS_SECTION_START \
	(&_IWRAM_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_IWRAM_BSS_SECTION_END \
	(&_IWRAM_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_TITLE_SCREEN))
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)

#define _TITLE_SCREEN_SRAM_SECTION_START \
	(&_SRAM_OVERLAY_SECTION_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_SRAM_SECTION_END \
	(&_SRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_TITLE_SCREEN))
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)

#define _TITLE_SCREEN_EWRAM_CODE_ROM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_EWRAM_CODE_EWRAM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_EWRAM_CODE_SECTION_END \
	(&_EWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_TITLE_SCREEN))
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)

#define _TITLE_SCREEN_IWRAM_CODE_ROM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_IWRAM_CODE_IWRAM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_TITLE_SCREEN))
#define _TITLE_SCREEN_IWRAM_CODE_SECTION_END \
	(&_IWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_TITLE_SCREEN))
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_TITLE_SCREEN)


// For OverlayLoader::load()
#define _OVERWORLD_LOAD_EWRAM_SECTION_ROM_START \
	(&_EWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_EWRAM_SECTION_EWRAM_START \
	(&_EWRAM_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_EWRAM_SECTION_END \
	(&_EWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_OVERWORLD_LOAD))
_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _OVERWORLD_LOAD_IWRAM_SECTION_ROM_START \
	(&_IWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_IWRAM_SECTION_IWRAM_START \
	(&_IWRAM_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_IWRAM_SECTION_END \
	(&_IWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_OVERWORLD_LOAD))
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _OVERWORLD_LOAD_BSS_SECTION_START \
	(&_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_BSS_SECTION_END \
	(&_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_OVERWORLD_LOAD))
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _OVERWORLD_LOAD_IWRAM_BSS_SECTION_START \
	(&_IWRAM_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_IWRAM_BSS_SECTION_END \
	(&_IWRAM_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_OVERWORLD_LOAD))
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _OVERWORLD_LOAD_SRAM_SECTION_START \
	(&_SRAM_OVERLAY_SECTION_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_SRAM_SECTION_END \
	(&_SRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_OVERWORLD_LOAD))
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _OVERWORLD_LOAD_EWRAM_CODE_ROM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_EWRAM_CODE_EWRAM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_EWRAM_CODE_SECTION_END \
	(&_EWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_OVERWORLD_LOAD))
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)

#define _OVERWORLD_LOAD_IWRAM_CODE_ROM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_IWRAM_CODE_IWRAM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_OVERWORLD_LOAD))
#define _OVERWORLD_LOAD_IWRAM_CODE_SECTION_END \
	(&_IWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_OVERWORLD_LOAD))
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_OVERWORLD_LOAD)


// For OverlayLoader::load()
#define _IN_OVERWORLD_EWRAM_SECTION_ROM_START \
	(&_EWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_EWRAM_SECTION_EWRAM_START \
	(&_EWRAM_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_EWRAM_SECTION_END \
	(&_EWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_OVERWORLD))
_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)

#define _IN_OVERWORLD_IWRAM_SECTION_ROM_START \
	(&_IWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_IWRAM_SECTION_IWRAM_START \
	(&_IWRAM_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_IWRAM_SECTION_END \
	(&_IWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_OVERWORLD))
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)

#define _IN_OVERWORLD_BSS_SECTION_START \
	(&_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_BSS_SECTION_END \
	(&_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_OVERWORLD))
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)

#define _IN_OVERWORLD_IWRAM_BSS_SECTION_START \
	(&_IWRAM_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_IWRAM_BSS_SECTION_END \
	(&_IWRAM_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_OVERWORLD))
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)

#define _IN_OVERWORLD_SRAM_SECTION_START \
	(&_SRAM_OVERLAY_SECTION_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_SRAM_SECTION_END \
	(&_SRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_OVERWORLD))
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)

#define _IN_OVERWORLD_EWRAM_CODE_ROM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_EWRAM_CODE_EWRAM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_EWRAM_CODE_SECTION_END \
	(&_EWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_OVERWORLD))
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)

#define _IN_OVERWORLD_IWRAM_CODE_ROM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_IWRAM_CODE_IWRAM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_IN_OVERWORLD))
#define _IN_OVERWORLD_IWRAM_CODE_SECTION_END \
	(&_IWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_OVERWORLD))
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_OVERWORLD)


// For OverlayLoader::load()
#define _LEVEL_LOAD_EWRAM_SECTION_ROM_START \
	(&_EWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_EWRAM_SECTION_EWRAM_START \
	(&_EWRAM_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_EWRAM_SECTION_END \
	(&_EWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_LEVEL_LOAD))
_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)

#define _LEVEL_LOAD_IWRAM_SECTION_ROM_START \
	(&_IWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_IWRAM_SECTION_IWRAM_START \
	(&_IWRAM_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_IWRAM_SECTION_END \
	(&_IWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_LEVEL_LOAD))
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)

#define _LEVEL_LOAD_BSS_SECTION_START \
	(&_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_BSS_SECTION_END \
	(&_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_LEVEL_LOAD))
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)

#define _LEVEL_LOAD_IWRAM_BSS_SECTION_START \
	(&_IWRAM_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_IWRAM_BSS_SECTION_END \
	(&_IWRAM_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_LEVEL_LOAD))
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)

#define _LEVEL_LOAD_SRAM_SECTION_START \
	(&_SRAM_OVERLAY_SECTION_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_SRAM_SECTION_END \
	(&_SRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_LEVEL_LOAD))
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)

#define _LEVEL_LOAD_EWRAM_CODE_ROM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_EWRAM_CODE_EWRAM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_EWRAM_CODE_SECTION_END \
	(&_EWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_LEVEL_LOAD))
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)

#define _LEVEL_LOAD_IWRAM_CODE_ROM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_IWRAM_CODE_IWRAM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_LEVEL_LOAD))
#define _LEVEL_LOAD_IWRAM_CODE_SECTION_END \
	(&_IWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_LEVEL_LOAD))
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_LEVEL_LOAD)


// For OverlayLoader::load()
#define _IN_LEVEL_EWRAM_SECTION_ROM_START \
	(&_EWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_EWRAM_SECTION_EWRAM_START \
	(&_EWRAM_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_EWRAM_SECTION_END \
	(&_EWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_LEVEL))
_EXPOSE_EWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)

#define _IN_LEVEL_IWRAM_SECTION_ROM_START \
	(&_IWRAM_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_IWRAM_SECTION_IWRAM_START \
	(&_IWRAM_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_IWRAM_SECTION_END \
	(&_IWRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_LEVEL))
_EXPOSE_IWRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)

#define _IN_LEVEL_BSS_SECTION_START \
	(&_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_BSS_SECTION_END \
	(&_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_LEVEL))
_EXPOSE_BSS_OVERLAY(_OVERLAY_NUM_IN_LEVEL)

#define _IN_LEVEL_IWRAM_BSS_SECTION_START \
	(&_IWRAM_BSS_OVERLAY_SECTION_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_IWRAM_BSS_SECTION_END \
	(&_IWRAM_BSS_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_LEVEL))
_EXPOSE_IWRAM_BSS_OVERLAY(_OVERLAY_NUM_IN_LEVEL)

#define _IN_LEVEL_SRAM_SECTION_START \
	(&_SRAM_OVERLAY_SECTION_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_SRAM_SECTION_END \
	(&_SRAM_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_LEVEL))
_EXPOSE_SRAM_OVERLAY(_OVERLAY_NUM_IN_LEVEL)

#define _IN_LEVEL_EWRAM_CODE_ROM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_EWRAM_CODE_EWRAM_START \
	(&_EWRAM_CODE_OVERLAY_SECTION_EWRAM_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_EWRAM_CODE_SECTION_END \
	(&_EWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_LEVEL))
_EXPOSE_EWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_LEVEL)

#define _IN_LEVEL_IWRAM_CODE_ROM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_ROM_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_IWRAM_CODE_IWRAM_START \
	(&_IWRAM_CODE_OVERLAY_SECTION_IWRAM_START(_OVERLAY_NUM_IN_LEVEL))
#define _IN_LEVEL_IWRAM_CODE_SECTION_END \
	(&_IWRAM_CODE_OVERLAY_SECTION_END(_OVERLAY_NUM_IN_LEVEL))
_EXPOSE_IWRAM_CODE_OVERLAY(_OVERLAY_NUM_IN_LEVEL)



#endif		// game_engine_stuff__slash__extra_overlay_defines_hpp
