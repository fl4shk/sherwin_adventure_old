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


#include "sprite_manager_class.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"

#include "sprite_class.hpp"
#include "../level_stuff/level_class.hpp"

#include "sprite_allocator_class.hpp"

#include "sprite_type_includes.hpp"

#include "../halt_stuff.hpp"


std::array< sprite*, sprite_manager::max_num_player_secondary_sprites >
	sprite_manager::the_player_secondary_sprites;

std::array< sprite*, sprite_manager::max_num_secondary_sprites >
	sprite_manager::the_secondary_sprites;

sprite* sprite_manager::the_player;

std::array< sprite*, sprite_manager::max_num_regular_sprites > 
	sprite_manager::the_sprites;



//// An array of player secondary sprites to allocate from
//std::array< sprite, sprite_manager::max_num_player_secondary_sprites > 
//	sprite_manager::the_allocatable_player_secondary_sprites;
//
//// An array of secondary sprites to allocate from, other than the ones
//// used by the_player 
//std::array< sprite, sprite_manager::max_num_secondary_sprites > 
//	sprite_manager::the_allocatable_secondary_sprites;
//
//// The array of REGULAR active sprites, not counting the_player.
//std::array< sprite, sprite_manager::max_num_regular_sprites > 
//	sprite_manager::the_allocatable_sprites;

//sprite_allocator sprite_manager::the_player_secondary_sprites_allocator
//	( array_helper<sprite>
//	( sprite_manager::the_allocatable_player_secondary_sprites.data(), 
//	sprite_manager::the_allocatable_player_secondary_sprites.size() ) );
//
//sprite_allocator sprite_manager::the_secondary_sprites_allocator
//	( array_helper<sprite>
//	( sprite_manager::the_allocatable_secondary_sprites.data(), 
//	sprite_manager::the_allocatable_secondary_sprites.size() ) );
//
//sprite_allocator sprite_manager::the_sprites_allocator
//	( array_helper<sprite>( sprite_manager::the_allocatable_sprites.data(),
//	sprite_manager::the_allocatable_sprites.size() ) );


// Temporarily use regular arrays to make debugging easier.
// An array of player secondary sprites to allocate from
sprite sprite_manager::the_allocatable_player_secondary_sprites
	[sprite_manager::max_num_player_secondary_sprites];

// An array of secondary sprites to allocate from, other than the ones
// used by the_player 
sprite sprite_manager::the_allocatable_secondary_sprites
	[sprite_manager::max_num_secondary_sprites];

sprite sprite_manager::the_allocatable_player
	[sprite_manager::max_num_player_sprites];

// The array of REGULAR active sprites, not counting the_player.
sprite sprite_manager::the_allocatable_sprites
	[sprite_manager::max_num_regular_sprites];



s16 sprite_manager::the_allocatable_player_secondary_sprites_free_list_arr
	[max_num_player_secondary_sprites];
s16 sprite_manager::the_allocatable_secondary_sprites_free_list_arr
	[max_num_secondary_sprites];
s16 sprite_manager::the_allocatable_player_free_list_arr
	[max_num_player_sprites];
s16 sprite_manager::the_allocatable_sprites_free_list_arr
	[max_num_regular_sprites];


// The sprite allocators
sprite_allocator sprite_manager::the_player_secondary_sprites_allocator
	( the_allocatable_player_secondary_sprites_free_list_arr,
	array_helper<sprite>
	( sprite_manager::the_allocatable_player_secondary_sprites, 
	sprite_manager::max_num_player_secondary_sprites ) );

sprite_allocator sprite_manager::the_secondary_sprites_allocator
	( the_allocatable_secondary_sprites_free_list_arr,
	array_helper<sprite>
	( sprite_manager::the_allocatable_secondary_sprites, 
	sprite_manager::max_num_secondary_sprites ) );

sprite_allocator sprite_manager::the_player_sprite_allocator
	( the_allocatable_player_free_list_arr,
	array_helper<sprite>( sprite_manager::the_allocatable_player,
	sprite_manager::max_num_player_sprites ) );

sprite_allocator sprite_manager::the_sprites_allocator
	( the_allocatable_sprites_free_list_arr,
	array_helper<sprite>( sprite_manager::the_allocatable_sprites,
	sprite_manager::max_num_regular_sprites ) );




// Active sprites
u32 sprite_manager::num_active_player_secondary_sprites, 
	sprite_manager::num_active_sprites, 
	sprite_manager::num_active_secondary_sprites;
std::array< sprite*, sprite_manager::max_num_player_secondary_sprites>
	sprite_manager::the_active_player_secondary_sprites;
std::array< sprite*, sprite_manager::max_num_secondary_sprites>
	sprite_manager::the_active_secondary_sprites;
std::array< sprite*, sprite_manager::max_num_regular_sprites>
	sprite_manager::the_active_sprites;


int sprite_manager::next_oam_index;



//// A bunch of functions whose addresses will be stored in an array of
//// function pointers that are used by the sprite_manager::allocate_sprite()
//// functions.  
//// By the way, the primary reason these functions are not stored in IWRAM
//// because I fear that doing so could cause me to run out of IWRAM if/when
//// there are ever a crapload of sprite_type's.  Of course, sprite
//// allocation is made faster by using the_sprite_type as an index to the
//// array of function pointers, so not having these in IWRAM should be fast
//// enough.
//
//
//void default_sprite_new_caller( sprite*& the_sprite,
//	sprite_allocator& the_sprite_allocator, bool facing_left )
//{
//	the_sprite = new (the_sprite_allocator) sprite(facing_left);
//}
//
//#define generate_sprite_new_caller(name) \
//	void name##_sprite_new_caller( sprite*& the_sprite, \
//		sprite_allocator& the_sprite_allocator, bool facing_left ) \
//	{ \
//		the_sprite = new (the_sprite_allocator) \
//			name##_sprite(facing_left); \
//	}
//
//list_of_main_sprite_type_suffixes(generate_sprite_new_caller);
//#undef generate_sprite_new_caller
//
//
//#define generate_funcptr_arr_entry(name) &name##_sprite_new_caller, 
//
//void (*sprite_new_caller_funcptr_arr[lim_st])( sprite*& the_sprite,
//	sprite_allocator& the_sprite_allocator, bool facing_left )
//	= { &default_sprite_new_caller, 
//	list_of_main_sprite_type_suffixes(generate_funcptr_arr_entry) };
//#undef generate_funcptr_arr_entry
//
//
//void test_func() __attribute__((target("arm")));
//void test_func()
//{
//}

