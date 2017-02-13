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




//const fixed24p8 coll_lseg_group_16x32::offset_x_for_any_hs_left
//	= make_f24p8(2);
const fixed24p8 coll_lseg_group_16x32::offset_x_for_any_hs_left
	= make_f24p8(0);
const fixed24p8 coll_lseg_group_16x32::offset_x_for_any_hs_right
	= make_f24p8(-coll_lseg_group_16x32::offset_x_for_any_hs_left.data);

//const fixed24p8 coll_lseg_group_16x32::offset_y_for_top_hs
//	= make_f24p8(-7);
//const fixed24p8 coll_lseg_group_16x32::offset_y_for_bot_hs
//	= (fixed24p8){-coll_lseg_group_16x32::offset_y_for_top_hs.data};

////const fixed24p8 coll_lseg_group_16x32::offset_x_for_left_vs
////	= make_f24p8(3);
//const fixed24p8 coll_lseg_group_16x32::offset_x_for_left_vs
//	= make_f24p8(4);
//const fixed24p8 coll_lseg_group_16x32::offset_x_for_right_vs
//	= (fixed24p8){-coll_lseg_group_16x32::offset_x_for_left_vs.data};

const fixed24p8 coll_lseg_group_16x32::vs_height_non_bot_mid_og
	= make_f24p8(num_pixels_per_block_dim);
//const fixed24p8 coll_lseg_group_16x32::vs_height_bot_mid_og
//	= custom_abs(coll_lseg_group_16x32::offset_y_for_bot_vs)
//	- make_f24p8(1);
//const fixed24p8 coll_lseg_group_16x32::vs_height_bot_mid_og
//	= make_f24p8(2);
const fixed24p8 coll_lseg_group_16x32::vs_height_bot_mid_og
	= vs_height_non_bot_mid_og;

// In-air top vertical sensors stretch a small number of pixels vertically
// outside s_coll_box
const fixed24p8 coll_lseg_group_16x32::vs_height_top
	= coll_lseg_group_16x32::offset_y_for_top_vs + make_f24p8(2);
const fixed24p8 coll_lseg_group_16x32::vs_height_bot_ia
	= coll_lseg_group_16x32::offset_y_for_top_vs + make_f24p8(1);
//const fixed24p8 coll_lseg_group_16x32::vs_height_bot_ia
//	= coll_lseg_group_16x32::offset_y_for_top_vs + make_f24p8(4);
//const fixed24p8 coll_lseg_group_16x32::vs_height_bot_ia
//	= coll_lseg_group_16x32::offset_y_for_top_vs + make_f24p8(8);

const fixed24p8 coll_lseg_group_16x32::offset_y_for_top_vs
	= make_f24p8(4);
//const fixed24p8 coll_lseg_group_16x32::offset_y_for_bot_vs
//	= make_f24p8(-4);
const fixed24p8 coll_lseg_group_16x32::offset_y_for_bot_vs
	= (fixed24p8){-coll_lseg_group_16x32::offset_y_for_top_vs.data};


coll_lseg_group_16x32::coll_lseg_group_16x32( const coll_box& s_coll_box,
	u32 s_on_ground )
{
	init( s_coll_box, s_on_ground );
}

void coll_lseg_group_16x32::init( const coll_box& s_coll_box, 
	u32 s_on_ground )
{
	init_arr_helpers();
	
	internal_on_ground = s_on_ground;
	
	
	horiz_ctups[hi_left_top].clseg = get_left_top_hs(s_coll_box);
	horiz_ctups[hi_left_mid].clseg = get_left_mid_hs(s_coll_box);
	horiz_ctups[hi_left_bot].clseg = get_left_bot_hs(s_coll_box);
	
	horiz_ctups[hi_right_top].clseg = get_right_top_hs(s_coll_box);
	horiz_ctups[hi_right_mid].clseg = get_right_mid_hs(s_coll_box);
	horiz_ctups[hi_right_bot].clseg = get_right_bot_hs(s_coll_box);
	
	vert_top_ctups[vi_top_left].clseg = get_top_left_vs(s_coll_box);
	vert_top_ctups[vi_top_mid].clseg = get_top_mid_vs(s_coll_box);
	vert_top_ctups[vi_top_right].clseg = get_top_right_vs(s_coll_box);
	
	if ( get_on_ground() )
	{
		vert_bot_ctups[vi_bot_left].clseg 
			= get_bot_left_vs_og(s_coll_box);
		vert_bot_ctups[vi_bot_mid].clseg 
			= get_bot_mid_vs_og(s_coll_box);
		vert_bot_ctups[vi_bot_right].clseg 
			= get_bot_right_vs_og(s_coll_box);
	}
	else // if ( !get_on_ground() )
	{
		vert_bot_ctups[vi_bot_left].clseg 
			= get_bot_left_vs_ia(s_coll_box);
		vert_bot_ctups[vi_bot_mid].clseg 
			= get_bot_mid_vs_ia(s_coll_box);
		vert_bot_ctups[vi_bot_right].clseg 
			= get_bot_right_vs_ia(s_coll_box);
	}
	
	for ( size_t i=0; i<num_horiz_ctups; ++i )
	{
		horiz_ctups[i].bcrlg.init(horiz_ctups[i].clseg);
	}
	for ( size_t i=0; i<num_vert_top_ctups; ++i )
	{
		vert_top_ctups[i].bcrlg.init(vert_top_ctups[i].clseg);
	}
	for ( size_t i=0; i<num_vert_bot_ctups; ++i )
	{
		vert_bot_ctups[i].bcrlg.init(vert_bot_ctups[i].clseg);
	}
	
	
}

