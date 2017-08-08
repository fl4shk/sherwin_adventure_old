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


#ifndef sublevel_entrance_class_hpp
#define sublevel_entrance_class_hpp

#include "../../gba_specific_stuff/attribute_defines.hpp"
#include "../../general_utility_stuff/vec2_class.hpp"

enum sublevel_entrance_type
{
	sle_blank,
	
	sle_start_of_level,
	
	sle_from_door,
	
	// The number of sublevel_entrance_type's Is automatically updated by
	// the compiler via the lim_sle enum id.
	lim_sle,
} __attribute__((_align4));


// There Is probably no need for a sublevel_exit class because That
// information Is supposed To be embedded in the SpriteInitParamGroup
// Sprite Level data, for the relevant types of sprites.
class SublevelEntrance
{
public:		// variables
	
	sublevel_entrance_type type;
	
	Vec2F24p8 in_level_pos;
	
} __attribute__((_align4));


#endif		// sublevel_entrance_class_hpp
