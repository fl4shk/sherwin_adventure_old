// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#include "fixed_classes.hpp"


fixed24p8 f24p8_div_by_f8p8( const fixed24p8& num, const fixed8p8& den )
{
	if ( den.data == 0 || den.data == 1 )
	{
		return {num.data};
	}
	
	s32 ret_data;
	
	bool numerator_is_negative = ( num.data < 0 );
	bool denominator_is_negative = ( den.data < 0 );
	
	s32 temp_1, temp_2;
	
	if ( numerator_is_negative )
	{
		temp_1 = -num.data;
	}
	else
	{
		temp_1 = num.data;
	}
	
	if ( denominator_is_negative )
	{
		temp_2 = -den.data;
	}
	else
	{
		temp_2 = den.data;
	}
	
	u64 udiv_output = lut_udiv( temp_1, temp_2 );
	
	//ret_data = ( udiv_output >> 24 ) * ( numerator_is_negative ? -1 : 1 )
	//	* ( denominator_is_negative ? -1 : 1 );
	
	ret_data = ( udiv_output >> 24 ) * ( numerator_is_negative ? -1 : 1 )
		* ( denominator_is_negative ? -1 : 1 );
	
	return {ret_data};
}

fixed24p8 f24p8_div_by_u16( const fixed24p8& num, u16 den )
{
	if ( den == 0 || den == 1 )
	{
		return {num.data};
	}
	
	s32 ret_data;
	
	bool numerator_is_negative = ( num.data < 0 );
	
	s32 temp_1, temp_2 = den;
	
	if ( numerator_is_negative )
	{
		temp_1 = -num.data;
	}
	else
	{
		temp_1 = num.data;
	}
	
	u64 udiv_output = lut_udiv( temp_1, (u32)temp_2 );
	
	ret_data = ( udiv_output >> 32 ) * ( numerator_is_negative ? -1 : 1 );
	
	return {ret_data};
}



