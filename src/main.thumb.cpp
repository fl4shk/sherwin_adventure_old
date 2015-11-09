#include "gba_specific_stuff/asm_funcs.hpp"

#include "gba_specific_stuff/button_stuff.hpp"
#include "gba_specific_stuff/bg_reg_stuff.hpp"
#include "gba_specific_stuff/oam_entry_classes.hpp"
#include "gba_specific_stuff/interrupt_stuff.hpp"
#include "gba_specific_stuff/bios_function_wrappers.hpp"
#include "gba_specific_stuff/dma_stuff.hpp"
//#include "gba_specific_stuff/sound_reg_stuff.hpp"
#include "gba_specific_stuff/timer_stuff.hpp"


#include "game_engine_stuff/fixed_classes.hpp"
#include "game_engine_stuff/trigonometry_funcs.hpp"
#include "game_engine_stuff/array_2d_helper_class.hpp"
#include "game_engine_stuff/debug_vars.hpp"

#include "game_engine_stuff/level_stuff/active_level_class.hpp"
#include "game_engine_stuff/level_stuff/active_level_manager_class.hpp"
#include "game_engine_stuff/sprite_stuff/sprite_manager_class.hpp"


//#include "game_engine_stuff/sa_list_class_stuff.hpp"


#include "gfx/the_block_gfx.h"
#include "gfx/title_screen.h"

#include "test_level/test_level.hpp"

#include "audio/practice_17.h"


#include <stdlib.h>

#include "maxmod.h"


scr_entry bg0_screenblock_mirror[screenblock_size] __attribute__((_ewram));

int test_int_global;


static const char sram_const_init_str[] = "Save data initialized.";
static constexpr u32 sram_init_str_size = sizeof(sram_const_init_str);
char sram_init_str[sram_init_str_size] __attribute__((_sram));

static constexpr u32 test_sram_arr_size = debug_arr_u32_size * sizeof(u32);
u8 test_sram_arr[test_sram_arr_size] __attribute__((_sram));




array_2d_helper<scr_entry> bg0_screenblock_2d( se_ram[bg0_sbb],
	screenblock_size_2d );
array_2d_helper<scr_entry> bg0_screenblock_mirror_2d 
	( bg0_screenblock_mirror, screenblock_size_2d );


// This function toggles whether music is playing if the select button is
// down this frame but was not down on the previous frame.
inline void pause_or_unpause_music()
{
	if( key_hit(key_select) )
	{
		if ( mmActive() ) { mmPause(); }
		else { mmResume(); }
	}
}

void vblank_func() __attribute__((__noinline__));

void vblank_func()
{
	mmFrame();
	
	key_poll();
	pause_or_unpause_music ();
	
	update_block_graphics_in_vram(the_block_gfxTiles);
	copy_oam_mirror_to_oam();
	copy_bgofs_mirror_to_registers();
	active_level_manager::copy_level_from_array_2d_helper_to_vram
		( bg0_screenblock_2d, bg0_screenblock_mirror_2d );
	
	
	sprite_gfx_manager::upload_sprite_tiles_to_vram
		(sprite_manager::the_player);
	for ( sprite& spr : sprite_manager::the_sprites )
	{
		//if ( spr.the_sprite_type != st_default )
		if ( spr.get_vram_chunk_index() != 0 )
		{
			sprite_gfx_manager::upload_sprite_tiles_to_vram(spr);
		}
		
		//next_debug_u32 = spr.get_vram_chunk_index() 
		//	* sprite_gfx_manager::num_tiles_in_ss_32x32;
		
	}
	
	//next_debug_u32 = sprite_manager::the_player.get_vram_chunk_index()
	//	* sprite_gfx_manager::num_tiles_in_ss_32x32;
	//
	//next_debug_u32 = sprite_manager::the_sprites[0].get_vram_chunk_index()
	//	* sprite_gfx_manager::num_tiles_in_ss_32x32;
}


void title_screen_func() __attribute__((__noinline__));

void title_screen_func()
{
	irq_init();
	
	bios_wait_for_vblank();
	
	
	// Use video Mode 0, use 1D object mapping, enable forced blank, 
	// and display BG 0
	reg_dispcnt |= dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_bg0_on;
	
	// Use screen base block 31 for BG0's Map
	reg_bg0cnt |= bgcnt_sbb(bg0_sbb);
	
	
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
	
	bios_do_lz77_uncomp_wram( title_screenMap, bg0_screenblock_mirror );
	
	active_level_manager::copy_level_from_array_2d_helper_to_vram 
		( bg0_screenblock_2d, bg0_screenblock_mirror_2d );
	
	
	// Disable forced blank
	clear_bits( reg_dispcnt, dcnt_blank_mask );
	
	
	
	memcpy8( test_sram_arr, (void *)debug_arr_u32, test_sram_arr_size );
	
	//mmSetVBlankHandler((void*)(&vblank_func));
	
	for (;;)
	{
		bios_wait_for_vblank();
		
		key_poll();
		
		// Start the game if the Start button is hit
		if ( key_hit(key_start) )
		{
			
			break;
		}
		
	}
}

