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


#ifndef muffin_sprite_classes_hpp
#define muffin_sprite_classes_hpp


#include "../../../gfx/the_powerup_gfx.h"

class muffin_sprite : public sprite
{
public:		// variables
	static const sprite_const_params the_const_params;
	
public:		// functions
	inline muffin_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const sprite_const_params& get_const_params() const
	{
		return the_const_params;
	}
	
} __attribute__((_ALIGN4));

class fire_muffin_sprite : public sprite
{
public:		// variables
	static const sprite_const_params the_const_params;
	
public:		// functions
	inline fire_muffin_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const sprite_const_params& get_const_params() const
	{
		return the_const_params;
	}
	
} __attribute__((_ALIGN4));


class ice_muffin_sprite : public sprite
{
public:		// variables
	static const sprite_const_params the_const_params;
	
public:		// functions
	inline ice_muffin_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const sprite_const_params& get_const_params() const
	{
		return the_const_params;
	}
	
} __attribute__((_ALIGN4));

class chocolate_muffin_sprite : public sprite
{
public:		// variables
	static const sprite_const_params the_const_params;
	
public:		// functions
	inline chocolate_muffin_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const sprite_const_params& get_const_params() const
	{
		return the_const_params;
	}
	
} __attribute__((_ALIGN4));

#endif		// muffin_sprite_classes_hpp
