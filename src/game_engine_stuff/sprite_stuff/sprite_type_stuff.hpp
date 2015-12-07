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
	
	// Enemy sprites
	st_snow_golem,
	
	// st_count is the amount of sprite types.  It is automatically updated
	// by the compiler.
	st_count,
	
} __attribute__((_align4));



#include "sprite_base_stuff_class.hpp"
#include "player_sprite_stuff_class.hpp"
#include "waffle_sprite_stuff_class.hpp"
#include "muffin_sprite_stuff_classes.hpp"
#include "door_sprite_stuff_class.hpp"
#include "snow_golem_sprite_stuff_class.hpp"



extern sprite_base_stuff the_sprite_base_stuff;
extern player_sprite_stuff the_player_sprite_stuff;
extern waffle_sprite_stuff the_waffle_sprite_stuff;
extern muffin_sprite_stuff the_muffin_sprite_stuff;
extern fire_muffin_sprite_stuff the_fire_muffin_sprite_stuff;
extern ice_muffin_sprite_stuff the_ice_muffin_sprite_stuff;
extern chocolate_muffin_sprite_stuff the_chocolate_muffin_sprite_stuff;
extern door_sprite_stuff the_door_sprite_stuff;
extern snow_golem_sprite_stuff the_snow_golem_sprite_stuff;

extern sprite_base_stuff* sprite_stuff_array[st_count];



#endif		// sprite_type_stuff_hpp
