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


#include "block_coll_result_group_classes.hpp"
#include "level_stuff/active_level_class.hpp"

#include "block_stuff/block_stuff.hpp"
#include "sprite_stuff/sprite_class.hpp"
#include "coll_lseg_classes.hpp"


block_coll_result::block_coll_result( const vec2_s32& s_coord )
{
	the_block = &active_level::the_block_at_coord(s_coord);
	the_bbvt = get_behavior_type_of_block_type(get_block_type());
}
block_coll_result::block_coll_result( const vec2_f24p8& s_coord_f24p8 )
	: block_coll_result(active_level::get_block_coord_of_point
	(s_coord_f24p8))
{
}

u32 block_coll_result_rect_group::temp_debug_thing;

block_coll_result_rect_group::block_coll_result_rect_group() 
	: start_pos( 0, 0 ), real_size_2d( 1, 1 ), moving_left(false), 
	moving_right(false)
{
	//asm_comment("constructor type 1");
	//memset( bcr_arr_2d_helper_data, 0, sizeof(bcr_arr_2d_helper_data) );
	
	//arr_memfill32( bcr_arr_2d_helper_data, 0, max_size );
	//start_pos = vec2_s32( 0, 0 );
	//real_size_2d = vec2_s32( 1, 1 );
	//
	//moving_left = moving_right = false;
	
	init_bcr_arr_2d_helper();
	
	for ( s32 j=0; j<real_height(); ++j )
	{
		for ( s32 i=0; i<real_width(); ++i )
		{
			at( i, j ) = block_coll_result( tl_corner() 
				+ vec2_s32( i, j ) );
		}
	}
}

block_coll_result_rect_group::block_coll_result_rect_group
	( const coll_box& the_coll_box, u32 s_moving_left, u32 s_moving_right )
{
	//asm_comment("constructor type 2");
	//memset( bcr_arr_2d_helper_data, 0, sizeof(bcr_arr_2d_helper_data) );
	
	//arr_memfill32( bcr_arr_2d_helper_data, 0, max_size );
	
	start_pos = active_level::get_block_coord_of_point( vec2_f24p8
		( the_coll_box.left(), the_coll_box.top() ) );
	const vec2_s32 end_pos = active_level::get_block_coord_of_point
		( vec2_f24p8( the_coll_box.right(), the_coll_box.bot() ) );
	real_size_2d = end_pos - start_pos + vec2_s32( 1, 1 );
	
	moving_left = s_moving_left;
	moving_right = s_moving_right;
	
	init_bcr_arr_2d_helper();
	
	for ( s32 j=0; j<real_height(); ++j )
	{
		for ( s32 i=0; i<real_width(); ++i )
		{
			at( i, j ) = block_coll_result( tl_corner() 
				+ vec2_s32( i, j ) );
		}
	}
	
}




block_coll_result_rect_group::block_coll_result_rect_group
	( const block_coll_result_rect_group& to_copy )
{
	*this = to_copy;
}
block_coll_result_rect_group& block_coll_result_rect_group::operator = 
	( const block_coll_result_rect_group& to_copy )
{
	arr_memcpy32( (block_coll_result*)bcr_arr_2d_helper_data, 
		to_copy.bcr_arr_2d_helper_data, max_size );
	
	start_pos = to_copy.start_pos;
	
	real_size_2d = to_copy.real_size_2d;
	
	moving_left = to_copy.moving_left;
	moving_right = to_copy.moving_right;
	
	init_bcr_arr_2d_helper();
	
	return *this;
}

