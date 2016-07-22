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


#include "coll_point_group_classes.hpp"
#include "sprite_stuff/sprite_class.hpp"

// Thursday, July 23, 2015 (9:35 PM EST) Note: I will use a top middle coll
// point and a bottom middle coll point, starting tomorrow.  

// The top middle coll point will be used for checking the type of block
// that has been hit by a sprite that has jumped.  

// The bottom middle coll point will be used
// as the primary thing for checking if a sprite is on the ground.


// Friday, October 23, 2015 (12:10 PM CST) Lol, I forgot that the first
// comment was there.

#define generate_pt(name) \
	vec2_f24p8 & pt_##name = get_pt_##name();
#define X(name) \
	pt_##name.x =
#define Y(name) \
	pt_##name.y =


coll_point_group_16x16::coll_point_group_16x16( const sprite& the_sprite )
{
	const coll_box& the_coll_box = the_sprite.the_coll_box;
	
	// The collision points
	list_of_16x16_coll_point_names(generate_pt)
	
	// Left and Right
	//pt_lt.x = pt_lb.x = the_coll_box.left();
	
	//pt_rt.x = pt_rb.x = the_coll_box.right();
	
	list_of_16x16_left_side_coll_point_names(X) 
		the_coll_box.left();
	
	list_of_16x16_right_side_coll_point_names(X) 
		the_coll_box.right();
	
	list_of_16x16_middle_vert_line_coll_point_names(X)
		the_coll_box.left() + (fixed24p8){ the_coll_box.size.x.data / 2 };
	
	
	
	list_of_16x16_vert_side_ypos_top_coll_point_names(Y) 
		the_coll_box.top() + (fixed24p8){ the_coll_box.size.y.data / 4 };
	//list_of_16x16_vert_side_ypos_top_coll_point_names(Y) 
	//	the_coll_box.top();
	
	list_of_16x16_vert_side_ypos_middle_coll_point_names(Y)
		the_coll_box.top() + (fixed24p8){ the_coll_box.size.y.data / 2 };
	
	list_of_16x16_vert_side_ypos_bottom_coll_point_names(Y) 
		the_coll_box.bot() - (fixed24p8){ the_coll_box.size.y.data / 4 };
	//list_of_16x16_vert_side_ypos_bottom_coll_point_names(Y) 
	//	the_coll_box.bot();
	
	
	
	
	// Top and Bottom
	//list_of_16x16_horiz_side_xpos_left_coll_point_names(X)
	//	the_coll_box.left() + (fixed24p8){0x400};
	//list_of_16x16_horiz_side_xpos_left_coll_point_names(X)
	//	the_coll_box.left() + (fixed24p8){0x480};
	list_of_16x16_horiz_side_xpos_left_coll_point_names(X)
		the_coll_box.left();
	
	list_of_16x16_horiz_side_xpos_middle_coll_point_names(X)
		the_coll_box.left() + (fixed24p8){ the_coll_box.size.x.data / 2 };
	
	//list_of_16x16_horiz_side_xpos_right_coll_point_names(X)
	//	the_coll_box.right() - (fixed24p8){0x400};
	//list_of_16x16_horiz_side_xpos_right_coll_point_names(X)
	//	the_coll_box.right() - (fixed24p8){0x480};
	list_of_16x16_horiz_side_xpos_right_coll_point_names(X)
		the_coll_box.right();
	
	
	
	
	list_of_16x16_top_side_coll_point_names(Y)
		the_coll_box.top();
	
	// This is a special case that covers walking down a slope.  However,
	// it would be good if I could make this not needed.
	if ( the_sprite.get_curr_on_ground() 
		&& the_sprite.vel.y >= (fixed24p8){0} )
	{
		list_of_16x16_bottom_side_coll_point_names(Y)
			//the_coll_box.bot();
			//the_coll_box.bot() + (fixed24p8){0x200};
			the_coll_box.bot() + (fixed24p8){0x400};
	}
	else //if (!the_sprite.get_curr_on_ground())
	{
		list_of_16x16_bottom_side_coll_point_names(Y)
			the_coll_box.bot();
	}
	
	
}


coll_point_group_16x32::coll_point_group_16x32( const sprite& the_sprite )
{
	const coll_box& the_coll_box = the_sprite.the_coll_box;
	
	//the_pt_group.correct_num_used_points_16x32();
	
	// The collision_points
	list_of_16x32_coll_point_names(generate_pt)
	
	// Left and Right
	//pt_lt.x = pt_lm.x = pt_lb.x = the_coll_box.left();
	
	//pt_rt.x = pt_rm.x = pt_rb.x = the_coll_box.right();
	list_of_16x32_left_side_coll_point_names(X)
		the_coll_box.left();
	
	list_of_16x32_right_side_coll_point_names(X)
		the_coll_box.right();
	
	list_of_16x32_middle_vert_line_coll_point_names(X)
		the_coll_box.left() + (fixed24p8){ the_coll_box.size.x.data / 2 };
	
	
	
	list_of_16x32_vert_side_ypos_top_coll_point_names(Y)
		the_coll_box.top() + (fixed24p8){0x480};
	//list_of_16x32_vert_side_ypos_top_coll_point_names(Y)
	//	the_coll_box.top();
	
	list_of_16x32_vert_side_ypos_middle_coll_point_names(Y)
		the_coll_box.top() + (fixed24p8){ the_coll_box.size.y.data / 2 };
	
	list_of_16x32_vert_side_ypos_bottom_coll_point_names(Y)
		the_coll_box.bot() - (fixed24p8){0x480};
	//list_of_16x32_vert_side_ypos_bottom_coll_point_names(Y)
	//	the_coll_box.bot();
	
	
	
	// Top and Bottom
	list_of_16x32_horiz_side_xpos_left_coll_point_names(X)
		the_coll_box.left() + (fixed24p8){0x400};
	//list_of_16x32_horiz_side_xpos_left_coll_point_names(X)
	//	the_coll_box.left() + (fixed24p8){0x480};
	//list_of_16x32_horiz_side_xpos_left_coll_point_names(X)
	//	the_coll_box.left();
	
	list_of_16x32_horiz_side_xpos_middle_coll_point_names(X)
		the_coll_box.left() + (fixed24p8){ the_coll_box.size.x.data / 2 };
	
	list_of_16x32_horiz_side_xpos_right_coll_point_names(X)
		the_coll_box.right() - (fixed24p8){0x400};
	//list_of_16x32_horiz_side_xpos_right_coll_point_names(X)
	//	the_coll_box.right() - (fixed24p8){0x480};
	//list_of_16x32_horiz_side_xpos_right_coll_point_names(X)
	//	the_coll_box.right();
	
	
	
	list_of_16x32_top_side_coll_point_names(Y)
		the_coll_box.top();
	
	// This is a special case that covers walking down a slope.  However,
	// it would be good if I could make this not needed.
	if ( the_sprite.get_curr_on_ground() 
		&& the_sprite.vel.y >= (fixed24p8){0} )
	{
		list_of_16x32_bottom_side_coll_point_names(Y)
			the_coll_box.bot() + (fixed24p8){0x400};
			//the_coll_box.bot() + (fixed24p8){0x200};
			//the_coll_box.bot() + (fixed24p8){0x300};
	}
	else //if (!the_sprite.get_curr_on_ground())
	{
		list_of_16x32_bottom_side_coll_point_names(Y)
			the_coll_box.bot();
	}
	
	
}

#undef generate_pt
#undef X
#undef Y


