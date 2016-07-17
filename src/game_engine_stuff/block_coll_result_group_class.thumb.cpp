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


#include "block_coll_result_group_class.hpp"
#include "level_stuff/active_level_class.hpp"

#include "block_stuff/block_stuff.hpp"

block_coll_result::block_coll_result( const vec2_s32& s_coord )
	: coord(s_coord)
{
	the_block = &active_level::the_block_data_at_coord(coord);
	the_bbvt = get_behavior_type_of_block_type(get_block_type());
}
block_coll_result::block_coll_result( const vec2_f24p8& s_coord_f24p8 )
	: block_coll_result(active_level::get_block_coord_of_point
	(s_coord_f24p8))
{
}



u32 block_coll_result_group::temp_debug_thing;



block_coll_result_group::block_coll_result_group
	( const coll_box& the_coll_box, u32 s_moving_left, u32 s_moving_right )
{
	arr_memfill32( bcr_arr_2d_helper_data, 0, max_size );
	
	start_pos = active_level::get_block_coord_of_point( vec2_f24p8
		( the_coll_box.left(), the_coll_box.top() ) );
	const vec2_s32 end_pos = active_level::get_block_coord_of_point
		( vec2_f24p8( the_coll_box.right(), the_coll_box.bot() ) );
	real_size_2d = end_pos - start_pos + vec2_s32( 1, 1 );
	
	moving_left = s_moving_left;
	moving_right = s_moving_right;
	
	bcr_arr_2d_helper.init( bcr_arr_2d_helper_data, vec2_u32( real_width(), 
		real_height() ) );
	
	for ( s32 j=0; j<real_height(); ++j )
	{
		for ( s32 i=0; i<real_width(); ++i )
		{
			bcr_arr_2d_helper.data_at( i, j ) = block_coll_result
				( tl_corner() + vec2_s32( i, j ) );
		}
	}
	
	
}
block_coll_result_group::block_coll_result_group
	( const block_coll_result_group& to_copy )
{
	*this = to_copy;
}
block_coll_result_group& block_coll_result_group::operator = 
	( const block_coll_result_group& to_copy )
{
	arr_memcpy32( (block_coll_result*)bcr_arr_2d_helper_data, 
		to_copy.bcr_arr_2d_helper_data, sizeof(bcr_arr_2d_helper_data) );
	real_size_2d = to_copy.real_size_2d;
	
	start_pos = to_copy.start_pos;
	
	moving_left = to_copy.moving_left;
	moving_right = to_copy.moving_right;
	
	bcr_arr_2d_helper = to_copy.bcr_arr_2d_helper;
	
	
	
	return *this;
}



void block_coll_result_group::get_corner_stuff
	( block_coll_result*& top_corner_bcr, 
	block_coll_result*& bot_corner_bcr, u32& top_corner_is_non_air,
	u32& bot_corner_is_non_air )
{
	vec2_s32 local_top_corner = local_tl_corner(),
		local_bot_corner = local_bl_corner();
	
	if (moving_left)
	{
		//local_top_corner.x = local_bot_corner.x = local_left();
	}
	else if (moving_right)
	{
		local_top_corner.x = local_bot_corner.x = local_right();
	}
	
	
	//top_corner_is_non_air = ( bcr_arr_2d_helper.data_at
	//	(local_top_corner).the_bbvt != bbvt_air );
	//bot_corner_is_non_air = ( bcr_arr_2d_helper.data_at
	//	(local_bot_corner).the_bbvt != bbvt_air );
	
	top_corner_bcr = &bcr_arr_2d_helper.data_at(local_top_corner);
	bot_corner_bcr = &bcr_arr_2d_helper.data_at(local_bot_corner);
	
	top_corner_is_non_air = ( top_corner_bcr->the_bbvt != bbvt_air );
	bot_corner_is_non_air = ( bot_corner_bcr->the_bbvt != bbvt_air );
	
	temp_debug_thing = 0;
	if (top_corner_is_non_air)
	{
		temp_debug_thing = 7;
	}
}