void bcr_lseg_group::init( const horiz_coll_lseg& the_coll_lseg )
{
	start_pos = active_level::get_block_coord_of_point
		( the_coll_lseg.left_pt() );
	const vec2_s32 end_pos = active_level::get_block_coord_of_point
		( the_coll_lseg.right_pt() );
	real_size = end_pos.x - start_pos.x + 1;
	is_horiz = true;
	
	
	init_bcr_arr_helper();
	
	//for ( s32 i=0; i<get_real_size(); ++i )
	for ( s32 i=get_real_size()-1; i>=0; --i )
	{
		at(i) = block_coll_result( get_start_pos() + get_horiz_offset(i) );
	}
	
}
void bcr_lseg_group::init( const vert_coll_lseg& the_coll_lseg )
{
	start_pos = active_level::get_block_coord_of_point
		( the_coll_lseg.top_pt() );
	const vec2_s32 end_pos = active_level::get_block_coord_of_point
		( the_coll_lseg.bot_pt() );
	real_size = end_pos.y - start_pos.y + 1;
	is_horiz = false;
	
	
	init_bcr_arr_helper();
	
	//for ( s32 i=0; i<get_real_size(); ++i )
	for ( s32 i=get_real_size()-1; i>=0; --i )
	{
		at(i) = block_coll_result( get_start_pos() + get_vert_offset(i) );
	}
	
}

block_coll_result* bcr_lseg_group::horiz_any_bbvt_is_fully_solid
	( vec2_s32& pos )
{
	for ( s32 i=0; i<get_real_size(); ++i )
	{
		if ( bbvt_is_fully_solid(bcr_arr_helper[i].get_bbvt()) )
		{
			pos = get_start_pos() + get_horiz_offset(i);
			return &(bcr_arr_helper[i]);
		}
	}
	
	return NULL;
}
block_coll_result* bcr_lseg_group::vert_any_bbvt_is_fully_solid
	( vec2_s32& pos )
{
	for ( s32 i=0; i<get_real_size(); ++i )
	{
		if ( bbvt_is_fully_solid(bcr_arr_helper[i].get_bbvt()) )
		{
			pos = get_start_pos() + get_vert_offset(i);
			return &(bcr_arr_helper[i]);
		}
	}
	
	return NULL;
}
block_coll_result* bcr_lseg_group::vert_any_bbvt_is_slope( vec2_s32& pos )
{
	for ( s32 i=0; i<get_real_size(); ++i )
	{
		if ( bbvt_is_slope(bcr_arr_helper[i].get_bbvt()) )
		{
			pos = get_start_pos() + get_vert_offset(i);
			return &(bcr_arr_helper[i]);
		}
	}
	
	return NULL;
}