void coll_lseg_group_16x32::init_arr_helpers()
{
	horiz_ctups.init( horiz_ctups_arr, num_horiz_ctups );
	vert_top_ctups.init( vert_top_ctups_arr, num_vert_top_ctups );
	vert_bot_ctups.init( vert_bot_ctups_arr, num_vert_bot_ctups );
}

const fixed24p8 coll_lseg_group_16x32::get_pos_x_for_left_hs
	( const coll_box& s_coll_box )
{
	return s_coll_box.left() + offset_x_for_any_hs_left;
}
const fixed24p8 coll_lseg_group_16x32::get_pos_x_for_right_hs
	( const coll_box& s_coll_box )
{
	return s_coll_box.get_x_center() + offset_x_for_any_hs_right;
}


// "hs" means "horizontal sensor"
// "og" means "on ground"
const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_top_hs
	( const coll_box& s_coll_box )
{
	//return s_coll_box.get_y_center() + offset_y_for_top_hs;
	return s_coll_box.get_y_center() 
		- (fixed24p8){ ( s_coll_box.size.y.data / 4 )
		+ ( s_coll_box.size.y.data / 8 )
		+ ( s_coll_box.size.y.data / 16 ) };
}
const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_mid_hs
	( const coll_box& s_coll_box )
{
	return s_coll_box.get_y_center();
}
const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_bot_hs
	( const coll_box& s_coll_box )
{
	//return s_coll_box.get_y_center() + offset_y_for_bot_hs;
	return s_coll_box.get_y_center() 
		+ (fixed24p8){ ( s_coll_box.size.y.data / 4 )
		+ ( s_coll_box.size.y.data / 8 )
		+ ( s_coll_box.size.y.data / 16 ) };
}

const horiz_coll_lseg coll_lseg_group_16x32::get_left_top_hs
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(s_coll_box),
		get_pos_y_for_top_hs(s_coll_box) ), 
		s_coll_box.half_width() );
}
const horiz_coll_lseg coll_lseg_group_16x32::get_left_mid_hs
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(s_coll_box),
		get_pos_y_for_mid_hs(s_coll_box) ), 
		s_coll_box.half_width() );
}
const horiz_coll_lseg coll_lseg_group_16x32::get_left_bot_hs
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(s_coll_box),
		get_pos_y_for_bot_hs(s_coll_box) ), 
		s_coll_box.half_width() );
}

const horiz_coll_lseg coll_lseg_group_16x32::get_right_top_hs
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(s_coll_box),
		get_pos_y_for_top_hs(s_coll_box) ), 
		s_coll_box.half_width() );
}
const horiz_coll_lseg coll_lseg_group_16x32::get_right_mid_hs
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(s_coll_box),
		get_pos_y_for_mid_hs(s_coll_box) ), 
		s_coll_box.half_width() );
}
const horiz_coll_lseg coll_lseg_group_16x32::get_right_bot_hs
	( const coll_box& s_coll_box )
{
	return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(s_coll_box),
		get_pos_y_for_bot_hs(s_coll_box) ), 
		s_coll_box.half_width() );
}


// "ia" means "in air"
// "vs" means "vertical sensor"
const fixed24p8 coll_lseg_group_16x32::get_pos_x_for_left_vs
	( const coll_box& s_coll_box )
{
	//return s_coll_box.left() + offset_x_for_left_vs;
	return s_coll_box.left() + (fixed24p8){ s_coll_box.size.x.data / 4 };
}
const fixed24p8 coll_lseg_group_16x32::get_pos_x_for_mid_vs
	( const coll_box& s_coll_box )
{
	return s_coll_box.get_x_center();
}
const fixed24p8 coll_lseg_group_16x32::get_pos_x_for_right_vs
	( const coll_box& s_coll_box )
{
	//return s_coll_box.right() + offset_x_for_right_vs;
	return s_coll_box.right() 
		- (fixed24p8){ s_coll_box.size.x.data / 4 };
}

const fixed24p8 coll_lseg_group_16x32::get_pos_y_for_top_vs
	( const coll_box& s_coll_box )
{
	return s_coll_box.top() - vs_height_top + offset_y_for_top_vs;
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
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_non_bot_mid_og );
}
const vert_coll_lseg coll_lseg_group_16x32::get_bot_mid_vs_og
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(s_coll_box),
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_bot_mid_og );
}
const vert_coll_lseg coll_lseg_group_16x32::get_bot_right_vs_og
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box), 
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_non_bot_mid_og );
}


const vert_coll_lseg coll_lseg_group_16x32::get_bot_left_vs_ia
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(s_coll_box), 
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_bot_ia );
}
const vert_coll_lseg coll_lseg_group_16x32::get_bot_mid_vs_ia
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(s_coll_box),
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_bot_ia );
}
const vert_coll_lseg coll_lseg_group_16x32::get_bot_right_vs_ia
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box), 
		get_pos_y_for_bot_vs(s_coll_box) ), vs_height_bot_ia );
}



const vert_coll_lseg coll_lseg_group_16x32::get_top_left_vs
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(s_coll_box),
		get_pos_y_for_top_vs(s_coll_box) ), vs_height_top );
}
const vert_coll_lseg coll_lseg_group_16x32::get_top_mid_vs
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(s_coll_box),
		get_pos_y_for_top_vs(s_coll_box) ), vs_height_top );
}
const vert_coll_lseg coll_lseg_group_16x32::get_top_right_vs
	( const coll_box& s_coll_box )
{
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box),
		get_pos_y_for_top_vs(s_coll_box) ), vs_height_top );
}

