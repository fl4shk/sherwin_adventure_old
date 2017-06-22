// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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
	curr_debug_st_result_index __attribute__((_IWRAM));

static const u32 debug_arr_s32_size = 32;
extern vs32 debug_arr_s32[debug_arr_s32_size];
#define NEXT_DEBUG_S32 (debug_arr_s32[curr_debug_s32_index++])
#define SHOW_DEBUG_STR_S32(str) (memcpy8(&NEXT_DEBUG_S32, str, \
	sizeof(s32)))


static const u32 debug_arr_u32_size = 32;
extern vu32 debug_arr_u32[debug_arr_u32_size];
#define NEXT_DEBUG_U32 (debug_arr_u32[curr_debug_u32_index++])
#define SHOW_DEBUG_STR_U32(str) (memcpy8(&NEXT_DEBUG_U32, str, \
	sizeof(s32)))


static const u32 debug_arr_f24p8_size = 32;
extern Fixed24p8 debug_arr_f24p8[debug_arr_f24p8_size];
#define NEXT_DEBUG_F24P8 (debug_arr_f24p8[curr_debug_f24p8_index++])
#define SHOW_DEBUG_STR_F24P8(str) (memcpy8(&NEXT_DEBUG_F24P8, str, \
	sizeof(Fixed24p8)))


static const u32 debug_arr_f8p8_size = 32;
extern Fixed8p8 debug_arr_f8p8[debug_arr_f8p8_size];
#define NEXT_DEBUG_F8P8 (debug_arr_f8p8[curr_debug_f8p8_index++])

void clear_debug_vars() __attribute__((_IWRAM_CODE));
*/


#define LIST_OF_DEBUG_SUFFIXES(macro) \
	macro(u32) macro(s32) macro(f24p8) macro(f8p8) macro(str)

#define MACRO_FOR_DEBUG_U32_TYPE_AND_SUFFIX(macro) \
	macro(u32, u32)
#define MACRO_FOR_DEBUG_S32_TYPE_AND_SUFFIX(macro) \
	macro(s32, s32)
#define MACRO_FOR_DEBUG_FIXED24P8_TYPE_AND_SUFFIX(macro) \
	macro(Fixed24p8, f24p8)
#define MACRO_FOR_DEBUG_FIXED8P8_TYPE_AND_SUFFIX(macro) \
	macro(Fixed8p8, f8p8)
#define MACRO_FOR_DEBUG_STR_TYPE_AND_SUFFIX(macro) \
	macro(DebugStr, str)


#define LIST_OF_DEBUG_TYPES_AND_SUFFIXES(macro) \
	MACRO_FOR_DEBUG_U32_TYPE_AND_SUFFIX(macro) \
	MACRO_FOR_DEBUG_S32_TYPE_AND_SUFFIX(macro) \
	MACRO_FOR_DEBUG_FIXED24P8_TYPE_AND_SUFFIX(macro) \
	MACRO_FOR_DEBUG_FIXED8P8_TYPE_AND_SUFFIX(macro) \
	MACRO_FOR_DEBUG_STR_TYPE_AND_SUFFIX(macro)

enum curr_debug_index_type
{
	cdit_u32,
	cdit_s32,
	cdit_f24p8,
	cdit_f8p8,
	cdit_str,
	
	lim_cdit
};


static constexpr u32 curr_index_arr_size = lim_cdit;

// 4 * 32 * 4 = 512 bytes eaten up by the non-string debug arrays.
static constexpr u32 debug_u32_arr_size = 32;
static constexpr u32 debug_s32_arr_size = 32;
static constexpr u32 debug_f24p8_arr_size = 32;
static constexpr u32 debug_f8p8_arr_size = 32;


// Please make sure That debug_str_arr_size Is a multiple of 4.
// debug_str_arr_size Is the number of DebugStr elements in
// DebugArrGroup::debug_str_arr.
static constexpr u32 debug_str_arr_size = 32;

//// (16 + 4) * 32 = 640 bytes eaten up by debug_str_arr.
// (20 + 4) * 32 = 768 bytes eaten up by debug_str_arr.

// Total of 20 + 512 + 640 = 1172 bytes (293 4-bytes-long words) eaten up
// by debug vars (INCLUDING the array indices).  This Is certainly
// wasteful....

