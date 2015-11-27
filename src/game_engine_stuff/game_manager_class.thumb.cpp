#include "game_manager_class.hpp"

#include "level_stuff/active_level_manager_class.hpp"
#include "sprite_stuff/sprite_manager_class.hpp"

#include "../gfx/the_block_gfx.h"
#include "../gfx/title_screen.h"

#include "../test_level/test_level.hpp"

#include "../audio/practice_17.h"


//#include <stdlib.h>


int game_manager::test_int_global;

const char game_manager::sram_const_init_str[] = "Save data initialized.";
const u32 game_manager::sram_init_str_size 
	= sizeof(game_manager::sram_const_init_str);

char game_manager::sram_init_str[game_manager::sram_init_str_size];
u8 game_manager::test_sram_arr[game_manager::test_sram_arr_size];

game_mode game_manager::curr_game_mode;


void game_manager::vblank_func()
{
	mmFrame();
	
	key_poll();
	//pause_or_unpause_music();
	
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
			break;
		
		// When changing from one sublevel to another.
		case gm_changing_sublevel:
			break;
		
		// When in a sublevel.
		case gm_in_sublevel:
			gfx_manager::update_block_graphics_in_vram(the_block_gfxTiles);
			copy_oam_mirror_to_oam();
			gfx_manager::copy_bgofs_mirror_to_registers();
			
			active_level_manager
				::copy_sublevel_from_array_2d_helper_to_vram();
			sprite_manager::upload_tiles_of_active_sprites_to_vram();
			break;
		
		default:
			break;
	}
}


