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


#ifndef sa_stack_class_hpp
#define sa_stack_class_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"

#include <array>
using std::array;


template< typename type, u32 size >
class sa_stack
{
public:		// variables
	//type the_array[size];
	array< type, size > the_array;
	u32 curr_index;
	
public:		// functions
	inline sa_stack() : curr_index(0)
	{
		memfill32( the_array.data(), type(), size * sizeof(type) );
	}
	
	inline void push( const type& to_push )
	{
		the_array[curr_index++] = to_push;
	}
	
	//inline virtual const type pop()
	//{
	//	return the_array[--curr_index];
	//}
	
	inline virtual void pop()
	{
		--curr_index;
	}
	
	inline const type& peek_top() const
	{
		return the_array[curr_index-1];
	}
	
	inline type& peek_top()
	{
		return the_array[curr_index-1];
	}
	
	inline u32 get_size() const
	{
		return size;
	}
	
	
} __attribute__((_align4));


template< u32 size >
class sa_free_list : public sa_stack< int, size >
{
public:		// variables
	typedef sa_stack< int, size > specific_sa_stack;
	
public:		// functions
	inline sa_free_list()
	{
		for ( int i=size-1; i>=0; --i )
		{
			specific_sa_stack::push(i);
		}
	}
	
	inline virtual void pop()
	{
		specific_sa_stack::the_array[specific_sa_stack::curr_index-1] = -1;
		--specific_sa_stack::curr_index;
	}
	
} __attribute__((_align4));



#endif		// sa_stack_class_hpp
