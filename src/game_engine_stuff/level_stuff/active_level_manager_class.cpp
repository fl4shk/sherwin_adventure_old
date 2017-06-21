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
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#include "active_level_manager_class.hpp"
#include "sprite_level_data_stuff.hpp"


#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../sprite_stuff/sprite_type_includes.hpp"

//#include "../sprite_stuff/player_sprite_class.hpp"


u32 active_level_manager::converted_block_tile_ids_0[lim_bt],
	active_level_manager::converted_block_tile_ids_1[lim_bt],
	active_level_manager::converted_block_tile_ids_2[lim_bt],
	active_level_manager::converted_block_tile_ids_3[lim_bt];

scr_entry active_level_manager::horiz_sublevel_tile_at_basic( u32 tile_x, 
	u32 tile_y )
{
	//return the_block_ids_2d
	
	u32 block_x = tile_x >> 0x1, block_y = tile_y >> 0x1;
	
	u32 inner_block_x = tile_x & 0x1, inner_block_y = tile_y & 0x1;
	
	
	
	//offset_2d.y * size_2d.x + offset_2d.x
	block_type the_block_type;
	
	if ( block_y * active_level::horiz_sublevel_block_data_2d.width() 
		+ block_x > active_level::horiz_sublevel_block_data_2d.get_size() )
	{
		the_block_type = bt_air;
	}
	else
	{
		the_block_type = active_level::horiz_sublevel_block_data_2d.at
			( block_x, block_y ).get_block_type();
	}
	
	
	u32 the_metatile_id = gfx_manager::get_metatile_number_of_block_type
		(the_block_type);
	u32 the_palette_id = gfx_manager::get_palette_number_of_block_type
		(the_block_type);
	
	u32 num_tiles_per_metatile = gfx_manager::num_tiles_in_ss_16x16;
	
	
	// First inner row
	if ( inner_block_y == 0 )
	{
		if ( inner_block_x == 0 )
		{
			return (u16)( ( se_id( the_metatile_id 
				* num_tiles_per_metatile ) + 0 )
				| se_palbank(the_palette_id) );
		}
		else //if ( inner_block_x == 1 )
		{
			return (u16)( se_id ( ( the_metatile_id 
				* num_tiles_per_metatile ) + 1 ) 
				| se_palbank(the_palette_id) );
		}
	}
	// Second inner row
	else //if ( inner_block_y == 1 )
	{
		if ( inner_block_x == 0 )
		{
			return (u16)( se_id( ( the_metatile_id 
				* num_tiles_per_metatile ) + 2 ) 
				| se_palbank(the_palette_id) );
		}
		else //if ( inner_block_x == 1 )
		{
			return (u16)( se_id( ( the_metatile_id 
				* num_tiles_per_metatile ) + 3 )
				| se_palbank(the_palette_id) );
		}
	}
	
}


scr_entry active_level_manager::horiz_sublevel_tile_at( u32 tile_x, 
	u32 tile_y )
{
	u32 block_x = tile_x >> 0x1, block_y = tile_y >> 0x1;
	
	u32 inner_block_x = tile_x & 0x1, inner_block_y = tile_y & 0x1;
	
	
	
	//offset_2d.y * size_2d.x + offset_2d.x
	s32 block_data_array_offset = block_y 
		* active_level::horiz_sublevel_xsize + block_x;
	
	block_type the_block_type;
	
	if ( block_data_array_offset < 0
		|| block_data_array_offset 
		> (s32)active_level::horiz_sublevel_size )
	{
		the_block_type = bt_air;
	}
	else
	{
		//the_block_type = active_level::horiz_sublevel_block_data_2d.at( block_x,
		//	block_y ).get_block_type();
		the_block_type = active_level::block_data_array
			[block_data_array_offset].get_block_type();
	}
	
	if ( inner_block_y == 0 )
	{
		if ( inner_block_x == 0 )
		{
			return converted_block_tile_ids_0[the_block_type];
		}
		else //if ( inner_block_x == 1 )
		{
			return converted_block_tile_ids_1[the_block_type];
		}
	}
	else //if ( inner_block_y == 1 )
	{
		if ( inner_block_x == 0 )
		{
			return converted_block_tile_ids_2[the_block_type];
		}
		else //if ( inner_block_x == 1 )
		{
			return converted_block_tile_ids_3[the_block_type];
		}
	}
	
	
	
}


