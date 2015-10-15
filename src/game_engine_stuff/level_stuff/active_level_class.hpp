#ifndef active_level_class_hpp
#define active_level_class_hpp

#include "../block_stuff/block_stuff.hpp"
//#include "../sprite_stuff/sprite_class.hpp"

#include "../sprite_stuff/sprite_type_stuff.hpp"
#include "../sa_stack_class.hpp"
//#include "sprite_level_data_stuff.hpp"

//#include "..array_helper_class.hpp"

//#include "level_class.hpp"
#include "level_defines.hpp"


#include <array>
#include <forward_list>


class sprite;
class sprite_init_param_group;


// This is a class that contains the data used by active levels after they
// have been loaded.  Only one level will ever be fully loaded at a time,
// so this class contains only static member data.  Also, it is important
// to note that the active_level_manager class is what loads and unloads
// levels.
// "Unloading" active levels will probably just consist of clearing the
// static arrays of the active_level class.
class active_level
{
public:		// static variables
	
	//static constexpr u32 block_data_array_size = 0x4000;
	static constexpr u32 block_data_array_size = 16384;
	static block block_data_array[block_data_array_size];
	
	
	static constexpr u32 max_num_sublevels = max_num_sublevels_per_level;
	static constexpr u32 persistent_block_data_array_size = 2048;
	static u16 persistent_block_data_arrays[max_num_sublevels]
		[persistent_block_data_array_size];
	
	
	// Horizontal levels can have a maximum of 16 "screens" of 32 by 32
	// arrays of blocks.  
	// 16384 / 32 = 512, and 512 / 32 = 16.
	static constexpr u32 horiz_level_size = block_data_array_size;
	static constexpr u32 horiz_level_ysize = 32;
	static constexpr u32 horiz_level_xsize = block_data_array_size 
		/ horiz_level_ysize;
	
	static constexpr vec2_u32 horiz_level_size_2d 
		= { horiz_level_xsize, horiz_level_ysize };
	
	static array_2d_helper<block> horiz_level_block_data_2d;
	
	
	// The array of lists of sprite initialization parameters, including
	// the spawned/despawned/dead status.
	static std::array< std::forward_list<sprite_init_param_group>,
		horiz_level_xsize > horiz_level_sprite_ipg_lists;
	
	
	
public:		// functions
	
	// This function computes the block coordinate of a point.
	static inline vec2_s32 get_block_coord_of_point( const vec2_f24p8& pt )
	{
		vec2_s32 ret;
		
		ret.x = pt.x.round_to_int() / 16;
		ret.y = pt.y.round_to_int() / 16;
		
		return ret;
	}
	
	static inline block_type get_block_type_at_coord 
		( const vec2_s32& block_coord )
	{
		return horiz_level_block_data_2d.data_at( block_coord.x,
			block_coord.y ).get_block_type();
	}
	
	static inline block& the_block_data_at_coord 
		( const vec2_s32& block_coord )
	{
		return horiz_level_block_data_2d.data_at( block_coord.x,
			block_coord.y );
	}
	
	
	// This function allocates a new block and returns the previous one
	//static inline u32 get_curr_free_block_slot_and_alloc()
	//{
	//	++curr_free_block_slot;
	//	return( curr_free_block_slot - 1 );
	//}
	
	//static inline void initialize_block_data_array()
	//{
	//	curr_free_block_slot = bt_count;
	//	
	//	for ( u32 i=0; i<bt_count; ++i )
	//	{
	//		block_data_array[(block_type)i].type = (block_type)i;
	//	}
	//}
	
} __attribute__((_align4));








#endif		// active_level_class_hpp
