// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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


#include "../general_utility_stuff/range_funcs.hpp"
#include "coll_box_class.hpp"
#include "coll_lseg_classes.hpp"


//bool generic_coll_lseg::intersects( const generic_coll_lseg& to_check,
//	vec2_f24p8* ret ) const
//{
//	const vec2_f24p8& p = end_points[0];
//	const vec2_f24p8& r = end_points[1];
//	
//	const vec2_f24p8& q = to_check.end_points[0];
//	const vec2_f24p8& s = to_check.end_points[1];
//	
//	fixed24p8 t, u;
//	
//	const fixed24p8 r_zcross_s = r.zcross(s);
//	
//	const vec2_f24p8 q_minus_p = q - p;
//	
//	const fixed24p8 u_num = q_minus_p.zcross(s);
//	
//	if ( r_zcross_s != (fixed24p8){0} )
//	{
//		const fixed24p8 t_num = q_minus_p.zcross(r);
//		
//		
//		if ( ret != NULL )
//		{
//			
//		}
//	}
//	else if ( u_num == (fixed24p8){0} )
//	{
//		const fixed24p8 r_dot_r = r.dot(r);
//		const fixed24p8 s_dot_r = s.dot(r);
//		const fixed24p8 t_0 = q_minus_p.dot(r) / r_dot_r;
//		const fixed24p8 t_1 = t_0 + ( s_dot_r / r_dot_r );
//		
//		const bool t01_in_range_0_to_1 
//			= in_range_inclusive( t_0, make_f24p8(0), make_f24p8(1) )
//			|| in_range_inclusive( t_1, make_f24p8(0), make_f24p8(1) );
//		
//		if (!t01_in_range_0_to_1)
//		{
//			if ( s_dot_r < make_f24p8(0) )
//			{
//				
//			}
//			else
//			{
//				
//			}
//		}
//		return true;
//	}
//	
//	return false;
//}

bool coll_lseg_extras::collinear_lsegs_intersect
	( const fixed24p8& a_0, const fixed24p8& a_1, const fixed24p8& b_0, 
	const fixed24p8& b_1 )
{
	return ( in_range_inclusive( a_0, a_1, b_0 ) 
		|| in_range_inclusive( a_0, a_1, b_1 )
		|| in_range_inclusive( b_0, b_1, a_0 ) 
		|| in_range_inclusive( b_0, b_1, a_1 ) );
}



const fixed24p8 coll_lseg_group_16x32::offset_y_for_top_hs_og
	= make_f24p8(-4);
const fixed24p8 coll_lseg_group_16x32::offset_y_for_bot_hs_og
	= make_f24p8(4);

const fixed24p8 coll_lseg_group_16x32::offset_x_for_left_vs
	= make_f24p8(1);
const fixed24p8 coll_lseg_group_16x32::offset_x_for_right_vs
	= make_f24p8(-1);

const fixed24p8 coll_lseg_group_16x32::vs_height_og
	= make_f24p8(num_pixels_per_block_dim);
const fixed24p8 coll_lseg_group_16x32::vs_height_ia
	= make_f24p8(1);

const fixed24p8 coll_lseg_group_16x32::offset_y_for_top_vs_ia
	= make_f24p8(1);
const fixed24p8 coll_lseg_group_16x32::offset_y_for_bot_vs
	= make_f24p8(-1);


coll_lseg_group_16x32::coll_lseg_group_16x32( const coll_box& s_coll_box,
	u32 s_on_ground )
{
	init( s_coll_box, s_on_ground );
}

void coll_lseg_group_16x32::init( const coll_box& s_coll_box, 
	u32 s_on_ground )
{
	internal_on_ground = s_on_ground;
	
	if ( get_on_ground() )
	{
		horiz_ctups[the_hi_left_top_og].clseg 
			= get_left_top_hs_og(s_coll_box);
		horiz_ctups[the_hi_left_bot_og].clseg 
			= get_left_bot_hs_og(s_coll_box);
		horiz_ctups[the_hi_right_top_og].clseg 
			= get_right_top_hs_og(s_coll_box);
		horiz_ctups[the_hi_right_bot_og].clseg 
			= get_right_bot_hs_og(s_coll_box);
		
		vert_ctups[the_vi_bot_left_og].clseg 
			= get_bot_left_vs_og(s_coll_box);
		vert_ctups[the_vi_bot_mid_og].clseg 
			= get_bot_mid_vs_og(s_coll_box);
		vert_ctups[the_vi_bot_right_og].clseg 
			= get_bot_right_vs_og(s_coll_box);
	}
	else // if ( !get_on_ground() )
	{
		horiz_ctups[the_hi_left_top_ia].clseg 
			= get_left_top_hs_ia(s_coll_box);
		horiz_ctups[the_hi_left_mid_ia].clseg 
			= get_left_mid_hs_ia(s_coll_box);
		horiz_ctups[the_hi_right_top_ia].clseg 
			= get_right_top_hs_ia(s_coll_box);
		horiz_ctups[the_hi_right_mid_ia].clseg 
			= get_right_mid_hs_ia(s_coll_box);
		
		vert_ctups[the_vi_top_left_ia].clseg 
			= get_top_left_vs_ia(s_coll_box);
		vert_ctups[the_vi_top_right_ia].clseg 
			= get_top_right_vs_ia(s_coll_box);
		vert_ctups[the_vi_bot_left_ia].clseg 
			= get_bot_left_vs_ia(s_coll_box);
		vert_ctups[the_vi_bot_mid_ia].clseg 
			= get_bot_mid_vs_ia(s_coll_box);
		vert_ctups[the_vi_bot_right_ia].clseg 
			= get_bot_right_vs_ia(s_coll_box);
	}
	
	for ( size_t i=0; i<num_horiz_ctups; ++i )
	{
		horiz_ctups[i].bcrlg.init(horiz_ctups[i].clseg);
	}
	for ( size_t i=0; i<num_vert_ctups; ++i )
	{
		vert_ctups[i].bcrlg.init(vert_ctups[i].clseg);
	}
	
	
}

