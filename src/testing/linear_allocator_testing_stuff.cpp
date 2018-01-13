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


#include "linear_allocator_testing_stuff.hpp"

static constexpr size_t test_buf_size = 8;
u32* test_ewram_buf;
u32* test_iwram_buf;

void test_linear_allocators()
{
	test_ewram_buf = sherwin_adventure::gba::ewram_linear_allocator
		.allocate_arr<u32>(test_buf_size);
	test_iwram_buf = sherwin_adventure::gba::iwram_linear_allocator
		.allocate_arr<u32>(test_buf_size);


	test_ewram_buf[0] = 9;
	test_ewram_buf[1] = 5;
	test_ewram_buf[2] = 6;
	test_ewram_buf[3] = 1;
	test_ewram_buf[4] = 9;
	test_ewram_buf[5] = 20;
	test_ewram_buf[6] = 7;
	test_ewram_buf[7] = 9000;


	test_iwram_buf[0] = 2000;
	test_iwram_buf[1] = 2001;
	test_iwram_buf[2] = 2002;
	test_iwram_buf[3] = 2003;
	test_iwram_buf[4] = 2004;
	test_iwram_buf[5] = 2005;
	test_iwram_buf[6] = 2006;
	test_iwram_buf[7] = 2007;
}
