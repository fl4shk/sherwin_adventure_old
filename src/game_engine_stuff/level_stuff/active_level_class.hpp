// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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


#ifndef active_level_class_hpp
#define active_level_class_hpp

#include "../block_stuff/block_stuff.hpp"
//#include "../sprite_stuff/sprite_class.hpp"

#include "../sprite_stuff/sprite_type_stuff.hpp"
//#include "../sa_stack_class.hpp"
#include "../sa_list_class_stuff.hpp"
//#include "sprite_level_data_stuff.hpp"

//#include "../array_helper_class.hpp"

//#include "level_class.hpp"
#include "level_defines.hpp"



class sprite;
class sprite_init_param_group;
class sublevel_pointer;
class level;


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
	
	// This will eat up 64 kiB of EWRAM.
	//static constexpr u32 block_data_array_size = 0x4000;
	static constexpr u32 block_data_array_size = 16384;
	static block block_data_array[block_data_array_size]
		__attribute__((_ewram));
	
	
	// This will eat up 32 kiB of EWRAM.
	// active_level::persistent_block_data_arrays is a 2D array of extra
	// data.  Each "row" within this 2D array is to be "claimed" by one of
	// the sublevels within a level
	static constexpr u32 max_num_sublevels = max_num_sublevels_per_level;
	static constexpr u32 persistent_block_data_array_size = 2048;
	static u16 persistent_block_data_arrays[max_num_sublevels]
		[persistent_block_data_array_size] __attribute__((_ewram));
	
	
	// Horizontal sublevels can have a maximum of 16 "screens" of 32 by 32
	// arrays of blocks.  
	// 16384 / 32 = 512, and 512 / 32 = 16.
	static constexpr u32 horiz_sublevel_size = block_data_array_size;
	static constexpr u32 horiz_sublevel_ysize = 32;
	static constexpr u32 horiz_sublevel_xsize = block_data_array_size 
		/ horiz_sublevel_ysize;
	
	//static constexpr vec2_u32 horiz_sublevel_size_2d 
	//	= { horiz_sublevel_xsize, horiz_sublevel_ysize };
	static const vec2_u32 horiz_sublevel_size_2d;
	
	
	// horiz_sublevel_block_data_2d is an array_2d_helper that wraps the
	// access to block_data_array for horizontal sublevels.  Support for
	// vertical sublevels MIGHT come later.
	static array_2d_helper<block> horiz_sublevel_block_data_2d;
	
	
	
	// The maximum number of sprite_init_param_group's in a sublevel.
	//static constexpr u32 max_num_sprite_ipgs_per_sublevel = 512;
	static constexpr u32 max_num_sprite_ipgs_per_sublevel = 256;
	
	// The array of lists of sprite initialization parameters, including
	// the spawned/despawned/dead status.
	//static std::array< std::forward_list<sprite_init_param_group>,
	//	horiz_sublevel_xsize > horiz_sublevel_sprite_ipg_lists
	//	__attribute__((_ewram));
	
	static sa_array_of_lists< sprite_init_param_group,
		max_num_sprite_ipgs_per_sublevel, horiz_sublevel_xsize > 
		horiz_sublevel_sprite_ipg_lists __attribute__((_ewram));
	
	// 
	static scr_entry bg0_screenblock_mirror[screenblock_size] 
		__attribute__((_ewram));
	
	
	// bg0_screenblock_2d is in VRAM.
	static array_2d_helper<scr_entry> bg0_screenblock_2d;
	
	// bg0_screenblock_mirror_2d is in EWRAM.
	static array_2d_helper<scr_entry> bg0_screenblock_mirror_2d;
	
	
	//// the_current_sublevel_ptr will later be replaced with a "regular"
	//// pointer to a constant level.  Also, at that time, a variable will be
	//// created which acts as an index to the array of sublevel_pointer's.
	//static const sublevel_pointer* the_current_sublevel_ptr_ptr;
	
	static const level* the_current_level_ptr __attribute__((_iwram));
	static u32 the_current_active_sublevel_index __attribute__((_iwram));
	
	
public:		// functions
	
	// This function computes the block coordinate of a point.
	static inline vec2_s32 get_block_coord_of_point( const vec2_f24p8& pt )
	{
		vec2_s32 ret;
		
		//ret.x = pt.x.round_to_int() / 16;
		//ret.y = pt.y.round_to_int() / 16;
		
		ret.x = pt.x.floor_to_int() / num_pixels_per_block_col;
		ret.y = pt.y.floor_to_int() / num_pixels_per_block_row;
		//ret.x = pt.x.round_to_int() / num_pixels_per_block_col;
		//ret.y = pt.y.round_to_int() / num_pixels_per_block_row;
		
		return ret;
	}
	
	static inline block_type get_block_type_at_coord 
		( const vec2_s32& block_coord )
	{
		return horiz_sublevel_block_data_2d.data_at( block_coord.x,
			block_coord.y ).get_block_type();
	}
	
	static inline block& the_block_data_at_coord 
		( const vec2_s32& block_coord )
	{
		return horiz_sublevel_block_data_2d.data_at( block_coord.x,
			block_coord.y );
	}
	
	static const sublevel_pointer& get_the_current_sublevel_ptr();
	
	
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
