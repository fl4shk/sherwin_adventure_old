#include "housekeeping.hpp"

#include "level_stuff/active_level_manager_class.hpp"
#include "sprite_stuff/sprite_manager_class.hpp"

#include "../gfx/the_block_gfx.h"
#include "../gfx/title_screen.h"

#include "../test_level/test_level.hpp"

#include "../audio/practice_17.h"


//#include <stdlib.h>

int test_int_global;

//static const char sram_const_init_str[] = "Save data initialized.";
//static constexpr u32 sram_init_str_size = sizeof(sram_const_init_str);
char sram_init_str[sram_init_str_size];

//static constexpr u32 test_sram_arr_size = debug_arr_u32_size * sizeof(u32);
u8 test_sram_arr[test_sram_arr_size];

void maxmod_vblank_updater_func()
{
	mmFrame();
}


void vblank_func()
{
	key_poll();
	//pause_or_unpause_music();
	
	update_block_graphics_in_vram(the_block_gfxTiles);
	copy_oam_mirror_to_oam();
	copy_bgofs_mirror_to_registers();
	
	//active_level_manager::copy_level_from_array_2d_helper_to_vram
	//	( active_level::bg0_screenblock_2d, 
	//	active_level::bg0_screenblock_mirror_2d );
	
	active_level_manager::copy_sublevel_from_array_2d_helper_to_vram();
	
	sprite_manager::upload_tiles_of_active_sprites_to_vram();
	
}


void title_screen_func()
{
	irq_init();
	
	bios_wait_for_vblank();
	
	//// Use video Mode 0, use 1D object mapping, enable forced blank, 
	//// and display BG 0
	//reg_dispcnt |= dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_bg0_on;
	
	// Use video Mode 0, use 1D object mapping, enable forced blank, 
	// and display BG 0, BG 1, BG 2, and BG 3
	reg_dispcnt = dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_bg0_on
		| dcnt_bg1_on | dcnt_bg2_on | dcnt_bg3_on | dcnt_obj_on;
	
	// Use screen base block 28 for BG0's Map
	reg_bg0cnt |= bgcnt_sbb(bg0_sbb);
	
	reg_bg1cnt |= bgcnt_sbb(bg1_sbb);
	reg_bg2cnt |= bgcnt_sbb(bg2_sbb);
	reg_bg3cnt |= bgcnt_sbb(bg3_sbb);
	
	
	// Clear bgofs_mirror
	for ( u32 i=0; i<3; ++i )
	{
		bgofs_mirror[i].curr.x = bgofs_mirror[i].prev.x = 0;
		bgofs_mirror[i].curr.y = bgofs_mirror[i].prev.y = 0;
	}
	
	copy_bgofs_mirror_to_registers();
	
	
	// Copy the title screen's tiles and tilemap to VRAM
	bios_do_lz77_uncomp_vram( title_screenTiles, bg_tile_vram );
	
	memcpy32( bg_pal_ram, title_screenPal,
		title_screenPalLen / sizeof(u32) );
	
	bios_do_lz77_uncomp_wram( title_screenMap, 
		active_level::bg0_screenblock_mirror );
	
	//active_level_manager::copy_sublevel_from_array_2d_helper_to_vram 
	//	( active_level::bg0_screenblock_2d, 
	//	active_level::bg0_screenblock_mirror_2d );
	active_level_manager::copy_sublevel_from_array_2d_helper_to_vram();
	
	// Disable forced blank
	clear_bits( reg_dispcnt, dcnt_blank_mask );
	
	
	//memcpy8( test_sram_arr, (void *)debug_arr_u32, test_sram_arr_size );
	
	//mmSetVBlankHandler((void*)(&vblank_func));
	
	for (;;)
	{
		bios_wait_for_vblank();
		
		key_poll();
		
		// Start the game if the Start button is hit
		if ( key_hit(key_start) )
		{
			reinit_the_game();
			break;
		}
		
	}
}

