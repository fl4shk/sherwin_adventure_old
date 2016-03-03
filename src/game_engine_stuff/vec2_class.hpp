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


#ifndef vec2_class_hpp
#define vec2_class_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "fixed_classes.hpp"


template< typename type >
class vec2
{
public:		// variables
	type x, y;
	
public:		// functions
	inline vec2()
	//	: x( type() ), y( type() )
	{
	}
	
	inline vec2( vec2<type>& to_copy )
		: x(to_copy.x), y(to_copy.y)
	{
	}
	
	
	inline vec2( type& s_x, type& s_y )
		: x(s_x), y(s_y)
	{
	}
	
	
	constexpr inline vec2( const vec2<type>& to_copy )
		: x(to_copy.x), y(to_copy.y)
	{
	}
	
	constexpr inline vec2( const type& s_x, const type& s_y )
		: x(s_x), y(s_y)
	{
	}
	
	
	inline void operator = ( const vec2<type>& to_copy )
	{
		x = to_copy.x;
		y = to_copy.y;
	}
	
	
	inline vec2<type> operator + ( const vec2<type>& to_add ) const
	{
		return vec2<type> ( x + to_add.x, y + to_add.y );
	}
	inline vec2<type> operator - ( const vec2<type>& to_sub ) const
	{
		return vec2<type> ( x - to_sub.x, y - to_sub.y );
	}
	
	inline vec2<type> operator * ( const type& scale ) const
	{
		return vec2<type> ( x * scale, y * scale );
	}
	
	
	
	inline void operator += ( const vec2<type>& to_add )
	{
		x += to_add.x;
		y += to_add.y;
	}
	inline void operator -= ( const vec2<type>& to_sub )
	{
		x -= to_sub.x;
		y -= to_sub.y;
	}
	
	inline void operator *= ( const type& scale )
	{
		x *= scale;
		y *= scale;
	}
	
	
	// Comparison Operator Overloads
	inline bool operator == ( const vec2<type>& to_cmp ) const
	{
		return ( ( x == to_cmp.x ) && ( y == to_cmp.y ) );
	}
	
	inline bool operator != ( const vec2<type>& to_cmp ) const
	{
		return ( ( x != to_cmp.x ) || ( y != to_cmp.y ) );
	}
	
	
	inline operator vec2<fixed24p8>() const;
	
} __attribute__((_align4));




template< typename type >
inline vec2<type> operator * ( const type& scale, 
	const vec2<type>& vec2_to_mul )
{
	return vec2_to_mul * scale;
}


typedef vec2<u16> vec2_u16; typedef vec2<s16> vec2_s16;
typedef vec2<u32> vec2_u32; typedef vec2<s32> vec2_s32;
typedef vec2<u64> vec2_u64; typedef vec2<s64> vec2_s64;


template<>
class vec2<fixed24p8> 
{
public:		// variables
	fixed24p8 x, y;
	
public:		// functions
	inline vec2()
	//	: x( fixed24p8() ), y( fixed24p8() )
	{
	}
	
	inline vec2( vec2<fixed24p8>& to_copy )
		: x(to_copy.x), y(to_copy.y)
	{
	}
	
	
	inline vec2( fixed24p8& s_x, fixed24p8& s_y )
		: x(s_x), y(s_y)
	{
	}
	
	//inline vec2( s32 s_x, s32 s_y )
	//{
	//	x.data = s_x;
	//	y.data = s_y;
	//}
	
	
	constexpr inline vec2( const vec2<fixed24p8>& to_copy )
		: x(to_copy.x), y(to_copy.y)
	{
	}
	
	constexpr inline vec2( const fixed24p8& s_x, const fixed24p8& s_y )
		: x(s_x), y(s_y)
	{
	}
	
	
	inline void operator = ( const vec2<fixed24p8>& to_copy )
	{
		x = to_copy.x;
		y = to_copy.y;
	}
	
	
	inline vec2<fixed24p8> operator + ( const vec2<fixed24p8>& to_add ) 
		const
	{
		return vec2<fixed24p8> ( x + to_add.x, y + to_add.y );
	}
	inline vec2<fixed24p8> operator - ( const vec2<fixed24p8>& to_sub ) 
		const
	{
		return vec2<fixed24p8> ( x - to_sub.x, y - to_sub.y );
	}
	
