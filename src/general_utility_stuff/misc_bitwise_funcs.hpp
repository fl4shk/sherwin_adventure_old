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


#ifndef general_utility_stuff__slash__misc_bitwise_funcs_hpp
#define general_utility_stuff__slash__misc_bitwise_funcs_hpp

#include "misc_defines.hpp"

namespace sherwin_adventure
{

namespace bitwise
{

template<typename Type>
inline void clear_bits(Type& to_clear, size_t mask)
{
	to_clear &= ~mask;
}

template<typename Type>
inline void set_bits(Type& to_set, size_t mask)
{
	to_set |= mask;
}

template<typename Type>
inline constexpr Type get_bits(Type to_get_from, size_t mask, 
	size_t shift=0)
{
	return ((to_get_from & mask) >> shift);
}

template<typename Type>
inline constexpr Type get_bits_with_range(Type to_get_from, 
	size_t bit_pos_range_hi, size_t bit_pos_range_lo)
{
	return get_bits(to_get_from, 
		bprange_to_shifted_mask(bit_pos_range_hi, bit_pos_range_lo),
		bit_pos_range_lo);
}


template<typename Type>
inline void clear_and_set_bits(Type& to_change, size_t clear_mask,
	size_t set_mask)
{
	to_change &= ~clear_mask;
	to_change |= set_mask;
}

template<typename Type>
inline void clear_and_set_bits_with_range(Type& to_change, size_t val,
	size_t bit_pos_range_hi, size_t bit_pos_range_lo)
{
	clear_and_set_bits(to_change, 
		bprange_to_shifted_mask(bit_pos_range_hi, bit_pos_range_lo), 
		((val & bprange_to_mask(bit_pos_range_hi, bit_pos_range_lo))
		<< bit_pos_range_lo));
}

}

}



#endif		// general_utility_stuff__slash__misc_bitwise_funcs_hpp
