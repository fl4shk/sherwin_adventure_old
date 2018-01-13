// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andrew Clark (FL4SHK).
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


#include "overlay_testing_stuff.hpp"


// This stuff is disabled so that it doesn't use up extra memory
#if 0

//static constexpr size_t test_buf_size = 1024;
static constexpr size_t test_buf_size = 64;
char test_buf[test_buf_size];


extern "C"
{

//char address_buf[20] [[_sram]];

//vu32 some_title_screen_arr[8] [[_title_screen_bss]];
//vu32 some_title_screen_var [[_title_screen_bss]];
//
//
//vu32 some_in_level_var [[_in_level_bss]];
//vu32 some_in_level_arr[8] [[_in_level_bss]];
//
//
//vu32 some_title_screen_buf[8] [[_title_screen_iwram_bss]];
//vu32 some_in_level_buf[8] [[_in_level_iwram_bss]];
//
//
//char asdf[8] [[_title_screen_sram]];
//char asdf_2[8] [[_in_level_sram]];
//
//char asdf_ewram[8] [[_title_screen_ewram]];
//char asdf_2_ewram[8] [[_in_level_ewram]];


//char extra_address_test_buf_0[32] [[_sram]];
//char extra_address_test_buf_1[32] [[_sram]];
//char extra_address_test_buf_2[32] [[_sram]];
//char extra_address_test_buf_3[32] [[_sram]];
char overlay_loader_test_buf[test_buf_size] [[_sram]];
char title_screen_test_buf[test_buf_size] [[_sram]];
char overworld_load_test_buf[test_buf_size] [[_sram]];

}



extern "C"
{

void test_title_screen()
{
	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(&test_title_screen));
	//memcpy8(extra_address_test_buf_0, test_buf, 9);

	snprintf(test_buf, test_buf_size, "test_title_screen()");
	memcpy8(title_screen_test_buf, test_buf, test_buf_size);
	memcpy8(overlay_loader_test_buf, test_buf, test_buf_size);
}

void test_overworld_load()
{
	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(&test_overworld_load));
	//memcpy8(extra_address_test_buf_1, test_buf, 9);

	snprintf(test_buf, test_buf_size, "test_overworld_load()");
	memcpy8(overworld_load_test_buf, test_buf, test_buf_size);
	memcpy8(overlay_loader_test_buf, test_buf, test_buf_size);
}

}


void test_some_linker_overlay_stuff()
{
	//very_temp = clseg_grp_16x32_size;
	//return main_2();
	//snprintf(address_buf, 20, "%X", 
	//	(unsigned)(&some_title_screen_other_var));

	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(&some_title_screen_arr));
	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(&__iwram_data0_section_size));

	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(__iwram_data0_section_size));
	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)(&__iwram_data0_rom_start__));

	//memcpy8(address_buf, test_buf, 9);
	//memcpy(some_in_level_arr, test_buf, 8);
	//memcpy(some_title_screen_arr, test_buf, 8);
	//memcpy32(some_title_screen_arr, test_buf, 8);


	game_engine::OverlayLoader overlay_loader;

	overlay_loader.load(game_engine::OverlayNum::TitleScreen);
	test_title_screen();

	overlay_loader.load(game_engine::OverlayNum::OverworldLoad);
	test_overworld_load();



	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)&__sram0_start__);
	//memcpy8(extra_address_test_buf_2, test_buf, 9);
	//snprintf(test_buf, test_buf_size, "%X",
	//	(unsigned)&__sram0_end__);
	//memcpy8(extra_address_test_buf_3, test_buf, 9);
}

#endif
