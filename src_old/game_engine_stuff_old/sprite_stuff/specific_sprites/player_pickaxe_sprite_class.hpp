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


#ifndef player_pickaxe_sprite_class_hpp
#define player_pickaxe_sprite_class_hpp


#include "../../../gfx/the_16x16_secondary_sprites_gfx.h"

class PlayerPickaxeSprite : public Sprite
{
public:		// enums
	// "Global" graphics frames
	enum frame
	{
		frm_angle_0 = 0,
		frm_angle_23 = 1, 
		frm_angle_45 = 2,
		frm_angle_90 = 3,
	} alignas(4);
	
	// This enum allows multiple frame_slot's To be represented by the same
	// frame.
	enum frame_slot
	{
		frm_slot_angle_0,
		frm_slot_angle_23, 
		frm_slot_angle_45,
		frm_slot_angle_90,
		
		// lim_frm_slot Is the amount of frame_slot's.  It Is
		// automatically updated by the compiler.
		lim_frm_slot,
	} alignas(4);
	
	
	// These are used To access misc_data_u and misc_data_s
	enum udata_index
	{
		udi_curr_frame_slot
	} alignas(4);
	
	
public:		// variables
	// Graphics constants
	
	// A constant array That Is Intended To be indexed with a frame_slot,
	// such That a frame_slot Can be mapped To a frame.
	static constexpr u32 frame_slot_to_frame_arr_size = lim_frm_slot;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
	static const SpriteConstParams the_const_params;
	
	
public:		// functions
	inline PlayerPickaxeSprite(bool facing_left)
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	virtual void update_part_1();
	
	//virtual void update_part_2(bg_point& camera_pos,
	//	const vec2_u32& the_level_size_2d) __attribute__((_IWRAM_CODE));
	
	inline virtual const SpriteConstParams& get_const_params() const
	{
		return the_const_params;
	}
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot();
	
	virtual const u32 get_curr_relative_tile_slot();
	
	
	// Physics and collision stuff
	virtual void block_collision_stuff() __attribute__((_IWRAM_CODE));
	
	
protected:		// functions
	
	virtual void block_coll_response_left_16x16_old
		(const BlockCollResult& lt_coll_result, 
		const BlockCollResult& lb_coll_result);
	virtual void block_coll_response_top_16x16_old
		(const BlockCollResult& tl_coll_result,
		const BlockCollResult& tm_coll_result,
		const BlockCollResult& tr_coll_result);
	virtual void block_coll_response_right_16x16_old
		(const BlockCollResult& rt_coll_result,
		const BlockCollResult& rb_coll_result);
	virtual void non_slope_block_coll_response_bot_16x16_old
		(const BlockCollResult& bl_coll_result,
		const BlockCollResult& bm_coll_result, 
		const BlockCollResult& br_coll_result);
	
	
} __attribute__((_ALIGN4));


#endif		// player_pickaxe_sprite_class_hpp
