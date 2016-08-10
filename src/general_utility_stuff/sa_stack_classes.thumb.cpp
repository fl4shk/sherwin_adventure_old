// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#include "sa_stack_classes.hpp"

sa_pod_stack_backend::sa_pod_stack_backend() : ptr_to_the_array_u8(0),
	ptr_to_next_index(0), type_size(0), num_elems(0)
{
}
sa_pod_stack_backend::sa_pod_stack_backend( u8* s_ptr_to_the_array_u8, 
	u32* s_ptr_to_next_index, u32 s_type_size, u32 s_num_elems )
	: ptr_to_the_array_u8(s_ptr_to_the_array_u8),
	ptr_to_next_index(s_ptr_to_next_index), type_size(s_type_size),
	num_elems(s_num_elems)
{
}

void sa_pod_stack_backend::pop()
{
	--get_next_index();
}

void sa_pod_stack_backend::write_to_the_array_u8( const u8* to_write_u8,
	u32 non_u8_index )
{
	u32 start_index_u8 = arr_byte_index_macro( get_type_size(), 
		non_u8_index );
	
	for ( u32 i=0; i<get_type_size(); ++i )
	{
		get_the_array_u8()[start_index_u8 + i] = to_write_u8[i];
	}
}

sa_free_list_backend::sa_free_list_backend() : sa_pod_stack_backend()
{
}
sa_free_list_backend::sa_free_list_backend( u8* s_ptr_to_the_array_u8, 
	u32* s_ptr_to_next_index, u32 s_num_elems ) 
	: sa_pod_stack_backend( s_ptr_to_the_array_u8, s_ptr_to_next_index,
	get_the_const_type_size(), s_num_elems )
{
	init();
}

sa_free_list_backend::sa_free_list_backend( s16* s_ptr_to_the_array,
	u32* s_ptr_to_next_index, u32 s_num_elems ) 
	: sa_pod_stack_backend( (u8*)s_ptr_to_the_array, s_ptr_to_next_index,
	get_the_const_type_size(), s_num_elems )
{
	init();
}


void sa_free_list_backend::init()
{
	get_next_index() = 0;
	
	// This makes it so that the values initially stored in the array are
	// decrementing in value, starting with the highest value of
	// ( get_size() - 1 ) and ending with 0. 
	for ( int i=get_size()-1; i>= 0; --i )
	{
		push(i);
	}
}

