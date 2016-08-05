// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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


#ifndef fixed_classes_hpp
#define fixed_classes_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "misc_utility_funcs.hpp"

class fixed24p8;
class fixed8p8;


//extern fixed24p8 f24p8_div_by_f8p8( const fixed24p8& num, 
//	const fixed8p8& den ) __attribute__((_iwram_code));
fixed24p8 f24p8_div_by_f8p8( const fixed24p8& num, const fixed8p8& den ) 
	__attribute__((_iwram_code));
fixed24p8 f24p8_div_by_u16( const fixed24p8& num, u16 den )
	__attribute__((_iwram_code));


// Underlying type is s32, with 8 fraction bits
// This will be the most often used fixed-point type in my GBA stuff
class fixed24p8
{
public:		// variables
	static constexpr u32 shift = 8;
	static constexpr u32 frac_mask = ( 1 << shift ) - 1;
	
	s32 data;
	
public:		// functions
	static constexpr inline u32 get_shift()
	{
		return shift;
	}
	static constexpr inline u32 get_frac_mask()
	{
		return frac_mask;
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
	
	inline fixed24p8 with_zero_frac_bits() const;
	
	inline u32 get_frac_bits() const;
	
	inline operator fixed8p8() const;
	
	
	// Arithmetic operator overloads
	
	
	inline fixed24p8 operator + ( const fixed24p8& to_add ) const;
	inline fixed24p8 operator - ( const fixed24p8& to_sub ) const;
	
	//inline fixed24p8 operator * ( const fixed24p8& to_mul ) const;
	inline fixed24p8 operator * ( const fixed8p8& to_mul ) const;
	fixed24p8 guaranteed_f24p8_by_f8p8_multiplication
		( const fixed8p8& to_mul ) __attribute__((_iwram_code));
	inline fixed24p8 operator / ( const fixed8p8& den ) const
	{
		return f24p8_div_by_f8p8( (fixed24p8){data}, den );
	}
	
	//inline fixed24p8 operator * ( u32 den ) const
	//{
	//	return {data * den};
	//}
	inline fixed24p8 operator / ( u16 den ) const
	{
		return f24p8_div_by_u16( (fixed24p8){data}, den );
	}
	
	
	inline fixed24p8& operator = ( const fixed24p8& to_copy );
	//inline fixed24p8& operator = ( s32 to_copy );
	
	inline void operator += ( const fixed24p8& to_add );
	inline void operator -= ( const fixed24p8& to_sub );
	//inline void operator *= ( const fixed24p8& to_mul );
	inline void operator *= ( const fixed8p8& to_mul );
	inline void operator /= ( const fixed8p8& den )
	{
		data = f24p8_div_by_f8p8( (fixed24p8){data}, den ).data;
	}
	
	//inline void operator *= ( u32 den )
	//{
	//	data *= den;
	//}
	inline void operator /= ( u16 den )
	{
		data = f24p8_div_by_u16( (fixed24p8){data}, den ).data;
	}
	
	
	
	
	// Comparison operator overloads
	inline bool operator == ( const fixed24p8& to_cmp ) const;
	inline bool operator != ( const fixed24p8& to_cmp ) const;
	inline bool operator < ( const fixed24p8& to_cmp ) const;
	inline bool operator > ( const fixed24p8& to_cmp ) const;
	inline bool operator <= ( const fixed24p8& to_cmp ) const;
	inline bool operator >= ( const fixed24p8& to_cmp ) const;
	
	
} __attribute__((_align4));


template<>
inline fixed24p8 custom_abs( const fixed24p8& val )
{
	return (fixed24p8){custom_abs<s32>(val.data)};
}

inline s32 fixed24p8::round_to_int() const
{
	return (s32)( ( data + ( 1 << ( shift - 1 ) ) ) >> shift );
}

inline s32 fixed24p8::floor_to_int() const
{
	//if ( data < 0 )
	//{
	//	return (s32)( ( data + ( 1 << shift ) - 1 ) >> shift );
	//}
	//else
	{
		return (s32)( data >> shift );
	}
	
	//s32 ret = custom_abs(data) >> shift;
	//
	//if ( data < 0 )
	//{
	//	ret = -ret;
	//}
	//
	//return ret;
}

//inline s32 fixed24p8::true_round_via_floor() const
//{
//	if ( get_frac_bits() >= 0x80 )
//	{
//		return floor_to_int() + 1;
//	}
//	else
//	{
//		return floor_to_int();
//	}
//}
//
//inline s16 fixed24p8::true_round_via_floor_s16() const
//{
//	if ( get_frac_bits() >= 0x80 )
//	{
//		return (s16)( floor_to_int() + 1 );
//	}
//	else
//	{
//		return (s16)(floor_to_int());
//	}
//}

inline fixed24p8 fixed24p8::with_zero_frac_bits() const
{
	fixed24p8 positive_n_value = custom_abs(*this);
	
	positive_n_value.data >>= shift;
	positive_n_value.data <<= shift;
	
	if ( data < 0 )
	{
		//n_value = -positive_n_value.data;
		return (fixed24p8){-positive_n_value.data};
	}
	return positive_n_value;
}

inline u32 fixed24p8::get_frac_bits() const
{
	//if ( data < 0 )
	//{
	//	u32 temp1 = (u32)(-data);
	//	return (u8)( temp1 & frac_mask );
	//}
	//else
	//{
	//	return (u8)( data & frac_mask );
	//}
	
	return (u8)( custom_abs(data) & frac_mask );
}



inline fixed24p8 fixed24p8::operator + ( const fixed24p8& to_add ) const
{
	return { (s32)(data + to_add.data) };
}
inline fixed24p8 fixed24p8::operator - ( const fixed24p8& to_sub ) const
{
	return { (s32)(data - to_sub.data) };
}



inline fixed24p8& fixed24p8::operator = ( const fixed24p8& to_copy )
{
	data = to_copy.data;
	return *this;
}

//inline fixed24p8& fixed24p8::operator = ( s32 to_copy )
//{
//	data = to_copy;
//	return *this;
//}

inline void fixed24p8::operator += ( const fixed24p8& to_add )
{
	data += to_add.data;
}
inline void fixed24p8::operator -= ( const fixed24p8& to_sub )
{
	data -= to_sub.data;
}





inline bool fixed24p8::operator == ( const fixed24p8& to_cmp ) const
{
	return ( data == to_cmp.data );
}
inline bool fixed24p8::operator != ( const fixed24p8& to_cmp ) const
{
	return ( data != to_cmp.data );
}
inline bool fixed24p8::operator < ( const fixed24p8& to_cmp ) const
{
	return ( data < to_cmp.data );
}
inline bool fixed24p8::operator > ( const fixed24p8& to_cmp ) const
{
	return ( data > to_cmp.data );
}
inline bool fixed24p8::operator <= ( const fixed24p8& to_cmp ) const
{
	return ( data <= to_cmp.data );
}
inline bool fixed24p8::operator >= ( const fixed24p8& to_cmp ) const
{
	return ( data >= to_cmp.data );
}





// Underlying type is s16, with 8 fraction bits
class fixed8p8
{
public:		// variables
	static constexpr u32 shift = 8;
	static constexpr u32 frac_mask = ( 1 << shift ) - 1;
	