void sprite_manager::allocate_sprite( sprite*& the_sprite, 
	sprite_allocator& the_sprite_allocator, 
	sprite_type the_sprite_type, bool facing_left )
{
	//if ( sprite_type_exists(the_sprite_type) )
	//{
	//	asm_comment("sprite_type_exists()");
	//	(*sprite_new_caller_funcptr_arr[the_sprite_type])( the_sprite, 
	//		the_sprite_allocator, facing_left );
	//	the_sprite->shared_constructor_code_part_2(facing_left);
	//}
	//else
	//{
	//	//show_debug_str_s32("nty0");
	//	debug_arr_group::write_str_and_inc("BadSprType0");
	//	halt();
	//}
	
	switch (the_sprite_type)
	{
		//case st_default:
		//	the_sprite = new (the_sprite_allocator) sprite(facing_left);
		//	asm_comment("st_default");
		//	break;
		
		#define generate_case_statement(name) \
		case st_##name:  \
			the_sprite = new (the_sprite_allocator) \
				name##_sprite(facing_left); \
			asm_comment("st_" #name); \
			break;
		
		list_of_main_sprite_type_suffixes(generate_case_statement)
		#undef generate_case_statement
		
		default:
			debug_arr_group::write_str_and_inc("BadSprType0");
			halt();
			break;
	}
	
	the_sprite->shared_constructor_code_part_2(facing_left);
}

void sprite_manager::allocate_sprite( sprite*& the_sprite, 
	sprite_allocator& the_sprite_allocator, sprite_type the_sprite_type, 
	const vec2_f24p8& s_in_level_pos, 
	const prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left )
{
	//if ( sprite_type_exists(the_sprite_type) )
	//{
	//	asm_comment("sprite_type_exists()");
	//	(*sprite_new_caller_funcptr_arr[the_sprite_type])( the_sprite, 
	//		the_sprite_allocator, facing_left );
	//	the_sprite->shared_constructor_code_part_2( s_in_level_pos, 
	//		camera_pos_pc_pair, facing_left );
	//}
	//else
	//{
	//	//show_debug_str_s32("nty1");
	//	debug_arr_group::write_str_and_inc("BadSprType1");
	//	halt();
	//}
	
	switch (the_sprite_type)
	{
		//case st_default:
		//	the_sprite = new (the_sprite_allocator) sprite(facing_left);
		//	asm_comment("st_default");
		//	break;
		
		#define generate_case_statement(name) \
		case st_##name:  \
			the_sprite = new (the_sprite_allocator) \
				name##_sprite(facing_left); \
			asm_comment("st_" #name); \
			break;
		
		list_of_main_sprite_type_suffixes(generate_case_statement)
		#undef generate_case_statement
		
		default:
			debug_arr_group::write_str_and_inc("BadSprType1");
			halt();
			break;
	}
	
	the_sprite->shared_constructor_code_part_2( s_in_level_pos, 
		camera_pos_pc_pair, facing_left );
	
}

void sprite_manager::reinit_sprite_with_sprite_ipg( sprite*& the_sprite, 
	sprite_allocator& the_sprite_allocator, 
	sprite_init_param_group* s_the_sprite_ipg )
{
	//u32 old_vram_chunk_index = the_sprite->get_vram_chunk_index();
	
	if ( the_sprite != NULL )
	{
		the_sprite_allocator.deallocate_sprite(*the_sprite);
		the_sprite = NULL;
	}
	
	
	if ( s_the_sprite_ipg->spawn_state == sss_not_active )
	{
		allocate_sprite( the_sprite, the_sprite_allocator, 
			s_the_sprite_ipg->type, !s_the_sprite_ipg->facing_right );
		
		vec2_f24p8 s_in_level_pos( make_f24p8( s_the_sprite_ipg
			->initial_block_grid_x_coord * 16 ), make_f24p8
			( s_the_sprite_ipg->initial_block_grid_y_coord * 16 ) );
		
		the_sprite->the_sprite_ipg = s_the_sprite_ipg;
		the_sprite->the_sprite_ipg->spawn_state = sss_active;
		
		the_sprite->set_curr_in_level_pos(s_in_level_pos);
		
	}
}



void sprite_manager::reinit_sprite_by_spawning( sprite*& the_sprite, 
	sprite_allocator& the_sprite_allocator, sprite_type s_the_sprite_type, 
	const vec2_f24p8& s_in_level_pos, 
	const prev_curr_pair<bg_point>& camera_pos_pc_pair, 
	bool facing_left )
{
	if ( the_sprite != NULL )
	{
		the_sprite_allocator.deallocate_sprite(*the_sprite);
		the_sprite = NULL;
	}
	
	allocate_sprite( the_sprite, the_sprite_allocator, s_the_sprite_type,
		s_in_level_pos, camera_pos_pc_pair, facing_left );
}


s32 sprite_manager::spawn_a_player_secondary_sprite_basic
	( sprite_type the_sprite_type, const vec2_f24p8& s_in_level_pos, 
	const prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left )
{
	//u32 next_sprite_index = 0;
	//
	//// Find a free sprite slot.  This should really be done with an
	//// sa_free_list.
	//for ( ;
	//	next_sprite_index<the_player_secondary_sprites.size();
	//	++next_sprite_index )
	//{
	//	//if ( the_player_secondary_sprites[next_sprite_index]
	//	//	.the_sprite_type == st_default )
	//	if ( the_player_secondary_sprites[next_sprite_index] == NULL )
	//	{
	//		break;
	//	}
	//}
	//
	//// Don't spawn any sprites if too many are active.
	//if ( next_sprite_index == the_player_secondary_sprites.size() )
	//{
	//	return -1;
	//}
	
	
	if ( !the_player_secondary_sprites_allocator.can_pop_index() )
	{
		debug_arr_group::write_str_and_inc("CantSpawnPSSpr");
		halt();
	}
	
	const s32 next_sprite_index = the_player_secondary_sprites_allocator
		.peek_top_index();
	//const s32 next_sprite_index = the_player_secondary_sprites_allocator
	//	.peek_top_index() + 1;
	
	if ( !in_range<s32>( (s32)0, (s32)the_player_secondary_sprites.size(), 
		next_sprite_index ) )
	{
		debug_arr_group::write_str_and_inc("NextIndexOoR");
		halt();
	}
	
	//the_player_secondary_sprites[next_sprite_index].reinit_by_spawning
	//	( the_sprite_type, s_in_level_pos, camera_pos, facing_left );
	reinit_sprite_by_spawning( the_player_secondary_sprites
		[next_sprite_index], the_player_secondary_sprites_allocator, 
		the_sprite_type, s_in_level_pos, camera_pos_pc_pair, facing_left ); 
	
	
	return next_sprite_index;
}

s32 sprite_manager::spawn_a_secondary_sprite_basic
	( sprite_type the_sprite_type, const vec2_f24p8& s_in_level_pos, 
	const prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left )
{
	//u32 next_sprite_index = 0;
	//
	//// Find a free sprite slot.  This should really be done with an
	//// sa_free_list.
	//for ( ;
	//	next_sprite_index<the_secondary_sprites.size();
	//	++next_sprite_index )
	//{
	//	//if ( the_secondary_sprites[next_sprite_index].the_sprite_type 
	//	//	== st_default )
	//	if ( the_secondary_sprites[next_sprite_index] == NULL )
	//	{
	//		break;
	//	}
	//}
	//
	//// Don't spawn any sprites if too many are active.
	//if ( next_sprite_index == the_secondary_sprites.size() )
	//{
	//	return -1;
	//}
	
	// Don't spawn any sprites if too many are active.
	if ( !the_secondary_sprites_allocator.can_pop_index() )
	{
		debug_arr_group::write_str_and_inc("CantSpawnSSpr");
		//halt();
		return -1;
	}
	
	const s32 next_sprite_index = the_secondary_sprites_allocator
		.peek_top_index();
	//const s32 next_sprite_index = the_secondary_sprites_allocator
	//	.peek_top_index() + 1;
	
	if ( !in_range<s32>( (s32)0, (s32)the_secondary_sprites.size(), 
		next_sprite_index ) )
	{
		debug_arr_group::write_str_and_inc("NextIndexOoR");
		halt();
	}
	
	//the_secondary_sprites[next_sprite_index].reinit_by_spawning
	//	( the_sprite_type, s_in_level_pos, camera_pos, facing_left );
	
	reinit_sprite_by_spawning( the_secondary_sprites[next_sprite_index],
		the_secondary_sprites_allocator, the_sprite_type, s_in_level_pos, 
		camera_pos_pc_pair, facing_left );
	
	return next_sprite_index;
}


// This is a temporary function.  It should be replaced by a function that
// inserts sprite spawning parameters into a list.  The sprites from said
// list would be spawned from within the function called
// spawn_sprites_if_needed().
s32 sprite_manager::spawn_a_sprite_basic( sprite_type the_sprite_type, 
	const vec2_f24p8& s_in_level_pos, 
	const prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left )
{
	//u32 next_sprite_index = 0;
	//
	//// Find a free sprite slot.  This should really be done with an
	//// sa_free_list.
	//for ( ; next_sprite_index<the_sprites.size(); ++next_sprite_index )
	//{
	//	//if ( the_sprites[next_sprite_index].the_sprite_type == st_default )
	//	if ( the_sprites[next_sprite_index] == NULL )
	//	{
	//		break;
	//	}
	//}
	//
	//// Don't spawn any sprites if too many are active.
	//if ( next_sprite_index == the_sprites.size() )
	//{
	//	return -1;
	//}
	
	
	// Don't spawn any sprites if too many are active.
	if ( !the_sprites_allocator.can_pop_index() )
	{
		debug_arr_group::write_str_and_inc("CantSpawnRegSpr");
		//halt();
		return -1;
	}
	
	const s32 next_sprite_index = the_sprites_allocator.peek_top_index();
	
	if ( !in_range<s32>( (s32)0, (s32)the_sprites.size(), 
		next_sprite_index ) )
	{
		debug_arr_group::write_str_and_inc("NextIndexOoR");
		halt();
	}
	
	if ( the_sprites[next_sprite_index] != NULL )
	{
		show_debug_s32_group(next_sprite_index);
		debug_arr_group::write_str_and_inc("SprNotNull");
		halt();
	}
	
	//the_sprites[next_sprite_index].reinit_by_spawning( the_sprite_type,
	//	s_in_level_pos, camera_pos, facing_left );
	
	reinit_sprite_by_spawning( the_sprites[next_sprite_index], 
		the_sprites_allocator, the_sprite_type, s_in_level_pos,
		camera_pos_pc_pair, facing_left );
	
	//allocate_sprite
	
	//sprite* temp_spr;
	//allocate_sprite( temp_spr, the_sprites_allocator, the_sprite_type,
	//	s_in_level_pos, camera_pos_pc_pair, facing_left );
	
	
	
	return next_sprite_index;
}






void sprite_manager::init_the_player ( const vec2_f24p8& s_in_level_pos, 
	const vec2_u32& the_sublevel_size_2d, 
	prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	if ( the_player != NULL )
	{
		the_player_sprite_allocator.deallocate_sprite(*the_player);
		the_player = NULL;
	}
	
	the_player = new (the_player_sprite_allocator) player_sprite
		( s_in_level_pos, the_sublevel_size_2d, camera_pos_pc_pair, 
		false );
	
	the_player->set_vram_chunk_index(the_player_vram_chunk_index);
	
	//sprite_stuff_array[st_player]->init( the_player,
	//	s_in_level_pos, the_sublevel_size_2d, camera_pos );
	//the_player->shared_constructor_code_part_2( s_in_level_pos,
	//	the_sublevel_size_2d, camera_pos, false );
	
	the_player->update_part_1();
	the_player->update_part_2();
	the_player->update_part_3( camera_pos_pc_pair, the_sublevel_size_2d );
}

void sprite_manager::clear_the_sprite_arrays()
{
	//memfill32( the_player_secondary_sprites.data(), 0,
	//	the_player_secondary_sprites.size() * sizeof(sprite*) 
	//	/ sizeof(u32) );
	//memfill32( the_secondary_sprites.data(), 0,
	//	the_secondary_sprites.size() * sizeof(sprite*) / sizeof(u32) );
	//memfill32( the_sprites.data(), 0, the_sprites.size() * sizeof(sprite*) 
	//	/ sizeof(u32) );
	//
	//
	////memfill32( the_allocatable_player_secondary_sprites.data(), 0,
	////	the_allocatable_player_secondary_sprites.size() 
	////	* sizeof(sprite) / sizeof(u32) );
	////memfill32( the_allocatable_secondary_sprites.data(), 0,
	////	the_allocatable_secondary_sprites.size() * sizeof(sprite) 
	////	/ sizeof(u32) );
	////memfill32( the_allocatable_sprites.data(), 0, 
	////	the_allocatable_sprites.size() * sizeof(sprite) 
	////	/ sizeof(u32) );
	//
	//
	//memfill32( the_allocatable_player_secondary_sprites, 0,
	//	max_num_player_secondary_sprites * sizeof(sprite) / sizeof(u32) );
	//memfill32( the_allocatable_secondary_sprites, 0,
	//	max_num_secondary_sprites * sizeof(sprite) / sizeof(u32) );
	//memfill32( the_allocatable_sprites, 0, max_num_regular_sprites 
	//	* sizeof(sprite) / sizeof(u32) );
	
	for ( u32 i=0; i<max_num_player_secondary_sprites; ++i )
	{
		if ( the_player_secondary_sprites[i] != NULL )
		{
			the_player_secondary_sprites_allocator.deallocate_sprite
				(*the_player_secondary_sprites[i]);
			the_player_secondary_sprites[i] = NULL;
		}
	}
	
	for ( u32 i=0; i<max_num_secondary_sprites; ++i )
	{
		if ( the_secondary_sprites[i] != NULL )
		{
			the_secondary_sprites_allocator.deallocate_sprite
				(*the_secondary_sprites[i]);
			the_secondary_sprites[i] = NULL;
		}
	}
	
	for ( u32 i=0; i<max_num_regular_sprites; ++i )
	{
		if ( the_sprites[i] != NULL )
		{
			the_sprites_allocator.deallocate_sprite(*the_sprites[i]);
			the_sprites[i] = NULL;
		}
	}
	
	
	//// Clear the arrays of pointers
	//arr_memfill32( the_player_secondary_sprites, 0 );
	//arr_memfill32( the_secondary_sprites, 0 );
	//arr_memfill32( the_sprites, 0 );
	
	
	//arr_memfill32( the_allocatable_player_secondary_sprites, 0,
	//	max_num_player_secondary_sprites );
	//arr_memfill32( the_allocatable_secondary_sprites, 0,
	//	max_num_secondary_sprites );
	//arr_memfill32( the_allocatable_sprites, 0, max_num_regular_sprites );
	
	
	
}

void sprite_manager::init_horiz_sublevel_sprite_ipg_lists
	( const sprite_init_param_group* the_ext_sprite_ipg_arr, 
	u32 the_ext_sprite_ipg_arr_size )
{
	for ( auto& the_list : active_level::horiz_sublevel_sprite_ipg_lists
		.ea_list_array )
	{
		the_list.fully_deallocate();
	}
	
	for ( u32 i=0; i<the_ext_sprite_ipg_arr_size; ++i )
	{
		if ( the_ext_sprite_ipg_arr[i].type != st_default )
		{
			active_level::horiz_sublevel_sprite_ipg_lists.ea_list_array
				[the_ext_sprite_ipg_arr[i].initial_block_grid_x_coord]
				.push_front(the_ext_sprite_ipg_arr[i]);
		}
	}
	
	//for ( auto& the_list : active_level::horiz_sublevel_sprite_ipg_lists
	//	.the_array )
	//{
	//	the_list.fully_deallocate();
	//}
	
	for ( auto& the_list : active_level::horiz_sublevel_sprite_ipg_lists
		.ea_list_array )
	{
		the_list.insertion_sort();
	}
	
	
	
}

//void sprite_manager::some_sprite_init_thing()
//{
//	
//	sprite_stuff_array[st_waffle]->init(the_sprites[0]);
//	
//	the_sprites[0].in_level_pos = the_player.in_level_pos;
//	
//	the_sprites[0].update_f24p8_positions();
//	the_sprites[0].update_on_screen_pos(gfx_manager::bgofs_mirror[0].curr);
//	the_sprites[0].copy_the_oam_entry_to_oam_mirror(1);
//	
//	for ( u32 i=1; i<the_sprites.size(); ++i )
//	{
//		sprite& the_spr = the_sprites[i];
//		sprite& the_prev_spr = the_sprites[i - 1];
//		
//		sprite_stuff_array[st_muffin]->init(the_spr);
//		
//		the_spr.in_level_pos = the_prev_spr.in_level_pos 
//			+ vec2_s32( 0x1000, 0 );
//		
//		the_spr.update_f24p8_positions();
//		the_spr.update_on_screen_pos(gfx_manager::bgofs_mirror[0].curr);
//		
//		the_spr.copy_the_oam_entry_to_oam_mirror(i + 1);
//		
//	}
//}

void sprite_manager::initial_sprite_spawning_at_start_of_level
	( prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	clear_the_sprite_arrays();
	
	
	const sublevel_entrance& the_start_of_level_sle
		= active_level::get_curr_sublevel_ptr()
		.sublevel_entrance_arr_arr_helper.the_array
		[active_level::get_curr_sublevel_ptr()
		.sublevel_entrance_arr_arr_helper.get_size() - 1];
	
	vec2_f24p8 player_initial_in_level_pos 
		= the_start_of_level_sle.in_level_pos;
	
	init_the_player( player_initial_in_level_pos, 
		active_level::get_curr_sublevel_ptr().get_size_2d(),
		camera_pos_pc_pair );
	
	//init_the_sprite_arrays();
	init_the_allocatable_sprite_arrays();
	
	//next_debug_u32 = (vu32)(player_ipg);
	//next_debug_u32 = player_ipg->type;
	//nocash_soft_break();
	
	initial_sprite_spawning_shared_code(camera_pos_pc_pair);
}



void sprite_manager::initial_sprite_spawning_at_intra_sublevel_warp
	( prev_curr_pair<bg_point>& camera_pos_pc_pair, 
	u32 sublevel_entrance_index )
{
	clear_the_sprite_arrays();
	
	
	const sublevel_entrance& the_dest_sle
		= active_level::get_curr_sublevel_ptr()
		.sublevel_entrance_arr_arr_helper.the_array
		[sublevel_entrance_index];
	
	vec2_f24p8 player_initial_in_level_pos;
	player_initial_in_level_pos.x = the_dest_sle.in_level_pos.x;
	//	= the_dest_sle.in_level_pos - vec2_f24p8( {0}, 
	//	make_f24p8(num_pixels_per_block_col) );
	//player_initial_in_level_pos.y = the_dest_sle.in_level_pos.y
	//	- make_f24p8( the_player.get_shape_size_as_vec2().y
	//	- num_pixels_per_block_col );
	player_initial_in_level_pos.y = the_dest_sle.in_level_pos.y;
	
	// This function call needs to be replaced with some non-destructive
	// form of changing the player's in_level_pos.
	init_the_player( player_initial_in_level_pos, 
		active_level::get_curr_sublevel_ptr().get_size_2d(),
		camera_pos_pc_pair );
	
	//init_the_sprite_arrays();
	init_the_allocatable_sprite_arrays();
	
	//next_debug_u32 = (vu32)(player_ipg);
	//next_debug_u32 = player_ipg->type;
	//nocash_soft_break();
	
	initial_sprite_spawning_shared_code(camera_pos_pc_pair);
}


void sprite_manager::initial_sprite_spawning_shared_code
	( prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	////auto which_spr = the_sprites.begin();
	//auto which_spr_ptr = the_sprites.begin();
	s32 next_sprite_index = -1;
	
	//u32 curr_ptr_slot = 0;
	//sprite* which_spr = the_sprites[0];
	
	// Convert 
	//vec2_f24p8 camera_pos_f24p8;
	//camera_pos_f24p8.x = make_f24p8(camera_pos.x);
	//camera_pos_f24p8.y = make_f24p8(camera_pos.y);
	
	// Convert the position of the camera to block grid coordinates
	vec2_f24p8 camera_block_grid_pos;
	//camera_block_grid_pos.x = make_f24p8( camera_pos.x >> 4 );
	//camera_block_grid_pos.y = make_f24p8( camera_pos.y >> 4 );
	//camera_block_grid_pos.x = camera_pos_pc_pair.curr.x.trunc_to_int() 
	//	>> 4;
	//camera_block_grid_pos.y = camera_pos_pc_pair.curr.y.trunc_to_int() 
	//	>> 4;
	//camera_block_grid_pos.x = camera_pos_pc_pair.curr.x.round_to_int() 
	//	>> 4;
	//camera_block_grid_pos.y = camera_pos_pc_pair.curr.y.round_to_int() 
	//	>> 4;
	camera_block_grid_pos.x = { camera_pos_pc_pair.curr.x
		.to_int_for_on_screen() >> 4 };
	camera_block_grid_pos.y = { camera_pos_pc_pair.curr.y
		.to_int_for_on_screen() >> 4 };
	
	
	//for ( std::forward_list<sprite_init_param_group>& which_list
	//	: active_level::horiz_sublevel_sprite_ipg_lists )
	for ( auto& which_list : active_level::horiz_sublevel_sprite_ipg_lists
		.ea_list_array )
	{
		//for ( sprite_init_param_group& sprite_ipg : which_list )
		for ( int i=which_list.get_front_index();
			i!=-1;
			i=which_list.get_node_at(i).next_index() )
		{
			sprite_init_param_group& sprite_ipg = which_list.get_node_at(i)
				.data;
			
			vec2_u32 spr_block_grid_coord;
			spr_block_grid_coord.x = sprite_ipg.initial_block_grid_x_coord;
			spr_block_grid_coord.y = sprite_ipg.initial_block_grid_y_coord;
			
			vec2_f24p8 spr_in_level_pos;
			spr_in_level_pos.x = make_f24p8( spr_block_grid_coord.x * 16 );
			spr_in_level_pos.y = make_f24p8( spr_block_grid_coord.y * 16 );
			
			vec2_f24p8 spr_on_screen_pos;
			//spr_on_screen_pos.x = spr_in_level_pos.x - camera_pos_f24p8.x;
			//spr_on_screen_pos.y = spr_in_level_pos.y - camera_pos_f24p8.y;
			spr_on_screen_pos.x = spr_in_level_pos.x 
				- camera_pos_pc_pair.curr.x;
			spr_on_screen_pos.y = spr_in_level_pos.y 
				- camera_pos_pc_pair.curr.y;
			
			// Don't spawn the sprite if it's HORIZONTALLY off-screen.
			// Perhaps eventually sprites should be spawned and despawned
			// if they are VERTICALLY off-screen.
			if ( !( spr_on_screen_pos.x.data >= 0 
				&& spr_on_screen_pos.x.data <= ( screen_width << 8 ) ) )
			{
				continue;
			}
			
			
			
			//while ( which_spr->the_sprite_type != st_default 
			//	&& which_spr != the_sprites.end() )
			//{
			//	++which_spr;
			//}
			//
			//which_spr->reinit_with_sprite_ipg(&sprite_ipg);
			//
			//if ( which_spr == the_sprites.end() )
			//{
			//	break;
			//}
			
			
			// This was the source of some spawning bugs because it didn't
			// use the elsewhere used sprite index allocation method
			////while ( (*which_spr_ptr) != NULL && which_spr_ptr
			////	!= the_sprites.end() )
			////{
			////	++which_spr_ptr;
			////}
			//
			////reinit_sprite_with_sprite_ipg( *which_spr_ptr,
			////	the_sprites_allocator, &sprite_ipg );
			//
			////if ( which_spr_ptr == the_sprites.end() )
			////{
			////	break;
			////}
			
			if (!the_sprites_allocator.can_pop_index())
			{
				break;
			}
			
			next_sprite_index = the_sprites_allocator.peek_top_index();
			
			reinit_sprite_with_sprite_ipg( the_sprites[next_sprite_index],
				the_sprites_allocator, &sprite_ipg );
		}
		
		//if ( which_spr == the_sprites.end() )
		//{
		//	break;
		//}
		
		//if ( which_spr_ptr == the_sprites.end() )
		//{
		//	break;
		//}
		
		if (!the_sprites_allocator.can_pop_index())
		{
			break;
		}
	}
	
	
	// sprite_manager::the_player uses OAM index the_player_oam_index.
	next_oam_index = the_active_sprites_starting_oam_index;
	
	// Run each active sprite's update_part_1() function.
	for ( sprite*& the_spr : the_sprites )
	{
		//if ( the_spr->the_sprite_type != st_default )
		if (the_spr)
		{
			//sprite_stuff_array[the_spr->the_sprite_type]
			//	->update_part_1(*the_spr);
			the_spr->update_part_1();
		}
	}
	
	// Run each active sprite's update_part_2() function.
	for ( sprite*& the_spr : the_sprites )
	{
		//if ( the_spr->the_sprite_type != st_default )
		if (the_spr)
		{
			//sprite_stuff_array[the_spr->the_sprite_type]->update_part_2();
			the_spr->update_part_2();
		}
	}
	
	// Run each active sprite's update_part_3() function.
	for ( sprite*& the_spr : the_sprites )
	{
		//if ( the_spr->the_sprite_type != st_default )
		if (the_spr)
		{
			//sprite_stuff_array[the_spr->the_sprite_type]->update_part_3
			//	( *the_spr, gfx_manager::bgofs_mirror[0].curr, 
			//	next_oam_index );
			the_spr->update_part_3( camera_pos_pc_pair, next_oam_index );
		}
	}
}



void sprite_manager::find_all_active_sprites()
{
	arr_memfill32( the_active_player_secondary_sprites, 0 );
	arr_memfill32( the_active_secondary_sprites, 0 );
	arr_memfill32( the_active_sprites, 0 );
	
	//auto find_active_sprites = []( sprite* sprites_arr, 
	//	sprite** active_sprites_arr, const u32 sprites_arr_size, 
	//	u32& num_active_sprites_in_category ) -> void
	//{
	//	for ( u32 i=0; i<sprites_arr_size; ++i )
	//	{
	//		sprite& the_spr = sprites_arr[i];
	//		if ( the_spr.the_sprite_type != st_default )
	//		{
	//			active_sprites_arr[num_active_sprites_in_category++] 
	//				= &the_spr;
	//		}
	//	}
	//};
	
	auto find_active_sprites = []( sprite* sprite_arr, 
		sprite** active_sprites_arr, const u32 sprites_arr_size, 
		u32& num_active_sprites_in_category ) -> void
	{
		num_active_sprites_in_category = 0;
		
		for ( u32 i=0; i<sprites_arr_size; ++i )
		{
			//sprite& the_spr = sprites_arr[i];
			//if ( the_spr.the_sprite_type != st_default )
			//{
			//	active_sprites_arr[num_active_sprites_in_category++] 
			//		= &the_spr;
			//}
			
			//sprite* the_spr_ptr = sprite_ptr_arr[i];
			sprite& the_spr = sprite_arr[i];
			
			//if ( the_spr_ptr != NULL )
			//{
			//	active_sprites_arr[num_active_sprites_in_category++]
			//		= the_spr_ptr;
			//}
			if ( the_spr.the_sprite_type != st_default )
			{
				active_sprites_arr[num_active_sprites_in_category++]
					= &the_spr;
			}
		}
	};
	
	//// Find all the currently-active secondary sprites "claimed" by
	//// the_player.
	//find_active_sprites( the_player_secondary_sprites.data(),
	//	the_active_player_secondary_sprites.data(),
	//	the_player_secondary_sprites.size(),
	//	num_active_player_secondary_sprites );
	//
	//// Find all the currently-active secondary sprites.
	//find_active_sprites( the_secondary_sprites.data(), 
	//	the_active_secondary_sprites.data(), the_secondary_sprites.size(), 
	//	num_active_secondary_sprites );
	//
	//// Find all the currently-active sprites.
	//find_active_sprites( the_sprites.data(), the_active_sprites.data(), 
	//	the_sprites.size(), num_active_sprites );
	
	// Find all the currently-active secondary sprites "claimed" by
	// the_player.
	find_active_sprites( the_allocatable_player_secondary_sprites,
		the_active_player_secondary_sprites.data(),
		the_player_secondary_sprites.size(),
		num_active_player_secondary_sprites );
	
	// Find all the currently-active secondary sprites.
	find_active_sprites( the_allocatable_secondary_sprites, 
		the_active_secondary_sprites.data(), the_secondary_sprites.size(), 
		num_active_secondary_sprites );
	
	// Find all the currently-active sprites.
	find_active_sprites( the_allocatable_sprites, 
		the_active_sprites.data(), the_sprites.size(), 
		num_active_sprites );
	
}

void sprite_manager::spawn_sprites_if_needed
	( const prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	
	prev_curr_pair<s32> camera_block_grid_pos_x;
	
	//camera_block_grid_pos_x.prev = camera_pos_pc_pair.prev.x >> 4;
	//camera_block_grid_pos_x.curr = camera_pos_pc_pair.curr.x >> 4;
	
	//camera_block_grid_pos_x.prev = camera_pos_pc_pair.prev.x
	//	.round_to_int() >> 4;
	//camera_block_grid_pos_x.curr = camera_pos_pc_pair.curr.x
	//	.round_to_int() >> 4;
	camera_block_grid_pos_x.prev = conv_pix_crd_to_blk_crd
		(camera_pos_pc_pair.prev.x.round_to_int());
	camera_block_grid_pos_x.curr = conv_pix_crd_to_blk_crd
		(camera_pos_pc_pair.curr.x.round_to_int());
	
	
	// "cm_dir" is short for "camera_movement_direction".
	int cm_dir;
	
	if ( camera_block_grid_pos_x.curr > camera_block_grid_pos_x.prev )
	{
		cm_dir = 1;
	}
	else if ( camera_block_grid_pos_x.curr < camera_block_grid_pos_x.prev )
	{
		cm_dir = -1;
	}
	else
	{
		cm_dir = 0;
	}
	
	
	// If the camera moved from left to right, add an offset of the size of
	// the screen in blocks
	if ( cm_dir > 0 )
	{
		camera_block_grid_pos_x.prev += screen_width_in_blocks;
		camera_block_grid_pos_x.curr += screen_width_in_blocks;
	}
	
	
	// Don't spawn any sprites from the level data if the camera has not
	// horizontally moved by enough pixels.
	if ( cm_dir == 0 )
	{
		return;
	}
	
	
	//u32 next_sprite_index = 0;
	//
	//// Find a free sprite slot.
	//for ( ; next_sprite_index<the_sprites.size(); ++next_sprite_index )
	//{
	//	//if ( the_sprites[next_sprite_index].the_sprite_type == st_default )
	//	//{
	//	//	break;
	//	//}
	//	if ( the_sprites[next_sprite_index] == NULL )
	//	{
	//		break;
	//	}
	//}
	//
	//// Don't spawn any sprites if too many are active.
	//if ( next_sprite_index == the_sprites.size() )
	//{
	//	return;
	//}
	
	if (!the_sprites_allocator.can_pop_index())
	{
		debug_arr_group::write_str_and_inc("CantSpawnFromLvl");
		return;
	}
	
	//s32 next_sprite_index = the_sprites_allocator.peek_top_index();
	s32 next_sprite_index = -1;
	
	// If the camera moved from left to right
	//if ( camera_block_grid_pos_x.curr > camera_block_grid_pos_x.prev )
	if ( cm_dir > 0 )
	{
		// Spawn whole columns of sprites at a time, regardless of whether
		// they are are veritcally on screen.  This assumes that all
		// sublevels are horizontal.
		for ( s32 i=camera_block_grid_pos_x.prev;
			i<=camera_block_grid_pos_x.curr;
			++i )
		//for ( s32 i=camera_block_grid_pos_x.prev;
		//	i<=camera_block_grid_pos_x.curr + 1;
		//	++i )
		{
			auto& curr_sprite_ipg_list = active_level
				::horiz_sublevel_sprite_ipg_lists.ea_list_array[i];
			
			// Spawn sprites from the top of the column to the bottom of
			// the column.
			//for ( sprite_init_param_group& sprite_ipg 
			//	: active_level::horiz_sublevel_sprite_ipg_lists[i] )
			for ( int j=curr_sprite_ipg_list.get_front_index();
				j!=-1;
				j=curr_sprite_ipg_list.get_node_at(j).next_index() )
			{
				sprite_init_param_group& sprite_ipg = curr_sprite_ipg_list
					.get_node_at(j).data;
				
				//// Find the lowest FREE sprite slot, if any.
				////while ( ( the_sprites[next_sprite_index].the_sprite_type 
				////	!= st_default )
				////	&& ( next_sprite_index != the_sprites.size() ) )
				//while ( ( the_sprites[next_sprite_index] != NULL )
				//	&& ( next_sprite_index != the_sprites.size() ) )
				//{
				//	++next_sprite_index;
				//}
				
				
				// If there isn't a free sprite slot, then stop trying to
				// spawn sprites.
				//if ( next_sprite_index == the_sprites.size() )
				//{
				//	break;
				//}
				if (!the_sprites_allocator.can_pop_index())
				{
					break;
				}
				
				next_sprite_index = the_sprites_allocator.peek_top_index();
				
				
				//the_sprites[next_sprite_index].reinit_with_sprite_ipg
				//	(&sprite_ipg);
				
				reinit_sprite_with_sprite_ipg( the_sprites
					[next_sprite_index], the_sprites_allocator, 
					&sprite_ipg );
			}
			
			// If there isn't a free sprite slot, then stop trying to spawn
			// sprites.
			//if ( next_sprite_index == the_sprites.size() )
			//{
			//	break;
			//}
			if (!the_sprites_allocator.can_pop_index())
			{
				break;
			}
			
		}
	}
	
	// If the camera moved from right to left
	else 
	{
		// Spawn whole columns of sprites at a time, regardless of whether
		// they are are veritcally on screen.  This assumes that all
		// sublevels are horizontal.
		//for ( s32 i=camera_block_grid_pos_x.prev + 5;
		//	i>=camera_block_grid_pos_x.curr - 1;
		//	--i )
		//for ( s32 i=camera_block_grid_pos_x.prev;
		//	i>=camera_block_grid_pos_x.curr - 2;
		//	--i )
		for ( s32 i=camera_block_grid_pos_x.prev - 1;
			i>=camera_block_grid_pos_x.curr - 2;
			--i )
		{
			if ( i < 0 )
			{
				break;
			}
			
			auto& curr_sprite_ipg_list = active_level
				::horiz_sublevel_sprite_ipg_lists.ea_list_array[i];
			
			// Spawn sprites from the top of the column to the bottom of
			// the column.
			//for ( sprite_init_param_group& sprite_ipg 
			//	: active_level::horiz_sublevel_sprite_ipg_lists[i] )
			for ( int j=curr_sprite_ipg_list.get_front_index();
				j!=-1;
				j=curr_sprite_ipg_list.get_node_at(j).next_index() )
			{
				sprite_init_param_group& sprite_ipg = curr_sprite_ipg_list
					.get_node_at(j).data;
				
				//// Find the lowest FREE sprite slot, if any.
				////while ( ( the_sprites[next_sprite_index].the_sprite_type 
				////	!= st_default )
				////	&& ( next_sprite_index != the_sprites.size() ) )
				//while ( ( the_sprites[next_sprite_index] != NULL )
				//	&& ( next_sprite_index != the_sprites.size() ) )
				//{
				//	++next_sprite_index;
				//}
				
				// If there isn't a free sprite slot, then stop trying to
				// spawn sprites.
				//if ( next_sprite_index == the_sprites.size() )
				//{
				//	break;
				//}
				if (!the_sprites_allocator.can_pop_index())
				{
					break;
				}
				
				next_sprite_index = the_sprites_allocator.peek_top_index();
				
				//the_sprites[next_sprite_index].reinit_with_sprite_ipg
				//	(&sprite_ipg);
				
				reinit_sprite_with_sprite_ipg( the_sprites
					[next_sprite_index], the_sprites_allocator, 
					&sprite_ipg );
			}
			
			// If there isn't a free sprite slot, then stop trying to spawn
			// sprites.
			//if ( next_sprite_index == the_sprites.size() )
			//{
			//	break;
			//}
			if (!the_sprites_allocator.can_pop_index())
			{
				break;
			}
			
		}
		
	}
	
}




// This function despawns sprites from the_player_secondary_sprites,
// the_sprites, and the_secondary_sprites, if they are offscreen.
void sprite_manager::despawn_sprites_if_needed
	( const bg_point& camera_pos )
{
	// Sprites are despawned only when they are HORIZONTALLY too far off
	// screen.
	constexpr s32 max_left = -( ( 2 * 16 ) << 8 ),
		max_right = ( screen_width + 2 * 16 ) << 8;
	
	
	//vec2_f24p8 camera_pos_f24p8;
	//camera_pos_f24p8.x = make_f24p8(camera_pos.x);
	//camera_pos_f24p8.y = make_f24p8(camera_pos.y);
	
	
	auto for_loop_contents = [&]( sprite*& spr, 
		sprite_allocator& the_sprite_allocator ) -> void
	{
		if ( spr != NULL )
		{
			//fixed24p8 spr_on_screen_pos_x = spr->in_level_pos.x 
			//	- camera_pos.x;
			fixed24p8 spr_on_screen_pos_x = spr->get_curr_in_level_pos().x 
				- camera_pos.x;
			
			if ( !( spr_on_screen_pos_x.data >= max_left
				&& spr_on_screen_pos_x.data <= max_right ) )
			{
				// I might eventually create spr->despawn() so that
				// sprites can control HOW they despawn
				//spr->despawn();
				
				if ( spr->the_sprite_ipg != NULL )
				{
					spr->the_sprite_ipg->spawn_state = sss_not_active;
				}
				
				the_sprite_allocator.deallocate_sprite(*spr);
				spr = NULL;
				//spr = NULL;
			}
			
		}
	};
	
	
	//for ( sprite*& spr : the_active_player_secondary_sprites )
	for ( u32 i=0; i<the_player_secondary_sprites.size(); ++i )
	{
		sprite*& spr = the_player_secondary_sprites[i];
		
		for_loop_contents( spr, the_player_secondary_sprites_allocator );
	}
	
	//for ( sprite*& spr : the_active_secondary_sprites )
	for ( u32 i=0; i<the_secondary_sprites.size(); ++i )
	{
		sprite*& spr = the_secondary_sprites[i];
		
		for_loop_contents( spr, the_secondary_sprites_allocator );
	}
	
	//for ( sprite*& spr : the_active_sprites )
	for ( u32 i=0; i<the_sprites.size(); ++i )
	{
		sprite*& spr = the_sprites[i];
		
		for_loop_contents( spr, the_sprites_allocator );
	}
}

void sprite_manager::upload_tiles_of_active_sprites_to_vram()
{
	// Clear the first 32x32-pixel VRAM chunk.  This prevents unused
	// OAM indices from displaying any graphics.  Perhaps this should
	// be optimized to use only a single 8x8-pixel VRAM chunk.
	//memfill32( &(((tile*)obj_tile_vram)[0]), 0, sizeof(tile)
	//	* gfx_manager::num_tiles_in_ss_32x32 / sizeof(u32) );
	
	gfx_manager::upload_sprite_tiles_to_vram(*the_player);
	
	auto for_loop_contents = []( sprite* spr ) -> void
	{
		//// These two if statements probably accomplish the same goal,
		//// which is why one of them is commented out
		////if ( spr.get_vram_chunk_index() != 0 )
		//if ( spr.the_sprite_type != st_default )
		//{
		//	gfx_manager::upload_sprite_tiles_to_vram(spr);
		//}
		
		if ( spr != NULL && spr->the_sprite_type != st_default )
		{
			gfx_manager::upload_sprite_tiles_to_vram(*spr);
		}
	};
	
	// For some reason range-based for loops and the lambda function don't
	// play well together.  I don't know if this is a GCC bug or a
	// misunderstanding on my part (could be both).
	//for ( sprite* spr : sprite_manager::the_player_secondary_sprites )
	for ( size_t i=0; 
		i<sprite_manager::the_player_secondary_sprites.size();
		++i )
	{
		for_loop_contents(sprite_manager::the_player_secondary_sprites
			.at(i));
	}
	
	//for ( sprite* spr : sprite_manager::the_sprites )
	for ( size_t i=0; i<sprite_manager::the_sprites.size(); ++i )
	{
		for_loop_contents(sprite_manager::the_sprites.at(i));
	}
	
	//for ( * spr : sprite_manager::the_secondary_sprites )
	for ( size_t i=0; i<sprite_manager::the_secondary_sprites.size(); ++i )
	{
		for_loop_contents(sprite_manager::the_secondary_sprites.at(i));
	}
}


void sprite_manager::update_all_sprites
	( const vec2_u32& the_sublevel_size_2d, 
	prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	
	
	
	//sprite_stuff_array[the_player.the_sprite_type]->update_part_1
	//	(the_player);
	the_player->update_part_1();
	
	
	
	auto update_part_1_for_active_sprites 
		= []( u32 num_active_sprites_in_category, 
		sprite** active_sprites_arr ) -> void
	{
		for ( u32 i=0; i<num_active_sprites_in_category; ++i )
		{
			sprite& the_spr = *(active_sprites_arr[i]);
			//sprite_stuff_array[the_spr.the_sprite_type]
			//	->update_part_1(the_spr);
			the_spr.update_part_1();
		}
	};
	
	
	// Update the currently-active secondary sprites "claimed" by
	// the_player.
	update_part_1_for_active_sprites( num_active_player_secondary_sprites,
		the_active_player_secondary_sprites.data() );
	
	// Update the currently-active secondary sprites.
	update_part_1_for_active_sprites( num_active_secondary_sprites,
		the_active_secondary_sprites.data() );
	
	// Update the currently-active sprites.
	update_part_1_for_active_sprites( num_active_sprites,
		the_active_sprites.data() );
	
	the_player->update_part_2();
	
	
	auto update_part_2_for_active_sprites 
		= []( u32 num_active_sprites_in_category, 
		sprite** active_sprites_arr ) -> void
	{
		for ( u32 i=0; i<num_active_sprites_in_category; ++i )
		{
			sprite& the_spr = *(active_sprites_arr[i]);
			//sprite_stuff_array[the_spr.the_sprite_type]
			//	->update_part_2(the_spr);
			the_spr.update_part_2();
		}
	};
	
	
	// Update the currently-active secondary sprites "claimed" by
	// the_player.
	update_part_2_for_active_sprites( num_active_player_secondary_sprites,
		the_active_player_secondary_sprites.data() );
	
	// Update the currently-active secondary sprites.
	update_part_2_for_active_sprites( num_active_secondary_sprites,
		the_active_secondary_sprites.data() );
	
	// Update the currently-active sprites.
	update_part_2_for_active_sprites( num_active_sprites,
		the_active_sprites.data() );
	
	
	
	//sprite_stuff_array[the_player.the_sprite_type]->update_part_2
	//	( the_player, camera_pos_pc_pair.curr, the_sublevel_size_2d );
	the_player->update_part_3( camera_pos_pc_pair, the_sublevel_size_2d );
	
	auto two_sprites_coll_box_test_thing = []( sprite& the_spr,
		sprite& the_other_spr ) -> void
	{
		if ( coll_box_intersects_now( the_spr.the_coll_box,
			the_other_spr.the_coll_box ) )
		{
			// Update a volatile variable so the compiler won't
			// optimize out this loop
			//debug_arr_f8p8[0] = make_f8p8(8);
			debug_arr_group::debug_f8p8_arr_helper.at(0) 
				= make_f8p8(8);
		}
	};
	
	
	// Secondary sprites "claimed" by the_player
	next_oam_index = the_player_secondary_sprites_starting_oam_index;
	
	for ( u32 i=0; i<num_active_player_secondary_sprites; ++i )
	{
		sprite& the_spr = *(the_active_player_secondary_sprites[i]);
		
		// I am pretty sure this isn't a necessary sanity check
		if ( the_spr.the_sprite_type == st_default )
		{
			continue;
		}
		
		// Update the sprite
		//sprite_stuff_array[the_spr.the_sprite_type]->update_part_3
		//	( the_spr, camera_pos_pc_pair.curr, next_oam_index );
		the_spr.update_part_3( camera_pos_pc_pair, next_oam_index );
		
		for ( u32 j=0; j<num_active_sprites; ++j )
		{
			sprite& the_other_spr = *(the_active_sprites[j]);
			
			two_sprites_coll_box_test_thing( the_spr, the_other_spr );
		}
		
	}
	
	
	// Other secondary sprites
	next_oam_index = the_secondary_sprites_starting_oam_index;
	
	for ( u32 i=0; i<num_active_secondary_sprites; ++i )
	{
		sprite& the_spr = *(the_active_secondary_sprites[i]);
		
		// I am pretty sure this isn't a necessary sanity check
		if ( the_spr.the_sprite_type == st_default )
		{
			continue;
		}
		
		// Update the sprite
		//sprite_stuff_array[the_spr.the_sprite_type]->update_part_3
		//	( the_spr, camera_pos_pc_pair.curr, next_oam_index );
		the_spr.update_part_3( camera_pos_pc_pair, next_oam_index );
		
		for ( u32 j=0; j<num_active_sprites; ++j )
		{
			sprite& the_other_spr = *(the_active_sprites[j]);
			
			two_sprites_coll_box_test_thing( the_spr, the_other_spr );
		}
		
	}
	
	
	// Regular sprites
	next_oam_index = the_active_sprites_starting_oam_index;
	
	for ( u32 i=0; i<num_active_sprites; ++i )
	{
		sprite& the_spr = *(the_active_sprites[i]);
		
		// I am pretty sure this isn't a necessary sanity check
		if ( the_spr.the_sprite_type == st_default )
		{
			continue;
		}
		
		// Update the sprite
		//sprite_stuff_array[the_spr.the_sprite_type]->update_part_3
		//	( the_spr, camera_pos_pc_pair.curr, next_oam_index );
		the_spr.update_part_3( camera_pos_pc_pair, next_oam_index );
		
		if ( i == 0 )
		{
			for ( u32 j=1; j<num_active_sprites; ++j )
			{
				sprite& the_other_spr = *(the_active_sprites[j]);
				
				two_sprites_coll_box_test_thing( the_spr, the_other_spr );
			}
		}
		else if ( i > 0 && i < num_active_sprites - 1 )
		{
			for ( u32 j=0; j<i; ++j )
			{
				sprite& the_other_spr = *(the_active_sprites[j]);
				
				two_sprites_coll_box_test_thing( the_spr, the_other_spr );
			}
			for ( u32 j=i+1; j<num_active_sprites; ++j )
			{
				sprite& the_other_spr = *(the_active_sprites[j]);
				
				two_sprites_coll_box_test_thing( the_spr, the_other_spr );
			}
		}
		
	}
	
	
}
