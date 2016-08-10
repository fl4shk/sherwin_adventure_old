// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#ifndef coll_point_extras_hpp
#define coll_point_extras_hpp

#include "../gba_specific_stuff/attribute_defines.hpp"

// Collision points that share a side
#define list_of_shared_left_side_coll_point_names(macro) \
	macro(lt) macro(lm) macro(lb)
#define list_of_shared_right_side_coll_point_names(macro) \
	macro(rt) macro(rm) macro(rb)
#define list_of_shared_top_side_coll_point_names(macro) \
	macro(tl) macro(tm) macro(tr)
#define list_of_shared_bot_side_coll_point_names(macro) \
	macro(bl) macro(bm) macro(br)


// Left or right side, same ypos collision points
#define list_of_shared_vert_side_ypos_top_coll_point_names(macro) \
	macro(lt) macro(rt)
#define list_of_shared_vert_side_ypos_mid_coll_point_names(macro) \
	macro(lm) macro(rm)
#define list_of_shared_vert_side_ypos_bot_coll_point_names(macro) \
	macro(lb) macro(rb)

// Top or bot same xpos collision points
#define list_of_shared_horiz_side_xpos_left_coll_point_names(macro) \
	macro(tl) macro(bl)
#define list_of_shared_horiz_side_xpos_mid_coll_point_names(macro) \
	macro(tm) macro(bm)
#define list_of_shared_horiz_side_xpos_right_coll_point_names(macro) \
	macro(tr) macro(br)

// I don't think this is in use any more
#define list_of_shared_slope_stuff_coll_point_names(macro) \
	macro(bm) macro(bl) macro(br)

// All the collision points
#define list_of_shared_coll_point_names(macro) \
	list_of_shared_left_side_coll_point_names(macro) \
	list_of_shared_top_side_coll_point_names(macro) \
	list_of_shared_right_side_coll_point_names(macro) \
	list_of_shared_bot_side_coll_point_names(macro)




#endif		// coll_point_extras_hpp
