// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#include "asm_funcs.hpp"

extern "C"
{

// Note that this won't work for copying to or from SRAM.
void* memcpy( void* dst, const void* src, size_t n )
{
	//memcpy8( dst, src, n );
	
	const u32 dst_unaligned = ((u32)dst) & 0x3;
	const u32 src_unaligned = ((u32)src) & 0x3;
	
	const bool both_areas_equally_aligned = ( dst_unaligned 
		== src_unaligned );
	
	auto copy_bytes_raw = []( u8* local_dst, const u8* local_src, 
		u32 local_n ) -> void
	{
		for ( s32 i=local_n-1; i>=0; --i )
		{
			local_dst[i] = local_src[i];
		}
	};
	
	// Use FAST copies if both dst and src are aligned to 4 bytes, or both
	// dst and src are unaligned BUT have THE SAME number of unaligned
	// bytes.
	if ( !( dst_unaligned || src_unaligned ) 
		|| both_areas_equally_aligned )
	{
		void* new_dst = dst;
		void* new_src = const_cast<void*>(src);
		size_t new_n = n;
		
		
		if ( ( dst_unaligned && src_unaligned ) 
			&& both_areas_equally_aligned )
		{
			const u32 new_dst_start_addr = ( ( (u32)dst / sizeof(u32) ) 
				* sizeof(u32) ) + sizeof(u32);
			const u32 new_src_start_addr = ( ( (u32)src / sizeof(u32) ) 
				* sizeof(u32) ) + sizeof(u32);
			
			new_dst = (void*)new_dst_start_addr;
			new_src = (void*)new_src_start_addr;
			
			
			//const u32 num_unaligned_bytes = new_dst_start_addr - (u32)dst;
			const u32 num_unaligned_bytes = sizeof(u32) - dst_unaligned;
			
			if ( num_unaligned_bytes <= n )
			{
				new_n -= num_unaligned_bytes;
				
				////for ( u32 i=0; i<num_unaligned_bytes; ++i )
				//for ( s32 i=num_unaligned_bytes-1; i>=0; ++i )
				//{
				//	((u8*)dst)[i] = ((u8*)src)[i];
				//}
				
				copy_bytes_raw( (u8*)dst, (const u8*)src,
					num_unaligned_bytes );
			}
			else // if ( num_unaligned_bytes > n )
			{
				new_n = 0;
				
				////for ( u32 i=0; i<n; ++i )
				//for ( s32 i=n-1; i>=0; ++i )
				//{
				//	((u8*)dst)[i] = ((u8*)src)[i];
				//}
				
				copy_bytes_raw( (u8*)dst, (const u8*)src, n );
			}
		}
		
		const u32 num_words = new_n / sizeof(u32), 
			num_residual_bytes = new_n & 0x3;
		
		if (num_words)
		{
			memcpy32( new_dst, new_src, num_words );
		}
		
		if (num_residual_bytes)
		{
			const u32 new_dst_residual_bytes_start = ((u32)new_dst) 
				+ ( num_words * sizeof(u32) ),
				new_src_residual_bytes_start = ( (u32)new_src ) 
				+ ( num_words * sizeof(u32) );
			
			////for ( u32 i=0; i<num_residual_bytes; ++i )
			//for ( s32 i=num_residual_bytes-1; i>=0; --i )
			//{
			//	((u8*)new_dst_residual_bytes_start)[i] 
			//		= ((u8*)new_src_residual_bytes_start)[i];
			//}
			
			copy_bytes_raw( (u8*)new_dst_residual_bytes_start,
				(const u8*)new_src_residual_bytes_start, 
				num_residual_bytes );
		}
	}
	// Use SLOW copies if either dst or src are not aligned to 4 bytes,
	// with the number of unaligned bytes different.
	// Since I use aligned copies most of the time, this should be fine.
	else
	{
		//memcpy8( dst, src, n );
		
		//for ( s32 i=n-1; i>=0; ++i )
		//{
		//	((u8*)dst)[i] = ((u8*)src)[i];
		//}
		
		copy_bytes_raw( (u8*)dst, (const u8*)src, n );
	}
	
	return dst;
}



// memset() can easily be SUPER optimized because of the constant byte
void* memset( void* dst, int c, size_t n )
{
	const u32 dst_unaligned = ((u32)dst) & 0x3;
	
	const u32 to_write = ( ((u8)c) << 24 ) | ( ((u8)c) << 16 ) 
		| ( ((u8)c) << 8 ) | ( ((u8)c) << 0 );
	
	
	auto write_bytes_raw = [to_write]( u8* local_dst, u32 local_n ) -> void
	{
		//for ( s32 i=local_n-1; i>=0; --i )
		//{
		//	//local_dst[i] = local_src[i];
		//	local_dst[i] = (u8)to_write;
		//}
		
		// With the above code (and not memfill8), write_bytes_raw() caused
		// GCC, at -O3, to generate calls to memset from within memset!
		// Thus, I have replaced the above slightly more optimized loop
		// with a call to memfill8.
		memfill8( local_dst, to_write, local_n );
	};
	
	
	void* new_dst = dst;
	size_t new_n = n;
	
	if (dst_unaligned)
	{
		const u32 new_dst_start_addr = ( ( (u32)dst / sizeof(u32) ) 
			* sizeof(u32) ) + sizeof(u32);
		
		new_dst = (void*)new_dst_start_addr;
		
		
		//const u32 num_unaligned_bytes = new_dst_start_addr - (u32)dst;
		const u32 num_unaligned_bytes = sizeof(u32) - dst_unaligned;
		
		
		if ( num_unaligned_bytes <= n )
		{
			new_n -= num_unaligned_bytes;
			
			////for ( u32 i=0; i<num_unaligned_bytes; ++i )
			//for ( s32 i=num_unaligned_bytes-1; i>=0; ++i )
			//{
			//	((u8*)dst)[i] = (u8)to_write;
			//}
			write_bytes_raw( (u8*)dst, num_unaligned_bytes );
		}
		else // if ( num_unaligned_bytes > n )
		{
			new_n = 0;
			
			////for ( u32 i=0; i<n; ++i )
			//for ( s32 i=n-1; i>=0; ++i )
			//{
			//	((u8*)dst)[i] = (u8)to_write;
			//}
			write_bytes_raw( (u8*)dst, n );
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
		
		////for ( u32 i=0; i<num_residual_bytes; ++i )
		//for ( s32 i=num_residual_bytes-1; i>=0; ++i )
		//{
		//	((u8*)dst_residual_bytes_start)[i] = (u8)to_write;
		//}
		write_bytes_raw( (u8*)dst_residual_bytes_start, 
			num_residual_bytes );
	}
	
	return dst;
}

}
