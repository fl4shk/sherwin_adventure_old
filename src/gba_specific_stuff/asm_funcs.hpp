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


#ifndef asm_funcs_hpp
#define asm_funcs_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "attribute_defines.hpp"

#define ASM_COMMENT( stuff ) \
	asm volatile( "@ ---" stuff " ---" )

#include <array>

extern "C"
{

// These two functions should now be much faster, and I Can feel free To
// allocate more stuffs on the stack!
void* memcpy( void* dst, const void* src, size_t n )
	__attribute__((_IWRAM_CODE,_TARGET_ARM));
void* memset( void* dst, int c, size_t n )
	__attribute__((_IWRAM_CODE,_TARGET_ARM));


// This function Is used by crt0.s
void* slower_memcpy( void* dst, const void* src, size_t n );


// memcpy32 Is from TONC
extern void memcpy32( void* dst, const void* src, u32 wordcount );

// memfill32 Is a modified version of memcpy32 To fill an array with a
// constant word.
extern void memfill32( void* dst, u32 src, u32 wordcount );



extern void memcpy8( void* dst, const void* src, u32 bytecount );
extern void memfill8( void* dst, u32 src, u32 bytecount );

}

// A bunch of wrappers
inline void memcpy32( volatile void* dst, const void* src, 
	u32 wordcount )
{
	memcpy32( (void*)dst, src, wordcount );
}

inline void memfill32( volatile void* dst, u32 src, u32 wordcount )
{
	memfill32( (void*)dst, src, wordcount );
}




inline void memcpy8( volatile void* dst, const void* src, u32 bytecount )
{
	memcpy8( (void*)dst, src, bytecount );
}
inline void memfill8( volatile void* dst, u32 src, u32 bytecount )
{
	memfill8( (void*)dst, (src & 0xff), bytecount );
}




// arr_mem*() with raw arrays
template< typename type >
inline void arr_memcpy32( type* dst, const void* src, u32 num_elems )
{
	memcpy32( (void*)dst, (const void*)src, num_elems * sizeof(type) 
		/ sizeof(u32) );
}
template< typename type >
inline void arr_memfill32( type* dst, u32 src, u32 num_elems )
{
	memfill32( (void*)dst, src, num_elems * sizeof(type) / sizeof(u32) );
}

template< typename type >
inline void arr_memcpy8( type* dst, const void* src, u32 num_elems )
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
inline void* arr_memcpy( type* dst, const void* src, u32 num_elems )
{
	return memcpy( (void*)dst, src, num_elems * sizeof(type) / sizeof(u8) );
}
template< typename type >
inline void* arr_memset( type* dst, int c, u32 num_elems )
{
	return memset( (void*)dst, c, num_elems * sizeof(type) / sizeof(u8) );
}





template< typename dst_type, typename src_type, size_t size >
inline void arr_memcpy32( std::array< dst_type, size >& dst, 
	std::array< src_type, size >& src )
{
	arr_memcpy32<dst_type>( dst.data(), src.data(), size );
}
template< typename type, size_t size >
inline void arr_memcpy32( std::array< type, size >& dst, const void* src )
{
	arr_memcpy32<type>( dst.data(), src, size );
}
template< typename type, size_t size >
inline void arr_memfill32( std::array< type, size >& dst, u32 src )
{
	arr_memfill32<type>( static_cast<type*>(dst.data()), src, size );
}


template< typename dst_type, typename src_type, size_t size >
inline void arr_memcpy8( std::array< dst_type, size >& dst, 
	std::array< src_type, size >& src )
{
	arr_memcpy8<dst_type>( dst.data(), src.data(), size );
}
template< typename type, size_t size >
inline void arr_memcpy8( std::array< type, size >& dst, const void* src )
{
	arr_memcpy8<type>( dst.data(), src, size );
}
template< typename type, size_t size >
inline void arr_memfill8( std::array< type, size >& dst, u32 src )
{
	arr_memfill8<type>( dst.data(), src, size );
}



template< typename dst_type, typename src_type, size_t size >
inline void* arr_memcpy( std::array< dst_type, size >& dst, 
	std::array< src_type, size >& src )
{
	return arr_memcpy<dst_type>( dst.data(), src.data(), size );
}
template< typename type, size_t size >
inline void* arr_memcpy( std::array< type, size >& dst, const void* src )
{
	return arr_memcpy<type>( dst.data(), src, size );
}
template< typename type, size_t size >
inline void* arr_memset( std::array< type, size >& dst, u32 src )
{
	return arr_memset<type>( dst.data(), src, size );
}




// Some inline template functions Intended for use with SRAM
template< typename type >
inline void single_memcpy8( u8* dst, const type& to_write )
{
	memcpy8( dst, &to_write, sizeof(type) );
}

template< typename type >
inline void single_write_as_bytes( u8* dst, const type& to_write )
{
	const u8* src = reinterpret_cast<const u8*>(&to_write);
	
	for ( s32 i=sizeof(type)-1; i>=0; --i )
	{
		dst[i] = src[i];
	}
}


template< typename type >
inline void single_memcpy8( u8* dst_start, size_t type_offset, 
	const type& to_write )
{
	u8* dst = &(dst_start[type_offset * sizeof(type)]);
	
	memcpy8( dst, &to_write, sizeof(type) );
}

template< typename type >
inline void single_write_as_bytes( u8* dst_start, size_t type_offset, 
	const type& to_write )
{
	u8* dst = &(dst_start[type_offset * sizeof(type)]);
	const u8* src = reinterpret_cast<const u8*>(&to_write);
	
	for ( s32 i=sizeof(type)-1; i>=0; --i )
	{
		dst[i] = src[i];
	}
}


template< typename type >
inline void struct_memcpy32( type& dst, const type& src )
{
	memcpy32( &dst, &src, sizeof(type) / sizeof(u32) );
}
template< typename type >
inline void struct_memcpy8( type& dst, const type& src )
{
	memcpy8( &dst, &src, sizeof(type) );
}
template< typename type >
inline void* struct_memcpy( type& dst, const type& src )
{
	return memcpy( &dst, &src, sizeof(type) );
}





#endif		// asm_funcs_hpp
