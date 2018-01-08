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


#ifndef gba_specific_stuff__slash__linear_allocator_classes_hpp
#define gba_specific_stuff__slash__linear_allocator_classes_hpp

#include "../misc_includes.hpp"

namespace sherwin_adventure
{
namespace gba
{
class LinearAllocatorBase
{
public:		// constants
	// 64 kiB
	static constexpr size_t ewram_alloc_space = (1 << 16);

	// 4 kiB
	static constexpr size_t iwram_alloc_space = (1 << 12);



protected:		// static variables
	static u8 __allocatable_ewram[ewram_alloc_space]
		__attribute__((_bss));
	static u8 __allocatable_iwram[iwram_alloc_space]
		__attribute__((_iwram_bss));

protected:		// variables
	size_t __index = 0;

public:		// functions
	inline LinearAllocatorBase()
	{
		reset();
	}

	inline void reset()
	{
		__index = 0;
	}

} __attribute__((_align4));

class EwramLinearAllocator : public LinearAllocatorBase
{
public:		// functions
	inline EwramLinearAllocator()
	{
	}
	template<typename Type>
	inline Type* allocate()
	{
		static constexpr size_t alloc_size = sizeof(Type);

		if ((__index + alloc_size) >= ewram_alloc_space)
		{
			game_engine::err("EwramLinearAllocator::allocate():  Eek!");
			return nullptr;
		}

		__index += alloc_size;

		auto ret = &(__allocatable_ewram[__index]);

		return static_cast<Type*>(ret);
	}
	template<typename Type>
	inline Type* allocate_arr(size_t num_arr_elems)
	{
		const size_t alloc_size = sizeof(Type) * num_arr_elems;

		if ((__index + alloc_size) >= ewram_alloc_space)
		{
			game_engine::err("EwramLinearAllocator::allocate_arr():  "
				"Eek!");
			return nullptr;
		}

		__index += alloc_size;

		auto ret = &(__allocatable_ewram[__index]);

		return static_cast<Type*>(ret);
	}

} __attribute__((_align4));

class IwramLinearAllocator : public LinearAllocatorBase
{
public:		// functions
	inline IwramLinearAllocator()
	{
	}
	template<typename Type>
	inline Type* allocate()
	{
		static constexpr size_t alloc_size = sizeof(Type);

		if ((__index + alloc_size) >= iwram_alloc_space)
		{
			game_engine::err("IwramLinearAllocator::allocate():  Eek!");
			return nullptr;
		}

		__index += alloc_size;

		auto ret = &(__allocatable_iwram[__index]);

		return static_cast<Type*>(ret);
	}
	template<typename Type>
	inline Type* allocate_arr(size_t num_arr_elems)
	{
		const size_t alloc_size = sizeof(Type) * num_arr_elems;

		if ((__index + alloc_size) >= iwram_alloc_space)
		{
			game_engine::err("IwramLinearAllocator::allocate_arr():  "
				"Eek!");
			return nullptr;
		}

		__index += alloc_size;

		auto ret = &(__allocatable_iwram[__index]);

		return static_cast<Type*>(ret);
	}

} __attribute__((_align4));

}
}


#endif		// gba_specific_stuff__slash__linear_allocator_classes_hpp
