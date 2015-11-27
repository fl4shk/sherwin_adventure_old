#ifndef sprite_gfx_stuff_hpp
#define sprite_gfx_stuff_hpp

#include "../misc_types.hpp"
#include "../../gba_specific_stuff/attribute_defines.hpp"
#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"

#include "../sa_stack_class.hpp"

class sprite;

// There are a total of 16 sprite palettes, each with 15 colors (and one
// transparent "color").
enum sprite_gfx_category
{
	// The player uses sprite palette slot 0
	sgc_player,
	
	// Powerup sprites use sprite palette slot 1
	sgc_powerup,
	
	//// Block-like sprites use sprite palette slots 2 and 3
	//sgc_block_like_0,
	//sgc_block_like_1,
	
	// Door sprites use sprite palette slot 2
	sgc_door,
	
	//// Enemy sprites use sprite palette slots 4, 5, and 6
	// Enemy sprites use sprite palette slots 3, 4, and 5
	sgc_enemy_0,
	sgc_enemy_1,
	sgc_enemy_2,
	
	
	// This is the number of sprite graphics categories, automatically
	// updated by the compiler.  This might count as a simple hack since
	// I'm basically abusing the way enums work.
	sgc_count,
};



#endif		// sprite_gfx_stuff_hpp
