// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#include "debug_vars.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"


u32 curr_debug_s32_index, curr_debug_u32_index, curr_debug_f24p8_index,
	curr_debug_f8p8_index, curr_debug_st_result_index;


vs32 debug_arr_s32[debug_arr_s32_size];
vu32 debug_arr_u32[debug_arr_u32_size];
fixed24p8 debug_arr_f24p8[debug_arr_f24p8_size];
fixed8p8 debug_arr_f8p8[debug_arr_f8p8_size];


void clear_debug_vars()
{
	curr_debug_s32_index = 0;
	curr_debug_u32_index = 0;
	curr_debug_f24p8_index = 0;
	
	memfill32( debug_arr_s32, 0, ( debug_arr_s32_size
		*  sizeof(s32) ) / sizeof(u32) );
	memfill32( debug_arr_u32, 0, debug_arr_u32_size );
	memfill32( debug_arr_f24p8, 0, ( debug_arr_f24p8_size
		*  sizeof(fixed24p8) ) / sizeof(u32) );
	memfill32( debug_arr_f8p8, 0, ( debug_arr_f8p8_size 
		* sizeof(fixed8p8) ) / sizeof(u32) );
}



