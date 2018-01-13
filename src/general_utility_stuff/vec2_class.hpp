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


#ifndef general_utility_stuff__slash__vec2_class_hpp
#define general_utility_stuff__slash__vec2_class_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "fixed_classes.hpp"
#include "misc_utility_funcs.hpp"

#include <utility>

#include "../namespace_using.hpp"

static constexpr size_t vec2_index_for_x = 0, vec2_index_for_y = 1;

namespace sherwin_adventure
{

namespace containers
{

template<typename Type>
class _alignas_regular Vec2
{
//public:		// constants
//	static constexpr size_t the_index_for_x = 0, the_index_for_y = 1;
//
public:		// variables
	Type x, y;

public:		// functions
	constexpr inline Vec2() : x(Type()), y(Type())
	{
	}

	//inline Vec2(const Type& s_x, const Type& s_y) : x(s_x), y(s_y)
	//{
	//}
	//
	//inline Vec2(const Vec2<Type>& to_copy) : x(to_copy.x), y(to_copy.y)
	//{
	//}



	template<typename type_1, typename type_2>
	constexpr inline Vec2(const type_1& s_x, const type_2& s_y)
		: x(s_x), y(s_y)
	{
	}
	template<typename other_type>
	constexpr inline Vec2(const Vec2<other_type>& to_copy)
		: x(to_copy.x), y(to_copy.y)
	{
	}
	template<typename other_type>
	constexpr inline Vec2(Vec2<other_type>&& to_move)
		: x(std::move(to_move.x)), y(std::move(to_move.y))
	{
	}


	template<typename other_type>
	inline Vec2<Type>& operator = (const Vec2<other_type>& to_copy)
	{
		x = to_copy.x;
		y = to_copy.y;

		return *this;
	}
	template<typename other_type>
	inline Vec2<Type>& operator = (Vec2<other_type>&& to_move)
	{
		x = std::move(to_move.x);
		y = std::move(to_move.y);

		return *this;
	}


	template<typename other_type>
	inline Vec2<Type> operator + (const Vec2<other_type>& to_add) const
	{
		return Vec2<Type>(x + to_add.x, y + to_add.y);
	}
	template<typename other_type>
	inline Vec2<Type> operator - (const Vec2<other_type>& to_sub) const
	{
		return Vec2<Type>(x - to_sub.x, y - to_sub.y);
	}

	template<typename other_type>
	inline Vec2<Type> operator * (const other_type& scale) const
	{
		return Vec2<Type>(x * scale, y * scale);
	}

	template<typename other_type>
	inline Type dot(const Vec2<other_type>& to_cross) const
	{
		const Type ret = (x * to_cross.x) + (y * to_cross.y);
		return ret;
	}
	template<typename other_type>
	inline Type zcross(const Vec2<other_type>& to_cross) const
	{
		const Type ret = (x * to_cross.y) - (y * to_cross.x);
		return ret;
	}

	template<typename other_type>
	inline Vec2<Type>& operator += (const Vec2<other_type>& to_add)
	{
		x += to_add.x;
		y += to_add.y;
		return *this;
	}
	template<typename other_type>
	inline Vec2<Type>& operator -= (const Vec2<other_type>& to_sub)
	{
		x -= to_sub.x;
		y -= to_sub.y;
		return *this;
	}

	template<typename other_type>
	inline Vec2<Type>& operator *= (const other_type& scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}


	// Comparison Operator Overloads
	template<typename other_type>
	inline bool operator == (const Vec2<other_type>& to_cmp) const
	{
		return ((x == to_cmp.x) && (y == to_cmp.y));
	}

	template<typename other_type>
	inline bool operator != (const Vec2<other_type>& to_cmp) const
	{
		return ((x != to_cmp.x) || (y != to_cmp.y));
	}


	template<typename other_type>
	inline operator Vec2<other_type>() const
	{
		return Vec2<other_type>(x, y);
	}

	inline Type& operator [] (size_t index)
	{
		if (index == vec2_index_for_x)
		{
			return x;
		}
		else //if (index != vec2_index_for_x)
		{
			return y;
		}
	}