class DebugStr
{
protected:		// variables
	u32 real_size;
	
public:		// and constants
	//// Please make sure That max_size Is a multiple of 4.  max_size Is the
	//// number of elements in arr.
	
	
	// It Is a very good idea for max_size To be a multiple of 4.  It makes
	// copying and clearing faster.
	///static constexpr u32 max_size = 16;
	static constexpr u32 max_size = 20;
	//char arr[max_size];
	std::array< char, max_size > arr;
	
public:		// functions
	inline DebugStr() : real_size(0)
	{
		clear_arr();
	}
	inline DebugStr(u32 n_real_size)
	{
		set_real_size(n_real_size);
		//memfill32(arr, 0, max_size / sizeof(u32));
		//arr_memfill32(arr, 0, max_size);
		clear_arr();
	}
	inline DebugStr(const DebugStr& to_copy)
	{
		operator = (to_copy);
	}
	inline DebugStr(const char* to_copy)
	{
		operator = (to_copy);
	}
	
	DebugStr& operator = (const DebugStr& to_copy);
	DebugStr& operator = (const char* to_copy);
	
	inline u32 get_real_size() const
	{
		return real_size;
	}
	
	inline void set_real_size(u32 n_real_size)
	{
		if (n_real_size > max_size)
		{
			real_size = max_size;
		}
		else
		{
			real_size = n_real_size;
		}
	}
	
	inline void clear_arr()
	{
		//arr_memfill32(arr, 0, max_size);
		//arr_memset(arr, 0, max_size);
		arr_memset(arr, 0);
	}
	inline void total_clear()
	{
		real_size = 0;
		clear_arr();
	}
	
	inline void clear_unused_portion()
	{
		for (u32 i=get_real_size(); i<max_size; ++i)
		{
			arr[i] = 0;
		}
	}
	
} __attribute__((_ALIGN4));


extern u32 (& curr_index_arr)[curr_index_arr_size];
extern u32 (& debug_u32_arr)[debug_u32_arr_size];
extern s32 (& debug_s32_arr)[debug_s32_arr_size];
extern Fixed24p8 (& debug_f24p8_arr)[debug_f24p8_arr_size];
extern Fixed8p8 (& debug_f8p8_arr)[debug_f8p8_arr_size];
extern DebugStr (& debug_str_arr)[debug_str_arr_size];

class DebugArrGroup
{
//protected:		// static variables (raw debug arrays)
public:		// static variables (raw debug arrays)
	struct raw_array_group
	{
		u32 curr_index_arr[curr_index_arr_size];
		
		u32 debug_u32_arr[debug_u32_arr_size];
		s32 debug_s32_arr[debug_s32_arr_size];
		Fixed24p8 debug_f24p8_arr[debug_f24p8_arr_size];
		Fixed8p8 debug_f8p8_arr[debug_f8p8_arr_size];
		
		DebugStr debug_str_arr[debug_str_arr_size];
	} __attribute__((_ALIGN4));
	static raw_array_group the_raw_array_group;
	
	
	// The main reason this Exists Is To give something To write To So That
	// a breakpoint Can be sure To be hit in GDB.  It's a  bit unfortunate
	// That I had To resort To something like this due To it being
	// inflexible, but oh well.
	static u32 gdb_breakpoint_helper;
	
public:		// static variables (array_helpers)
	static ArrayHelper<u32> curr_index_arr_helper;
	
	static ArrayHelper<u32> debug_u32_arr_helper;
	static ArrayHelper<s32> debug_s32_arr_helper;
	static ArrayHelper<Fixed24p8> debug_f24p8_arr_helper;
	static ArrayHelper<Fixed8p8> debug_f8p8_arr_helper;
	
	static ArrayHelper<DebugStr> debug_str_arr_helper;
	
//protected:		// functions
public:		// functions
	
	static inline u32* curr_index_arr()
	{
		return the_raw_array_group.curr_index_arr;
	}
	
	static inline u32* debug_u32_arr() 
	{
		return the_raw_array_group.debug_u32_arr;
	}
	static inline s32* debug_s32_arr()
	{
		return the_raw_array_group.debug_s32_arr;
	}
	static inline Fixed24p8* debug_f24p8_arr()
	{
		return the_raw_array_group.debug_f24p8_arr;
	}
	static inline Fixed8p8* debug_f8p8_arr()
	{
		return the_raw_array_group.debug_f8p8_arr;
	}
	static inline DebugStr* debug_str_arr()
	{
		return the_raw_array_group.debug_str_arr;
	}
public:		// functions
	
	
	static void clear_debug_vars();
	
	#define RAW_WRITE_DEBUG_U32_AND_INC(to_write) \
	DebugArrGroup::debug_u32_arr() \
		[DebugArrGroup::curr_index_arr()[cdit_u32]++] \
		= static_cast<u32>(to_write);
	
	#define RAW_WRITE_DEBUG_S32_AND_INC(to_write) \
	DebugArrGroup::debug_s32_arr() \
		[DebugArrGroup::curr_index_arr()[cdit_s32]++] \
		= static_cast<s32>(to_write);
	
