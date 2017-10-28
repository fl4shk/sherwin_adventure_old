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


//#include "sprite_gfx_stuff.hpp"
#include "gfx_manager_class.hpp"

#include "game_manager_class.hpp"


#include "../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../gba_specific_stuff/oam_entry_defines.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "../general_utility_stuff/misc_bitwise_funcs.hpp"
#include "../general_utility_stuff/debug_vars.hpp"

#include "../gfx/title_screen.h"

#include "block_stuff/block_stuff.hpp"
#include "../gfx/the_block_gfx.h"
//#include "../gfx/text_8x16_gfx.h"
#include "../gfx/text_8x8_thick_gfx.h"


#include "sprite_stuff/sprite_class.hpp"
#include "../gfx/sherwin_gfx.h"
#include "../gfx/the_powerup_gfx.h"
//#include "../gfx/the_block_like_sprites_gfx.h"
#include "../gfx/the_door_gfx.h"
#include "../gfx/the_golem_enemy_gfx.h"
#include "../gfx/the_16x16_secondary_sprites_gfx.h"

BgPoint GfxManager::prev_prev_bgofs_mirror[bgofs_mirror_size];
PrevCurrPair<BgPoint> GfxManager::bgofs_mirror[bgofs_mirror_size];

// Current component arrays, stored in EWRAM as Fixed24p8's for speed and
// accuracy reasons.
Fixed24p8 GfxManager::bg_fade_curr_red_arr
	[bg_fade_curr_component_arr_size],
GfxManager::bg_fade_curr_green_arr
	[bg_fade_curr_component_arr_size],
GfxManager::bg_fade_curr_blue_arr
	[bg_fade_curr_component_arr_size];

Fixed24p8 GfxManager::obj_fade_curr_red_arr
	[obj_fade_curr_component_arr_size],
GfxManager::obj_fade_curr_green_arr
	[obj_fade_curr_component_arr_size],
GfxManager::obj_fade_curr_blue_arr
	[obj_fade_curr_component_arr_size];


// Fade out/in step amounts.
Fixed24p8 GfxManager::bg_fade_red_step_amount_arr
	[bg_fade_step_amount_arr_size],
GfxManager::bg_fade_green_step_amount_arr
	[bg_fade_step_amount_arr_size],
GfxManager::bg_fade_blue_step_amount_arr
	[bg_fade_step_amount_arr_size];

Fixed24p8 GfxManager::obj_fade_red_step_amount_arr
	[obj_fade_step_amount_arr_size],
GfxManager::obj_fade_green_step_amount_arr
	[obj_fade_step_amount_arr_size],
GfxManager::obj_fade_blue_step_amount_arr
	[obj_fade_step_amount_arr_size];


// BG palette stuff
u16 GfxManager::bg_pal_mirror[bg_pal_ram_size_in_u16];

// Sprite palette stuff
u16 GfxManager::obj_pal_mirror[obj_pal_ram_size_in_u16];

// HUD stuff
u32 GfxManager::hud_vram_as_tiles_start_offset;


void GfxManager::copy_bgofs_mirror_to_registers()
{
	//REG_BGOFS[0] = bgofs_mirror[0].curr;
	//REG_BGOFS[1] = bgofs_mirror[1].curr;
	//REG_BGOFS[2] = bgofs_mirror[2].curr;
	//REG_BGOFS[3] = bgofs_mirror[3].curr;

	for (u32 i=0; i<4; ++i)
	{
		REG_BGOFS[i].x = (s16)bgofs_mirror[i].curr.x.to_int_for_on_screen();
		REG_BGOFS[i].y = (s16)bgofs_mirror[i].curr.y.to_int_for_on_screen();

		//REG_BGOFS[i].x = ((s32)bgofs_mirror[i].curr.x
		//	.to_int_for_on_screen()) & 0xffff;
		//REG_BGOFS[i].y = ((s32)bgofs_mirror[i].curr.y
		//	.to_int_for_on_screen()) & 0xffff;

		//REG_BGOFS[i].x = (s16)bgofs_mirror[i].curr.x.floor_to_int();
		//REG_BGOFS[i].y = (s16)bgofs_mirror[i].curr.y.floor_to_int();

		//REG_BGOFS[i].x = bgofs_mirror[i].curr.x.floor_to_int() & 0xffff;
		//REG_BGOFS[i].y = bgofs_mirror[i].curr.y.floor_to_int() & 0xffff;
	}
}


