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
	macro(lt) macro(lm) macro(lb)
#define list_of_16x16_right_side_coll_point_names(macro) \
	macro(rt) macro(rm) macro(rb)
#define list_of_16x16_top_side_coll_point_names(macro) \
	macro(tl) macro(tm) macro(tr)
#define list_of_16x16_bottom_side_coll_point_names(macro) \
	macro(bl) macro(bm) macro(br)
// Note that these are set the the same y positions as the corresponding lX
// and rX coll points.
#define list_of_16x16_middle_vert_line_coll_point_names(macro) \
	macro(mt) macro(mm) macro(mb)


// Left, middle vertical line, or right side, same ypos collision points
#define list_of_16x16_vert_side_ypos_top_coll_point_names(macro) \
	macro(lt) macro(mt) macro(rt)
#define list_of_16x16_vert_side_ypos_middle_coll_point_names(macro) \
	macro(lm) macro(mm) macro(rm)
#define list_of_16x16_vert_side_ypos_bottom_coll_point_names(macro) \
	macro(lb) macro(mb) macro(rb)

// Top or bottom same xpos collision points
#define list_of_16x16_horiz_side_xpos_left_coll_point_names(macro) \
	macro(tl) macro(bl)
#define list_of_16x16_horiz_side_xpos_middle_coll_point_names(macro) \
	macro(tm) macro(bm)
#define list_of_16x16_horiz_side_xpos_right_coll_point_names(macro) \
	macro(tr) macro(br)

// I don't think this is in use any more
#define list_of_16x16_slope_stuff_coll_point_names(macro) \
	macro(bm) macro(bl) macro(br)

// All the collision points
#define list_of_16x16_coll_point_names(macro) \
	list_of_16x16_left_side_coll_point_names(macro) \
	list_of_16x16_top_side_coll_point_names(macro) \
	list_of_16x16_right_side_coll_point_names(macro) \
	list_of_16x16_bottom_side_coll_point_names(macro) \
	list_of_16x16_middle_vert_line_coll_point_names(macro)




// Collision points that share a side
#define list_of_16x32_left_side_coll_point_names(macro) \
	macro(lt) macro(lm) macro(lb)
#define list_of_16x32_right_side_coll_point_names(macro) \
	macro(rt) macro(rm) macro(rb)
#define list_of_16x32_top_side_coll_point_names(macro) \
	macro(tl) macro(tm) macro(tr)
#define list_of_16x32_bottom_side_coll_point_names(macro) \
	macro(bl) macro(bm) macro(br)
// Note that these are set the the same y positions as the corresponding lX
// and rX coll points.
#define list_of_16x32_middle_vert_line_coll_point_names(macro) \
	macro(mt) macro(mm) macro(mb)


// Left, middle vertical line, or right side, same ypos collision points
#define list_of_16x32_vert_side_ypos_top_coll_point_names(macro) \
	macro(lt) macro(mt) macro(rt)
#define list_of_16x32_vert_side_ypos_middle_coll_point_names(macro) \
	macro(lm) macro(mm) macro(rm)
#define list_of_16x32_vert_side_ypos_bottom_coll_point_names(macro) \
	macro(lb) macro(mb) macro(rb)

// Top or bottom same xpos collision points
#define list_of_16x32_horiz_side_xpos_left_coll_point_names(macro) \
	macro(tl) macro(bl)
#define list_of_16x32_horiz_side_xpos_middle_coll_point_names(macro) \
	macro(tm) macro(bm)
#define list_of_16x32_horiz_side_xpos_right_coll_point_names(macro) \
	macro(tr) macro(br)

// I don't think this is in use any more
#define list_of_16x32_slope_stuff_coll_point_names(macro) \
	macro(bm) macro(bl) macro(br)

// All the collision points
#define list_of_16x32_coll_point_names(macro) \
	list_of_16x32_left_side_coll_point_names(macro) \
	list_of_16x32_top_side_coll_point_names(macro) \
	list_of_16x32_right_side_coll_point_names(macro) \
	list_of_16x32_bottom_side_coll_point_names(macro) \
	list_of_16x32_middle_vert_line_coll_point_names(macro)




// Collision points that share a side
#define list_of_32x16_left_side_coll_point_names(macro) \
	macro(lt) macro(lm) macro(lb)
#define list_of_32x16_right_side_coll_point_names(macro) \
	macro(rt) macro(rm) macro(rb)
#define list_of_32x16_top_side_coll_point_names(macro) \
	macro(tl) macro(tm) macro(tr)
#define list_of_32x16_bottom_side_coll_point_names(macro) \
	macro(bl) macro(bm) macro(br)
// Note that these are set the the same y positions as the corresponding lX
// and rX coll points.
#define list_of_32x16_middle_vert_line_coll_point_names(macro) \
	macro(mt) macro(mm) macro(mb)


// Left, middle vertical line, or right side, same ypos collision points
#define list_of_32x16_vert_side_ypos_top_coll_point_names(macro) \
	macro(lt) macro(mt) macro(rt)
#define list_of_32x16_vert_side_ypos_middle_coll_point_names(macro) \
	macro(lm) macro(mm) macro(rm)
#define list_of_32x16_vert_side_ypos_bottom_coll_point_names(macro) \
	macro(lb) macro(mb) macro(rb)

// Top or bottom same xpos collision points
#define list_of_32x16_horiz_side_xpos_left_coll_point_names(macro) \
	macro(tl) macro(bl)
#define list_of_32x16_horiz_side_xpos_middle_coll_point_names(macro) \
	macro(tm) macro(bm)
#define list_of_32x16_horiz_side_xpos_right_coll_point_names(macro) \
	macro(tr) macro(br)

// I don't think this is in use any more
#define list_of_32x16_slope_stuff_coll_point_names(macro) \
	macro(bm) macro(bl) macro(br)

// All the collision points
#define list_of_32x16_coll_point_names(macro) \
	list_of_32x16_left_side_coll_point_names(macro) \
	list_of_32x16_top_side_coll_point_names(macro) \
	list_of_32x16_right_side_coll_point_names(macro) \
	list_of_32x16_bottom_side_coll_point_names(macro) \
	list_of_32x16_middle_vert_line_coll_point_names(macro)


#endif		// coll_point_extras_hpp
