// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef sprite_allocator_class_hpp
#define sprite_allocator_class_hpp

#include "../../general_utility_stuff/array_helper_class.hpp"
//#include "sprite_class.hpp"

#include "../../general_utility_stuff/sa_stack_classes.hpp"

class Sprite;

class SpriteAllocator : public ArrayHelper<Sprite>
{
protected:		// variables
	u32 the_sa_free_list_backend_curr_index;
	SaFreeListBackend the_sa_free_list_backend;
	
public:		// functions
	SpriteAllocator( s16* the_sa_free_list_backend_array, 
		Sprite* s_the_array, u32 s_size );
	SpriteAllocator( s16* the_sa_free_list_backend_array,
		const ArrayHelper<Sprite>& s_allocatable_sprite_arr );
	
	////void* allocate_sprite() __attribute__((_IWRAM_CODE,hot));
	////void* allocate_sprite() __attribute__((hot));
	////void* allocate_sprite();
	////void* allocate_sprite() __attribute__((_IWRAM_CODE));
	////void deallocate_sprite( Sprite*& the_sprite )
	////	__attribute__((_IWRAM_CODE));
	//void* allocate_sprite() __attribute__((_IWRAM_CODE,cold));
	//void deallocate_sprite( Sprite*& the_sprite )
	//	__attribute__((_IWRAM_CODE,cold));
	
	//void* allocate_sprite() __attribute__((cold,returns_nonnull));
	//void deallocate_sprite( Sprite*& the_sprite ) __attribute__((cold));
	void* allocate_sprite() __attribute__((_IWRAM_CODE,returns_nonnull));
	void deallocate_sprite( Sprite& the_sprite )
		__attribute__((_IWRAM_CODE));
	
	
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
	//inline const s32 peek_next_index() const
	//{
	//	return the_sa_free_list_backend.peek_next();
	//}
	
protected:		// functions
	//inline 
	
} __attribute__((_ALIGN4));

#endif		// sprite_allocator_class_hpp
