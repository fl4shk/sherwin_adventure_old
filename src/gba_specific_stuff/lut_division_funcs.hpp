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


#ifndef lut_division_funcs_hpp
#define lut_division_funcs_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "attribute_defines.hpp"

u64 unsafe_lut_udiv( u32 numerator, u16 divisor )
	__attribute__((_IWRAM_CODE,_TARGET_ARM));
s64 unsafe_lut_sdiv( s32 numerator, s16 divisor )
	__attribute__((_IWRAM_CODE,_TARGET_ARM));
u64 safe_lut_udiv( u32 numerator, u16 divisor, int& valid ) 
	__attribute__((_IWRAM_CODE,_TARGET_ARM));
s64 safe_lut_sdiv( s32 numerator, s16 divisor, int& valid ) 
	__attribute__((_IWRAM_CODE,_TARGET_ARM));


extern const u32 udiv_table[];
extern const s32 sdiv_table[];

#endif		// lut_division_funcs_hpp
