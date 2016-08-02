// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


//#include "sprite_gfx_stuff.hpp"
#include "gfx_manager_class.hpp"

#include "game_manager_class.hpp"


#include "../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../gba_specific_stuff/oam_entry_defines.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "misc_bitwise_funcs.hpp"
#include "debug_vars.hpp"

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

bg_point gfx_manager::prev_prev_bgofs_mirror[bgofs_mirror_size];
prev_curr_pair<bg_point> gfx_manager::bgofs_mirror[bgofs_mirror_size];

// Current component arrays, stored in EWRAM as fixed24p8's for speed and
// accuracy reasons.
fixed24p8 gfx_manager::bg_fade_curr_red_arr
	[bg_fade_curr_component_arr_size],
gfx_manager::bg_fade_curr_green_arr
	[bg_fade_curr_component_arr_size],
gfx_manager::bg_fade_curr_blue_arr
	[bg_fade_curr_component_arr_size];

fixed24p8 gfx_manager::obj_fade_curr_red_arr
	[obj_fade_curr_component_arr_size],
gfx_manager::obj_fade_curr_green_arr
	[obj_fade_curr_component_arr_size],
gfx_manager::obj_fade_curr_blue_arr
	[obj_fade_curr_component_arr_size];


// Fade out/in step amounts.
fixed24p8 gfx_manager::bg_fade_red_step_amount_arr
	[bg_fade_step_amount_arr_size],
gfx_manager::bg_fade_green_step_amount_arr
	[bg_fade_step_amount_arr_size],
gfx_manager::bg_fade_blue_step_amount_arr
	[bg_fade_step_amount_arr_size];

fixed24p8 gfx_manager::obj_fade_red_step_amount_arr
	[obj_fade_step_amount_arr_size],
gfx_manager::obj_fade_green_step_amount_arr
	[obj_fade_step_amount_arr_size],
gfx_manager::obj_fade_blue_step_amount_arr
	[obj_fade_step_amount_arr_size];


// BG palette stuff
u16 gfx_manager::bg_pal_mirror[bg_pal_ram_size_in_u16];

// Sprite palette stuff
u16 gfx_manager::obj_pal_mirror[obj_pal_ram_size_in_u16];

// HUD stuff
u32 gfx_manager::hud_vram_as_tiles_start_offset;


void gfx_manager::copy_bgofs_mirror_to_registers()
{
	//reg_bgofs[0] = bgofs_mirror[0].curr;
	//reg_bgofs[1] = bgofs_mirror[1].curr;
	//reg_bgofs[2] = bgofs_mirror[2].curr;
	//reg_bgofs[3] = bgofs_mirror[3].curr;
	
	for ( u32 i=0; i<4; ++i )
	{
		reg_bgofs[i].x = (s16)bgofs_mirror[i].curr.x.to_int_for_on_screen();
		reg_bgofs[i].y = (s16)bgofs_mirror[i].curr.y.to_int_for_on_screen();
		
		//reg_bgofs[i].x = ( (s32)bgofs_mirror[i].curr.x
		//	.to_int_for_on_screen() ) & 0xffff;
		//reg_bgofs[i].y = ( (s32)bgofs_mirror[i].curr.y
		//	.to_int_for_on_screen() ) & 0xffff;
		
		//reg_bgofs[i].x = (s16)bgofs_mirror[i].curr.x.floor_to_int();
		//reg_bgofs[i].y = (s16)bgofs_mirror[i].curr.y.floor_to_int();
		
		//reg_bgofs[i].x = bgofs_mirror[i].curr.x.floor_to_int() & 0xffff;
		//reg_bgofs[i].y = bgofs_mirror[i].curr.y.floor_to_int() & 0xffff;
	}
}


void gfx_manager::upload_bg_palettes_to_target( vu16* target )
{
	if ( game_manager::curr_game_mode == gm_title_screen )
	{
		memcpy32( target, title_screenPal,
			title_screenPalLen / sizeof(u32) );
	}
	else //if ( game_manager::curr_game_mode >= gm_initializing_the_game
		//&& game_manager::curr_game_mode <= gm_in_sublevel )
	{
		memcpy32( &(target[bgps_in_level_block_0 
			* num_colors_per_palette]), 
			the_block_gfxPal,
			the_block_gfxPalLen / sizeof(u32) );
		//memcpy32( &(target[bgps_in_level_hud 
		//	* num_colors_per_palette]), 
		//	text_8x16_gfxPal,
		//	text_8x16_gfxPalLen / sizeof(u32) );
		memcpy32( &(target[bgps_in_level_hud 
			* num_colors_per_palette]),
			text_8x8_thick_gfxPal,
			text_8x8_thick_gfxPalLen / sizeof(u32) );
	}
}


