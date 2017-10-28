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


#include "../../level_stuff/active_level_class.hpp"
#include "../../../general_utility_stuff/misc_types.hpp"


const BlockStuffConstParams
	ExclamBlockStuff::the_const_params
= {
	// metatile_number
	4,

	// palette_number
	0,

	// metatile_graphics_slot
	4,
};

void ExclamBlockStuff::strongly_hit_response(Block& the_block, 
	const Vec2s32& coord)
{
	ActiveLevel::horiz_sublevel_block_data_2d.at(coord).type 
		= bt_dud;

	ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] = is_bt_dud;
}
void ExclamBlockStuff::finish_initializing_using_persistent_data
	(Block& the_block)
{
	if (ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] == is_bt_dud)
	{
		the_block.type = bt_dud;
	}
}



