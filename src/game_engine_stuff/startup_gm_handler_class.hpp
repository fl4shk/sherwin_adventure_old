// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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


#ifndef game_engine_stuff__slash__startup_gm_handler_class_hpp
#define game_engine_stuff__slash__startup_gm_handler_class_hpp

#include "game_mode_stuff.hpp"

namespace sherwin_adventure
{
namespace game_engine
{

class StartupGmHandler : public GameModeHandlerBase
{
public:		// classes
	class StartupSubsystem : public Subsystem
	{
	public:		// variables
	public:		// functions
		inline void iterate()
		{
		}
	} __attribute__((_align4));

private:		// variables
	StartupSubsystem* startup_subsystem = nullptr;
	

public:		// functions
	StartupGmHandler(GameModeLoader* s_loader);
	virtual ~StartupGmHandler();
	void run();

private:		// functions
	//inline auto& graphics_subsystem()
	//{
	//}

} __attribute__((_align4));

}
}

#endif		// game_engine_stuff__slash__startup_gm_handler_class_hpp
