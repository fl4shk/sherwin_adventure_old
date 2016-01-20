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


#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"

#include "sprite_manager_class.hpp"

// Graphics constants
const player_hammer_sprite_stuff::frame
	player_hammer_sprite_stuff::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size]
= {
	frm_angle_0, frm_angle_23, frm_angle_45, frm_angle_90
};




const vec2_f24p8 player_hammer_sprite_stuff::the_initial_coll_box_size
	= { {14 << fixed24p8::shift}, {14 << fixed24p8::shift} },
	player_hammer_sprite_stuff::the_initial_cb_pos_offset 
	= { {0 << fixed24p8::shift}, {0 << fixed24p8::shift} };


//void player_hammer_sprite_stuff::update_part_1( sprite& the_hammer )
//{
//	
//}

const u32 player_hammer_sprite_stuff::get_curr_relative_tile_slot
	( sprite& the_hammer )
{
	return frame_slot_to_frame_arr[the_hammer.misc_data_u
		[udi_curr_frame_slot]] * num_active_gfx_tiles;
}


