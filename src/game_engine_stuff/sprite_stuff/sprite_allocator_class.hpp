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


#ifndef sprite_allocator_class_hpp
#define sprite_allocator_class_hpp

#include "../array_helper_class.hpp"
#include "sprite_class.hpp"

class sprite_allocator : public array_helper<sprite>
{
public:		// functions
	inline sprite_allocator( sprite* the_array, u32 s_size )
		: array_helper<sprite>( the_array, s_size )
	{
	}
	inline sprite_allocator
		( const array_helper<sprite>& s_allocatable_sprite_arr )
		: array_helper<sprite>(s_allocatable_sprite_arr)
	{
	}
	
	void* allocate_sprite() __attribute__((_iwram_code));
	void deallocate_sprite( sprite*& the_sprite )
		__attribute__((_iwram_code));
	
	
} __attribute__((_align4));

#endif		// sprite_allocator_class_hpp
