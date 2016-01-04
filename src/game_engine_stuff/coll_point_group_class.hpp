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


#ifndef coll_point_group_class_hpp
#define coll_point_group_class_hpp

#include "../gba_specific_stuff/attribute_defines.hpp"
#include "vec2_class.hpp"

#include "coll_box_class.hpp"

class sprite;


// This class is primarily used by the collision detection and response
// between sprites and blocks, or at least coll_boxes and blocks.
class coll_point_group
{
public:		// enums
	enum arr_index_16x16 
	{
		// Left side
		arr_ind_16x16_pt_lt, arr_ind_16x16_pt_lb,
		
		// Top side
		arr_ind_16x16_pt_tl, arr_ind_16x16_pt_tm, arr_ind_16x16_pt_tr,
		
		// Right side
		arr_ind_16x16_pt_rt, arr_ind_16x16_pt_rb,
		
		// Bottom side
		arr_ind_16x16_pt_bl, arr_ind_16x16_pt_bm, arr_ind_16x16_pt_br,
		
		// arr_ind_16x16_count is the amount of arr_index_16x16's.  It is
		// automatically updated by the compiler.
		arr_ind_16x16_count,
	};
	
	
	enum arr_index_16x32
	{
		// Left side
		arr_ind_16x32_pt_lt, arr_ind_16x32_pt_lm, arr_ind_16x32_pt_lb,
		
		// Top side
		arr_ind_16x32_pt_tl, arr_ind_16x32_pt_tm, arr_ind_16x32_pt_tr,
		
		// Right side
		arr_ind_16x32_pt_rt, arr_ind_16x32_pt_rm, arr_ind_16x32_pt_rb,
		
		// Bottom side
		arr_ind_16x32_pt_bl, arr_ind_16x32_pt_bm, arr_ind_16x32_pt_br,
		
		// arr_ind_16x32_count is the amount of arr_index_16x32's.  It is
		// automatically updated by the compiler.
		arr_ind_16x32_count,
	};

	enum arr_index_32x16
	{
		// Left side
		arr_ind_32x16_pt_lt, arr_ind_32x16_pt_lb,
		
		// Top side
		arr_ind_32x16_pt_tl, arr_ind_32x16_pt_tm, arr_ind_32x16_pt_tr,
		
		// Right side
		arr_ind_32x16_pt_rt, arr_ind_32x16_pt_rb,
		
		// Bottom side
		arr_ind_32x16_pt_bl, arr_ind_32x16_pt_bm, arr_ind_32x16_pt_br,
		
		// arr_ind_32x16_count is the amount of arr_index_32x16's.  It is
		// automatically updated by the compiler.
		arr_ind_32x16_count,
	};
	
public:		// variables
	// The maximum number of collision points, 32, is definitely more than
	// is necessary, but thus far there's not that much need to optimize
	// the number of collision points (also I'm too lazy to put effort into
	// doing so).
	static const u32 total_coll_points = 32;
	u32 num_used_points;
	vec2_f24p8 the_array[total_coll_points];
	
	
public:		// functions
	inline coll_point_group()
	{
		num_used_points = 0;
		memfill32( the_array, 0, sizeof(the_array) 
			/ sizeof(u32) );
	}
	
	inline void push_coll_point( const vec2_f24p8& to_push )
	{
		the_array[num_used_points++] = to_push;
	}
	
	// These functions are on two lines to prevent ridiculousness with the
	// length of this header file.  Also, it just looks cleaner.
	inline vec2_f24p8& get_pt_lt_16x16()
		{ return the_array[arr_ind_16x16_pt_lt]; }
	inline vec2_f24p8& get_pt_lb_16x16()
		{ return the_array[arr_ind_16x16_pt_lb]; }
	inline vec2_f24p8& get_pt_tl_16x16()
		{ return the_array[arr_ind_16x16_pt_tl]; }
	inline vec2_f24p8& get_pt_tm_16x16()
		{ return the_array[arr_ind_16x16_pt_tm]; }
	inline vec2_f24p8& get_pt_tr_16x16()
		{ return the_array[arr_ind_16x16_pt_tr]; }
	inline vec2_f24p8& get_pt_rt_16x16()
		{ return the_array[arr_ind_16x16_pt_rt]; }
	inline vec2_f24p8& get_pt_rb_16x16()
		{ return the_array[arr_ind_16x16_pt_rb]; }
	inline vec2_f24p8& get_pt_bl_16x16()
		{ return the_array[arr_ind_16x16_pt_bl]; }
	inline vec2_f24p8& get_pt_bm_16x16()
		{ return the_array[arr_ind_16x16_pt_bm]; }
	inline vec2_f24p8& get_pt_br_16x16()
		{ return the_array[arr_ind_16x16_pt_br]; }
	
