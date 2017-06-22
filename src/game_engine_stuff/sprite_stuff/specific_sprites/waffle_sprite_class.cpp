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


#include "../sprite_type_stuff.hpp"
#include "../sprite_type_includes.hpp"

#include "../../../gba_specific_stuff/button_stuff.hpp"
#include "../../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../../level_stuff/active_level_manager_class.hpp"
#include "../sprite_manager_class.hpp"

const SpriteConstParams WaffleSprite::the_const_params
= {
	// the_const_sprite_type
	StWaffle, 
	
	// the_palette_slot
	sps_powerup, 
	
	// the_relative_metatile_slot
	0,
	
	// num_active_gfx_tiles
	Sprite::the_const_params.num_active_gfx_tiles,
	
	// tile_arr 
	const_cast<tile*>(reinterpret_cast<const tile*>(the_powerup_gfxTiles)),
};


void WaffleSprite::update_part_2()
{
	// I Can't remember why I needed To save the initial position of Waffle
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
			vel.x.data = -( 1 << Fixed24p8::get_shift() );
		}
		
		// Facing right
		else
		{
			vel.x.data = 1 << Fixed24p8::get_shift();
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
void WaffleSprite::block_coll_response_left_old
	( const BlockCollResult& lt_coll_result,
	const BlockCollResult& lb_coll_result )
{
	s32& move_timer = misc_data_s[sdi_move_timer];
	
	
	////in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 ) * 16 )
	////	- cb_pos_offset.x;
	//set_curr_in_level_pos_x( make_f24p8( ( lt_coll_result.coord.x + 1 ) 
	//	* 16 ) - cb_pos_offset.x );
	
	move_timer = move_timer_start;
	
	vel.x.data = -vel.x.data;
}


void WaffleSprite::block_coll_response_right_old
	( const BlockCollResult& rt_coll_result,
	const BlockCollResult& rb_coll_result )
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



void WaffleSprite::block_coll_response_left
	( const SprBlkCollGroupBase::HorizCollTuple& hs )
{
	s32& move_timer = misc_data_s[sdi_move_timer];
	
	
	////in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 ) * 16 )
	////	- cb_pos_offset.x;
	//set_curr_in_level_pos_x( make_f24p8( ( lt_coll_result.coord.x + 1 ) 
	//	* 16 ) - cb_pos_offset.x );
	push_out_of_left_block(hs.blk_crd_pos);
	
	move_timer = move_timer_start;
	
	vel.x.data = -vel.x.data;
}

void WaffleSprite::block_coll_response_right
	( const SprBlkCollGroupBase::HorizCollTuple& hs )
{
	s32& move_timer = misc_data_s[sdi_move_timer];
	
	////in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 )
	////	- the_coll_box.size.x - cb_pos_offset.x;
	////	//- make_f24p8(get_shape_size_as_vec2().x);
	//set_curr_in_level_pos_x( make_f24p8( rt_coll_result.coord.x * 16 )
	//	- the_coll_box.size.x - cb_pos_offset.x );
	push_out_of_right_block(hs.blk_crd_pos);
	
	
	move_timer = move_timer_start;
	
	vel.x.data = -vel.x.data;
}