void gfx_manager::copy_bg_pal_mirror_to_bg_pal_ram()
{
	memcpy32( bg_pal_ram, bg_pal_mirror, bg_pal_ram_size 
		/ sizeof(u32) );
}


//void gfx_manager::update_block_graphics_in_vram
//	( const unsigned short* the_tiles )
void gfx_manager::upload_bg_tiles_to_vram()
{
	
	// Note:  this function currently does multiple VRAM graphics updates
	// whenever multiple block_types share the same graphics_slot.  An
	// example of this is how each variation of bt_eyes shares the same
	// graphics slot.
	for ( u32 i=0; i<block_type::bt_count; ++i )
	{
		u32 graphics_slot = get_graphics_slot_of_block_type 
			( (block_type)i );
		u32 metatile_number = get_metatile_number_of_block_type
			( (block_type)i );
		
		//dma3_cpy( &( bg_tile_vram[graphics_slot * 16]), 
		//	&( the_tiles 
		//		[metatile_number * 16 * 4] ),
		//	16 * 4, 0 );
		
		//memcpy32( &(bg_tile_vram[graphics_slot * 16]),
		//	&(the_tiles[metatile_number * 16 * 4]),
		//	16 * 4 / sizeof(u16) );
		
		memcpy32( &(bg_tile_vram_as_tiles[graphics_slot]),
			
			&((reinterpret_cast<const tile*>(the_block_gfxTiles))
			[metatile_number * num_tiles_in_ss_16x16]),
			
			sizeof(tile) * num_tiles_in_ss_16x16 / sizeof (u32) );
	}
	
	//memcpy32( &(bg_tile_vram_as_tiles[hud_vram_as_tiles_start_offset]),
	//	text_8x16_gfxTiles, 
	//	text_8x16_gfxTilesLen / sizeof(u32) );
	memcpy32( &(bg_tile_vram_as_tiles[hud_vram_as_tiles_start_offset]),
		text_8x8_thick_gfxTiles,
		text_8x8_thick_gfxTilesLen / sizeof(u32) );
}


void gfx_manager::upload_sprite_palettes_to_target( vu16* target )
{
	//memcpy32( target, the_spritesPal, 
	//	the_spritesPalLen / sizeof(u32) );
	
	//static constexpr u32 num_colors_per_palette = 16;
	
	// The player's palettes
	memcpy32( &(target[sps_player * num_colors_per_palette]), 
		sherwin_gfxPal, sherwin_gfxPalLen / sizeof(u32) );
	
	// The powerups' palettes
	memcpy32( &(target[sps_powerup * num_colors_per_palette]), 
		the_powerup_gfxPal, the_powerup_gfxPalLen / sizeof(u32) );
	
	//// The block-like sprites' palettes
	//memcpy32( &(target[sps_block_like_0 * num_colors_per_palette]),
	//	the_block_like_sprites_gfxPal, the_block_like_sprites_gfxPalLen 
	//	/ sizeof(u32) );
	
	// The door sprites' palettes
	memcpy32( &(target[sps_door * num_colors_per_palette]), 
		the_door_gfxPal, the_door_gfxPalLen / sizeof(u32) );
	
	// The golems and other enemies' palettes
	memcpy32( &(target[sps_enemy_0 * num_colors_per_palette]),
		the_golem_enemy_gfxPal, the_golem_enemy_gfxPalLen / sizeof(u32) );
	
	// The secondary sprites' palettes
	memcpy32( &(target[sps_secondary_0 * num_colors_per_palette]),
		the_16x16_secondary_sprites_gfxPal,
		the_16x16_secondary_sprites_gfxPalLen / sizeof(u32) );
}

void gfx_manager::copy_obj_pal_mirror_to_obj_pal_ram()
{
	memcpy32( obj_pal_ram, obj_pal_mirror, obj_pal_ram_size 
		/ sizeof(u32) );
}


