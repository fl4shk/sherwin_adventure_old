// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


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
#include "../coll_point_group_classes.hpp"

#include "../../general_utility_stuff/debug_vars.hpp"

class sprite;


//#include "../gfx_manager_class.hpp"
#include "../gfx_manager_class.hpp"



// woo, an X-macro
#define list_of_main_sprite_type_suffixes(macro) \
\
/* The Player */ \
macro(player) \
\
/* Powerup Sprites */ \
macro(waffle) \
\
macro(muffin) \
macro(fire_muffin) \
macro(ice_muffin) \
macro(chocolate_muffin) \
\
/* // Block-like Sprites \
st_warp_block, */ \
/* Warp Sprites */ \
macro(door) \
\
/* Enemy Sprites */ \
macro(snow_golem) \
\
/* Secondary Sprites */ \
macro(player_pickaxe)


// Adding, removing, or changing sprite types
enum sprite_type
{
	// The Default Sprite (also used for when there is no sprite in the
	// slot).
	st_default,
	
	#define generate_enum_entry(suffix) \
	st_##suffix,
	
	list_of_main_sprite_type_suffixes(generate_enum_entry)
	#undef generate_enum_entry
	
	// st_count is the amount of sprite types.  It is automatically updated
	// by the compiler.
	st_count,
	
} alignas_regular;



inline bool sprite_type_exists( sprite_type the_sprite_type )
{
	return ( the_sprite_type >= st_default && the_sprite_type < st_count );
}

// So, what's this for again?
inline bool sprite_type_is_derived( sprite_type the_sprite_type )
{
	return ( the_sprite_type > st_default && the_sprite_type < st_count );
}


#endif		// sprite_type_stuff_hpp
