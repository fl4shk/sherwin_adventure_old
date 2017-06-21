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
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef array_helper_class_hpp
#define array_helper_class_hpp



#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"


// This is a VERY thin wrapper class for working with 1D arrays
template< typename type >
class array_helper
{
public:			// variables
	type* the_array = NULL;
	
protected:		// variables
	size_t size = 0;
	
public:			// functions
	array_helper()
	{
	}
	
	array_helper( type* s_the_array, size_t s_size )
		: the_array(s_the_array), size(s_size)
	{
	}
	
	array_helper( const array_helper<type>& to_copy )
		: the_array(to_copy.the_array), size(to_copy.size)
	{
	}
	
	void init( type* s_the_array, size_t s_size )
	{
		the_array = s_the_array;
		size = s_size;
	}
	
	
	array_helper<type>& operator = ( const array_helper<type>& to_copy )
	{
		the_array = to_copy.the_array;
		size = to_copy.size;
		
		return *this;
	}
	
	
	const type* get_array() const
	{
		return the_array;
	}
	
	size_t get_size() const
	{
		return size;
	}
	
	
	type& operator [] ( size_t offset )
	{
		return at(offset);
	}
	const type& operator [] ( size_t offset ) const
	{
		return at(offset);
	}
	
	type& at( size_t offset )
	{
		return the_array[offset];
	}
	const type& at( size_t offset ) const
	{
		return the_array[offset];
	}
	
	
} __attribute__((_ALIGN4));


#endif		// array_helper_class_hpp
