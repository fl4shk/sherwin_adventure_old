// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andy Clark (FL4SHK).
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


#include <stdint.h>

typedef uint8_t u8; typedef int8_t s8;
typedef uint16_t u16; typedef int16_t s16;
typedef uint32_t u32; typedef int32_t s32;
typedef uint64_t u64; typedef int64_t s64;
typedef unsigned int uint;

#include <iostream>
#include <string>
#include <type_traits>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#include <stdio.h>
#include <math.h>

#define pi 3.141592653589793 

// Force writing a little-endian value
template< typename type >
size_t little_endian_fwrite( const type* to_write, size_t nmemb, 
	FILE* stream )
{
	static_assert( std::is_integral<type>(), "little_endian_fwrite() "
		" only works for integral (built-in integer) types!" );
	
	size_t ret = 0;
	
	static constexpr size_t size = sizeof(type);
	
	for ( u64 i=0; i<nmemb; ++i )
	{
		for ( u64 j=0; j<size; ++j )
		{
			u64 temp = to_write[i];
			temp >>= ( j * static_cast<u64>(8) );
			ret += fwrite( &temp, sizeof(u8), 1, stream );
		}
	}
	
	return ret;
}


void generate_sine_lut();
void generate_unsigned_one_slash_x_lut();
void generate_signed_one_slash_x_lut();

int main ()
{
	generate_sine_lut();
	generate_unsigned_one_slash_x_lut();
	generate_signed_one_slash_x_lut();
	
	return 0;
}


void generate_sine_lut()
{
	FILE* lut_file = fopen( "sine_lut_512_entries_of_4p12.bin", "wb" );
	
	//for ( uint i=0; i<512; ++i )
	for ( u64 i=0; i<512; ++i )
	{
		// This is intended to result in a LUT with 512 entries of 4.12
		// fixed-point values.  The values work for an entire circle.
		s16 ggggg = ( 1 << 12 ) * ( sin( i * ( pi / 256 ) ) );
		little_endian_fwrite( &ggggg, 1, lut_file );
		
		// Example of using this for sin(angle) where angle is in
		// [0,0xffff] domain:  
			//return (s32)( sin_lut[ ( angle >> 7 ) & 0x1ff ] );
		
		// Example of using this for cos(angle) where angle is in
		// [0,0xffff] domain:  
			 //return (s32)( sin_lut[ ( ( angle >> 7 ) + 128 ) & 0x1ff ] );
	}
	
	fclose(lut_file);
}
void generate_unsigned_one_slash_x_lut()
{
	FILE* lut_file = fopen
		( "unsigned_one_slash_x_lut_65536_entries_of_0p32.bin", "wb" );
	
	for ( u64 i=0; i<( static_cast<u64>(1) << static_cast<u64>(16) ); ++i )
	{
		const u16 temp = i;
		
		const long double temp1 = temp;
		const long double temp2 = 1.0dl / temp1;
		
		// 32 fractional bits
		const long double temp3 = ( static_cast<u64>(1) 
			<< static_cast<u64>(32) );
		const long double temp4 = temp3 * temp2;
		
		const u32 to_write = static_cast<u32>(temp4);
		little_endian_fwrite( &to_write, 1, lut_file );
	}
	
	fclose(lut_file);
}
void generate_signed_one_slash_x_lut()
{
	FILE* lut_file = fopen
		( "signed_one_slash_x_lut_65536_entries_of_0p32.bin", "wb" );
	
	for ( u64 i=0; i<( static_cast<u64>(1) << static_cast<u64>(16) ); ++i )
	{
		const s16 temp = i;
		
		const long double temp1 = temp;
		const long double temp2 = 1.0dl / temp1;
		
		// 32 fractional bits
		const long double temp3 = ( static_cast<u64>(1) 
			<< static_cast<u64>(32) );
		const long double temp4 = temp3 * temp2;
		
		const s32 to_write = static_cast<s32>(temp4);
		little_endian_fwrite( &to_write, 1, lut_file );
	}
	
	fclose(lut_file);
}

