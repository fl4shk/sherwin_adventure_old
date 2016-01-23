// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#ifndef block_stuff_hpp
#define block_stuff_hpp

#include "../../gba_specific_stuff/attribute_defines.hpp"
#include "../misc_types.hpp"
#include "../array_2d_helper_class.hpp"
#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"

#include <array>

// These block_type's are used by BG0
enum block_type
{
	// A graphics-less block that sprites are free to move through.
	bt_air,
	
	// A block that looks like a wooden log.  It is indestructible, which
	// is quite unlike real life wooden logs.
	bt_log,
	
	// A wooden block without anything inside.  It is destroyed (that is,
	// replaced with an air block) when strongly hit.
	bt_wood,
	
	// A block with eyes without anything inside.  It becomes an empty
	// block upon being strongly hit.
	bt_eyes,
	
	// A block with an exclamation point on it.  The purpose of these
	// blocks is yet to be chosen, but I'm thinking that some kind of event
	// will happen when one is strongly hit.
	bt_exclam,
	
	// An empty block that is indestructible.  
	bt_dud,
	
	// Wooden blocks with contents
	bt_wood_with_bt_dud,
	bt_wood_with_st_waffle,
	bt_wood_with_st_muffin,
	bt_wood_with_st_fire_muffin,
	bt_wood_with_st_ice_muffin,
	bt_wood_with_st_chocolate_muffin,
	
	// Eyes blocks with contents
	//bt_eyes_with_bt_dud		// This is the same as bt_eyes.
	bt_eyes_with_st_waffle,
	bt_eyes_with_st_muffin,
	bt_eyes_with_st_fire_muffin,
	bt_eyes_with_st_ice_muffin,
	bt_eyes_with_st_chocolate_muffin,
	
	
	// Grass/Dirt blocks
	bt_grass_single,
	
	bt_grass_top_left,
	bt_grass_top_middle,
	bt_grass_top_right,
	
	bt_dirt_middle_left,
	bt_dirt_middle_middle,
	bt_dirt_middle_right,
	
	bt_dirt_bottom_left,
	bt_dirt_bottom_middle,
	bt_dirt_bottom_right,
	
	
	// 45 degree angle slope
	bt_grass_slope_p16_p16,
	
	// 135 degree angle slope
	bt_grass_slope_n16_p16,
	
	// Approximately 26.57 degrees angle slope, with two blocks
	bt_grass_slope_p32_p16_short,
	bt_grass_slope_p32_p16_tall,
	
	// Approximately 153.43 degrees angle slope, with two blocks
	bt_grass_slope_n32_p16_tall,
	bt_grass_slope_n32_p16_short,
	
	// These two blocks are for decoration
	bt_grass_in_slope_left,
	bt_grass_in_slope_right,
	
	
	// bt_count is the amount of block types.  It is automatically updated
	// by the compiler.
	bt_count,
	
} __attribute__((_align4));


#define list_of_block_stuff_classes(macro) \
\
/* A graphics-less block that sprites are free to move through. */ \
macro(air_block_stuff) \
\
/* A block that looks like a wooden log.  It is indestructible, which
  is quite unlike real life wooden logs. */ \
macro(log_block_stuff) \
\
/* A wooden block without anything inside.  It is destroyed (that is, 
  replaced with an air block) when strongly hit. */ \
macro(wood_block_stuff) \
\
/* A block with eyes without anything inside.  It becomes an empty 
  block upon being strongly hit. */ \
macro(eyes_block_stuff) \
\
/* A block with an exclamation point on it.  The purpose of these 
  blocks is yet to be chosen, but I'm thinking that some kind of
  event will happen when one is strongly hit. */ \
