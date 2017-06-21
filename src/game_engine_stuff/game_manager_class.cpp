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
// General Public License FOR more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#include "game_manager_class.hpp"

#include "level_stuff/active_level_manager_class.hpp"
#include "sprite_stuff/sprite_manager_class.hpp"
#include "hud_manager_class.hpp"

#include "../gfx/the_block_gfx.h"
#include "../gfx/title_screen.h"

#include "../test_level/test_level.hpp"

#include "../audio/practice_17.h"


//#include <stdlib.h>


int game_manager::test_int_global;

const char game_manager::sram_const_init_str[] = "Save data initialized.";
const u32 game_manager::sram_init_str_size 
	= sizeof(game_manager::sram_const_init_str) / sizeof(char);

char game_manager::sram_init_str[game_manager::sram_init_str_size];
u8 game_manager::test_sram_arr[game_manager::test_sram_arr_size];

game_mode game_manager::curr_game_mode;


void game_manager::vblank_func()
{
	// If a bug was automatically detected.
	if ( curr_game_mode == gm_do_halt )
	{
		// Stop the sound stuff
		if (mmActive())
		{
			//mmPause();
			mmSetModuleVolume(static_cast<mm_word>(0));
			mmSetJingleVolume(static_cast<mm_word>(0));
			mmEffectCancelAll();
			
			mmFrame();
			
			//mmPause();
			//mmStop();
		}
		
		
		// Enable forced blank
		REG_DISPCNT = DCNT_BLANK_ON;
		
		return;
	}
	
	
	gfx_manager::copy_bgofs_mirror_to_registers();
	
	//mmFrame();
	
	key_poll();
	//pause_or_unpause_music();
	
	if ( curr_game_mode != gm_title_screen 
		&& curr_game_mode != gm_initializing_the_game )
	{
		if (mmActive())
		{
			mmFrame();
		}
	}
	
	switch ( curr_game_mode )
	{
		// When on the title screen.
		case gm_title_screen:
			break;
		
		// When initializing the game
		case gm_initializing_the_game:
			break;
		
		// When loading a level.
		case gm_loading_level:
			hud_manager::hud_was_generated = false;
			break;
		
		// When changing from one sublevel to another.
		case gm_changing_sublevel:
			break;
		
		// When in a sublevel.
		case gm_in_sublevel:
			copy_oam_mirror_to_oam();
			gfx_manager::copy_bgofs_mirror_to_registers();
			gfx_manager::upload_bg_tiles_to_vram();
			
			active_level_manager
				::copy_sublevel_from_array_csz_2d_helper_to_vram();
			sprite_manager::upload_tiles_of_active_sprites_to_vram();
			
			hud_manager::copy_hud_from_array_csz_2d_helper_to_vram();
			break;
		
		// If a bug was automatically detected (this should never be the
		// case since gm_do_halt is handled at the start of this function).
		case gm_do_halt:
			break;
		
		default:
			break;
	}
}


void game_manager::title_screen_func()
{
	curr_game_mode = gm_title_screen;
	
	irq_init();
	//irqEnable(IRQ_VBLANK);
	
	bios_wait_for_vblank();
	
	// Use video Mode 0, use 1D object mapping, enable forced blank, 
	// and display BG 0.
	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ_1D | DCNT_BLANK_ON | DCNT_BG0_ON;
	
	//// Use video Mode 0, use 1D object mapping, enable forced blank, 
	//// and display BG 0, BG 1, BG 2, and BG 3
	//REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ_1D | DCNT_BLANK_ON | DCNT_BG0_ON
	//	| DCNT_BG1_ON | DCNT_BG2_ON | DCNT_BG3_ON | DCNT_OBJ_ON;
	
	// Use screen base block 28 FOR BG0's Map
	REG_BG0CNT = bgcnt_sbb(BG0_SBB);
	
	REG_BG1CNT = bgcnt_sbb(bg1_sbb);
	REG_BG2CNT = bgcnt_sbb(bg2_sbb);
	REG_BG3CNT = bgcnt_sbb(bg3_sbb);
	
	
	// Clear bgofs_mirror
	FOR ( u32 i=0; i<3; ++i )
	{
		gfx_manager::bgofs_mirror[i].curr.x 
			= gfx_manager::bgofs_mirror[i].prev.x = {0};
		gfx_manager::bgofs_mirror[i].curr.y 
			= gfx_manager::bgofs_mirror[i].prev.y = {0};
	}
	
	gfx_manager::copy_bgofs_mirror_to_registers();
	
	
	// Copy the title screen's tiles and tilemap to VRAM
	bios_do_lz77_uncomp_vram( title_screenTiles, BG_TILE_VRAM );
	
	gfx_manager::upload_bg_palettes_to_target(BG_PAL_RAM);
	
	// This is sort of a hack.
	bios_do_lz77_uncomp_wram( title_screenMap, 
		active_level::bg0_screenblock_mirror );
	active_level_manager::copy_sublevel_from_array_csz_2d_helper_to_vram();
	
	
	// Disable forced blank
	clear_bits( REG_DISPCNT, DCNT_BLANK_MASK );
	
	//memcpy8( test_sram_arr, (void *)debug_arr_u32, test_sram_arr_size );
	
	FOR (;;)
	{
		bios_wait_for_vblank();
		
		key_poll();
		
		// Start the game if the Start button is hit
		if ( key_hit(KEY_START) )
		{
			
			
			//irqSet( IRQ_VBLANK, (u32)vblank_func );
			//irqEnable(IRQ_VBLANK);
			
			irqSet( IRQ_VBLANK, (u32)irq_dummy );
			irqEnable(IRQ_VBLANK);
			
			reinit_the_game();
			break;
		}
		
	}
}

