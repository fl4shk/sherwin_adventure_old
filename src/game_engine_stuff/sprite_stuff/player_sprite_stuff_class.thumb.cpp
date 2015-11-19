#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../level_stuff/active_level_manager_class.hpp"
#include "sprite_manager_class.hpp"

fixed24p8 player_sprite_stuff::speed;
bool player_sprite_stuff::use_16x16;
bool player_sprite_stuff::run_toggle;
//bool player_sprite_stuff::running;

const player_sprite_stuff::frame 
	player_sprite_stuff::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size] 
= { 
	// Invisible
	frm_invisible, 
	
	// Standing
	frm_stand,
	
	// Walking/running
	frm_stand, frm_walk_0, frm_walk_1, frm_walk_0
};


// Graphics constants
const u32 player_sprite_stuff::the_relative_metatile_slot_arr[]
	= { frm_invisible, frm_stand, frm_walk_0, frm_walk_1 };

const u32 player_sprite_stuff::the_relative_metatile_slot_arr_size
	= sizeof(player_sprite_stuff::the_relative_metatile_slot_arr)
	/ sizeof(u32);



void player_sprite_stuff::init( sprite& the_player, bool facing_left  )
{
	the_player.the_sprite_type = get_sprite_type();
	
	//the_player.the_oam_entry.set_tile_number 
	//	( get_curr_tile_slot_old(the_player) );
	the_player.the_oam_entry.set_tile_number
		( the_player.get_vram_chunk_index() 
		* sprite_gfx_manager::num_tiles_in_ss_32x32 );
	the_player.the_oam_entry.set_pal_number 
		( get_gfx_category(the_player) );
	
	the_player.set_shape_size(oam_entry::ss_16x32);
	the_player.the_coll_box.size = { 12 << fixed24p8::shift, 
		29 << fixed24p8::shift };
	//the_player.the_coll_box.size = { 12 << fixed24p8::shift, 
	//	30 << fixed24p8::shift };
	
	the_player.cb_pos_offset = { 2 << fixed24p8::shift, 
		3 << fixed24p8::shift };
	//the_player.cb_pos_offset = { 2 << fixed24p8::shift, 
	//	2 << fixed24p8::shift };
	
	
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
}

void player_sprite_stuff::init( sprite& the_player, 
	const vec2_f24p8& s_in_level_pos, const vec2_u32& the_level_size_2d,
	bg_point& camera_pos, bool facing_left )
{
	
	//sprite_stuff_array[the_player.the_sprite_type]->init(the_player);
	init(the_player);
	
	the_player.in_level_pos = s_in_level_pos;
	
	//the_player.in_level_pos = { 0x2000, 0x18000 };
	//the_player.the_sprite_type = st_player;
	
	
	the_player.update_f24p8_positions();
	
	the_player.update_on_screen_pos(camera_pos);
	
	
	the_player.center_camera_almost(camera_pos);
	active_level_manager::correct_bg0_scroll_mirror(the_level_size_2d);
	the_player.update_on_screen_pos(camera_pos);
	the_player.copy_the_oam_entry_to_oam_mirror(0);
	
}


void player_sprite_stuff::gfx_update( sprite& the_player )
{
	//the_player.the_oam_entry.set_tile_number
	//	( get_curr_tile_slot_old(the_player) );
	//the_player.the_oam_entry.set_tile_number
	//	( the_player.get_vram_chunk_index() 
	//	* sprite_gfx_manager::num_tiles_in_ss_32x32 );
	the_player.the_oam_entry.set_tile_number
		( get_curr_tile_slot(the_player) );
	
	the_player.the_oam_entry.set_pal_number 
		( get_gfx_category(the_player) );
}

void player_sprite_stuff::update_part_1( sprite& the_player ) 
{
	gfx_update(the_player);
	
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
			
			case st_warp_block:
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
					
					//next_debug_f24p8.data = spr.the_sprite_ipg
					//	->extra_param_0;
					////next_debug_f24p8.data 
					////	= the_dest_sle.in_level_pos.x.data
					////	* num_pixels_per_block_row;
					////next_debug_f24p8.data 
					////	= the_dest_sle.in_level_pos.y.data 
					////	* num_pixels_per_block_col;
					//next_debug_f24p8 = the_dest_sle.in_level_pos.x;
					//next_debug_f24p8 = the_dest_sle.in_level_pos.y;
					//next_debug_f24p8 = the_player.in_level_pos.x;
					//next_debug_f24p8 = the_player.in_level_pos.y;
					
					//the_player.in_level_pos = the_dest_sle.in_level_pos;
					the_player.in_level_pos.x = the_dest_sle_ptr
						->in_level_pos.x;
					the_player.in_level_pos.y = the_dest_sle_ptr
						->in_level_pos.y - make_f24p8
						( the_player.get_shape_size_as_vec2().y
						- num_pixels_per_block_col );
					//the_player.vel = vec2_f24p8();
					
					the_player.update_f24p8_positions();
					the_player.update_on_screen_pos(camera_pos);
					
					the_player.center_camera_almost(camera_pos);
					active_level_manager::correct_bg0_scroll_mirror
						(the_level_size_2d);
					the_player.update_on_screen_pos(camera_pos);
				}
				break;
				
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
	the_player.copy_the_oam_entry_to_oam_mirror(0);
}

//const u32 player_sprite_stuff::get_curr_tile_slot( sprite& the_player )
//{
//	return sprite_gfx_category_first_vram_slot_list 
//		[get_gfx_category(the_player)]
//		+ get_curr_relative_tile_slot(the_player);
//}

const u32 player_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_player )
{
	s32& walk_frame_timer = the_player.misc_data_s[sdi_walk_frame_timer];
	u32& active_walk_frame_slot = the_player.misc_data_u
		[udi_active_walk_frame_slot];
	
	if ( active_walk_frame_slot < frm_slot_walk_0 
		|| active_walk_frame_slot > frm_slot_walk_3 )
	{
		active_walk_frame_slot = frm_slot_walk_0;
	}
	
	if (the_player.on_ground)
	{
		// Standing still
		if ( speed == (fixed24p8){0} )
		{
			walk_frame_timer = 0;
			active_walk_frame_slot = frm_slot_walk_1;
			//return frame_slot_to_frame_arr[active_walk_frame_slot] 
			//	* num_active_gfx_tiles;
			return frame_slot_to_frame_arr[frm_slot_walk_0]
				* num_active_gfx_tiles;
		}
		
		// Walking speed or not-max running speed
		else if ( speed >= walk_speed && speed < max_run_speed )
		{
			++walk_frame_timer;
			
			if ( walk_frame_timer > walk_frame_timer_end )
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
			
			return frame_slot_to_frame_arr[active_walk_frame_slot] 
				* num_active_gfx_tiles;
			
		}
		
		// Max running speed
		else if ( speed == max_run_speed )
		{
			++walk_frame_timer;
			
			if ( walk_frame_timer > run_frame_timer_end )
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
	else //if ( !the_player.on_ground )
	{
		return frame_slot_to_frame_arr[frm_slot_walk_2] 
			* num_active_gfx_tiles;
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




