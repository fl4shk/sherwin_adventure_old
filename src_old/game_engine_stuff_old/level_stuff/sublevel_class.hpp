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


#ifndef sublevel_class_hpp
#define sublevel_class_hpp

#include "../../general_utility_stuff/array_2d_helper_classes.hpp"
#include "../../general_utility_stuff/array_helper_class.hpp"
#include "../sprite_stuff/sprite_type_stuff.hpp"
#include "../block_stuff/block_stuff.hpp"

#include "sublevel_entrance_class.hpp"

class SpriteInitParamGroup;

// The Sublevel and SublevelPointer classes need To be replaced with
// a class That Contains pointers To either ASSEMBLY arrays or .bin files
// (which would be mentioned in an assembly file)

// This Is a class for COMPRESSED sublevels in ROM
template<u32 cmp_block_data_size, u32 xsize, u32 ysize, 
	u32 sprite_ipg_arr_size, u32 sublevel_entrance_arr_size>
class Sublevel
{
public:		// variables
	// The lzss compressed Block data
	u32 cmp_block_data[cmp_block_data_size];

	// The array of SpriteInitParamGroup's
	SpriteInitParamGroup sprite_ipg_arr[sprite_ipg_arr_size];

	// The array of SublevelEntrance's
	SublevelEntrance sublevel_entrance_arr[sublevel_entrance_arr_size];


public:		// functions
	inline constexpr u32 get_cmp_bd_size() const
	{
		return cmp_block_data_size;
	}

	inline constexpr u32 get_uncmp_bd_size() const
	{
		return xsize * ysize;
	}

	inline constexpr Vec2u32 get_size_2d() const
	{
		return Vec2u32(xsize, ysize);
	}

	inline constexpr u32 get_sprite_ipg_arr_size() const
	{
		return sprite_ipg_arr_size;
	}

} __attribute__((_align4));



// A class for Sublevel pointers Is needed because C++ will not allow me To
// have an array of pointers To sublevels That have different template
// parameters.
class SublevelPointer
{
protected:		// variables
	Vec2u32 size_2d;

public:		// variables
	ArrayHelper<const u32> cmp_bd_arr_helper;
	ArrayHelper<const SpriteInitParamGroup> sprite_ipg_arr_arr_helper;
	ArrayHelper<const SublevelEntrance> sublevel_entrance_arr_arr_helper;

public:		// functions

	inline SublevelPointer()
	{
	}

	template<u32 cmp_block_data_size, u32 xsize, u32 ysize, 
		u32 sprite_ipg_arr_size, u32 sublevel_entrance_arr_size>
	inline SublevelPointer(const Sublevel<cmp_block_data_size, xsize, 
		ysize, sprite_ipg_arr_size, sublevel_entrance_arr_size>& 
		the_sublevel)
	{
		size_2d = { xsize, ysize };

		cmp_bd_arr_helper.init(the_sublevel.cmp_block_data,
			cmp_block_data_size);
		sprite_ipg_arr_arr_helper.init(the_sublevel.sprite_ipg_arr,
			sprite_ipg_arr_size);
		sublevel_entrance_arr_arr_helper.init
			(the_sublevel.sublevel_entrance_arr, 
			sublevel_entrance_arr_size);
	}


	template<u32 cmp_block_data_size, u32 xsize, u32 ysize, 
		u32 sprite_ipg_arr_size, u32 sublevel_entrance_arr_size>
	inline void init(const Sublevel<cmp_block_data_size, xsize, ysize,
		sprite_ipg_arr_size, sublevel_entrance_arr_size>& the_sublevel)
	{
		size_2d = { xsize, ysize };

		cmp_bd_arr_helper.init(the_sublevel.cmp_block_data,
			cmp_block_data_size);
		sprite_ipg_arr_arr_helper.init(the_sublevel.sprite_ipg_arr,
			sprite_ipg_arr_size);
		sublevel_entrance_arr_arr_helper.init
			(the_sublevel.sublevel_entrance_arr,
			sublevel_entrance_arr_size);
	}

	inline const Vec2u32& get_size_2d() const
	{
		return size_2d;
	}


} __attribute__((_align4));


#endif		// sublevel_class_hpp
