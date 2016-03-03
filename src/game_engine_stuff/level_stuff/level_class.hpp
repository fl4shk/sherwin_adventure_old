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


#ifndef level_class_hpp
#define level_class_hpp

#include "sublevel_class.hpp"
#include "level_defines.hpp"

#include <array>
using std::array;

// This is a class that contains a group of COMPRESSED sublevels in ROM.
// It also allows 
class level
{
public:		// constants
	static constexpr u32 max_num_sublevels = max_num_sublevels_per_level;
	
protected:		// variables
	u32 actual_num_sublevels;
	array< sublevel_pointer, max_num_sublevels > the_sublevels;
	
public:		// functions
	
	inline level( sublevel_pointer& first_sublevel_ptr )
		: actual_num_sublevels(1)
	{
		the_sublevels[0] = first_sublevel_ptr;
	}
	inline level( sublevel_pointer&& first_sublevel_ptr )
		: actual_num_sublevels(1)
	{
		the_sublevels[0] = first_sublevel_ptr;
	}
	
	inline level( sublevel_pointer& first_sublevel_ptr, 
		sublevel_pointer& second_sublevel_ptr )
		: actual_num_sublevels(2)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
	}
	inline level( sublevel_pointer&& first_sublevel_ptr, 
		sublevel_pointer&& second_sublevel_ptr )
		: actual_num_sublevels(2)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
	}
	
	inline level( sublevel_pointer& first_sublevel_ptr, 
		sublevel_pointer& second_sublevel_ptr,
		sublevel_pointer& third_sublevel_ptr )
		: actual_num_sublevels(3)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
	}
	inline level( sublevel_pointer&& first_sublevel_ptr, 
		sublevel_pointer&& second_sublevel_ptr,
		sublevel_pointer&& third_sublevel_ptr )
		: actual_num_sublevels(3)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
	}
	
	inline level( sublevel_pointer& first_sublevel_ptr, 
		sublevel_pointer& second_sublevel_ptr,
		sublevel_pointer& third_sublevel_ptr,
		sublevel_pointer& fourth_sublevel_ptr )
		: actual_num_sublevels(4)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
	}
	inline level( sublevel_pointer&& first_sublevel_ptr, 
		sublevel_pointer&& second_sublevel_ptr,
		sublevel_pointer&& third_sublevel_ptr,
		sublevel_pointer&& fourth_sublevel_ptr )
		: actual_num_sublevels(4)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
	}
	
	inline level( sublevel_pointer& first_sublevel_ptr, 
		sublevel_pointer& second_sublevel_ptr,
		sublevel_pointer& third_sublevel_ptr,
		sublevel_pointer& fourth_sublevel_ptr,
		sublevel_pointer& fifth_sublevel_ptr )
		: actual_num_sublevels(5)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
		the_sublevels[4] = fifth_sublevel_ptr;
	}
	inline level( sublevel_pointer&& first_sublevel_ptr, 
		sublevel_pointer&& second_sublevel_ptr,
		sublevel_pointer&& third_sublevel_ptr,
		sublevel_pointer&& fourth_sublevel_ptr,
		sublevel_pointer&& fifth_sublevel_ptr )
		: actual_num_sublevels(5)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
		the_sublevels[4] = fifth_sublevel_ptr;
	}
	
	inline level( sublevel_pointer& first_sublevel_ptr, 
		sublevel_pointer& second_sublevel_ptr,
		sublevel_pointer& third_sublevel_ptr,
		sublevel_pointer& fourth_sublevel_ptr,
		sublevel_pointer& fifth_sublevel_ptr,
		sublevel_pointer& sixth_sublevel_ptr )
		: actual_num_sublevels(6)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
		the_sublevels[4] = fifth_sublevel_ptr;
		the_sublevels[5] = sixth_sublevel_ptr;
	}
	inline level( sublevel_pointer&& first_sublevel_ptr, 
		sublevel_pointer&& second_sublevel_ptr,
		sublevel_pointer&& third_sublevel_ptr,
		sublevel_pointer&& fourth_sublevel_ptr,
		sublevel_pointer&& fifth_sublevel_ptr,
		sublevel_pointer&& sixth_sublevel_ptr )
		: actual_num_sublevels(6)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
		the_sublevels[4] = fifth_sublevel_ptr;
		the_sublevels[5] = sixth_sublevel_ptr;
	}
	
	inline level( sublevel_pointer& first_sublevel_ptr, 
		sublevel_pointer& second_sublevel_ptr,
		sublevel_pointer& third_sublevel_ptr,
		sublevel_pointer& fourth_sublevel_ptr,
		sublevel_pointer& fifth_sublevel_ptr,
		sublevel_pointer& sixth_sublevel_ptr,
		sublevel_pointer& seventh_sublevel_ptr )
		: actual_num_sublevels(7)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
		the_sublevels[4] = fifth_sublevel_ptr;
		the_sublevels[5] = sixth_sublevel_ptr;
		the_sublevels[6] = seventh_sublevel_ptr;
	}
	inline level( sublevel_pointer&& first_sublevel_ptr, 
		sublevel_pointer&& second_sublevel_ptr,
		sublevel_pointer&& third_sublevel_ptr,
		sublevel_pointer&& fourth_sublevel_ptr,
		sublevel_pointer&& fifth_sublevel_ptr,
		sublevel_pointer&& sixth_sublevel_ptr,
		sublevel_pointer&& seventh_sublevel_ptr )
		: actual_num_sublevels(7)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
		the_sublevels[4] = fifth_sublevel_ptr;
		the_sublevels[5] = sixth_sublevel_ptr;
		the_sublevels[6] = seventh_sublevel_ptr;
	}
	
	inline level( sublevel_pointer& first_sublevel_ptr, 
		sublevel_pointer& second_sublevel_ptr,
		sublevel_pointer& third_sublevel_ptr,
		sublevel_pointer& fourth_sublevel_ptr,
		sublevel_pointer& fifth_sublevel_ptr,
		sublevel_pointer& sixth_sublevel_ptr,
		sublevel_pointer& seventh_sublevel_ptr,
		sublevel_pointer& eighth_subelevel_ptr )
		: actual_num_sublevels(8)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
		the_sublevels[4] = fifth_sublevel_ptr;
		the_sublevels[5] = sixth_sublevel_ptr;
		the_sublevels[6] = seventh_sublevel_ptr;
		the_sublevels[7] = eighth_subelevel_ptr;
	}
	inline level( sublevel_pointer&& first_sublevel_ptr, 
		sublevel_pointer&& second_sublevel_ptr,
		sublevel_pointer&& third_sublevel_ptr,
		sublevel_pointer&& fourth_sublevel_ptr,
		sublevel_pointer&& fifth_sublevel_ptr,
		sublevel_pointer&& sixth_sublevel_ptr,
		sublevel_pointer&& seventh_sublevel_ptr,
		sublevel_pointer&& eighth_subelevel_ptr )
		: actual_num_sublevels(8)
	{
		the_sublevels[0] = first_sublevel_ptr;
		the_sublevels[1] = second_sublevel_ptr;
		the_sublevels[2] = third_sublevel_ptr;
		the_sublevels[3] = fourth_sublevel_ptr;
		the_sublevels[4] = fifth_sublevel_ptr;
		the_sublevels[5] = sixth_sublevel_ptr;
		the_sublevels[6] = seventh_sublevel_ptr;
		the_sublevels[7] = eighth_subelevel_ptr;
	}
	
	
	inline const u32 get_actual_num_sublevels() const
	{
		return actual_num_sublevels;
	}
	
	inline const sublevel_pointer* get_the_sublevels() const
	{
		return the_sublevels.data();
	}
	
	
} __attribute__((_align4));


#endif		// level_class_hpp
