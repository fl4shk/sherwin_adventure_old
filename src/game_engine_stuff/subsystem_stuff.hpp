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


#ifndef subsystem_stuff_hpp
#define subsystem_stuff_hpp

#include <array>
#include <memory>

#include "../misc_includes.hpp"
#include "overlay_loader_stuff.hpp"
#include "../general_utility_stuff/free_list_allocator_base_class.hpp"

namespace sherwin_adventure
{
namespace game_engine
{

class SubsystemAllocator;

// Abstract base class for a so-called "subsystem" which is an
// organizational tool to allow connecting together pieces of the game
// engine.
class Subsystem
{
protected:		// variables
	s16 __index = -1;

public:		// functions
	inline Subsystem()
	{
	}

	inline Subsystem(s16 s_index) 
		: __index(s_index)
	{
	}


	gen_getter_and_setter_by_val(index);

	inline void* operator new (size_t size, 
		SubsystemAllocator& subsystem_allocator);

	virtual void iterate() = 0;

} __attribute__((_align4));


class SubsystemAllocator : public FreeListAllocatorBase<Subsystem>
{
public:		// functions
	SubsystemAllocator(Subsystem* s_arr, s16* s_free_list_arr, 
		size_t s_size);


protected:		// functions

} __attribute__((_align4));


void* Subsystem::operator new (size_t size, 
	SubsystemAllocator& subsystem_allocator)
{
	return subsystem_allocator.allocate();
}


}
}

#endif		// subsystem_stuff_hpp
