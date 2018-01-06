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


#ifndef general_utility_stuff__slash__misc_defines_hpp
#define general_utility_stuff__slash__misc_defines_hpp


#define width_to_msb_pos(some_width) (some_width - 1)
#define bprange_to_mask(bit_pos_hi, bit_pos_lo) \
	((1 << (bit_pos_hi - bit_pos_lo + 1)) - 1)
#define bprange_to_shifted_mask(bit_pos_hi, bit_pos_lo) \
	(((1 << (bit_pos_hi - bit_pos_lo + 1)) - 1) << bit_pos_lo)

#define asm_comment(stuff) \
	asm volatile("//@ ---" stuff " ---")

#endif		// general_utility_stuff__slash__misc_defines_hpp
