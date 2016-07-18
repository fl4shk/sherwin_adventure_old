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


#include "asm_funcs.hpp"

extern "C"
{

void* memcpy( void* dst, const void* src, size_t n )
{
	//memcpy8( dst, src, n );
	
	const u32 dst_unaligned = ((u32)dst) & 0x3;
	const u32 src_unaligned = ((u32)src) & 0x3;
	
	// Use FAST copies if both dst and src are aligned to 4 bytes.  Note
	// that this won't work for copying to or from SRAM.
	if ( !( dst_unaligned || src_unaligned ) )
	{
		const u32 num_words = n / sizeof(u32), 
			num_residual_bytes = n & 0x3;
		
		if (num_words)
		{
			memcpy32( dst, src, num_words );
		}
		
		if (num_residual_bytes)
		{
			const u32 dst_residual_bytes_start = ((u32)dst) + ( num_words 
				* sizeof(u32) ),
				src_residual_bytes_start = ( (u32)src ) + ( num_words 
				* sizeof(u32) );
			
			for ( u32 i=0; i<num_residual_bytes; ++i )
			{
				((u8*)dst_residual_bytes_start)[i] 
					= ((u8*)src_residual_bytes_start)[i];
			}
		}
	}
	// Use SLOW copies if either dst or src are not aligned to 4 bytes.
	// Since I use aligned copies most of the time, this should be fine.
	else //if ( dst_unaligned || src_unaligned )
	{
		memcpy8( dst, src, n );
	}
	
	return dst;
}

// memset() can easily be SUPER optimized because of the constant byte
void* memset( void* dst, int c, size_t n )
{
	const u32 dst_unaligned = ((u32)dst) & 0x3;
	
	const u32 to_write = ( ((u8)c) << 24 ) | ( ((u8)c) << 16 ) 
		| ( ((u8)c) << 8 ) | ( ((u8)c) << 0 );
	
	
	
	void* new_dst = dst;
	size_t new_n = n;
	
	if (dst_unaligned)
	{
		const u32 new_dst_start_addr = ( ( (u32)dst / sizeof(u32) ) 
			* sizeof(u32) ) + sizeof(u32);
		
		new_dst = (void*)new_dst_start_addr;
		
		const u32 num_unaligned_bytes = new_dst_start_addr - (u32)dst;
		
		if ( num_unaligned_bytes <= n )
		{
			new_n -= num_unaligned_bytes;
			
			for ( u32 i=0; i<num_unaligned_bytes; ++i )
			{
				((u8*)dst)[i] = (u8)to_write;
			}
		}
		else // if ( num_unaligned_bytes > n )
		{
			new_n = 0;
			for ( u32 i=0; i<n; ++i )
			{
				((u8*)dst)[i] = (u8)to_write;
			}
		}
	}
	
	const u32 num_words = new_n / sizeof(u32), 
		num_residual_bytes = new_n & 0x3;
	
	if (num_words)
	{
		memfill32( new_dst, to_write, num_words );
	}
	
	if (num_residual_bytes)
	{
		const u32 dst_residual_bytes_start = ((u32)new_dst) + ( num_words
			* sizeof(u32) );
		
		for ( u32 i=0; i<num_residual_bytes; ++i )
		{
			((u8*)dst_residual_bytes_start)[i] = (u8)to_write;
		}
	}
	
	
	return dst;
}

}
