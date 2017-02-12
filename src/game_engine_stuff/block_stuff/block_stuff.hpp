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


#ifndef block_stuff_hpp
#define block_stuff_hpp

#include "../../gba_specific_stuff/attribute_defines.hpp"
#include "../../general_utility_stuff/misc_types.hpp"
#include "../../general_utility_stuff/array_2d_helper_class.hpp"
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
	
	
	// lim_bt is the amount of block types.  It is automatically updated
	// by the compiler.
	lim_bt,
	
} _alignas_regular;

// It's about time I added in something like this!  In MANY cases, there
// are block_type's that have the SAME behavior, so this should also be
// possible to use for jump tables (or switch statements)
enum block_behavior_type
{
	// The actually non-default block_behavior_type (most blocks are
	// completely solid)
	bbvt_air,
	
	// The vast majority of blocks will use this type of behavior.  It is
	// the one used by the block_base_stuff class so that most block types
	// won't need to re-define get_behavior_type().
	bbvt_solid,
	
	// 45 degree angle slope (up and to the right)
	bbvt_slope_p16_p16,
	
	// 135 degree angle slope (up and to the left)
	bbvt_slope_n16_p16,
	
	// Approximately 26.57 degrees angle slope, with two blocks (up and to
	// the right)
	bbvt_slope_p32_p16_short,
	bbvt_slope_p32_p16_tall,
	
	// Approximately 153.43 degrees angle slope, with two blocks (up and to
	// the left)
	bbvt_slope_n32_p16_tall,
	bbvt_slope_n32_p16_short,
	
	
	// lim_bbvt is the amount of block behavior types.  It is
	// automatically updated by the compiler.
	lim_bbvt,
	
	
} _alignas_regular;

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

#define list_of_left_slope_configurations(macro) \
macro(n16_p16) \
macro(n32_p16_tall) \
macro(n32_p16_short)

#define list_of_right_slope_configurations(macro) \
macro(p16_p16) \
macro(p32_p16_short) \
macro(p32_p16_tall)



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
//	// bg1lim_bt is the amount of block types.  It is automatically
//	// updated by the compiler.
//	bg1lim_bt,
//} __attribute__((_align4));


class block;

#include "block_base_stuff_class.hpp"

extern std::array< block_base_stuff*, lim_bt > block_stuff_array
	__attribute__((_ewram));

#include "air_block_stuff_class.hpp"
#include "log_block_stuff_class.hpp"
#include "wood_block_stuff_classes.hpp"
#include "eyes_block_stuff_classes.hpp"
#include "exclam_block_stuff_classes.hpp"
#include "dud_block_stuff_class.hpp"
#include "grass_and_dirt_block_stuff_classes.hpp"
#include "day_sky_and_night_sky_block_classes.hpp"


#define X(name) extern name the_##name __attribute__((_ewram));
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

inline bool block_type_exists( block_type the_block_type )
{
	return ( the_block_type >= bt_air && the_block_type < lim_bt );
}

inline block_behavior_type get_behavior_type_of_block_type
	( block_type the_block_type )
{
	return block_stuff_array[the_block_type]->get_behavior_type();
}

inline bool bbvt_is_slope( block_behavior_type behavior_type )
{
	return ( behavior_type >= bbvt_slope_p16_p16 
		&& behavior_type <= bbvt_slope_n32_p16_short );
}

// bbvt_is_left_slope() is not inline so that a jump table can be generated
// by a switch statement
bool bbvt_is_left_slope( block_behavior_type behavior_type );
	//__attribute__((_iwram_code));


// bbvt_is_right_slope() is not inline so that a jump table can be
// generated by a switch statement
bool bbvt_is_right_slope( block_behavior_type behavior_type );
	//__attribute__((_iwram_code));


// Check whether the_block_type is fully solid
inline bool bbvt_is_fully_solid( block_behavior_type behavior_type )
{
	return behavior_type == bbvt_solid;
}


inline bool bbvt_is_neither_air_nor_left_slope
	( block_behavior_type behavior_type )
{
	return ( behavior_type != bbvt_air
		&& !bbvt_is_left_slope(behavior_type) );
}

inline bool bbvt_is_neither_air_nor_right_slope
	( block_behavior_type behavior_type )
{
	return ( behavior_type != bbvt_air
		&& !bbvt_is_right_slope(behavior_type) );
}


// These two functions find the type of slope that is EXPECTED be to the
// left or right of any_slope_bbvt_in, where any_slope_bbvt_in is ANY type
// of SLOPE
bool get_left_following_slope_bbvt( block_behavior_type any_slope_bbvt_in, 
	block_behavior_type& some_slope_bbvt_out, s32& blk_crd_y_pos_offset );
bool get_right_following_slope_bbvt( block_behavior_type any_slope_bbvt_in, 
	block_behavior_type& some_slope_bbvt_out, s32& blk_crd_y_pos_offset );


#endif		// block_stuff_hpp
