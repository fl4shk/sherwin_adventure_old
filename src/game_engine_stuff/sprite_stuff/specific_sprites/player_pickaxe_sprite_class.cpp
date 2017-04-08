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


#include "../sprite_type_stuff.hpp"
#include "../sprite_type_includes.hpp"
#include "../sprite_class.hpp"

#include "../sprite_manager_class.hpp"


// Graphics constants
const player_pickaxe_sprite::frame
	player_pickaxe_sprite::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size]
= {
	frm_angle_0, frm_angle_23, frm_angle_45, frm_angle_90
};


const sprite_const_params player_pickaxe_sprite::the_const_params
= {
	// the_const_sprite_type
	st_player_pickaxe, 
	
	// the_palette_slot
	sps_secondary_0, 
	
	// the_relative_metatile_slot (not used by this class)
	0,
	
	// num_active_gfx_tiles
	gfx_manager::num_tiles_in_ss_16x16,
	
	// tile_arr 
	const_cast<tile*>(reinterpret_cast<const tile*>
		(the_16x16_secondary_sprites_gfxTiles)),
	
	// the_initial_shape_size
	oam_entry::ss_16x16,
	
	// the_initial_coll_box_size
	{ {15 << fixed24p8::get_shift()}, {15 << fixed24p8::get_shift()} },
	
	// the_initial_cb_pos_offset
	{ {0 << fixed24p8::get_shift()}, {0 << fixed24p8::get_shift()} },
};


void player_pickaxe_sprite::update_part_1()
{
	//update_f24p8_positions();
	block_collision_stuff();
}


const u32 player_pickaxe_sprite::get_curr_relative_tile_slot()
{
	return frame_slot_to_frame_arr[misc_data_u[udi_curr_frame_slot]] 
		* get_num_active_gfx_tiles();
}


// Physics and collision stuff
void player_pickaxe_sprite::block_collision_stuff()
{
	//block_collision_stuff_strongly_hit_stuff_only_16x16();
	block_collision_stuff_16x16();
}

void player_pickaxe_sprite::block_coll_response_left_16x16_old
	( const block_coll_result& lt_coll_result, 
	const block_coll_result& lb_coll_result )
{
	//block_stuff_array[lt_coll_result.the_block->type]
	//	->strongly_hit_response( active_level::the_block_at_coord
	//	(lt_coll_result.coord), lt_coll_result.coord );
	//
	//if ( lb_coll_result.coord != lt_coll_result.coord )
	//{
	//	block_stuff_array[lb_coll_result.the_block->type]
	//		->strongly_hit_response( active_level::the_block_at_coord
	//		(lb_coll_result.coord), lb_coll_result.coord );
	//}
}

void player_pickaxe_sprite::block_coll_response_top_16x16_old
	( const block_coll_result& tl_coll_result,
	const block_coll_result& tm_coll_result,
	const block_coll_result& tr_coll_result )
{
	//block_stuff_array[tl_coll_result.the_block->type]
	//	->strongly_hit_response( active_level::the_block_at_coord
	//	(tl_coll_result.coord), tl_coll_result.coord );
	//
	//if ( tm_coll_result.coord != tl_coll_result.coord )
	//{
	//	block_stuff_array[tm_coll_result.the_block->type]
	//		->strongly_hit_response( active_level::the_block_at_coord
	//		(tm_coll_result.coord), tm_coll_result.coord );
	//}
	//
	//if ( tr_coll_result.coord != tl_coll_result.coord 
	//	&& tr_coll_result.coord != tm_coll_result.coord )
	//{
	//	block_stuff_array[tr_coll_result.the_block->type]
	//		->strongly_hit_response( active_level::the_block_at_coord
	//		(tr_coll_result.coord), tr_coll_result.coord );
	//}
}

void player_pickaxe_sprite::block_coll_response_right_16x16_old
	( const block_coll_result& rt_coll_result,
	const block_coll_result& rb_coll_result )
{
	//block_stuff_array[rt_coll_result.the_block->type]
	//	->strongly_hit_response( active_level::the_block_at_coord
	//	(rt_coll_result.coord), rt_coll_result.coord );
	//
	//if ( rb_coll_result.coord != rt_coll_result.coord )
	//{
	//	block_stuff_array[rb_coll_result.the_block->type]
	//		->strongly_hit_response( active_level::the_block_at_coord
	//		(rb_coll_result.coord), rb_coll_result.coord );
	//}
}

void player_pickaxe_sprite::non_slope_block_coll_response_bot_16x16_old
	( const block_coll_result& bl_coll_result,
	const block_coll_result& bm_coll_result, 
	const block_coll_result& br_coll_result )
{
	//block_stuff_array[bl_coll_result.the_block->type]
	//	->strongly_hit_response( active_level::the_block_at_coord
	//	(bl_coll_result.coord), bl_coll_result.coord );
	//
	//if ( bm_coll_result.coord != bl_coll_result.coord )
	//{
	//	block_stuff_array[bm_coll_result.the_block->type]
	//		->strongly_hit_response( active_level::the_block_at_coord
	//		(bm_coll_result.coord), bm_coll_result.coord );
	//}
	//
	//if ( br_coll_result.coord != bl_coll_result.coord 
	//	&& br_coll_result.coord != bm_coll_result.coord )
	//{
	//	block_stuff_array[br_coll_result.the_block->type]
	//		->strongly_hit_response( active_level::the_block_at_coord
	//		(br_coll_result.coord), br_coll_result.coord );
	//}
}

