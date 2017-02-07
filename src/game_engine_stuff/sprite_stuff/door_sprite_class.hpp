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


#ifndef door_sprite_stuff_class_hpp
#define door_sprite_stuff_class_hpp

#include "../../gfx/the_door_gfx.h"


class sprite;
class sublevel_entrance;

class door_sprite : public sprite
{
public:		// variables
	static const sprite_const_params the_const_params;
	
	
public:		// functions
	inline door_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	virtual void shared_constructor_code_part_2( bool facing_left );
	
	inline virtual const sprite_const_params& get_const_params() const
	{
		return the_const_params;
	}
	
	// Graphics stuff
	//virtual void gfx_update();
	
	
	// Initial
	//static const sublevel_entrance& get_dest_sle();
	
	
	// Physics and collision stuff
	//// All door sprites are not affected by gravity, and they don't move.
	//virtual void block_collision_stuff();
	
	
} __attribute__((_align4));


#endif		// door_sprite_stuff_class_hpp
