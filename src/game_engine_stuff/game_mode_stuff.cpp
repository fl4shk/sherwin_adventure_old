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


#include "game_mode_stuff.hpp"
#include "startup_gm_handler_class.hpp"

#include "../general_utility_stuff/debug_vars.hpp"

namespace sherwin_adventure
{
namespace game_engine
{



GameModeHandlerBase::GameModeHandlerBase(GameModeLoader* s_loader)
	: __loader(s_loader)
{
}

GameModeHandlerBase::~GameModeHandlerBase()
{
	//for (size_t i=0; i<__curr_num_subsystems; ++i)
	//{
	//	delete __subsystems.at(i);
	//}
}

//void GameModeHandlerBase::append(std::unique_ptr<Subsystem>&& to_append)
void GameModeHandlerBase::append(Subsystem* to_append)
{
	if (__curr_num_subsystems >= __subsystems.size())
	{
		////DebugArrGroup::write_str_and_inc("GameModeHandlerBase::");
		//show_debug_str_group("TooManySys");
		//halt();

		err("GameModeHandlerBase::append():  Too many subsystems Eek!");
	}

	__subsystems.at(__curr_num_subsystems++) = to_append;
}

GameModeLoader::GameModeLoader()
{
	//__curr_handler.reset(new StartupGmHandler());
}


}
}

