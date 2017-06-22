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


#include "../../level_stuff/active_level_class.hpp"
#include "../../../general_utility_stuff/misc_types.hpp"

const BlockStuffConstParams
	AirBlockStuff::the_const_params
= {
	// metatile_number
	0,
	
	// palette_number
	0,
	
	// metatile_graphics_slot
	0,
	
	// behavior_type 
	bbvt_air,
};

void AirBlockStuff::strongly_hit_response( Block& the_block, 
	const vec2_s32& coord )
{
}