void GfxManager::upload_bg_palettes_to_target(vu16* target)
{
	if (GameManager::curr_game_mode == gm_title_screen)
	{
		memcpy32(target, title_screenPal,
			title_screenPalLen / sizeof(u32));
	}
	else //if (GameManager::curr_game_mode >= gm_initializing_the_game
		//&& GameManager::curr_game_mode <= gm_in_sublevel)
	{
		memcpy32(&(target[bgps_in_level_block_0 
			* num_colors_per_palette]), 
			the_block_gfxPal,
			the_block_gfxPalLen / sizeof(u32));
		//memcpy32(&(target[bgps_in_level_hud 
		//	* num_colors_per_palette]), 
		//	text_8x16_gfxPal,
		//	text_8x16_gfxPalLen / sizeof(u32));
		memcpy32(&(target[bgps_in_level_hud 
			* num_colors_per_palette]),
			text_8x8_thick_gfxPal,
			text_8x8_thick_gfxPalLen / sizeof(u32));
	}
}


void GfxManager::copy_bg_pal_mirror_to_bg_pal_ram()
{
	memcpy32(BG_PAL_RAM, bg_pal_mirror, bg_pal_ram_size 
		/ sizeof(u32));
	//arr_memcpy32(BG_PAL_RAM, bg_pal_mirror, bg_pal_ram_size);
}


//void GfxManager::update_block_graphics_in_vram
//	(const unsigned short* the_tiles)
void GfxManager::upload_bg_tiles_to_vram()
{

	// Note:  this function currently does multiple VRAM graphics updates
	// whenever multiple block_types share the same graphics_slot.  An
	// example of this Is how each variation of bt_eyes shares the same
	// graphics slot.
	for (u32 i=0; i<block_type::lim_bt; ++i)
	{
		u32 graphics_slot = get_graphics_slot_of_block_type 
			((block_type)i);
		u32 metatile_number = get_metatile_number_of_block_type
			((block_type)i);

		memcpy32(&(BG_TILE_VRAM_AS_TILES[graphics_slot]),

			&((reinterpret_cast<const Tile*>(the_block_gfxTiles))
			[metatile_number * num_tiles_in_ss_16x16]),

			sizeof(Tile) * num_tiles_in_ss_16x16 / sizeof (u32));

		//arr_memcpy32(&(BG_TILE_VRAM_AS_TILES[graphics_slot]),
		//
		//	&((reinterpret_cast<const Tile*>(the_block_gfxTiles))
		//	[metatile_number * num_tiles_in_ss_16x16]),
		//
		//	sizeof(Tile) * num_tiles_in_ss_16x16);
	}

	memcpy32(&(BG_TILE_VRAM_AS_TILES[hud_vram_as_tiles_start_offset]),
		text_8x8_thick_gfxTiles,
		text_8x8_thick_gfxTilesLen / sizeof(u32));
	//arr_memcpy32(&(BG_TILE_VRAM_AS_TILES[hud_vram_as_tiles_start_offset]),
	//	text_8x8_thick_gfxTiles, text_8x8_thick_gfxTilesLen);
}


void GfxManager::upload_sprite_palettes_to_target(vu16* target)
{
	//memcpy32(target, the_spritesPal, 
	//	the_spritesPalLen / sizeof(u32));

	//static constexpr u32 num_colors_per_palette = 16;

	// The Player's palettes
	memcpy32(&(target[sps_player * num_colors_per_palette]), 
		sherwin_gfxPal, sherwin_gfxPalLen / sizeof(u32));

	// The powerups' palettes
	memcpy32(&(target[sps_powerup * num_colors_per_palette]), 
		the_powerup_gfxPal, the_powerup_gfxPalLen / sizeof(u32));


	// The Door sprites' palettes
	memcpy32(&(target[sps_door * num_colors_per_palette]), 
		the_door_gfxPal, the_door_gfxPalLen / sizeof(u32));

	// The golems and other enemies' palettes
	memcpy32(&(target[sps_enemy_0 * num_colors_per_palette]),
		the_golem_enemy_gfxPal, the_golem_enemy_gfxPalLen / sizeof(u32));

	// The secondary sprites' palettes
	memcpy32(&(target[sps_secondary_0 * num_colors_per_palette]),
		the_16x16_secondary_sprites_gfxPal,
		the_16x16_secondary_sprites_gfxPalLen / sizeof(u32));
}

