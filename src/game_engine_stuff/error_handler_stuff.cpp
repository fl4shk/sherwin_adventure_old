// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 Andrew Clark (FL4SHK).
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


#include "error_handler_stuff.hpp"

//#include "game_manager_class.hpp"
#include "../gba_specific_stuff/bios_function_wrappers.hpp"

namespace sherwin_adventure
{
namespace game_engine
{

//void halt()
//{
//	//GameManager::curr_game_mode = gm_do_halt;
//
//	for (;;)
//	{
//		gba::bios_wait_for_vblank();
//	}
//}

void err(const char* msg)
{
	DebugArrGroup::raw_array_group.err_str = msg;
	//display(msg);

	//halt();

	for (;;)
	{
		gba::bios_wait_for_vblank();
	}
}


}
}
