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


#ifndef game_engine_stuff__slash__overlay_loader_stuff_hpp
#define game_engine_stuff__slash__overlay_loader_stuff_hpp


#include "../namespace_using.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "../general_utility_stuff/gen_getter_setter_defines.hpp"
#include "error_handler_stuff.hpp"

namespace sherwin_adventure
{
namespace game_engine
{


class _alignas_regular OverlayLoader
{
private:		// variables
	OverlayNum __overlay_num;

public:		// functions
	inline OverlayLoader()
	{
		load(OverlayNum::Startup);
	}

	// This function doesn't need a lot of speed, and thus it will be run
	// from ROM.
	void load(OverlayNum n_overlay_num);
	//[[_target_arm]] void load(OverlayNum n_overlay_num);

	gen_getter_by_val(overlay_num);

private:		// functions
	////[[noinline,_target_arm]]
	//void thing_0();
	////[[noinline,_target_arm]]
	//void thing_1();
	////[[noinline,_target_arm]]
	//void thing_2();
	////[[noinline,_target_arm]]
	//void thing_3();
	////[[noinline,_target_arm]]
	//void thing_4();
	////[[noinline,_target_arm]]
	//void thing_5();
	////[[noinline,_target_arm]]
	//void thing_6();

};


}
}


#endif		// game_engine_stuff__slash__overlay_loader_stuff_hpp
