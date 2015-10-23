#ifndef block_stuff_hpp
#define block_stuff_hpp

#include "../../gba_specific_stuff/attribute_defines.hpp"
#include "../misc_types.hpp"
#include "../array_2d_helper_class.hpp"
#include "../../gba_specific_stuff/bg_reg_stuff.hpp"

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
	
	bt_grass_slope_45_degrees,
	bt_grass_slope_135_degrees,
	
	// These two blocks are for decoration
	bt_grass_in_slope_left,
	bt_grass_in_slope_right,
	
	
	// bt_count is the amount of block types.  It is automatically updated
	// by the compiler.
	bt_count,
	
} __attribute__((_align4));


class block;


#include "block_base_stuff_class.hpp"

extern block_base_stuff* block_stuff_array[bt_count];

#include "air_block_stuff_class.hpp"
#include "log_block_stuff_class.hpp"
#include "wood_block_stuff_classes.hpp"
#include "eyes_block_stuff_classes.hpp"
#include "exclam_block_stuff_classes.hpp"
#include "dud_block_stuff_class.hpp"
#include "grass_and_dirt_block_stuff_classes.hpp"


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



inline u32 get_metatile_number_of_block_type( block_type the_block_type ) 
	__attribute__((always_inline));


inline u32 get_metatile_number_of_block_type( block_type the_block_type )
{
	//if ( the_block_type < 0 || the_block_type >= block_type::bt_count )
	//{
	//	return block_stuff_array[bt_air]->get_metatile_number();
	//}
	//else
	//{
	//	return block_stuff_array[the_block_type]->get_metatile_number();
	//}
	
	return block_stuff_array[the_block_type]->get_metatile_number();
}



inline const u32 get_graphics_slot_of_block_type 
	( block_type the_block_type ) __attribute__((always_inline));


inline const u32 get_graphics_slot_of_block_type 
	( block_type the_block_type )
{
	// This assumes that EVERY block uses 4 graphics slots in VRAM
	//return ( the_block_type * 4 );
	return block_stuff_array[the_block_type]->get_metatile_graphics_slot()
		* 4;
}

inline u32 get_palette_number_of_block_type( block_type the_block_type ) 
	__attribute__((always_inline));


inline u32 get_palette_number_of_block_type( block_type the_block_type )
{
	//if ( the_block_type < 0 || the_block_type >= block_type::bt_count )
	//{
	//	return block_stuff_array[bt_air]->get_palette_number();
	//}
	//else
	//{
	//	return block_stuff_array[the_block_type]->get_palette_number();
	//}
	
	return block_stuff_array[the_block_type]->get_palette_number();
}



void update_block_graphics_in_vram( const unsigned short* the_tiles )
	__attribute__((_iwram_code));





class block_coll_result
{
public:		// variables
	vec2_s32 coord;
	block_type type;
	
public:		// functions
	
	
} __attribute__((_align4));




#endif		// block_stuff_hpp