void active_level_manager::correct_bg0_scroll_mirror 
	( const vec2_u32& sublevel_size_in_blocks_2d )
{
	//return;
	
	//s32 sublevel_x_coord_tile = gfx_manager::bgofs_mirror[0].curr.x >> 3;
	//s32 sublevel_y_coord_tile = gfx_manager::bgofs_mirror[0].curr.y >> 3;
	
	//s32 sublevel_x_coord_tile = gfx_manager::bgofs_mirror[0].curr.x
	//	.to_int_for_on_screen() >> 3;
	//s32 sublevel_y_coord_tile = gfx_manager::bgofs_mirror[0].curr.y
	//	.to_int_for_on_screen() >> 3;
	s32 sublevel_x_coord_tile = gfx_manager::bgofs_mirror[0].curr.x
		.floor_to_int() >> 3;
	s32 sublevel_y_coord_tile = gfx_manager::bgofs_mirror[0].curr.y
		.floor_to_int() >> 3;
	
	//bool change_frac_bits = false;
	bool change_frac_bits = true;
	
	if ( sublevel_x_coord_tile < 0 )
	{
		//gfx_manager::bgofs_mirror[0].curr.x = 0;
		
		if ( change_frac_bits )
		{
			gfx_manager::bgofs_mirror[0].curr.x = {0};
		}
		else //if ( !change_frac_bits )
		{
			gfx_manager::bgofs_mirror[0].curr.x.data 
				= gfx_manager::bgofs_mirror[0].curr.x.get_frac_bits();
		}
	}
	
	else if ( sublevel_x_coord_tile 
		> (s32)(sublevel_width_in_tiles(sublevel_size_in_blocks_2d) 
		- screen_width_in_tiles - 1 ) )
	{
		//gfx_manager::bgofs_mirror[0].curr.x = ( sublevel_width_in_tiles
		//	(sublevel_size_in_blocks_2d)
		//	* num_pixels_per_tile_row_or_column )
		//	- SCREEN_WIDTH;
		
		if ( change_frac_bits )
		{
			gfx_manager::bgofs_mirror[0].curr.x = make_f24p8
				( ( sublevel_width_in_tiles(sublevel_size_in_blocks_2d)
				* num_pixels_per_tile_row_or_column ) - SCREEN_WIDTH );
		}
		else //if ( !change_frac_bits )
		{
			gfx_manager::bgofs_mirror[0].curr.x = make_f24p8
				( ( sublevel_width_in_tiles(sublevel_size_in_blocks_2d)
				* num_pixels_per_tile_row_or_column ) - SCREEN_WIDTH,
				gfx_manager::bgofs_mirror[0].curr.x.get_frac_bits() );
		}
	}
	
	
	
	if ( sublevel_y_coord_tile < 0 )
	{
		//gfx_manager::bgofs_mirror[0].curr.y = 0;
		
		if ( change_frac_bits )
		{
			gfx_manager::bgofs_mirror[0].curr.y = {0};
		}
		else //if ( !change_frac_bits )
		{
			gfx_manager::bgofs_mirror[0].curr.y.data 
				= gfx_manager::bgofs_mirror[0].curr.y.get_frac_bits();
		}
	}
	
	else if ( sublevel_y_coord_tile 
		> (s32)(sublevel_height_in_tiles(sublevel_size_in_blocks_2d)
		- screen_height_in_tiles -1 ) )
	{
		//gfx_manager::bgofs_mirror[0].curr.y = ( sublevel_height_in_tiles
		//	(sublevel_size_in_blocks_2d)
		//	* num_pixels_per_tile_row_or_column )
		//	- SCREEN_HEIGHT;
		
		if ( change_frac_bits )
		{
			gfx_manager::bgofs_mirror[0].curr.y = make_f24p8
				( ( sublevel_height_in_tiles(sublevel_size_in_blocks_2d)
				* num_pixels_per_tile_row_or_column ) - SCREEN_HEIGHT );
		}
		else //if ( !change_frac_bits )
		{
			gfx_manager::bgofs_mirror[0].curr.y = make_f24p8
				( ( sublevel_height_in_tiles(sublevel_size_in_blocks_2d)
				* num_pixels_per_tile_row_or_column ) - SCREEN_HEIGHT, 
				gfx_manager::bgofs_mirror[0].curr.y.get_frac_bits() );
		}
	}
}