	s16 data;
	
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
	
	inline operator fixed24p8() const;
	
	
	inline fixed8p8 operator + ( const fixed8p8& to_add ) const;
	inline fixed8p8 operator - ( const fixed8p8& to_sub ) const;
	
	
	inline fixed8p8& operator = ( const fixed8p8& to_copy );
	inline void operator += ( const fixed8p8& to_add );
	inline void operator -= ( const fixed8p8& to_sub );
	
	
	// Comparison operator overloads
	inline bool operator == ( const fixed8p8& to_cmp ) const;
	inline bool operator != ( const fixed8p8& to_cmp ) const;
	inline bool operator < ( const fixed8p8& to_cmp ) const;
	inline bool operator > ( const fixed8p8& to_cmp ) const;
	inline bool operator <= ( const fixed8p8& to_cmp ) const;
	inline bool operator >= ( const fixed8p8& to_cmp ) const;
	
	
} __attribute__((_align4));


inline s16 fixed8p8::round_to_int() const
{
	return (s16)( ( data + ( 1 << ( shift - 1 ) ) ) >> shift );
}

inline s16 fixed8p8::floor_to_int() const
{
	//if ( data < 0 )
	//{
	//	return (s16)( ( data + ( 1 << shift ) - 1 ) >> shift );
	//}
	//else
	{
		return (s16)( data >> shift );
	}
	
	
	//s16 ret = custom_abs(data) >> shift;
	//
	//if ( data < 0 )
	//{
	//	ret = -ret;
	//}
	//
	//return ret;
}

inline u32 fixed8p8::get_frac_bits() const
{
	//if ( data < 0 )
	//{
	//	u16 temp1 = (u16)(-data);
	//	return (u8)( temp1 & frac_mask );
	//}
	//else
	//{
	//	return (u8)( data & frac_mask );
	//}
	
	return (u8)( custom_abs(data) & frac_mask );
}




inline fixed8p8 fixed8p8::operator + ( const fixed8p8& to_add ) const
{
	return { (s16)(data + to_add.data) };
}
inline fixed8p8 fixed8p8::operator - ( const fixed8p8& to_sub ) const
{
	return { (s16)(data - to_sub.data) };
}


inline fixed8p8& fixed8p8::operator = ( const fixed8p8& to_copy )
{
	data = to_copy.data;
	return *this;
}
inline void fixed8p8::operator += ( const fixed8p8& to_add )
{
	data += to_add.data;
}
inline void fixed8p8::operator -= ( const fixed8p8& to_sub )
{
	data -= to_sub.data;
}

// Comparison operator overloads
inline bool fixed8p8::operator == ( const fixed8p8& to_cmp ) const
{
	return ( data == to_cmp.data );
}
inline bool fixed8p8::operator != ( const fixed8p8& to_cmp ) const
{
	return ( data != to_cmp.data );
}
inline bool fixed8p8::operator < ( const fixed8p8& to_cmp ) const
{
	return ( data < to_cmp.data );
}
inline bool fixed8p8::operator > ( const fixed8p8& to_cmp ) const
{
	return ( data > to_cmp.data );
}
inline bool fixed8p8::operator <= ( const fixed8p8& to_cmp ) const
{
	return ( data <= to_cmp.data );
}
inline bool fixed8p8::operator >= ( const fixed8p8& to_cmp ) const
{
	return ( data >= to_cmp.data );
}




inline fixed24p8::operator fixed8p8 () const
{
	if ( data < 0 )
	{
		u32 temp1 = (u32)(-data);
		u16 temp2 = temp1 & 0xffff;
		return { (s16)(-temp2) };
	}
	else
	{
		return { (s16)( data & 0xffff ) };
	}
}


inline fixed8p8::operator fixed24p8() const
{
	return { (s32)data };
}





// Fixed point multiplication, with accuracy loss.  Don't do too many of
// these in a row because errors multiply.
inline fixed24p8 operator * ( const fixed8p8& a, const fixed8p8& b )
{
	fixed24p8 ret;
	
	ret.data = a.data * b.data;
	ret.data >>= fixed24p8::shift;
	
	return ret;
}



inline fixed24p8 operator + ( const fixed8p8& a, const fixed24p8& b )
{
	return ( ((fixed24p8)a) + b );
}

inline fixed24p8 operator - ( const fixed8p8& a, const fixed24p8& b )
{
	return ( ((fixed24p8)a) - b );
}


inline void fixed24p8::operator *= ( const fixed8p8& to_mul )
{
	data *=  to_mul.data;
	data >>= fixed24p8::shift;
}



// Fixed point multiplication, with accuracy loss.  Don't do too many of
// these in a row because errors multiply.
inline fixed24p8 fixed24p8::operator * ( const fixed8p8& to_mul ) const
{
	fixed24p8 ret;
	
	ret.data = data * to_mul.data;
	ret.data >>= fixed24p8::shift;
	
	return ret;
}






inline fixed24p8 operator - ( const fixed24p8& a )
{
	return ( (fixed24p8){ -a.data } );
}

inline fixed8p8 operator - ( const fixed8p8& a )
{
	//return ( (fixed8p8){ -(s16)(a.data) } );
	s16 ret_data = -a.data;
	
	return (fixed8p8){ret_data};
}

//fixed24p8 make_f24p8( s32 whole_part, u8 frac_part=0 ) 
//	__attribute__((_iwram_code));
//
//
//fixed8p8 make_f8p8( s8 whole_part, u8 frac_part=0 ) 
//	__attribute__((_iwram_code));




template< typename underlying_type, u32 shift >
class fixedpt_num_packed
{
public:		// typedefs
	typedef fixedpt_num_packed< underlying_type, shift > 
		specific_fixedpt_type;
	
public:		// variables
	static constexpr u32 frac_mask = ( 1 << shift ) - 1;
	static constexpr u32 underlying_type_is_signed 
		= ( underlying_type(-1) < underlying_type(0) );
	
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
		return (underlying_type)( ( data + ( 1 << ( get_shift() - 1 ) ) ) 
			>> get_shift() );
	}
	inline underlying_type floor_to_int() const
	{
		return (underlying_type)( data >> get_shift() );
	}
	inline u32 get_frac_bits() const
	{
		return (u8)( custom_abs(data) & get_frac_mask() );
	}
	
