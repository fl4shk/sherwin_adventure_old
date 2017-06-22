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


#include "sprite_allocator_class.hpp"
#include "sprite_class.hpp"

#include "../../general_utility_stuff/misc_utility_funcs.hpp"
#include "../../gba_specific_stuff/asm_funcs.hpp"

#include "../halt_stuff.hpp"

SpriteAllocator::SpriteAllocator( s16* the_sa_free_list_backend_array, 
	Sprite* s_the_array, u32 s_size )
	: ArrayHelper<Sprite>( s_the_array, s_size ),
	the_sa_free_list_backend_curr_index(0),
	the_sa_free_list_backend( (s16*)the_sa_free_list_backend_array,
	&the_sa_free_list_backend_curr_index, s_size )
{
}
SpriteAllocator::SpriteAllocator( s16* the_sa_free_list_backend_array,
	const ArrayHelper<Sprite>& s_allocatable_sprite_arr )
	: ArrayHelper<Sprite>(s_allocatable_sprite_arr),
	the_sa_free_list_backend_curr_index(0),
	the_sa_free_list_backend( (s16*)the_sa_free_list_backend_array,
	&the_sa_free_list_backend_curr_index, 
	s_allocatable_sprite_arr.get_size() )
{
}

void* SpriteAllocator::allocate_sprite()
{
	//// This could definitely be faster
	//for ( u32 i=0; i<get_size(); ++i )
	//{
	//	Sprite& curr_sprite = at(i);
	//	
	//	if ( curr_sprite.the_sprite_type == st_default )
	//	{
	//		return (void*)(&curr_sprite);
	//	}
	//}
	
	ASM_COMMENT("if (can_pop_index()");
	if (can_pop_index())
	{
		int n_arr_index = the_sa_free_list_backend.peek_top();
		Sprite& ret = at(n_arr_index);
		ret.the_arr_index = n_arr_index;
		
		the_sa_free_list_backend.pop();
		
		if ( ret.the_sprite_type != st_default )
		{
			ASM_COMMENT("BadSprite");
			DebugArrGroup::write_str_and_inc("BadSprite");
			halt();
		}
		
		return (void*)(&ret);
	}
	
	
	ASM_COMMENT("NoFreeSprite");
	// No free Sprite found, So at least put something in the debug vars.
	// cout or printf would be nice here.
	//NEXT_DEBUG_U32 = ( ( 'a' << 24 ) | ( 's' << 16 ) | ( 'p' << 8 )
	//	| ( 'r' << 0 ) );
	
	DebugArrGroup::write_str_and_inc("NoFreeSprite");
	halt();
	
	//return NULL;
	for (;;)
	{
	}
}

void SpriteAllocator::deallocate_sprite( Sprite& the_sprite )
{
	//if ( the_sprite == NULL )
	//{
	//	//DebugArrGroup::write_str_and_inc("SadsSprNULL");
	//	//halt();
	//	return;
	//}
	
	if ( the_sprite.the_sprite_type == st_default )
	{
		//DebugArrGroup::write_str_and_inc("SadsSprStDefault");
		//halt();
		return;
	}
	
	if (!can_push_index())
	{
		DebugArrGroup::write_str_and_inc("SadsCan'tPush");
		halt();
	}
	
	
	the_sprite.the_sprite_type = st_default;
	
	
	// Some sprites are spawned in from something other than the Level data
	// and DON'T HAVE a the_sprite_ipg
	if (the_sprite.the_sprite_ipg)
	{
		if ( the_sprite.the_sprite_ipg->spawn_state == sss_active )
		{
			the_sprite.the_sprite_ipg->spawn_state = sss_not_active;
		}
		the_sprite.the_sprite_ipg = NULL;
	}
	
	//u32 old_vram_chunk_index = the_sprite.get_vram_chunk_index();
	//
	//*the_sprite = Sprite();
	//the_sprite.shared_constructor_code();
	//*the_sprite = Sprite(the_sprite.get_vram_chunk_index());
	
	
	the_sa_free_list_backend.push(the_sprite.the_arr_index);
	the_sprite.the_arr_index = -1;
	
	
	//the_sprite = NULL;
	
	//for ( u32 i=0; i<get_size(); ++i )
	//{
	//	Sprite& curr_sprite = at(i);
	//	
	//	if ( *the_sprite == &curr_sprite )
	//	{
	//		the_sprite->~Sprite();
	//		the_sprite = NULL;
	//		
	//		return;
	//	}
	//}
	
	
	//// No Sprite found, So at least put something in the debug vars.
	//// cout or printf would be nice here.
	//NEXT_DEBUG_U32 = ( ( 'd' << 24 ) | ( 's' << 16 ) | ( 'p' << 8 )
	//	| ( 'r' << 0 ) );
}


