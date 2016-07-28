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

#include "block_coll_result_group_classes.hpp"
#include "level_stuff/active_level_class.hpp"

#include "block_stuff/block_stuff.hpp"
#include "sprite_stuff/sprite_class.hpp"




inline void temp_func_get_horiz_adjusted_x
	( const block_coll_result_rect_group& the_bcr_group, 
	const fixed24p8& cb_vert_side_x_coord_f24p8, 
	const fixed24p8& threshold_x,
	array_helper<vec2_s32>& adjusted_cb_corner_lbc_arr_helper )
{
	vec2_s32& horiz_adjusted_cb_top_corner_lbc 
		= adjusted_cb_corner_lbc_arr_helper.data_at(0);
	vec2_s32& horiz_adjusted_cb_bot_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(1);
	
	horiz_adjusted_cb_top_corner_lbc.x = horiz_adjusted_cb_bot_corner_lbc.x
		= ( ( cb_vert_side_x_coord_f24p8 - threshold_x ).floor_to_int() 
		/ num_pixels_per_block_dim ) - the_bcr_group.left();
}
inline void temp_func_get_horiz_adjusted_y
	( const block_coll_result_rect_group& the_bcr_group, 
	const vec2_f24p8& cb_corner_y_coords, 
	array_helper<vec2_s32>& adjusted_cb_corner_lbc_arr_helper )
{
	vec2_s32& horiz_adjusted_cb_top_corner_lbc 
		= adjusted_cb_corner_lbc_arr_helper.data_at(0);
	vec2_s32& horiz_adjusted_cb_bot_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(1);
	
	const fixed24p8& cb_top_y_coord_f24p8 = cb_corner_y_coords.x;
	const fixed24p8& cb_bot_y_coord_f24p8 = cb_corner_y_coords.y;
	
	horiz_adjusted_cb_top_corner_lbc.y = ( cb_top_y_coord_f24p8
		.floor_to_int() / num_pixels_per_block_dim ) - the_bcr_group.top();
	horiz_adjusted_cb_bot_corner_lbc.y = ( cb_bot_y_coord_f24p8
		.floor_to_int() / num_pixels_per_block_dim ) - the_bcr_group.top();
}


inline void temp_func_get_vert_adjusted_x
	( const block_coll_result_rect_group& the_bcr_group, 
	const fixed24p8& cb_vert_side_x_coord_f24p8, 
	array_helper<vec2_s32>& adjusted_cb_corner_lbc_arr_helper )
{
	vec2_s32& vert_adjusted_cb_top_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(2);
	vec2_s32& vert_adjusted_cb_bot_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(3);
	
	vert_adjusted_cb_top_corner_lbc.x = vert_adjusted_cb_bot_corner_lbc.x
		= ( cb_vert_side_x_coord_f24p8.floor_to_int() 
		/ num_pixels_per_block_dim ) - the_bcr_group.left();
}
inline void temp_func_get_vert_adjusted_y
	( const block_coll_result_rect_group& the_bcr_group, 
	const vec2_f24p8& cb_corner_y_coords, const fixed24p8& threshold_y,
	array_helper<vec2_s32>& adjusted_cb_corner_lbc_arr_helper )
{
	vec2_s32& vert_adjusted_cb_top_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(2);
	vec2_s32& vert_adjusted_cb_bot_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(3);
	
	const fixed24p8& cb_top_y_coord_f24p8 = cb_corner_y_coords.x;
	const fixed24p8& cb_bot_y_coord_f24p8 = cb_corner_y_coords.y;
	
	
	vert_adjusted_cb_top_corner_lbc.y = ( ( cb_top_y_coord_f24p8 
		- threshold_y ).floor_to_int() / num_pixels_per_block_dim ) 
		- the_bcr_group.top();
	vert_adjusted_cb_bot_corner_lbc.y = ( ( cb_bot_y_coord_f24p8 
		- threshold_y ).floor_to_int() / num_pixels_per_block_dim ) 
		- the_bcr_group.top();
}






