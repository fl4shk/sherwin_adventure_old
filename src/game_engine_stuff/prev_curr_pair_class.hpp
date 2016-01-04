// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#ifndef prev_curr_pair_class_hpp
#define prev_curr_pair_class_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"

template < typename type >
class vec2;

// This is a small class for the purposes of holding the states of
// "previous" and "current" pairs.  It is primarily intended for use with
// SMALL types, such as vec2's, built-in types, and so on and so forth.
template < typename type >
struct prev_curr_pair
{
public:		// variables
	type prev, curr;
	
public:		// functions
	
	inline void back_up()
	{
		prev = curr;
	}
	
	inline void back_up_and_update( const type& n_curr )
	{
		prev = curr;
		curr = n_curr;
	}
	
	inline bool has_changed() const
	{
		return ( prev == curr );
	}
	
	inline operator vec2<type>() const
	{
		return vec2<type>( prev, curr );
	}
	
	
} __attribute__((_align4));



#endif		// prev_curr_pair_class_hpp
