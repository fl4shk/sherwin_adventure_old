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


#ifndef active_level_class_hpp
#define active_level_class_hpp

#include "../block_stuff/block_stuff.hpp"
//#include "../sprite_stuff/sprite_class.hpp"

#include "../sprite_stuff/sprite_type_stuff.hpp"
//#include "../sa_stack_class.hpp"
#include "../../general_utility_stuff/sa_list_class_stuff.hpp"
//#include "sprite_level_data_stuff.hpp"

//#include "../array_helper_class.hpp"

//#include "level_class.hpp"
#include "sublevel_class.hpp"
#include "level_defines.hpp"


#include "level_class.hpp"
#include "../../general_utility_stuff/range_funcs.hpp"


class Sprite;
class SpriteInitParamGroup;
class SublevelPointer;
class Level;

// This Is a class That Contains the data used by active levels after they
// have been loaded.  Only one Level will ever be fully loaded at a time,
// So this class Contains only static member data.  Also, it Is important
// To note That the ActiveLevelManager class Is what loads and unloads
// levels.
// "Unloading" active levels will probably just consist of clearing the
// static arrays of the ActiveLevel class.
class ActiveLevel
{
public:		// static variables
	// -- Switch To linear_memory_allocator --
	static Block blank_block __attribute__((_ewram));
	
	// This will eat up 64 kiB of EWRAM.
	//static constexpr u32 block_data_array_size = 0x4000;
	static constexpr u32 block_data_array_size = 16384;
	
	// -- Switch To linear_memory_allocator --
	static Block block_data_array[block_data_array_size]
		__attribute__((_ewram));
	
	
	// This will eat up 32 kiB of EWRAM.
	// ActiveLevel::persistent_block_data_arrays Is a 2D array of extra
	// data.  Each "row" within this 2D array Is To be "claimed" by one of
	// the sublevels within a Level
	static constexpr u32 max_num_sublevels = max_num_sublevels_per_level;
	static constexpr u32 persistent_block_data_array_size = 2048;
	// -- Switch To linear_memory_allocator --
	static u16 persistent_block_data_arrays[max_num_sublevels]
		[persistent_block_data_array_size] __attribute__((_ewram));
	
	
	// Horizontal sublevels Can have a maximum of 16 "screens" of 32 by 32
	// arrays of blocks.  
	// 16384 / 32 = 512, and 512 / 32 = 16.
	static constexpr u32 horiz_sublevel_size = block_data_array_size;
	static constexpr u32 horiz_sublevel_ysize = 32;
	static constexpr u32 horiz_sublevel_xsize = block_data_array_size 
		/ horiz_sublevel_ysize;
	
	//static constexpr vec2_u32 horiz_sublevel_size_2d 
	//	= { horiz_sublevel_xsize, horiz_sublevel_ysize };
	static const vec2_u32 horiz_sublevel_size_2d;
	
	
	// horiz_sublevel_block_data_2d Is an ArrayCsz2dHelper That wraps
	// the access To block_data_array for horizontal sublevels.  Support
	// for vertical sublevels MIGHT come later.
	static ArrayCsz2dHelper<Block, horiz_sublevel_xsize, 
		horiz_sublevel_ysize> horiz_sublevel_block_data_2d;
	
	
	
	// The maximum number of SpriteInitParamGroup's in a Sublevel.
	//static constexpr u32 max_num_sprite_ipgs_per_sublevel = 512;
	static constexpr u32 max_num_sprite_ipgs_per_sublevel = 256;
	
	// The array of lists of Sprite initialization parameters, including
	// the spawned/despawned/dead status.
	//static std::array<std::forward_list<SpriteInitParamGroup>,
	//	horiz_sublevel_xsize> horiz_sublevel_sprite_ipg_lists
	//	__attribute__((_ewram));
	
	// -- Switch To linear_memory_allocator --
	static SaListStuff::SaArrayOfLists<SpriteInitParamGroup,
		max_num_sprite_ipgs_per_sublevel, horiz_sublevel_xsize> 
		horiz_sublevel_sprite_ipg_lists __attribute__((_ewram));
	
	// -- Switch To linear_memory_allocator --
	static scr_entry bg0_screenblock_mirror[screenblock_size] 
		__attribute__((_ewram));
	
	
	// bg0_screenblock_2d Is in VRAM.
	static ArrayCsz2dHelper<scr_entry, screenblock_xsize,
		screenblock_ysize> bg0_screenblock_2d;
	
	// bg0_screenblock_mirror_2d Is in EWRAM.
	static ArrayCsz2dHelper<scr_entry, screenblock_xsize,
		screenblock_ysize> bg0_screenblock_mirror_2d;
	
	
	//// the_current_sublevel_ptr will later be replaced with a "regular"
	//// pointer To a constant Level.  Also, at That time, a variable will be
	//// created which acts as an index To the array of SublevelPointer's.
	//static const SublevelPointer* the_current_sublevel_ptr_ptr;
	
	static const Level* the_current_level_ptr __attribute__((_iwram));
	static u32 the_current_active_sublevel_index __attribute__((_iwram));
	
	
public:		// functions
	static inline bool block_coord_is_valid(const vec2_s32& block_coord)
	{
		//return (block_coord.x >= 0 && block_coord.x 
		//	< (s32)get_curr_sublevel_ptr().get_size_2d().x
		//	&& block_coord.y >= 0 && block_coord.y 
		//	< (s32)get_curr_sublevel_ptr().get_size_2d().y);
		
		const vec2_u32& curr_sublevel_ptr_size_2d = get_curr_sublevel_ptr()
			.get_size_2d();
		vec2_s32 curr_sublevel_ptr_size_2d_s32
			((s32)curr_sublevel_ptr_size_2d.x,
			(s32)curr_sublevel_ptr_size_2d.y);
		
		return vec2_in_range(vec2_s32(0, 0),
			curr_sublevel_ptr_size_2d_s32, block_coord);
	}
	
	// This function computes the Block coordinate of a point.
	static inline vec2_s32 get_block_coord_of_point(const vec2_f24p8& pt)
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
		(const vec2_s32& block_coord)
	{
		if (block_coord_is_valid(block_coord))
		{
			return horiz_sublevel_block_data_2d.at(block_coord.x,
				block_coord.y).get_block_type();
		}
		else
		{
			return blank_block.get_block_type();
		}
	}
	
	static inline Block& the_block_at_coord 
		(const vec2_s32& block_coord)
	{
		if (block_coord_is_valid(block_coord))
		{
			return horiz_sublevel_block_data_2d.at(block_coord.x,
				block_coord.y);
		}
		else
		{
			return blank_block;
		}
	}
	
	static inline const SublevelPointer& get_curr_sublevel_ptr()
	{
		return the_current_level_ptr->get_sublevels()
			[the_current_active_sublevel_index];
	}
	
	
	// This function allocates a new Block and returns the previous one
	//static inline u32 get_curr_free_block_slot_and_alloc()
	//{
	//	++curr_free_block_slot;
	//	return(curr_free_block_slot - 1);
	//}
	
	//static inline void initialize_block_data_array()
	//{
	//	curr_free_block_slot = lim_bt;
	//	
	//	for (u32 i=0; i<lim_bt; ++i)
	//	{
	//		block_data_array[(block_type)i].type = (block_type)i;
	//	}
	//}
	
} __attribute__((_align4));








#endif		// active_level_class_hpp