// "hs" means "horizontal sensor"
// "og" means "on ground"
const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_top_hs_og
	( const coll_box& s_coll_box )
{
	return s_coll_box.get_y_center() + offset_y_for_top_hs_og;
}
const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_bot_hs_og
	( const coll_box& s_coll_box )
{
	return s_coll_box.get_y_center() + offset_y_for_bot_hs_og;
}

const horiz_coll_lseg coll_lseg_group_16x32::get_left_top_hs_og
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( s_coll_box.left(), 
		get_pos_y_for_top_hs_og(s_coll_box) ), 
		s_coll_box.half_width() );
}
const horiz_coll_lseg coll_lseg_group_16x32::get_right_top_hs_og
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( s_coll_box.get_x_center(), 
		get_pos_y_for_top_hs_og(s_coll_box) ), 
		s_coll_box.half_width() );
}

const horiz_coll_lseg coll_lseg_group_16x32::get_left_bot_hs_og
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( s_coll_box.left(), 
		get_pos_y_for_bot_hs_og(s_coll_box) ), 
		s_coll_box.half_width() );
}
const horiz_coll_lseg coll_lseg_group_16x32::get_right_bot_hs_og
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( s_coll_box.get_x_center(), 
		get_pos_y_for_bot_hs_og(s_coll_box) ), 
		s_coll_box.half_width() );
}


// "ia" means "in air"
const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_top_hs_ia
	( const coll_box& s_coll_box )
{
	return s_coll_box.top();
}
const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_mid_hs_ia
	( const coll_box& s_coll_box )
{
	return s_coll_box.get_y_center();
}

const horiz_coll_lseg coll_lseg_group_16x32::get_left_top_hs_ia
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( s_coll_box.left(), 
		get_pos_y_for_top_hs_ia(s_coll_box) ), 
		s_coll_box.half_width() );
}
const horiz_coll_lseg coll_lseg_group_16x32::get_right_top_hs_ia
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( s_coll_box.get_x_center(), 
		get_pos_y_for_top_hs_ia(s_coll_box) ), 
		s_coll_box.half_width() );
}

const horiz_coll_lseg coll_lseg_group_16x32::get_left_mid_hs_ia
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( s_coll_box.left(), 
		get_pos_y_for_mid_hs_ia(s_coll_box) ), 
		s_coll_box.half_width() );
}
const horiz_coll_lseg coll_lseg_group_16x32::get_right_mid_hs_ia
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( s_coll_box.get_x_center(), 
		get_pos_y_for_mid_hs_ia(s_coll_box) ), 
		s_coll_box.half_width() );
}


// "vs" means "vertical sensor"
const fixed24p8 coll_lseg_group_16x32::get_pos_x_for_left_vs
	( const coll_box& s_coll_box )
{
	return s_coll_box.left() + offset_x_for_left_vs;
}
const fixed24p8 coll_lseg_group_16x32::get_pos_x_for_mid_vs
	( const coll_box& s_coll_box )
{
	return s_coll_box.get_x_center();
}
const fixed24p8 coll_lseg_group_16x32::get_pos_x_for_right_vs
	( const coll_box& s_coll_box )
{
	return s_coll_box.right() + offset_x_for_right_vs;
}

const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_top_vs_ia
	( const coll_box& s_coll_box )
{
	return s_coll_box.top() - vs_height_ia + offset_y_for_top_vs_ia;
}
const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_bot_vs
	( const coll_box& s_coll_box )
{
	return s_coll_box.bot() + offset_y_for_bot_vs;
}


const vert_coll_lseg coll_lseg_group_16x32::get_bot_left_vs_og
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(s_coll_box), 
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_og );
}
const vert_coll_lseg coll_lseg_group_16x32::get_bot_mid_vs_og
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(s_coll_box),
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_og );
}
const vert_coll_lseg coll_lseg_group_16x32::get_bot_right_vs_og
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box), 
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_og );
}


const vert_coll_lseg coll_lseg_group_16x32::get_bot_left_vs_ia
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(s_coll_box), 
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_ia );
}
const vert_coll_lseg coll_lseg_group_16x32::get_bot_mid_vs_ia
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(s_coll_box),
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_ia );
}
const vert_coll_lseg coll_lseg_group_16x32::get_bot_right_vs_ia
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box), 
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_ia );
}



const vert_coll_lseg coll_lseg_group_16x32::get_top_left_vs_ia
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(s_coll_box),
		get_pos_y_for_top_vs_ia(s_coll_box) ), vs_height_ia );
}
const vert_coll_lseg coll_lseg_group_16x32::get_top_right_vs_ia
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box),
		get_pos_y_for_top_vs_ia(s_coll_box) ), vs_height_ia );
}

