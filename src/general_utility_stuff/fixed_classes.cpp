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

#include "fixed_classes.hpp"
#include "../gba_specific_stuff/lut_division_funcs.hpp"

using namespace gba;

namespace sherwin_adventure
{

namespace misc_util
{

Fixed24p8 Fixed24p8::operator * (const Fixed24p8& to_mul) const
{
	Fixed24p8 ret;

	s64 ret_data_s64 = (s64)data * (s64)to_mul.data;
	ret_data_s64 >>= Fixed24p8::get_shift();

	ret.data = (s32)ret_data_s64;

	return ret;

}


inline Fixed24p8 unsafe_f24p8_div_by_f8p8(const Fixed24p8& num, 
	const Fixed8p8& den)
{
	const s64 temp = static_cast<s64>(num.data);
	const s32 one_slash_den = sdiv_table[den.data];
	const s64 temp_2 = static_cast<s64>(one_slash_den);
	const s64 temp_3 = (temp * temp_2);
	//s64 temp_3 = unsafe_lut_sdiv(num.data, den.data);

	const s32 ret_data = (temp_3 >> 24);

	return {ret_data};
}


Fixed24p8 f24p8_div_by_f8p8(const Fixed24p8& num, const Fixed8p8& den)
{
	if (den.data == 0 || den.data == 1)
	{
		return {num.data};
	}

	return unsafe_f24p8_div_by_f8p8(num, den);
}

Fixed24p8 f24p8_div_by_f24p8(const Fixed24p8& num, const Fixed24p8& den)
{
	if (den.data == 0 || den.data == 1)
	{
		return {num.data};
	}

	if (custom_abs(den.data) & 0xffff0000)
	{
		//const s32 ret_data = num.data / den.data;
		const s64 ret_data = ((s64)((s64)((s64)(num.data) << 8) 
			/ (s64)den.data));

		return {static_cast<s32>(ret_data)};
	}

	return unsafe_f24p8_div_by_f8p8(num, den);
}

Fixed24p8 f24p8_div_by_u16(const Fixed24p8& num, u16 den)
{
	if (den == 0 || den == 1)
	{
		return {num.data};
	}

	s32 ret_data;

	bool numerator_is_negative = (num.data < 0);

	s32 temp_1, temp_2 = den;

	if (numerator_is_negative)
	{
		temp_1 = -num.data;
	}
	else
	{
		temp_1 = num.data;
	}

	u64 udiv_output = unsafe_lut_udiv(temp_1, (u32)temp_2);

	ret_data = (udiv_output >> 32) * (numerator_is_negative ? -1 : 1);

	return {ret_data};
}


}

}


