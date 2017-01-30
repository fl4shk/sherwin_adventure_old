// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
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


#ifndef misc_bitwise_funcs_hpp
#define misc_bitwise_funcs_hpp

#include "misc_types.hpp"



template< typename type >
inline void clear_bits( type& to_clear, u32 mask )
{
	to_clear &= ~mask;
}

template< typename type >
inline void set_bits( type& to_set, u32 mask )
{
	to_set |= mask;
}

template< typename type >
inline constexpr type get_bits( type to_get_from, u32 mask, u32 shift=0 )
{
	return ( ( to_get_from & mask ) >> shift );
}

template< typename type >
inline void clear_and_set_bits( type& to_change, u32 clear_mask,
	u32 set_mask )
{
	to_change &= ~clear_mask;
	to_change |= set_mask;
}




#endif		// misc_bitwise_funcs_hpp
