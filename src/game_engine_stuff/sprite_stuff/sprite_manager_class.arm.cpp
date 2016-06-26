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


#include "sprite_manager_class.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"


void sprite_manager::spawn_sprites_if_needed
	( const prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	
	prev_curr_pair<s32> camera_block_grid_pos_x;
	
	//camera_block_grid_pos_x.prev = camera_pos_pc_pair.prev.x >> 4;
	//camera_block_grid_pos_x.curr = camera_pos_pc_pair.curr.x >> 4;
	
	camera_block_grid_pos_x.prev = camera_pos_pc_pair.prev.x.round_to_int() 
		>> 4;
	camera_block_grid_pos_x.curr = camera_pos_pc_pair.curr.x.round_to_int() 
		>> 4;
	
	
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
	
	
	// Don't spawn any sprites if the camera has not horizontally moved
	// by enough pixels.
	if ( cm_dir == 0 )
	{
		return;
	}
	
	
	u32 next_sprite_index = 0;
	
	// Find a free sprite slot.
	for ( ; next_sprite_index<the_sprites.size(); ++next_sprite_index )
	{
		if ( the_sprites[next_sprite_index].the_sprite_type == st_default )
		{
			break;
		}
	}
	
	// Don't spawn any sprites if too many are active.
	if ( next_sprite_index == the_sprites.size() )
	{
		return;
	}
	
	
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
				::horiz_sublevel_sprite_ipg_lists.the_array[i];
			
			// Spawn sprites from the top of the column to the bottom of
			// the column.
			//for ( sprite_init_param_group& sprite_ipg 
			//	: active_level::horiz_sublevel_sprite_ipg_lists[i] )
			for ( int j=curr_sprite_ipg_list.front_node_index;
				j!=-1;
				j=curr_sprite_ipg_list.get_node_at_node_index(j)
				.next_node_index )
			{
				sprite_init_param_group& sprite_ipg = curr_sprite_ipg_list
					.get_node_at_node_index(j).the_data;
				
				// Find the lowest FREE sprite slot, if any.
				while ( ( the_sprites[next_sprite_index].the_sprite_type 
					!= st_default )
					&& ( next_sprite_index != the_sprites.size() ) )
				{
					++next_sprite_index;
				}
				
				// If there isn't a free sprite slot, then stop trying to
				// spawn sprites.
				if ( next_sprite_index == the_sprites.size() )
				{
					break;
				}
				
				the_sprites[next_sprite_index].reinit_with_sprite_ipg
					(&sprite_ipg);
				
			}
			
			// If there isn't a free sprite slot, then stop trying to spawn
			// sprites.
			if ( next_sprite_index == the_sprites.size() )
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
				::horiz_sublevel_sprite_ipg_lists.the_array[i];
			
			// Spawn sprites from the top of the column to the bottom of
			// the column.
			//for ( sprite_init_param_group& sprite_ipg 
			//	: active_level::horiz_sublevel_sprite_ipg_lists[i] )
			for ( int j=curr_sprite_ipg_list.front_node_index;
				j!=-1;
				j=curr_sprite_ipg_list.get_node_at_node_index(j)
				.next_node_index )
			{
				sprite_init_param_group& sprite_ipg = curr_sprite_ipg_list
					.get_node_at_node_index(j).the_data;
				
				// Find the lowest FREE sprite slot, if any.
				while ( ( the_sprites[next_sprite_index].the_sprite_type 
					!= st_default )
					&& ( next_sprite_index != the_sprites.size() ) )
				{
					++next_sprite_index;
				}
				
				// If there isn't a free sprite slot, then stop trying to
				// spawn sprites.
				if ( next_sprite_index == the_sprites.size() )
				{
					break;
				}
				
				the_sprites[next_sprite_index].reinit_with_sprite_ipg
					(&sprite_ipg);
				
			}
			
			// If there isn't a free sprite slot, then stop trying to spawn
			// sprites.
			if ( next_sprite_index == the_sprites.size() )
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
	
	auto for_loop_contents = [&]( sprite& spr ) -> void
	{
		if ( spr.the_sprite_type != st_default )
		{
			fixed24p8 spr_on_screen_pos_x = spr.in_level_pos.x 
				- camera_pos.x;
			
			if ( !( spr_on_screen_pos_x.data >= max_left
				&& spr_on_screen_pos_x.data <= max_right ) )
			{
				// I might eventually create spr.despawn() so that
				// sprites can control HOW they despawn
				//spr.despawn();
				
				spr.the_sprite_type = st_default;
				if ( spr.the_sprite_ipg != NULL )
				{
					spr.the_sprite_ipg->spawn_state = sss_not_active;
				}
			}
		}
	};
	
	for ( sprite& spr : the_player_secondary_sprites )
	{
		for_loop_contents(spr);
	}
	
	for ( sprite& spr : the_secondary_sprites )
	{
		for_loop_contents(spr);
	}
	
	for ( sprite& spr : the_sprites )
	{
		for_loop_contents(spr);
	}
	
}


s32 sprite_manager::spawn_a_player_secondary_sprite_basic
	( sprite_type the_sprite_type, const vec2_f24p8& s_in_level_pos, 
	const bg_point& camera_pos, bool facing_left )
{
	u32 next_sprite_index = 0;
	
	// Find a free sprite slot.
	for ( ;
		next_sprite_index<the_player_secondary_sprites.size();
		++next_sprite_index )
	{
		if ( the_player_secondary_sprites[next_sprite_index]
			.the_sprite_type == st_default )
		{
			break;
		}
	}
	
	// Don't spawn any sprites if too many are active.
	if ( next_sprite_index == the_player_secondary_sprites.size() )
	{
		return -1;
	}
	
	the_player_secondary_sprites[next_sprite_index].reinit_by_spawning
		( the_sprite_type, s_in_level_pos, camera_pos, facing_left );
	
	return next_sprite_index;
}

