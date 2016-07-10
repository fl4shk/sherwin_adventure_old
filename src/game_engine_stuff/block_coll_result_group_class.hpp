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


#ifndef block_coll_result_group_class_hpp
#define block_coll_result_group_class_hpp


#include "block_stuff/block_stuff.hpp"


class block_coll_result
{
public:		// variables
	vec2_s32 coord;
	//block_type type;
	block* the_block;
	
public:		// functions
	
	
} __attribute__((_align4));



class block_coll_result_group
{
public:		// variables
	static const u32 max_num_block_coll_results = 9;
	block_coll_result the_array[max_num_block_coll_results];
	
public:		// functions
	
	
	
	
} __attribute__((_align4));




#endif		// block_coll_result_group_class_hpp
