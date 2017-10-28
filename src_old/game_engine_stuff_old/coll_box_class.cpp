// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
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


#include "coll_box_class.hpp"
#include "../general_utility_stuff/debug_vars.hpp"


//int coll_box_intersects_now(const CollBox& a, const CollBox& b)
//{
//	//return !((b.left().data + 1) > (a.right().data - 1)
//	//	|| (b.right().data - 1) < (a.left().data + 1)
//	//	|| (b.top().data + 1) > (a.bot().data - 1)
//	//	|| (b.bot().data - 1) < (a.top().data + 1));
//
//	return !(b.left() > a.right()
//		|| b.right() < a.left()
//		|| b.top() > a.bot()
//		|| b.bot() < a.top());
//}
//
//int coll_box_intersects_now_2(const CollBox& a, const CollBox& b)
//{
//	return !((b.left().data + 1) >= (a.right().data - 1)
//		|| (b.right().data - 1) <= (a.left().data + 1)
//		|| (b.top().data + 1) >= (a.bot().data - 1)
//		|| b.bot() <= a.top());
//}


int CollBox::Contains(const Vec2F24p8& point)
{
	if (point.x > left() && point.x < right() 
		&& point.y > top() && point.y < bot())
	{
		return true;
	}

	return false;
}



void CollBox::set_side_coords(Fixed24p8 left_x, Fixed24p8 right_x,
	Fixed24p8 top_y, Fixed24p8 bot_y)
{
	pos = { left_x, top_y };
	size = { right_x - left_x, bot_y - top_y };
}



void CollBox::get_corners(Vec2F24p8& lt_corner, Vec2F24p8& rt_corner, 
	Vec2F24p8& rb_corner, Vec2F24p8& lb_corner)
{
	lt_corner.x = lb_corner.x = left();
	rt_corner.x = rb_corner.x = right();

	lt_corner.y = rt_corner.y = top();
	lb_corner.y = rb_corner.y = bot();
}



void CollBox::get_block_coords_intersected_by_corners 
	(Vec2s32& lt_block_coord, Vec2s32& rt_block_coord,
	Vec2s32& rb_block_coord, Vec2s32& lb_block_coord)
{

	lt_block_coord.x = lb_block_coord.x = left().round_to_int() >> 4;
	rt_block_coord.x = rb_block_coord.x = right().round_to_int() >> 4;

	lt_block_coord.y = rt_block_coord.y = top().round_to_int() >> 4;
	lb_block_coord.y = rb_block_coord.y = bot().round_to_int() >> 4;

}



int coll_box_intersects_now(const CollBox& a, const CollBox& b)
{
	//return !((b.left().data + 1) > (a.right().data - 1)
	//	|| (b.right().data - 1) < (a.left().data + 1)
	//	|| (b.top().data + 1) > (a.bot().data - 1)
	//	|| (b.bot().data - 1) < (a.top().data + 1));

	return !(b.left() > a.right()
		|| b.right() < a.left()
		|| b.top() > a.bot()
		|| b.bot() < a.top());
}

int coll_box_intersects_now_2(const CollBox& a, const CollBox& b)
{
	return !((b.left().data + 1) >= (a.right().data - 1)
		|| (b.right().data - 1) <= (a.left().data + 1)
		|| (b.top().data + 1) >= (a.bot().data - 1)
		|| b.bot() <= a.top());
}
