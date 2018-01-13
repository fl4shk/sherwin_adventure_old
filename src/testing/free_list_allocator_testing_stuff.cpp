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


#include "free_list_allocator_testing_stuff.hpp"


//namespace sherwin_adventure
//{
//namespace containers
//{
//namespace test_alloc
//{
//
//class AllocatorA;
//
//class _alignas_regular A : public FreeListAllocContainedBase<AllocatorA>
//{
//public:		// variables
//	u32 x = 0;
//
//public:		// functions
//	inline A()
//		: x(0)
//	{
//	}
//	inline A(s32 s_arr_index)
//		: FreeListAllocContainedBase(s_arr_index), x(0)
//	{
//	}
//	inline A(s32 s_arr_index, u32 s_x)
//		: FreeListAllocContainedBase(s_arr_index), x(s_x)
//	{
//	}
//
//	virtual ~A()
//	{
//		DebugArrGroup::write_str_and_inc("SnooPINGAS");
//		DebugArrGroup::write_u32_and_inc(x);
//	}
//
//};
//
//class _alignas_regular AllocatorA : public FreeListAllocatorBase<A>
//{
//public:		// typedefs
//	typedef FreeListAllocatorBase<A> Base;
//
//public:		// functions
//	inline AllocatorA()
//	{
//	}
//	inline AllocatorA(A* s_arr, s16* s_free_list_arr, size_t s_size)
//		: Base(s_arr, s_free_list_arr, s_size)
//	{
//	}
//
//	inline void init(A* s_arr, s16* s_free_list_arr, size_t s_size)
//	{
//		Base::init(s_arr, s_free_list_arr, s_size);
//	}
//
//};
//
//static constexpr size_t num_a = 50;
//A arr_a[num_a];
//s16 free_list_arr_a[num_a];
//
//AllocatorA alloc_a(arr_a, free_list_arr_a, num_a);
//
//
//}
//}
//}
//
//
//void test_free_list_allocator()
//{
//	using namespace containers::test_alloc;
//
//	{
//		//auto a = new (alloc_a) A;
//		//auto b = new (alloc_a) A;
//		//auto c = new (alloc_a) A;
//
//		auto a = alloc_a.attempt_allocate();
//		new (a) A();
//		auto b = alloc_a.attempt_allocate();
//		new (b) A();
//		auto c = alloc_a.attempt_allocate();
//		new (c) A();
//
//		a->x = 9;
//		b->x = 7;
//		c->x = 5;
//
//		alloc_a.deallocate(a);
//		alloc_a.deallocate(b);
//		alloc_a.deallocate(c);
//	}
//
//	//DebugArrGroup::clear_debug_vars();
//
//	{
//		//auto a = new (alloc_a) A;
//		//auto b = new (alloc_a) A;
//		//auto c = new (alloc_a) A;
//
//		auto a = alloc_a.attempt_allocate();
//		new (a) A();
//		auto b = alloc_a.attempt_allocate();
//		new (b) A();
//		auto c = alloc_a.attempt_allocate();
//		new (c) A();
//
//		a->x = 20;
//		b->x = 22;
//		c->x = 24;
//
//		alloc_a.deallocate(c);
//		alloc_a.deallocate(b);
//		alloc_a.deallocate(a);
//	}
//}

