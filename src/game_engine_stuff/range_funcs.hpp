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


#ifndef range_funcs_hpp
#define range_funcs_hpp

#include "vec2_class.hpp"

template< typename type >
inline bool in_range( type range_start, type range_end_plus_1, 
	type to_check )
{
	return ( to_check >= range_start && to_check < range_end_plus_1 );
}

template< typename type >
inline bool vec2_in_range( vec2<type> range_start, 
	vec2<type> range_end_plus_1, vec2<type> to_check )
{
	return ( to_check.x >= range_start.x 
		&& to_check.x < range_end_plus_1.x
		&& to_check.y >= range_start.y 
		&& to_check.y < range_end_plus_1.y );
}


#endif		// range_funcs_hpp
