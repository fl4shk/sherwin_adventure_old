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


#include "game_manager_class.hpp"

#include "level_stuff/active_level_manager_class.hpp"
#include "sprite_stuff/sprite_manager_class.hpp"
#include "hud_manager_class.hpp"

#include "../gfx/the_block_gfx.h"
#include "../gfx/title_screen.h"

#include "../test_level/test_level.hpp"

#include "../audio/practice_17.h"


//#include <stdlib.h>


int GameManager::test_int_global;

const char GameManager::sram_const_init_str[] = "Save data initialized.";
const u32 GameManager::sram_init_str_size 
	= sizeof(GameManager::sram_const_init_str) / sizeof(char);

char GameManager::sram_init_str[GameManager::sram_init_str_size];
u8 GameManager::test_sram_arr[GameManager::test_sram_arr_size];

game_mode GameManager::curr_game_mode;


void GameManager::vblank_func()
{
	// If a bug was automatically detected.
	if (curr_game_mode == gm_do_halt)
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


	GfxManager::copy_bgofs_mirror_to_registers();

	//mmFrame();

	key_poll();
	//pause_or_unpause_music();

	if (curr_game_mode != gm_title_screen 
		&& curr_game_mode != gm_initializing_the_game)
	{
		if (mmActive())
		{
			mmFrame();
		}
	}

	switch (curr_game_mode)
	{
		// When on the title screen.
		case gm_title_screen:
			break;

		// When initializing the game
		case gm_initializing_the_game:
			break;

		// When loading a Level.
		case gm_loading_level:
			HudManager::hud_was_generated = false;
			break;

		// When changing from one Sublevel To another.
		case gm_changing_sublevel:
			break;

		// When in a Sublevel.
		case gm_in_sublevel:
			copy_oam_mirror_to_oam();
			GfxManager::copy_bgofs_mirror_to_registers();
			GfxManager::upload_bg_tiles_to_vram();

			ActiveLevelManager
				::copy_sublevel_from_array_csz_2d_helper_to_vram();
			SpriteManager::upload_tiles_of_active_sprites_to_vram();

			HudManager::copy_hud_from_array_csz_2d_helper_to_vram();
			break;

		// If a bug was automatically detected (this should never be the
		// case since gm_do_halt Is handled at the start of this function).
		case gm_do_halt:
			break;

		default:
			break;
	}
}


void GameManager::title_screen_func()
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

	// Use screen base Block 28 for BG0's Map
	REG_BG0CNT = BGCNT_SBB(BG0_SBB);

	REG_BG1CNT = BGCNT_SBB(bg1_sbb);
	REG_BG2CNT = BGCNT_SBB(bg2_sbb);
	REG_BG3CNT = BGCNT_SBB(bg3_sbb);


	// Clear bgofs_mirror
	for (u32 i=0; i<3; ++i)
	{
		GfxManager::bgofs_mirror[i].curr.x 
			= GfxManager::bgofs_mirror[i].prev.x = {0};
		GfxManager::bgofs_mirror[i].curr.y 
			= GfxManager::bgofs_mirror[i].prev.y = {0};
	}

	GfxManager::copy_bgofs_mirror_to_registers();


	// Copy the title screen's tiles and tilemap To VRAM
	bios_do_lz77_uncomp_vram(title_screenTiles, BG_TILE_VRAM);

	GfxManager::upload_bg_palettes_to_target(BG_PAL_RAM);

	// This Is sort of a hack.
	bios_do_lz77_uncomp_wram(title_screenMap, 
		ActiveLevel::bg0_screenblock_mirror);
	ActiveLevelManager::copy_sublevel_from_array_csz_2d_helper_to_vram();


	// Disable forced blank
	clear_bits(REG_DISPCNT, DCNT_BLANK_MASK);

	//memcpy8(test_sram_arr, (void *)debug_arr_u32, test_sram_arr_size);

	for (;;)
	{
		bios_wait_for_vblank();

		key_poll();

		// Start the game if the Start button Is hit
		if (key_hit(KEY_START))
		{


			//irqSet(IRQ_VBLANK, (u32)vblank_func);
			//irqEnable(IRQ_VBLANK);

			irqSet(IRQ_VBLANK, (u32)irq_dummy);
			irqEnable(IRQ_VBLANK);

			reinit_the_game();
			break;
		}

	}
}

