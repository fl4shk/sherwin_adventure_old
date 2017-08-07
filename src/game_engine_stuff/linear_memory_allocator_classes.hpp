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


#ifndef linear_memory_allocator_classes_hpp
#define linear_memory_allocator_classes_hpp


#include "../general_utility_stuff/misc_types.hpp"
#include "../general_utility_stuff/gen_getter_setter_defines.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"

class EwramAllocator
{
public:		// constants
	static constexpr size_t max_size = 0x38000;
	
private:		// variables
	size_t internal_curr_index = 0;
	
	static u8 internal_buf[max_size] __attribute__((_EWRAM));
	
	
private:		// functions
	GEN_SETTER_BY_VAL(curr_index);
	
	GEN_STATIC_GETTER_BY_REF(buf);
	
public:		// functions
	inline EwramAllocator()
	{
		reset();
	}
	inline void reset()
	{
		set_curr_index(0);
	}
	
	
	GEN_GETTER_BY_VAL(curr_index);
	
	
} __attribute__((_ALIGN4));


#endif		// linear_memory_allocator_classes_hpp