	inline specific_fixedpt_type operator + 
		( const specific_fixedpt_type& to_add ) const
	{
		return (specific_fixedpt_type){ data + to_add.data };
	}
	inline specific_fixedpt_type operator - 
		( const specific_fixedpt_type& to_sub ) const
	{
		return (specific_fixedpt_type){ data - to_sub.data };
	}
	
	
	inline specific_fixedpt_type& operator = 
		( const specific_fixedpt_type& to_copy )
	{
		data = to_copy.data;
	}
	inline void operator += ( const specific_fixedpt_type& to_add )
	{
		data += to_add.data;
	}
	inline void operator -= ( const specific_fixedpt_type& to_sub )
	{
		data -= to_sub.data;
	}
	
	
	// Comparison operator overloads
	#define list_of_comparison_operators(macro) \
		macro(==) macro(!=) macro(<) macro(>) macro(<=) macro(>=)
	
	#define generate_comparison_operator_overload(specific_operator) \
	inline bool operator specific_operator \
		( const specific_fixedpt_type& to_cmp ) const \
	{ \
		return ( data specific_operator to_cmp.data ); \
	};
	
	list_of_comparison_operators(generate_comparison_operator_overload)
	
	#undef list_of_comparison_operators
	#undef generate_comparison_operator_overload
	
	
	
} __attribute__((_packed));