void GameManager::reinit_the_game()
{
	curr_game_mode = gm_initializing_the_game;
	bios_wait_for_vblank();

	GfxManager::fade_out_to_white(15);

	GfxManager::init_hud_vram_as_tiles_start_offset();


	// Use video Mode 0, use 1D object mapping, enable forced blank,
	// display BG 0, BG 1, and objects.
	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ_1D | DCNT_BLANK_ON | DCNT_BG0_ON
		| DCNT_BG1_ON | DCNT_OBJ_ON;

	//// Use video Mode 0, use 1D object mapping, enable forced blank, 
	//// and display BG 0, BG 1, BG 2, BG 3, and objects
	//REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ_1D | DCNT_BLANK_ON | DCNT_BG0_ON
	//	| DCNT_BG1_ON | DCNT_BG2_ON | DCNT_BG3_ON | DCNT_OBJ_ON;

	// Use screen base Block 28 for BG0's Map.
	REG_BG0CNT = BGCNT_SBB(BG0_SBB) | BGCNT_PRIO(1);

	// Give BG1 a higher display priority than BG0.
	REG_BG1CNT = BGCNT_SBB(bg1_sbb) | BGCNT_PRIO(0);
	REG_BG2CNT = BGCNT_SBB(bg2_sbb) | BGCNT_PRIO(1);
	REG_BG3CNT = BGCNT_SBB(bg3_sbb) | BGCNT_PRIO(1);

	//u32 the_metatile_id = GfxManager::get_metatile_number_of_block_type
	//	(bt_eyes);
	//u32 the_palette_id = GfxManager::get_palette_number_of_block_type
	//	(bt_eyes);
	//u32 num_tiles_per_metatile = GfxManager::num_tiles_in_ss_16x16;
	//
	//for (u32 i=0; i<screenblock_size; ++i)
	//{
	//	SE_RAM[bg1_sbb][i] 
	//		= SE_ID(the_metatile_id * num_tiles_per_metatile)
	//		| SE_PALBANK(the_palette_id);
	//}

	//bios_wait_for_vblank();

	//for (u32 i=0; i<screenblock_size; ++i)
	//{
	//	SE_RAM[bg1_sbb][i] = bt_wood * 4;
	//}

	// Copy the Sprite palettes To OBJ Palette RAM.
	GfxManager::upload_sprite_palettes_to_target(OBJ_PAL_RAM);

	//// Copy the Sprite graphics To OBJ Video RAM.
	//GfxManager::upload_default_sprite_graphics();

	// Also, copy the_block_gfxPalLen To BG Palette RAM
	GfxManager::upload_bg_palettes_to_target(BG_PAL_RAM);

	//bios_wait_for_vblank();

	// Finally, copy the_block_gfxTiles To BG VRAM, screenblock 0
	GfxManager::upload_bg_tiles_to_vram();

	//bios_wait_for_vblank();
	SpriteManager::next_oam_index = 0; 
	ActiveLevelManager::load_level(&test_level);



	GfxManager::fade_out_to_white(1);
	HudManager::update_hud_in_screenblock_mirror_2d();
	HudManager::copy_hud_from_array_csz_2d_helper_to_vram();

	irqSet(IRQ_VBLANK, (u32)mmVBlank);
	irqEnable(IRQ_VBLANK);
	// Don't call mmInitDefault more than once.  It uses malloc(),
	// and it apparently MaxMOD doesn't ever call free().
	mmInitDefault((mm_addr)practice_17_bin, 8);
	mmSetVBlankHandler(reinterpret_cast<void*>(vblank_func));
	// Also, start playing music when the game Is started.
	mmStart(MOD_PRACTICE_17, MM_PLAY_LOOP);

	SpriteManager::upload_tiles_of_active_sprites_to_vram();

	//bios_wait_for_vblank();
	// Disable forced blank
	clear_bits(REG_DISPCNT, DCNT_BLANK_MASK);


	GfxManager::fade_in(15);
	bios_wait_for_vblank();

	//curr_game_mode = gm_in_sublevel;
}



