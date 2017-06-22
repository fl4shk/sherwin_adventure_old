// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef prev_curr_pair_class_hpp
#define prev_curr_pair_class_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"

#include <utility>

template < typename type >
class Vec2;

// This Is a small class for the purposes of holding the states of
// "previous" and "current" pairs.  It Is primarily Intended for use with
// SMALL types, such as Vec2's, built-in types, and So on and So forth.
template< typename type >
class PrevCurrPair
{
public:		// variables
	type prev, curr;
	
public:		// functions
	
	inline void back_up()
	{
		prev = curr;
	}
	
	inline void back_up_and_update(const type& n_curr)
	{
		prev = std::move(curr);
		curr = n_curr;
	}
	inline void back_up_and_update(type&& n_curr)
	{
		prev = std::move(curr);
		curr = std::move(n_curr);
	}
	
	inline bool has_changed() const
	{
		return (prev != curr);
	}
	
	inline operator Vec2<type>() const
	{
		return Vec2<type>(prev, curr);
	}
	
	
} __attribute__((_ALIGN4));



#endif		// prev_curr_pair_class_hpp
