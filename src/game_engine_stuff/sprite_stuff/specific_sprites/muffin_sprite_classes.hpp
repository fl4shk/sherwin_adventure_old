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


#ifndef muffin_sprite_classes_hpp
#define muffin_sprite_classes_hpp


#include "../../../gfx/the_powerup_gfx.h"

class MuffinSprite : public Sprite
{
public:		// variables
	static const SpriteConstParams the_const_params;
	
public:		// functions
	inline MuffinSprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const SpriteConstParams& get_const_params() const
	{
		return the_const_params;
	}
	
} __attribute__((_ALIGN4));

class FireMuffinSprite : public Sprite
{
public:		// variables
	static const SpriteConstParams the_const_params;
	
public:		// functions
	inline FireMuffinSprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const SpriteConstParams& get_const_params() const
	{
		return the_const_params;
	}
	
} __attribute__((_ALIGN4));


class IceMuffinSprite : public Sprite
{
public:		// variables
	static const SpriteConstParams the_const_params;
	
public:		// functions
	inline IceMuffinSprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const SpriteConstParams& get_const_params() const
	{
		return the_const_params;
	}
	
} __attribute__((_ALIGN4));

class ChocolateMuffinSprite : public Sprite
{
public:		// variables
	static const SpriteConstParams the_const_params;
	
public:		// functions
	inline ChocolateMuffinSprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const SpriteConstParams& get_const_params() const
	{
		return the_const_params;
	}
	
} __attribute__((_ALIGN4));

#endif		// muffin_sprite_classes_hpp
