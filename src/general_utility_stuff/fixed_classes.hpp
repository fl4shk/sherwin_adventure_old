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


#ifndef general_utility_stuff__slash__fixed_classes_hpp
#define general_utility_stuff__slash__fixed_classes_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "misc_utility_funcs.hpp"

#include "../namespace_using.hpp"
namespace sherwin_adventure
{

namespace misc_util
{


class Fixed24p8;
class Fixed8p8;


//extern [[_iwram_code]]Fixed24p8 f24p8_div_by_f8p8(const Fixed24p8& num, 
//	const Fixed8p8& den);
[[_iwram_code,_target_arm]]
Fixed24p8 f24p8_div_by_f8p8(const Fixed24p8& num, const Fixed8p8& den);

[[_iwram_code,_target_arm]]
Fixed24p8 f24p8_div_by_f24p8(const Fixed24p8& num, const Fixed24p8& den);

[[_iwram_code,_target_arm]]
Fixed24p8 f24p8_div_by_u16(const Fixed24p8& num, u16 den);


static constexpr u32 f24p8_shift = 8;
static constexpr u32 f24p8_frac_mask = (1 << f24p8_shift) - 1;

// Underlying Type Is s32, with 8 fraction bits
// This will be the most often used fixed-point Type in my GBA stuff
class _alignas_regular Fixed24p8
{
public:		// variables

	s32 data = 0;

public:		// functions
	static constexpr inline u32 get_shift()
	{
		return f24p8_shift;
	}
	static constexpr inline u32 get_frac_mask()
	{
		return f24p8_frac_mask;
	}

	// This function does TRUE rounding
	inline s32 round_to_int() const;

	inline s32 floor_to_int() const;

	//inline s32 true_round_via_floor() const;
	//
	//inline s16 true_round_via_floor_s16() const;

	inline s32 to_int_for_on_screen() const
	{
		return round_to_int();
		//return floor_to_int();
	}

	inline Fixed24p8 with_zero_frac_bits() const;

	inline u32 get_frac_bits() const;

	inline operator Fixed8p8() const;


	// Arithmetic operator overloads


	inline Fixed24p8 operator + (const Fixed24p8& to_add) const;
	inline Fixed24p8 operator - (const Fixed24p8& to_sub) const;

	//inline Fixed24p8 operator * (const Fixed24p8& to_mul) const;
	[[_iwram_code,_target_arm]]
	Fixed24p8 operator * (const Fixed24p8& to_mul) const;
	inline Fixed24p8 guaranteed_f24p8_by_f8p8_multiplication
		(const Fixed8p8& to_mul) const;
	inline Fixed24p8 operator / (const Fixed8p8& den) const
	{
		return f24p8_div_by_f8p8((Fixed24p8){data}, den);
	}
	inline Fixed24p8 operator / (const Fixed24p8& den) const
	{
		return f24p8_div_by_f24p8((Fixed24p8){data}, den);
	}

	//inline Fixed24p8 operator * (u32 den) const
	//{
	//	return {data * den};
	//}
	inline Fixed24p8 operator / (u16 den) const
	{
		return f24p8_div_by_u16((Fixed24p8){data}, den);
	}


	inline Fixed24p8& operator = (const Fixed24p8& to_copy);
	//inline Fixed24p8& operator = (s32 to_copy);

	inline Fixed24p8& operator += (const Fixed24p8& to_add);
	inline Fixed24p8& operator -= (const Fixed24p8& to_sub);
	inline Fixed24p8& operator *= (const Fixed24p8& to_mul)
	{
		*this = *this * to_mul;
		return *this;
	}
	inline Fixed24p8& operator /= (const Fixed8p8& den)
	{
		data = f24p8_div_by_f8p8((Fixed24p8){data}, den).data;
		return *this;
	}

	//inline void operator *= (u32 den)
	//{
	//	data *= den;
	//}
	inline Fixed24p8& operator /= (u16 den)
	{
		data = f24p8_div_by_u16((Fixed24p8){data}, den).data;
		return *this;
	}