macro(exclam_block_stuff) \
\
/* An empty block that is indestructible.   */ \
macro(dud_block_stuff) \
\
/* Wooden blocks with contents */ \
macro(wood_block_with_bt_dud_stuff) \
macro(wood_block_with_st_waffle_stuff) \
macro(wood_block_with_st_muffin_stuff) \
macro(wood_block_with_st_fire_muffin_stuff) \
macro(wood_block_with_st_ice_muffin_stuff) \
macro(wood_block_with_st_chocolate_muffin_stuff) \
\
/* Eyes blocks with contents */ \
/*bt_eyes_with_bt_dud		// This is the same as bt_eyes. */ \
macro(eyes_block_with_st_waffle_stuff) \
macro(eyes_block_with_st_muffin_stuff) \
macro(eyes_block_with_st_fire_muffin_stuff) \
macro(eyes_block_with_st_ice_muffin_stuff) \
macro(eyes_block_with_st_chocolate_muffin_stuff) \
\
\
/* Grass/Dirt blocks */ \
macro(grass_single_block_stuff) \
\
macro(grass_top_left_block_stuff) \
macro(grass_top_middle_block_stuff) \
macro(grass_top_right_block_stuff) \
\
macro(dirt_middle_left_block_stuff) \
macro(dirt_middle_middle_block_stuff) \
macro(dirt_middle_right_block_stuff) \
\
macro(dirt_bottom_left_block_stuff) \
macro(dirt_bottom_middle_block_stuff) \
macro(dirt_bottom_right_block_stuff) \
\
\
/* 45 degree angle slope */ \
macro(grass_slope_p16_p16_block_stuff) \
\
/* 135 degree angle slope */ \
macro(grass_slope_n16_p16_block_stuff) \
\
/* Approximately 26.57 degrees angle slope, with two blocks */ \
macro(grass_slope_p32_p16_short_block_stuff) \
macro(grass_slope_p32_p16_tall_block_stuff) \
\
/* Approximately 153.43 degrees angle slope, with two blocks */ \
macro(grass_slope_n32_p16_tall_block_stuff) \
macro(grass_slope_n32_p16_short_block_stuff) \
\
/* These two blocks are for decoration */ \
macro(grass_in_slope_left_block_stuff) \
macro(grass_in_slope_right_block_stuff)


#define list_of_slope_configurations(macro) \
/* 45 degree angle slope */ \
macro(p16_p16) \
/* 135 degree angle slope */ \
macro(n16_p16) \
/* Approximately 26.57 degrees angle slope, with two blocks */ \
macro(p32_p16_short) \
macro(p32_p16_tall) \
/* Approximately 153.43 degrees angle slope, with two blocks */ \
macro(n32_p16_tall) \
macro(n32_p16_short)


//// These bg1_block_type's are used by BG1.
//enum bg1_block_type
//{
//	// Day Sky
//	bg1bt_day_sky,
//	
//	// Night Sky block.  Also doubles as a go-to block for fading out or
//	// in.
//	bg1bt_night_sky,
//	
//	
//	// bg1bt_count is the amount of block types.  It is automatically
//	// updated by the compiler.
//	bg1bt_count,
//} __attribute__((_align4));


class block;

#include "block_base_stuff_class.hpp"

extern std::array< block_base_stuff*, bt_count > block_stuff_array
	__attribute__((_iwram));

#include "air_block_stuff_class.hpp"
#include "log_block_stuff_class.hpp"
#include "wood_block_stuff_classes.hpp"
#include "eyes_block_stuff_classes.hpp"
#include "exclam_block_stuff_classes.hpp"
#include "dud_block_stuff_class.hpp"
#include "grass_and_dirt_block_stuff_classes.hpp"
#include "day_sky_and_night_sky_block_classes.hpp"

#define X(name) extern name the_##name __attribute__((_iwram));
list_of_block_stuff_classes(X)
#undef X

// A class for unique block data.
class block
{
public:		// variables
	u16 type;
	u16 persistent_data_index;
	
public:		// functions
	
	inline block_type get_block_type() const
	{
		return (block_type)type;
	}
	
} __attribute__((_align4));



inline bool bt_is_slope( block_type the_block_type )
{
	return ( the_block_type >= bt_grass_slope_p16_p16 
		&& the_block_type <= bt_grass_slope_n32_p16_short );
}

inline bool bt_is_left_slope( block_type the_block_type )
{
	return ( the_block_type == bt_grass_slope_n16_p16 
		|| the_block_type == bt_grass_slope_n32_p16_tall
		|| the_block_type == bt_grass_slope_n32_p16_short );
}
inline bool bt_is_right_slope( block_type the_block_type )
{
	return ( the_block_type == bt_grass_slope_p16_p16 
		|| the_block_type == bt_grass_slope_p32_p16_short 
		|| the_block_type == bt_grass_slope_p32_p16_tall );
}

// Check whether the_block_type is fully solid
inline bool bt_is_neither_air_nor_slope( block_type the_block_type )
{
	return ( the_block_type != bt_air && !bt_is_slope(the_block_type) );
}

inline bool bt_is_neither_air_nor_left_slope( block_type the_block_type )
{
	return ( the_block_type != bt_air 
		&& !bt_is_left_slope(the_block_type) );
}

inline bool bt_is_neither_air_nor_right_slope( block_type the_block_type )
{
	return ( the_block_type != bt_air 
		&& !bt_is_right_slope(the_block_type) );
}


class block_coll_result
{
public:		// variables
	vec2_s32 coord;
	block_type type;
	
public:		// functions
	
	
} __attribute__((_align4));




#endif		// block_stuff_hpp
