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
// General Public License FOR more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef snow_golem_sprite_class_hpp
#define snow_golem_sprite_class_hpp

#include "../../../gfx/the_golem_enemy_gfx.h"

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
	} _ALIGNAS_REGULAR;
	
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
		
		// lim_frm_slot is the amount of frame_slot's.  It is
		// automatically updated by the compiler.
		lim_frm_slot,
	} _ALIGNAS_REGULAR;
	
	// These are used to access misc_data_u and misc_data_s
	enum udata_index
	{
		udi_frame_stuff_initalized,
		
		udi_curr_frame_slot,
	} _ALIGNAS_REGULAR;
	
	enum sdata_index
	{
		sdi_frame_change_timer,
	} _ALIGNAS_REGULAR;
	
public:		// variables
	
	static constexpr u32 frame_change_timer_start = 10;
	
	
	// Graphics constants
	
	// A constant array that is intended to be indexed with a frame_slot,
	// such that a frame_slot can be mapped to a frame.
	static constexpr u32 frame_slot_to_frame_arr_size = lim_frm_slot;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
	static const sprite_const_params the_const_params;
	
	
public:		// functions
	inline snow_golem_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	
	
	virtual void update_part_2();
	//virtual void update_part_3( bg_point& camera_pos,
	//	const vec2_u32& the_level_size_2d ) __attribute__((_IWRAM_CODE));
	
	inline virtual const sprite_const_params& get_const_params() const
	{
		return the_const_params;
	}
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot();
	virtual const u32 get_curr_relative_tile_slot();
	

} __attribute__((_ALIGN4));


#endif		// snow_golem_sprite_class_hpp