s32 sprite_manager::spawn_a_secondary_sprite_basic
	( sprite_type the_sprite_type, const vec2_f24p8& s_in_level_pos, 
	const bg_point& camera_pos, bool facing_left )
{
	u32 next_sprite_index = 0;
	
	// Find a free sprite slot.
	for ( ;
		next_sprite_index<the_secondary_sprites.size();
		++next_sprite_index )
	{
		if ( the_secondary_sprites[next_sprite_index].the_sprite_type 
			== st_default )
		{
			break;
		}
	}
	
	// Don't spawn any sprites if too many are active.
	if ( next_sprite_index == the_secondary_sprites.size() )
	{
		return -1;
	}
	
	the_secondary_sprites[next_sprite_index].reinit_by_spawning
		( the_sprite_type, s_in_level_pos, camera_pos, facing_left );
	
	return next_sprite_index;
}


// This is a temporary function.  It should be replaced by a function that
// inserts sprite spawning parameters into a list.  The sprites from said
// list would be spawned from within the function called
// spawn_sprites_if_needed().
void sprite_manager::spawn_a_sprite_basic( sprite_type the_sprite_type, 
	const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos, 
	bool facing_left )
{
	u32 next_sprite_index = 0;
	
	// Find a free sprite slot.
	for ( ; next_sprite_index<the_sprites.size(); ++next_sprite_index )
	{
		if ( the_sprites[next_sprite_index].the_sprite_type == st_default )
		{
			break;
		}
	}
	
	// Don't spawn any sprites if too many are active.
	if ( next_sprite_index == the_sprites.size() )
	{
		return;
	}
	
	the_sprites[next_sprite_index].reinit_by_spawning( the_sprite_type,
		s_in_level_pos, camera_pos, facing_left );
	
}


void sprite_manager::update_all_sprites
	( const vec2_u32& the_sublevel_size_2d, 
	prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	sprite_stuff_array[the_player.the_sprite_type]
		->update_part_1(the_player);
	
	
	u32 num_active_player_secondary_sprites = 0, num_active_sprites = 0, 
		num_active_secondary_sprites = 0;
	
	std::array< sprite*, max_num_player_secondary_sprites>
		the_active_player_secondary_sprites;
	std::array< sprite*, max_num_secondary_sprites>
		the_active_secondary_sprites;
	std::array< sprite*, max_num_regular_sprites> the_active_sprites;
	
	for ( u32 i=0; i<the_active_player_secondary_sprites.size(); ++i )
	{
		the_active_player_secondary_sprites[i] = NULL;
	}
	for ( u32 i=0; i<the_active_secondary_sprites.size(); ++i )
	{
		the_active_secondary_sprites[i] = NULL;
	}
	for ( u32 i=0; i<the_active_sprites.size(); ++i )
	{
		the_active_sprites[i] = NULL;
	}
	
	auto find_active_sprites = []( sprite* sprites_arr, 
		sprite** active_sprites_arr, const u32 sprites_arr_size, 
		u32& num_active_sprites_in_category ) -> void
	{
		for ( u32 i=0; i<sprites_arr_size; ++i )
		{
			sprite& the_spr = sprites_arr[i];
			if ( the_spr.the_sprite_type != st_default )
			{
				active_sprites_arr[num_active_sprites_in_category++] 
					= &the_spr;
			}
		}
	};
	
	// Find all the currently-active secondary sprites "claimed" by
	// the_player.
	find_active_sprites( the_player_secondary_sprites.data(),
		the_active_player_secondary_sprites.data(),
		the_player_secondary_sprites.size(),
		num_active_player_secondary_sprites );
	
	// Find all the currently-active secondary sprites.
	find_active_sprites( the_secondary_sprites.data(), 
		the_active_secondary_sprites.data(), the_secondary_sprites.size(), 
		num_active_secondary_sprites );
	
	// Find all the currently-active sprites.
	find_active_sprites( the_sprites.data(), the_active_sprites.data(), 
		the_sprites.size(), num_active_sprites );
	
	
	
	auto update_part_1_for_active_sprites 
		= []( u32 num_active_sprites_in_category, 
		sprite** active_sprites_arr ) -> void
	{
		for ( u32 i=0; i<num_active_sprites_in_category; ++i )
		{
			sprite& the_spr = *(active_sprites_arr[i]);
			sprite_stuff_array[the_spr.the_sprite_type]
				->update_part_1(the_spr);
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
	
	
	sprite_stuff_array[the_player.the_sprite_type]->update_part_2
		( the_player, camera_pos_pc_pair.curr, the_sublevel_size_2d );
	
	auto two_sprites_coll_box_test_thing = []( sprite& the_spr,
		sprite& the_other_spr ) -> void
	{
		if ( coll_box_intersects_now( the_spr.the_coll_box,
			the_other_spr.the_coll_box ) )
		{
			// Update a volatile variable so the compiler won't
			// optimize out this loop
			debug_arr_f8p8[0] = make_f8p8(8);
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
		sprite_stuff_array[the_spr.the_sprite_type]->update_part_2
			( the_spr, camera_pos_pc_pair.curr, next_oam_index );
		
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
		sprite_stuff_array[the_spr.the_sprite_type]->update_part_2
			( the_spr, camera_pos_pc_pair.curr, next_oam_index );
		
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
		sprite_stuff_array[the_spr.the_sprite_type]->update_part_2
			( the_spr, camera_pos_pc_pair.curr, next_oam_index );
		
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

