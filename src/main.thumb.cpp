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


#include "game_engine_stuff/game_manager_class.hpp"
#include "game_engine_stuff/gfx_manager_class.hpp"


// This is an assembly function.  It doesn't do very much.
extern "C" int ewram_test_func();


int main()
{
	// This will eventually be used to identify whether save data has been
	// created.  As of right now, there is no need for save data, but that
	// will change in the future.  It is likely that 64 kiB of save data
	// will be more than enough.
	memcpy8( game_manager::sram_init_str,
		game_manager::sram_const_init_str, 
		game_manager::sram_init_str_size );
	
	irq_init();
	
	game_manager::title_screen_func();
	
	// This function is called by game_manager::title_screen_func().
	//game_manager::reinit_the_game();
	
	for (;;)
	{
		gfx_manager::back_up_bgofs_mirror();
		
		sprite& the_player = sprite_manager::the_player;
		
		clear_debug_vars();
		
		clear_oam_mirror();
		
		// Key polling is done in game_manager::vblank_func()
		//key_poll();
		
		if ( soft_reset_keys_down() )
		{
			// Reset the game if A, B, Start, and Select are pressed
			//bios_do_hard_reset();
			////bios_do_soft_reset();
			game_manager::reinit_the_game();
		}
		
		
		// Despawn sprites that are too far offscreen.
		sprite_manager::despawn_sprites_if_needed
			(gfx_manager::bgofs_mirror[0]);
		
		sprite_manager::update_all_sprites
			( active_level::get_the_current_sublevel_ptr().get_size_2d(), 
			gfx_manager::bgofs_mirror[0] );
		
		
		//// This is temporary
		//if ( key_held(key_l) )
		//{
		//	sprite_manager::spawn_a_sprite_basic( st_waffle,
		//		the_player.in_level_pos, gfx_manager::bgofs_mirror[0].curr,
		//		(bool)the_player.the_oam_entry.get_hflip_status() );
		//}
		
		//if ( key_hit(key_select) )
		//{
		//	game_manager::fade_out_to_black(1);
		//	
		//	game_manager::wait_for_x_frames(60);
		//	
		//	game_manager::fade_in(1);
		//}
		
		sprite_manager::spawn_sprites_if_needed
			(gfx_manager::bgofs_mirror[0]);
		
		//if ( key_hit(key_l) )
		//{
		//	--player_sprite_stuff::remaining_hp;
		//}
		//if ( key_hit(key_r) )
		//{
		//	++player_sprite_stuff::remaining_hp;
		//}
		//
		
		
		//active_level_manager::update_sublevel_in_screenblock_mirror_2d
		//	( active_level::bg0_screenblock_mirror_2d, 
		//	test_level.get_size_2d() );
		active_level_manager::update_sublevel_in_screenblock_mirror_2d();
		
		bios_wait_for_vblank();
		//game_manager::vblank_func();
		
	}
	
	
	return 0;
}