void game_manager::title_screen_func()
{
	curr_game_mode = gm_title_screen;
	
	irq_init();
	
	bios_wait_for_vblank();
	
	// Use video Mode 0, use 1D object mapping, enable forced blank, 
	// and display BG 0
	reg_dispcnt |= dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_bg0_on;
	
	//// Use video Mode 0, use 1D object mapping, enable forced blank, 
	//// and display BG 0, BG 1, BG 2, and BG 3
	//reg_dispcnt = dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_bg0_on
	//	| dcnt_bg1_on | dcnt_bg2_on | dcnt_bg3_on | dcnt_obj_on;
	
	// Use screen base block 28 for BG0's Map
	reg_bg0cnt |= bgcnt_sbb(bg0_sbb);
	
	reg_bg1cnt |= bgcnt_sbb(bg1_sbb);
	reg_bg2cnt |= bgcnt_sbb(bg2_sbb);
	reg_bg3cnt |= bgcnt_sbb(bg3_sbb);
	
	
	// Clear bgofs_mirror
	for ( u32 i=0; i<3; ++i )
	{
		gfx_manager::bgofs_mirror[i].curr.x 
			= gfx_manager::bgofs_mirror[i].prev.x = 0;
		gfx_manager::bgofs_mirror[i].curr.y 
			= gfx_manager::bgofs_mirror[i].prev.y = 0;
	}
	
	gfx_manager::copy_bgofs_mirror_to_registers();
	
	
	// Copy the title screen's tiles and tilemap to VRAM
	bios_do_lz77_uncomp_vram( title_screenTiles, bg_tile_vram );
	
	memcpy32( bg_pal_ram, title_screenPal,
		title_screenPalLen / sizeof(u32) );
	
	bios_do_lz77_uncomp_wram( title_screenMap, 
		active_level::bg0_screenblock_mirror );
	
	active_level_manager::copy_sublevel_from_array_2d_helper_to_vram();
	
	// Disable forced blank
	clear_bits( reg_dispcnt, dcnt_blank_mask );
	
	//memcpy8( test_sram_arr, (void *)debug_arr_u32, test_sram_arr_size );
	
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

void game_manager::reinit_the_game()
{
	curr_game_mode = gm_initializing_the_game;
	bios_wait_for_vblank();
	
	fade_out_to_white(15);
	
	
	// Use video Mode 0, use 1D object mapping, enable forced blank,
	// display BG 0 and objects.
	reg_dispcnt |= dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_bg0_on
		| dcnt_obj_on;
	
	//// Use video Mode 0, use 1D object mapping, enable forced blank, 
	//// and display BG 0, BG 1, BG 2, BG 3, and objects
	//reg_dispcnt = dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_bg0_on
	//	| dcnt_bg1_on | dcnt_bg2_on | dcnt_bg3_on | dcnt_obj_on;
	
	// Use screen base block 28 for BG0's Map
	reg_bg0cnt |= bgcnt_sbb(bg0_sbb);
	
	reg_bg1cnt |= bgcnt_sbb(bg1_sbb);
	reg_bg2cnt |= bgcnt_sbb(bg2_sbb);
	reg_bg3cnt |= bgcnt_sbb(bg3_sbb);
	
	//bios_wait_for_vblank();
	
	//for ( u32 i=0; i<screenblock_size; ++i )
	//{
	//	se_ram[bg1_sbb][i] = bt_wood * 4;
	//}
	
	// Copy the sprite palettes to OBJ Palette RAM.
	gfx_manager::upload_default_sprite_palettes_to_obj_pal_ram();
	
	//// Copy the sprite graphics to OBJ Video RAM.
	//gfx_manager::upload_default_sprite_graphics();
	
	// Also, copy the_block_gfxPalLen to BG Palette RAM
	memcpy32( bg_pal_ram, the_block_gfxPal,
		the_block_gfxPalLen / sizeof(u32) );
	
	//bios_wait_for_vblank();
	
	// Finally, copy the_block_gfxTiles to BG VRAM, screenblock 0
	gfx_manager::update_block_graphics_in_vram(the_block_gfxTiles);
	
	//bios_wait_for_vblank();
	sprite_manager::next_oam_index = 0; 
	active_level_manager::load_level(&test_level);
	
	// Also, start playing music when the game is started.
	irqSet( irq_vblank, (u32)mmVBlank );
	irqEnable(irq_vblank);
	
	mmInitDefault( (mm_addr)practice_17_bin, 8 );
	mmStart( MOD_PRACTICE_17, MM_PLAY_LOOP );
	
	mmSetVBlankHandler(reinterpret_cast<void*>(vblank_func));
	
	// An extra bios_wait_for_vblank() so that 
	bios_wait_for_vblank();
	
	fade_out_to_white(1);
	
	// Disable forced blank
	clear_bits( reg_dispcnt, dcnt_blank_mask );
	
	fade_in(15);
	
	bios_wait_for_vblank();
	
	//curr_game_mode = gm_in_sublevel;
}



void game_manager::fade_out_to_black( u32 num_steps, 
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
		
		gfx_manager::bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		gfx_manager::bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		gfx_manager::bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is black, for the entire screen.
		fixed24p8& red_step_amount 
			= gfx_manager::bg_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= gfx_manager::bg_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= gfx_manager::bg_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- gfx_manager::bg_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- gfx_manager::bg_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- gfx_manager::bg_fade_curr_blue_arr[i] ) / (u16)num_steps;
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
		
		gfx_manager::obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		gfx_manager::obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		gfx_manager::obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is black, for the entire screen.
		fixed24p8& red_step_amount 
			= gfx_manager::obj_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= gfx_manager::obj_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= gfx_manager::obj_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- gfx_manager::obj_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- gfx_manager::obj_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- gfx_manager::obj_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Fading iteration
	for ( u32 i=0; i<num_steps; ++i )
	{
		// For each BG palette
		for ( u32 j=0; j<num_colors_in_8_palettes; ++j )
		{
			fixed24p8& curr_red = gfx_manager::bg_fade_curr_red_arr[j];
			fixed24p8& curr_green = gfx_manager::bg_fade_curr_green_arr[j];
			fixed24p8& curr_blue = gfx_manager::bg_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= gfx_manager::bg_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= gfx_manager::bg_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= gfx_manager::bg_fade_blue_step_amount_arr[j];
			
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
			fixed24p8& curr_red = gfx_manager::obj_fade_curr_red_arr[j];
			fixed24p8& curr_green = gfx_manager::obj_fade_curr_green_arr[j];
			fixed24p8& curr_blue = gfx_manager::obj_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= gfx_manager::obj_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= gfx_manager::obj_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= gfx_manager::obj_fade_blue_step_amount_arr[j];
			
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


void game_manager::fade_out_to_white( u32 num_steps, 
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
		
		gfx_manager::bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		gfx_manager::bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		gfx_manager::bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is white, for the entire screen.
		fixed24p8& red_step_amount 
			= gfx_manager::bg_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= gfx_manager::bg_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= gfx_manager::bg_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- gfx_manager::bg_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- gfx_manager::bg_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- gfx_manager::bg_fade_curr_blue_arr[i] ) / (u16)num_steps;
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
		
		gfx_manager::obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		gfx_manager::obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		gfx_manager::obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is white, for the entire screen.
		fixed24p8& red_step_amount 
			= gfx_manager::obj_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= gfx_manager::obj_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= gfx_manager::obj_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- gfx_manager::obj_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- gfx_manager::obj_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- gfx_manager::obj_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Fading iteration
	for ( u32 i=0; i<num_steps; ++i )
	{
		// For each BG palette
		for ( u32 j=0; j<num_colors_in_8_palettes; ++j )
		{
			fixed24p8& curr_red = gfx_manager::bg_fade_curr_red_arr[j];
			fixed24p8& curr_green = gfx_manager::bg_fade_curr_green_arr[j];
			fixed24p8& curr_blue = gfx_manager::bg_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= gfx_manager::bg_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= gfx_manager::bg_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= gfx_manager::bg_fade_blue_step_amount_arr[j];
			
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
			fixed24p8& curr_red = gfx_manager::obj_fade_curr_red_arr[j];
			fixed24p8& curr_green = gfx_manager::obj_fade_curr_green_arr[j];
			fixed24p8& curr_blue = gfx_manager::obj_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= gfx_manager::obj_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= gfx_manager::obj_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= gfx_manager::obj_fade_blue_step_amount_arr[j];
			
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
		
		wait_for_x_frames(num_frames_to_wait_per_iter);
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


void game_manager::fade_in( u32 num_steps, 
	u32 num_frames_to_wait_per_iter )
{
	// A function like this should eventually be created for background
	// palettes.
	gfx_manager::upload_default_sprite_palettes_to_obj_pal_mirror();
	
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
		
		gfx_manager::bg_fade_curr_red_arr[i] = make_f24p8(red_orig);
		gfx_manager::bg_fade_curr_green_arr[i] = make_f24p8(green_orig);
		gfx_manager::bg_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is white, for the entire screen.
		fixed24p8& red_step_amount 
			= gfx_manager::bg_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= gfx_manager::bg_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= gfx_manager::bg_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- gfx_manager::bg_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- gfx_manager::bg_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- gfx_manager::bg_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Build the OBJ arrays of step amounts
	for ( u32 i=0; i<num_colors_in_8_palettes; ++i )
	{
		s32 red_orig = rgb15_get_red_component(obj_pal_ram[i]);
		s32 green_orig = rgb15_get_green_component(obj_pal_ram[i]);
		s32 blue_orig = rgb15_get_blue_component(obj_pal_ram[i]);
		
		s32 target_red = rgb15_get_red_component
			(gfx_manager::obj_pal_mirror[i]);
		s32 target_green = rgb15_get_green_component
			(gfx_manager::obj_pal_mirror[i]);
		s32 target_blue = rgb15_get_blue_component
			(gfx_manager::obj_pal_mirror[i]);
		
		gfx_manager::obj_fade_curr_red_arr[i] = make_f24p8(red_orig);
		gfx_manager::obj_fade_curr_green_arr[i] = make_f24p8(green_orig);
		gfx_manager::obj_fade_curr_blue_arr[i] = make_f24p8(blue_orig);
		
		// The target color is white, for the entire screen.
		fixed24p8& red_step_amount 
			= gfx_manager::obj_fade_red_step_amount_arr[i];
		fixed24p8& green_step_amount 
			= gfx_manager::obj_fade_green_step_amount_arr[i];
		fixed24p8& blue_step_amount 
			= gfx_manager::obj_fade_blue_step_amount_arr[i];
		
		red_step_amount = ( make_f24p8(target_red) 
			- gfx_manager::obj_fade_curr_red_arr[i] ) / (u16)num_steps;
		green_step_amount = ( make_f24p8(target_green)
			- gfx_manager::obj_fade_curr_green_arr[i] ) / (u16)num_steps;
		blue_step_amount = ( make_f24p8(target_green)
			- gfx_manager::obj_fade_curr_blue_arr[i] ) / (u16)num_steps;
	}
	
	// Fading iteration
	for ( u32 i=0; i<num_steps; ++i )
	{
		// For each BG palette
		for ( u32 j=0; j<the_block_gfxPalLen / sizeof(u16); ++j )
		{
			fixed24p8& curr_red = gfx_manager::bg_fade_curr_red_arr[j];
			fixed24p8& curr_green = gfx_manager::bg_fade_curr_green_arr[j];
			fixed24p8& curr_blue = gfx_manager::bg_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= gfx_manager::bg_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= gfx_manager::bg_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= gfx_manager::bg_fade_blue_step_amount_arr[j];
			
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
			fixed24p8& curr_red = gfx_manager::obj_fade_curr_red_arr[j];
			fixed24p8& curr_green = gfx_manager::obj_fade_curr_green_arr[j];
			fixed24p8& curr_blue = gfx_manager::obj_fade_curr_blue_arr[j];
			
			fixed24p8 red_step_amount 
				= gfx_manager::obj_fade_red_step_amount_arr[j];
			fixed24p8 green_step_amount 
				= gfx_manager::obj_fade_green_step_amount_arr[j];
			fixed24p8 blue_step_amount 
				= gfx_manager::obj_fade_blue_step_amount_arr[j];
			
			fixed24p8 target_red = { (s32)rgb15_get_red_component
				(gfx_manager::obj_pal_mirror[j]) << fixed24p8::shift };
			fixed24p8 target_green = { (s32)rgb15_get_green_component
				(gfx_manager::obj_pal_mirror[j]) << fixed24p8::shift };
			fixed24p8 target_blue = { (s32)rgb15_get_blue_component
				(gfx_manager::obj_pal_mirror[j]) << fixed24p8::shift };
			
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
	
	
	bios_wait_for_vblank();
	// Just in case the conversion wasn't complete.
	memcpy32( bg_pal_ram, the_block_gfxPal,
		the_block_gfxPalLen / sizeof(u32) );
	gfx_manager::upload_default_sprite_palettes_to_obj_pal_ram();
	
}



