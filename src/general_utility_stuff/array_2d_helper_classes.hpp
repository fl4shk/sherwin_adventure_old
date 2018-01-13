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


#ifndef general_utility_stuff__slash__array_2d_helper_classes_hpp
#define general_utility_stuff__slash__array_2d_helper_classes_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "vec2_class.hpp"



namespace sherwin_adventure
{

namespace containers
{

// This utility class is intended to be used when inherently 2D data, with
// CONSTANT dimensions (as is usually the case in my GBA code), is stored
// within a 1D array.
template<typename Type, size_t _width, size_t _height>
class _alignas_regular ArrayCsz2dHelper
{
protected:		// variables
	static constexpr Vec2<size_t> __size_2d = {_width, _height};
	static constexpr size_t __size = __size_2d.x * __size_2d.y;

//public:			// variables
	Type* __arr = nullptr;

public:			// functions
	inline ArrayCsz2dHelper()
	{
	}
	inline ArrayCsz2dHelper(Type* s___arr)
		: __arr(s___arr)
	{
	}
	inline ArrayCsz2dHelper(const ArrayCsz2dHelper& to_copy) = default;

	void init(Type* s___arr)
	{
		__arr = s___arr;
	}

	ArrayCsz2dHelper& operator = (const ArrayCsz2dHelper& to_copy) 
		= default;


	Type* arr() const
	{
		return __arr;
	}

	size_t width() const
	{
		return __size_2d.x;
	}
	size_t height() const
	{
		return __size_2d.y;
	}

	const Vec2<size_t>& size_2d() const
	{
		return __size_2d;
	}
	size_t size() const
	{
		return __size;
	}

	Type& at(size_t x, size_t y)
	{
		return __arr[y * __size_2d.x + x];
	}
	Type& at(const Vec2<size_t>& offset_2d)
	{
		return __arr[offset_2d.y * __size_2d.x + offset_2d.x];
	}
	Type& at(const Vec2S32& offset_2d)
	{
		return __arr[offset_2d.y * __size_2d.x + offset_2d.x];
	}


	const Type& at(size_t x, size_t y) const
	{
		return __arr[y * __size_2d.x + x];
	}
	const Type& at(const Vec2<size_t>& offset_2d) const
	{
		return __arr[offset_2d.y * __size_2d.x + offset_2d.x];
	}
	const Type& at(const Vec2S32& offset_2d) const
	{
		return __arr[offset_2d.y * __size_2d.x + offset_2d.x];
	}



};

// This utility class is intended to be used when inherently 2D data is
// stored within a 1D array.
template<typename Type>
class _alignas_regular Array2dHelper
{
protected:		// variables
	Vec2<size_t> __size_2d;
	size_t __size = 0;

//public:			// variables
	Type* __arr = nullptr;

public:			// functions
	//Array2dHelper() : __size_2d({ 0, 0 }), __size(0), __arr(0)
	//{
	//}
	inline Array2dHelper()
	{
	}
	inline Array2dHelper(Type* s___arr, 
		const Vec2<size_t>& s_size_2d)
		: __size_2d(s_size_2d), __size(s_size_2d.x * s_size_2d.y),
		__arr(s___arr)
	{
	}
	inline Array2dHelper(const Array2dHelper& to_copy) = default;

	void init(Type* s___arr, const Vec2<size_t>& s_size_2d)
	{
		__size_2d = s_size_2d;
		__size = __size_2d.x * __size_2d.y;
		__arr = s___arr;
	}

	Array2dHelper& operator = (const Array2dHelper& to_copy) = default;


	Type* arr() const
	{
		return __arr;
	}

	size_t width() const
	{
		return __size_2d.x;
	}
	size_t height() const
	{
		return __size_2d.y;
	}

	const Vec2<size_t>& size_2d() const
	{
		return __size_2d;
	}
	size_t size() const
	{
		return __size;
	}

	Type& at(size_t x, size_t y)
	{
		return __arr[y * __size_2d.x + x];
	}
	Type& at(const Vec2<size_t>& offset_2d)
	{
		return __arr[offset_2d.y * __size_2d.x + offset_2d.x];
	}
	Type& at(const Vec2S32& offset_2d)
	{
		return __arr[offset_2d.y * __size_2d.x + offset_2d.x];
	}


	const Type& at(size_t x, size_t y) const
	{
		return __arr[y * __size_2d.x + x];
	}
	const Type& at(const Vec2<size_t>& offset_2d) const
	{
		return __arr[offset_2d.y * __size_2d.x + offset_2d.x];
	}
	const Type& at(const Vec2S32& offset_2d) const
	{
		return __arr[offset_2d.y * __size_2d.x + offset_2d.x];
	}



};


}


}



#endif		// general_utility_stuff__slash__array_2d_helper_classes_hpp