void reinit_the_game()
{
	//// Use video Mode 0, use 1D object mapping, enable forced blank, 
	//// display objects, and display BG 0
	//reg_dispcnt = dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_obj_on
	//	| dcnt_bg0_on;
	//
	//
	//// Use screen base block 31 for BG0's Map
	//reg_bg0cnt |= bgcnt_sbb(bg0_sbb);
	
	
	// Use video Mode 0, use 1D object mapping, enable forced blank, 
	// and display BG 0, BG 1, BG 2, and BG 3
	reg_dispcnt = dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_bg0_on
		| dcnt_bg1_on | dcnt_bg2_on | dcnt_bg3_on | dcnt_obj_on;
	
	// Use screen base block 28 for BG0's Map
	reg_bg0cnt |= bgcnt_sbb(bg0_sbb);
	
	reg_bg1cnt |= bgcnt_sbb(bg1_sbb);
	reg_bg2cnt |= bgcnt_sbb(bg2_sbb);
	reg_bg3cnt |= bgcnt_sbb(bg3_sbb);
	
	//for ( u32 i=0; i<screenblock_size; ++i )
	//{
	//	se_ram[bg1_sbb][i] = bt_wood * 4;
	//}
	
	bios_wait_for_vblank();
	// Copy the sprite palettes to OBJ Palette RAM.
	sprite_gfx_manager::upload_default_sprite_palettes_to_obj_pal_ram();
	
	//// Copy the sprite graphics to OBJ Video RAM.
	//sprite_gfx_manager::upload_default_sprite_graphics();
	
	// Also, copy the_block_gfxPalLen to BG Palette RAM
	memcpy32( bg_pal_ram, the_block_gfxPal,
		the_block_gfxPalLen / sizeof(u32) );
	
	
	// Finally, copy the_block_gfxTiles to BG VRAM, screenblock 0
	update_block_graphics_in_vram(the_block_gfxTiles);
	
	//bios_wait_for_vblank();
	sprite_manager::next_oam_index = 0; 
	active_level_manager::load_level(&test_level);
	
	
	//// Wait for about 0.25 seconds.
	//wait_for_x_frames(15);
	
	
	// Also, start playing music when the game is started.
	
	irqSet( irq_vblank, (u32)mmVBlank );
	irqEnable(irq_vblank);
	
	mmInitDefault( (mm_addr)practice_17_bin, 8 );
	mmStart( MOD_PRACTICE_17, MM_PLAY_LOOP );
	
	mmSetVBlankHandler(reinterpret_cast<void*>
		(maxmod_vblank_updater_func));
	
	//mmSetVBlankHandler((void*)&maxmod_vblank_func);
	
	//mmPause();
	
	// Disable forced blank
	clear_bits( reg_dispcnt, dcnt_blank_mask );
	
	bios_wait_for_vblank();
	vblank_func(); 
}


void fade_out_to_black( u32 num_steps, u32 num_frames_to_wait_per_iter )
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
		fixed24p8& red_step_amount = bg_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount = bg_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount = bg_fade_blue_step_amount_arr[i];
		
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
		fixed24p8& red_step_amount = obj_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount = obj_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount = obj_fade_blue_step_amount_arr[i];
		
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
		
		wait_for_x_frames(num_frames_to_wait_per_iter);
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


void fade_in_from_black( u32 num_steps, u32 num_frames_to_wait_per_iter )
{
	// A function like this should eventually be created for background
	// palettes.
	sprite_gfx_manager::upload_default_sprite_palettes_to_obj_pal_mirror();
	
	bios_wait_for_vblank();
	
	// Build the BG arrays of step amounts
	for ( u32 i=0; i<the_block_gfxPalLen / sizeof(u16); ++i )
	{
		s32 red_orig = rgb15_get_red_component(bg_pal_ram[i]);
		s32 green_orig = rgb15_get_green_component(bg_pal_ram[i]);
		s32 blue_orig = rgb15_get_blue_component(bg_pal_ram[i]);
		
		s32 target_red = rgb15_get_red_component(the_block_gfxPal[i]);
		s32 target_green = rgb15_get_green_component(the_block_gfxPal[i]);
		s32 target_blue = rgb15_get_blue_component(the_block_gfxPal[i]);
		
		bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is black, for the entire screen.
		fixed24p8& red_step_amount = bg_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount = bg_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount = bg_fade_blue_step_amount_arr[i];
		
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
		
		s32 target_red = rgb15_get_red_component
			(sprite_gfx_manager::obj_pal_mirror[i]);
		s32 target_green = rgb15_get_green_component
			(sprite_gfx_manager::obj_pal_mirror[i]);
		s32 target_blue = rgb15_get_blue_component
			(sprite_gfx_manager::obj_pal_mirror[i]);
		
		obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is black, for the entire screen.
		fixed24p8& red_step_amount = obj_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount = obj_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount = obj_fade_blue_step_amount_arr[i];
		
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
		for ( u32 j=0; j<the_block_gfxPalLen / sizeof(u16); ++j )
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
			fixed24p8 target_red = { (s32)rgb15_get_red_component
				(the_block_gfxPal[j]) << fixed24p8::shift };
			fixed24p8 target_green = { (s32)rgb15_get_green_component
				(the_block_gfxPal[j]) << fixed24p8::shift };
			fixed24p8 target_blue = { (s32)rgb15_get_blue_component
				(the_block_gfxPal[j]) << fixed24p8::shift };
			
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
				(sprite_gfx_manager::obj_pal_mirror[j]) 
				<< fixed24p8::shift };
			fixed24p8 target_green = { (s32)rgb15_get_green_component
				(sprite_gfx_manager::obj_pal_mirror[j])
				<< fixed24p8::shift };
			fixed24p8 target_blue = { (s32)rgb15_get_blue_component
				(sprite_gfx_manager::obj_pal_mirror[j])
				<< fixed24p8::shift };
			
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
		
		wait_for_x_frames(num_frames_to_wait_per_iter);
	}
	
	
	
	// Just in case the conversion wasn't complete.
	memcpy32( bg_pal_ram, the_block_gfxPal,
		the_block_gfxPalLen / sizeof(u32) );
	sprite_gfx_manager::upload_default_sprite_palettes_to_obj_pal_ram();
	
}


