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


#ifndef general_utility_stuff__slash__trigonometry_funcs_hpp
#define general_utility_stuff__slash__trigonometry_funcs_hpp

#include "fixed_classes.hpp"

extern "C"
{

static const u32 sin_table_size = 512;
extern const s16 sin_table[sin_table_size];

};


namespace sherwin_adventure
{

namespace trig
{

static const u32 trig_lut_fixed_shift = 12;

// NOTE:  theta's range Is [0, 0xffff] for [0,2π), just like the BIOS
// functions.  Also, the returned value has a fixed-point shift of 12.

// Look up a sine value
inline s32 lut_sin(u32 theta)
{
	return sin_table[(theta >> 7) & 0x1ff];
}

// Look up a cosine value
inline s32 lut_cos(u32 theta)
{
	return sin_table[((theta >> 7) + 128) & 0x1ff];
}


//x = y = 20;
//
//x += (4 * lut_cos (theta)) >> trig_lut_fixed_shift; 
//y += (4 * lut_sin (theta)) >> trig_lut_fixed_shift;


inline Fixed24p8 lut_sin_f24p8(u32 theta)
{
	return (Fixed24p8){ lut_sin(theta) 
		>> (trig_lut_fixed_shift - Fixed24p8::get_shift()) };
}

inline Fixed24p8 lut_cos_f24p8(u32 theta)
{
	return (Fixed24p8){ lut_cos(theta) 
		>> (trig_lut_fixed_shift - Fixed24p8::get_shift()) };
}


inline Fixed8p8 lut_sin_f8p8(u32 theta)
{
	return (Fixed8p8){ (s16)(lut_sin(theta) 
		>> (trig_lut_fixed_shift - Fixed8p8::shift)) };
}

inline Fixed8p8 lut_cos_f8p8(u32 theta)
{
	return (Fixed8p8){ (s16)(lut_cos(theta) 
		>> (trig_lut_fixed_shift - Fixed8p8::shift)) };
}



}

}


#endif		// general_utility_stuff__slash__trigonometry_funcs_hpp