//bcr_ptr_line::bcr_ptr_line( block_coll_result_rect_group& the_bcr_group,
//	const vec2_s32& s_local_param_pos, u32 s_is_horiz ) 
//	: local_param_pos(s_local_param_pos), is_horiz(s_is_horiz)
//{
//	// If this line of bcr ptr's is a row
//	if (get_is_horiz())
//	{
//		real_size = the_bcr_group.real_width();
//		s32 which_row = get_local_param_pos().y;
//		
//		for ( s32 i=0; i<get_real_size(); ++i )
//		{
//			at(i) = &the_bcr_group( i, which_row );
//		}
//	}
//	// If this line of bcr ptr's is a column
//	else //if (get_is_vert())
//	{
//		real_size = the_bcr_group.real_height();
//		s32 which_col = get_local_param_pos().x;
//		
//		for ( s32 j=0; j<get_real_size(); ++j )
//		{
//			at(j) = &the_bcr_group( which_col, j );
//		}
//	}
//	
//	init_ptr_arr_helper();
//}
//
//
//// ARM functions
//
//inline void temp_func_get_horiz_adjusted_x
//	( const block_coll_result_rect_group& the_bcr_group, 
//	const fixed24p8& cb_vert_side_x_coord_f24p8, 
//	const fixed24p8& threshold_x,
//	array_helper<vec2_s32>& adjusted_cb_corner_lbc_arr_helper )
//{
//	vec2_s32& horiz_adjusted_cb_top_corner_lbc 
//		= adjusted_cb_corner_lbc_arr_helper.at(0);
//	vec2_s32& horiz_adjusted_cb_bot_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(1);
//	
//	horiz_adjusted_cb_top_corner_lbc.x = horiz_adjusted_cb_bot_corner_lbc.x
//		= ( ( cb_vert_side_x_coord_f24p8 - threshold_x ).floor_to_int() 
//		/ num_pixels_per_block_dim ) - the_bcr_group.left();
//}
//inline void temp_func_get_horiz_adjusted_y
//	( const block_coll_result_rect_group& the_bcr_group, 
//	const vec2_f24p8& cb_corner_y_coords, 
//	array_helper<vec2_s32>& adjusted_cb_corner_lbc_arr_helper )
//{
//	vec2_s32& horiz_adjusted_cb_top_corner_lbc 
//		= adjusted_cb_corner_lbc_arr_helper.at(0);
//	vec2_s32& horiz_adjusted_cb_bot_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(1);
//	
//	const fixed24p8& cb_top_y_coord_f24p8 = cb_corner_y_coords.x;
//	const fixed24p8& cb_bot_y_coord_f24p8 = cb_corner_y_coords.y;
//	
//	horiz_adjusted_cb_top_corner_lbc.y = ( cb_top_y_coord_f24p8
//		.floor_to_int() / num_pixels_per_block_dim ) - the_bcr_group.top();
//	horiz_adjusted_cb_bot_corner_lbc.y = ( cb_bot_y_coord_f24p8
//		.floor_to_int() / num_pixels_per_block_dim ) - the_bcr_group.top();
//}
//
//
//inline void temp_func_get_vert_adjusted_x
//	( const block_coll_result_rect_group& the_bcr_group, 
//	const fixed24p8& cb_vert_side_x_coord_f24p8, 
//	array_helper<vec2_s32>& adjusted_cb_corner_lbc_arr_helper )
//{
//	vec2_s32& vert_adjusted_cb_top_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(2);
//	vec2_s32& vert_adjusted_cb_bot_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(3);
//	
//	vert_adjusted_cb_top_corner_lbc.x = vert_adjusted_cb_bot_corner_lbc.x
//		= ( cb_vert_side_x_coord_f24p8.floor_to_int() 
//		/ num_pixels_per_block_dim ) - the_bcr_group.left();
//}
//inline void temp_func_get_vert_adjusted_y
//	( const block_coll_result_rect_group& the_bcr_group, 
//	const vec2_f24p8& cb_corner_y_coords, const fixed24p8& threshold_y,
//	array_helper<vec2_s32>& adjusted_cb_corner_lbc_arr_helper )
//{
//	vec2_s32& vert_adjusted_cb_top_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(2);
//	vec2_s32& vert_adjusted_cb_bot_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(3);
//	
//	const fixed24p8& cb_top_y_coord_f24p8 = cb_corner_y_coords.x;
//	const fixed24p8& cb_bot_y_coord_f24p8 = cb_corner_y_coords.y;
//	
//	
//	vert_adjusted_cb_top_corner_lbc.y = ( ( cb_top_y_coord_f24p8 
//		- threshold_y ).floor_to_int() / num_pixels_per_block_dim ) 
//		- the_bcr_group.top();
//	vert_adjusted_cb_bot_corner_lbc.y = ( ( cb_bot_y_coord_f24p8 
//		- threshold_y ).floor_to_int() / num_pixels_per_block_dim ) 
//		- the_bcr_group.top();
//}
//
//
//
//
//
//
//void block_coll_result_rect_group::get_corner_stuff_old
//	( array_helper<block_coll_result*>& bcr_ptr_arr_helper, 
//	array_helper<u32>& bool_as_u32_arr_helper )
//{
//	block_coll_result*& top_corner_bcr = bcr_ptr_arr_helper.at(0);
//	block_coll_result*& bot_corner_bcr = bcr_ptr_arr_helper.at(1);
//	
//	u32& top_corner_is_non_air = bool_as_u32_arr_helper.at(0);
//	u32& bot_corner_is_non_air = bool_as_u32_arr_helper.at(1);
//	
//	
//	vec2_s32 local_top_corner = local_tl_corner(),
//		local_bot_corner = local_bl_corner();
//	
//	if (moving_left)
//	{
//		//local_top_corner.x = local_bot_corner.x = local_left();
//	}
//	else if (moving_right)
//	{
//		local_top_corner.x = local_bot_corner.x = local_right();
//	}
//	
//	
//	//top_corner_is_non_air = ( bcr_arr_2d_helper.at
//	//	(local_top_corner).the_bbvt != bbvt_air );
//	//bot_corner_is_non_air = ( bcr_arr_2d_helper.at
//	//	(local_bot_corner).the_bbvt != bbvt_air );
//	
//	top_corner_bcr = &bcr_arr_2d_helper.at(local_top_corner);
//	bot_corner_bcr = &bcr_arr_2d_helper.at(local_bot_corner);
//	
//	top_corner_is_non_air = ( top_corner_bcr->the_bbvt != bbvt_air );
//	bot_corner_is_non_air = ( bot_corner_bcr->the_bbvt != bbvt_air );
//}
//
//
//
//void block_coll_result_rect_group::get_coll_box_related_stuff_old
//	( const sprite& the_sprite, 
//	array_helper<block_coll_result*>& bcr_ptr_arr_helper )
//{
//	static const u32 num_adjusted_corner_positions = 4;
//	vec2_s32 adjusted_cb_corner_lbc_arr[num_adjusted_corner_positions];
//	
//	array_helper<vec2_s32> adjusted_cb_corner_lbc_arr_helper
//		( adjusted_cb_corner_lbc_arr, num_adjusted_corner_positions );
//	
//	vec2_s32& horiz_adjusted_cb_top_corner_lbc 
//		= adjusted_cb_corner_lbc_arr_helper.at(0);
//	vec2_s32& horiz_adjusted_cb_bot_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(1);
//	vec2_s32& vert_adjusted_cb_top_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(2);
//	vec2_s32& vert_adjusted_cb_bot_corner_lbc
//		= adjusted_cb_corner_lbc_arr_helper.at(3);
//	
//	block_coll_result*& horiz_adjusted_cb_top_corner_bcr
//		= bcr_ptr_arr_helper.at(2);
//	block_coll_result*& horiz_adjusted_cb_bot_corner_bcr
//		= bcr_ptr_arr_helper.at(3);
//	block_coll_result*& vert_adjusted_cb_top_corner_bcr
//		= bcr_ptr_arr_helper.at(4);
//	block_coll_result*& vert_adjusted_cb_bot_corner_bcr
//		= bcr_ptr_arr_helper.at(5);
//	
//	
//	const coll_box& the_coll_box = the_sprite.the_coll_box; 
//	//const fixed24p8 disp_x = the_sprite.get_curr_in_level_pos().x 
//	//	- the_sprite.get_prev_in_level_pos().x;
//	//const fixed24p8 disp_y = the_sprite.get_curr_in_level_pos().y 
//	//	- the_sprite.get_prev_in_level_pos().y;
//	const fixed24p8 threshold_x = moving_right 
//		? the_sprite.max_vel_x_abs_val : -the_sprite.max_vel_x_abs_val;
//	const fixed24p8 threshold_y = ( the_sprite.get_curr_in_level_pos().y
//		> the_sprite.get_prev_in_level_pos().y ) ? the_sprite.max_y_vel
//		: -the_sprite.max_y_vel;
//	
//	//vec2_f24p8 cb_top_corner_f24p8( the_coll_box.left(), 
//	//	the_coll_box.top() ), cb_bot_corner_f24p8( the_coll_box.left(),
//	//	the_coll_box.bot() );
//	//vec2_f24p8 cb_top_corner_f24p8, cb_bot_corner_f24p8;
//	
//	
//	//cb_top_corner_f24p8.x = cb_bot_corner_f24p8.x = the_coll_box.left();
//	//cb_top_corner_f24p8.y = the_coll_box.top();
//	//cb_bot_corner_f24p8.y = the_coll_box.bot();
//	
//	
//	const fixed24p8 cb_top_y_coord_f24p8 = the_coll_box.top(),
//		cb_bot_y_coord_f24p8 = the_coll_box.bot();
//	
//	fixed24p8 cb_vert_side_x_coord_f24p8 = the_coll_box.left();
//	
//	if (moving_left)
//	{
//		////cb_top_corner_f24p8.x = cb_bot_corner_f24p8.x = the_coll_box
//		////	.left();
//		//cb_vert_side_x_coord_f24p8 = the_coll_box.left();
//	}
//	else if (moving_right)
//	{
//		////cb_top_corner_f24p8.x = cb_bot_corner_f24p8.x = the_coll_box
//		////	.right();
//		cb_vert_side_x_coord_f24p8 = the_coll_box.right();
//	}
//	
//	
//	// The local block coords
//	temp_func_get_horiz_adjusted_x( *this, cb_vert_side_x_coord_f24p8,
//		threshold_x, adjusted_cb_corner_lbc_arr_helper );
//	temp_func_get_horiz_adjusted_y( *this, vec2_f24p8
//		( cb_top_y_coord_f24p8, cb_bot_y_coord_f24p8 ), 
//		adjusted_cb_corner_lbc_arr_helper );
//	
//	
//	temp_func_get_vert_adjusted_x( *this, cb_vert_side_x_coord_f24p8,
//		adjusted_cb_corner_lbc_arr_helper );
//	temp_func_get_vert_adjusted_y( *this, vec2_f24p8
//		( cb_top_y_coord_f24p8, cb_bot_y_coord_f24p8 ), threshold_y,
//		adjusted_cb_corner_lbc_arr_helper );
//	
//	
//	//horiz_adjusted_cb_top_corner_lbc.x = horiz_adjusted_cb_bot_corner_lbc.x
//	//	= ( ( cb_vert_side_x_coord_f24p8 - threshold_x ).floor_to_int() 
//	//	/ num_pixels_per_block_dim ) - left();
//	//horiz_adjusted_cb_top_corner_lbc.y = ( cb_top_y_coord_f24p8
//	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
//	//horiz_adjusted_cb_bot_corner_lbc.y = ( cb_bot_y_coord_f24p8
//	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
//	
//	
//	//vert_adjusted_cb_top_corner_lbc.x = vert_adjusted_cb_bot_corner_lbc.x
//	//	= ( cb_vert_side_x_coord_f24p8.floor_to_int() 
//	//	/ num_pixels_per_block_dim ) - left();
//	//vert_adjusted_cb_top_corner_lbc.y = ( ( cb_top_y_coord_f24p8 - threshold_y )
//	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
//	//vert_adjusted_cb_bot_corner_lbc.y = ( ( cb_bot_y_coord_f24p8 - threshold_y )
//	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
//	
//	
//	//horiz_adjusted_cb_top_corner_lbc.x = horiz_adjusted_cb_bot_corner_lbc.x
//	//	= ( ( cb_top_corner_f24p8.x - threshold_x ).floor_to_int() 
//	//	/ num_pixels_per_block_dim ) - left();
//	//horiz_adjusted_cb_top_corner_lbc.y = ( cb_top_corner_f24p8.y
//	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
//	//horiz_adjusted_cb_bot_corner_lbc.y = ( cb_bot_corner_f24p8.y
//	//	.floor_to_int() / num_pixels_per_block_dim ) - top();
//	//
//	//
//	//vert_adjusted_cb_top_corner_lbc.x = vert_adjusted_cb_bot_corner_lbc.x
//	//	= ( cb_top_corner_f24p8.x.floor_to_int() 
//	//	/ num_pixels_per_block_dim ) - left();
//	//vert_adjusted_cb_top_corner_lbc.y = ( ( cb_top_corner_f24p8.y 
//	//	- threshold_y ).floor_to_int() / num_pixels_per_block_dim ) - top();
//	//vert_adjusted_cb_bot_corner_lbc.y = ( ( cb_bot_corner_f24p8.y 
//	//	- threshold_y ).floor_to_int() / num_pixels_per_block_dim ) - top();
//	
//	if ( contains_local_block_x_coord(horiz_adjusted_cb_top_corner_lbc.x) )
//	{
//		if ( contains_local_block_y_coord
//			(horiz_adjusted_cb_top_corner_lbc.y) )
//		{
//			horiz_adjusted_cb_top_corner_bcr = &at
//				(horiz_adjusted_cb_top_corner_lbc);
//		}
//		if ( contains_local_block_y_coord
//			(horiz_adjusted_cb_bot_corner_lbc.y) )
//		{
//			horiz_adjusted_cb_bot_corner_bcr = &at
//				(horiz_adjusted_cb_bot_corner_lbc);
//		}
//	}
//	
//	if ( contains_local_block_x_coord(vert_adjusted_cb_top_corner_lbc.x) )
//	{
//		if ( contains_local_block_y_coord
//			(vert_adjusted_cb_top_corner_lbc.y) )
//		{
//			vert_adjusted_cb_top_corner_bcr = &at
//				(vert_adjusted_cb_top_corner_lbc);
//		}
//		if ( contains_local_block_y_coord
//			(vert_adjusted_cb_bot_corner_lbc.y) )
//		{
//			vert_adjusted_cb_bot_corner_bcr = &at
//				(vert_adjusted_cb_bot_corner_lbc);
//		}
//	}
//	
//}
//
//void block_coll_result_rect_group::get_side_blocked_stuff_old
//	( array_helper<u32>& bool_as_u32_arr_helper )
//{
//	u32& vert_side_below_top_corner_is_blocked
//		= bool_as_u32_arr_helper.at(2);
//	u32& vert_side_above_bot_corner_is_blocked
//		= bool_as_u32_arr_helper.at(3);
//	u32& top_side_other_than_corner_is_blocked
//		= bool_as_u32_arr_helper.at(4);
//	u32& bot_side_other_than_corner_is_blocked
//		= bool_as_u32_arr_helper.at(5);
//	
//	//// This was done by the caller (or at least it should have been!)
//	//vert_side_below_top_corner_is_blocked 
//	//	= vert_side_above_bot_corner_is_blocked
//	//	= top_side_other_than_corner_is_blocked 
//	//	= bot_side_other_than_corner_is_blocked = false;
//	
//	s32 local_vert_side_x = local_left();
//	
//	s32 part_2_range_start = local_left() + 1, 
//		part_2_range_end_plus_1 = local_right() + 1;
//	
//	if (moving_left)
//	{
//		//local_vert_side_x = local_left();
//		
//		//part_2_range_start = local_left() + 1;
//		//part_2_range_end_plus_1 = local_right() + 1;
//	}
//	else if (moving_right)
//	{
//		local_vert_side_x = local_right();
//		
//		//part_2_range_start = local_left();
//		//part_2_range_end_plus_1 = local_right();
//		--part_2_range_start;
//		--part_2_range_end_plus_1;
//	}
//	
//	
//	//for ( s32 j=local_top()+1; j<real_height(); ++j )
//	//{
//	//	if ( at( local_vert_side_x, j ).the_bbvt != bbvt_air )
//	//	{
//	//		vert_side_below_top_corner_is_blocked = true;
//	//		break;
//	//	}
//	//}
//	//
//	//for ( s32 j=local_top(); j<real_height()-1; ++j )
//	//{
//	//	if ( at( local_vert_side_x, j ).the_bbvt != bbvt_air )
//	//	{
//	//		vert_side_above_bot_corner_is_blocked = true;
//	//		break;
//	//	}
//	//}
//	
//	// Compress those two loops into one since they overlap
//	for ( s32 j=local_top(); j<real_height(); ++j )
//	{
//		if ( !vert_side_below_top_corner_is_blocked 
//			&& j >= local_top() + 1 )
//		{
//			if ( at( local_vert_side_x, j ).the_bbvt != bbvt_air )
//			{
//				vert_side_below_top_corner_is_blocked = true;
//			}
//		}
//		
//		if ( !vert_side_above_bot_corner_is_blocked
//			&& j < real_height() - 1 )
//		{
//			if ( at( local_vert_side_x, j ).the_bbvt != bbvt_air )
//			{
//				vert_side_above_bot_corner_is_blocked = true;
//			}
//		}
//		
//		if ( vert_side_below_top_corner_is_blocked
//			&& vert_side_above_bot_corner_is_blocked )
//		{
//			break;
//		}
//	}
//	
//	
//	for ( s32 i=part_2_range_start; i<part_2_range_end_plus_1; ++i )
//	{
//		if (!top_side_other_than_corner_is_blocked)
//		{
//			if ( at( i, local_top() ).the_bbvt != bbvt_air )
//			{
//				top_side_other_than_corner_is_blocked = true;
//			}
//		}
//		
//		if (!bot_side_other_than_corner_is_blocked)
//		{
//			if ( at( i, local_bot() ).the_bbvt != bbvt_air )
//			{
//				bot_side_other_than_corner_is_blocked = true;
//			}
//		}
//		
//		if ( top_side_other_than_corner_is_blocked 
//			&& bot_side_other_than_corner_is_blocked )
//		{
//			break;
//		}
//	}
//}
