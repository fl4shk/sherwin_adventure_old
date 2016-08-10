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


#include "debug_vars.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"

#include <string.h>

/*
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
	curr_debug_f8p8_index = 0;
	
	//memfill32( debug_arr_s32, 0, ( debug_arr_s32_size
	//	*  sizeof(s32) ) / sizeof(u32) );
	//memfill32( debug_arr_u32, 0, debug_arr_u32_size );
	//memfill32( debug_arr_f24p8, 0, ( debug_arr_f24p8_size
	//	*  sizeof(fixed24p8) ) / sizeof(u32) );
	memfill32( debug_arr_s32, 0, ( debug_arr_s32_size * sizeof(s32)
		+ debug_arr_u32_size * sizeof(u32) 
		+ debug_arr_f24p8_size * sizeof(fixed24p8) ) / sizeof(u32) );
	memfill32( debug_arr_f8p8, 0, ( debug_arr_f8p8_size 
		* sizeof(fixed8p8) ) / sizeof(u32) );
}
*/

debug_str& debug_str::operator = ( const debug_str& to_copy )
{
	set_real_size(to_copy.get_real_size());
	//memcpy32( arr, to_copy.arr, max_size / sizeof(u32) );
	//arr_memcpy32( arr, to_copy.arr, max_size );
	//arr_memcpy( arr, to_copy.arr, max_size );
	
	arr_memcpy( arr.data(), to_copy.arr.data(), get_real_size() );
	
	clear_unused_portion();
	
	return *this;
}

debug_str& debug_str::operator = ( const char* to_copy )
{
	//memfill32( arr, 0, max_size / sizeof(u32) );
	//arr_memfill32( arr, 0, max_size );
	//clear();
	
	for ( real_size=0; real_size<max_size; ++real_size )
	{
		if ( to_copy[real_size] == '\0' )
		{
			break;
		}
		arr[real_size] = to_copy[real_size];
	}
	
	// Clear any leftover bytes
	clear_unused_portion();
	
	return *this;
}

vu32 (& curr_index_arr)[curr_index_arr_size]
	= debug_arr_group::the_raw_array_group.curr_index_arr;
vu32 (& debug_u32_arr)[debug_u32_arr_size]
	= debug_arr_group::the_raw_array_group.debug_u32_arr;
vs32 (& debug_s32_arr)[debug_s32_arr_size]
	= debug_arr_group::the_raw_array_group.debug_s32_arr;
fixed24p8 (& debug_f24p8_arr)[debug_f24p8_arr_size]
	= debug_arr_group::the_raw_array_group.debug_f24p8_arr;
fixed8p8 (& debug_f8p8_arr)[debug_f8p8_arr_size]
	= debug_arr_group::the_raw_array_group.debug_f8p8_arr;
debug_str (& debug_str_arr)[debug_str_arr_size]
	= debug_arr_group::the_raw_array_group.debug_str_arr;


// static variables (raw debug arrays)
debug_arr_group::raw_array_group debug_arr_group::the_raw_array_group;

// static variables (array_helpers)
array_helper<vu32> debug_arr_group::curr_index_arr_helper
	( the_raw_array_group.curr_index_arr, curr_index_arr_size );

array_helper<vu32> debug_arr_group::debug_u32_arr_helper
	( the_raw_array_group.debug_u32_arr, debug_u32_arr_size );
array_helper<vs32> debug_arr_group::debug_s32_arr_helper
	( the_raw_array_group.debug_s32_arr, debug_s32_arr_size );
array_helper<fixed24p8> debug_arr_group::debug_f24p8_arr_helper
	( the_raw_array_group.debug_f24p8_arr, debug_f24p8_arr_size );
array_helper<fixed8p8> debug_arr_group::debug_f8p8_arr_helper
	( the_raw_array_group.debug_f8p8_arr, debug_f8p8_arr_size );

array_helper<debug_str> debug_arr_group::debug_str_arr_helper
	( the_raw_array_group.debug_str_arr, debug_str_arr_size );


void debug_arr_group::clear_debug_vars()
{
	////memfill32( curr_index_arr(), 0, cdit_count / sizeof(u32) );
	//for ( u32 i=0; i<curr_index_arr_helper.get_size(); ++i )
	//{
	//	curr_index_arr_helper.at(i) = 0;
	//}
	//
	//// One big memfill32() call that depends on the order in which the
	//// arrays are declared.
	////memfill32( debug_u32_arr, 0, ( debug_u32_arr_size * sizeof(u32)
	////	+ debug_s32_arr_size * sizeof(s32)
	////	+ debug_f24p8_arr_size * sizeof(fixed24p8)
	////	+ debug_f8p8_arr_size * sizeof(fixed8p8) ) / sizeof(u32) );
	//
	//
	//// I believe this will work?
	//memfill32( debug_u32_arr(), 0, ( (u32)debug_f8p8_arr() 
	//	+ ( debug_f8p8_arr_size * sizeof(fixed8p8) ) 
	//	- (u32)(u32*)debug_u32_arr()) / sizeof(u32) );
	//
	//// Use a separate memfill32() call for the array of debug_strs, just in
	//// case.
	//memfill32( debug_str_arr(), 0, debug_str_arr_helper.get_size() 
	//	* sizeof(debug_str) / sizeof(u32) );
	
	//memfill32( &the_raw_array_group, 0, sizeof(raw_array_group) 
	//	/ sizeof(u32) );
	
	memset( &the_raw_array_group, 0, sizeof(raw_array_group) );
}


