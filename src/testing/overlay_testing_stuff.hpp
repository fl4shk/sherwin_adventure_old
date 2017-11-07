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


#ifndef overlay_testing_stuff_hpp
#define overlay_testing_stuff_hpp

#include "../misc_includes.hpp"
#include "../game_engine_stuff/overlay_loader_stuff.hpp"


extern "C"
{

void test_title_screen() __attribute__((_title_screen_iwram_code));

void test_overworld_load() __attribute__((_overworld_load_iwram_code));

}

void test_some_linker_overlay_stuff();

#endif		//overlay_testing_stuff_hpp