void GfxManager::copy_obj_pal_mirror_to_obj_pal_ram()
{
	memcpy32(OBJ_PAL_RAM, obj_pal_mirror, obj_pal_ram_size 
		/ sizeof(u32));
	//arr_memcpy32(OBJ_PAL_RAM, obj_pal_mirror, obj_pal_ram_size);
}


void GfxManager::upload_sprite_tiles_to_vram(Sprite& the_sprite)
{
	// It gets tiring To have To type
	// sprite_stuff_array[the_sprite.the_sprite_type] So much.
	//sprite_base_stuff* sbs_ptr = sprite_stuff_array
	//	[the_sprite.the_sprite_type];

	//// This memfill32() call isn't strictly necessary, but it makes VRAM
	//// look nicer in the VRAM viewer functionality of some emulators.
	//memfill32(&(((Tile*)OBJ_TILE_VRAM)[the_sprite.get_vram_chunk_index()
	//	* num_tiles_in_ss_32x32]), 0, sizeof(Tile) * num_tiles_in_ss_32x32
	//	/ sizeof(u32));


	memcpy32(&(((Tile*)OBJ_TILE_VRAM)[the_sprite.get_vram_chunk_index()
			* num_tiles_in_ss_32x32]),

		&(the_sprite.get_tile_arr()
			[the_sprite.get_curr_relative_tile_slot()]),

		//sizeof(Tile) * num_tiles_in_ss_32x32 / sizeof(u32));
		sizeof(Tile) * the_sprite.get_num_active_gfx_tiles() 
		/ sizeof(u32));

	//arr_memcpy32(&(((Tile*)OBJ_TILE_VRAM)
	//	[the_sprite.get_vram_chunk_index() * num_tiles_in_ss_32x32]),
	//
	//	&(the_sprite.get_tile_arr()
	//		[the_sprite.get_curr_relative_tile_slot()]),
	//
	//	//sizeof(Tile) * num_tiles_in_ss_32x32 / sizeof(u32));
	//	sizeof(Tile) * the_sprite.get_num_active_gfx_tiles());
}