void block_coll_result_group::get_coll_box_related_stuff
	( const coll_box& the_coll_box, const fixed24p8& vel_y, 
	vec2_s32& adjusted_cb_top_corner_lbc,
	vec2_s32& adjusted_cb_bot_corner_lbc,
	block_coll_result*& adjusted_cb_top_corner_bcr,
	block_coll_result*& adjusted_cb_bot_corner_bcr )
{
	vec2_f24p8 cb_top_corner_f24p8( the_coll_box.left(), 
		the_coll_box.top() ), cb_bot_corner_f24p8( the_coll_box.left(),
		the_coll_box.bot() );
	
	if (moving_left)
	{
		//cb_top_corner_f24p8.x = cb_bot_corner_f24p8.x = the_coll_box
		//	.left();
	}
	else if (moving_right)
	{
		cb_top_corner_f24p8.x = cb_bot_corner_f24p8.x = the_coll_box
			.right();
	}
	
	// The local block coords
	adjusted_cb_top_corner_lbc = active_level::get_block_coord_of_point
		( cb_top_corner_f24p8 - vec2_f24p8( {0}, vel_y ) ) - tl_corner();
	adjusted_cb_bot_corner_lbc = active_level::get_block_coord_of_point
		( cb_bot_corner_f24p8 - vec2_f24p8( {0}, vel_y ) ) - tl_corner();
	
	if (contains_local_block_coord(adjusted_cb_top_corner_lbc))
	{
		adjusted_cb_top_corner_bcr = &bcr_arr_2d_helper.data_at
			(adjusted_cb_top_corner_lbc);
	}
	if (contains_local_block_coord(adjusted_cb_bot_corner_lbc))
	{
		adjusted_cb_bot_corner_bcr = &bcr_arr_2d_helper.data_at
			(adjusted_cb_bot_corner_lbc);
	}
}

void block_coll_result_group::get_side_blocked_stuff
	( u32& vert_side_below_top_corner_is_blocked,
	u32& vert_side_above_bot_corner_is_blocked,
	u32& top_side_other_than_corner_is_blocked,
	u32& bot_side_other_than_corner_is_blocked )
{
	vert_side_below_top_corner_is_blocked 
		= vert_side_above_bot_corner_is_blocked
		= top_side_other_than_corner_is_blocked 
		= bot_side_other_than_corner_is_blocked = false;
	
	s32 local_vert_side_x = local_left();
	
	s32 part_2_range_start = local_left() + 1, 
		part_2_range_end_plus_1 = local_right() + 1;
	
	if (moving_left)
	{
		//local_vert_side_x = local_left();
		
		//part_2_range_start = local_left() + 1;
		//part_2_range_end_plus_1 = local_right() + 1;
	}
	else if (moving_right)
	{
		local_vert_side_x = local_right();
		
		//part_2_range_start = local_left();
		//part_2_range_end_plus_1 = local_right();
		--part_2_range_start;
		--part_2_range_end_plus_1;
	}
	
	for ( s32 j=local_top()+1; j<real_height(); ++j )
	{
		if ( bcr_arr_2d_helper.data_at( local_vert_side_x, j ).the_bbvt 
			!= bbvt_air )
		{
			vert_side_below_top_corner_is_blocked = true;
			break;
		}
	}
	
	for ( s32 j=local_top(); j<real_height()-1; ++j )
	{
		if ( bcr_arr_2d_helper.data_at( local_vert_side_x, j ).the_bbvt 
			!= bbvt_air )
		{
			vert_side_above_bot_corner_is_blocked = true;
			break;
		}
	}
	
	
	
	for ( s32 i=part_2_range_start; i<part_2_range_end_plus_1; ++i )
	{
		// Check whether the top
		if ( bcr_arr_2d_helper.data_at( i, local_top() ).the_bbvt 
			!= bbvt_air )
		{
			top_side_other_than_corner_is_blocked = true;
		}
		
		if ( bcr_arr_2d_helper.data_at( i, local_bot() ).the_bbvt 
			!= bbvt_air )
		{
			bot_side_other_than_corner_is_blocked = true;
		}
	}
}


