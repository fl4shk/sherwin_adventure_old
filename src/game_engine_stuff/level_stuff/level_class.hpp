// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
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


#ifndef level_class_hpp
#define level_class_hpp

#include "sublevel_class.hpp"
#include "level_defines.hpp"

#include <array>
using std::array;

// This Is a class That Contains a group of COMPRESSED sublevels in ROM.
// It also allows 
class Level
{
public:		// constants
	static constexpr u32 max_num_sublevels = max_num_sublevels_per_level;
	
protected:		// variables
	u32 actual_num_sublevels = 0;
	array<SublevelPointer, max_num_sublevels > the_sublevels;
	
	
private:		// functions
	
	void init(SublevelPointer& some_sublevel_pointer)
	{
		the_sublevels.at(actual_num_sublevels++) = some_sublevel_pointer;
	}
	
	template<typename... rem_types >
	void init(SublevelPointer& first, 
		rem_types&... rem_sublevel_pointers)
	{
		init(first);
		init(rem_sublevel_pointers...);
	}
	
	
	void init(SublevelPointer&& some_sublevel_pointer)
	{
		the_sublevels.at(actual_num_sublevels++) = some_sublevel_pointer;
	}
	
	template<typename... rem_types >
	void init(SublevelPointer&& first, 
		rem_types&&... rem_sublevel_pointers)
	{
		init(std::move(first));
		init(std::move(rem_sublevel_pointers...));
	}
public:		// functions
	
	template<typename... arg_types >
	Level(arg_types&... some_sublevel_pointers)
	{
		init(some_sublevel_pointers...);
	}
	template<typename... arg_types >
	Level(arg_types&&... some_sublevel_pointers)
	{
		init(some_sublevel_pointers...);
	}
	
	
	inline const u32 get_actual_num_sublevels() const
	{
		return actual_num_sublevels;
	}
	
	inline const SublevelPointer* get_sublevels() const
	{
		return the_sublevels.data();
	}
	
	
} __attribute__((_ALIGN4));


#endif		// level_class_hpp
