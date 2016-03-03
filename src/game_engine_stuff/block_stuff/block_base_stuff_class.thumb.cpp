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


#include "../level_stuff/active_level_class.hpp"
#include "../misc_types.hpp"

const u32 block_base_stuff::get_metatile_number()
{
	return metatile_number;
}
const u32 block_base_stuff::get_palette_number()
{
	return palette_number;
}
const u32 block_base_stuff::get_metatile_graphics_slot()
{
	return metatile_graphics_slot;
}

// Dummy function to be implemented by classes that inherit from this one,
// if they need it.
void block_base_stuff::strongly_hit_response( block& the_block, 
	const vec2_s32& coord )
{
}

// Dummy function to be implemented by classes that inherit from this one,
// if they need it.
void block_base_stuff::finish_initializing_using_persistent_data
	( block& the_block )
{
}


