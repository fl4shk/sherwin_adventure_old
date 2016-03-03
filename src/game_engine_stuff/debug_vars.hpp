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


#ifndef debug_vars_hpp
#define debug_vars_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "coll_box_class.hpp"
#include "fixed_classes.hpp"



extern u32 curr_debug_s32_index, curr_debug_u32_index, 
	curr_debug_f24p8_index, curr_debug_f8p8_index, 
	curr_debug_st_result_index __attribute__((_iwram));


static const u32 debug_arr_s32_size = 32;
extern vs32 debug_arr_s32[debug_arr_s32_size];
#define next_debug_s32 ( debug_arr_s32[curr_debug_s32_index++] )
#define show_debug_str_s32(str) ( memcpy8( &next_debug_s32, str, \
	sizeof(s32) ) )


static const u32 debug_arr_u32_size = 32;
extern vu32 debug_arr_u32[debug_arr_u32_size];
#define next_debug_u32 ( debug_arr_u32[curr_debug_u32_index++] )
#define show_debug_str_u32(str) ( memcpy8( &next_debug_u32, str, \
	sizeof(s32) ) )


static const u32 debug_arr_f24p8_size = 32;
extern fixed24p8 debug_arr_f24p8[debug_arr_f24p8_size];
#define next_debug_f24p8 ( debug_arr_f24p8[curr_debug_f24p8_index++] )
#define show_debug_str_f24p8(str) ( memcpy8( &next_debug_f24p8, str, \
	sizeof(fixed24p8) ) )


static const u32 debug_arr_f8p8_size = 32;
extern fixed8p8 debug_arr_f8p8[debug_arr_f8p8_size];
#define next_debug_f8p8 ( debug_arr_f8p8[curr_debug_f8p8_index++] )


void clear_debug_vars() __attribute__((_iwram_code));


#endif		// debug_vars_hpp
