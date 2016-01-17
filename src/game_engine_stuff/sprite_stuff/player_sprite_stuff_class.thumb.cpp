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


#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../level_stuff/active_level_manager_class.hpp"
#include "sprite_manager_class.hpp"

#include "../gfx_manager_class.hpp"

fixed24p8 player_sprite_stuff::speed;
bool player_sprite_stuff::use_16x16;
bool player_sprite_stuff::run_toggle;

s32 player_sprite_stuff::max_hp;
s32 player_sprite_stuff::remaining_hp;


// Hammer stuff
bool player_sprite_stuff::swinging_hammer;
u32 player_sprite_stuff::hammer_sprite_slot;




// Graphics constants
const player_sprite_stuff::frame 
	player_sprite_stuff::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size] 
= { 
	// Invisible
	frm_invisible, 
	
	// Standing
	frm_stand,
	
	// Walking/running
	frm_stand, frm_walk_0, frm_walk_1, frm_walk_0,
	
	// Swinging the hammer, on the ground
	frm_hammer_swing_ground_0, frm_hammer_swing_ground_1,
	frm_hammer_swing_ground_2, frm_hammer_swing_ground_3,
	
	// Swinging the hammer, in the air
	frm_hammer_swing_air_0, frm_hammer_swing_air_1, frm_hammer_swing_air_2,
	frm_hammer_swing_air_3
};


const u32 player_sprite_stuff::the_relative_metatile_slot_arr[]
	= { frm_invisible, frm_stand, frm_walk_0, frm_walk_1, 
	frm_hammer_swing_ground_0, frm_hammer_swing_ground_1,
	frm_hammer_swing_ground_2, frm_hammer_swing_ground_3,
	frm_hammer_swing_air_0, frm_hammer_swing_air_1, frm_hammer_swing_air_2,
	frm_hammer_swing_air_3 };

const u32 player_sprite_stuff::the_relative_metatile_slot_arr_size
	= sizeof(player_sprite_stuff::the_relative_metatile_slot_arr)
	/ sizeof(u32);

const vec2_f24p8 player_sprite_stuff::the_initial_coll_box_size 
	= { {12 << fixed24p8::shift }, {29 << fixed24p8::shift } },
	player_sprite_stuff::the_initial_cb_pos_offset 
	= { {2 << fixed24p8::shift }, {3 << fixed24p8::shift } };

const vec2_f24p8 player_sprite_stuff::the_initial_in_level_pos_offset
	= { {0 << fixed24p8::shift}, {0 << fixed24p8::shift} };

//const vec2_f24p8 player_sprite_stuff::the_initial_coll_box_size 
//	= { {12 << fixed24p8::shift }, {29 << fixed24p8::shift } },
//	player_sprite_stuff::the_initial_cb_pos_offset 
//	= { {( 2 + 8 ) << fixed24p8::shift }, {3 << fixed24p8::shift } };
//
//const vec2_f24p8 player_sprite_stuff::the_initial_in_level_pos_offset
//	= { {8 << fixed24p8::shift}, {0 << fixed24p8::shift} };

void player_sprite_stuff::init( sprite& the_player, bool facing_left  )
{
	the_player.the_sprite_type = get_sprite_type();
	
	//the_player.the_oam_entry.set_tile_number 
	//	( get_curr_tile_slot_old(the_player) );
	the_player.the_oam_entry.set_tile_number
		( the_player.get_vram_chunk_index() 
		* gfx_manager::num_tiles_in_ss_32x32 );
	the_player.the_oam_entry.set_pal_number 
		( get_palette_slot(the_player) );
	
	////the_player.set_shape_size(oam_entry::ss_16x32);
	//the_player.set_shape_size( get_initial_shape_size() );
	//the_player.the_coll_box.size = { 12 << fixed24p8::shift, 
	//	29 << fixed24p8::shift };
	////the_player.the_coll_box.size = { 12 << fixed24p8::shift, 
	////	30 << fixed24p8::shift };
	//
	//the_player.cb_pos_offset = { 2 << fixed24p8::shift, 
	//	3 << fixed24p8::shift };
	////the_player.cb_pos_offset = { 2 << fixed24p8::shift, 
	////	2 << fixed24p8::shift };
	set_initial_shape_size_of_sprite(the_player);
	set_initial_coll_box_stuff_of_sprite(the_player);
	
	
	// This is for slope testing stuffs
	//the_player.set_shape_size(oam_entry::ss_16x16);
	////the_player.the_coll_box.size = { 12 << fixed24p8::shift,
	////	13 << fixed24p8::shift };
	////the_player.cb_pos_offset = { 2 << fixed24p8::shift,
	////	3 << fixed24p8::shift };
	//the_player.the_coll_box.size = { 16 << fixed24p8::shift,
	//	16 << fixed24p8::shift };
	//the_player.cb_pos_offset = { 0 << fixed24p8::shift,
	//	0 << fixed24p8::shift };
	
	
	clear_and_set_bits( the_player.the_oam_entry.attr2, 
		obj_attr2_prio_mask, obj_attr2_prio_1 );
}