extern "C" int ewram_test_func();


inline void debug_infin_loop()
{
	for (;;)
	{
		bios_wait_for_vblank();
		vblank_func();
	}
}


int main()
{
	memcpy8( sram_init_str, sram_const_init_str, sram_init_str_size );
	
	irq_init();
	
	// 
	title_screen_func();
	
	
	// Use video Mode 0, use 1D object mapping, enable forced blank, 
	// display objects, and display BG 0
	reg_dispcnt |= dcnt_mode0 | dcnt_obj_1d | dcnt_blank_on | dcnt_obj_on
		| dcnt_bg0_on;
	
	
	// Use screen base block 31 for BG0's Map
	reg_bg0cnt |= bgcnt_sbb(bg0_sbb);
	
	
	// Copy the sprite palettes to OBJ Palette RAM.
	sprite_gfx_manager::upload_default_sprite_palettes();
	
	//// Copy the sprite graphics to OBJ Video RAM.
	//sprite_gfx_manager::upload_default_sprite_graphics();
	
	
	// Also, copy the_block_gfxPalLen to BG Palette RAM
	memcpy32( bg_pal_ram, the_block_gfxPal,
		the_block_gfxPalLen / sizeof(u32) );
	
	
	// Finally, copy the_block_gfxTiles to BG VRAM, screenblock 0
	update_block_graphics_in_vram(the_block_gfxTiles);
	
	
	//// Initialize the list of sprite level data.
	//active_level_manager::init_horiz_level_sprite_ipg_lists
	//	( sublevel_pointer(test_level) );
	//
	//bios_do_lz77_uncomp_wram( test_level.cmp_block_data,
	//	active_level::block_data_array );
	//
	//active_level_manager::update_level_in_screenblock_mirror_2d 
	//	( bg0_screenblock_mirror_2d, test_level.get_size_2d() );
	//active_level_manager::copy_level_from_array_2d_helper_to_vram 
	//	( bg0_screenblock_2d, bg0_screenblock_mirror_2d );
	
	active_level_manager::initial_level_loading
		( sublevel_pointer(test_level), bg0_screenblock_2d, 
		bg0_screenblock_mirror_2d );
	
	
	int next_oam_index; 
	
	
	sprite_manager::init_the_array_of_active_sprites();
	
	sprite_manager::initial_sprite_spawning_from_level_data
		( test_level.get_size_2d(), bgofs_mirror[0].curr, next_oam_index );
	
	
	active_level_manager::update_level_in_screenblock_mirror_2d 
		( bg0_screenblock_mirror_2d, test_level.get_size_2d() );
	
	
	// Also, start playing music when the game is started.
	mmInitDefault( (mm_addr)practice_17_bin, 8 );
	mmStart( MOD_PRACTICE_17, MM_PLAY_LOOP );
	
	mmPause();
	
	vblank_func();
	
	// Disable forced blank
	clear_bits( reg_dispcnt, dcnt_blank_mask );
	
	bios_wait_for_vblank();
	vblank_func(); 
	
	
	for (;;)
	{
		back_up_bgofs_mirror();
		
		sprite& the_player = sprite_manager::the_player;
		
		clear_debug_vars();
		
		clear_debug_vars();
		for ( sprite& spr : sprite_manager::the_sprites)
		{
			next_debug_u32 = spr.get_vram_chunk_index();
			//next_debug_u32 = spr.the_sprite_type == st_waffle;
		}
		
		memfill32( oam_mirror, 0, sizeof(oam_mirror) / sizeof(u32) );
		
		// Key polling is done in vblank_func()
		//key_poll();
		
		
		if ( soft_reset_keys_down() )
		{
			// Reset the game if A, B, Start, and Select are pressed
			bios_do_hard_reset();
			//bios_do_soft_reset();
		}
		
		
		// Despawn sprites that are too far offscreen.
		sprite_manager::despawn_sprites_if_needed(bgofs_mirror[0]);
		
		sprite_manager::update_all_sprites( test_level.get_size_2d(), 
			bgofs_mirror[0], next_oam_index );
		
		
		// This is temporary
		if ( key_held(key_l) )
		{
			sprite_manager::spawn_a_sprite_basic( st_waffle,
				the_player.in_level_pos, bgofs_mirror[0].curr,
				(bool)the_player.the_oam_entry.get_hflip_status() );
		}
		
		
		sprite_manager::spawn_sprites_if_needed(bgofs_mirror[0]);
		
		
		active_level_manager::update_level_in_screenblock_mirror_2d
			( bg0_screenblock_mirror_2d, test_level.get_size_2d() );
		
		
		bios_wait_for_vblank();
		
		vblank_func();
		
	}
	
	
	return 0;
}



