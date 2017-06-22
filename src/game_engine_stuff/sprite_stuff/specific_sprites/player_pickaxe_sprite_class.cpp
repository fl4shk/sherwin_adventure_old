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
#include "../sprite_class.hpp"

#include "../sprite_manager_class.hpp"


// Graphics constants
const PlayerPickaxeSprite::frame
	PlayerPickaxeSprite::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size]
= {
	frm_angle_0, frm_angle_23, frm_angle_45, frm_angle_90
};


const SpriteConstParams PlayerPickaxeSprite::the_const_params
= {
	// the_const_sprite_type
	StPlayerPickaxe, 
	
	// the_palette_slot
	sps_secondary_0, 
	
	// the_relative_metatile_slot (not used by this class)
	0,
	
	// num_active_gfx_tiles
	GfxManager::num_tiles_in_ss_16x16,
	
	// tile_arr 
	const_cast<tile*>(reinterpret_cast<const tile*>
		(the_16x16_secondary_sprites_gfxTiles)),
	
	// the_initial_shape_size
	OamEntry::ss_16x16,
	
	// the_initial_coll_box_size
	{ {15 << Fixed24p8::get_shift()}, {15 << Fixed24p8::get_shift()} },
	
	// the_initial_cb_pos_offset
	{ {0 << Fixed24p8::get_shift()}, {0 << Fixed24p8::get_shift()} },
};


void PlayerPickaxeSprite::update_part_1()
{
	//update_f24p8_positions();
	block_collision_stuff();
}


const u32 PlayerPickaxeSprite::get_curr_relative_tile_slot()
{
	return frame_slot_to_frame_arr[misc_data_u[udi_curr_frame_slot]] 
		* get_num_active_gfx_tiles();
}


// Physics and collision stuff
void PlayerPickaxeSprite::block_collision_stuff()
{
	//block_collision_stuff_strongly_hit_stuff_only_16x16();
	block_collision_stuff_16x16();
}

void PlayerPickaxeSprite::block_coll_response_left_16x16_old
	( const BlockCollResult& lt_coll_result, 
	const BlockCollResult& lb_coll_result )
{
	//block_stuff_array[lt_coll_result.the_block->type]
	//	->strongly_hit_response( ActiveLevel::the_block_at_coord
	//	(lt_coll_result.coord), lt_coll_result.coord );
	//
	//if ( lb_coll_result.coord != lt_coll_result.coord )
	//{
	//	block_stuff_array[lb_coll_result.the_block->type]
	//		->strongly_hit_response( ActiveLevel::the_block_at_coord
	//		(lb_coll_result.coord), lb_coll_result.coord );
	//}
}

void PlayerPickaxeSprite::block_coll_response_top_16x16_old
	( const BlockCollResult& tl_coll_result,
	const BlockCollResult& tm_coll_result,
	const BlockCollResult& tr_coll_result )
{
	//block_stuff_array[tl_coll_result.the_block->type]
	//	->strongly_hit_response( ActiveLevel::the_block_at_coord
	//	(tl_coll_result.coord), tl_coll_result.coord );
	//
	//if ( tm_coll_result.coord != tl_coll_result.coord )
	//{
	//	block_stuff_array[tm_coll_result.the_block->type]
	//		->strongly_hit_response( ActiveLevel::the_block_at_coord
	//		(tm_coll_result.coord), tm_coll_result.coord );
	//}
	//
	//if ( tr_coll_result.coord != tl_coll_result.coord 
	//	&& tr_coll_result.coord != tm_coll_result.coord )
	//{
	//	block_stuff_array[tr_coll_result.the_block->type]
	//		->strongly_hit_response( ActiveLevel::the_block_at_coord
	//		(tr_coll_result.coord), tr_coll_result.coord );
	//}
}

void PlayerPickaxeSprite::block_coll_response_right_16x16_old
	( const BlockCollResult& rt_coll_result,
	const BlockCollResult& rb_coll_result )
{
	//block_stuff_array[rt_coll_result.the_block->type]
	//	->strongly_hit_response( ActiveLevel::the_block_at_coord
	//	(rt_coll_result.coord), rt_coll_result.coord );
	//
	//if ( rb_coll_result.coord != rt_coll_result.coord )
	//{
	//	block_stuff_array[rb_coll_result.the_block->type]
	//		->strongly_hit_response( ActiveLevel::the_block_at_coord
	//		(rb_coll_result.coord), rb_coll_result.coord );
	//}
}

void PlayerPickaxeSprite::non_slope_block_coll_response_bot_16x16_old
	( const BlockCollResult& bl_coll_result,
	const BlockCollResult& bm_coll_result, 
	const BlockCollResult& br_coll_result )
{
	//block_stuff_array[bl_coll_result.the_block->type]
	//	->strongly_hit_response( ActiveLevel::the_block_at_coord
	//	(bl_coll_result.coord), bl_coll_result.coord );
	//
	//if ( bm_coll_result.coord != bl_coll_result.coord )
	//{
	//	block_stuff_array[bm_coll_result.the_block->type]
	//		->strongly_hit_response( ActiveLevel::the_block_at_coord
	//		(bm_coll_result.coord), bm_coll_result.coord );
	//}
	//
	//if ( br_coll_result.coord != bl_coll_result.coord 
	//	&& br_coll_result.coord != bm_coll_result.coord )
	//{
	//	block_stuff_array[br_coll_result.the_block->type]
	//		->strongly_hit_response( ActiveLevel::the_block_at_coord
	//		(br_coll_result.coord), br_coll_result.coord );
	//}
}