void gfx_manager::upload_sprite_tiles_to_vram( sprite& the_sprite )
{
	// It gets tiring to have to type
	// sprite_stuff_array[the_sprite.the_sprite_type] so much.
	//sprite_base_stuff* sbs_ptr = sprite_stuff_array
	//	[the_sprite.the_sprite_type];
	
	//// This memfill32() call isn't strictly necessary, but it makes VRAM
	//// look nicer in the VRAM viewer functionality of some emulators.
	//memfill32( &(((tile*)obj_tile_vram)[the_sprite.get_vram_chunk_index()
	//	* num_tiles_in_ss_32x32]), 0, sizeof(tile) * num_tiles_in_ss_32x32
	//	/ sizeof(u32) );
	
	
	memcpy32( &(((tile*)obj_tile_vram)[the_sprite.get_vram_chunk_index()
			* num_tiles_in_ss_32x32]),
		
		&(the_sprite.get_tile_arr()
			[the_sprite.get_curr_relative_tile_slot()]),
		
		//sizeof(tile) * num_tiles_in_ss_32x32 / sizeof(u32) );
		sizeof(tile) * the_sprite.get_num_active_gfx_tiles() 
		/ sizeof(u32) );
}


void gfx_manager::fade_out_to_black( u32 num_steps, 
	u32 num_frames_to_wait_per_iter )
{
	// Build the BG arrays of step amounts
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		s32 red_orig = rgb15_get_red_component(bg_pal_ram[i]);
		s32 green_orig = rgb15_get_green_component(bg_pal_ram[i]);
		s32 blue_orig = rgb15_get_blue_component(bg_pal_ram[i]);
		
		s32 target_red = 0;
		s32 target_green = 0;
		s32 target_blue = 0;
		
		bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is black, for the entire screen.
		fixed24p8& red_step_amount 
			= bg_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= bg_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= bg_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- bg_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- bg_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- bg_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Build the OBJ arrays of step amounts
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		s32 red_orig = rgb15_get_red_component(obj_pal_ram[i]);
		s32 green_orig = rgb15_get_green_component(obj_pal_ram[i]);
		s32 blue_orig = rgb15_get_blue_component(obj_pal_ram[i]);
		
		s32 target_red = 0;
		s32 target_green = 0;
		s32 target_blue = 0;
		
		obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is black, for the entire screen.
		fixed24p8& red_step_amount 
			= obj_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= obj_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= obj_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- obj_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- obj_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- obj_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Fading iteration
	for ( u32 i=0; i<num_steps; ++i )
	{
		// For each BG palette
		for ( u32 j=0; j<num_colors_in_8_palettes; ++j )
		{
			fixed24p8& curr_red = bg_fade_curr_red_arr[j];
			fixed24p8& curr_green = bg_fade_curr_green_arr[j];
			fixed24p8& curr_blue = bg_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= bg_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= bg_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= bg_fade_blue_step_amount_arr[j];
			
			clamped_rgb15_f24p8_component_add( curr_red, 
				red_step_amount, (fixed24p8){0} );
			clamped_rgb15_f24p8_component_add( curr_green, 
				green_step_amount, (fixed24p8){0} );
			clamped_rgb15_f24p8_component_add( curr_blue, 
				blue_step_amount, (fixed24p8){0} );
			
			bg_pal_ram[j] = make_rgb15( curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int() );
		}
		
		// For each OBJ palette
		for ( u32 j=0; j<num_colors_in_8_palettes; ++j )
		{
			fixed24p8& curr_red = obj_fade_curr_red_arr[j];
			fixed24p8& curr_green = obj_fade_curr_green_arr[j];
			fixed24p8& curr_blue = obj_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= obj_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= obj_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= obj_fade_blue_step_amount_arr[j];
			
			clamped_rgb15_f24p8_component_add( curr_red, 
				red_step_amount, (fixed24p8){0} );
			clamped_rgb15_f24p8_component_add( curr_green, 
				green_step_amount, (fixed24p8){0} );
			clamped_rgb15_f24p8_component_add( curr_blue, 
				blue_step_amount, (fixed24p8){0} );
			
			obj_pal_ram[j] = make_rgb15( curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int() );
		}
		
		game_manager::wait_for_x_frames(num_frames_to_wait_per_iter);
	}
	
	
	// Just in case the conversion wasn't complete
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		bg_pal_ram[i] = 0;
	}
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		obj_pal_ram[i] = 0;
	}
}


