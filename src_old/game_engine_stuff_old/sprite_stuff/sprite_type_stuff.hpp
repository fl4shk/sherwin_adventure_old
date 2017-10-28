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


#ifndef sprite_type_stuff_hpp
#define sprite_type_stuff_hpp


#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/oam_entry_defines.hpp"
#include "../../gba_specific_stuff/dma_stuff.hpp"
#include "../../gba_specific_stuff/asm_funcs.hpp"
#include "../../general_utility_stuff/misc_bitwise_funcs.hpp"
//#include "../block_stuff/block_stuff.hpp"
//#include "../level_stuff/active_level_class.hpp"

#include "../../gba_specific_stuff/oam_entry_classes.hpp"

#include "../coll_box_class.hpp"
//#include "../coll_point_group_classes.hpp"

#include "../../general_utility_stuff/debug_vars.hpp"
#include "../../general_utility_stuff/range_funcs.hpp"

class Sprite;


//#include "../gfx_manager_class.hpp"
#include "../gfx_manager_class.hpp"



#define FIRST_PLAYER_SPRITE_TYPE_SUFFIX(macro) \
macro(Player)

#define LIST_OF_PLAYER_SPRITE_TYPE_SUFFIXES(macro) \
/* The Player */ \
FIRST_PLAYER_SPRITE_TYPE_SUFFIX(macro) \



#define FIRST_POWERUP_SPRITE_TYPE_SUFFIX(macro) \
macro(Waffle)

#define LIST_OF_POWERUP_SPRITE_TYPE_SUFFIXES(macro) \
/* Powerup Sprites */ \
FIRST_POWERUP_SPRITE_TYPE_SUFFIX(macro) \
\
macro(Muffin) \
macro(FireMuffin) \
macro(IceMuffin) \
macro(ChocolateMuffin)




// Pseudo-background sprites are ONLY checked for intersection with
// the_player (and possibly Player secondary sprites)
#define FIRST_PSEUDO_BG_SPRITE_TYPE_SUFFIX(macro) \
macro(Door)

#define LIST_OF_PSEUDO_BG_SPRITE_TYPE_SUFFIXES(macro) \
/* // Block-like Sprites \
st_warp_block, */ \
/* Warp Sprites */ \
FIRST_PSEUDO_BG_SPRITE_TYPE_SUFFIX(macro)




#define FIRST_ENEMY_SPRITE_TYPE_SUFFIX(macro) \
macro(SnowGolem)

#define LIST_OF_ENEMY_SPRITE_TYPE_SUFFIXES(macro) \
/* Enemy Sprites */ \
FIRST_ENEMY_SPRITE_TYPE_SUFFIX(macro) \




#define FIRST_PLAYER_SECONDARY_SPRITE_TYPE_SUFFIX(macro) \
macro(PlayerPickaxe)

#define LIST_OF_PLAYER_SECONDARY_SPRITE_TYPE_SUFFIXES(macro) \
/* Player Secondary Sprites */ \
FIRST_PLAYER_SECONDARY_SPRITE_TYPE_SUFFIX(macro)



// woo, an X-macro
#define LIST_OF_MAIN_SPRITE_TYPE_SUFFIXES(macro) \
\
/* The Player */ \
LIST_OF_PLAYER_SPRITE_TYPE_SUFFIXES(macro) \
\
/* Powerup Sprites */ \
LIST_OF_POWERUP_SPRITE_TYPE_SUFFIXES(macro) \
\
/* Pseudo Background Sprites */ \
LIST_OF_PSEUDO_BG_SPRITE_TYPE_SUFFIXES(macro) \
\
/* Enemy Sprites */ \
LIST_OF_ENEMY_SPRITE_TYPE_SUFFIXES(macro) \
\
/* Player Secondary Sprites */ \
LIST_OF_PLAYER_SECONDARY_SPRITE_TYPE_SUFFIXES(macro)


// Adding, removing, or changing Sprite types
enum sprite_type
{
	// The Default Sprite (also used for when there Is no Sprite in the
	// slot).
	StDefault,

	#define GENERATE_ENUM_ENTRY(suffix) \
	St##suffix,

	LIST_OF_MAIN_SPRITE_TYPE_SUFFIXES(GENERATE_ENUM_ENTRY)
	#undef GENERATE_ENUM_ENTRY

	// LimSt Is the amount of Sprite types.  It Is automatically updated
	// by the compiler.
	LimSt,

} _alignas_regular;


#define GENERATE_ST_VALUE(suffix) St##suffix

inline bool sprite_type_is_player(sprite_type the_sprite_type)
{
	return in_range(FIRST_PLAYER_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		FIRST_POWERUP_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		the_sprite_type);
}

inline bool sprite_type_is_powerup(sprite_type the_sprite_type)
{
	return in_range(FIRST_POWERUP_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		FIRST_PSEUDO_BG_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		the_sprite_type);
}

inline bool sprite_type_is_pseudo_bg(sprite_type the_sprite_type)
{
	return in_range(FIRST_PSEUDO_BG_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		FIRST_ENEMY_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		the_sprite_type);
}

inline bool sprite_type_is_enemy(sprite_type the_sprite_type)
{
	return in_range(FIRST_ENEMY_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		FIRST_PLAYER_SECONDARY_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		the_sprite_type);
}

inline bool sprite_type_is_player_secondary(sprite_type the_sprite_type)
{
	return in_range
		(FIRST_PLAYER_SECONDARY_SPRITE_TYPE_SUFFIX(GENERATE_ST_VALUE),
		LimSt, the_sprite_type);
}
#undef GENERATE_ST_VALUE

inline bool sprite_type_exists(sprite_type the_sprite_type)
{
	return (the_sprite_type >= StDefault && the_sprite_type < LimSt);
}

// So, what's this for again?
// Good question!
inline bool sprite_type_is_derived(sprite_type the_sprite_type)
{
	return (the_sprite_type > StDefault && the_sprite_type < LimSt);
}


#endif		// sprite_type_stuff_hpp
