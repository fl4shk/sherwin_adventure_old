// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
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
#include "general_utility_stuff/array_2d_helper_classes.hpp"
#include "general_utility_stuff/debug_vars.hpp"

#include "game_engine_stuff/level_stuff/active_level_class.hpp"
#include "game_engine_stuff/level_stuff/active_level_manager_class.hpp"
#include "game_engine_stuff/sprite_stuff/sprite_manager_class.hpp"


#include "game_engine_stuff/game_manager_class.hpp"
#include "game_engine_stuff/gfx_manager_class.hpp"

#include "game_engine_stuff/halt_stuff.hpp"
#include "game_engine_stuff/coll_lseg_classes.hpp"
#include "game_engine_stuff/hud_manager_class.hpp"


// This Is an assembly function.  It doesn't do very much.
extern "C" int ewram_test_func();


static const u32 ewram_test_arr_size = 10;
u8 ewram_test_arr[ewram_test_arr_size] __attribute__((_EWRAM));

static const char test_str[] = "Birds2";
static const u32 test_str_size = (sizeof(test_str) / sizeof(char)) - 1;

//static const size_t sram_test_arr_size = 2000;
//u8 sram_test_arr[sram_test_arr_size] __attribute__((_SRAM));

extern const size_t clseg_grp_16x32_size;
volatile size_t very_temp;
static constexpr size_t test_buf_size = 20;
char test_buf[test_buf_size];

int main_2();
//int real_main() __attribute__((_IWRAM_CODE));
int real_main();


int main()
{
	//very_temp = clseg_grp_16x32_size;
	//return main_2();
	return real_main();
	//snprintf(test_buf, test_buf_size, "%s", "asdf");
	
}

//volatile u32 very_temp;
int main_2()
{
	//profile_dynamic_allocations(20);
	
	
	//HorizCollLseg a(vec2_s32(10, 20), make_f24p8(10));
	//HorizCollLseg b(vec2_s32(20, 20), make_f24p8(1));
	//
	//VertCollLseg c(vec2_s32(10, 20), make_f24p8(50));
	//////show_debug_u32_group(a.intersects(b), a.intersects(c), 
	//////	c.intersects(a));
	////profile_start();
	//////very_temp = a.intersects(c);
	////profile_stop();
	
	
	const Fixed24p8 a = make_f24p8(20, 0x80),
		b = make_f24p8(8, 0x4a);
	
	//const Fixed24p8 a = make_f24p8(0x200, 0x80),
	//	b = make_f24p8(0x100, 0x4a);
	
	profile_start();
	const Fixed24p8 c = a / b;
	show_profile_stop();
	show_debug_s32_group(c.data);
	
	
	return 0;
}

int real_main()
{
	irq_init();
	
	// This will eventually be used To identify whether save data has been
	// created.  As of right now, there Is no need for save data, but That
	// will change in the future.  It Is likely That 64 kiB of save data
	// will be more than enough.
	memcpy8(GameManager::sram_init_str,
		GameManager::sram_const_init_str, 
		GameManager::sram_init_str_size);
	
	
	//ASM_COMMENT("Before first show_debug_s32_group() call");
	//show_debug_s32_group
	//	(fixedu12p4_packed::get_underlying_type_is_signed(),
	//	fixeds12p4_packed::get_underlying_type_is_signed(),
	//	fixeds8p8_packed::get_underlying_type_is_signed(),
	//	sizeof(fixedu12p4_packed), 
	//	sizeof(fixeds12p4_packed),
	//	sizeof(fixeds8p8_packed));
	//
	//ASM_COMMENT("Before second show_debug_s32_group() call");
	//show_debug_s32_group(make_f24p8(-3, 5).data, 
	//	make_f8p8(-3, 5).data, 
	//	make_fu12p4_packed(10, 12).data, 
	//	make_fs12p4_packed(-3, 5).data, 
	//	make_fs8p8_packed(124, 200).data);
	
	
	//arr_memfill8((u8*)ewram_test_arr, '#', ewram_test_arr_size);
	//memset(ewram_test_arr, '#', ewram_test_arr_size);
	//memset(ewram_test_arr, '#', 4);
	
	//ewram_test_arr[0] = '9';
	
	
	//memset(&ewram_test_arr[1], '3', 9);
	//memcpy(&ewram_test_arr[1], test_str, 5);
	//slower_memcpy(&ewram_test_arr[1], test_str, 5);
	
	//memcpy(&ewram_test_arr[1]
	
	//halt();
	
	
	
	
	GameManager::title_screen_func();
	
	// This function Is called by GameManager::title_screen_func().
	//GameManager::reinit_the_game();
	
	
	
	for (;;)
	{
		GfxManager::back_up_bgofs_mirror();
		
		Sprite& the_player = *SpriteManager::the_player;
		
		DebugArrGroup::clear_debug_vars();
		
		clear_oam_mirror();
		
		// Key polling Is done in GameManager::vblank_func()
		//key_poll();
		
		if (soft_reset_keys_down())
		{
			// Reset the game if A, B, Start, and Select are pressed
			//bios_do_hard_reset();
			////bios_do_soft_reset();
			GameManager::reinit_the_game();
		}
		
		
		
		SpriteManager::find_all_active_sprites();
		
		
		// Despawn sprites That are too far offscreen.
		SpriteManager::despawn_sprites_if_needed
			(GfxManager::bgofs_mirror[0].curr);
		
		
		SpriteManager::find_all_active_sprites();
		
		
		SpriteManager::update_all_sprites
			(ActiveLevel::get_curr_sublevel_ptr().get_size_2d(), 
			GfxManager::bgofs_mirror[0]);
		
		
		
		// This Is temporary
		//if (key_hit_or_held(KEY_L))
		if (key_hit(KEY_L))
		{
			//SpriteManager::spawn_a_sprite_basic(StWaffle,
			//	the_player.in_level_pos.curr, GfxManager::bgofs_mirror[0],
			//	(bool)the_player.the_oam_entry.get_hflip_status());
			SpriteManager::spawn_a_sprite_basic(StWaffle,
				the_player.in_level_pos.curr +
				vec2_f24p8(make_f24p8(0), 
				make_f24p8(the_player.get_shape_size_as_vec2().y / 2)), 
				GfxManager::bgofs_mirror[0],
				(bool)the_player.the_oam_entry.get_hflip_status());
		}
		
		
		//if (key_hit(KEY_SELECT))
		//{
		//	GameManager::fade_out_to_black(1);
		//	
		//	GameManager::wait_for_x_frames(60);
		//	
		//	GameManager::fade_in(1);
		//}
		
		SpriteManager::spawn_sprites_if_needed
			(GfxManager::bgofs_mirror[0]);
		
		//if (key_hit(KEY_L))
		//{
		//	--player_sprite_stuff::remaining_hp;
		//}
		//if (key_hit(KEY_R))
		//{
		//	++player_sprite_stuff::remaining_hp;
		//}
		//
		
		
		//ActiveLevelManager::update_sublevel_in_screenblock_mirror_2d
		//	(ActiveLevel::bg0_screenblock_mirror_2d, 
		//	test_level.get_size_2d());
		ActiveLevelManager::update_sublevel_in_screenblock_mirror_2d();
		
		HudManager::update_hud_in_screenblock_mirror_2d();
		bios_wait_for_vblank();
		//GameManager::vblank_func();
		
	}
	
	
	
	return 0;
}


