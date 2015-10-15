//#include "block_stuff.hpp"
#include "../level_stuff/active_level_class.hpp"

#include "../../gba_specific_stuff/bg_reg_stuff.hpp"
#include "../../gba_specific_stuff/dma_stuff.hpp"


block_base_stuff* block_stuff_array[bt_count] __attribute__((_iwram))
= {
	// A graphics-less block that sprites are free to move through.
	new air_block_stuff,
	
	// A block that looks like a wooden log.  It is indestructible, which
	// is quite unlike real life wooden logs.
	new log_block_stuff,
	
	// A wooden block without anything inside.  It is destroyed (that is,
	// replaced with an air block) when strongly hit.
	new wood_block_stuff,
	
	// A question mark block without anything inside.  It becomes an empty
	// block upon being strongly hit.
	new qmark_block_stuff,
	
	// A block with an exclamation point on it.  The purpose of these
	// blocks is yet to be chosen, but I'm thinking that some kind of event
	// will happen when one is strongly hit.
	new exclam_block_stuff,
	
	// An empty block that is indestructible.  
	new dud_block_stuff,
	
	// Wooden blocks with contents
	new wood_block_with_bt_dud_stuff,
	new wood_block_with_st_waffle_stuff,
	new wood_block_with_st_muffin_stuff,
	new wood_block_with_st_fire_muffin_stuff,
	new wood_block_with_st_ice_muffin_stuff,
	new wood_block_with_st_chocolate_muffin_stuff,
	
	// Question mark blocks with contents
	new qmark_block_with_st_waffle_stuff,
	new qmark_block_with_st_muffin_stuff,
	new qmark_block_with_st_fire_muffin_stuff,
	new qmark_block_with_st_ice_muffin_stuff,
	new qmark_block_with_st_chocolate_muffin_stuff,
	
	// Grass/Dirt blocks
	new grass_single_block_stuff,
	
	new grass_top_left_block_stuff,
	new grass_top_middle_block_stuff,
	new grass_top_right_block_stuff,
	
	new dirt_middle_left_block_stuff,
	new dirt_middle_middle_block_stuff,
	new dirt_middle_right_block_stuff,
	
	new dirt_bottom_left_block_stuff,
	new dirt_bottom_middle_block_stuff,
	new dirt_bottom_right_block_stuff,
	
	new grass_slope_135_degrees_block_stuff,
	new grass_slope_45_degrees_block_stuff,
	
	new grass_in_slope_left_block_stuff,
	new grass_in_slope_right_block_stuff,
	
	
};





void update_block_graphics_in_vram( const unsigned short* the_tiles )
{
	// Note:  this function currently does multiple VRAM graphics updates
	// whenever more than one block_type use the same graphics_slot.
	for ( u32 i=0; i<block_type::bt_count; ++i )
	{
		u32 graphics_slot = get_graphics_slot_of_block_type 
			( (block_type)i );
		u32 metatile_number = get_metatile_number_of_block_type
			( (block_type)i );
		
		dma3_cpy( &( bg_tile_vram[graphics_slot * 16]), 
			&( the_tiles 
				[metatile_number * 16 * 4] ),
			16 * 4, 0 );
		
	}
}



