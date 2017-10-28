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


//_IN_LEVEL_EWRAM_SECTION_ROM_START
//_IN_LEVEL_EWRAM_SECTION_EWRAM_START
//_IN_LEVEL_EWRAM_SECTION_SIZE
//
//_IN_LEVEL_IWRAM_SECTION_ROM_START
//_IN_LEVEL_IWRAM_SECTION_IWRAM_START
//_IN_LEVEL_IWRAM_SECTION_SIZE
//
//_IN_LEVEL_BSS_SECTION_START
//_IN_LEVEL_BSS_SECTION_SIZE
//
//_IN_LEVEL_IWRAM_BSS_SECTION_START
//_IN_LEVEL_IWRAM_BSS_SECTION_SIZE
//
//_IN_LEVEL_SRAM_SECTION_START
//_IN_LEVEL_SRAM_SECTION_SIZE
//
//_IN_LEVEL_EWRAM_CODE_ROM_START
//_IN_LEVEL_EWRAM_CODE_EWRAM_START
//_IN_LEVEL_EWRAM_CODE_SECTION_SIZE
//
//_IN_LEVEL_IWRAM_CODE_ROM_START
//_IN_LEVEL_IWRAM_CODE_IWRAM_START
//_IN_LEVEL_IWRAM_CODE_SECTION_SIZE


namespace sherwin_adventure
{
namespace overlay
{

void OverlayLoader::load(OverlayNum n_overlay_num)
{
	__overlay_num = n_overlay_num;

	switch (overlay_num())
	{
		case OverlayNum::TitleScreen:
			//memcpy(__iwram_data0_load, __iwram_data)
			break;

		case OverlayNum::OverworldLoad:
			
			break;

		case OverlayNum::InOverworld:
			
			break;

		case OverlayNum::LevelLoad:
			
			break;

		case OverlayNum::InLevel:
			
			break;

		default:
			game_engine::halt();
			break;
	}

}

}
}
