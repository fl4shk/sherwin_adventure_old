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


#ifndef general_utility_stuff__slash__debug_vars_hpp
#define general_utility_stuff__slash__debug_vars_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
//#include "coll_box_class.hpp"
#include "fixed_classes.hpp"
#include "array_helper_classes.hpp"
#include "gen_getter_setter_defines.hpp"


namespace sherwin_adventure
{

namespace misc_util
{

#define LIST_OF_DEBUG_SUFFIXES(macro) \
	macro(u32) macro(s32) macro(f24p8) macro(f8p8) macro(str)

#define MACRO_FOR_DEBUG_U32_TYPE_AND_SUFFIX(macro) \
	macro(u32, u32, U32)
#define MACRO_FOR_DEBUG_S32_TYPE_AND_SUFFIX(macro) \
	macro(s32, s32, S32)
#define MACRO_FOR_DEBUG_FIXED24P8_TYPE_AND_SUFFIX(macro) \
	macro(Fixed24p8, f24p8, F24p8)
#define MACRO_FOR_DEBUG_FIXED8P8_TYPE_AND_SUFFIX(macro) \
	macro(Fixed8p8, f8p8, F8p8)
#define MACRO_FOR_DEBUG_STR_TYPE_AND_SUFFIX(macro) \
	macro(DebugStr<DebugArrGroup::RawArrayGroup::debug_str_len>, str, Str)


#define LIST_OF_DEBUG_TYPES_AND_SUFFIXES(macro) \
	MACRO_FOR_DEBUG_U32_TYPE_AND_SUFFIX(macro) \
	MACRO_FOR_DEBUG_S32_TYPE_AND_SUFFIX(macro) \
	MACRO_FOR_DEBUG_FIXED24P8_TYPE_AND_SUFFIX(macro) \
	MACRO_FOR_DEBUG_FIXED8P8_TYPE_AND_SUFFIX(macro) \
	MACRO_FOR_DEBUG_STR_TYPE_AND_SUFFIX(macro)

enum class CurrDebugIndexType : size_t
{
	U32,
	S32,
	F24p8,
	F8p8,
	Str,

	LimCdit
};


static constexpr size_t curr_index_arr_size
	= static_cast<size_t>(CurrDebugIndexType::LimCdit);

// 4 * 32 * 4 = 512 bytes eaten up by the non-string debug arrays.
static constexpr size_t debug_u32_arr_size = 32;
static constexpr size_t debug_s32_arr_size = 32;
static constexpr size_t debug_f24p8_arr_size = 32;
static constexpr size_t debug_f8p8_arr_size = 32;


// Please make sure That debug_str_arr_size Is a multiple of 4.
// debug_str_arr_size Is the number of DebugStr elements in
// DebugArrGroup::debug_str_arr.
//static constexpr size_t debug_str_arr_size = 32;
static constexpr size_t debug_str_arr_size = 32;

//// (16 + 4) * 32 = 640 bytes eaten up by debug_str_arr.
// (20 + 4) * 32 = 768 bytes eaten up by debug_str_arr.

// Total of 20 + 512 + 640 = 1172 bytes (293 4-bytes-long words) eaten up
// by debug vars (INCLUDING the array indices).  This Is certainly
// wasteful....

template<size_t __max_size> 
class _alignas_regular DebugStr
{
protected:		// variables
	u32 __real_size;

public:		// and constants
	//// Please make sure That max_size Is a multiple of 4.  max_size Is the
	//// number of elements in arr.


	// It Is a very good idea for max_size To be a multiple of 4.  It makes
	// copying and clearing faster.
	///static constexpr u32 max_size = 16;
	//static constexpr u32 max_size = 20;
	//static constexpr u32 max_size = 256;
	static constexpr size_t max_size = __max_size;
	//char arr[max_size];
	std::array<char, max_size> arr;

public:		// functions
	inline DebugStr() : __real_size(0)
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

	//DebugStr& operator = (const DebugStr& to_copy);
	//DebugStr& operator = (const char* to_copy);

