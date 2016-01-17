// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


std::array< sprite, sprite_manager::max_num_player_secondary_sprites >
	sprite_manager::the_player_secondary_sprites;

std::array< sprite, sprite_manager::max_num_secondary_sprites >
	sprite_manager::the_secondary_sprites;

sprite sprite_manager::the_player;

std::array< sprite, sprite_manager::max_num_regular_sprites > 
	sprite_manager::the_sprites;

int sprite_manager::next_oam_index;


void sprite_manager::init_the_player ( const vec2_f24p8& s_in_level_pos, 
	const vec2_u32& the_sublevel_size_2d, bg_point& camera_pos )
{
	// The player should ALWAYS use the second VRAM chunk.
	the_player = sprite(the_player_vram_chunk_index);
	
	sprite_stuff_array[st_player]->init( the_player,
		s_in_level_pos, the_sublevel_size_2d, camera_pos );
}


void sprite_manager::init_horiz_sublevel_sprite_ipg_lists
	( const sprite_init_param_group* the_ext_sprite_ipg_arr, 
	u32 the_ext_sprite_ipg_arr_size )
{
	for ( auto& the_list : active_level::horiz_sublevel_sprite_ipg_lists
		.the_array )
	{
		the_list.fully_deallocate();
	}
	
	for ( u32 i=0; i<the_ext_sprite_ipg_arr_size; ++i )
	{
		if ( the_ext_sprite_ipg_arr[i].type != st_default )
		{
			active_level::horiz_sublevel_sprite_ipg_lists.the_array
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
		.the_array )
	{
		the_list.insertion_sort();
	}
	
	
	
}

void sprite_manager::some_sprite_init_thing()
{
	
	sprite_stuff_array[st_waffle]->init(the_sprites[0]);
	
	the_sprites[0].in_level_pos = the_player.in_level_pos;
	
	the_sprites[0].update_f24p8_positions();
	the_sprites[0].update_on_screen_pos(gfx_manager::bgofs_mirror[0].curr);
	the_sprites[0].copy_the_oam_entry_to_oam_mirror(1);
	
	for ( u32 i=1; i<the_sprites.size(); ++i )
	{
		sprite& the_spr = the_sprites[i];
		sprite& the_prev_spr = the_sprites[i - 1];
		
		sprite_stuff_array[st_muffin]->init(the_spr);
		
		the_spr.in_level_pos = the_prev_spr.in_level_pos 
			+ vec2_s32( 0x1000, 0 );
		
		the_spr.update_f24p8_positions();
		the_spr.update_on_screen_pos(gfx_manager::bgofs_mirror[0].curr);
		
		the_spr.copy_the_oam_entry_to_oam_mirror(i + 1);
		
	}
}

void sprite_manager::initial_sprite_spawning_at_start_of_level
	( bg_point& camera_pos )
{
	memfill32( the_sprites.data(), 0, the_sprites.size() * sizeof(sprite) 
		/ sizeof(u32) );
	
	const sublevel_entrance& the_start_of_level_sle
		= active_level::get_the_current_sublevel_ptr()
		.sublevel_entrance_arr_arr_helper.the_array
		[active_level::get_the_current_sublevel_ptr()
		.sublevel_entrance_arr_arr_helper.get_size() - 1];
	
	vec2_f24p8 player_initial_in_level_pos 
		= the_start_of_level_sle.in_level_pos;
	
	init_the_player( player_initial_in_level_pos, 
		active_level::get_the_current_sublevel_ptr().get_size_2d(),
		camera_pos );
	
	init_the_sprite_arrays();
	
	//next_debug_u32 = (vu32)(player_ipg);
	//next_debug_u32 = player_ipg->type;
	//nocash_soft_break();
	
	initial_sprite_spawning_shared_code(camera_pos);
}

void sprite_manager::initial_sprite_spawning_at_intra_sublevel_warp
	( bg_point& camera_pos, u32 sublevel_entrance_index )
{
	memfill32( the_sprites.data(), 0, the_sprites.size() * sizeof(sprite) 
		/ sizeof(u32) );
	
	const sublevel_entrance& the_dest_sle
		= active_level::get_the_current_sublevel_ptr()
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
		active_level::get_the_current_sublevel_ptr().get_size_2d(),
		camera_pos );
	
	init_the_sprite_arrays();
	
	//next_debug_u32 = (vu32)(player_ipg);
	//next_debug_u32 = player_ipg->type;
	//nocash_soft_break();
	
	initial_sprite_spawning_shared_code(camera_pos);
}