	#define RAW_WRITE_DEBUG_F24P8_AND_INC(to_write) \
	DebugArrGroup::debug_f24p8_arr() \
		[DebugArrGroup::curr_index_arr()[cdit_f24p8]++] \
		= static_cast<Fixed24p8>(to_write);
	
	#define RAW_WRITE_DEBUG_F8P8_AND_INC(to_write) \
	DebugArrGroup::debug_f8p8_arr() \
		[DebugArrGroup::curr_index_arr()[cdit_f8p8]++] \
		= static_cast<Fixed8p8>(to_write);
	
	#define RAW_WRITE_DEBUG_STR_AND_INC(to_write) \
	DebugArrGroup::debug_str_arr() \
		[DebugArrGroup::curr_index_arr()[cdit_str]++] = to_write;
	
	static inline void write_u32_and_inc(u32 to_write)
	{
		RAW_WRITE_DEBUG_U32_AND_INC(to_write);
	}
	static inline void write_s32_and_inc(s32 to_write)
	{
		RAW_WRITE_DEBUG_S32_AND_INC(to_write);
	}
	static inline void write_f24p8_and_inc(const Fixed24p8& to_write)
	{
		RAW_WRITE_DEBUG_F24P8_AND_INC(to_write);
	}
	static inline void write_f8p8_and_inc(const Fixed8p8& to_write)
	{
		RAW_WRITE_DEBUG_F8P8_AND_INC(to_write);
	}
	
	static inline void write_str_and_inc(const DebugStr& to_write)
	{
		RAW_WRITE_DEBUG_STR_AND_INC(to_write);
	}
	
	static inline void write_str_and_inc(const char* to_write)
	{
		RAW_WRITE_DEBUG_STR_AND_INC(to_write);
	}
	
	
	
} __attribute__((_ALIGN4));





//template< typename debug_arr_type, typename type >
//void show_debug_values_group_backend(debug_arr_type* debug_values_arr, 
//	u32& curr_index, const u32 total_num_args, type* all_values_arr) 
//	__attribute__((noinline));
template< typename debug_arr_type, typename type >
void show_debug_values_group_backend(debug_arr_type* debug_values_arr, 
	u32& curr_index, const u32 total_num_args, const type* all_values_arr)
{
	//ASM_COMMENT("show_debug_values_group_backend()");
	
	//ASM_COMMENT("Before old_curr_index");
	const u32 old_curr_index = curr_index;
	
	//ASM_COMMENT("Before curr_index = old_curr_index + total_num_args");
	
	//curr_index += total_num_args;
	// Turns out That curr_index = old_curr_index + total_num_args Is
	// FASTER than curr_index += total_num_args with the code That gets
	// generated.
	curr_index = old_curr_index + total_num_args;
	
	//ASM_COMMENT("Before for loop");
	for (s32 i=total_num_args-1; i>=0; --i)
	{
		debug_values_arr[old_curr_index + i] = all_values_arr[i];
	}
	
	//ASM_COMMENT("end of show_debug_values_group_backend()");
}



// type Is the actual type, and suffix Is the type's suffix.  Sometimes,
// type == suffix, especially with generic types.
#define GENERATE_FUNC_CONTENTS(type, suffix) \
ASM_COMMENT("show_debug_" #suffix "_group()"); \
static constexpr size_t total_num_args = sizeof...(all_the_values); \
type all_values_arr[total_num_args]; \
copy_to_array(all_values_arr, all_the_values...); \
show_debug_values_group_backend \
	(DebugArrGroup::debug_##suffix##_arr(), \
	DebugArrGroup::curr_index_arr()[cdit_##suffix], total_num_args, \
	all_values_arr);

template< typename... all_the_types >
inline void show_debug_u32_group(const all_the_types&... all_the_values)
{
	MACRO_FOR_DEBUG_U32_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}


template< typename... all_the_types >
inline void show_debug_s32_group(const all_the_types&... all_the_values)
{
	MACRO_FOR_DEBUG_S32_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}

template< typename... all_the_types >
inline void show_debug_f24p8_group(const all_the_types&... all_the_values)
{
	MACRO_FOR_DEBUG_FIXED24P8_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}

template< typename... all_the_types >
inline void show_debug_f8p8_group(const all_the_types&... all_the_values)
{
	MACRO_FOR_DEBUG_FIXED8P8_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}

template< typename... all_the_types >
inline void show_debug_str_group(const all_the_types&... all_the_values)
{
	MACRO_FOR_DEBUG_STR_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}


#undef GENERATE_FUNC_CONTENTS


#endif		// debug_vars_hpp
