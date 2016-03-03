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


#ifndef active_level_manager_class_hpp
#define active_level_manager_class_hpp


#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/bios_function_wrappers.hpp"
#include "../array_2d_helper_class.hpp"
#include "../block_stuff/block_stuff.hpp"
#include "active_level_class.hpp"
#include "../sprite_stuff/sprite_manager_class.hpp"


//#define bg0_sbb 31
constexpr u32 bg0_sbb = 28;
constexpr u32 bg1_sbb = 29;
constexpr u32 bg2_sbb = 30;
constexpr u32 bg3_sbb = 31;

#include "level_class.hpp"

#include "../game_manager_class.hpp"

class active_level_manager
{
public:		// variables
	
	static u32 converted_block_tile_ids_0[bt_count],
		converted_block_tile_ids_1[bt_count],
		converted_block_tile_ids_2[bt_count],
		converted_block_tile_ids_3[bt_count];
	
	
public:		// functions
	
	static scr_entry horiz_sublevel_tile_at_basic( u32 tile_x, 
		u32 tile_y ) __attribute__((_iwram_code));
	static scr_entry horiz_sublevel_tile_at( u32 tile_x, u32 tile_y )
		__attribute__((_iwram_code));
	
	
	
	static inline u32 sublevel_width_in_tiles 
		( array_2d_helper<u16>& the_block_ids_2d )
	{
		return the_block_ids_2d.width() * 2;
	}
	static inline u32 sublevel_height_in_tiles 
		( array_2d_helper<u16>& the_block_ids_2d )
	{
		return the_block_ids_2d.height() * 2;
	}
	
	static inline u32 sublevel_width_in_tiles 
		( const vec2_u32& sublevel_size_in_blocks_2d )
	{
		return sublevel_size_in_blocks_2d.x * 2;
	}
	static inline u32 sublevel_height_in_tiles 
		( const vec2_u32& sublevel_size_in_blocks_2d )
	{
		return sublevel_size_in_blocks_2d.y * 2;
	}
	
	
	static void correct_bg0_scroll_mirror 
		( const vec2_u32& sublevel_size_in_blocks_2d )
		__attribute__((_iwram_code));
	
	static void update_sublevel_in_screenblock_mirror_2d()
		__attribute__((_iwram_code));
	
	static void copy_sublevel_from_array_2d_helper_to_vram()
		__attribute__((_iwram_code));
	
	
	
	//static void init_horiz_sublevel_sprite_ipg_lists
	//	( const sprite_init_param_group* the_ext_sprite_ipg_arr, 
	//	u32 the_ext_sprite_ipg_arr_size )
	//	__attribute__((_iwram_code));
	
	
	static inline void init_horiz_sublevel_sprite_ipg_lists()
	{
		sprite_manager::init_horiz_sublevel_sprite_ipg_lists
			( active_level::get_the_current_sublevel_ptr()
			.sprite_ipg_arr_arr_helper.get_the_array(),
			active_level::get_the_current_sublevel_ptr()
			.sprite_ipg_arr_arr_helper.get_size() );
	}
	
	static inline void load_level( const level* n_the_current_level_ptr )
	{
		game_manager::curr_game_mode = gm_loading_level;
		active_level::the_current_level_ptr = n_the_current_level_ptr;
		
		player_sprite_stuff::run_toggle = false;
		
		// The following line is temporary!
		player_sprite_stuff::max_hp = 10;
		
		player_sprite_stuff::remaining_hp = player_sprite_stuff::max_hp;
		
		for ( u32 i=0; i<active_level::max_num_sublevels; ++i )
		{
			memfill32( active_level::persistent_block_data_arrays[i],
				0, sizeof(active_level::persistent_block_data_arrays[i])
				/ sizeof(u32) );
		}
		
		load_sublevel_basic(0);
	}
	
	static inline void load_sublevel_basic( u32 n_sublevel_index )
	{
		game_manager::curr_game_mode = gm_changing_sublevel;
		active_level::the_current_active_sublevel_index = n_sublevel_index;
		
		// Initialize the list of sprite level data.
		init_horiz_sublevel_sprite_ipg_lists();
		
		// Decompress the sublevel's block data into block_data_array.
		bios_do_lz77_uncomp_wram
			( active_level::get_the_current_sublevel_ptr()
			.cmp_bd_arr_helper.the_array, 
			active_level::block_data_array );
		
		for ( u32 i=0; i<active_level::block_data_array_size; ++i )
		{
			block& the_block = active_level::block_data_array[i];
			
			block_stuff_array[the_block.type]
				->finish_initializing_using_persistent_data(the_block);
		}
		
		update_sublevel_in_screenblock_mirror_2d();
		
		sprite_manager::initial_sprite_spawning_at_start_of_level
			(gfx_manager::bgofs_mirror[0].curr);
		
		update_sublevel_in_screenblock_mirror_2d();
		
		game_manager::curr_game_mode = gm_in_sublevel;
		
		bios_wait_for_vblank();
	}
	
	static inline void load_sublevel_at_intra_sublevel_warp
		( u32 n_sublevel_index, u32 sublevel_entrance_index )
	{
		game_manager::curr_game_mode = gm_changing_sublevel;
		gfx_manager::fade_out_to_black(15);
		
		active_level::the_current_active_sublevel_index = n_sublevel_index;
		
		clear_oam_mirror();
		//bios_wait_for_vblank();
		copy_oam_mirror_to_oam();
		
		// Initialize the list of sprite level data.
		init_horiz_sublevel_sprite_ipg_lists();
		
		// Decompress the sublevel's block data into block_data_array.
		bios_do_lz77_uncomp_wram
			( active_level::get_the_current_sublevel_ptr()
			.cmp_bd_arr_helper.the_array, 
			active_level::block_data_array );
		
		for ( u32 i=0; i<active_level::block_data_array_size; ++i )
		{
			block& the_block = active_level::block_data_array[i];
			
			block_stuff_array[the_block.type]
				->finish_initializing_using_persistent_data(the_block);
		}
		
		update_sublevel_in_screenblock_mirror_2d();
		
		
		sprite_manager::initial_sprite_spawning_at_intra_sublevel_warp
			( gfx_manager::bgofs_mirror[0].curr, sublevel_entrance_index );
		update_sublevel_in_screenblock_mirror_2d();
		
		game_manager::curr_game_mode = gm_in_sublevel;
		
		bios_wait_for_vblank();
		//game_manager::vblank_func();
		
		// Wait for about 0.25 seconds.
		//wait_for_x_frames(15);
		
		gfx_manager::fade_in(15);
	}
	
} __attribute__((_align4));





#endif		// active_level_manager_class_hpp