void player_sprite_stuff::init( sprite& the_player, 
	const vec2_f24p8& s_in_level_pos, const vec2_u32& the_level_size_2d,
	bg_point& camera_pos, bool facing_left )
{
	
	//sprite_stuff_array[the_player.the_sprite_type]->init(the_player);
	init(the_player);
	
	the_player.in_level_pos = s_in_level_pos 
		- get_the_initial_in_level_pos_offset();
	
	//the_player.in_level_pos = { 0x2000, 0x18000 };
	//the_player.the_sprite_type = st_player;
	
	
	the_player.update_f24p8_positions();
	
	the_player.update_on_screen_pos(camera_pos);
	
	
	the_player.center_camera_almost(camera_pos);
	active_level_manager::correct_bg0_scroll_mirror(the_level_size_2d);
	the_player.update_on_screen_pos(camera_pos);
	the_player.copy_the_oam_entry_to_oam_mirror
		(sprite_manager::the_player_oam_index);
	
	clear_and_set_bits( the_player.the_oam_entry.attr2, 
		obj_attr2_prio_mask, obj_attr2_prio_1 );
}


//void player_sprite_stuff::gfx_update( sprite& the_player )
//{
//	//the_player.the_oam_entry.set_tile_number
//	//	( get_curr_tile_slot_old(the_player) );
//	//the_player.the_oam_entry.set_tile_number
//	//	( the_player.get_vram_chunk_index() 
//	//	* gfx_manager::num_tiles_in_ss_32x32 );
//	the_player.the_oam_entry.set_tile_number
//		( get_curr_tile_slot(the_player) );
//	
//	the_player.the_oam_entry.set_pal_number 
//		( get_palette_slot(the_player) );
//}

void player_sprite_stuff::update_part_1( sprite& the_player ) 
{
	gfx_update(the_player);
	
	if ( key_hit(key_r) && !swinging_hammer )
	{
		hammer_sprite_slot 
			= sprite_manager::spawn_a_player_secondary_sprite_basic
			( st_player_hammer, the_player.in_level_pos,
			gfx_manager::bgofs_mirror[0].curr,
			the_player.the_oam_entry.get_hflip_status() );
		
		if ( hammer_sprite_slot != -1 )
		{
			swinging_hammer = true;
		}
	}
	
	if ( key_hit(key_b) )
	{
		if ( !run_toggle )
		{
			run_toggle = true;
		}
		else
		{
			run_toggle = false;
		}
	}
	
	speed = 0;
	
	if ( key_hit_or_held(key_left) && !key_hit_or_held(key_right) )
	{
		speed = walk_speed;
		if ( run_toggle )
		{
			speed = max_run_speed;
		}
		
		the_player.vel.x = -speed;
		the_player.the_oam_entry.enable_hflip();
	}
	else if ( key_hit_or_held(key_right) && !key_hit_or_held(key_left) )
	{
		speed = walk_speed;
		if ( run_toggle )
		{
			speed = max_run_speed;
		}
		
		the_player.vel.x = speed;
		the_player.the_oam_entry.disable_hflip();
	}
	else
	{
		the_player.vel.x = {0};
	}
	
	handle_jumping_stuff( the_player, key_hit(key_a), key_held(key_a) );
	
	
	the_player.update_f24p8_positions();
	
	the_player.block_collision_stuff();
	
}



