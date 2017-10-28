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
#include "general_utility_stuff/array_2d_helper_classes.hpp"
#include "general_utility_stuff/debug_vars.hpp"

//#include "game_engine_stuff/level_stuff/active_level_class.hpp"
//#include "game_engine_stuff/level_stuff/active_level_manager_class.hpp"
//#include "game_engine_stuff/sprite_stuff/sprite_manager_class.hpp"
//
//
//#include "game_engine_stuff/game_manager_class.hpp"
//#include "game_engine_stuff/gfx_manager_class.hpp"
//
//#include "game_engine_stuff/halt_stuff.hpp"
//#include "game_engine_stuff/coll_lseg_classes.hpp"
//#include "game_engine_stuff/hud_manager_class.hpp"

#include "gba_specific_stuff/interrupt_stuff.hpp"

#include "namespace_using.hpp"

// This Is an assembly function.  It doesn't do very much.
extern "C" int ewram_test_func();


static const u32 ewram_test_arr_size = 10;
u8 ewram_test_arr[ewram_test_arr_size] __attribute__((_ewram));

static const char test_str[] = "Birds2";
static const u32 test_str_size = (sizeof(test_str) / sizeof(char)) - 1;

//static const size_t sram_test_arr_size = 2000;
//u8 sram_test_arr[sram_test_arr_size] __attribute__((_sram));

extern const size_t clseg_grp_16x32_size;
volatile size_t very_temp;
static constexpr size_t test_buf_size = 20;
char test_buf[test_buf_size];

extern "C"
{

//int real_main() __attribute__((_iwram_code));
int real_main();

}


extern "C"
{

char address_buff[20] __attribute__((_sram));

vu32 some_title_screen_arr[8] __attribute__((_title_screen_bss));
vu32 some_title_screen_var __attribute__((_title_screen_bss));


vu32 some_in_level_var __attribute__((_in_level_bss));
vu32 some_in_level_arr[8] __attribute__((_in_level_bss));


vu32 some_title_screen_buf[8] __attribute__((_title_screen_iwram_bss));
vu32 some_in_level_buf[8] __attribute__((_in_level_iwram_bss));


char asdf[8] __attribute__((_title_screen_sram));
char asdf_2[8] __attribute__((_in_level_sram));

char asdf_ewram[8] __attribute__((_title_screen_ewram));
char asdf_2_ewram[8] __attribute__((_in_level_ewram));


int egg_title_screen __attribute__((_title_screen_iwram));

}



int main()
{
	//very_temp = clseg_grp_16x32_size;
	//return main_2();
	//snprintf(address_buff, 20, "%X", 
	//	(unsigned)(&some_title_screen_other_var));

	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(&some_title_screen_arr));
	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(&__iwram_data0_section_size));

	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(__iwram_data0_section_size));
	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(*__iwram_data0_start));

	gba::memcpy8(address_buff, test_buf, 9);
	//memcpy(some_in_level_arr, test_buf, 8);
	//memcpy(some_title_screen_arr, test_buf, 8);
	return real_main();
	//snprintf(test_buf, test_buf_size, "%s", "asdf");

}


extern "C"
{

int real_main()
{
	gba::irq_init();

	for (;;)
	{
		gba::bios_wait_for_vblank();
	}
}


}