void sprite_manager::initial_sprite_spawning_shared_code
	( bg_point& camera_pos )
{
	auto which_spr = the_sprites.begin();
	
	// Convert 
	vec2_f24p8 camera_pos_f24p8;
	camera_pos_f24p8.x = make_f24p8(camera_pos.x);
	camera_pos_f24p8.y = make_f24p8(camera_pos.y);
	
	// Convert the position of the camera to block grid coordinates
	vec2_f24p8 camera_block_grid_pos;
	camera_block_grid_pos.x = make_f24p8( camera_pos.x >> 4 );
	camera_block_grid_pos.y = make_f24p8( camera_pos.y >> 4 );
	
	
	//for ( std::forward_list<sprite_init_param_group>& which_list
	//	: active_level::horiz_sublevel_sprite_ipg_lists )
	for ( auto& which_list : active_level::horiz_sublevel_sprite_ipg_lists
		.the_array )
	{
		//for ( sprite_init_param_group& sprite_ipg : which_list )
		for ( int i=which_list.front_node_index;
			i!=-1;
			i=which_list.get_node_at_node_index(i).next_node_index )
		{
			sprite_init_param_group& sprite_ipg = which_list
				.get_node_at_node_index(i).the_data;
			
			vec2_u32 spr_block_grid_coord;
			spr_block_grid_coord.x = sprite_ipg.initial_block_grid_x_coord;
			spr_block_grid_coord.y = sprite_ipg.initial_block_grid_y_coord;
			
			vec2_f24p8 spr_in_level_pos;
			spr_in_level_pos.x = make_f24p8( spr_block_grid_coord.x * 16 );
			spr_in_level_pos.y = make_f24p8( spr_block_grid_coord.y * 16 );
			
			vec2_f24p8 spr_on_screen_pos;
			spr_on_screen_pos.x = spr_in_level_pos.x - camera_pos_f24p8.x;
			spr_on_screen_pos.y = spr_in_level_pos.y - camera_pos_f24p8.y;
			
			// Don't spawn the sprite if it's HORIZONTALLY off-screen.
			// Perhaps eventually sprites should be spawned and despawned
			// if they are VERTICALLY off-screen.
			if ( !( spr_on_screen_pos.x.data >= 0 
				&& spr_on_screen_pos.x.data <= ( screen_width << 8 ) ) )
			{
				continue;
			}
			
			while ( which_spr->the_sprite_type != st_default 
				&& which_spr != the_sprites.end() )
			{
				++which_spr;
			}
			
			which_spr->reinit_with_sprite_ipg(&sprite_ipg);
			
			if ( which_spr == the_sprites.end() )
			{
				break;
			}
		}
		
		if ( which_spr == the_sprites.end() )
		{
			break;
		}
	}
	
	
	// sprite_manager::the_player uses OAM index the_player_oam_index.
	next_oam_index = the_active_sprites_starting_oam_index;
	
	// Run each active sprite's update_part_1() function.
	for ( sprite& the_spr : the_sprites )
	{
		if ( the_spr.the_sprite_type != st_default )
		{
			sprite_stuff_array[the_spr.the_sprite_type]
				->update_part_1(the_spr);
		}
	}
	
	// Run each active sprite's update_part_2() function.
	for ( sprite& the_spr : the_sprites )
	{
		if ( the_spr.the_sprite_type != st_default )
		{
			sprite_stuff_array[the_spr.the_sprite_type]->update_part_2
				( the_spr, gfx_manager::bgofs_mirror[0].curr, 
				next_oam_index );
		}
	}
}


//void sprite_manager::initial_sprite_spawning_from_sublevel_data_old
//	( const bg_point& camera_pos )
//{
//	auto iter3 = the_sprites.begin();
//	
//	vec2_f24p8 camera_pos_f24p8;
//	camera_pos_f24p8.x = make_f24p8(camera_pos.x);
//	camera_pos_f24p8.y = make_f24p8(camera_pos.y);
//	
//	vec2_f24p8 camera_block_grid_pos;
//	camera_block_grid_pos.x = make_f24p8( camera_pos.x >> 4 );
//	camera_block_grid_pos.y = make_f24p8( camera_pos.y >> 4 );
//	
//	
//	for ( auto iter=active_level::horiz_sublevel_sprite_ipg_lists.begin();
//		iter!=active_level::horiz_sublevel_sprite_ipg_lists.end();
//		++iter )
//	{
//		for ( auto iter2=iter->begin(); iter2!=iter->end(); ++iter2 )
//		{
//			vec2_u32 spr_block_grid_coord;
//			spr_block_grid_coord.x = iter2->initial_block_grid_x_coord;
//			spr_block_grid_coord.y = iter2->initial_block_grid_y_coord;
//			
//			vec2_f24p8 spr_in_level_pos;
//			spr_in_level_pos.x = make_f24p8( spr_block_grid_coord.x * 16 );
//			spr_in_level_pos.y = make_f24p8( spr_block_grid_coord.y * 16 );
//			
//			vec2_f24p8 spr_on_screen_pos;
//			spr_on_screen_pos.x = spr_in_level_pos.x - camera_pos_f24p8.x;
//			spr_on_screen_pos.y = spr_in_level_pos.y - camera_pos_f24p8.y;
//			
//			
//			if ( !( spr_on_screen_pos.x.data >= 0 
//				&& spr_on_screen_pos.y.data >= 0
//				&& spr_on_screen_pos.x.data <= ( screen_width << 8 )
//				&& spr_on_screen_pos.y.data <= ( screen_height << 8 ) ) )
//			{
//				continue;
//			}
//			
//			
//			while ( iter3->the_sprite_type != st_default 
//				&& iter3 != the_sprites.end() )
//			{
//				++iter3;
//			}
//			
//			// Apparently reinit_with_sprite_ipg is bugged?
//			iter3->reinit_with_sprite_ipg( &(*iter2) );
//			
//			//++iter3;
//			
//			if ( iter3 == the_sprites.end() )
//			{
//				break;
//			}
//		}
//		
//		if ( iter3 == the_sprites.end() )
//		{
//			break;
//		}
//	}
//	
//	next_oam_index = 1;
//	
//	for ( u32 i=0; i<the_sprites.size(); ++i )
//	{
//		sprite& the_spr = the_sprites[i];
//		
//		if ( the_spr.the_sprite_type != st_default )
//		{
//			sprite_stuff_array[the_spr.the_sprite_type]
//				->update_part_1(the_spr);
//		}
//	}
//	
//	for ( u32 i=0; i<the_sprites.size(); ++i )
//	{
//		sprite& the_spr = the_sprites[i];
//		
//		if ( the_spr.the_sprite_type != st_default )
//		{
//			sprite_stuff_array[the_spr.the_sprite_type]->update_part_2
//				( the_spr, gfx_manager::bgofs_mirror[0].curr,
//				next_oam_index );
//		}
//	}
//	
//	
//}