typedef fixedpt_num_packed< u16, 4 > fixedu12p4_packed;
typedef fixedpt_num_packed< s16, 4 > fixeds12p4_packed;
typedef fixedpt_num_packed< s16, 8 > fixeds8p8_packed;



template< typename specific_fixedpt_type >
inline specific_fixedpt_type make_signed_fixedpt_num( s32 whole_part, 
	u32 frac_part=0 )
{
	static constexpr u32 shift = specific_fixedpt_type::get_shift();
	static constexpr u32 frac_mask 
		= specific_fixedpt_type::get_frac_mask();
	
	//s32 temp_data, ret_data;
	decltype(specific_fixedpt_type::data) temp_data, ret_data;
	
	
	if ( whole_part < 0 )
	{
		temp_data = (-whole_part) << shift;
		temp_data |= ( frac_part & frac_mask );
		
		ret_data = -temp_data;
	}
	else
	{
		temp_data = whole_part << shift;
		temp_data |= ( frac_part & frac_mask );
		
		ret_data = temp_data;
	}
	
	//return reinterpret_cast<specific_fixedpt_type>({ ret_data });
	return (specific_fixedpt_type){ ret_data };
}


template< typename specific_fixedpt_type >
inline specific_fixedpt_type make_unsigned_fixedpt_num( u32 whole_part, 
	u32 frac_part=0 )
{
	static constexpr u32 shift = specific_fixedpt_type::get_shift();
	static constexpr u32 frac_mask 
		= specific_fixedpt_type::get_frac_mask();
	
	decltype(specific_fixedpt_type::data) ret_data;
	
	
	ret_data = whole_part << shift;
	ret_data |= ( frac_part & frac_mask );
	
	//return reinterpret_cast<specific_fixedpt_type>({ ret_data });
	return (specific_fixedpt_type){ ret_data };
}


inline fixed24p8 make_f24p8( s32 whole_part, u32 frac_part=0 )
{
	return make_signed_fixedpt_num<fixed24p8>( whole_part, frac_part );
}
inline fixed8p8 make_f8p8( s32 whole_part, u32 frac_part=0 )
{
	return make_signed_fixedpt_num<fixed8p8>( whole_part, frac_part );
}

inline fixedu12p4_packed make_fu12p4_packed( u32 whole_part, 
	u32 frac_part=0 )
{
	return make_unsigned_fixedpt_num<fixedu12p4_packed>( whole_part, 
		frac_part );
}
inline fixeds12p4_packed make_fs12p4_packed( s32 whole_part, 
	u32 frac_part=0 )
{
	return make_signed_fixedpt_num<fixeds12p4_packed>( whole_part, 
		frac_part );
}

inline fixeds8p8_packed make_fs8p8_packed( s32 whole_part, 
	u32 frac_part=0 )
{
	return make_signed_fixedpt_num<fixeds8p8_packed>( whole_part, 
		frac_part );
}

#endif		// fixed_classes_hpp