	[[gnu::noinline]]
	auto& operator = (const DebugStr& to_copy)
	{
		set_real_size(to_copy.real_size());
		//memcpy32(arr, to_copy.arr, max_size / sizeof(u32));
		//arr_memcpy32(arr, to_copy.arr, max_size);
		//arr_memcpy(arr, to_copy.arr, max_size);

		arr_memcpy(arr.data(), to_copy.arr.data(), real_size());

		clear_unused_portion();

		return *this;
	}

	[[gnu::noinline]]
	auto& operator = (const char* to_copy) 
	{
		//memfill32(arr, 0, max_size / sizeof(u32));
		//arr_memfill32(arr, 0, max_size);
		//clear();

		for (__real_size=0; __real_size<max_size; ++__real_size)
		{
			if (to_copy[__real_size] == '\0')
			{
				break;
			}
			arr[__real_size] = to_copy[__real_size];
		}

		// Clear any leftover bytes
		clear_unused_portion();

		return *this;
	}

	gen_getter_by_val(real_size);

	inline void set_real_size(u32 n_real_size)
	{
		if (n_real_size > max_size)
		{
			__real_size = max_size;
		}
		else
		{
			__real_size = n_real_size;
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
		__real_size = 0;
		clear_arr();
	}

	inline void clear_unused_portion()
	{
		for (u32 i=real_size(); i<max_size; ++i)
		{
			arr[i] = 0;
		}
	}

};



class _alignas_regular DebugArrGroup
{
//protected:		// static variables (raw debug arrays)
public:		// static variables (raw debug arrays)
	struct _alignas_regular RawArrayGroup
	{
		static constexpr size_t debug_str_len = 20;
		//static constexpr size_t err_str_len = 256;

		size_t curr_index_arr[curr_index_arr_size];

		u32 debug_u32_arr[debug_u32_arr_size];
		s32 debug_s32_arr[debug_s32_arr_size];
		Fixed24p8 debug_f24p8_arr[debug_f24p8_arr_size];
		Fixed8p8 debug_f8p8_arr[debug_f8p8_arr_size];

		DebugStr<debug_str_len> debug_str_arr[debug_str_arr_size];

		//DebugStr<err_str_len> err_str;
		const char* err_str;

		//const char* warn_str[debug_str_arr_size];
	};
	static RawArrayGroup raw_array_group;



	// The main reason this Exists Is To give something To write To So That
	// a breakpoint Can be sure To be hit in GDB.  It's a  bit unfortunate
	// That I had To resort To something like this due To it being
	// inflexible, but oh well.
	static u32 gdb_breakpoint_helper;

public:		// static variables (array_helpers)
	static ArrayHelper<size_t> curr_index_arr_helper;

	static ArrayHelper<u32> debug_u32_arr_helper;
	static ArrayHelper<s32> debug_s32_arr_helper;
	static ArrayHelper<Fixed24p8> debug_f24p8_arr_helper;
	static ArrayHelper<Fixed8p8> debug_f8p8_arr_helper;

	static ArrayHelper<DebugStr<RawArrayGroup::debug_str_len>> 
		debug_str_arr_helper;

//protected:		// functions
public:		// functions

	static inline auto curr_index_arr()
	{
		return raw_array_group.curr_index_arr;
	}

	static inline auto debug_u32_arr() 
	{
		return raw_array_group.debug_u32_arr;
	}
	static inline auto debug_s32_arr()
	{
		return raw_array_group.debug_s32_arr;
	}
	static inline auto debug_f24p8_arr()
	{
		return raw_array_group.debug_f24p8_arr;
	}
	static inline auto debug_f8p8_arr()
	{
		return raw_array_group.debug_f8p8_arr;
	}
	static inline auto debug_str_arr()
	{
		return raw_array_group.debug_str_arr;
	}
public:		// functions


	static void clear_debug_vars();