void gfx_manager::fade_out_to_white( u32 num_steps, 
	u32 num_frames_to_wait_per_iter )
{
	// Build the BG arrays of step amounts
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		s32 red_orig = rgb15_get_red_component(bg_pal_ram[i]);
		s32 green_orig = rgb15_get_green_component(bg_pal_ram[i]);
		s32 blue_orig = rgb15_get_blue_component(bg_pal_ram[i]);
		
		s32 target_red = rgb15_component_max_val;
		s32 target_green = rgb15_component_max_val;
		s32 target_blue = rgb15_component_max_val;
		
		bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is white, for the entire screen.
		fixed24p8& red_step_amount 
			= bg_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= bg_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= bg_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- bg_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- bg_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- bg_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Build the OBJ arrays of step amounts
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		s32 red_orig = rgb15_get_red_component(obj_pal_ram[i]);
		s32 green_orig = rgb15_get_green_component(obj_pal_ram[i]);
		s32 blue_orig = rgb15_get_blue_component(obj_pal_ram[i]);
		
		s32 target_red = rgb15_component_max_val;
		s32 target_green = rgb15_component_max_val;
		s32 target_blue = rgb15_component_max_val;
		
		obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is white, for the entire screen.
		fixed24p8& red_step_amount 
			= obj_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= obj_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= obj_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- obj_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- obj_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- obj_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Fading iteration
	for ( u32 i=0; i<num_steps; ++i )
	{
		// For each BG palette
		for ( u32 j=0; j<num_colors_in_8_palettes; ++j )
		{
			fixed24p8& curr_red = bg_fade_curr_red_arr[j];
			fixed24p8& curr_green = bg_fade_curr_green_arr[j];
			fixed24p8& curr_blue = bg_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= bg_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= bg_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= bg_fade_blue_step_amount_arr[j];
			
			clamped_rgb15_f24p8_component_add( curr_red, 
				red_step_amount, (fixed24p8){ rgb15_component_max_val 
				<< fixed24p8::shift } );
			clamped_rgb15_f24p8_component_add( curr_green, 
				green_step_amount, (fixed24p8){ rgb15_component_max_val
				<< fixed24p8::shift } );
			clamped_rgb15_f24p8_component_add( curr_blue, 
				blue_step_amount, (fixed24p8){ rgb15_component_max_val
				<< fixed24p8::shift } );
			
			bg_pal_ram[j] = make_rgb15( curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int() );
		}
		
		// For each OBJ palette
		for ( u32 j=0; j<num_colors_in_8_palettes; ++j )
		{
			fixed24p8& curr_red = obj_fade_curr_red_arr[j];
			fixed24p8& curr_green = obj_fade_curr_green_arr[j];
			fixed24p8& curr_blue = obj_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= obj_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= obj_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= obj_fade_blue_step_amount_arr[j];
			
			clamped_rgb15_f24p8_component_add( curr_red, 
				red_step_amount, (fixed24p8){ rgb15_component_max_val
				<< fixed24p8::shift } );
			clamped_rgb15_f24p8_component_add( curr_green, 
				green_step_amount, (fixed24p8){ rgb15_component_max_val
				<< fixed24p8::shift } );
			clamped_rgb15_f24p8_component_add( curr_blue, 
				blue_step_amount, (fixed24p8){ rgb15_component_max_val
				<< fixed24p8::shift } );
			
			obj_pal_ram[j] = make_rgb15( curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int() );
		}
		
		game_manager::wait_for_x_frames(num_frames_to_wait_per_iter);
	}
	
	
	bios_wait_for_vblank();
	// Just in case the conversion wasn't complete
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		//bg_pal_ram[i] = make_rgb15( rgb15_component_max_val,
		//	rgb15_component_max_val, rgb15_component_max_val );
		bg_pal_ram[i] = 0x7fff;
	}
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		//obj_pal_ram[i] = make_rgb15( rgb15_component_max_val,
		//	rgb15_component_max_val, rgb15_component_max_val );
		obj_pal_ram[i] = 0x7fff;
	}
}


