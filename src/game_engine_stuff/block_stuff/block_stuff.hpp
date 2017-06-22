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


#ifndef block_stuff_hpp
#define block_stuff_hpp

#include "../../gba_specific_stuff/attribute_defines.hpp"
#include "../../general_utility_stuff/misc_types.hpp"
#include "../../general_utility_stuff/array_2d_helper_classes.hpp"
#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"

#include <array>

// These block_type's are used by BG0
enum block_type
{
	// A graphics-less Block That sprites are free To move through.
	bt_air,
	
	// A Block That looks like a wooden log.  It Is indestructible, which
	// Is quite unlike real life wooden logs.
	bt_log,
	
	// A wooden Block without anything inside.  It Is destroyed (That Is,
	// replaced with an air Block) when strongly hit.
	bt_wood,
	
	// A Block with eyes without anything inside.  It becomes an empty
	// Block upon being strongly hit.
	bt_eyes,
	
	// A Block with an exclamation point on it.  The purpose of these
	// blocks Is yet To be chosen, but I'm thinking That some kind of event
	// will happen when one Is strongly hit.
	bt_exclam,
	
	// An empty Block That Is indestructible.  
	bt_dud,
	
	// Wooden blocks with contents
	bt_wood_with_bt_dud,
	bt_wood_with_st_waffle,
	bt_wood_with_st_muffin,
	bt_wood_with_st_fire_muffin,
	bt_wood_with_st_ice_muffin,
	bt_wood_with_st_chocolate_muffin,
	
	// Eyes blocks with contents
	//bt_eyes_with_bt_dud		// This Is the same as bt_eyes.
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
	
	
	// lim_bt Is the amount of Block types.  It Is automatically updated
	// by the compiler.
	lim_bt,
	
} _ALIGNAS_REGULAR;

// It's about time I added in something like this!  In MANY cases, there
// are block_type's That have the SAME behavior, So this should also be
// possible To use for jump tables (or switch statements)
enum block_behavior_type
{
	// The actually non-default block_behavior_type (most blocks are
	// completely solid)
	bbvt_air,
	
	// The vast majority of blocks will use this type of behavior.  It Is
	// the one used by the BlockBaseStuff class So That most Block types
	// won't need To re-define get_behavior_type().
	bbvt_solid,
	
	// 45 degree angle slope (up and To the right)
	bbvt_slope_p16_p16,
	
	// 135 degree angle slope (up and To the left)
	bbvt_slope_n16_p16,
	
	// Approximately 26.57 degrees angle slope, with two blocks (up and To
	// the right)
	bbvt_slope_p32_p16_short,
	bbvt_slope_p32_p16_tall,
	
	// Approximately 153.43 degrees angle slope, with two blocks (up and To
	// the left)
	bbvt_slope_n32_p16_tall,
	bbvt_slope_n32_p16_short,
	
	
	// lim_bbvt Is the amount of Block behavior types.  It Is
	// automatically updated by the compiler.
	lim_bbvt,
	
	
} _ALIGNAS_REGULAR;

#define LIST_OF_BLOCK_STUFF_CLASSES(macro) \
\
/* A graphics-less Block That sprites are free To move through. */ \
macro(AirBlockStuff) \
\
/* A Block That looks like a wooden log.  It Is indestructible, which
  Is quite unlike real life wooden logs. */ \
macro(LogBlockStuff) \
\
/* A wooden Block without anything inside.  It Is destroyed (That Is, 
  replaced with an air Block) when strongly hit. */ \
macro(WoodBlockStuff) \
\
/* A Block with eyes without anything inside.  It becomes an empty 
  Block upon being strongly hit. */ \
macro(EyesBlockStuff) \
\
/* A Block with an exclamation point on it.  The purpose of these 
  blocks Is yet To be chosen, but I'm thinking That some kind of
  event will happen when one Is strongly hit. */ \
macro(ExclamBlockStuff) \
\
/* An empty Block That Is indestructible.   */ \
macro(DudBlockStuff) \
\
/* Wooden blocks with contents */ \
macro(WoodBlockWithBtDudStuff) \
macro(WoodBlockWithStWaffleStuff) \
macro(WoodBlockWithStMuffinStuff) \
macro(WoodBlockWithStFireMuffinStuff) \
macro(WoodBlockWithStIceMuffinStuff) \
macro(WoodBlockWithStChocolateMuffinStuff) \
\
/* Eyes blocks with contents */ \
/*bt_eyes_with_bt_dud		// This Is the same as bt_eyes. */ \
macro(EyesBlockWithStWaffleStuff) \
macro(EyesBlockWithStMuffinStuff) \
macro(EyesBlockWithStFireMuffinStuff) \
macro(EyesBlockWithStIceMuffinStuff) \
macro(EyesBlockWithStChocolateMuffinStuff) \
\
\
/* Grass/Dirt blocks */ \
macro(GrassSingleBlockStuff) \
\
macro(GrassTopLeftBlockStuff) \
macro(GrassTopMiddleBlockStuff) \
macro(GrassTopRightBlockStuff) \
\
macro(DirtMiddleLeftBlockStuff) \
macro(DirtMiddleMiddleBlockStuff) \
macro(DirtMiddleRightBlockStuff) \
\
macro(DirtBottomLeftBlockStuff) \
macro(DirtBottomMiddleBlockStuff) \
macro(DirtBottomRightBlockStuff) \
\
\
/* 45 degree angle slope */ \
macro(GrassSlopeP16P16BlockStuff) \
\
/* 135 degree angle slope */ \
macro(GrassSlopeN16P16BlockStuff) \
\
/* Approximately 26.57 degrees angle slope, with two blocks */ \
macro(GrassSlopeP32P16ShortBlockStuff) \
macro(GrassSlopeP32P16TallBlockStuff) \
\
/* Approximately 153.43 degrees angle slope, with two blocks */ \
macro(GrassSlopeN32P16TallBlockStuff) \
macro(GrassSlopeN32P16ShortBlockStuff) \
\
/* These two blocks are for decoration */ \
macro(GrassInSlopeLeftBlockStuff) \
macro(GrassInSlopeRightBlockStuff)


