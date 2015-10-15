#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../level_stuff/active_level_manager_class.hpp"
#include "sprite_manager_class.hpp"

fixed24p8 player_sprite_stuff::speed __attribute__((_iwram));
bool player_sprite_stuff::use_16x16 __attribute__((_iwram));
bool player_sprite_stuff::run_toggle __attribute__((_iwram));


void player_sprite_stuff::init( sprite& the_player, bool facing_left  )
{
	the_player.the_sprite_type = get_sprite_type();
	
	the_player.the_oam_entry.set_tile_number 
		( get_curr_tile_slot(the_player) );
	the_player.the_oam_entry.set_pal_number 
		( get_gfx_category(the_player) );
	
	the_player.set_shape_size(oam_entry::ss_16x32);
	the_player.the_coll_box.size = { 14 << fixed24p8::shift, 
		30 << fixed24p8::shift };
	the_player.cb_pos_offset = { 2 << fixed24p8::shift, 
		2 << fixed24p8::shift };
	
	//use_16x16 = false;
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


const sprite_type player_sprite_stuff::get_sprite_type() const
{
	return st_player;
}

void player_sprite_stuff::gfx_update( sprite& the_player )
{
	the_player.the_oam_entry.set_tile_number
		( get_curr_tile_slot(the_player) );
	the_player.the_oam_entry.set_pal_number 
		( get_gfx_category(the_player) );
}

void player_sprite_stuff::update_part_1( sprite& the_player ) 
{
	gfx_update(the_player);
	
	//if ( key_hit(key_r) )
	//{
	//	if ( !use_16x32 )
	//	{
	//		use_16x32 = true;
	//		the_player.set_shape_size(oam_entry::ss_16x32);
	//		the_player.the_coll_box.size.y = make_f24p8(30);
	//		the_player.in_level_pos.y -= ( make_f24p8(16) - the_player
	//			.cb_pos_offset.y );
	//	}
	//	else
	//	{
	//		use_16x32 = false;
	//		the_player.set_shape_size(oam_entry::ss_16x16);
	//		the_player.the_coll_box.size.y = make_f24p8(14);
	//	}
	//}
	
	speed = {0x100};
	
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
	
	if ( run_toggle )
	{
		speed = {0x200};
	}
	
	
	if ( key_hit_or_held(key_left) )
	{
		the_player.vel.x = -speed;
		the_player.the_oam_entry.enable_hflip();
	}
	else if ( key_hit_or_held(key_right) )
	{
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
	
	for ( auto iter=sprite_manager::the_sprites.begin();
		iter!=sprite_manager::the_sprites.end();
		++iter )
	{
		switch ( iter->the_sprite_type )
		{
			//case st_waffle:
			case st_muffin:
			case st_fire_muffin:
			case st_ice_muffin:
			case st_chocolate_muffin:
				if ( coll_box_intersects_now( the_player.the_coll_box,
					iter->the_coll_box ) )
				{
					iter->the_sprite_type = st_default;
					iter->the_sprite_ipg->spawn_state = sss_dead;
				}
				break;
				
			default:
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

const sprite_gfx_category player_sprite_stuff::get_gfx_category 
	( sprite& the_player )
{
	return the_gfx_category;
}
const u32 player_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_player )
{
	return relative_tile_slot;
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




