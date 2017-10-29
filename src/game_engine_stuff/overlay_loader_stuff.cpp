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


#include "overlay_loader_stuff.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"

#include "extra_overlay_defines.hpp"


namespace sherwin_adventure
{
namespace game_engine
{

void OverlayLoader::load(OverlayNum n_overlay_num)
{
	__overlay_num = n_overlay_num;

	switch (overlay_num())
	{
		case OverlayNum::TitleScreen:
			memcpy32(_TITLE_SCREEN_EWRAM_SECTION_EWRAM_START,
				_TITLE_SCREEN_EWRAM_SECTION_ROM_START,
				((size_t)_TITLE_SCREEN_EWRAM_SECTION_END
				- (size_t)_TITLE_SCREEN_EWRAM_SECTION_EWRAM_START));

			memcpy(_TITLE_SCREEN_IWRAM_SECTION_IWRAM_START,
				_TITLE_SCREEN_IWRAM_SECTION_ROM_START,
				((size_t)_TITLE_SCREEN_IWRAM_SECTION_END
				- (size_t)_TITLE_SCREEN_IWRAM_SECTION_IWRAM_START));

			memset(_TITLE_SCREEN_BSS_SECTION_START, 
				0,
				((size_t)_TITLE_SCREEN_BSS_SECTION_END
				- (size_t)_TITLE_SCREEN_BSS_SECTION_START));

			memset(_TITLE_SCREEN_IWRAM_BSS_SECTION_START, 
				0,
				((size_t)_TITLE_SCREEN_IWRAM_BSS_SECTION_END
				- (size_t)_TITLE_SCREEN_IWRAM_BSS_SECTION_START));

			memfill8(_TITLE_SCREEN_SRAM_SECTION_START, 
				0,
				((size_t)_TITLE_SCREEN_SRAM_SECTION_END
				- (size_t)_TITLE_SCREEN_SRAM_SECTION_START));

			memcpy(_TITLE_SCREEN_EWRAM_CODE_EWRAM_START,
				_TITLE_SCREEN_EWRAM_CODE_ROM_START,
				((size_t)_TITLE_SCREEN_EWRAM_CODE_SECTION_END
				- (size_t)_TITLE_SCREEN_EWRAM_CODE_EWRAM_START));

			memcpy(_TITLE_SCREEN_IWRAM_CODE_IWRAM_START,
				_TITLE_SCREEN_IWRAM_CODE_ROM_START,
				((size_t)_TITLE_SCREEN_IWRAM_CODE_SECTION_END
				- (size_t)_TITLE_SCREEN_IWRAM_CODE_IWRAM_START));

			break;

		case OverlayNum::OverworldLoad:
			memcpy(_OVERWORLD_LOAD_EWRAM_SECTION_EWRAM_START,
				_OVERWORLD_LOAD_EWRAM_SECTION_ROM_START,
				((size_t)_OVERWORLD_LOAD_EWRAM_SECTION_END
				- (size_t)_OVERWORLD_LOAD_EWRAM_SECTION_EWRAM_START));

			memcpy(_OVERWORLD_LOAD_IWRAM_SECTION_IWRAM_START,
				_OVERWORLD_LOAD_IWRAM_SECTION_ROM_START,
				((size_t)_OVERWORLD_LOAD_IWRAM_SECTION_END
				- (size_t)_OVERWORLD_LOAD_IWRAM_SECTION_IWRAM_START));

			memset(_OVERWORLD_LOAD_BSS_SECTION_START, 
				0,
				((size_t)_OVERWORLD_LOAD_BSS_SECTION_END
				- (size_t)_OVERWORLD_LOAD_BSS_SECTION_START));

			memset(_OVERWORLD_LOAD_IWRAM_BSS_SECTION_START, 
				0,
				((size_t)_OVERWORLD_LOAD_IWRAM_BSS_SECTION_END
				- (size_t)_OVERWORLD_LOAD_IWRAM_BSS_SECTION_START));

			memfill8(_OVERWORLD_LOAD_SRAM_SECTION_START, 
				0,
				((size_t)_OVERWORLD_LOAD_SRAM_SECTION_END
				- (size_t)_OVERWORLD_LOAD_SRAM_SECTION_START));

			memcpy(_OVERWORLD_LOAD_EWRAM_CODE_EWRAM_START,
				_OVERWORLD_LOAD_EWRAM_CODE_ROM_START,
				((size_t)_OVERWORLD_LOAD_EWRAM_CODE_SECTION_END
				- (size_t)_OVERWORLD_LOAD_EWRAM_CODE_EWRAM_START));

			memcpy(_OVERWORLD_LOAD_IWRAM_CODE_IWRAM_START,
				_OVERWORLD_LOAD_IWRAM_CODE_ROM_START,
				((size_t)_OVERWORLD_LOAD_IWRAM_CODE_SECTION_END
				- (size_t)_OVERWORLD_LOAD_IWRAM_CODE_IWRAM_START));

			break;

		case OverlayNum::InOverworld:
			memcpy(_IN_OVERWORLD_EWRAM_SECTION_EWRAM_START,
				_IN_OVERWORLD_EWRAM_SECTION_ROM_START,
				((size_t)_IN_OVERWORLD_EWRAM_SECTION_END
				- (size_t)_IN_OVERWORLD_EWRAM_SECTION_EWRAM_START));

			memcpy(_IN_OVERWORLD_IWRAM_SECTION_IWRAM_START,
				_IN_OVERWORLD_IWRAM_SECTION_ROM_START,
				((size_t)_IN_OVERWORLD_IWRAM_SECTION_END
				- (size_t)_IN_OVERWORLD_IWRAM_SECTION_IWRAM_START));

			memset(_IN_OVERWORLD_BSS_SECTION_START, 
				0,
				((size_t)_IN_OVERWORLD_BSS_SECTION_END
				- (size_t)_IN_OVERWORLD_BSS_SECTION_START));

			memset(_IN_OVERWORLD_IWRAM_BSS_SECTION_START, 
				0,
				((size_t)_IN_OVERWORLD_IWRAM_BSS_SECTION_END
				- (size_t)_IN_OVERWORLD_IWRAM_BSS_SECTION_START));

			memfill8(_IN_OVERWORLD_SRAM_SECTION_START, 
				0,
				((size_t)_IN_OVERWORLD_SRAM_SECTION_END
				- (size_t)_IN_OVERWORLD_SRAM_SECTION_START));

			memcpy(_IN_OVERWORLD_EWRAM_CODE_EWRAM_START,
				_IN_OVERWORLD_EWRAM_CODE_ROM_START,
				((size_t)_IN_OVERWORLD_EWRAM_CODE_SECTION_END
				- (size_t)_IN_OVERWORLD_EWRAM_CODE_EWRAM_START));

			memcpy(_IN_OVERWORLD_IWRAM_CODE_IWRAM_START,
				_IN_OVERWORLD_IWRAM_CODE_ROM_START,
				((size_t)_IN_OVERWORLD_IWRAM_CODE_SECTION_END
				- (size_t)_IN_OVERWORLD_IWRAM_CODE_IWRAM_START));

			break;

		case OverlayNum::LevelLoad:
			memcpy(_LEVEL_LOAD_EWRAM_SECTION_EWRAM_START,
				_LEVEL_LOAD_EWRAM_SECTION_ROM_START,
				((size_t)_LEVEL_LOAD_EWRAM_SECTION_END
				- (size_t)_LEVEL_LOAD_EWRAM_SECTION_EWRAM_START));

			memcpy(_LEVEL_LOAD_IWRAM_SECTION_IWRAM_START,
				_LEVEL_LOAD_IWRAM_SECTION_ROM_START,
				((size_t)_LEVEL_LOAD_IWRAM_SECTION_END
				- (size_t)_LEVEL_LOAD_IWRAM_SECTION_IWRAM_START));

			memset(_LEVEL_LOAD_BSS_SECTION_START, 
				0,
				((size_t)_LEVEL_LOAD_BSS_SECTION_END
				- (size_t)_LEVEL_LOAD_BSS_SECTION_START));

			memset(_LEVEL_LOAD_IWRAM_BSS_SECTION_START, 
				0,
				((size_t)_LEVEL_LOAD_IWRAM_BSS_SECTION_END
				- (size_t)_LEVEL_LOAD_IWRAM_BSS_SECTION_START));

			memfill8(_LEVEL_LOAD_SRAM_SECTION_START, 
				0,
				((size_t)_LEVEL_LOAD_SRAM_SECTION_END
				- (size_t)_LEVEL_LOAD_SRAM_SECTION_START));

			memcpy(_LEVEL_LOAD_EWRAM_CODE_EWRAM_START,
				_LEVEL_LOAD_EWRAM_CODE_ROM_START,
				((size_t)_LEVEL_LOAD_EWRAM_CODE_SECTION_END
				- (size_t)_LEVEL_LOAD_EWRAM_CODE_EWRAM_START));

			memcpy(_LEVEL_LOAD_IWRAM_CODE_IWRAM_START,
				_LEVEL_LOAD_IWRAM_CODE_ROM_START,
				((size_t)_LEVEL_LOAD_IWRAM_CODE_SECTION_END
				- (size_t)_LEVEL_LOAD_IWRAM_CODE_IWRAM_START));

			break;

		case OverlayNum::InLevel:
			memcpy(_IN_LEVEL_EWRAM_SECTION_EWRAM_START,
				_IN_LEVEL_EWRAM_SECTION_ROM_START,
				((size_t)_IN_LEVEL_EWRAM_SECTION_END
				- (size_t)_IN_LEVEL_EWRAM_SECTION_EWRAM_START));

			memcpy(_IN_LEVEL_IWRAM_SECTION_IWRAM_START,
				_IN_LEVEL_IWRAM_SECTION_ROM_START,
				((size_t)_IN_LEVEL_IWRAM_SECTION_END
				- (size_t)_IN_LEVEL_IWRAM_SECTION_IWRAM_START));

			memset(_IN_LEVEL_BSS_SECTION_START, 
				0,
				((size_t)_IN_LEVEL_BSS_SECTION_END
				- (size_t)_IN_LEVEL_BSS_SECTION_START));

			memset(_IN_LEVEL_IWRAM_BSS_SECTION_START, 
				0,
				((size_t)_IN_LEVEL_IWRAM_BSS_SECTION_END
				- (size_t)_IN_LEVEL_IWRAM_BSS_SECTION_START));

			memfill8(_IN_LEVEL_SRAM_SECTION_START, 
				0,
				((size_t)_IN_LEVEL_SRAM_SECTION_END
				- (size_t)_IN_LEVEL_SRAM_SECTION_START));

			memcpy(_IN_LEVEL_EWRAM_CODE_EWRAM_START,
				_IN_LEVEL_EWRAM_CODE_ROM_START,
				((size_t)_IN_LEVEL_EWRAM_CODE_SECTION_END
				- (size_t)_IN_LEVEL_EWRAM_CODE_EWRAM_START));

			memcpy(_IN_LEVEL_IWRAM_CODE_IWRAM_START,
				_IN_LEVEL_IWRAM_CODE_ROM_START,
				((size_t)_IN_LEVEL_IWRAM_CODE_SECTION_END
				- (size_t)_IN_LEVEL_IWRAM_CODE_IWRAM_START));

			break;

		default:
			game_engine::halt();
			break;
	}

}

}
}
