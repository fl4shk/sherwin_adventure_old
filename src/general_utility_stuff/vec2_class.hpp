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
#include "misc_utility_funcs.hpp"

#include <utility>

template< typename type >
class vec2
{
public:		// constants
	static constexpr size_t the_index_for_x = 0, the_index_for_y = 1;
	
public:		// variables
	type x, y;
	
public:		// functions
	constexpr inline vec2() : x( type() ), y( type() )
	{
	}
	
	//inline vec2( const type& s_x, const type& s_y ) : x(s_x), y(s_y)
	//{
	//}
	//
	//inline vec2( const vec2<type>& to_copy ) : x(to_copy.x), y(to_copy.y)
	//{
	//}
	
	
	
	template< typename type_1, typename type_2 >
	constexpr inline vec2( const type_1& s_x, const type_2& s_y )
		: x(s_x), y(s_y)
	{
	}
	template< typename other_type >
	constexpr inline vec2( const vec2<other_type>& to_copy )
		: x(to_copy.x), y(to_copy.y)
	{
	}
	template< typename other_type >
	constexpr inline vec2( vec2<other_type>&& to_move )
		: x(std::move(to_move.x)), y(std::move(to_move.y))
	{
	}
	
	
	template< typename other_type >
	inline vec2<type>& operator = ( const vec2<other_type>& to_copy )
	{
		x = to_copy.x;
		y = to_copy.y;
		
		return *this;
	}
	template< typename other_type >
	inline vec2<type>& operator = ( vec2<other_type>&& to_move )
	{
		x = std::move(to_move.x);
		y = std::move(to_move.y);
		
		return *this;
	}
	
	
	template< typename other_type >
	inline vec2<type> operator + ( const vec2<other_type>& to_add ) const
	{
		return vec2<type> ( x + to_add.x, y + to_add.y );
	}
	template< typename other_type >
	inline vec2<type> operator - ( const vec2<other_type>& to_sub ) const
	{
		return vec2<type> ( x - to_sub.x, y - to_sub.y );
	}
	
	template< typename other_type >
	inline vec2<type> operator * ( const other_type& scale ) const
	{
		return vec2<type> ( x * scale, y * scale );
	}
	
	
	template< typename other_type >
	inline void operator += ( const vec2<other_type>& to_add )
	{
		x += to_add.x;
		y += to_add.y;
	}
	template< typename other_type >
	inline void operator -= ( const vec2<other_type>& to_sub )
	{
		x -= to_sub.x;
		y -= to_sub.y;
	}
	
	template< typename other_type >
	inline void operator *= ( const other_type& scale )
	{
		x *= scale;
		y *= scale;
	}
	
	
	// Comparison Operator Overloads
	template< typename other_type >
	inline bool operator == ( const vec2<other_type>& to_cmp ) const
	{
		return ( ( x == to_cmp.x ) && ( y == to_cmp.y ) );
	}
	
	template< typename other_type >
	inline bool operator != ( const vec2<other_type>& to_cmp ) const
	{
		return ( ( x != to_cmp.x ) || ( y != to_cmp.y ) );
	}
	
	
	template< typename other_type >
	inline operator vec2<other_type>() const
	{
		return vec2<other_type>( x, y );
	}
	
	inline type& operator [] ( size_t index )
	{
		if ( index == the_index_for_x )
		{
			return x;
		}
		else //if ( index != the_index_for_x )
		{
			return y;
		}
	}
	
