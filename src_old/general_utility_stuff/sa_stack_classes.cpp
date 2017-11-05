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


#include "sa_stack_classes.hpp"

SaPodStackBackend::SaPodStackBackend() : the_array_u8(0),
	next_index_ptr(0), type_size(0), num_elems(0)
{
}
SaPodStackBackend::SaPodStackBackend(u8* s_the_array_u8, 
	u32* s_next_index_ptr, u32 s_type_size, u32 s_num_elems)
	: the_array_u8(s_the_array_u8), next_index_ptr(s_next_index_ptr), 
	type_size(s_type_size), num_elems(s_num_elems)
{
}

//void SaPodStackBackend::pop()
//{
//	--get_next_index();
//}

void SaPodStackBackend::write_to_the_array_u8(const u8* to_write_u8,
	u32 non_u8_index)
{
	u32 start_index_u8 = ARR_BYTE_INDEX_MACRO(get_type_size(), 
		non_u8_index);

	for (u32 i=0; i<get_type_size(); ++i)
	{
		get_array_u8()[start_index_u8 + i] = to_write_u8[i];
	}
}

SaFreeListBackend::SaFreeListBackend() : SaPodStackBackend()
{
}
SaFreeListBackend::SaFreeListBackend(u8* s_the_array_u8, 
	u32* s_next_index_ptr, u32 s_num_elems) 
	: SaPodStackBackend(s_the_array_u8, s_next_index_ptr,
	get_const_type_size(), s_num_elems)
{
	init();
}

SaFreeListBackend::SaFreeListBackend(s16* s_the_array,
	u32* s_next_index_ptr, u32 s_num_elems) 
	: SaPodStackBackend((u8*)s_the_array, s_next_index_ptr,
	get_const_type_size(), s_num_elems)
{
	init();
}


void SaFreeListBackend::init()
{
	get_next_index() = 0;

	// This makes it So That the values initially stored in the array are
	// decrementing in value, starting with the highest value of
	// (get_size() - 1) and ending with 0. 
	for (int i=get_size()-1; i>= 0; --i)
	{
		push(i);
	}
}


//s16& SaFreeListBackend::peek_top_and_pop()
//{
//	pop();
//
//	return get_array()[get_next_index()];
//}

