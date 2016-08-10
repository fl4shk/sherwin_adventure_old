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


#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"
#include "door_sprite_class.hpp"

#include "../level_stuff/sublevel_class.hpp"

// Graphics stuff

const vec2_f24p8 door_sprite::the_initial_coll_box_size
	= { {14 << fixed24p8::shift}, {32 << fixed24p8::shift} },
	door_sprite::the_initial_cb_pos_offset = { {1}, {0} };

void door_sprite::shared_constructor_code_part_2( bool facing_left )
{
	// Use the default initialization function first.
	sprite::shared_constructor_code_part_2(facing_left);
	
	// Door sprites should be thought of as part of the "background".
	// Other sprites are supposed to appear in front of the door sprites,
	// no matter which OAM entries are involved.
	clear_and_set_bits( the_oam_entry.attr2, obj_attr2_prio_mask, 
		obj_attr2_prio_2 );
}



//// This function needs to be updated to support levels that have multiple 
//// sublevels, which is likely to be the usual case.
//const sublevel_entrance& door_sprite::get_dest_sle()
//{
//	// the_door.the_sprite_ipg->extra_param_0 contains the
//	// destination of the st_door, or at least, it's SUPPOSED to
//	// contain the destination.
//	
//	//next_debug_f24p8.data = active_level::the_current_sublevel_ptr
//	//	.sublevel_entrance_arr_arr_helper.the_array
//	//	[the_door.the_sprite_ipg->extra_param_0];
//	//next_debug_f24p8.data = the_door.the_sprite_ipg->extra_param_0;
//	
//	//return active_level::the_current_sublevel_ptr_ptr
//	//	->sublevel_entrance_arr_arr_helper.the_array
//	//	[the_door.the_sprite_ipg->extra_param_0];
//	//return active_level::the_current_level_ptr->get_the_sublevels()
//	//	[active_level::the_current_active_sublevel_index]
//	//	->sublevel_entrance_arr_arr_helper.the_array
//	//	[the_door.the_sprite_ipg->extra_param_0];
//	
//	return active_level::get_the_current_sublevel_ptr()
//		.sublevel_entrance_arr_arr_helper.the_array
//		[the_door.the_sprite_ipg->extra_param_0];
//}

