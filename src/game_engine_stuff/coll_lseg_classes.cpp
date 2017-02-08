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


bool generic_coll_lseg::intersects( const generic_coll_lseg& to_check,
	vec2_f24p8* ret ) const
{
	const vec2_f24p8& p = end_points[0];
	const vec2_f24p8& r = end_points[1];
	
	const vec2_f24p8& q = to_check.end_points[0];
	const vec2_f24p8& s = to_check.end_points[1];
	
	fixed24p8 t, u;
	
	const vec2_f24p8 q_minus_p = q - p;
	const fixed24p8 r_cross_s = r.zcross(s);
	
	
	if ( r_cross_s != (fixed24p8){0} )
	{
	}
	
	
	return false;
}

bool coll_lseg_extras::collinear_lsegs_intersect
	( const fixed24p8& a_0, const fixed24p8& a_1, const fixed24p8& b_0, 
	const fixed24p8& b_1 )
{
	return ( in_range_inclusive( a_0, a_1, b_0 ) 
		|| in_range_inclusive( a_0, a_1, b_1 )
		|| in_range_inclusive( b_0, b_1, a_0 ) 
		|| in_range_inclusive( b_0, b_1, a_1 ) );
}