	// Comparison operator overloads
	inline bool operator == (const Fixed24p8& to_cmp) const;
	inline bool operator != (const Fixed24p8& to_cmp) const;
	inline bool operator < (const Fixed24p8& to_cmp) const;
	inline bool operator > (const Fixed24p8& to_cmp) const;
	inline bool operator <= (const Fixed24p8& to_cmp) const;
	inline bool operator >= (const Fixed24p8& to_cmp) const;


};


template<>
inline Fixed24p8 custom_abs(const Fixed24p8& val)
{
	return (Fixed24p8){custom_abs<s32>(val.data)};
}

inline s32 Fixed24p8::round_to_int() const
{
	return (s32)((data + (1 << (get_shift() - 1))) >> get_shift());
}

inline s32 Fixed24p8::floor_to_int() const
{
	//if (data < 0)
	//{
	//	return (s32)((data + (1 << get_shift()) - 1) >> get_shift());
	//}
	//else
	{
		return (s32)(data >> get_shift());
	}

	//s32 ret = custom_abs(data) >> get_shift();
	//
	//if (data < 0)
	//{
	//	ret = -ret;
	//}
	//
	//return ret;
}

//inline s32 Fixed24p8::true_round_via_floor() const
//{
//	if (get_frac_bits() >= 0x80)
//	{
//		return floor_to_int() + 1;
//	}
//	else
//	{
//		return floor_to_int();
//	}
//}
//
//inline s16 Fixed24p8::true_round_via_floor_s16() const
//{
//	if (get_frac_bits() >= 0x80)
//	{
//		return (s16)(floor_to_int() + 1);
//	}
//	else
//	{
//		return (s16)(floor_to_int());
//	}
//}

inline Fixed24p8 Fixed24p8::with_zero_frac_bits() const
{
	Fixed24p8 positive_n_value = custom_abs(*this);

	positive_n_value.data >>= get_shift();
	positive_n_value.data <<= get_shift();

	if (data < 0)
	{
		//n_value = -positive_n_value.data;
		return (Fixed24p8){-positive_n_value.data};
	}
	return positive_n_value;
}

inline u32 Fixed24p8::get_frac_bits() const
{
	//if (data < 0)
	//{
	//	u32 temp1 = (u32)(-data);
	//	return (u8)(temp1 & frac_mask);
	//}
	//else
	//{
	//	return (u8)(data & frac_mask);
	//}

	return (u8)(custom_abs(data) & get_frac_mask());
}



inline Fixed24p8 Fixed24p8::operator + (const Fixed24p8& to_add) const
{
	return { (s32)(data + to_add.data) };
}
inline Fixed24p8 Fixed24p8::operator - (const Fixed24p8& to_sub) const
{
	return { (s32)(data - to_sub.data) };
}

inline Fixed24p8& Fixed24p8::operator = (const Fixed24p8& to_copy)
{
	data = to_copy.data;
	return *this;
}

//inline Fixed24p8& Fixed24p8::operator = (s32 to_copy)
//{
//	data = to_copy;
//	return *this;
//}

inline Fixed24p8& Fixed24p8::operator += (const Fixed24p8& to_add)
{
	data += to_add.data;
	return *this;
}
inline Fixed24p8& Fixed24p8::operator -= (const Fixed24p8& to_sub)
{
	data -= to_sub.data;
	return *this;
}





inline bool Fixed24p8::operator == (const Fixed24p8& to_cmp) const
{
	return (data == to_cmp.data);
}
inline bool Fixed24p8::operator != (const Fixed24p8& to_cmp) const
{
	return (data != to_cmp.data);
}
inline bool Fixed24p8::operator < (const Fixed24p8& to_cmp) const
{
	return (data < to_cmp.data);
}
inline bool Fixed24p8::operator > (const Fixed24p8& to_cmp) const
{
	return (data > to_cmp.data);
}
inline bool Fixed24p8::operator <= (const Fixed24p8& to_cmp) const
{
	return (data <= to_cmp.data);
}
inline bool Fixed24p8::operator >= (const Fixed24p8& to_cmp) const
{
	return (data >= to_cmp.data);
}





// Underlying Type Is s16, with 8 fraction bits
class _alignas_regular Fixed8p8
{
public:		// variables
	static constexpr u32 shift = 8;
	static constexpr u32 frac_mask = (1 << shift) - 1;

