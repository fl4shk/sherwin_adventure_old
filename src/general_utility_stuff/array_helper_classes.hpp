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


#ifndef general_utility_stuff__slash__array_helper_classes_hpp
#define general_utility_stuff__slash__array_helper_classes_hpp



#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "misc_defines.hpp"

namespace sherwin_adventure
{

namespace containers
{

template<typename Type, size_t _size>
class _alignas_regular ArrayCszHelper
{
public:			// variables
	Type* __arr = nullptr;

protected:		// variables
	static constexpr size_t __size = _size;

public:			// functions
	ArrayCszHelper()
	{
	}

	ArrayCszHelper(Type* s_arr) : __arr(s_arr)
	{
	}

	ArrayCszHelper(const ArrayCszHelper& to_copy) = default;

	void init(Type* s_arr)
	{
		__arr = s_arr;
	}


	ArrayCszHelper& operator = 
		(const ArrayCszHelper& to_copy) = default;


	const Type* arr() const
	{
		return __arr;
	}

	size_t size() const
	{
		return __size;
	}

	Type& at(size_t offset)
	{
		return __arr[offset];
	}
	const Type& at(size_t offset) const
	{
		return __arr[offset];
	}


};



// This is a VERY thin wrapper class for working with 1D arrays of
// arbitrary sizes
template<typename Type>
class _alignas_regular ArrayHelper
{
//public:			// variables
protected:		// variables
	Type* __arr = nullptr;

protected:		// variables
	size_t __size = 0;

public:			// functions
	inline ArrayHelper()
	{
	}

	inline ArrayHelper(Type* s_arr, size_t s_size)
		: __arr(s_arr), __size(s_size)
	{
	}

	inline ArrayHelper(const ArrayHelper& to_copy) = default;

	void init(Type* s_arr, size_t s_size)
	{
		__arr = s_arr;
		__size = s_size;
	}


	inline ArrayHelper& operator = (const ArrayHelper& to_copy) = default;


	const Type* arr() const
	{
		return __arr;
	}

	size_t size() const
	{
		return __size;
	}

	Type& at(size_t offset)
	{
		return __arr[offset];
	}
	const Type& at(size_t offset) const
	{
		return __arr[offset];
	}


};

}

}


#endif		// general_utility_stuff__slash__array_helper_classes_hpp
