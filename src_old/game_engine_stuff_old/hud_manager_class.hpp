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


#ifndef hud_manager_class_hpp
#define hud_manager_class_hpp

#include "../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../gba_specific_stuff/bios_function_wrappers.hpp"
#include "../general_utility_stuff/array_2d_helper_classes.hpp"
#include "gfx_manager_class.hpp"

class HudManager
{
public:		// variables
	static bool hud_was_generated __attribute__((_ewram));
	
	
	// -- Switch To linear_memory_allocator --
	static ScrEntry bg1_screenblock_mirror[screenblock_size]
		__attribute__((_ewram));
	
	
	// bg1_screenblock_2d Is in VRAM.
	static ArrayCsz2dHelper<ScrEntry, screenblock_xsize,
		screenblock_ysize> bg1_screenblock_2d;
	
	// bg1_screenblock_mirror_2d Is in EWRAM.
	static ArrayCsz2dHelper<ScrEntry, screenblock_xsize, 
		screenblock_ysize> bg1_screenblock_mirror_2d;
	
	static constexpr u32 char_to_plottable_char_arr_size = 0x100;
	static const char char_to_plottable_char_arr
		[char_to_plottable_char_arr_size];
	
public:		// functions
	// for some reason, NOT having these two functions marked as
	// __noinline__ causes problems.
	//static void plot_char_8x16_to_screenblock_mirror(u32 the_char, 
	//	u32 pos_x, u32 pos_y) __attribute__((_iwram_code,__noinline__));
	
	//static void plot_char_8x8_to_screenblock_mirror(u32 the_char,
	//	u32 pos_x, u32 pos_y) __attribute__((_iwram_code,__noinline__));
	
	static void plot_horiz_str_8x8_to_screenblock_mirror(const char* str,
		u32 str_size, u32& plot_x, u32& plot_y);
		__attribute__((_iwram_code));
	
	
	static void update_hud_in_screenblock_mirror_2d();
		__attribute__((_iwram_code));
	
	static void copy_hud_from_array_csz_2d_helper_to_vram();
	
} __attribute__((_align4));


#endif		// hud_manager_class_hpp
