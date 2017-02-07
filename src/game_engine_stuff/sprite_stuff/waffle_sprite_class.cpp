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


#include "sprite_type_stuff.hpp"
#include "sprite_type_includes.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../level_stuff/active_level_manager_class.hpp"
#include "sprite_manager_class.hpp"

const sprite_const_params waffle_sprite::the_const_params
= {
	// the_const_sprite_type
	st_waffle, 
	
	// the_palette_slot
	sps_powerup, 
	
	// the_relative_metatile_slot
	0,
	
	// num_active_gfx_tiles
	sprite::the_const_params.num_active_gfx_tiles,
	
	// tile_arr 
	const_cast<tile*>(reinterpret_cast<const tile*>(the_powerup_gfxTiles)),
};


void waffle_sprite::update_part_2()
{
	// I can't remember why I needed to save the initial position of waffle
	// sprites.  Eh.
	
	u32& initial_pos_was_set = misc_data_u[udi_initial_pos_was_set];
	s32& initial_pos_x = misc_data_s[sdi_initial_pos_x];
	s32& initial_pos_y = misc_data_s[sdi_initial_pos_y];
	s32& move_timer = misc_data_s[sdi_move_timer];
	
	if ( !initial_pos_was_set )
	{
		initial_pos_was_set = true;
		
		//initial_pos_x = in_level_pos.x.data;
		//initial_pos_y = in_level_pos.y.data;
		initial_pos_x = get_curr_in_level_pos().x.data;
		initial_pos_y = get_curr_in_level_pos().y.data;
		
		move_timer = move_timer_start;
		
		// Facing left
		if ( the_oam_entry.get_hflip_status() )
		{
			vel.x.data = -( 1 << fixed24p8::shift );
		}
		
		// Facing right
		else
		{
			vel.x.data = 1 << fixed24p8::shift;
		}
		
	}
	
	if ( move_timer <= 0 )
	{
		move_timer = move_timer_start;
		
		vel.x.data = -vel.x.data;
	}
	
	--move_timer;
	
	
	update_f24p8_positions();
	block_collision_stuff();
}


// Physics and collision stuff
void waffle_sprite::block_coll_response_left_16x16_old
	( const block_coll_result& lt_coll_result,
	const block_coll_result& lb_coll_result )
{
	s32& move_timer = misc_data_s[sdi_move_timer];
	
	
	////in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 ) * 16 )
	////	- cb_pos_offset.x;
	//set_curr_in_level_pos_x( make_f24p8( ( lt_coll_result.coord.x + 1 ) 
	//	* 16 ) - cb_pos_offset.x );
	
	move_timer = move_timer_start;
	
	vel.x.data = -vel.x.data;
}


void waffle_sprite::block_coll_response_right_16x16_old
	( const block_coll_result& rt_coll_result,
	const block_coll_result& rb_coll_result )
{
	s32& move_timer = misc_data_s[sdi_move_timer];
	
	////in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 )
	////	- the_coll_box.size.x - cb_pos_offset.x;
	////	//- make_f24p8(get_shape_size_as_vec2().x);
	//set_curr_in_level_pos_x( make_f24p8( rt_coll_result.coord.x * 16 )
	//	- the_coll_box.size.x - cb_pos_offset.x );
	
	
	move_timer = move_timer_start;
	
	vel.x.data = -vel.x.data;
}



void waffle_sprite::block_coll_response_left_16x16
	( const block_coll_result_rect_group& the_bcr_rect_group )
{
	s32& move_timer = misc_data_s[sdi_move_timer];
	
	
	////in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 ) * 16 )
	////	- cb_pos_offset.x;
	//set_curr_in_level_pos_x( make_f24p8( ( lt_coll_result.coord.x + 1 ) 
	//	* 16 ) - cb_pos_offset.x );
	push_out_of_left_block(the_bcr_rect_group);
	
	move_timer = move_timer_start;
	
	vel.x.data = -vel.x.data;
}

void waffle_sprite::block_coll_response_right_16x16
	( const block_coll_result_rect_group& the_bcr_rect_group )
{
	s32& move_timer = misc_data_s[sdi_move_timer];
	
	////in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 )
	////	- the_coll_box.size.x - cb_pos_offset.x;
	////	//- make_f24p8(get_shape_size_as_vec2().x);
	//set_curr_in_level_pos_x( make_f24p8( rt_coll_result.coord.x * 16 )
	//	- the_coll_box.size.x - cb_pos_offset.x );
	push_out_of_right_block(the_bcr_rect_group);
	
	
	move_timer = move_timer_start;
	
	vel.x.data = -vel.x.data;
}