void GfxManager::fade_out_to_black(u32 num_steps, 
	u32 num_frames_to_wait_per_iter)
{
	// Build the BG arrays of step amounts
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		s32 red_orig = rgb15_get_red_component(BG_PAL_RAM[i]);
		s32 green_orig = rgb15_get_green_component(BG_PAL_RAM[i]);
		s32 blue_orig = rgb15_get_blue_component(BG_PAL_RAM[i]);

		s32 target_red = 0;
		s32 target_green = 0;
		s32 target_blue = 0;

		bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);

		// The target color Is black, for the entire screen.
		Fixed24p8& red_step_amount 
			= bg_fade_red_step_amount_arr[i];
		Fixed24p8& green_step_amount 
			= bg_fade_green_step_amount_arr[i];
		Fixed24p8& blue_step_amount 
			= bg_fade_blue_step_amount_arr[i];

		red_step_amount = (make_f24p8(target_red) 
			- bg_fade_curr_red_arr[i]) / (u16)num_steps;
		green_step_amount = (make_f24p8(target_green)
			- bg_fade_curr_green_arr[i]) / (u16)num_steps;
		blue_step_amount = (make_f24p8(target_blue)
			- bg_fade_curr_blue_arr[i]) / (u16)num_steps;
	}

	// Build the OBJ arrays of step amounts
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		s32 red_orig = rgb15_get_red_component(OBJ_PAL_RAM[i]);
		s32 green_orig = rgb15_get_green_component(OBJ_PAL_RAM[i]);
		s32 blue_orig = rgb15_get_blue_component(OBJ_PAL_RAM[i]);

		s32 target_red = 0;
		s32 target_green = 0;
		s32 target_blue = 0;

		obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);

		// The target color Is black, for the entire screen.
		Fixed24p8& red_step_amount 
			= obj_fade_red_step_amount_arr[i];
		Fixed24p8& green_step_amount 
			= obj_fade_green_step_amount_arr[i];
		Fixed24p8& blue_step_amount 
			= obj_fade_blue_step_amount_arr[i];

		red_step_amount = (make_f24p8(target_red) 
			- obj_fade_curr_red_arr[i]) / (u16)num_steps;
		green_step_amount = (make_f24p8(target_green)
			- obj_fade_curr_green_arr[i]) / (u16)num_steps;
		blue_step_amount = (make_f24p8(target_blue)
			- obj_fade_curr_blue_arr[i]) / (u16)num_steps;
	}

	// Fading iteration
	for (u32 i=0; i<num_steps; ++i)
	{
		// for each BG palette
		for (u32 j=0; j<num_colors_in_8_palettes; ++j)
		{
			Fixed24p8& curr_red = bg_fade_curr_red_arr[j];
			Fixed24p8& curr_green = bg_fade_curr_green_arr[j];
			Fixed24p8& curr_blue = bg_fade_curr_blue_arr[j];

			Fixed24p8 red_step_amount 
				= bg_fade_red_step_amount_arr[j];
			Fixed24p8 green_step_amount 
				= bg_fade_green_step_amount_arr[j];
			Fixed24p8 blue_step_amount 
				= bg_fade_blue_step_amount_arr[j];

			clamped_rgb15_f24p8_component_add(curr_red, 
				red_step_amount, (Fixed24p8){0});
			clamped_rgb15_f24p8_component_add(curr_green, 
				green_step_amount, (Fixed24p8){0});
			clamped_rgb15_f24p8_component_add(curr_blue, 
				blue_step_amount, (Fixed24p8){0});

			BG_PAL_RAM[j] = make_rgb15(curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int());
		}

		// for each OBJ palette
		for (u32 j=0; j<num_colors_in_8_palettes; ++j)
		{
			Fixed24p8& curr_red = obj_fade_curr_red_arr[j];
			Fixed24p8& curr_green = obj_fade_curr_green_arr[j];
			Fixed24p8& curr_blue = obj_fade_curr_blue_arr[j];

			Fixed24p8 red_step_amount 
				= obj_fade_red_step_amount_arr[j];
			Fixed24p8 green_step_amount 
				= obj_fade_green_step_amount_arr[j];
			Fixed24p8 blue_step_amount 
				= obj_fade_blue_step_amount_arr[j];

			clamped_rgb15_f24p8_component_add(curr_red, 
				red_step_amount, (Fixed24p8){0});
			clamped_rgb15_f24p8_component_add(curr_green, 
				green_step_amount, (Fixed24p8){0});
			clamped_rgb15_f24p8_component_add(curr_blue, 
				blue_step_amount, (Fixed24p8){0});

			OBJ_PAL_RAM[j] = make_rgb15(curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int());
		}

		GameManager::wait_for_x_frames(num_frames_to_wait_per_iter);
	}


	// Just in case the conversion wasn't complete
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		BG_PAL_RAM[i] = 0;
	}
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		OBJ_PAL_RAM[i] = 0;
	}
}