	inline vec2<fixed24p8> operator * ( const fixed24p8& scale ) const
	{
		return vec2<fixed24p8> ( x * scale, y * scale );
	}
	
	
	
	
	
	
	inline void operator += ( const vec2<fixed24p8>& to_add )
	{
		x += to_add.x;
		y += to_add.y;
	}
	inline void operator -= ( const vec2<fixed24p8>& to_sub )
	{
		x -= to_sub.x;
		y -= to_sub.y;
	}
	
	//inline void operator *= ( const fixed24p8& scale )
	//{
	//	x *= scale;
	//	y *= scale;
	//}
	
	
	// Comparison Operator Overloads
	inline bool operator == ( const vec2<fixed24p8>& to_cmp ) const
	{
		return ( ( x == to_cmp.x ) && ( y == to_cmp.y ) );
	}
	
	inline bool operator != ( const vec2<fixed24p8>& to_cmp ) const
	{
		return ( ( x != to_cmp.x ) || ( y != to_cmp.y ) );
	}
	
	inline void operator = ( const vec2_s32& to_copy )
	{
		x.data = to_copy.x;
		y.data = to_copy.y;
	}
	
} __attribute__((_align4));


template <>
class vec2<fixed8p8> 
{
public:		// variables
	fixed8p8 x, y;
	
public:		// functions
	inline vec2()
	//	: x( fixed8p8() ), y( fixed8p8() )
	{
	}
	
	inline vec2( vec2<fixed8p8>& to_copy )
		: x(to_copy.x), y(to_copy.y)
	{
	}
	
	
	inline vec2( fixed8p8& s_x, fixed8p8& s_y )
		: x(s_x), y(s_y)
	{
	}
	
	
	constexpr inline vec2( const vec2<fixed8p8>& to_copy )
		: x(to_copy.x), y(to_copy.y)
	{
	}
	
	constexpr inline vec2( const fixed8p8& s_x, const fixed8p8& s_y )
		: x(s_x), y(s_y)
	{
	}
	
	
	inline void operator = ( const vec2<fixed8p8>& to_copy )
	{
		x = to_copy.x;
		y = to_copy.y;
	}
	
	
	inline vec2<fixed8p8> operator + ( const vec2<fixed8p8>& to_add ) const
	{
		return vec2<fixed8p8> ( x + to_add.x, y + to_add.y );
	}
	inline vec2<fixed8p8> operator - ( const vec2<fixed8p8>& to_sub ) const
	{
		return vec2<fixed8p8> ( x - to_sub.x, y - to_sub.y );
	}
	
	inline vec2<fixed8p8> operator * ( const fixed8p8& scale ) const
	{
		return vec2<fixed8p8> ( x * scale, y * scale );
	}
	
	
	
	
	
	
	inline void operator += ( const vec2<fixed8p8>& to_add )
	{
		x += to_add.x;
		y += to_add.y;
	}
	inline void operator -= ( const vec2<fixed8p8>& to_sub )
	{
		x -= to_sub.x;
		y -= to_sub.y;
	}
	
	//inline void operator *= ( const fixed8p8& scale )
	//{
	//	x *= scale;
	//	y *= scale;
	//}
	
	
	// Comparison Operator Overloads
	inline bool operator == ( const vec2<fixed8p8>& to_cmp ) const
	{
		return ( ( x == to_cmp.x ) && ( y == to_cmp.y ) );
	}
	
	inline bool operator != ( const vec2<fixed8p8>& to_cmp ) const
	{
		return ( ( x != to_cmp.x ) || ( y != to_cmp.y ) );
	}
	
	inline void operator = ( const vec2_s16& to_copy )
	{
		x.data = to_copy.x;
		y.data = to_copy.y;
	}
	
	inline operator vec2<fixed24p8>() const;
	
} __attribute__((_align4));

inline vec2<fixed8p8>::operator vec2<fixed24p8>() const
{
	return { (fixed24p8)x, (fixed24p8)y };
}



typedef vec2<fixed24p8> vec2_f24p8;
typedef vec2<fixed8p8> vec2_f8p8;


inline vec2_f24p8 operator + ( const vec2_f8p8&a, const vec2_f24p8& b )
{
	return { a.x + b.x, a.y + b.y };
}


inline vec2_f24p8 operator - ( const vec2_f8p8&a, const vec2_f24p8& b )
{
	return { a.x - b.x, a.y - b.y };
}

template<>
inline vec2<s32>::operator vec2<fixed24p8>() const
{
	return { {x}, {y} };
}


#endif		// vec2_class_hpp
