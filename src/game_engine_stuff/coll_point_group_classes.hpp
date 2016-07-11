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


#ifndef coll_point_group_classes_hpp
#define coll_point_group_classes_hpp

#include "../gba_specific_stuff/attribute_defines.hpp"
#include "coll_point_extras.hpp"

#include "vec2_class.hpp"

#include "coll_box_class.hpp"

class sprite;


// This class is primarily used by the collision detection and response
// between sprites and blocks, or at least coll_boxes and blocks.
class coll_point_group_base
{
public:		// enums
	enum arr_index_16x16 
	{
		#define X(name) \
			arr_ind_16x16_pt_##name, 
		
		// Left side
		list_of_16x16_left_side_coll_point_names(X)
		
		// Right side
		list_of_16x16_right_side_coll_point_names(X)
		
		// Top side
		list_of_16x16_top_side_coll_point_names(X)
		
		// Bottom side
		list_of_16x16_bottom_side_coll_point_names(X)
		
		// Middle vertical line
		list_of_16x16_middle_vert_line_coll_point_names(X)
		
		#undef X
		
		// arr_ind_16x16_count is the amount of arr_index_16x16's.  It is
		// automatically updated by the compiler.
		arr_ind_16x16_count,
	} __attribute__((_align4));
	
	
	// The reason an X-macro isn't used here is because ctags wouldn't be
	// able to work with it.
	enum arr_index_16x32 
	{
		#define X(name) \
			arr_ind_16x32_pt_##name, 
		
		// Left side
		list_of_16x32_left_side_coll_point_names(X)
		
		// Right side
		list_of_16x32_right_side_coll_point_names(X)
		
		// Top side
		list_of_16x32_top_side_coll_point_names(X)
		
		// Bottom side
		list_of_16x32_bottom_side_coll_point_names(X)
		
		// Middle vertical line
		list_of_16x32_middle_vert_line_coll_point_names(X)
		
		#undef X
		
		// arr_ind_16x32_count is the amount of arr_index_16x32's.  It is
		// automatically updated by the compiler.
		arr_ind_16x32_count,
	} __attribute__((_align4));
	
	
	// The reason an X-macro isn't used here is because ctags wouldn't be
	// able to work with it.
	enum arr_index_32x16 
	{
		#define X(name) \
			arr_ind_32x16_pt_##name, 
		
		// Left side
		list_of_32x16_left_side_coll_point_names(X)
		
		// Right side
		list_of_32x16_right_side_coll_point_names(X)
		
		// Top side
		list_of_32x16_top_side_coll_point_names(X)
		
		// Bottom side
		list_of_32x16_bottom_side_coll_point_names(X)
		
		// Middle vertical line
		list_of_32x16_middle_vert_line_coll_point_names(X)
		
		#undef X
		
		// arr_ind_32x16_count is the amount of arr_index_32x16's.  It is
		// automatically updated by the compiler.
		arr_ind_32x16_count,
	} __attribute__((_align4));
	
public:		// variables
	// The maximum number of collision points, 32, is definitely more than
	// is necessary, but thus far there's not that much need to optimize
	// the number of collision points (also I'm too lazy to put effort into
	// doing so).
	static const u32 max_num_coll_points = 32;
	vec2_f24p8 the_array[max_num_coll_points];
	
	
public:		// functions
	inline coll_point_group_base()
	{
		memfill32( the_array, 0, sizeof(the_array) / sizeof(u32) );
	}
	
} __attribute__((_align4));

class coll_point_group_16x16 : public coll_point_group_base
{
public:		// functions
	coll_point_group_16x16( const sprite& the_sprite )
		__attribute__((_iwram_code));
	
	inline vec2_f24p8& get_pt_lt()
		{ return the_array[arr_ind_16x16_pt_lt]; }
	inline vec2_f24p8& get_pt_lb()
		{ return the_array[arr_ind_16x16_pt_lb]; }
	