void block_coll_result_rect_group::get_corner_stuff_old
	( array_helper<block_coll_result*>& bcr_ptr_arr_helper, 
	array_helper<u32>& bool_as_u32_arr_helper )
{
	block_coll_result*& top_corner_bcr = bcr_ptr_arr_helper.data_at(0);
	block_coll_result*& bot_corner_bcr = bcr_ptr_arr_helper.data_at(1);
	
	u32& top_corner_is_non_air = bool_as_u32_arr_helper.data_at(0);
	u32& bot_corner_is_non_air = bool_as_u32_arr_helper.data_at(1);
	
	
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
}


void block_coll_result_rect_group::get_coll_box_related_stuff_old
	( const sprite& the_sprite, 
	array_helper<block_coll_result*>& bcr_ptr_arr_helper )
{
	static const u32 num_adjusted_corner_positions = 4;
	vec2_s32 adjusted_cb_corner_lbc_arr[num_adjusted_corner_positions];
	
	array_helper<vec2_s32> adjusted_cb_corner_lbc_arr_helper
		( adjusted_cb_corner_lbc_arr, num_adjusted_corner_positions );
	
	vec2_s32& horiz_adjusted_cb_top_corner_lbc 
		= adjusted_cb_corner_lbc_arr_helper.data_at(0);
	vec2_s32& horiz_adjusted_cb_bot_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(1);
	vec2_s32& vert_adjusted_cb_top_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(2);
	vec2_s32& vert_adjusted_cb_bot_corner_lbc
		= adjusted_cb_corner_lbc_arr_helper.data_at(3);
	
	block_coll_result*& horiz_adjusted_cb_top_corner_bcr
		= bcr_ptr_arr_helper.data_at(2);
	block_coll_result*& horiz_adjusted_cb_bot_corner_bcr
		= bcr_ptr_arr_helper.data_at(3);
	block_coll_result*& vert_adjusted_cb_top_corner_bcr
		= bcr_ptr_arr_helper.data_at(4);
	block_coll_result*& vert_adjusted_cb_bot_corner_bcr
		= bcr_ptr_arr_helper.data_at(5);
	
	
	const coll_box& the_coll_box = the_sprite.the_coll_box; 
	//const fixed24p8 disp_x = the_sprite.get_curr_in_level_pos().x 
	//	- the_sprite.get_prev_in_level_pos().x;
	//const fixed24p8 disp_y = the_sprite.get_curr_in_level_pos().y 
	//	- the_sprite.get_prev_in_level_pos().y;
	const fixed24p8 threshold_x = moving_right 
		? the_sprite.max_vel_x_abs_val : -the_sprite.max_vel_x_abs_val;
	const fixed24p8 threshold_y = ( the_sprite.get_curr_in_level_pos().y
		> the_sprite.get_prev_in_level_pos().y ) ? the_sprite.max_y_vel
		: -the_sprite.max_y_vel;
	
	//vec2_f24p8 cb_top_corner_f24p8( the_coll_box.left(), 
	//	the_coll_box.top() ), cb_bot_corner_f24p8( the_coll_box.left(),
	//	the_coll_box.bot() );
	//vec2_f24p8 cb_top_corner_f24p8, cb_bot_corner_f24p8;
	
	
	//cb_top_corner_f24p8.x = cb_bot_corner_f24p8.x = the_coll_box.left();
	//cb_top_corner_f24p8.y = the_coll_box.top();
	//cb_bot_corner_f24p8.y = the_coll_box.bot();
	
	
	const fixed24p8 cb_top_y_coord_f24p8 = the_coll_box.top(),
		cb_bot_y_coord_f24p8 = the_coll_box.bot();
	
	fixed24p8 cb_vert_side_x_coord_f24p8 = the_coll_box.left();
	
	if (moving_left)
	{
		////cb_top_corner_f24p8.x = cb_bot_corner_f24p8.x = the_coll_box
		////	.left();
		//cb_vert_side_x_coord_f24p8 = the_coll_box.left();
	}
	else if (moving_right)
	{
		////cb_top_corner_f24p8.x = cb_bot_corner_f24p8.x = the_coll_box
		////	.right();
		cb_vert_side_x_coord_f24p8 = the_coll_box.right();
	}
	
	
	// The local block coords
	temp_func_get_horiz_adjusted_x( *this, cb_vert_side_x_coord_f24p8,
		threshold_x, adjusted_cb_corner_lbc_arr_helper );
	temp_func_get_horiz_adjusted_y( *this, vec2_f24p8
		( cb_top_y_coord_f24p8, cb_bot_y_coord_f24p8 ), 
		adjusted_cb_corner_lbc_arr_helper );
	
	
	temp_func_get_vert_adjusted_x( *this, cb_vert_side_x_coord_f24p8,
		adjusted_cb_corner_lbc_arr_helper );
	temp_func_get_vert_adjusted_y( *this, vec2_f24p8
		( cb_top_y_coord_f24p8, cb_bot_y_coord_f24p8 ), threshold_y,
		adjusted_cb_corner_lbc_arr_helper );
	
	
	//horiz_adjusted_cb_top_corner_lbc.x = horiz_adjusted_cb_bot_corner_lbc.x
	//	= ( ( cb_vert_side_x_coord_f24p8 - threshold_x ).floor_to_int() 
	//	/ num_pixels_per_block_dim ) - left();
	//horiz_adjusted_cb_top_corner_lbc.y = ( cb_top_y_coord_f24p8
	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
	//horiz_adjusted_cb_bot_corner_lbc.y = ( cb_bot_y_coord_f24p8
	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
	
	
	//vert_adjusted_cb_top_corner_lbc.x = vert_adjusted_cb_bot_corner_lbc.x
	//	= ( cb_vert_side_x_coord_f24p8.floor_to_int() 
	//	/ num_pixels_per_block_dim ) - left();
	//vert_adjusted_cb_top_corner_lbc.y = ( ( cb_top_y_coord_f24p8 - threshold_y )
	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
	//vert_adjusted_cb_bot_corner_lbc.y = ( ( cb_bot_y_coord_f24p8 - threshold_y )
	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
	
	
	//horiz_adjusted_cb_top_corner_lbc.x = horiz_adjusted_cb_bot_corner_lbc.x
	//	= ( ( cb_top_corner_f24p8.x - threshold_x ).floor_to_int() 
	//	/ num_pixels_per_block_dim ) - left();
	//horiz_adjusted_cb_top_corner_lbc.y = ( cb_top_corner_f24p8.y
	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
	//horiz_adjusted_cb_bot_corner_lbc.y = ( cb_bot_corner_f24p8.y
	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
	//
	//
	//vert_adjusted_cb_top_corner_lbc.x = vert_adjusted_cb_bot_corner_lbc.x
	//	= ( cb_top_corner_f24p8.x.floor_to_int() 
	//	/ num_pixels_per_block_dim ) - left();
	//vert_adjusted_cb_top_corner_lbc.y = ( ( cb_top_corner_f24p8.y 
	//	- threshold_y ).floor_to_int() / num_pixels_per_block_dim ) - top();
	//vert_adjusted_cb_bot_corner_lbc.y = ( ( cb_bot_corner_f24p8.y 
	//	- threshold_y ).floor_to_int() / num_pixels_per_block_dim ) - top();
	
	if ( contains_local_block_x_coord(horiz_adjusted_cb_top_corner_lbc.x) )
	{
		if ( contains_local_block_y_coord
			(horiz_adjusted_cb_top_corner_lbc.y) )
		{
			horiz_adjusted_cb_top_corner_bcr = &data_at
				(horiz_adjusted_cb_top_corner_lbc);
		}
		if ( contains_local_block_y_coord
			(horiz_adjusted_cb_bot_corner_lbc.y) )
		{
			horiz_adjusted_cb_bot_corner_bcr = &data_at
				(horiz_adjusted_cb_bot_corner_lbc);
		}
	}
	
	if ( contains_local_block_x_coord(vert_adjusted_cb_top_corner_lbc.x) )
	{
		if ( contains_local_block_y_coord
			(vert_adjusted_cb_top_corner_lbc.y) )
		{
			vert_adjusted_cb_top_corner_bcr = &data_at
				(vert_adjusted_cb_top_corner_lbc);
		}
		if ( contains_local_block_y_coord
			(vert_adjusted_cb_bot_corner_lbc.y) )
		{
			vert_adjusted_cb_bot_corner_bcr = &data_at
				(vert_adjusted_cb_bot_corner_lbc);
		}
	}
	
}

