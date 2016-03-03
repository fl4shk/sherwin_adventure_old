// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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


#ifndef game_manager_class_hpp
#define game_manager_class_hpp

#include "../gba_specific_stuff/bios_function_wrappers.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "../gba_specific_stuff/button_stuff.hpp"
#include "debug_vars.hpp"

#include "maxmod.h"


#include "gfx_manager_class.hpp"


enum game_mode
{
	// When on the title screen.
	gm_title_screen,
	
	// When initializing the game
	gm_initializing_the_game,
	
	// When loading a level.
	gm_loading_level,
	
	// When changing from one sublevel to another.
	gm_changing_sublevel,
	
	// When in a sublevel.
	gm_in_sublevel,
	
	
	// gm_count is the amount of game modes.  It is automatically updated
	// by the compiler.
	gm_count,
	
} __attribute__((_align4));



class game_manager
{
public:		// variables
	
	static int test_int_global;
	
	static const char sram_const_init_str[];
	//static constexpr u32 sram_init_str_size = sizeof(sram_const_init_str);
	//static char sram_init_str[sram_init_str_size] __attribute__((_sram));
	static const u32 sram_init_str_size;
	static char sram_init_str[] __attribute__((_sram));
	
	//static constexpr u32 test_sram_arr_size = debug_arr_u32_size 
	//	* sizeof(u32);
	static constexpr u32 test_sram_arr_size = sizeof(debug_arr_u32);
	static u8 test_sram_arr[test_sram_arr_size] __attribute__((_sram));
	
	
	// The current game mode.
	static game_mode curr_game_mode;
	
	
	
public:		// functions
	
	// This function toggles whether music is playing if the select button
	// is down this frame but was not down on the previous frame.
	static inline void pause_or_unpause_music()
	{
		if( key_hit(key_select) )
		{
			if ( mmActive() ) { mmPause(); }
			else { mmResume(); }
		}
	}
	
	static inline void debug_infin_loop()
	{
		for (;;)
		{
			bios_wait_for_vblank();
			//vblank_func();
		}
	}
	
	static inline void wait_for_x_frames( u32 x )
	{
		for ( u32 i=0; i<x; ++i )
		{
			bios_wait_for_vblank();
		}
	}
	
	
	//static void vblank_func() __attribute__(( _iwram_code, __noinline__ ));
	static void vblank_func() __attribute__((_iwram_code));
	
	//static void title_screen_func() __attribute__((__noinline__));
	static void title_screen_func();
	
	static void reinit_the_game();
	
	
	
	
	
	
} __attribute__((_align4));






#endif		// game_manager_class_hpp