	inline vec2_f24p8& get_pt_rt()
		{ return the_array[arr_ind_16x16_pt_rt]; }
	inline vec2_f24p8& get_pt_rb()
		{ return the_array[arr_ind_16x16_pt_rb]; }
	
	inline vec2_f24p8& get_pt_tl()
		{ return the_array[arr_ind_16x16_pt_tl]; }
	inline vec2_f24p8& get_pt_tm()
		{ return the_array[arr_ind_16x16_pt_tm]; }
	inline vec2_f24p8& get_pt_tr()
		{ return the_array[arr_ind_16x16_pt_tr]; }
	
	inline vec2_f24p8& get_pt_bl()
		{ return the_array[arr_ind_16x16_pt_bl]; }
	inline vec2_f24p8& get_pt_bm()
		{ return the_array[arr_ind_16x16_pt_bm]; }
	inline vec2_f24p8& get_pt_br()
		{ return the_array[arr_ind_16x16_pt_br]; }
	
	inline vec2_f24p8& get_pt_mt()
		{ return the_array[arr_ind_16x16_pt_mt]; }
	inline vec2_f24p8& get_pt_mb()
		{ return the_array[arr_ind_16x16_pt_mb]; }
} __attribute__((_align4));


class coll_point_group_16x32 : public coll_point_group_base
{
public:		// functions
	coll_point_group_16x32( const sprite& the_sprite )
		__attribute__((_iwram_code));
	
	inline vec2_f24p8& get_pt_lt()
		{ return the_array[arr_ind_16x32_pt_lt]; }
	inline vec2_f24p8& get_pt_lm()
		{ return the_array[arr_ind_16x32_pt_lm]; }
	inline vec2_f24p8& get_pt_lb()
		{ return the_array[arr_ind_16x32_pt_lb]; }
	
	inline vec2_f24p8& get_pt_rt()
		{ return the_array[arr_ind_16x32_pt_rt]; }
	inline vec2_f24p8& get_pt_rm()
		{ return the_array[arr_ind_16x32_pt_rm]; }
	inline vec2_f24p8& get_pt_rb()
		{ return the_array[arr_ind_16x32_pt_rb]; }
	
	inline vec2_f24p8& get_pt_tl()
		{ return the_array[arr_ind_16x32_pt_tl]; }
	inline vec2_f24p8& get_pt_tm()
		{ return the_array[arr_ind_16x32_pt_tm]; }
	inline vec2_f24p8& get_pt_tr()
		{ return the_array[arr_ind_16x32_pt_tr]; }
	
	inline vec2_f24p8& get_pt_bl()
		{ return the_array[arr_ind_16x32_pt_bl]; }
	inline vec2_f24p8& get_pt_bm()
		{ return the_array[arr_ind_16x32_pt_bm]; }
	inline vec2_f24p8& get_pt_br()
		{ return the_array[arr_ind_16x32_pt_br]; }
	
	inline vec2_f24p8& get_pt_mt()
		{ return the_array[arr_ind_16x32_pt_mt]; }
	inline vec2_f24p8& get_pt_mm()
		{ return the_array[arr_ind_16x32_pt_mm]; }
	inline vec2_f24p8& get_pt_mb()
		{ return the_array[arr_ind_16x32_pt_mb]; }
} __attribute__((_align4));

//void generate_coll_point_group_16x16( const sprite& the_sprite, 
//	coll_point_group& the_pt_group ) __attribute__((_iwram_code));
//
//void generate_coll_point_group_16x32( const sprite& the_sprite, 
//	coll_point_group& the_pt_group ) __attribute__((_iwram_code));
//
//void generate_coll_point_group_32x16( const sprite& the_sprite, 
//	coll_point_group& the_pt_group ) __attribute__((_iwram_code));
//
//void generate_coll_point_group_32x32( const sprite& the_sprite, 
//	coll_point_group& the_pt_group ) __attribute__((_iwram_code));



#endif		// coll_point_group_classes_hpp
