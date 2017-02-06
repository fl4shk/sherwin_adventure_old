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


#include "gba_specific_stuff/asm_funcs.hpp"

#include "gba_specific_stuff/button_stuff.hpp"
#include "gba_specific_stuff/gfx_reg_stuff.hpp"
#include "gba_specific_stuff/oam_entry_classes.hpp"
#include "gba_specific_stuff/interrupt_stuff.hpp"
#include "gba_specific_stuff/bios_function_wrappers.hpp"
#include "gba_specific_stuff/dma_stuff.hpp"
//#include "gba_specific_stuff/sound_reg_stuff.hpp"
#include "gba_specific_stuff/timer_stuff.hpp"
#include "gba_specific_stuff/profiling_stuff.hpp"


#include "general_utility_stuff/fixed_classes.hpp"
#include "general_utility_stuff/trigonometry_funcs.hpp"
#include "general_utility_stuff/array_2d_helper_class.hpp"
#include "general_utility_stuff/debug_vars.hpp"

#include "game_engine_stuff/level_stuff/active_level_class.hpp"
#include "game_engine_stuff/level_stuff/active_level_manager_class.hpp"
#include "game_engine_stuff/sprite_stuff/sprite_manager_class.hpp"


#include "game_engine_stuff/game_manager_class.hpp"
#include "game_engine_stuff/gfx_manager_class.hpp"

#include "game_engine_stuff/halt_stuff.hpp"



// This is an assembly function.  It doesn't do very much.
extern "C" int ewram_test_func();


static const u32 ewram_test_arr_size = 10;
u8 ewram_test_arr[ewram_test_arr_size] __attribute__((_ewram));

static const char test_str[] = "Birds2";
static const u32 test_str_size = ( sizeof(test_str) / sizeof(char) ) - 1;


int second_main();
int real_main();

int main()
{
	//return second_main();
	return real_main();
}

int second_main()
{
	profile_dynamic_allocations(20);
	return 0;
}

int real_main()
{
	irq_init();
	
	// This will eventually be used to identify whether save data has been
	// created.  As of right now, there is no need for save data, but that
	// will change in the future.  It is likely that 64 kiB of save data
	// will be more than enough.
	memcpy8( game_manager::sram_init_str,
		game_manager::sram_const_init_str, 
		game_manager::sram_init_str_size );
	
	
	//asm_comment("Before first show_debug_s32_group() call");
	//show_debug_s32_group
	//	( fixedu12p4_packed::get_underlying_type_is_signed(),
	//	fixeds12p4_packed::get_underlying_type_is_signed(),
	//	fixeds8p8_packed::get_underlying_type_is_signed(),
	//	sizeof(fixedu12p4_packed), 
	//	sizeof(fixeds12p4_packed),
	//	sizeof(fixeds8p8_packed) );
	//
	//asm_comment("Before second show_debug_s32_group() call");
	//show_debug_s32_group( make_f24p8( -3, 5 ).data, 
	//	make_f8p8( -3, 5 ).data, 
	//	make_fu12p4_packed( 10, 12 ).data, 
	//	make_fs12p4_packed( -3, 5 ).data, 
	//	make_fs8p8_packed( 124, 200 ).data );
	
	
	//arr_memfill8( (u8*)ewram_test_arr, '#', ewram_test_arr_size );
	//memset( ewram_test_arr, '#', ewram_test_arr_size );
	//memset( ewram_test_arr, '#', 4 );
	
	//ewram_test_arr[0] = '9';
	
	
	//memset( &ewram_test_arr[1], '3', 9 );
	//memcpy( &ewram_test_arr[1], test_str, 5 );
	//slower_memcpy( &ewram_test_arr[1], test_str, 5 );
	
	//memcpy( &ewram_test_arr[1]
	
	//halt();
	
	
	
	
	game_manager::title_screen_func();
	
	// This function is called by game_manager::title_screen_func().
	//game_manager::reinit_the_game();
	
	
	
	for (;;)
	{
		gfx_manager::back_up_bgofs_mirror();
		
		sprite& the_player = *sprite_manager::the_player;
		
		debug_arr_group::clear_debug_vars();
		
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
		
		
		
		sprite_manager::find_all_active_sprites();
		
		
		// Despawn sprites that are too far offscreen.
		sprite_manager::despawn_sprites_if_needed
			(gfx_manager::bgofs_mirror[0].curr);
		
		
		sprite_manager::find_all_active_sprites();
		
		
		sprite_manager::update_all_sprites
			( active_level::get_curr_sublevel_ptr().get_size_2d(), 
			gfx_manager::bgofs_mirror[0] );
		
		
		
		// This is temporary
		if ( key_hit_or_held(key_l) )
		{
			sprite_manager::spawn_a_sprite_basic( st_waffle,
				the_player.in_level_pos.curr, gfx_manager::bgofs_mirror[0],
				(bool)the_player.the_oam_entry.get_hflip_status() );
		}
		
		
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


