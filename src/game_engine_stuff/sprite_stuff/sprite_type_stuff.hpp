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


#ifndef sprite_type_stuff_hpp
#define sprite_type_stuff_hpp


#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/oam_entry_defines.hpp"
#include "../../gba_specific_stuff/dma_stuff.hpp"
#include "../../gba_specific_stuff/asm_funcs.hpp"
#include "../misc_bitwise_funcs.hpp"
//#include "../block_stuff/block_stuff.hpp"
#include "../level_stuff/active_level_class.hpp"

#include "../../gba_specific_stuff/oam_entry_classes.hpp"

#include "../coll_box_class.hpp"
#include "../coll_point_group_class.hpp"

#include "../debug_vars.hpp"

class sprite;


//#include "../gfx_manager_class.hpp"
#include "../gfx_manager_class.hpp"


// Adding, removing, or changing sprite types
enum sprite_type
{
	// The Default Sprite (also used for when there is no sprite in the
	// slot).
	st_default,
	
	// The Player
	st_player,
	
	// Powerup Sprites
	st_waffle,
	
	st_muffin,
	st_fire_muffin,
	st_ice_muffin,
	st_chocolate_muffin,
	
	//// Block-like Sprites
	//st_warp_block,
	// Warp Sprites
	st_door,
	
	// Enemy Sprites
	st_snow_golem,
	
	// st_count is the amount of sprite types.  It is automatically updated
	// by the compiler.
	st_count,
	
} __attribute__((_align4));

#define list_of_main_sprite_types \
\
/* The Player */ \
X(player) \
\
/* Powerup Sprites */ \
X(waffle) \
\
X(muffin) \
X(fire_muffin) \
X(ice_muffin) \
X(chocolate_muffin) \
\
/* // Block-like Sprites \
st_warp_block, */ \
/* Warp Sprites */ \
X(door) \
\
/* Enemy Sprites */ \
X(snow_golem)



// The Default Sprite (also used for when there is no sprite in the slot).
#include "sprite_base_stuff_class.hpp"

// The Player
#include "player_sprite_stuff_class.hpp"

// Powerup Sprites
#include "waffle_sprite_stuff_class.hpp"
#include "muffin_sprite_stuff_classes.hpp"

// Warp Sprites
#include "door_sprite_stuff_class.hpp"

// Enemy Sprites
#include "snow_golem_sprite_stuff_class.hpp"



extern sprite_base_stuff the_sprite_base_stuff;

#define X(name) extern name##_sprite_stuff the_##name##_sprite_stuff;
list_of_main_sprite_types
#undef X


extern sprite_base_stuff* sprite_stuff_array[st_count]
	__attribute__((_iwram));



#endif		// sprite_type_stuff_hpp
