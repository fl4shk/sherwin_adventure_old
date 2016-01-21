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


#ifndef player_pickaxe_sprite_stuff_class_hpp
#define player_pickaxe_sprite_stuff_class_hpp


#include "../../gfx/the_16x16_secondary_sprites_gfx.h"

class player_pickaxe_sprite_stuff : public sprite_base_stuff
{
public:		// enums
	// "Global" graphics frames
	enum frame
	{
		frm_angle_0 = 0,
		frm_angle_23 = 1, 
		frm_angle_45 = 2,
		frm_angle_90 = 3,
		
	} __attribute__((_align4));
	
	// This enum allows multiple frame_slot's to be represented by the same
	// frame.
	enum frame_slot 
	{
		frm_slot_angle_0,
		frm_slot_angle_23, 
		frm_slot_angle_45,
		frm_slot_angle_90,
		
		// frm_slot_count is the amount of frame_slot's.  It is
		// automatically updated by the compiler.
		frm_slot_count,
		
	} __attribute__((_align4));
	
	
	// These are used to access misc_data_u and misc_data_s
	enum udata_index { udi_curr_frame_slot } __attribute__((_align4));
	
	
public:		// variables
	// Graphics constants
	
	// A constant array that is intended to be indexed with a frame_slot,
	// such that a frame_slot can be mapped to a frame.
	static constexpr u32 frame_slot_to_frame_arr_size = frm_slot_count;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
	static constexpr sprite_type the_sprite_type = st_player_pickaxe;
	static constexpr sprite_palette_slot the_palette_slot 
		= sps_secondary_0;
	
	static constexpr u32 num_active_gfx_tiles 
		= gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>
		(the_16x16_secondary_sprites_gfxTiles));
	
	static const oam_entry::shape_size the_initial_shape_size 
		= oam_entry::ss_16x16;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
	
public:		// functions
	
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	//virtual void update_part_1( sprite& the_pickaxe );
	
	//virtual void update_part_2( sprite& the_pickaxe, bg_point& camera_pos,
	//	const vec2_u32& the_level_size_2d ) __attribute__((_iwram_code));
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot( sprite& the_pickaxe );
	
	inline virtual const sprite_palette_slot get_palette_slot 
		( sprite& the_pickaxe )
	{
		return the_palette_slot;
	}
	virtual const u32 get_curr_relative_tile_slot( sprite& the_pickaxe );
	
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


#endif		// player_pickaxe_sprite_stuff_class_hpp
