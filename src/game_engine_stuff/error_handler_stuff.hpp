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


#ifndef game_engine_stuff__slash__error_handler_stuff_hpp
#define game_engine_stuff__slash__error_handler_stuff_hpp

#include "../general_utility_stuff/debug_vars.hpp"

namespace sherwin_adventure
{
namespace game_engine
{

//void halt();
void err(const char* msg);
void warn(const char* msg);

}
}


#endif		// game_engine_stuff__slash__error_handler_stuff_hpp