	static inline void write_u32_and_inc(u32 to_write)
	{
		debug_u32_arr()[curr_index_arr()
			[static_cast<size_t>(CurrDebugIndexType::U32)]++]
			= static_cast<u32>(to_write);
	}
	static inline void write_s32_and_inc(s32 to_write)
	{
		debug_s32_arr()[curr_index_arr()
			[static_cast<size_t>(CurrDebugIndexType::S32)]++]
			= static_cast<s32>(to_write);
	}
	static inline void write_f24p8_and_inc(const Fixed24p8& to_write)
	{
		debug_f24p8_arr()[curr_index_arr()
			[static_cast<size_t>(CurrDebugIndexType::F24p8)]++]
			= static_cast<Fixed24p8>(to_write);
	}
	static inline void write_f8p8_and_inc(const Fixed8p8& to_write)
	{
		debug_f8p8_arr()[curr_index_arr()
			[static_cast<size_t>(CurrDebugIndexType::F8p8)]++]
			= static_cast<Fixed8p8>(to_write);
	}

	////static inline void write_str_and_inc(const DebugStr& to_write)
	//static inline void write_str_and_inc
	//	(const DebugStr<RawArrayGroup::debug_str_len>& to_write)
	//{
	//	debug_str_arr()[curr_index_arr()
	//		[static_cast<size_t>(CurrDebugIndexType::Str)]++] = to_write;
	//}

	static inline void write_str_and_inc(const char* to_write)
	{
		debug_str_arr()[curr_index_arr()
			[static_cast<size_t>(CurrDebugIndexType::Str)]++] = to_write;
	}



};

extern size_t (& curr_index_arr)[curr_index_arr_size];
extern u32 (& debug_u32_arr)[debug_u32_arr_size];
extern s32 (& debug_s32_arr)[debug_s32_arr_size];
extern Fixed24p8 (& debug_f24p8_arr)[debug_f24p8_arr_size];
extern Fixed8p8 (& debug_f8p8_arr)[debug_f8p8_arr_size];
extern DebugStr<DebugArrGroup::RawArrayGroup::debug_str_len> 
	(& debug_str_arr)[debug_str_arr_size];





//template<typename debug_arr_type, typename Type>
//[[gnu::noinline]]
//void show_debug_values_group_backend(debug_arr_type* debug_values_arr, 
//	u32& curr_index, const u32 total_num_args, Type* all_values_arr);
template<typename debug_arr_type, typename Type>
void show_debug_values_group_backend(debug_arr_type* debug_values_arr, 
	u32& curr_index, const u32 total_num_args, const Type* all_values_arr)
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



// Type Is the actual Type, and suffix Is the Type's suffix.  Sometimes,
// Type == suffix, especially with generic types.
#define GENERATE_FUNC_CONTENTS(Type, suffix, enum_val) \
ASM_COMMENT("show_debug_" #suffix "_group()"); \
static constexpr size_t total_num_args = sizeof...(all_the_values); \
Type all_values_arr[total_num_args]; \
init_array(all_values_arr, all_the_values...); \
show_debug_values_group_backend \
	(DebugArrGroup::debug_##suffix##_arr(), \
	DebugArrGroup::curr_index_arr() \
	[static_cast<size_t>(CurrDebugIndexType::enum_val)], \
	total_num_args, all_values_arr);

template<typename... AllTheTypes>
inline void show_debug_u32_group(const AllTheTypes&... all_the_values)
{
	MACRO_FOR_DEBUG_U32_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}


template<typename... AllTheTypes>
inline void show_debug_s32_group(const AllTheTypes&... all_the_values)
{
	MACRO_FOR_DEBUG_S32_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}

template<typename... AllTheTypes>
inline void show_debug_f24p8_group(const AllTheTypes&... all_the_values)
{
	MACRO_FOR_DEBUG_FIXED24P8_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}

template<typename... AllTheTypes>
inline void show_debug_f8p8_group(const AllTheTypes&... all_the_values)
{
	MACRO_FOR_DEBUG_FIXED8P8_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}

template<typename... AllTheTypes>
inline void show_debug_str_group(const AllTheTypes&... all_the_values)
{
	MACRO_FOR_DEBUG_STR_TYPE_AND_SUFFIX(GENERATE_FUNC_CONTENTS);
}


#undef GENERATE_FUNC_CONTENTS

}

}


#endif		// general_utility_stuff__slash__debug_vars_hpp