	inline void correct_num_used_points_16x16()
		{ num_used_points = arr_ind_16x16_count; }
	
	
	// These functions are on two lines to prevent ridiculousness with the
	// length of this header file.  Also, it just looks cleaner.
	inline vec2_f24p8& get_pt_lt_16x32()
		{ return the_array[arr_ind_16x32_pt_lt]; }
	inline vec2_f24p8& get_pt_lm_16x32()
		{ return the_array[arr_ind_16x32_pt_lm]; }
	inline vec2_f24p8& get_pt_lb_16x32()
		{ return the_array[arr_ind_16x32_pt_lb]; }
	inline vec2_f24p8& get_pt_tl_16x32()
		{ return the_array[arr_ind_16x32_pt_tl]; }
	inline vec2_f24p8& get_pt_tm_16x32()
		{ return the_array[arr_ind_16x32_pt_tm]; }
	inline vec2_f24p8& get_pt_tr_16x32()
		{ return the_array[arr_ind_16x32_pt_tr]; }
	inline vec2_f24p8& get_pt_rt_16x32()
		{ return the_array[arr_ind_16x32_pt_rt]; }
	inline vec2_f24p8& get_pt_rm_16x32()
		{ return the_array[arr_ind_16x32_pt_rm]; }
	inline vec2_f24p8& get_pt_rb_16x32()
		{ return the_array[arr_ind_16x32_pt_rb]; }
	inline vec2_f24p8& get_pt_bl_16x32()
		{ return the_array[arr_ind_16x32_pt_bl]; }
	inline vec2_f24p8& get_pt_bm_16x32()
		{ return the_array[arr_ind_16x32_pt_bm]; }
	inline vec2_f24p8& get_pt_br_16x32()
		{ return the_array[arr_ind_16x32_pt_br]; }
	
	inline void correct_num_used_points_16x32()
		{ num_used_points = arr_ind_16x32_count; }
	
	// These functions are on two lines to prevent ridiculousness with the
	// length of this header file.  Also, it just looks cleaner.
	inline vec2_f24p8& get_pt_lt_32x16()
		{ return the_array[arr_ind_32x16_pt_lt]; }
	inline vec2_f24p8& get_pt_lb_32x16()
		{ return the_array[arr_ind_32x16_pt_lb]; }
	inline vec2_f24p8& get_pt_tl_32x16()
		{ return the_array[arr_ind_32x16_pt_tl]; }
	inline vec2_f24p8& get_pt_tm_32x16()
		{ return the_array[arr_ind_32x16_pt_tm]; }
	inline vec2_f24p8& get_pt_tr_32x16()
		{ return the_array[arr_ind_32x16_pt_tr]; }
	inline vec2_f24p8& get_pt_rt_32x16()
		{ return the_array[arr_ind_32x16_pt_rt]; }
	inline vec2_f24p8& get_pt_rb_32x16()
		{ return the_array[arr_ind_32x16_pt_rb]; }
	inline vec2_f24p8& get_pt_bl_32x16()
		{ return the_array[arr_ind_32x16_pt_bl]; }
	inline vec2_f24p8& get_pt_bm_32x16()
		{ return the_array[arr_ind_32x16_pt_bm]; }
	inline vec2_f24p8& get_pt_br_32x16()
		{ return the_array[arr_ind_32x16_pt_br]; }
	
	inline void correct_num_used_points_32x16()
		{ num_used_points = arr_ind_32x16_count; }
	
} __attribute__((_align4));

void generate_coll_point_group_16x16( const sprite& the_sprite, 
	coll_point_group& the_pt_group ) __attribute__((_iwram_code));

void generate_coll_point_group_16x32( const sprite& the_sprite, 
	coll_point_group& the_pt_group ) __attribute__((_iwram_code));

void generate_coll_point_group_32x16( const sprite& the_sprite, 
	coll_point_group& the_pt_group ) __attribute__((_iwram_code));

void generate_coll_point_group_32x32( const sprite& the_sprite, 
	coll_point_group& the_pt_group ) __attribute__((_iwram_code));


#endif		// coll_point_group_class_hpp