void block_coll_result_rect_group::get_side_blocked_stuff_old
	( array_helper<u32>& bool_as_u32_arr_helper )
{
	u32& vert_side_below_top_corner_is_blocked
		= bool_as_u32_arr_helper.data_at(2);
	u32& vert_side_above_bot_corner_is_blocked
		= bool_as_u32_arr_helper.data_at(3);
	u32& top_side_other_than_corner_is_blocked
		= bool_as_u32_arr_helper.data_at(4);
	u32& bot_side_other_than_corner_is_blocked
		= bool_as_u32_arr_helper.data_at(5);
	
	//// This was done by the caller (or at least it should have been!)
	//vert_side_below_top_corner_is_blocked 
	//	= vert_side_above_bot_corner_is_blocked
	//	= top_side_other_than_corner_is_blocked 
	//	= bot_side_other_than_corner_is_blocked = false;
	
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
	
	
	//for ( s32 j=local_top()+1; j<real_height(); ++j )
	//{
	//	if ( data_at( local_vert_side_x, j ).the_bbvt != bbvt_air )
	//	{
	//		vert_side_below_top_corner_is_blocked = true;
	//		break;
	//	}
	//}
	//
	//for ( s32 j=local_top(); j<real_height()-1; ++j )
	//{
	//	if ( data_at( local_vert_side_x, j ).the_bbvt != bbvt_air )
	//	{
	//		vert_side_above_bot_corner_is_blocked = true;
	//		break;
	//	}
	//}
	
	// Compress those two loops into one since they overlap
	for ( s32 j=local_top(); j<real_height(); ++j )
	{
		if ( !vert_side_below_top_corner_is_blocked 
			&& j >= local_top() + 1 )
		{
			if ( data_at( local_vert_side_x, j ).the_bbvt != bbvt_air )
			{
				vert_side_below_top_corner_is_blocked = true;
			}
		}
		
		if ( !vert_side_above_bot_corner_is_blocked
			&& j < real_height() - 1 )
		{
			if ( data_at( local_vert_side_x, j ).the_bbvt != bbvt_air )
			{
				vert_side_above_bot_corner_is_blocked = true;
			}
		}
		
		if ( vert_side_below_top_corner_is_blocked
			&& vert_side_above_bot_corner_is_blocked )
		{
			break;
		}
	}
	
	
	for ( s32 i=part_2_range_start; i<part_2_range_end_plus_1; ++i )
	{
		if (!top_side_other_than_corner_is_blocked)
		{
			if ( data_at( i, local_top() ).the_bbvt != bbvt_air )
			{
				top_side_other_than_corner_is_blocked = true;
			}
		}
		
		if (!bot_side_other_than_corner_is_blocked)
		{
			if ( data_at( i, local_bot() ).the_bbvt != bbvt_air )
			{
				bot_side_other_than_corner_is_blocked = true;
			}
		}
		
		if ( top_side_other_than_corner_is_blocked 
			&& bot_side_other_than_corner_is_blocked )
		{
			break;
		}
	}
}


