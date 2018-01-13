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


#ifndef gba_specific_stuff__slash__asm_funcs_hpp
#define gba_specific_stuff__slash__asm_funcs_hpp

#include "../namespace_using.hpp"
#include "../general_utility_stuff/misc_types.hpp"
#include "attribute_defines.hpp"

#include <string.h>

#define ASM_COMMENT(stuff) \
	asm volatile("@ ---" stuff " ---")

#include <array>

inline void* memcpy(volatile void* dst, const void* src, size_t n)
{
	return memcpy((void*)dst, src, n);
}

extern "C"
{

// These two functions should now be much faster, and I Can feel free To
// allocate more stuffs on the stack!
[[_iwram_code,_target_arm]] 
	void* memcpy(void* dst, const void* src, size_t n);

[[_iwram_code,_target_arm]]
void* memset(void* dst, int c, size_t n)
	;


// This function Is used by crt0.s
void* slower_memcpy(void* dst, const void* src, size_t n);


// memcpy32 Is from TONC
extern void memcpy32(void* dst, const void* src, u32 wordcount);

// memfill32 Is a modified version of memcpy32 To fill an array with a
// constant word.
extern void memfill32(void* dst, u32 src, u32 wordcount);



extern void memcpy8(void* dst, const void* src, u32 bytecount);
extern void memfill8(void* dst, u32 src, u32 bytecount);

}


// A bunch of wrappers
inline void memcpy32(volatile void* dst, const void* src, 
	u32 wordcount)
{
	memcpy32((void*)dst, src, wordcount);
}

inline void memfill32(volatile void* dst, u32 src, u32 wordcount)
{
	memfill32((void*)dst, src, wordcount);
}




inline void memcpy8(volatile void* dst, const void* src, u32 bytecount)
{
	memcpy8((void*)dst, src, bytecount);
}
inline void memfill8(volatile void* dst, u32 src, u32 bytecount)
{
	memfill8((void*)dst, (src & 0xff), bytecount);
}




// arr_mem*() with raw arrays
template<typename Type>
inline void arr_memcpy32(Type* dst, const void* src, u32 num_elems)
{
	memcpy32((void*)dst, (const void*)src, num_elems * sizeof(Type) 
		/ sizeof(u32));
}
template<typename Type>
inline void arr_memfill32(Type* dst, u32 src, u32 num_elems)
{
	memfill32((void*)dst, src, num_elems * sizeof(Type) / sizeof(u32));
}

template<typename Type>
inline void arr_memcpy8(Type* dst, const void* src, u32 num_elems)
{
	memcpy8((void*)dst, src, num_elems * sizeof(Type) / sizeof(u8));
}
template<typename Type>
inline void arr_memfill8(Type* dst, u32 src, u32 num_elems)
{
	memfill8((void*)dst, (src & 0xff), num_elems * sizeof(Type) 
		/ sizeof(u8));
}

template<typename Type>
inline void* arr_memcpy(Type* dst, const void* src, u32 num_elems)
{
	return memcpy((void*)dst, src, num_elems * sizeof(Type) / sizeof(u8));
}
template<typename Type>
inline void* arr_memset(Type* dst, int c, u32 num_elems)
{
	return memset((void*)dst, c, num_elems * sizeof(Type) / sizeof(u8));
}





template<typename dst_type, typename src_type, size_t size>
inline void arr_memcpy32(std::array<dst_type, size>& dst, 
	std::array<src_type, size>& src)
{
	arr_memcpy32<dst_type>(dst.data(), src.data(), size);
}
template<typename Type, size_t size>
inline void arr_memcpy32(std::array<Type, size>& dst, const void* src)
{
	arr_memcpy32<Type>(dst.data(), src, size);
}
template<typename Type, size_t size>
inline void arr_memfill32(std::array<Type, size>& dst, u32 src)
{
	arr_memfill32<Type>(static_cast<Type*>(dst.data()), src, size);
}


template<typename dst_type, typename src_type, size_t size>
inline void arr_memcpy8(std::array<dst_type, size>& dst, 
	std::array<src_type, size>& src)
{
	arr_memcpy8<dst_type>(dst.data(), src.data(), size);
}
template<typename Type, size_t size>
inline void arr_memcpy8(std::array<Type, size>& dst, const void* src)
{
	arr_memcpy8<Type>(dst.data(), src, size);
}
template<typename Type, size_t size>
inline void arr_memfill8(std::array<Type, size>& dst, u32 src)
{
	arr_memfill8<Type>(dst.data(), src, size);
}



template<typename dst_type, typename src_type, size_t size>
inline void* arr_memcpy(std::array<dst_type, size>& dst, 
	std::array<src_type, size>& src)
{
	return arr_memcpy<dst_type>(dst.data(), src.data(), size);
}
template<typename Type, size_t size>
inline void* arr_memcpy(std::array<Type, size>& dst, const void* src)
{
	return arr_memcpy<Type>(dst.data(), src, size);
}
template<typename Type, size_t size>
inline void* arr_memset(std::array<Type, size>& dst, u32 src)
{
	return arr_memset<Type>(dst.data(), src, size);
}




// Some inline template functions Intended for use with SRAM
template<typename Type>
inline void single_memcpy8(u8* dst, const Type& to_write)
{
	memcpy8(dst, &to_write, sizeof(Type));
}

template<typename Type>
inline void single_write_as_bytes(u8* dst, const Type& to_write)
{
	const u8* src = reinterpret_cast<const u8*>(&to_write);

	for (s32 i=sizeof(Type)-1; i>=0; --i)
	{
		dst[i] = src[i];
	}
}


template<typename Type>
inline void single_memcpy8(u8* dst_start, size_t type_offset, 
	const Type& to_write)
{
	u8* dst = &(dst_start[type_offset * sizeof(Type)]);

	memcpy8(dst, &to_write, sizeof(Type));
}

template<typename Type>
inline void single_write_as_bytes(u8* dst_start, size_t type_offset, 
	const Type& to_write)
{
	u8* dst = &(dst_start[type_offset * sizeof(Type)]);
	const u8* src = reinterpret_cast<const u8*>(&to_write);

	for (s32 i=sizeof(Type)-1; i>=0; --i)
	{
		dst[i] = src[i];
	}
}


template<typename Type>
inline void struct_memcpy32(Type& dst, const Type& src)
{
	memcpy32(&dst, &src, sizeof(Type) / sizeof(u32));
}
template<typename Type>
inline void struct_memcpy8(Type& dst, const Type& src)
{
	memcpy8(&dst, &src, sizeof(Type));
}
template<typename Type>
inline void* struct_memcpy(Type& dst, const Type& src)
{
	return memcpy(&dst, &src, sizeof(Type));
}

#endif		// gba_specific_stuff__slash__asm_funcs_hpp
