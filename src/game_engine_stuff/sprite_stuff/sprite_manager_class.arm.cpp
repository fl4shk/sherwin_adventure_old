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


#include "sprite_manager_class.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"

#include "sprite_allocator_class.hpp"

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
				::horiz_sublevel_sprite_ipg_lists.the_array[i];
			
			// Spawn sprites from the top of the column to the bottom of
			// the column.
			//for ( sprite_init_param_group& sprite_ipg 
			//	: active_level::horiz_sublevel_sprite_ipg_lists[i] )
			for ( int j=curr_sprite_ipg_list.get_front_node_index();
				j!=-1;
				j=curr_sprite_ipg_list.get_node_at(j).next_node_index() )
			{
				sprite_init_param_group& sprite_ipg = curr_sprite_ipg_list
					.get_node_at(j).the_data;
				
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
				::horiz_sublevel_sprite_ipg_lists.the_array[i];
			
			// Spawn sprites from the top of the column to the bottom of
			// the column.
			//for ( sprite_init_param_group& sprite_ipg 
			//	: active_level::horiz_sublevel_sprite_ipg_lists[i] )
			for ( int j=curr_sprite_ipg_list.get_front_node_index();
				j!=-1;
				j=curr_sprite_ipg_list.get_node_at(j).next_node_index() )
			{
				sprite_init_param_group& sprite_ipg = curr_sprite_ipg_list
					.get_node_at(j).the_data;
				
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

