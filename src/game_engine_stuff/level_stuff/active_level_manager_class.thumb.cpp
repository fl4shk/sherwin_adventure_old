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


#include "active_level_manager_class.hpp"
#include "sprite_level_data_stuff.hpp"


#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../sprite_stuff/sprite_type_includes.hpp"

//#include "../sprite_stuff/player_sprite_class.hpp"


u32 active_level_manager::converted_block_tile_ids_0[bt_count],
	active_level_manager::converted_block_tile_ids_1[bt_count],
	active_level_manager::converted_block_tile_ids_2[bt_count],
	active_level_manager::converted_block_tile_ids_3[bt_count];



void active_level_manager::load_level
	( const level* n_the_current_level_ptr )
{
	game_manager::curr_game_mode = gm_loading_level;
	active_level::the_current_level_ptr = n_the_current_level_ptr;
	
	player_sprite::run_toggle = false;
	
	// The following line is temporary!
	player_sprite::max_hp = 10;
	
	player_sprite::remaining_hp = player_sprite::max_hp;
	
	for ( u32 i=0; i<active_level::max_num_sublevels; ++i )
	{
		memfill32( active_level::persistent_block_data_arrays[i], 0, 
			sizeof(active_level::persistent_block_data_arrays[i])
			/ sizeof(u32) );
	}
	
	load_sublevel_basic(0);
}

void active_level_manager::load_sublevel_basic( u32 n_sublevel_index )
{
	game_manager::curr_game_mode = gm_changing_sublevel;
	active_level::the_current_active_sublevel_index = n_sublevel_index;
	
	// Initialize the list of sprite level data.
	init_horiz_sublevel_sprite_ipg_lists();
	
	// Decompress the sublevel's block data into block_data_array.
	bios_do_lz77_uncomp_wram( active_level::get_curr_sublevel_ptr()
		.cmp_bd_arr_helper.the_array, active_level::block_data_array );
	
	for ( u32 i=0; i<active_level::block_data_array_size; ++i )
	{
		block& the_block = active_level::block_data_array[i];
		
		block_stuff_array[the_block.type]
			->finish_initializing_using_persistent_data(the_block);
	}
	
	update_sublevel_in_screenblock_mirror_2d();
	
	sprite_manager::initial_sprite_spawning_at_start_of_level
		(gfx_manager::bgofs_mirror[0]);
	
	update_sublevel_in_screenblock_mirror_2d();
	
	game_manager::curr_game_mode = gm_in_sublevel;
	
	bios_wait_for_vblank();
}

void active_level_manager::load_sublevel_at_intra_sublevel_warp
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
	bios_do_lz77_uncomp_wram( active_level::get_curr_sublevel_ptr()
		.cmp_bd_arr_helper.the_array, active_level::block_data_array );
	
	for ( u32 i=0; i<active_level::block_data_array_size; ++i )
	{
		block& the_block = active_level::block_data_array[i];
		
		block_stuff_array[the_block.type]
			->finish_initializing_using_persistent_data(the_block);
	}
	
	update_sublevel_in_screenblock_mirror_2d();
	
	
	sprite_manager::initial_sprite_spawning_at_intra_sublevel_warp
		( gfx_manager::bgofs_mirror[0], sublevel_entrance_index );
	update_sublevel_in_screenblock_mirror_2d();
	
	game_manager::curr_game_mode = gm_in_sublevel;
	
	bios_wait_for_vblank();
	//game_manager::vblank_func();
	
	// Wait for about 0.25 seconds.
	//wait_for_x_frames(15);
	
	gfx_manager::fade_in(15);
}
