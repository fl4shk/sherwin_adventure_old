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


#include "free_list_allocator_testing_stuff.hpp"


namespace sherwin_adventure
{
namespace containers
{

class TestAllocAAllocator;

class TestAllocA : public FreeListAllocContainedBase
{
public:		// variables
	u32 x = 0;

public:		// functions
	inline TestAllocA()
		: x(0)
	{
	}
	inline TestAllocA(s32 s_arr_index)
		: FreeListAllocContainedBase(s_arr_index), x(0)
	{
	}
	inline TestAllocA(s32 s_arr_index, u32 s_x)
		: FreeListAllocContainedBase(s_arr_index), x(s_x)
	{
	}

	virtual ~TestAllocA()
	{
		DebugArrGroup::write_str_and_inc("SnooPINGAS");
	}

	void* operator new (size_t size, TestAllocAAllocator& allocator);

} __attribute__((_align4));



}
}


void test_free_list_allocator()
{
	using namespace containers;
}