	s16 data = 0;

public:		// functions
	static constexpr inline u32 get_shift()
	{
		return shift;
	}
	static constexpr inline u32 get_frac_mask()
	{
		return frac_mask;
	}

	inline s16 round_to_int() const;
	inline s16 floor_to_int() const;
	inline u32 get_frac_bits() const;

	inline operator Fixed24p8() const;


	inline Fixed8p8 operator + (const Fixed8p8& to_add) const;
	inline Fixed8p8 operator - (const Fixed8p8& to_sub) const;


	inline Fixed8p8& operator = (const Fixed8p8& to_copy);
	inline Fixed8p8& operator += (const Fixed8p8& to_add);
	inline Fixed8p8& operator -= (const Fixed8p8& to_sub);


	// Comparison operator overloads
	inline bool operator == (const Fixed8p8& to_cmp) const;
	inline bool operator != (const Fixed8p8& to_cmp) const;
	inline bool operator < (const Fixed8p8& to_cmp) const;
	inline bool operator > (const Fixed8p8& to_cmp) const;
	inline bool operator <= (const Fixed8p8& to_cmp) const;
	inline bool operator >= (const Fixed8p8& to_cmp) const;


};


inline s16 Fixed8p8::round_to_int() const
{
	return (s16)((data + (1 << (shift - 1))) >> shift);
}

inline s16 Fixed8p8::floor_to_int() const
{
	//if (data < 0)
	//{
	//	return (s16)((data + (1 << shift) - 1) >> shift);
	//}
	//else
	{
		return (s16)(data >> shift);
	}


	//s16 ret = custom_abs(data) >> shift;
	//
	//if (data < 0)
	//{
	//	ret = -ret;
	//}
	//
	//return ret;
}

inline u32 Fixed8p8::get_frac_bits() const
{
	//if (data < 0)
	//{
	//	u16 temp1 = (u16)(-data);
	//	return (u8)(temp1 & frac_mask);
	//}
	//else
	//{
	//	return (u8)(data & frac_mask);
	//}

	return (u8)(custom_abs(data) & frac_mask);
}




inline Fixed8p8 Fixed8p8::operator + (const Fixed8p8& to_add) const
{
	return { (s16)(data + to_add.data) };
}
inline Fixed8p8 Fixed8p8::operator - (const Fixed8p8& to_sub) const
{
	return { (s16)(data - to_sub.data) };
}

inline Fixed24p8 Fixed24p8::guaranteed_f24p8_by_f8p8_multiplication
	(const Fixed8p8& to_mul) const
{
	return ((*this) * static_cast<Fixed24p8>(to_mul));
}



inline Fixed8p8& Fixed8p8::operator = (const Fixed8p8& to_copy)
{
	data = to_copy.data;
	return *this;
}
inline Fixed8p8& Fixed8p8::operator += (const Fixed8p8& to_add)
{
	data += to_add.data;
	return *this;
}
inline Fixed8p8& Fixed8p8::operator -= (const Fixed8p8& to_sub)
{
	data -= to_sub.data;
	return *this;
}

// Comparison operator overloads
inline bool Fixed8p8::operator == (const Fixed8p8& to_cmp) const
{
	return (data == to_cmp.data);
}
inline bool Fixed8p8::operator != (const Fixed8p8& to_cmp) const
{
	return (data != to_cmp.data);
}
inline bool Fixed8p8::operator < (const Fixed8p8& to_cmp) const
{
	return (data < to_cmp.data);
}
inline bool Fixed8p8::operator > (const Fixed8p8& to_cmp) const
{
	return (data > to_cmp.data);
}
inline bool Fixed8p8::operator <= (const Fixed8p8& to_cmp) const
{
	return (data <= to_cmp.data);
}
inline bool Fixed8p8::operator >= (const Fixed8p8& to_cmp) const
{
	return (data >= to_cmp.data);
}




inline Fixed24p8::operator Fixed8p8() const
{
	if (data < 0)
	{
		u32 temp1 = (u32)(-data);
		u16 temp2 = temp1 & 0xffff;
		return { (s16)(-temp2) };
	}
	else
	{
		return { (s16)(data & 0xffff) };
	}
}


inline Fixed8p8::operator Fixed24p8() const
{
	return { (s32)data };
}





//// Fixed point multiplication, with accuracy loss.  Don't do too many of
//// these in a row because errors multiply.
//inline Fixed24p8 operator * (const Fixed8p8& a, const Fixed8p8& b)
//{
//	Fixed24p8 ret;
//
//	ret.data = a.data * b.data;
//	ret.data >>= Fixed24p8::get_shift();
//
//	return ret;
//}



inline Fixed24p8 operator + (const Fixed8p8& a, const Fixed24p8& b)
{
	return (((Fixed24p8)a) + b);
}

inline Fixed24p8 operator - (const Fixed8p8& a, const Fixed24p8& b)
{
	return (((Fixed24p8)a) - b);
}


//inline Fixed24p8& Fixed24p8::operator *= (const Fixed8p8& to_mul)
//{
//	data *= to_mul.data;
//	data >>= Fixed24p8::get_shift();
//	return *this;
//}



//// Fixed point multiplication, with accuracy loss.  Don't do too many of
//// these in a row because errors multiply.
//inline Fixed24p8 Fixed24p8::operator * (const Fixed8p8& to_mul) const
//{
//	Fixed24p8 ret;
//
//	ret.data = data * to_mul.data;
//	ret.data >>= Fixed24p8::get_shift();
//
//	return ret;
//}






inline Fixed24p8 operator - (const Fixed24p8& a)
{
	return ((Fixed24p8){ -a.data });
}

inline Fixed8p8 operator - (const Fixed8p8& a)
{
	//return ((Fixed8p8){ -(s16)(a.data) });
	s16 ret_data = -a.data;

	return (Fixed8p8){ret_data};
}

//[[_iwram_code]]
//Fixed24p8 make_f24p8(s32 whole_part, u8 frac_part=0);
//
//[[_iwram_code]]
//Fixed8p8 make_f8p8(s8 whole_part, u8 frac_part=0);




template<typename underlying_type, u32 shift>
class [[_packed]] FixedptNumPacked
{
public:		// typedefs
	typedef FixedptNumPacked<underlying_type, shift> 
		specific_fixedpt_type;

public:		// variables
	static constexpr u32 frac_mask = (1 << shift) - 1;
	//static constexpr u32 underlying_type_is_signed 
	//	= (underlying_type(-1) < underlying_type(0));
	static constexpr u32 underlying_type_is_signed
		= type_is_signed<underlying_type>();

