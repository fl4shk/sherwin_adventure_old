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


#ifndef asm_funcs_hpp
#define asm_funcs_hpp

#include "../game_engine_stuff/misc_types.hpp"
#include "attribute_defines.hpp"

#define asm_comment(stuff) \
	asm volatile( "@ ---" stuff " ---" )

#include <array>

extern "C"
{

// These two functions should now be much faster, and I can feel free to
// allocate more stuffs on the stack!
void* memcpy( void* dst, const void* src, size_t n )
	__attribute__((_iwram_code));
void* memset( void* dst, int c, size_t n )
	__attribute__((_iwram_code));


// This function is used by crt0.s
void* slower_memcpy( void* dst, const void* src, size_t n );


// lut_udiv should actually take a u16 dem, not a u32 dem
extern u64 lut_udiv( u32 num, u32 dem );

// memcpy32 is from TONC
extern void memcpy32( void* dst, const void* src, u32 wordcount );

// memfill32 is a modified version of memcpy32 to fill an array with a
// constant word.
extern void memfill32( void* dst, u32 src, u32 wordcount );



extern void memcpy8( void* dst, const void* src, u32 bytecount );
extern void memfill8( void* dst, u32 src, u32 bytecount );

}

inline void memcpy32( volatile void* dst, const void* src, 
	u32 wordcount )
{
	memcpy32( (void*)dst, src, wordcount );
}

inline void memfill32( volatile void* dst, u32 src, u32 wordcount )
{
	memfill32( (void*)dst, src, wordcount );
}


template<typename type>
inline void arr_memcpy32( type* dst, const type* src, u32 num_elems )
{
	memcpy32( (void*)dst, (const void*)src, num_elems * sizeof(type) 
		/ sizeof(u32) );
}
template<typename type>
inline void arr_memfill32( type* dst, u32 src, u32 num_elems )
{
	memfill32( (void*)dst, src, num_elems * sizeof(type) / sizeof(u32) );
}


template< typename type, size_t size >
inline void arr_memfill32( std::array< type, size >& arr_to_fill, 
	u32 src )
{
	arr_memfill32<type>( arr_to_fill.data(), src, size );
}




inline void memcpy8( volatile void* dst, const void* src, u32 bytecount )
{
	memcpy8( (void*)dst, src, bytecount );
}
inline void memfill8( volatile void* dst, u32 src, u32 bytecount )
{
	memfill8( (void*)dst, (src & 0xff), bytecount );
}


template< typename type >
inline void arr_memcpy8( type* dst, const type* src, u32 num_elems )
{
	memcpy8( (void*)dst, src, num_elems * sizeof(type) / sizeof(u8) );
}
template< typename type >
inline void arr_memfill8( type* dst, u32 src, u32 num_elems )
{
	memfill8( (void*)dst, (src & 0xff), num_elems * sizeof(type) 
		/ sizeof(u8) );
}



template< typename type >
inline void* arr_memcpy( type* dst, const type* src, u32 num_elems )
{
	return memcpy( dst, src, num_elems * sizeof(type) / sizeof(u8) );
}

template< typename type >
inline void* arr_memset( type* dst, int c, u32 num_elems )
{
	return memset( dst, c, num_elems * sizeof(type) / sizeof(u8) );
}


#endif		// asm_funcs_hpp