void player_sprite_stuff::update_part_2( sprite& the_player,
	bg_point& camera_pos, const vec2_u32& the_level_size_2d )
{
	
	bool warped_this_frame = false, 
		warped_to_other_sublevel_this_frame = false;
	
	for ( sprite& spr : sprite_manager::the_sprites )
	{
		switch ( spr.the_sprite_type )
		{
			//case st_waffle:
			case st_muffin:
			case st_fire_muffin:
			case st_ice_muffin:
			case st_chocolate_muffin:
				if ( coll_box_intersects_now( the_player.the_coll_box,
					spr.the_coll_box ) )
				{
					//nocash_soft_break();
					spr.the_sprite_type = st_default;
					if ( spr.the_sprite_ipg != NULL )
					{
						spr.the_sprite_ipg->spawn_state = sss_dead;
					}
				}
				break;
			
			case st_door:
				if ( coll_box_intersects_now( the_player.the_coll_box,
					spr.the_coll_box ) && key_hit(key_up) 
					&& !warped_this_frame )
				{
					warped_this_frame = true;
					
					//const sublevel_entrance& the_dest_sle 
					//	= warp_block_sprite_stuff::get_dest_sle(spr);
					
					const sublevel_entrance* the_dest_sle_ptr
						= &( active_level::the_current_level_ptr
						->get_the_sublevels()[spr.the_sprite_ipg
						->extra_param_1]
						.sublevel_entrance_arr_arr_helper.the_array
						[spr.the_sprite_ipg->extra_param_0] );
					
					
					if ( spr.the_sprite_ipg->extra_param_1 
						!= active_level
						::the_current_active_sublevel_index )
					{
						active_level_manager
							::load_sublevel_at_intra_sublevel_warp
							( spr.the_sprite_ipg->extra_param_1, 
							spr.the_sprite_ipg->extra_param_0 );
						
						warped_to_other_sublevel_this_frame = true;
					}
					
					the_player.in_level_pos.x = the_dest_sle_ptr
						->in_level_pos.x 
						- get_the_initial_in_level_pos_offset().x;
					the_player.in_level_pos.y = the_dest_sle_ptr
						->in_level_pos.y
						- get_the_initial_in_level_pos_offset().y;
					
					the_player.update_f24p8_positions();
					the_player.update_on_screen_pos(camera_pos);
					
					the_player.center_camera_almost(camera_pos);
					active_level_manager::correct_bg0_scroll_mirror
						(the_level_size_2d);
					the_player.update_on_screen_pos(camera_pos);
					
				}
				break;
				
			case st_snow_golem:
			default:
				break;
		}
		
		if ( warped_to_other_sublevel_this_frame )
		{
			break;
		}
	}
	
	
	the_player.camera_follow_basic(camera_pos);
	
	active_level_manager::correct_bg0_scroll_mirror(the_level_size_2d);
	
	the_player.update_on_screen_pos(camera_pos);
	
	// Despawn sprites if the_player warped from one part of the current
	// sublevel to another part of the current sublevel, if they are
	// offscreen.  Also, spawn sprites that are in the new area.
	if ( warped_this_frame && !warped_to_other_sublevel_this_frame )
	{
		sprite_manager::despawn_sprites_if_needed(camera_pos);
		
		sprite_manager::initial_sprite_spawning_shared_code(camera_pos);
	}
	
	if ( player_sprite_stuff::remaining_hp < 0 )
	{
		player_sprite_stuff::remaining_hp = 0;
	}
	else if ( player_sprite_stuff::remaining_hp 
		> player_sprite_stuff::max_hp )
	{
		player_sprite_stuff::remaining_hp 
			= player_sprite_stuff::max_hp;
	}
	
	the_player.copy_the_oam_entry_to_oam_mirror
		(sprite_manager::the_player_oam_index);
}

//const u32 player_sprite_stuff::get_curr_tile_slot( sprite& the_player )
//{
//	return sprite_palette_slot_first_vram_slot_list 
//		[get_palette_slot(the_player)]
//		+ get_curr_relative_tile_slot(the_player);
//}

