#include "sprite_type_stuff.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../level_stuff/active_level_manager_class.hpp"
#include "sprite_manager_class.hpp"


const sprite_type waffle_sprite_stuff::get_sprite_type() const
{
	return st_waffle;
}

void waffle_sprite_stuff::update_part_1( sprite& the_powerup )
{
	// I can't remember why I needed to save the initial position of waffle
	// sprites.  Eh.
	u32& initial_pos_was_set 
		= the_powerup.misc_data_u[udi_initial_pos_was_set];
	s32& initial_pos_x = the_powerup.misc_data_s[sdi_initial_pos_x];
	s32& initial_pos_y = the_powerup.misc_data_s[sdi_initial_pos_y];
	s32& move_timer = the_powerup.misc_data_s[sdi_move_timer];
	
	if ( !initial_pos_was_set )
	{
		initial_pos_was_set = true;
		
		initial_pos_x = the_powerup.in_level_pos.x.data;
		initial_pos_y = the_powerup.in_level_pos.y.data;
		
		move_timer = move_timer_start;
		
		// Facing left
		if ( the_powerup.the_oam_entry.get_hflip_status() )
		{
			the_powerup.vel.x.data = -( 1 << fixed24p8::shift );
		}
		
		// Facing right
		else
		{
			the_powerup.vel.x.data = 1 << fixed24p8::shift;
		}
		
	}
	
	if ( move_timer <= 0 )
	{
		move_timer = move_timer_start;
		
		the_powerup.vel.x.data = -the_powerup.vel.x.data;
	}
	
	--move_timer;
	
	
	the_powerup.update_f24p8_positions();
	block_collision_stuff(the_powerup);
}

// Graphics stuff
//void waffle_sprite_stuff::gfx_update( sprite& the_powerup )
//{
//	the_powerup.the_oam_entry.set_tile_number 
//		( get_curr_tile_slot(the_powerup) );
//	the_powerup.the_oam_entry.set_pal_number 
//		( get_gfx_category(the_powerup) );
//}

const sprite_gfx_category waffle_sprite_stuff::get_gfx_category
	( sprite& the_powerup )
{
	return sgc_powerup;
}
const u32 waffle_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_powerup )
{
	return 0 * num_tiles_in_ss_16x16;
}


// Physics and collision stuff
void waffle_sprite_stuff::block_collision_stuff( sprite& the_powerup )
{
	block_collision_stuff_16x16(the_powerup);
}


void waffle_sprite_stuff::block_coll_response_left_16x16
	( sprite& the_powerup, const block_coll_result& lt_coll_result,
	const block_coll_result& lb_coll_result )
{
	s32& move_timer = the_powerup.misc_data_s[sdi_move_timer];
	
	the_powerup.in_level_pos.x 
		= make_f24p8( ( lt_coll_result.coord.x + 1 ) * 16 )
		- the_powerup.cb_pos_offset.x;
	
	move_timer = move_timer_start;
	
	the_powerup.vel.x.data = -the_powerup.vel.x.data;
	
}


void waffle_sprite_stuff::block_coll_response_right_16x16
	( sprite& the_powerup, const block_coll_result& rt_coll_result,
	const block_coll_result& rb_coll_result )
{
	s32& move_timer = the_powerup.misc_data_s[sdi_move_timer];
	
	the_powerup.in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 )
		- the_powerup.the_coll_box.size.x - the_powerup.cb_pos_offset.x;
		//- make_f24p8(the_powerup.get_shape_size_as_vec2().x);
	
	
	move_timer = move_timer_start;
	
	the_powerup.vel.x.data = -the_powerup.vel.x.data;
	
}



