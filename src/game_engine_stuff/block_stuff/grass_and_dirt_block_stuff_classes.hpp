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


#ifndef grass_and_dirt_block_stuff_classes_hpp
#define grass_and_dirt_block_stuff_classes_hpp


class grass_single_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 6;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	// Turns out that inline virtual is not actually inline.
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));

class grass_top_left_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 7;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));
class grass_top_middle_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 8;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));
class grass_top_right_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 9;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));


class dirt_middle_left_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 10;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));
class dirt_middle_middle_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 11;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));
class dirt_middle_right_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 12;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));

class dirt_bottom_left_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 13;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));
class dirt_bottom_middle_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 14;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));
class dirt_bottom_right_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 15;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));

// Slopes
class grass_slope_p16_p16_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 16;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	static constexpr block_behavior_type behavior_type 
		= bbvt_slope_p16_p16;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
	virtual block_behavior_type get_behavior_type();
} __attribute__((_align4));
class grass_slope_n16_p16_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 17;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	static constexpr block_behavior_type behavior_type 
		= bbvt_slope_n16_p16;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
	virtual block_behavior_type get_behavior_type();
} __attribute__((_align4));

class grass_slope_p32_p16_short_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 18;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	static constexpr block_behavior_type behavior_type 
		= bbvt_slope_p32_p16_short;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
	virtual block_behavior_type get_behavior_type();
} __attribute__((_align4));

class grass_slope_p32_p16_tall_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 19;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	static constexpr block_behavior_type behavior_type 
		= bbvt_slope_p32_p16_tall;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
	virtual block_behavior_type get_behavior_type();
} __attribute__((_align4));

class grass_slope_n32_p16_tall_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 20;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	static constexpr block_behavior_type behavior_type 
		= bbvt_slope_n32_p16_tall;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
	virtual block_behavior_type get_behavior_type();
} __attribute__((_align4));
class grass_slope_n32_p16_short_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 21;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	static constexpr block_behavior_type behavior_type 
		= bbvt_slope_n32_p16_short;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
	virtual block_behavior_type get_behavior_type();
} __attribute__((_align4));

class grass_in_slope_left_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 22;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));
class grass_in_slope_right_block_stuff : public block_base_stuff
{
public:		// variables
	static constexpr u32 metatile_number = 23;
	static constexpr u32 palette_number = 0;
	static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
} __attribute__((_align4));


#endif		// grass_and_dirt_block_stuff_classes_hpp