void GfxManager::fade_out_to_white(u32 num_steps, 
	u32 num_frames_to_wait_per_iter)
{
	// Build the BG arrays of step amounts
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		s32 red_orig = rgb15_get_red_component(BG_PAL_RAM[i]);
		s32 green_orig = rgb15_get_green_component(BG_PAL_RAM[i]);
		s32 blue_orig = rgb15_get_blue_component(BG_PAL_RAM[i]);

		s32 target_red = RGB15_COMPONENT_MAX_VAL;
		s32 target_green = RGB15_COMPONENT_MAX_VAL;
		s32 target_blue = RGB15_COMPONENT_MAX_VAL;

		bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);

		// The target color Is white, for the entire screen.
		Fixed24p8& red_step_amount 
			= bg_fade_red_step_amount_arr[i];
		Fixed24p8& green_step_amount 
			= bg_fade_green_step_amount_arr[i];
		Fixed24p8& blue_step_amount 
			= bg_fade_blue_step_amount_arr[i];

		red_step_amount = (make_f24p8(target_red) 
			- bg_fade_curr_red_arr[i]) / (u16)num_steps;
		green_step_amount = (make_f24p8(target_green)
			- bg_fade_curr_green_arr[i]) / (u16)num_steps;
		blue_step_amount = (make_f24p8(target_blue)
			- bg_fade_curr_blue_arr[i]) / (u16)num_steps;
	}

	// Build the OBJ arrays of step amounts
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		s32 red_orig = rgb15_get_red_component(OBJ_PAL_RAM[i]);
		s32 green_orig = rgb15_get_green_component(OBJ_PAL_RAM[i]);
		s32 blue_orig = rgb15_get_blue_component(OBJ_PAL_RAM[i]);

		s32 target_red = RGB15_COMPONENT_MAX_VAL;
		s32 target_green = RGB15_COMPONENT_MAX_VAL;
		s32 target_blue = RGB15_COMPONENT_MAX_VAL;

		obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);

		// The target color Is white, for the entire screen.
		Fixed24p8& red_step_amount 
			= obj_fade_red_step_amount_arr[i];
		Fixed24p8& green_step_amount 
			= obj_fade_green_step_amount_arr[i];
		Fixed24p8& blue_step_amount 
			= obj_fade_blue_step_amount_arr[i];

		red_step_amount = (make_f24p8(target_red) 
			- obj_fade_curr_red_arr[i]) / (u16)num_steps;
		green_step_amount = (make_f24p8(target_green)
			- obj_fade_curr_green_arr[i]) / (u16)num_steps;
		blue_step_amount = (make_f24p8(target_blue)
			- obj_fade_curr_blue_arr[i]) / (u16)num_steps;
	}

	// Fading iteration
	for (u32 i=0; i<num_steps; ++i)
	{
		// for each BG palette
		for (u32 j=0; j<num_colors_in_8_palettes; ++j)
		{
			Fixed24p8& curr_red = bg_fade_curr_red_arr[j];
			Fixed24p8& curr_green = bg_fade_curr_green_arr[j];
			Fixed24p8& curr_blue = bg_fade_curr_blue_arr[j];

			Fixed24p8 red_step_amount 
				= bg_fade_red_step_amount_arr[j];
			Fixed24p8 green_step_amount 
				= bg_fade_green_step_amount_arr[j];
			Fixed24p8 blue_step_amount 
				= bg_fade_blue_step_amount_arr[j];

			clamped_rgb15_f24p8_component_add(curr_red, 
				red_step_amount, (Fixed24p8){ RGB15_COMPONENT_MAX_VAL 
				<< Fixed24p8::get_shift() });
			clamped_rgb15_f24p8_component_add(curr_green, 
				green_step_amount, (Fixed24p8){ RGB15_COMPONENT_MAX_VAL
				<< Fixed24p8::get_shift() });
			clamped_rgb15_f24p8_component_add(curr_blue, 
				blue_step_amount, (Fixed24p8){ RGB15_COMPONENT_MAX_VAL
				<< Fixed24p8::get_shift() });

			BG_PAL_RAM[j] = make_rgb15(curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int());
		}

		// for each OBJ palette
		for (u32 j=0; j<num_colors_in_8_palettes; ++j)
		{
			Fixed24p8& curr_red = obj_fade_curr_red_arr[j];
			Fixed24p8& curr_green = obj_fade_curr_green_arr[j];
			Fixed24p8& curr_blue = obj_fade_curr_blue_arr[j];

			Fixed24p8 red_step_amount 
				= obj_fade_red_step_amount_arr[j];
			Fixed24p8 green_step_amount 
				= obj_fade_green_step_amount_arr[j];
			Fixed24p8 blue_step_amount 
				= obj_fade_blue_step_amount_arr[j];

			clamped_rgb15_f24p8_component_add(curr_red, 
				red_step_amount, (Fixed24p8){ RGB15_COMPONENT_MAX_VAL
				<< Fixed24p8::get_shift() });
			clamped_rgb15_f24p8_component_add(curr_green, 
				green_step_amount, (Fixed24p8){ RGB15_COMPONENT_MAX_VAL
				<< Fixed24p8::get_shift() });
			clamped_rgb15_f24p8_component_add(curr_blue, 
				blue_step_amount, (Fixed24p8){ RGB15_COMPONENT_MAX_VAL
				<< Fixed24p8::get_shift() });

			OBJ_PAL_RAM[j] = make_rgb15(curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int());
		}

		GameManager::wait_for_x_frames(num_frames_to_wait_per_iter);
	}


	bios_wait_for_vblank();

	// Just in case the conversion wasn't complete
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		//BG_PAL_RAM[i] = make_rgb15(RGB15_COMPONENT_MAX_VAL,
		//	RGB15_COMPONENT_MAX_VAL, RGB15_COMPONENT_MAX_VAL);
		BG_PAL_RAM[i] = 0x7fff;
	}
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		//OBJ_PAL_RAM[i] = make_rgb15(RGB15_COMPONENT_MAX_VAL,
		//	RGB15_COMPONENT_MAX_VAL, RGB15_COMPONENT_MAX_VAL);
		OBJ_PAL_RAM[i] = 0x7fff;
	}
}


