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


#ifndef game_mode_stuff_hpp
#define game_mode_stuff_hpp

#include <array>
#include <memory>

#include "../misc_includes.hpp"
#include "overlay_loader_stuff.hpp"
#include "../general_utility_stuff/free_list_allocator_base_class.hpp"

namespace sherwin_adventure
{
namespace game_engine
{


// Abstract base class for a so-called "subsystem" which is an
// organizational tool to allow connecting together pieces of the game
// engine.
class Subsystem
{
public:		// functions
	virtual void iterate() = 0;
} __attribute__((_align4));





// Base class for a handler of a particular game mode (title screen, 
// in the overworld, loading a level, etc.)
class GameModeHandler
{
public:		// constants
	// I don't think there will be more than 20 possible subsystems active
	// at once.  I'll change this later if deemed necessary.
	static constexpr size_t max_num_subsystems = 20;

protected:		// variables
	size_t __num_subsystems = 0;

	// It's okay to use std::unique_ptr here.
	std::array<std::unique_ptr<Subsystem>, max_num_subsystems>
		__subsystems;


public:		// functions
	GameModeHandler();
	virtual ~GameModeHandler();

} __attribute__((_align4));





// Class that loads game modes
class GameModeLoader
{
private:		// variables
	OverlayLoader __overlay_loader;

public:		// functions
	GameModeLoader();
	// I don't need a destructor for this class



private:		// functions
	gen_getter_by_ref(overlay_loader);

} __attribute__((_align4));

}
}


#endif		// game_mode_stuff_hpp
