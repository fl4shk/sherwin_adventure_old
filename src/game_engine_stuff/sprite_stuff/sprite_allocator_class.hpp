// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#ifndef sprite_allocator_class_hpp
#define sprite_allocator_class_hpp

#include "../array_helper_class.hpp"
//#include "sprite_class.hpp"

#include "../sa_stack_classes.hpp"

class sprite;

class sprite_allocator : public array_helper<sprite>
{
protected:		// variables
	u32 the_sa_free_list_backend_curr_index;
	sa_free_list_backend the_sa_free_list_backend;
	
public:		// functions
	sprite_allocator( int* the_sa_free_list_backend_array, 
		sprite* s_the_array, u32 s_size );
	sprite_allocator( int* the_sa_free_list_backend_array,
		const array_helper<sprite>& s_allocatable_sprite_arr );
	
	////void* allocate_sprite() __attribute__((_iwram_code,hot));
	////void* allocate_sprite() __attribute__((hot));
	////void* allocate_sprite();
	////void* allocate_sprite() __attribute__((_iwram_code));
	////void deallocate_sprite( sprite*& the_sprite )
	////	__attribute__((_iwram_code));
	//void* allocate_sprite() __attribute__((_iwram_code,cold));
	//void deallocate_sprite( sprite*& the_sprite )
	//	__attribute__((_iwram_code,cold));
	
	//void* allocate_sprite() __attribute__((cold,returns_nonnull));
	//void deallocate_sprite( sprite*& the_sprite ) __attribute__((cold));
	void* allocate_sprite() __attribute__((_iwram_code,returns_nonnull));
	void deallocate_sprite( sprite*& the_sprite )
		__attribute__((_iwram_code));
	
	
	inline bool can_push_index() const
	{
		return the_sa_free_list_backend.can_push();
	}
	inline bool can_pop_index() const
	{
		return the_sa_free_list_backend.can_pop();
	}
	inline const s32 peek_top_index() const
	{
		return the_sa_free_list_backend.peek_top();
	}
	
protected:		// functions
	//inline 
	
} __attribute__((_align4));

#endif		// sprite_allocator_class_hpp
