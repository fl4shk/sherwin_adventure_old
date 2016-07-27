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
//#include "coll_box_class.hpp"
#include "fixed_classes.hpp"
#include "array_helper_class.hpp"

/*
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
*/


enum curr_debug_index_type
{
	cdit_u32,
	cdit_s32,
	cdit_f24p8,
	cdit_f8p8,
	cdit_str,
	
	cdit_count
};


static constexpr u32 curr_index_arr_size = cdit_count;

// 4 * 32 * 4 = 512 bytes eaten up by the non-string debug arrays.
static constexpr u32 debug_u32_arr_size = 32;
static constexpr u32 debug_s32_arr_size = 32;
static constexpr u32 debug_f24p8_arr_size = 32;
static constexpr u32 debug_f8p8_arr_size = 32;


// Please make sure that debug_str_arr_size is a multiple of 4.
// debug_str_arr_size is the number of debug_str elements in
// debug_arr_group::debug_str_arr.
static constexpr u32 debug_str_arr_size = 32;

// ( 16 + 4 ) * 32 = 640 bytes eaten up by debug_str_arr.

// Total of 20 + 512 + 640 = 1172 bytes (293 4-bytes-long words) eaten up
// by debug vars (INCLUDING the array indices).  This is certainly
// wasteful....

class debug_str
{
protected:		// variables
	u32 real_size;
	
public:		// and constants
	// Please make sure that max_size is a multiple of 4.  max_size is the
	// number of elements in arr.
	///static constexpr u32 max_size = 16;
	static constexpr u32 max_size = 16;
	char arr[max_size];
	
public:		// functions
	debug_str();
	debug_str( u32 n_real_size );
	debug_str( const debug_str& to_copy );
	debug_str( const char* to_copy );
	
	debug_str& operator = ( const debug_str& to_copy );
	debug_str& operator = ( const char* to_copy );
	
	inline u32 get_real_size() const
	{
		return real_size;
	}
	
	inline void set_real_size( u32 n_real_size )
	{
		if ( n_real_size > max_size )
		{
			real_size = max_size;
		}
		else
		{
			real_size = n_real_size;
		}
	}
	
	inline void clear()
	{
		arr_memfill32( arr, 0, max_size );
	}
} __attribute__((_align4));



class debug_arr_group
{
protected:		// static variables (raw debug arrays)
	struct raw_array_group
	{
		vu32 curr_index_arr[curr_index_arr_size];
		
		vu32 debug_u32_arr[debug_u32_arr_size];
		vs32 debug_s32_arr[debug_s32_arr_size];
		fixed24p8 debug_f24p8_arr[debug_f24p8_arr_size];
		fixed8p8 debug_f8p8_arr[debug_f8p8_arr_size];
		
		debug_str debug_str_arr[debug_str_arr_size];
	} __attribute__((_align4));
	static raw_array_group the_raw_array_group;
	
public:		// static variables (array_helpers)
	static array_helper<vu32> curr_index_arr_helper;
	
	static array_helper<vu32> debug_u32_arr_helper;
	static array_helper<vs32> debug_s32_arr_helper;
	static array_helper<fixed24p8> debug_f24p8_arr_helper;
	static array_helper<fixed8p8> debug_f8p8_arr_helper;
	
	static array_helper<debug_str> debug_str_arr_helper;
	
protected:		// functions
	static inline vu32* curr_index_arr()
	{
		return the_raw_array_group.curr_index_arr;
	}
	static inline vu32* debug_u32_arr() 
	{
		return the_raw_array_group.debug_u32_arr;
	}
	static inline vs32* debug_s32_arr()
	{
		return the_raw_array_group.debug_s32_arr;
	}
	static inline fixed24p8* debug_f24p8_arr()
	{
		return the_raw_array_group.debug_f24p8_arr;
	}
	static inline fixed8p8* debug_f8p8_arr()
	{
		return the_raw_array_group.debug_f8p8_arr;
	}
	static inline debug_str* debug_str_arr()
	{
		return the_raw_array_group.debug_str_arr;
	}
public:		// functions
	
	
	static void clear_debug_vars();
	
	static inline void write_u32_and_inc( u32 to_write )
	{
		debug_u32_arr_helper.data_at(curr_index_arr_helper.data_at
			(cdit_u32)++) = to_write;
	}
	static inline void write_s32_and_inc( s32 to_write )
	{
		debug_s32_arr_helper.data_at(curr_index_arr_helper.data_at
			(cdit_s32)++) = to_write;
	}
	static inline void write_f24p8_and_inc( const fixed24p8& to_write )
	{
		debug_f24p8_arr_helper.data_at(curr_index_arr_helper.data_at
			(cdit_f24p8)++) = to_write;
	}
	static inline void write_f8p8_and_inc( const fixed8p8& to_write )
	{
		debug_f8p8_arr_helper.data_at(curr_index_arr_helper.data_at
			(cdit_f8p8)++) = to_write;
	}
	
	static inline void write_str_and_inc( const debug_str& to_write )
	{
		debug_str_arr_helper.data_at(curr_index_arr_helper.data_at
			(cdit_str)++) = to_write;
	}
	
	static inline void write_str_and_inc( const char* to_write )
	{
		debug_str_arr_helper.data_at(curr_index_arr_helper.data_at
			(cdit_str)++) = to_write;
	}
	
} __attribute__((_align4));



#endif		// debug_vars_hpp
