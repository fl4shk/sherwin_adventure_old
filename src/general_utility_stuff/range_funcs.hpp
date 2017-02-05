// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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


#ifndef range_funcs_hpp
#define range_funcs_hpp

#include "vec2_class.hpp"


// in_range and vec2_in_range are PRIMARILY intended for use with a range
// of 0 (inclusive) to size (exclusive)
template< typename type >
inline bool in_range( type range_start_inclusive, type range_end_exclusive, 
	type to_check )
{
	return ( to_check >= range_start_inclusive 
		&& to_check < range_end_exclusive );
}

template< typename type >
inline bool vec2_in_range( vec2<type> range_start_inclusive, 
	vec2<type> range_end_exclusive, vec2<type> to_check )
{
	return ( to_check.x >= range_start_inclusive.x 
		&& to_check.x < range_end_exclusive.x
		&& to_check.y >= range_start_inclusive.y 
		&& to_check.y < range_end_exclusive.y );
}


template< typename type >
inline type clamp_to_range( type range_start_inclusive, 
	type range_end_exclusive, type to_clamp )
{
	if ( to_clamp < range_start_inclusive )
	{
		//to_clamp = range_start_inclusive;
		return range_start_inclusive;
	}
	else if ( to_clamp >= range_end_exclusive )
	{
		//to_clamp = range_end_exclusive - type(1);
		return range_end_exclusive - (type)(1);
		//type ret = range_end_exclusive;
		//ret -= (type)1;
		
	}
	else
	{
		return to_clamp;
	}
}




#endif		// range_funcs_hppc