void GfxManager::fade_in(u32 num_steps, u32 num_frames_to_wait_per_iter)
{
	upload_bg_palettes_to_target(bg_pal_mirror);
	upload_sprite_palettes_to_target(obj_pal_mirror);

	bios_wait_for_vblank();

	// Build the BG arrays of step amounts
	//for (u32 i=0; i<the_block_gfxPalLen / sizeof(u16); ++i)
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		s32 red_orig = rgb15_get_red_component(BG_PAL_RAM[i]);
		s32 green_orig = rgb15_get_green_component(BG_PAL_RAM[i]);
		s32 blue_orig = rgb15_get_blue_component(BG_PAL_RAM[i]);

		//s32 target_red = rgb15_get_red_component(the_block_gfxPal[i]);
		//s32 target_green = rgb15_get_green_component(the_block_gfxPal[i]);
		//s32 target_blue = rgb15_get_blue_component(the_block_gfxPal[i]);

		s32 target_red = rgb15_get_red_component(bg_pal_mirror[i]);
		s32 target_green = rgb15_get_green_component(bg_pal_mirror[i]);
		s32 target_blue = rgb15_get_blue_component(bg_pal_mirror[i]);

		bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);

		// The target color Is white, for the entire screen.
		Fixed24p8& red_step_amount 
			= bg_fade_red_step_amount_arr[i];
		Fixed24p8& green_step_amount 
			= bg_fade_green_step_amount_arr[i];
		Fixed24p8& blue_step_amount 
			= bg_fade_blue_step_amount_arr[i];

		red_step_amount = (make_f24p8(target_red) 
			- bg_fade_curr_red_arr[i]) / (u16)num_steps;
		green_step_amount = (make_f24p8(target_green)
			- bg_fade_curr_green_arr[i]) / (u16)num_steps;
		blue_step_amount = (make_f24p8(target_blue)
			- bg_fade_curr_blue_arr[i]) / (u16)num_steps;
	}

	// Build the OBJ arrays of step amounts
	for (u32 i=0; i<num_colors_in_8_palettes; ++i)
	{
		s32 red_orig = rgb15_get_red_component(OBJ_PAL_RAM[i]);
		s32 green_orig = rgb15_get_green_component(OBJ_PAL_RAM[i]);
		s32 blue_orig = rgb15_get_blue_component(OBJ_PAL_RAM[i]);

		s32 target_red = rgb15_get_red_component(obj_pal_mirror[i]);
		s32 target_green = rgb15_get_green_component(obj_pal_mirror[i]);
		s32 target_blue = rgb15_get_blue_component(obj_pal_mirror[i]);

		obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);

		// The target color Is white, for the entire screen.
		Fixed24p8& red_step_amount 
			= obj_fade_red_step_amount_arr[i];
		Fixed24p8& green_step_amount 
			= obj_fade_green_step_amount_arr[i];
		Fixed24p8& blue_step_amount 
			= obj_fade_blue_step_amount_arr[i];

		red_step_amount = (make_f24p8(target_red) 
			- obj_fade_curr_red_arr[i]) / (u16)num_steps;
		green_step_amount = (make_f24p8(target_green)
			- obj_fade_curr_green_arr[i]) / (u16)num_steps;
		blue_step_amount = (make_f24p8(target_blue)
			- obj_fade_curr_blue_arr[i]) / (u16)num_steps;
	}

	// Fading iteration
	for (u32 i=0; i<num_steps; ++i)
	{
		ASM_COMMENT("Before BG palette loop");
		// for each BG palette
		//for (u32 j=0; j<the_block_gfxPalLen / sizeof(u16); ++j)
		for (u32 j=0; j<num_colors_in_8_palettes; ++j)
		{
			Fixed24p8& curr_red = bg_fade_curr_red_arr[j];
			Fixed24p8& curr_green = bg_fade_curr_green_arr[j];
			Fixed24p8& curr_blue = bg_fade_curr_blue_arr[j];

			Fixed24p8 red_step_amount 
				= bg_fade_red_step_amount_arr[j];
			Fixed24p8 green_step_amount 
				= bg_fade_green_step_amount_arr[j];
			Fixed24p8 blue_step_amount 
				= bg_fade_blue_step_amount_arr[j];

			// Don't need make_f24p8() for these because color component
			// values are guaranteed To be positive.
			//Fixed24p8 target_red = { (s32)rgb15_get_red_component
			//	(the_block_gfxPal[j]) << Fixed24p8::get_shift() };
			//Fixed24p8 target_green = { (s32)rgb15_get_green_component
			//	(the_block_gfxPal[j]) << Fixed24p8::get_shift() };
			//Fixed24p8 target_blue = { (s32)rgb15_get_blue_component
			//	(the_block_gfxPal[j]) << Fixed24p8::get_shift() };

			Fixed24p8 target_red = { (s32)rgb15_get_red_component
				(bg_pal_mirror[j]) << Fixed24p8::get_shift() };
			Fixed24p8 target_green = { (s32)rgb15_get_green_component
				(bg_pal_mirror[j]) << Fixed24p8::get_shift() };
			Fixed24p8 target_blue = { (s32)rgb15_get_blue_component
				(bg_pal_mirror[j]) << Fixed24p8::get_shift() };

			clamped_rgb15_f24p8_component_add(curr_red, 
				red_step_amount, target_red);
			clamped_rgb15_f24p8_component_add(curr_green, 
				green_step_amount, target_green);
			clamped_rgb15_f24p8_component_add(curr_blue, 
				blue_step_amount, target_blue);

			BG_PAL_RAM[j] = make_rgb15(curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int());
		}

		ASM_COMMENT("Before OBJ palette loop");
		// for each OBJ palette
		for (u32 j=0; j<num_colors_in_8_palettes; ++j)
		{
			Fixed24p8& curr_red = obj_fade_curr_red_arr[j];
			Fixed24p8& curr_green = obj_fade_curr_green_arr[j];
			Fixed24p8& curr_blue = obj_fade_curr_blue_arr[j];

			Fixed24p8 red_step_amount 
				= obj_fade_red_step_amount_arr[j];
			Fixed24p8 green_step_amount 
				= obj_fade_green_step_amount_arr[j];
			Fixed24p8 blue_step_amount 
				= obj_fade_blue_step_amount_arr[j];

			Fixed24p8 target_red = { (s32)rgb15_get_red_component
				(obj_pal_mirror[j]) << Fixed24p8::get_shift() };
			Fixed24p8 target_green = { (s32)rgb15_get_green_component
				(obj_pal_mirror[j]) << Fixed24p8::get_shift() };
			Fixed24p8 target_blue = { (s32)rgb15_get_blue_component
				(obj_pal_mirror[j]) << Fixed24p8::get_shift() };

			clamped_rgb15_f24p8_component_add(curr_red, 
				red_step_amount, target_red);
			clamped_rgb15_f24p8_component_add(curr_green, 
				green_step_amount, target_green);
			clamped_rgb15_f24p8_component_add(curr_blue, 
				blue_step_amount, target_blue);

			OBJ_PAL_RAM[j] = make_rgb15(curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int());
		}

		ASM_COMMENT("Before wait_for_x_frames()");
		GameManager::wait_for_x_frames(num_frames_to_wait_per_iter);
	}


	bios_wait_for_vblank();
	// Just in case the conversion wasn't complete.
	upload_bg_palettes_to_target(BG_PAL_RAM);
	upload_sprite_palettes_to_target(OBJ_PAL_RAM);

}