	underlying_type data;

public:		// functions

	static constexpr inline u32 get_shift()
	{
		return shift;
	}
	static constexpr inline u32 get_frac_mask()
	{
		return frac_mask;
	}
	static constexpr inline u32 get_underlying_type_is_signed()
	{
		return underlying_type_is_signed;
	}



	inline underlying_type round_to_int() const
	{
		return (underlying_type)((data + (1 << (get_shift() - 1))) 
			>> get_shift());
	}
	inline underlying_type floor_to_int() const
	{
		return (underlying_type)(data >> get_shift());
	}
	inline u32 get_frac_bits() const
	{
		return (u8)(custom_abs(data) & get_frac_mask());
	}

	inline specific_fixedpt_type operator + 
		(const specific_fixedpt_type& to_add) const
	{
		return (specific_fixedpt_type){ data + to_add.data };
	}
	inline specific_fixedpt_type operator - 
		(const specific_fixedpt_type& to_sub) const
	{
		return (specific_fixedpt_type){ data - to_sub.data };
	}


	inline specific_fixedpt_type& operator = 
		(const specific_fixedpt_type& to_copy)
	{
		data = to_copy.data;
		return *this;
	}
	inline specific_fixedpt_type& operator += 
		(const specific_fixedpt_type& to_add)
	{
		data += to_add.data;
		return *this;
	}
	inline specific_fixedpt_type& operator -= 
		(const specific_fixedpt_type& to_sub)
	{
		data -= to_sub.data;
		return *this;
	}


