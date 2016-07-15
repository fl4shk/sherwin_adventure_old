// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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


#ifndef snow_golem_sprite_class_hpp
#define snow_golem_sprite_class_hpp

#include "../../gfx/the_golem_enemy_gfx.h"

class snow_golem_sprite : public sprite
{
public:		// enums
	// "Global" graphics frames
	enum frame
	{
		// Standing frame
		frm_stand = 0, 
		
		// Snowball throwing frames
		frm_throw_0 = 1, 
		frm_throw_1 = 2,
		frm_throw_2 = 3,
	} alignas(4);
	
	// This enum allows multiple frame_slot's to be represented by the same
	// frame.
	enum frame_slot
	{
		// Standing
		frm_slot_stand,
		
		// Throwing a snowball
		frm_slot_throw_0,
		frm_slot_throw_1, 
		frm_slot_throw_2, 
		
		// frm_slot_count is the amount of frame_slot's.  It is
		// automatically updated by the compiler.
		frm_slot_count,
	} alignas(4);
	
	// These are used to access misc_data_u and misc_data_s
	enum udata_index
	{
		udi_frame_stuff_initalized,
		
		udi_curr_frame_slot,
	} alignas(4);
	
	enum sdata_index
	{
		sdi_frame_change_timer,
	} alignas(4);
	
public:		// variables
	
	static constexpr u32 frame_change_timer_start = 10;
	
	
	// Graphics constants
	
	// A constant array that is intended to be indexed with a frame_slot,
	// such that a frame_slot can be mapped to a frame.
	static constexpr u32 frame_slot_to_frame_arr_size = frm_slot_count;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
	static constexpr sprite_type the_const_sprite_type = st_snow_golem;
	static constexpr sprite_palette_slot the_palette_slot = sps_enemy_0;
	
	static constexpr u32 num_active_gfx_tiles 
		= gfx_manager::num_tiles_in_ss_16x32;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(the_golem_enemy_gfxTiles));
	
	static const oam_entry::shape_size the_initial_shape_size 
		= oam_entry::ss_16x32;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
public:		// functions
	inline snow_golem_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	
	inline virtual const sprite_type get_const_sprite_type() const
	{
		return the_const_sprite_type;
	}
	
	virtual void update_part_2();
	//virtual void update_part_3( bg_point& camera_pos,
	//	const vec2_u32& the_level_size_2d ) __attribute__((_iwram_code));
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot();
	
	inline virtual const sprite_palette_slot get_palette_slot()
	{
		return the_palette_slot;
	}
	virtual const u32 get_curr_relative_tile_slot();
	
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
	}
	
	inline virtual const oam_entry::shape_size get_the_initial_shape_size() 
		const
	{
		return the_initial_shape_size;
	}
	
	inline virtual const vec2_f24p8& get_the_initial_coll_box_size() const
	{
		return the_initial_coll_box_size;
	}
	inline virtual const vec2_f24p8& get_the_initial_cb_pos_offset() const
	{
		return the_initial_cb_pos_offset;
	}
	
} __attribute__((_align4));


#endif		// snow_golem_sprite_class_hpp