void gfx_manager::fade_in( u32 num_steps, u32 num_frames_to_wait_per_iter )
{
	upload_bg_palettes_to_target(bg_pal_mirror);
	upload_sprite_palettes_to_target(obj_pal_mirror);
	
	bios_wait_for_vblank();
	
	// Build the BG arrays of step amounts
	//for ( u32 i=0; i<the_block_gfxPalLen / sizeof(u16); ++i )
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		s32 red_orig = rgb15_get_red_component(bg_pal_ram[i]);
		s32 green_orig = rgb15_get_green_component(bg_pal_ram[i]);
		s32 blue_orig = rgb15_get_blue_component(bg_pal_ram[i]);
		
		//s32 target_red = rgb15_get_red_component(the_block_gfxPal[i]);
		//s32 target_green = rgb15_get_green_component(the_block_gfxPal[i]);
		//s32 target_blue = rgb15_get_blue_component(the_block_gfxPal[i]);
		
		s32 target_red = rgb15_get_red_component(bg_pal_mirror[i]);
		s32 target_green = rgb15_get_green_component(bg_pal_mirror[i]);
		s32 target_blue = rgb15_get_blue_component(bg_pal_mirror[i]);
		
		bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is white, for the entire screen.
		fixed24p8& red_step_amount 
			= bg_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= bg_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= bg_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- bg_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- bg_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- bg_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Build the OBJ arrays of step amounts
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		s32 red_orig = rgb15_get_red_component(obj_pal_ram[i]);
		s32 green_orig = rgb15_get_green_component(obj_pal_ram[i]);
		s32 blue_orig = rgb15_get_blue_component(obj_pal_ram[i]);
		
		s32 target_red = rgb15_get_red_component(obj_pal_mirror[i]);
		s32 target_green = rgb15_get_green_component(obj_pal_mirror[i]);
		s32 target_blue = rgb15_get_blue_component(obj_pal_mirror[i]);
		
		obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is white, for the entire screen.
		fixed24p8& red_step_amount 
			= obj_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= obj_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= obj_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- obj_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- obj_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- obj_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Fading iteration
	for ( u32 i=0; i<num_steps; ++i )
	{
		// For each BG palette
		//for ( u32 j=0; j<the_block_gfxPalLen / sizeof(u16); ++j )
		for ( u32 j=0; j<num_colors_in_8_palettes; ++j )
		{
			fixed24p8& curr_red = bg_fade_curr_red_arr[j];
			fixed24p8& curr_green = bg_fade_curr_green_arr[j];
			fixed24p8& curr_blue = bg_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= bg_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= bg_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= bg_fade_blue_step_amount_arr[j];
			
			// Don't need make_f24p8() for these because color component
			// values are guaranteed to be positive.
			//fixed24p8 target_red = { (s32)rgb15_get_red_component
			//	(the_block_gfxPal[j]) << fixed24p8::shift };
			//fixed24p8 target_green = { (s32)rgb15_get_green_component
			//	(the_block_gfxPal[j]) << fixed24p8::shift };
			//fixed24p8 target_blue = { (s32)rgb15_get_blue_component
			//	(the_block_gfxPal[j]) << fixed24p8::shift };
			
			fixed24p8 target_red = { (s32)rgb15_get_red_component
				(bg_pal_mirror[j]) << fixed24p8::shift };
			fixed24p8 target_green = { (s32)rgb15_get_green_component
				(bg_pal_mirror[j]) << fixed24p8::shift };
			fixed24p8 target_blue = { (s32)rgb15_get_blue_component
				(bg_pal_mirror[j]) << fixed24p8::shift };
			
			clamped_rgb15_f24p8_component_add( curr_red, 
				red_step_amount, target_red );
			clamped_rgb15_f24p8_component_add( curr_green, 
				green_step_amount, target_green );
			clamped_rgb15_f24p8_component_add( curr_blue, 
				blue_step_amount, target_blue );
			
			bg_pal_ram[j] = make_rgb15( curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int() );
		}
		
		// For each OBJ palette
		for ( u32 j=0; j<num_colors_in_8_palettes; ++j )
		{
			fixed24p8& curr_red = obj_fade_curr_red_arr[j];
			fixed24p8& curr_green = obj_fade_curr_green_arr[j];
			fixed24p8& curr_blue = obj_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= obj_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= obj_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= obj_fade_blue_step_amount_arr[j];
			
			fixed24p8 target_red = { (s32)rgb15_get_red_component
				(obj_pal_mirror[j]) << fixed24p8::shift };
			fixed24p8 target_green = { (s32)rgb15_get_green_component
				(obj_pal_mirror[j]) << fixed24p8::shift };
			fixed24p8 target_blue = { (s32)rgb15_get_blue_component
				(obj_pal_mirror[j]) << fixed24p8::shift };
			
			clamped_rgb15_f24p8_component_add( curr_red, 
				red_step_amount, target_red );
			clamped_rgb15_f24p8_component_add( curr_green, 
				green_step_amount, target_green );
			clamped_rgb15_f24p8_component_add( curr_blue, 
				blue_step_amount, target_blue );
			
			obj_pal_ram[j] = make_rgb15( curr_red.round_to_int(),
				curr_green.round_to_int(),
				curr_blue.round_to_int() );
		}
		
		game_manager::wait_for_x_frames(num_frames_to_wait_per_iter);
	}
	
	
	bios_wait_for_vblank();
	// Just in case the conversion wasn't complete.
	upload_bg_palettes_to_target(bg_pal_ram);
	upload_sprite_palettes_to_target(obj_pal_ram);
	
}

