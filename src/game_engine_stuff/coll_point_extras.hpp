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


#ifndef coll_point_extras_hpp
#define coll_point_extras_hpp

#include "../gba_specific_stuff/attribute_defines.hpp"


// Collision points that share a side
#define list_of_16x16_left_side_coll_point_names(macro) \
	macro(lt) macro(lb)
#define list_of_16x16_right_side_coll_point_names(macro) \
	macro(rt) macro(rb)
#define list_of_16x16_top_side_coll_point_names(macro) \
	macro(tl) macro(tm) macro(tr)
#define list_of_16x16_bottom_side_coll_point_names(macro) \
	macro(bl) macro(bm) macro(br)

// Left or right side, same ypos collision points
#define list_of_16x16_vert_side_ypos_top_coll_point_names(macro) \
	macro(lt) macro(rt)
#define list_of_16x16_vert_side_ypos_bottom_coll_point_names(macro) \
	macro(lb) macro(rb)

// Top or bottom same xpos collision points
#define list_of_16x16_horiz_side_xpos_left_coll_point_names(macro) \
	macro(tl) macro(bl)
#define list_of_16x16_horiz_side_xpos_middle_coll_point_names(macro) \
	macro(tm) macro(bm)
#define list_of_16x16_horiz_side_xpos_right_coll_point_names(macro) \
	macro(tr) macro(br)

#define list_of_16x16_slope_stuff_coll_point_names(macro) \
	macro(bm) macro(bl) macro(br)

// All the collision points
#define list_of_16x16_coll_point_names(macro) \
	list_of_16x16_left_side_coll_point_names(macro) \
	list_of_16x16_top_side_coll_point_names(macro) \
	list_of_16x16_right_side_coll_point_names(macro) \
	list_of_16x16_bottom_side_coll_point_names(macro) \


// The reason an X-macro isn't used here is because ctags wouldn't be
// able to work with it.
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
	
	#undef X
	
	// arr_ind_16x16_count is the amount of arr_index_16x16's.  It is
	// automatically updated by the compiler.
	arr_ind_16x16_count,
} __attribute__((_align4));



// Collision points that share a side
#define list_of_16x32_left_side_coll_point_names(macro) \
	macro(lt) macro(lm) macro(lb)
#define list_of_16x32_right_side_coll_point_names(macro) \
	macro(rt) macro(rm) macro(rb)
#define list_of_16x32_top_side_coll_point_names(macro) \
	macro(tl) macro(tm) macro(tr)
#define list_of_16x32_bottom_side_coll_point_names(macro) \
	macro(bl) macro(bm) macro(br)

// Left or right side, same ypos collision points
#define list_of_16x32_vert_side_ypos_top_coll_point_names(macro) \
	macro(lt) macro(rt)
#define list_of_16x32_vert_side_ypos_middle_coll_point_names(macro) \
	macro(lm) macro(rm)
#define list_of_16x32_vert_side_ypos_bottom_coll_point_names(macro) \
	macro(lb) macro(rb)

// Top or bottom same xpos collision points
#define list_of_16x32_horiz_side_xpos_left_coll_point_names(macro) \
	macro(tl) macro(bl)
#define list_of_16x32_horiz_side_xpos_middle_coll_point_names(macro) \
	macro(tm) macro(bm)
#define list_of_16x32_horiz_side_xpos_right_coll_point_names(macro) \
	macro(tr) macro(br)

#define list_of_16x32_slope_stuff_coll_point_names(macro) \
	macro(bm) macro(bl) macro(br)

// All the collision points
#define list_of_16x32_coll_point_names(macro) \
	list_of_16x32_left_side_coll_point_names(macro) \
	list_of_16x32_right_side_coll_point_names(macro) \
	list_of_16x32_top_side_coll_point_names(macro) \
	list_of_16x32_bottom_side_coll_point_names(macro) \


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
	
	#undef X
	
	// arr_ind_16x32_count is the amount of arr_index_16x32's.  It is
	// automatically updated by the compiler.
	arr_ind_16x32_count,
} __attribute__((_align4));



// Collision points that share a side
#define list_of_32x16_left_side_coll_point_names(macro) \
	macro(lt) macro(lb)
#define list_of_32x16_right_side_coll_point_names(macro) \
	macro(rt) macro(rb)
#define list_of_32x16_top_side_coll_point_names(macro) \
	macro(tl) macro(tm) macro(tr)
#define list_of_32x16_bottom_side_coll_point_names(macro) \
	macro(bl) macro(bm) macro(br)

// Left or right side, same ypos collision points
#define list_of_32x16_vert_side_ypos_top_coll_point_names(macro) \
	macro(lt) macro(rt)
#define list_of_32x16_vert_side_ypos_bottom_coll_point_names(macro) \
	macro(lb) macro(rb)

// Top or bottom same xpos collision points
#define list_of_32x16_horiz_side_xpos_left_coll_point_names(macro) \
	macro(tl) macro(bl)
#define list_of_32x16_horiz_side_xpos_middle_coll_point_names(macro) \
	macro(tm) macro(bm)
#define list_of_32x16_horiz_side_xpos_right_coll_point_names(macro) \
	macro(tr) macro(br)

#define list_of_32x16_slope_stuff_coll_point_names(macro) \
	macro(bm) macro(bl) macro(br)

// All the collision points
#define list_of_32x16_coll_point_names(macro) \
	list_of_32x16_left_side_coll_point_names(macro) \
	list_of_32x16_right_side_coll_point_names(macro) \
	list_of_32x16_top_side_coll_point_names(macro) \
	list_of_32x16_bottom_side_coll_point_names(macro) \


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
	
	#undef X
	
	// arr_ind_32x16_count is the amount of arr_index_32x16's.  It is
	// automatically updated by the compiler.
	arr_ind_32x16_count,
} __attribute__((_align4));



#endif		// coll_point_extras_hpp