void active_level_manager::update_sublevel_in_screenblock_mirror_2d()
	//( array_2d_helper<scr_entry>& screenblock_mirror_2d,
	//const vec2_u32& sublevel_size_in_blocks_2d )
{
	
	correct_bg0_scroll_mirror(active_level::get_curr_sublevel_ptr()
		.get_size_2d());
	
	
	// VRAM tiles are 8x8 pixels in size, so divide the 
	//s32 sublevel_x_coord_tile = gfx_manager::bgofs_mirror[0].curr.x >> 3;
	//s32 sublevel_y_coord_tile = gfx_manager::bgofs_mirror[0].curr.y >> 3;
	s32 sublevel_x_coord_tile = gfx_manager::bgofs_mirror[0].curr.x
		.floor_to_int() >> 3;
	s32 sublevel_y_coord_tile = gfx_manager::bgofs_mirror[0].curr.y
		.floor_to_int() >> 3;
	
	
	// Create a list of 8x8 tile IDs for each block_type
	for ( u32 i=0; i<lim_bt; ++i )
	{
		block_type the_block_type = (block_type)i;
		
		u32 the_metatile_id 
			= gfx_manager::get_metatile_number_of_block_type
			(the_block_type);
		u32 the_palette_id = gfx_manager::get_palette_number_of_block_type
			(the_block_type);
		
		// Top-left 8x8 tile ID
		converted_block_tile_ids_0[i] = ( ( the_metatile_id * 4 ) + 0 )
			| se_palbank(the_palette_id);
		
		// Top-right 8x8 tile ID
		converted_block_tile_ids_1[i] = ( ( the_metatile_id * 4 ) + 1 )
			| se_palbank(the_palette_id);
		
		// Bottom-left 8x8 tile ID
		converted_block_tile_ids_2[i] = ( ( the_metatile_id * 4 ) + 2 )
			| se_palbank(the_palette_id);
		
		// Bottom-right 8x8 tile ID
		converted_block_tile_ids_3[i] = ( ( the_metatile_id * 4 ) + 3 )
			| se_palbank(the_palette_id);
	}
	
	//
	for ( u32 i=0; i<screen_width_in_tiles + 1; ++i )
	{
		for ( u32 j=0; j<screen_height_in_tiles + 1; ++j )
		{
			// Why exactly am I using un-named constants here?
			active_level::bg0_screenblock_mirror_2d.at
				( ( sublevel_x_coord_tile + i ) & 0x1f,
				( sublevel_y_coord_tile + j ) & 0x1f )
			= horiz_sublevel_tile_at( sublevel_x_coord_tile + i,
				sublevel_y_coord_tile + j );
		}
	}
	
	
}

void active_level_manager::copy_sublevel_from_array_csz_2d_helper_to_vram()
	//( array_2d_helper<scr_entry>& screenblock_in_vram_2d,
	//array_2d_helper<scr_entry>& screenblock_mirror_2d )
{
	memcpy32( active_level::bg0_screenblock_2d.the_array, 
		active_level::bg0_screenblock_mirror_2d.the_array,
		sizeof(scr_entry) * active_level::bg0_screenblock_mirror_2d
		.get_size() / sizeof(u32) ); 
}


// This function has been moved to the sprite_manager class.  Also, it has
// been updated.
//void active_level_manager::init_horiz_sublevel_sprite_ipg_lists 
//	( const sprite_init_param_group* the_ext_sprite_ipg_arr, 
//	u32 the_ext_sprite_ipg_arr_size )
//{
//	
//	for ( u32 i=0; i<the_ext_sprite_ipg_arr_size; ++i )
//	{
//		if ( the_ext_sprite_ipg_arr[i].type != st_default 
//			&& the_ext_sprite_ipg_arr[i].type != st_player )
//		{
//			active_level::horiz_sublevel_sprite_ipg_lists 
//				[the_ext_sprite_ipg_arr[i].initial_block_grid_x_coord]
//				.push_front(the_ext_sprite_ipg_arr[i]);
//		}
//	}
//	
//	
//	for ( auto iter = active_level::horiz_sublevel_sprite_ipg_lists.begin(); 
//		iter != active_level::horiz_sublevel_sprite_ipg_lists.end(); 
//		++iter )
//	{
//		if ( !iter->empty() )
//		{
//			iter->sort();
//		}
//	}
//	
//	
//}




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
