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
	static const u32 shift = 8;
	static const u32 frac_mask = 0xff;
	
	s32 data;
	
public:		// functions
	// This function does TRUE rounding
	inline s32 round_to_int() const;
	
	// This function does "regular rounding", also known as simply
	// truncating the fraction bits
	inline s32 trunc_to_int() const;
	
	//inline s32 true_round_via_trunc() const;
	//
	//inline s16 true_round_via_trunc_s16() const;
	
	inline fixed24p8 with_zero_frac_bits() const
	{
		fixed24p8 n_value = *this;
		
		if ( n_value.data < 0 )
		{
			s32 positive_n_value_data = -n_value.data;
			
			//positive_n_value_data &= ~((s32)frac_mask);
			positive_n_value_data >>= shift;
			positive_n_value_data <<= shift;
			
			n_value.data = -positive_n_value_data;
		}
		else if ( n_value.data > 0 )
		{
			//n_value.data &= ~((s32)frac_mask);
			n_value.data >>= shift;
			n_value.data <<= shift;
		}
		
		return n_value;
	}
	
	inline u8 get_frac_bits() const;
	
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
	inline fixed24p8& operator = ( s32 to_copy );
	
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


inline s32 fixed24p8::round_to_int() const
{
	return (s32)( ( data + ( 1 << ( shift - 1 ) ) ) >> shift );
}

inline s32 fixed24p8::trunc_to_int() const
{
	//if ( data < 0 )
	//{
	//	return (s32)( ( data + ( 1 << shift ) - 1 ) >> shift );
	//}
	//else
	//{
	//	return (s32)( data >> shift );
	//}
	
	if ( data < 0 )
	{
		s32 ret = -data;
		
		ret >>= shift;
		
		ret = -ret;
		
		return ret;
	}
	else
	{
		return (s32)( data >> shift );
	}
}

//inline s32 fixed24p8::true_round_via_trunc() const
//{
//	if ( get_frac_bits() >= 0x80 )
//	{
//		return trunc_to_int() + 1;
//	}
//	else
//	{
//		return trunc_to_int();
//	}
//}
//
//inline s16 fixed24p8::true_round_via_trunc_s16() const
//{
//	if ( get_frac_bits() >= 0x80 )
//	{
//		return (s16)( trunc_to_int() + 1 );
//	}
//	else
//	{
//		return (s16)(trunc_to_int());
//	}
//}


inline u8 fixed24p8::get_frac_bits() const
{
	if ( data < 0 )
	{
		u32 temp1 = (u32)(-data);
		return (u8)( temp1 & frac_mask );
	}
	else
	{
		return (u8)( data & frac_mask );
	}
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

inline fixed24p8& fixed24p8::operator = ( s32 to_copy )
{
	data = to_copy;
	return *this;
}

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
	static const u32 shift = 8;
	static const u32 frac_mask = 0xff;
	
	s16 data;
	
public:		// functions
	inline s16 round_to_int() const;
	inline s16 trunc_to_int() const;
	inline u8 get_frac_bits() const;
	
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
	
	
};


inline s16 fixed8p8::round_to_int() const
{
	return (s16)( ( data + ( 1 << ( shift - 1 ) ) ) >> 8 );
}

inline s16 fixed8p8::trunc_to_int() const
{
	//if ( data < 0 )
	//{
	//	return (s16)( ( data + ( 1 << shift ) - 1 ) >> shift );
	//}
	//else
	//{
	//	return (s16)( data >> shift );
	//}
	
	if ( data < 0 )
	{
		s16 ret = -data;
		
		ret >>= shift;
		
		ret = -ret;
		
		return ret;
	}
	else
	{
		return (s16)( data >> shift );
	}
}

inline u8 fixed8p8::get_frac_bits() const
{
	if ( data < 0 )
	{
		u16 temp1 = (u16)(-data);
		return (u8)( temp1 & frac_mask );
	}
	else
	{
		return (u8)( data & frac_mask );
	}
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

inline fixed24p8 make_f24p8( s32 whole_part, u8 frac_part=0 )
{
	s32 temp_data, ret_data;
	
	if ( whole_part < 0 )
	{
		temp_data = (-whole_part) << fixed24p8::shift;
		temp_data |= frac_part;
		
		ret_data = -temp_data;
	}
	else
	{
		temp_data = whole_part << fixed24p8::shift;
		temp_data |= frac_part;
		
		ret_data = temp_data;
	}
	
	return (fixed24p8){ ret_data };
}


inline fixed8p8 make_f8p8( s8 whole_part, u8 frac_part=0 )
{
	s16 temp_data, ret_data;
	
	if ( whole_part < 0 )
	{
		temp_data = (-whole_part) << fixed8p8::shift;
		temp_data |= frac_part;
		
		ret_data = -temp_data;
	}
	else
	{
		temp_data = whole_part << fixed8p8::shift;
		temp_data |= frac_part;
		
		ret_data = temp_data;
	}
	
	return { ret_data };
}


#endif		// fixed_classes_hpp