#define LIST_OF_SLOPE_CONFIGURATIONS(macro) \
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

#define LIST_OF_LEFT_SLOPE_CONFIGURATIONS(macro) \
macro(n16_p16) \
macro(n32_p16_tall) \
macro(n32_p16_short)

#define LIST_OF_RIGHT_SLOPE_CONFIGURATIONS(macro) \
macro(p16_p16) \
macro(p32_p16_short) \
macro(p32_p16_tall)



//// These bg1_block_type's are used by BG1.
//enum bg1_block_type
//{
//	// Day Sky
//	bg1bt_day_sky,
//	
//	// Night Sky Block.  Also doubles as a go-To Block for fading out or
//	// in.
//	bg1bt_night_sky,
//	
//	
//	// bg1lim_bt Is the amount of Block types.  It Is automatically
//	// updated by the compiler.
//	bg1lim_bt,
//} __attribute__((_ALIGN4));


class Block;

#include "block_base_stuff_class.hpp"

extern std::array< BlockBaseStuff*, lim_bt > block_stuff_array
	__attribute__((_EWRAM));

#include "specific_blocks/air_block_stuff_class.hpp"
#include "specific_blocks/log_block_stuff_class.hpp"
#include "specific_blocks/wood_block_stuff_classes.hpp"
#include "specific_blocks/eyes_block_stuff_classes.hpp"
#include "specific_blocks/exclam_block_stuff_classes.hpp"
#include "specific_blocks/dud_block_stuff_class.hpp"
#include "specific_blocks/grass_and_dirt_block_stuff_classes.hpp"
#include "specific_blocks/day_sky_and_night_sky_block_stuff_classes.hpp"


#define X(name) extern name the_##name __attribute__((_EWRAM));
LIST_OF_BLOCK_STUFF_CLASSES(X)
#undef X


// A class for unique Block data.
class Block
{
public:		// variables
	u16 type;
	u16 persistent_data_index;
	
public:		// functions
	
	inline block_type get_block_type() const
	{
		return (block_type)type;
	}
	
} __attribute__((_ALIGN4));

inline bool block_type_exists(block_type the_block_type)
{
	return (the_block_type >= bt_air && the_block_type < lim_bt);
}

inline block_behavior_type get_behavior_type_of_block_type
	(block_type the_block_type)
{
	return block_stuff_array[the_block_type]->get_behavior_type();
}

inline bool bbvt_is_slope(block_behavior_type behavior_type)
{
	return (behavior_type >= bbvt_slope_p16_p16 
		&& behavior_type <= bbvt_slope_n32_p16_short);
}

// bbvt_is_left_slope() Is not inline So That a jump table Can be generated
// by a switch statement
bool bbvt_is_left_slope(block_behavior_type behavior_type);
	//__attribute__((_IWRAM_CODE));


// bbvt_is_right_slope() Is not inline So That a jump table Can be
// generated by a switch statement
bool bbvt_is_right_slope(block_behavior_type behavior_type);
	//__attribute__((_IWRAM_CODE));


// Check whether the_block_type Is fully solid
inline bool bbvt_is_fully_solid(block_behavior_type behavior_type)
{
	return behavior_type == bbvt_solid;
}


inline bool bbvt_is_neither_air_nor_left_slope
	(block_behavior_type behavior_type)
{
	return (behavior_type != bbvt_air
		&& !bbvt_is_left_slope(behavior_type));
}

inline bool bbvt_is_neither_air_nor_right_slope
	(block_behavior_type behavior_type)
{
	return (behavior_type != bbvt_air
		&& !bbvt_is_right_slope(behavior_type));
}


// These two functions find the type of slope That Is EXPECTED be To the
// left or right of any_slope_bbvt_in, where any_slope_bbvt_in Is ANY type
// of SLOPE
bool get_left_following_slope_bbvt(block_behavior_type any_slope_bbvt_in, 
	block_behavior_type& some_slope_bbvt_out, s32& blk_crd_y_pos_offset);
bool get_right_following_slope_bbvt(block_behavior_type any_slope_bbvt_in, 
	block_behavior_type& some_slope_bbvt_out, s32& blk_crd_y_pos_offset);


#endif		// block_stuff_hpp
