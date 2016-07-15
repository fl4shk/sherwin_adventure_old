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

#include "coll_box_class.hpp"

class block_coll_result
{
public:		// variables
	vec2_s32 coord;
	//block_type type;
	block* the_block;
	
public:		// functions
	inline block_coll_result() : coord(), the_block(NULL)
	{
	}
	block_coll_result( const vec2_s32& s_coord )
		__attribute__((_iwram_code));
	block_coll_result( const vec2_f24p8& s_coord_f24p8 )
		__attribute__((_iwram_code));
	inline block_coll_result( const block_coll_result& to_copy )
	{
		*this = to_copy;
	}
	
	inline block_coll_result& operator = 
		( const block_coll_result& to_copy )
	{
		coord = to_copy.coord;
		the_block = to_copy.the_block;
		
		return *this;
	}
	
	inline block_type get_block_type() const
	{
		return the_block->get_block_type();
	}
	
} __attribute__((_align4));


class block_coll_result_group
{
//public:		// variables
protected:		// variables
	static constexpr vec2_u32 max_size_2d = vec2_u32( 3, 3 );
	static constexpr u32 max_size = max_size_2d.x * max_size_2d.y;
	
	block_coll_result bcr_arr_2d_helper_data[max_size];
	vec2_s32 real_size_2d;
	
public:		// variables
	array_2d_helper<block_coll_result> bcr_arr_2d_helper;
	
public:		// functions
	block_coll_result_group( const coll_box& the_coll_box );
	block_coll_result_group
		( const block_coll_result_group& to_copy );
	
	block_coll_result_group& operator = 
		( const block_coll_result_group& to_copy );
	
	inline s32 real_left() const
	{
		return bcr_arr_2d_helper_data[0].coord.x;
	}
	inline s32 real_right() const
	{
		return real_left() + real_size_2d.x;
	}
	
	inline s32 real_top() const
	{
		return bcr_arr_2d_helper_data[0].coord.y;
	}
	inline s32 real_bot() const
	{
		return real_top() + real_size_2d.y;
	}
	
	inline vec2_s32 real_start_pos() const
	{
		return vec2_s32( real_left(), real_top() );
	}
	inline vec2_s32 real_end_pos() const
	{
		return vec2_s32( real_right(), real_bot() );
	}
	
	inline s32 real_width() const
	{
		return real_size_2d.x;
	}
	inline s32 real_height() const
	{
		return real_size_2d.y;
	}
	inline const vec2_s32 get_real_size_2d() const
	{
		return real_size_2d;
	}
	
} __attribute__((_align4));





#endif		// block_coll_result_group_class_hpp
