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


#ifndef gba_specific_stuff__slash__lut_division_funcs_hpp
#define gba_specific_stuff__slash__lut_division_funcs_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "attribute_defines.hpp"

#include "../namespace_using.hpp"

namespace sherwin_adventure
{

namespace gba
{
[[_iwram_code,_target_arm]]
u64 unsafe_lut_udiv(u32 numerator, u16 divisor);

[[_iwram_code,_target_arm]]
s64 unsafe_lut_sdiv(s32 numerator, s16 divisor);

[[_iwram_code,_target_arm]]
u64 safe_lut_udiv(u32 numerator, u16 divisor, int& valid);

[[_iwram_code,_target_arm]]
s64 safe_lut_sdiv(s32 numerator, s16 divisor, int& valid);



}

}

extern "C"
{

extern const u32 udiv_table[];
extern const s32 sdiv_table[];

}

#endif		// gba_specific_stuff__slash__lut_division_funcs_hpp