void game_manager::reinit_the_game()
{
	curr_game_mode = gm_initializing_the_game;
	bios_wait_for_vblank();
	
	gfx_manager::fade_out_to_white(15);
	
	gfx_manager::init_hud_vram_as_tiles_start_offset();
	
	
	// Use video Mode 0, use 1D object mapping, enable forced blank,
	// display BG 0, BG 1, and objects.
	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ_1D | DCNT_BLANK_ON | DCNT_BG0_ON
		| DCNT_BG1_ON | DCNT_OBJ_ON;
	
	//// Use video Mode 0, use 1D object mapping, enable forced blank, 
	//// and display BG 0, BG 1, BG 2, BG 3, and objects
	//REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ_1D | DCNT_BLANK_ON | DCNT_BG0_ON
	//	| DCNT_BG1_ON | DCNT_BG2_ON | DCNT_BG3_ON | DCNT_OBJ_ON;
	
	// Use screen base block 28 FOR BG0's Map.
	REG_BG0CNT = bgcnt_sbb(BG0_SBB) | bgcnt_prio(1);
	
	// Give BG1 a higher display priority than BG0.
	REG_BG1CNT = bgcnt_sbb(bg1_sbb) | bgcnt_prio(0);
	REG_BG2CNT = bgcnt_sbb(bg2_sbb) | bgcnt_prio(1);
	REG_BG3CNT = bgcnt_sbb(bg3_sbb) | bgcnt_prio(1);
	
	//u32 the_metatile_id = gfx_manager::get_metatile_number_of_block_type
	//	(bt_eyes);
	//u32 the_palette_id = gfx_manager::get_palette_number_of_block_type
	//	(bt_eyes);
	//u32 num_tiles_per_metatile = gfx_manager::num_tiles_in_ss_16x16;
	//
	//FOR ( u32 i=0; i<screenblock_size; ++i )
	//{
	//	SE_RAM[bg1_sbb][i] 
	//		= se_id( the_metatile_id * num_tiles_per_metatile )
	//		| se_palbank(the_palette_id);
	//}
	
	//bios_wait_for_vblank();
	
	//FOR ( u32 i=0; i<screenblock_size; ++i )
	//{
	//	SE_RAM[bg1_sbb][i] = bt_wood * 4;
	//}
	
	// Copy the sprite palettes to OBJ Palette RAM.
	gfx_manager::upload_sprite_palettes_to_target(OBJ_PAL_RAM);
	
	//// Copy the sprite graphics to OBJ Video RAM.
	//gfx_manager::upload_default_sprite_graphics();
	
	// Also, copy the_block_gfxPalLen to BG Palette RAM
	gfx_manager::upload_bg_palettes_to_target(BG_PAL_RAM);
	
	//bios_wait_for_vblank();
	
	// Finally, copy the_block_gfxTiles to BG VRAM, screenblock 0
	gfx_manager::upload_bg_tiles_to_vram();
	
	//bios_wait_for_vblank();
	sprite_manager::next_oam_index = 0; 
	active_level_manager::load_level(&test_level);
	
	
	
	gfx_manager::fade_out_to_white(1);
	hud_manager::update_hud_in_screenblock_mirror_2d();
	hud_manager::copy_hud_from_array_csz_2d_helper_to_vram();
	
	irqSet( IRQ_VBLANK, (u32)mmVBlank );
	irqEnable(IRQ_VBLANK);
	// Don't call mmInitDefault more than once.  It uses malloc(),
	// and it apparently MaxMOD doesn't ever call free().
	mmInitDefault( (mm_addr)practice_17_bin, 8 );
	mmSetVBlankHandler(reinterpret_cast<void*>(vblank_func));
	// Also, start playing music when the game is started.
	mmStart( MOD_PRACTICE_17, MM_PLAY_LOOP );
	
	sprite_manager::upload_tiles_of_active_sprites_to_vram();
	
	//bios_wait_for_vblank();
	// Disable forced blank
	clear_bits( REG_DISPCNT, DCNT_BLANK_MASK );
	
	
	gfx_manager::fade_in(15);
	bios_wait_for_vblank();
	
	//curr_game_mode = gm_in_sublevel;
}



