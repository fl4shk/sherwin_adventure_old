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


#ifndef active_level_manager_class_hpp
#define active_level_manager_class_hpp


#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/bios_function_wrappers.hpp"
#include "../../general_utility_stuff/array_2d_helper_classes.hpp"
#include "../block_stuff/block_stuff.hpp"
#include "active_level_class.hpp"
#include "../sprite_stuff/sprite_manager_class.hpp"


//#define BG0_SBB 31
static constexpr u32 BG0_SBB = 28;
static constexpr u32 bg1_sbb = 29;
static constexpr u32 bg2_sbb = 30;
static constexpr u32 bg3_sbb = 31;

#include "level_class.hpp"

#include "../game_manager_class.hpp"

class ActiveLevelManager
{
public:		// variables
	
	// -- Switch To linear_memory_allocator --
	static u32 converted_block_tile_ids_0[lim_bt],
		converted_block_tile_ids_1[lim_bt],
		converted_block_tile_ids_2[lim_bt],
		converted_block_tile_ids_3[lim_bt];
	
	
public:		// functions
	
	static scr_entry horiz_sublevel_tile_at_basic(u32 tile_x, 
		u32 tile_y) __attribute__((_iwram_code,_target_arm));
	static scr_entry horiz_sublevel_tile_at(u32 tile_x, u32 tile_y)
		__attribute__((_iwram_code,_target_arm));
	
	
	
	//static inline u32 sublevel_width_in_tiles 
	//	(Array2dHelper<u16>& the_block_ids_2d)
	//{
	//	return the_block_ids_2d.width() * 2;
	//}
	//static inline u32 sublevel_height_in_tiles 
	//	(Array2dHelper<u16>& the_block_ids_2d)
	//{
	//	return the_block_ids_2d.height() * 2;
	//}
	
	static inline u32 sublevel_width_in_tiles 
		(const vec2_u32& sublevel_size_in_blocks_2d)
	{
		return sublevel_size_in_blocks_2d.x * 2;
	}
	static inline u32 sublevel_height_in_tiles 
		(const vec2_u32& sublevel_size_in_blocks_2d)
	{
		return sublevel_size_in_blocks_2d.y * 2;
	}
	
	
	static void correct_bg0_scroll_mirror 
		(const vec2_u32& sublevel_size_in_blocks_2d)
		__attribute__((_iwram_code,_target_arm));
	
	static void update_sublevel_in_screenblock_mirror_2d()
		__attribute__((_iwram_code,_target_arm));
	
	static void copy_sublevel_from_array_csz_2d_helper_to_vram();
		//__attribute__((_iwram_code,_target_arm));
	
	
	
	//static void init_horiz_sublevel_sprite_ipg_lists
	//	(const SpriteInitParamGroup* the_ext_sprite_ipg_arr, 
	//	u32 the_ext_sprite_ipg_arr_size)
	//	__attribute__((_iwram_code,_target_arm));
	
	
	static inline void init_horiz_sublevel_sprite_ipg_lists()
	{
		SpriteManager::init_horiz_sublevel_sprite_ipg_lists
			(ActiveLevel::get_curr_sublevel_ptr()
			.sprite_ipg_arr_arr_helper.get_array(),
			ActiveLevel::get_curr_sublevel_ptr()
			.sprite_ipg_arr_arr_helper.get_size());
	}
	
	static void load_level(const Level* n_the_current_level_ptr);
	
	static void load_sublevel_basic(u32 n_sublevel_index);
	
	static void load_sublevel_at_intra_sublevel_warp
		(u32 n_sublevel_index, u32 sublevel_entrance_index);
	
} __attribute__((_align4));





#endif		// active_level_manager_class_hpp