const u32 player_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_player )
{
	// Walk frame stuff
	s32& walk_frame_timer = the_player.misc_data_s[sdi_walk_frame_timer];
	u32& active_walk_frame_slot = the_player.misc_data_u
		[udi_active_walk_frame_slot];
	
	// Hammer swing frame stuff
	s32& hammer_swing_frame_timer = the_player.misc_data_s
		[sdi_hammer_swing_frame_timer];
	u32& active_hammer_swing_frame_slot = the_player.misc_data_u
		[udi_active_hammer_swing_frame_slot];
	
	
	if ( active_walk_frame_slot < frm_slot_walk_0 
		|| active_walk_frame_slot > frm_slot_walk_3 )
	{
		active_walk_frame_slot = frm_slot_walk_0;
	}
	
	if (the_player.on_ground)
	{
		if ( active_hammer_swing_frame_slot 
			< frm_slot_hammer_swing_ground_0 
			|| active_hammer_swing_frame_slot 
			> frm_slot_hammer_swing_ground_3 )
		{
			active_hammer_swing_frame_slot 
				= frm_slot_hammer_swing_ground_0;
		}
	}
	else //if (!the_player.on_ground)
	{
		if ( active_hammer_swing_frame_slot 
			< frm_slot_hammer_swing_air_0 
			|| active_hammer_swing_frame_slot 
			> frm_slot_hammer_swing_air_3 )
		{
			active_hammer_swing_frame_slot = frm_slot_hammer_swing_air_0;
		}
	}
	
	if (the_player.on_ground)
	{
		if (!swinging_hammer)
		{
			hammer_swing_frame_timer = 0;
			active_hammer_swing_frame_slot 
				= frm_slot_hammer_swing_ground_0;
			
			auto lambda_func_for_else_if = [&]( const u32 frame_timer_end ) 
				-> void
			{
				++walk_frame_timer;
				
				if ( walk_frame_timer > frame_timer_end )
				{
					walk_frame_timer = 0;
					
					if ( active_walk_frame_slot == frm_slot_walk_0 )
					{
						active_walk_frame_slot = frm_slot_walk_1;
					}
					else if ( active_walk_frame_slot == frm_slot_walk_1 )
					{
						active_walk_frame_slot = frm_slot_walk_2;
					}
					else if ( active_walk_frame_slot == frm_slot_walk_2 )
					{
						active_walk_frame_slot = frm_slot_walk_3;
					}
					else if ( active_walk_frame_slot == frm_slot_walk_3 )
					{
						active_walk_frame_slot = frm_slot_walk_0;
					}
					
				}
				
			};
			
			// Standing still
			if ( speed == (fixed24p8){0} )
			{
				walk_frame_timer = 0;
				//active_walk_frame_slot = frm_slot_walk_1;
				active_walk_frame_slot = frm_slot_walk_0;
				//return frame_slot_to_frame_arr[active_walk_frame_slot] 
				//	* num_active_gfx_tiles;
				return frame_slot_to_frame_arr[frm_slot_walk_0]
					* num_active_gfx_tiles;
			}
			
			
			// Walking speed or not-max running speed
			else if ( speed >= walk_speed && speed < max_run_speed )
			{
				lambda_func_for_else_if(walk_frame_timer_end);
				
				return frame_slot_to_frame_arr[active_walk_frame_slot] 
					* num_active_gfx_tiles;
			}
			
			// Max running speed
			else if ( speed == max_run_speed )
			{
				lambda_func_for_else_if(run_frame_timer_end);
				
				return frame_slot_to_frame_arr[active_walk_frame_slot] 
					* num_active_gfx_tiles;
			}
			
			else
			{
				// This should NEVER happen, so show a walking frame as a
				// debugging tool
				walk_frame_timer = 0;
				active_walk_frame_slot = frm_slot_walk_3;
				return frame_slot_to_frame_arr[active_walk_frame_slot] 
					* num_active_gfx_tiles;
			}
		}
		else //if (swinging_hammer)
		{
			++hammer_swing_frame_timer;
			
			if ( hammer_swing_frame_timer > hammer_swing_frame_timer_end )
			{
				hammer_swing_frame_timer = 0;
				
				if ( active_hammer_swing_frame_slot 
					== frm_slot_hammer_swing_ground_0 )
				{
					active_hammer_swing_frame_slot 
						= frm_slot_hammer_swing_ground_1;
				}
				else if ( active_hammer_swing_frame_slot 
					== frm_slot_hammer_swing_ground_1 )
				{
					active_hammer_swing_frame_slot 
						= frm_slot_hammer_swing_ground_2;
				}
				else if ( active_hammer_swing_frame_slot 
					== frm_slot_hammer_swing_ground_2 )
				{
					active_hammer_swing_frame_slot 
						= frm_slot_hammer_swing_ground_3;
				}
				else if ( active_hammer_swing_frame_slot 
					== frm_slot_hammer_swing_ground_3 )
				{
					//active_hammer_swing_frame_slot 
					//	= frm_slot_hammer_swing_ground_0;
					swinging_hammer = false;
				}
			}
			
			if (swinging_hammer)
			{
				return frame_slot_to_frame_arr
					[active_hammer_swing_frame_slot] 
					* num_active_gfx_tiles;
			}
			else //if (!swinging_hammer)
			{
				return frame_slot_to_frame_arr[active_walk_frame_slot]
					* num_active_gfx_tiles;
			}
		}
	}
	else //if (!the_player.on_ground)
	{
		if (!swinging_hammer)
		{
			hammer_swing_frame_timer = 0;
			active_hammer_swing_frame_slot = frm_slot_hammer_swing_air_0;
			
			return frame_slot_to_frame_arr[frm_slot_walk_2] 
				* num_active_gfx_tiles;
		}
		else //if(swinging_hammer)
		{
			++hammer_swing_frame_timer;
			
			if ( hammer_swing_frame_timer > hammer_swing_frame_timer_end )
			{
				hammer_swing_frame_timer = 0;
				
				if ( active_hammer_swing_frame_slot 
					== frm_slot_hammer_swing_air_0 )
				{
					active_hammer_swing_frame_slot 
						= frm_slot_hammer_swing_air_1;
				}
				else if ( active_hammer_swing_frame_slot 
					== frm_slot_hammer_swing_air_1 )
				{
					active_hammer_swing_frame_slot 
						= frm_slot_hammer_swing_air_2;
				}
				else if ( active_hammer_swing_frame_slot 
					== frm_slot_hammer_swing_air_2 )
				{
					active_hammer_swing_frame_slot 
						= frm_slot_hammer_swing_air_3;
				}
				else if ( active_hammer_swing_frame_slot 
					== frm_slot_hammer_swing_air_3 )
				{
					//active_hammer_swing_frame_slot 
					//	= frm_slot_hammer_swing_air_0;
					swinging_hammer = false;
				}
			}
			
			if (swinging_hammer)
			{
				return frame_slot_to_frame_arr
					[active_hammer_swing_frame_slot] 
					* num_active_gfx_tiles;
			}
			else //if (!swinging_hammer)
			{
				return frame_slot_to_frame_arr[active_walk_frame_slot]
					* num_active_gfx_tiles;
			}
		}
	}
	
}