	inline const Type& operator [] (size_t index) const
	{
		if (index == vec2_index_for_x)
		{
			return x;
		}
		else //if (index != vec2_index_for_x)
		{
			return y;
		}
	}

};




template<typename Type>
inline Vec2<Type> operator * (const Type& scale, 
	const Vec2<Type>& vec2_to_mul)
{
	return vec2_to_mul * scale;
}


typedef Vec2<u16> Vec2U16; typedef Vec2<s16> Vec2S16;
typedef Vec2<u32> Vec2U32; typedef Vec2<s32> Vec2S32;
typedef Vec2<u64> Vec2U64; typedef Vec2<s64> Vec2S64;


#define GENERATE_SPECIFIC_VEC2_CLASS_CONTENTS(specific_type) \
public:		/* variables */ \
	specific_type x, y; \
	\
public:		/* functions */ \
	constexpr inline Vec2() : x(specific_type()), y(specific_type()) \
	{ \
	} \
	\
	constexpr inline Vec2(const specific_type& s_x, \
		const specific_type& s_y) : x(s_x), y(s_y) \
	{ \
	} \
	constexpr inline Vec2(const Vec2& to_copy) \
		: x(to_copy.x), y(to_copy.y) \
	{ \
	} \
	constexpr inline Vec2(Vec2&& to_move) \
		: x(std::move(to_move.x)), y(std::move(to_move.y)) \
	{ \
	} \
	\
	inline Vec2& operator = \
		(const Vec2& to_copy) \
	{ \
		x = to_copy.x; \
		y = to_copy.y; \
		\
		return *this; \
	} \
	inline Vec2& operator = \
		(Vec2&& to_move) \
	{ \
		x = std::move(to_move.x); \
		y = std::move(to_move.y); \
		\
		return *this; \
	} \
	\
	inline Vec2 operator + \
		(const Vec2& to_add) const \
	{ \
		return Vec2(x + to_add.x, y + to_add.y); \
	} \
	inline Vec2 operator - \
		(const Vec2& to_sub) const \
	{ \
		return Vec2(x - to_sub.x, y - to_sub.y); \
	} \
	\
	template<typename other_type> \
	inline Vec2 operator * (const other_type& scale) \
		const \
	{ \
		return Vec2(x * scale, y * scale); \
	} \
	\
	template<typename other_type> \
	inline specific_type dot(const Vec2<other_type>& to_cross) const \
	{ \
		const specific_type ret = (x * to_cross.x) \
			+ (y * to_cross.y); \
		return ret; \
	} \
	template<typename other_type> \
	inline specific_type zcross(const Vec2<other_type>& to_cross) const \
	{ \
		const specific_type ret = (x * to_cross.y) \
			- (y * to_cross.x); \
		return ret; \
	} \
	inline Vec2& operator += \
		(const Vec2& to_add) \
	{ \
		x += to_add.x; \
		y += to_add.y; \
		\
		return *this; \
	} \
	inline Vec2& operator -= \
		(const Vec2& to_sub) \
	{ \
		x -= to_sub.x; \
		y -= to_sub.y; \
		\
		return *this; \
	} \
	\
	template<typename other_type> \
	inline Vec2& operator *= (const other_type& scale) \
	{ \
		x *= scale; \
		y *= scale; \
		\
		return *this; \
	} \
	\
	/* Comparison Operator Overloads */ \
	inline bool operator == (const Vec2& to_cmp) const \
	{ \
		return ((x == to_cmp.x) && (y == to_cmp.y)); \
	} \
	\
	inline bool operator != (const Vec2& to_cmp) const \
	{ \
		return ((x != to_cmp.x) || (y != to_cmp.y)); \
	} \
	\
	template<typename other_type> \
	inline operator Vec2<other_type>() const \
	{ \
		return Vec2<other_type>(x, y); \
	} \
	\
	inline specific_type& operator [] (size_t index) \
	{ \
		if (index == vec2_index_for_x) \
		{ \
			return x; \
		} \
		else /* if (index != vec2_index_for_x) */ \
		{ \
			return y; \
		} \
	} \
	\
	inline const specific_type& operator [] (size_t index) const \
	{ \
		if (index == vec2_index_for_x) \
		{ \
			return x; \
		} \
		else /* if (index != vec2_index_for_x) */ \
		{ \
			return y; \
		} \
	} \


template<>
class _alignas_regular Vec2<Fixed24p8>
{
GENERATE_SPECIFIC_VEC2_CLASS_CONTENTS(Fixed24p8)
};

template<>
class _alignas_regular Vec2<Fixed8p8>
{
GENERATE_SPECIFIC_VEC2_CLASS_CONTENTS(Fixed8p8)
};

typedef Vec2<Fixed24p8> Vec2F24p8;
typedef Vec2<Fixed8p8> Vec2F8p8;



//template<>
//inline Vec2<Fixed8p8>::operator Vec2<Fixed24p8>() const
//{
//	return { (Fixed24p8)x, (Fixed24p8)y };
//}





inline Vec2F24p8 operator + (const Vec2F8p8&a, const Vec2F24p8& b)
{
	return { a.x + b.x, a.y + b.y };
}


inline Vec2F24p8 operator - (const Vec2F8p8&a, const Vec2F24p8& b)
{
	return { a.x - b.x, a.y - b.y };
}

//template<>
//inline Vec2<s32>::operator Vec2<Fixed24p8>() const
//{
//	return { {x}, {y} };
//}

template<typename Type>
inline Vec2<Type> custom_abs(const Vec2<Type>& val)
{
	return Vec2<Type>(custom_abs(val.x), custom_abs(val.y));
}


// These are not actually hacks because the specific Vec2's contain plain
// old data.
inline Vec2S16& copy_vec2_s16_via_ptr(Vec2S16& to_assign, 
	const Vec2S16& to_copy)
{
	*reinterpret_cast<u32*>(&to_assign)
		= *reinterpret_cast<const u32*>(&to_copy);

	return to_assign;
}
inline Vec2U16& copy_Vec2U16_via_ptr(Vec2U16& to_assign, 
	const Vec2U16& to_copy)
{
	*reinterpret_cast<u32*>(&to_assign)
		= *reinterpret_cast<const u32*>(&to_copy);

	return to_assign;
}

}

}



#endif		// general_utility_stuff__slash__vec2_class_hpp
