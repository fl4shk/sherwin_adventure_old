// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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


#ifndef stack_classes_hpp
#define stack_classes_hpp

#include "../misc_includes.hpp"
#include "array_helper_classes.hpp"

#include <array>


namespace sherwin_adventure
{
namespace containers
{

template<typename Type, size_t __size>
class SaStack
{
protected:		// variables
	std::array<Type, __size> __arr;
	size_t __next_index = 0;

public:		// functions
	inline SaStack() : __next_index(0)
	{
	}

	gen_getter_by_con_ref(arr);
	gen_getter_by_val(next_index);

	inline auto size() const
	{
		return arr().size();
	}


	void push(const Type& to_push)
	{
		arr().at(__next_index++) = to_push;
	}

	void pop()
	{
		--__next_index;
	}

	//inline Type peek_top()
	//{
	//	return arr().at(__next_index - 1);
	//}
	inline const Type& peek_top() const
	{
		return arr().at(__next_index - 1);
	}

	inline const Type& peek_top_and_pop()
	{
		const Type& ret = peek_top();

		// pop() doesn't actually destroy the instance, so this is safe?
		pop();

		return ret;
	}

	inline bool can_push() const
	{
		return (next_index() <= size());
	}

	inline bool can_pop() const
	{
		return (next_index() > 0);
	}

protected:		// functions
	gen_getter_by_ref(arr);

} __attribute__((_align4));


template<typename Type>
class ExtAllocStack : public ArrayHelper<Type>
{
public:		// typedefs
	typedef ArrayHelper<Type> Base;

protected:		// variables
	size_t __next_index = 0;

public:		// functions
	inline ExtAllocStack() : __next_index(0)
	{
	}

	inline ExtAllocStack(Type* s_arr, size_t s_size)
		: Base(s_arr, s_size), __next_index(0)
	{
	}

	// No copying allowed
	inline ExtAllocStack(const ExtAllocStack& to_copy) = delete;

	inline void init(Type* s_arr, size_t s_size)
	{
		Base::init(s_arr, s_size);
		__next_index = 0;
	}

	// No copying allowed
	inline ExtAllocStack& operator = (const ExtAllocStack& to_copy)
		 = delete;

	gen_getter_by_val(next_index);

	void push(const Type& to_push)
	{
		Base::at(__next_index++) = to_push;
	}

	void pop()
	{
		--__next_index;
	}

	//inline Type peek_top()
	//{
	//	return Base::at(__next_index - 1);
	//}
	inline const Type& peek_top() const
	{
		return Base::at(__next_index - 1);
	}

	inline const Type& peek_top_and_pop()
	{
		const Type& ret = peek_top();

		// pop() doesn't actually destroy the instance, so this is safe?
		pop();

		return ret;
	}

	inline bool can_push() const
	{
		return (next_index() <= Base::size());
	}

	inline bool can_pop() const
	{
		return (next_index() > 0);
	}

} __attribute__((_align4));



template<size_t __size>
class SaFreeList : public SaStack<s16, __size>
{
public:		// typedefs
	typedef SaStack<s16, __size> Base;

public:		// functions
	SaFreeList() __attribute__((noinline))
	{
		for (size_t i=0; i<Base::size(); ++i)
		{
			Base::push(i);
		}
	}

} __attribute__((_align4));



class ExtAllocFreeList : public ExtAllocStack<s16>
{
public:		// typedefs
	typedef ExtAllocStack<s16> Base;

public:		// functions
	inline ExtAllocFreeList()
	{
	}

	inline ExtAllocFreeList(s16* s_arr, size_t s_size)
		: Base(s_arr, s_size)
	{
		init();
	}

	// No copying allowed
	inline ExtAllocFreeList(const ExtAllocFreeList& to_copy) = delete;

	void init() __attribute__((noinline))
	{
		__next_index = 0;
		for (size_t i=0; i<Base::size(); ++i)
		{
			Base::push(i);
		}
	}

	// No copying allowed
	inline ExtAllocFreeList operator = (const ExtAllocFreeList& to_copy) 
		= delete;


} __attribute__((_align4));

}
}


#endif		// stack_classes_hpp