	// Comparison operator overloads
	#define LIST_OF_COMPARISON_OPERATORS(macro) \
		macro(==) macro(!=) macro(<) macro(>) macro(<=) macro(>=)

	#define GENERATE_COMPARISON_OPERATOR_OVERLOAD(specific_operator) \
	inline bool operator specific_operator \
		(const specific_fixedpt_type& to_cmp) const \
	{ \
		return (data specific_operator to_cmp.data); \
	};

	LIST_OF_COMPARISON_OPERATORS(GENERATE_COMPARISON_OPERATOR_OVERLOAD)

	#undef LIST_OF_COMPARISON_OPERATORS
	#undef GENERATE_COMPARISON_OPERATOR_OVERLOAD



};

typedef FixedptNumPacked<u16, 4> Fixedu12p4Packed;
typedef FixedptNumPacked<s16, 4> Fixeds12p4Packed;
typedef FixedptNumPacked<s16, 8> Fixeds8p8Packed;



template<typename specific_fixedpt_type>
inline specific_fixedpt_type make_signed_fixedpt_num(s32 whole_part, 
	u32 frac_part=0)
{
	static constexpr u32 shift = specific_fixedpt_type::get_shift();
	static constexpr u32 frac_mask 
		= specific_fixedpt_type::get_frac_mask();

	//s32 temp_data, ret_data;
	decltype(specific_fixedpt_type::data) temp_data, ret_data;


	if (whole_part < 0)
	{
		temp_data = (-whole_part) << shift;
		temp_data |= (frac_part & frac_mask);

		ret_data = -temp_data;
	}
	else
	{
		temp_data = whole_part << shift;
		temp_data |= (frac_part & frac_mask);

		ret_data = temp_data;
	}

	//return reinterpret_cast<specific_fixedpt_type>({ ret_data });
	return (specific_fixedpt_type){ ret_data };
}


template<typename specific_fixedpt_type>
inline specific_fixedpt_type make_unsigned_fixedpt_num(u32 whole_part, 
	u32 frac_part=0)
{
	static constexpr u32 shift = specific_fixedpt_type::get_shift();
	static constexpr u32 frac_mask 
		= specific_fixedpt_type::get_frac_mask();

	decltype(specific_fixedpt_type::data) ret_data;


	ret_data = whole_part << shift;
	ret_data |= (frac_part & frac_mask);

	//return reinterpret_cast<specific_fixedpt_type>({ ret_data });
	return (specific_fixedpt_type){ ret_data };
}


inline Fixed24p8 make_f24p8(s32 whole_part, u32 frac_part=0)
{
	return make_signed_fixedpt_num<Fixed24p8>(whole_part, frac_part);
}
inline Fixed8p8 make_f8p8(s32 whole_part, u32 frac_part=0)
{
	return make_signed_fixedpt_num<Fixed8p8>(whole_part, frac_part);
}

inline Fixedu12p4Packed make_fu12p4_packed(u32 whole_part, 
	u32 frac_part=0)
{
	return make_unsigned_fixedpt_num<Fixedu12p4Packed>(whole_part, 
		frac_part);
}
inline Fixeds12p4Packed make_fs12p4_packed(s32 whole_part, 
	u32 frac_part=0)
{
	return make_signed_fixedpt_num<Fixeds12p4Packed>(whole_part, 
		frac_part);
}

inline Fixeds8p8Packed make_fs8p8_packed(s32 whole_part, 
	u32 frac_part=0)
{
	return make_signed_fixedpt_num<Fixeds8p8Packed>(whole_part, 
		frac_part);
}

}

}

#endif		// general_utility_stuff__slash__fixed_classes_hpp
