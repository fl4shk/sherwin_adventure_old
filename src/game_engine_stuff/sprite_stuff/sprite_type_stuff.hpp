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

class sprite;


//#include "../gfx_manager_class.hpp"
#include "../gfx_manager_class.hpp"



#define first_player_sprite_type_suffix( macro ) \
macro(player)

#define list_of_player_sprite_type_suffixes( macro ) \
/* The Player */ \
first_player_sprite_type_suffix(macro) \



#define first_powerup_sprite_type_suffix( macro ) \
macro(waffle)

#define list_of_powerup_sprite_type_suffixes( macro ) \
/* Powerup Sprites */ \
first_powerup_sprite_type_suffix(macro) \
\
macro(muffin) \
macro(fire_muffin) \
macro(ice_muffin) \
macro(chocolate_muffin)




// Pseudo-background sprites are ONLY checked FOR intersection with
// the_player (and possibly player secondary sprites)
#define first_pseudo_bg_sprite_type_suffix( macro ) \
macro(door)

#define list_of_pseudo_bg_sprite_type_suffixes( macro ) \
/* // Block-like Sprites \
st_warp_block, */ \
/* Warp Sprites */ \
first_pseudo_bg_sprite_type_suffix(macro)




#define first_enemy_sprite_type_suffix( macro ) \
macro(snow_golem)

#define list_of_enemy_sprite_type_suffixes( macro ) \
/* Enemy Sprites */ \
first_enemy_sprite_type_suffix(macro) \




#define first_player_secondary_sprite_type_suffix( macro ) \
macro(player_pickaxe)

#define list_of_player_secondary_sprite_type_suffixes( macro ) \
/* Player Secondary Sprites */ \
first_player_secondary_sprite_type_suffix(macro)



// woo, an X-macro
#define list_of_main_sprite_type_suffixes(macro) \
\
/* The Player */ \
list_of_player_sprite_type_suffixes(macro) \
\
/* Powerup Sprites */ \
list_of_powerup_sprite_type_suffixes(macro) \
\
/* Pseudo Background Sprites */ \
list_of_pseudo_bg_sprite_type_suffixes(macro) \
\
/* Enemy Sprites */ \
list_of_enemy_sprite_type_suffixes(macro) \
\
/* Player Secondary Sprites */ \
list_of_player_secondary_sprite_type_suffixes(macro)


// Adding, removing, or changing sprite types
enum sprite_type
{
	// The Default Sprite (also used FOR when there is no sprite in the
	// slot).
	st_default,
	
	#define generate_enum_entry(suffix) \
	st_##suffix,
	
	list_of_main_sprite_type_suffixes(generate_enum_entry)
	#undef generate_enum_entry
	
	// lim_st is the amount of sprite types.  It is automatically updated
	// by the compiler.
	lim_st,
	
} _ALIGNAS_REGULAR;


#define generate_st_value(suffix) st_##suffix

inline bool sprite_type_is_player( sprite_type the_sprite_type )
{
	return in_range( first_player_sprite_type_suffix(generate_st_value),
		first_powerup_sprite_type_suffix(generate_st_value),
		the_sprite_type );
}

inline bool sprite_type_is_powerup( sprite_type the_sprite_type )
{
	return in_range( first_powerup_sprite_type_suffix(generate_st_value),
		first_pseudo_bg_sprite_type_suffix(generate_st_value),
		the_sprite_type );
}

inline bool sprite_type_is_pseudo_bg( sprite_type the_sprite_type )
{
	return in_range( first_pseudo_bg_sprite_type_suffix(generate_st_value),
		first_enemy_sprite_type_suffix(generate_st_value),
		the_sprite_type );
}

inline bool sprite_type_is_enemy( sprite_type the_sprite_type )
{
	return in_range( first_enemy_sprite_type_suffix(generate_st_value),
		first_player_secondary_sprite_type_suffix(generate_st_value),
		the_sprite_type );
}

inline bool sprite_type_is_player_secondary( sprite_type the_sprite_type )
{
	return in_range
		( first_player_secondary_sprite_type_suffix(generate_st_value),
		lim_st, the_sprite_type );
}
#undef generate_st_value

inline bool sprite_type_exists( sprite_type the_sprite_type )
{
	return ( the_sprite_type >= st_default && the_sprite_type < lim_st );
}

// So, what's this FOR again?
// Good question!
inline bool sprite_type_is_derived( sprite_type the_sprite_type )
{
	return ( the_sprite_type > st_default && the_sprite_type < lim_st );
}


#endif		// sprite_type_stuff_hpp