	inline const type& operator [] ( size_t index ) const
	{
		if ( index == the_index_for_x )
		{
			return x;
		}
		else //if ( index != the_index_for_x )
		{
			return y;
		}
	}
	
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


#define generate_specific_vec2_class_contents( specific_type ) \
public:		/* constants */ \
	static constexpr size_t the_index_for_x = 0, the_index_for_y = 1; \
	\
public:		/* variables */ \
	specific_type x, y; \
	\
public:		/* functions */ \
	constexpr inline vec2() : x(specific_type()), y(specific_type()) \
	{ \
	} \
	\
	constexpr inline vec2( const specific_type& s_x, \
		const specific_type& s_y ) : x(s_x), y(s_y) \
	{ \
	} \
	constexpr inline vec2( const vec2<specific_type>& to_copy ) \
		: x(to_copy.x), y(to_copy.y) \
	{ \
	} \
	constexpr inline vec2( vec2<specific_type>&& to_move ) \
		: x(std::move(to_move.x)), y(std::move(to_move.y)) \
	{ \
	} \
	\
	inline vec2<specific_type>& operator = \
		( const vec2<specific_type>& to_copy ) \
	{ \
		x = to_copy.x; \
		y = to_copy.y; \
		\
		return *this; \
	} \
	inline vec2<specific_type>& operator = \
		( vec2<specific_type>&& to_move ) \
	{ \
		x = std::move(to_move.x); \
		y = std::move(to_move.y); \
		\
		return *this; \
	} \
	\
	inline vec2<specific_type> operator + \
		( const vec2<specific_type>& to_add ) const \
	{ \
		return vec2<specific_type> ( x + to_add.x, y + to_add.y ); \
	} \
	inline vec2<specific_type> operator - \
		( const vec2<specific_type>& to_sub ) const \
	{ \
		return vec2<specific_type> ( x - to_sub.x, y - to_sub.y ); \
	} \
	\
	template< typename other_type > \
	inline vec2<specific_type> operator * ( const other_type& scale ) \
		const \
	{ \
		return vec2<specific_type> ( x * scale, y * scale ); \
	} \
	\
	inline void operator += ( const vec2<specific_type>& to_add ) \
	{ \
		x += to_add.x; \
		y += to_add.y; \
	} \
	inline void operator -= ( const vec2<specific_type>& to_sub ) \
	{ \
		x -= to_sub.x; \
		y -= to_sub.y; \
	} \
	\
	template< typename other_type > \
	inline void operator *= ( const other_type& scale ) \
	{ \
		x *= scale; \
		y *= scale; \
	} \
	\
	/* Comparison Operator Overloads */ \
	inline bool operator == ( const vec2<specific_type>& to_cmp ) const \
	{ \
		return ( ( x == to_cmp.x ) && ( y == to_cmp.y ) ); \
	} \
	\
	inline bool operator != ( const vec2<specific_type>& to_cmp ) const \
	{ \
		return ( ( x != to_cmp.x ) || ( y != to_cmp.y ) ); \
	} \
	\
	template< typename other_type > \
	inline operator vec2<other_type>() const \
	{ \
		return vec2<other_type>( x, y ); \
	} \
	\
	inline specific_type& operator [] ( size_t index ) \
	{ \
		if ( index == the_index_for_x ) \
		{ \
			return x; \
		} \
		else /* if ( index != the_index_for_x ) */ \
		{ \
			return y; \
		} \
	} \
	\
	inline const specific_type& operator [] ( size_t index ) const \
	{ \
		if ( index == the_index_for_x ) \
		{ \
			return x; \
		} \
		else /* if ( index != the_index_for_x ) */ \
		{ \
			return y; \
		} \
	} \


template<>
class vec2<fixed24p8>
{
generate_specific_vec2_class_contents(fixed24p8)
} __attribute__((_align4));

template<>
class vec2<fixed8p8>
{
generate_specific_vec2_class_contents(fixed8p8)
} __attribute__((_align4));

typedef vec2<fixed24p8> vec2_f24p8;
typedef vec2<fixed8p8> vec2_f8p8;



//template<>
//inline vec2<fixed8p8>::operator vec2<fixed24p8>() const
//{
//	return { (fixed24p8)x, (fixed24p8)y };
//}





inline vec2_f24p8 operator + ( const vec2_f8p8&a, const vec2_f24p8& b )
{
	return { a.x + b.x, a.y + b.y };
}


inline vec2_f24p8 operator - ( const vec2_f8p8&a, const vec2_f24p8& b )
{
	return { a.x - b.x, a.y - b.y };
}

//template<>
//inline vec2<s32>::operator vec2<fixed24p8>() const
//{
//	return { {x}, {y} };
//}

template< typename type >
inline vec2<type> custom_abs( const vec2<type>& val )
{
	return vec2<type>( custom_abs(val.x), custom_abs(val.y) );
}


// These are not actually hacks because they contain plain old data.
inline vec2_s16& copy_vec2_s16_via_ptr( vec2_s16& to_assign, 
	const vec2_s16& to_copy )
{
	*reinterpret_cast<u32*>(&to_assign)
		= *reinterpret_cast<const u32*>(&to_copy);
	
	return to_assign;
}
inline vec2_u16& copy_vec2_u16_via_ptr( vec2_u16& to_assign, 
	const vec2_u16& to_copy )
{
	*reinterpret_cast<u32*>(&to_assign)
		= *reinterpret_cast<const u32*>(&to_copy);
	
	return to_assign;
}



#endif		// vec2_class_hpp