void player_sprite_stuff::block_collision_stuff( sprite& the_player )
{
	if ( the_player.the_coll_box.size.x >= make_f24p8(0)
		&& the_player.the_coll_box.size.x <= make_f24p8(16)
		&& the_player.the_coll_box.size.y > make_f24p8(16 )
		&& the_player.the_coll_box.size.y <= make_f24p8(32) )
	{
		block_collision_stuff_16x32(the_player);
	}
	else
	{
		block_collision_stuff_16x16(the_player);
	}
}

void player_sprite_stuff::block_coll_response_top_16x16 
	( sprite& the_player, const block_coll_result& tl_coll_result, 
	const block_coll_result& tm_coll_result,
	const block_coll_result& tr_coll_result )
{
	the_player.in_level_pos.y 
		= make_f24p8( ( tl_coll_result.coord.y + 1 ) * 16 );
		//- the_player.cb_pos_offset.y;
	the_player.vel.y = {0x00};
	the_player.jump_hold_timer = 0;
	
	block_stuff_array[tm_coll_result.type]->strongly_hit_response 
		( active_level::the_block_data_at_coord(tm_coll_result.coord), 
		tm_coll_result.coord );
	
}
void player_sprite_stuff::block_coll_response_top_16x32 
	( sprite& the_player, const block_coll_result& tl_coll_result, 
	const block_coll_result& tm_coll_result,
	const block_coll_result& tr_coll_result )
{
	block_coll_response_top_16x16( the_player, tl_coll_result,
		tm_coll_result, tr_coll_result );
}



void player_sprite_stuff::handle_jumping_stuff( sprite& the_player, 
	u32 is_jump_key_hit, u32 is_jump_key_held )
{
	if ( the_player.on_ground && is_jump_key_hit )
	{
		the_player.vel.y = jump_vel;
		the_player.jump_hold_timer = max_jump_hold_timer;
	}
	else if ( !the_player.on_ground )
	{
		if ( the_player.jump_hold_timer > 0  )
		{
			if ( is_jump_key_held )
			{
				--the_player.jump_hold_timer;
			}
			else
			{
				the_player.jump_hold_timer = 0;
				
				//if ( the_player.vel.y.data < -0x200 )
				//{
				//	the_player.vel.y.data = -0x200;
				//}
				
				apply_gravity(the_player);
				
				//while ( the_player.vel.y.data <= 0 )
				//{
				//	apply_gravity(the_player);
				//}
				
			}
		}
		
		else if ( the_player.jump_hold_timer == 0 )
		{
			//if ( the_player.vel.y.data < -0x200 )
			//{
			//	the_player.vel.y.data = -0x200;
			//}
			
			apply_gravity(the_player);
			
			//while ( the_player.vel.y.data <= 0 )
			//{
			//	apply_gravity(the_player);
			//}
		}
	}
	
}




