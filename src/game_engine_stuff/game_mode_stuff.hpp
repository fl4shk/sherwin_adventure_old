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


#ifndef game_engine_stuff__slash__game_mode_stuff_hpp
#define game_engine_stuff__slash__game_mode_stuff_hpp

#include <array>
#include <memory>

#include "../misc_includes.hpp"
#include "overlay_loader_stuff.hpp"
#include "../general_utility_stuff/free_list_allocator_base_class.hpp"

#include "subsystem_stuff.hpp"

namespace sherwin_adventure
{
namespace game_engine
{

class GameModeLoader;


//enum class _alignas_regular GameMode : size_t
//{
//	TitleScreen,
//	OverworldLoad,
//	InOverworld,
//	LevelLoad,
//	InLevel,
//
//	ErrorHandler,
//
//	Lim,
//};


// Base class for a handler of a particular game mode (title screen, 
// in the overworld, loading a level, etc.)
class _alignas_regular GameModeHandlerBase
{
public:		// constants
	// I don't think there will be more than 20 possible subsystems active
	// at once.  I'll change this later if deemed necessary.
	static constexpr size_t max_num_subsystems = 20;

protected:		// variables
	// Current number of allocated subsystems
	size_t __curr_num_subsystems = 0;

	// Don't need __next_subsystems
	//std::array<Subsystem*, max_num_subsystems> __subsystems,
	//	__next_subsystems;
	std::array<Subsystem*, max_num_subsystems> __subsystems;

	GameModeLoader* __loader;

public:		// functions
	GameModeHandlerBase(GameModeLoader* s_loader);
	virtual ~GameModeHandlerBase();

	virtual void run() = 0;

	gen_getter_and_setter_by_val(loader);

protected:		// functions
	void append(Subsystem* to_append);

};




// Class that loads game modes
class _alignas_regular GameModeLoader
{
private:		// variables
	OverlayLoader __overlay_loader;
	GameModeHandlerBase* __curr_handler;

public:		// functions
	GameModeLoader();
	// I don't need a destructor for this class



private:		// functions
	gen_getter_by_ref(overlay_loader);

};

}
}


#endif		// game_engine_stuff__slash__game_mode_stuff_hpp
