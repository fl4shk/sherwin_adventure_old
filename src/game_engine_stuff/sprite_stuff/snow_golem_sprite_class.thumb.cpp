// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#include "sprite_type_stuff.hpp"
#include "sprite_type_includes.hpp"

#include "sprite_class.hpp"

#include "sprite_manager_class.hpp"


// Graphics constants
const snow_golem_sprite::frame snow_golem_sprite::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size]
= {
	// Standing
	frm_stand,
	
	// Throwing a snowball
	frm_throw_0, frm_throw_1, frm_throw_2
};

// This needs to be better fit to snow golem enemies.
const vec2_f24p8 snow_golem_sprite::the_initial_coll_box_size 
	= { {12 << fixed24p8::shift }, {29 << fixed24p8::shift } },
	snow_golem_sprite::the_initial_cb_pos_offset 
	= { {2 << fixed24p8::shift }, {3 << fixed24p8::shift } };


void snow_golem_sprite::update_part_2()
{
	// Eventually, interesting stuff should happen in this function.
	
	u32& frame_stuff_initialized = misc_data_u[udi_frame_stuff_initalized];
	u32& curr_frame_slot = misc_data_u[udi_curr_frame_slot];
	
	s32& frame_change_timer = misc_data_s[sdi_frame_change_timer];
	
	// This could just as easily be done in the init() function, but that'd
	// require re-implementing it for this class.
	if (!frame_stuff_initialized)
	{
		frame_stuff_initialized = 1;
		
		curr_frame_slot = frm_slot_stand;
		frame_change_timer = frame_change_timer_start;
		return;
	}
	
	--frame_change_timer;
	
	if ( frame_change_timer < 0 )
	{
		frame_change_timer = frame_change_timer_start;
		++curr_frame_slot;
		
		if ( curr_frame_slot >= frm_slot_count )
		{
			curr_frame_slot = 0;
		}
	}
	
	update_f24p8_positions();
}


// Graphics stuff
const u32 snow_golem_sprite::get_curr_relative_tile_slot()
{
	//// Temporary!
	//return frame_slot_to_frame_arr[frm_slot_throw_2] 
	//	* num_active_gfx_tiles;
	
	// Temporary!
	u32& curr_frame_slot = misc_data_u[udi_curr_frame_slot];
	return frame_slot_to_frame_arr[curr_frame_slot] * num_active_gfx_tiles;
}


