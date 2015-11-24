#include "gba_specific_stuff/asm_funcs.hpp"

#include "gba_specific_stuff/button_stuff.hpp"
#include "gba_specific_stuff/gfx_reg_stuff.hpp"
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


#include "game_engine_stuff/housekeeping.hpp"



extern "C" int ewram_test_func();


int main()
{
	memcpy8( sram_init_str, sram_const_init_str, sram_init_str_size );
	
	irq_init();
	
	// 
	title_screen_func();
	
	//reinit_the_game();
	
	for (;;)
	{
		back_up_bgofs_mirror();
		
		sprite& the_player = sprite_manager::the_player;
		
		clear_debug_vars();
		
		memfill32( oam_mirror, 0, sizeof(oam_mirror) / sizeof(u32) );
		
		// Key polling is done in vblank_func()
		//key_poll();
		
		
		if ( soft_reset_keys_down() )
		{
			// Reset the game if A, B, Start, and Select are pressed
			//bios_do_hard_reset();
			////bios_do_soft_reset();
			reinit_the_game();
		}
		
		
		// Despawn sprites that are too far offscreen.
		sprite_manager::despawn_sprites_if_needed(bgofs_mirror[0]);
		
		sprite_manager::update_all_sprites
			( active_level::get_the_current_sublevel_ptr().get_size_2d(), 
			bgofs_mirror[0] );
		
		
		//// This is temporary
		//if ( key_held(key_l) )
		//{
		//	sprite_manager::spawn_a_sprite_basic( st_waffle,
		//		the_player.in_level_pos, bgofs_mirror[0].curr,
		//		(bool)the_player.the_oam_entry.get_hflip_status() );
		//}
		
		//if ( key_hit(key_select) )
		//{
		//	fade_out_to_black(1);
		//	
		//	wait_for_x_frames(60);
		//	
		//	fade_in_from_black(1);
		//}
		
		sprite_manager::spawn_sprites_if_needed(bgofs_mirror[0]);
		
		
		//active_level_manager::update_sublevel_in_screenblock_mirror_2d
		//	( active_level::bg0_screenblock_mirror_2d, 
		//	test_level.get_size_2d() );
		active_level_manager::update_sublevel_in_screenblock_mirror_2d();
		
		
		
		bios_wait_for_vblank();
		
		vblank_func();
		
	}
	
	
	return 0;
}



