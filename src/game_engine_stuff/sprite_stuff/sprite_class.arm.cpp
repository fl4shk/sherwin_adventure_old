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


#include "sprite_class.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../gfx_manager_class.hpp"

#include "sprite_allocator_class.hpp"

#include "../misc_utility_funcs.hpp"

#include "../level_stuff/active_level_class.hpp"

#include "sprite_manager_class.hpp"
#include "../../gba_specific_stuff/button_stuff.hpp"

#include "../level_stuff/sublevel_class.hpp"



void sprite::block_collision_stuff_16x16()
{
	//bool moving_left = false, moving_right = false, moving_up = false,
	//	not_moving_up = false;
	//
	//if ( get_curr_in_level_pos().x < get_prev_in_level_pos().x )
	//{
	//	moving_left = true;
	//}
	//else if ( get_curr_in_level_pos().x > get_prev_in_level_pos().x )
	//{
	//	moving_right = true;
	//}
	//
	//if ( get_curr_in_level_pos().y < get_prev_in_level_pos().y )
	//{
	//	moving_up = true;
	//}
	//else //if ( get_curr_in_level_pos().y >= get_prev_in_level_pos().y )
	//{
	//	not_moving_up = true;
	//}
}
void sprite::block_collision_stuff_16x32()
{
	u32 moving_left = false, moving_right = false, moving_up = false,
		moving_down = false;
	
	if ( get_curr_in_level_pos().x < get_prev_in_level_pos().x )
	{
		moving_left = true;
	}
	else if ( get_curr_in_level_pos().x > get_prev_in_level_pos().x )
	{
		moving_right = true;
	}
	
	if ( get_curr_in_level_pos().y < get_prev_in_level_pos().y )
	{
		moving_up = true;
	}
	else if ( get_curr_in_level_pos().y > get_prev_in_level_pos().y )
	{
		moving_down = true;
	}
	
	
	block_coll_result_group the_bcr_group( the_coll_box, moving_left, 
		moving_right );
	
	
	
	static constexpr u32 num_relevant_corners = 2,
		num_adjusted_corner_positions = 4,
		side_is_partially_blocked_arr_size = 4;
	
	static constexpr u32 bcr_ptr_arr_size = num_relevant_corners
		+ num_adjusted_corner_positions,
		
		bool_as_u32_arr_size = num_relevant_corners
		+ side_is_partially_blocked_arr_size,
		
		adjusted_corner_lbc_arr_size = num_adjusted_corner_positions;
	
	
	class arr_group
	{
	public:		// variables
		block_coll_result* bcr_ptr_arr[bcr_ptr_arr_size];
		u32 bool_as_u32_arr[bool_as_u32_arr_size];
		vec2_s32 adjusted_corner_lbc_arr[adjusted_corner_lbc_arr_size];
	} __attribute__((_align4));
	
	
	arr_group the_arr_group;
	
	// I didn't know about this syntax beforehand....  Perhaps auto& would
	// be better to use.
	block_coll_result* (&bcr_ptr_arr)[bcr_ptr_arr_size] = the_arr_group
		.bcr_ptr_arr;
	u32 (&bool_as_u32_arr)[bool_as_u32_arr_size] = the_arr_group
		.bool_as_u32_arr;
	vec2_s32 (&adjusted_corner_lbc_arr)[adjusted_corner_lbc_arr_size] 
		= the_arr_group.adjusted_corner_lbc_arr;
	
	
	array_helper<block_coll_result*> bcr_ptr_arr_helper( bcr_ptr_arr, 
		bcr_ptr_arr_size );
	array_helper<u32> bool_as_u32_arr_helper( bool_as_u32_arr, 
		bool_as_u32_arr_size );
	array_helper<vec2_s32> adjusted_corner_lbc_arr_helper
		( adjusted_corner_lbc_arr, adjusted_corner_lbc_arr_size );
	
	
	// Oh boy, here come the references
	block_coll_result*& top_corner_bcr = bcr_ptr_arr[0];
	block_coll_result*& bot_corner_bcr = bcr_ptr_arr[1];
	
	u32& top_corner_is_non_air = bool_as_u32_arr[0];
	u32& bot_corner_is_non_air = bool_as_u32_arr[1];
	
	u32& vert_side_below_top_corner_is_blocked = bool_as_u32_arr[2];
	u32& vert_side_above_bot_corner_is_blocked = bool_as_u32_arr[3];
	
	// The top side to the right or left of the relevant corner
	u32& top_side_other_than_corner_is_blocked = bool_as_u32_arr[4];
	u32& bot_side_other_than_corner_is_blocked = bool_as_u32_arr[5];
	
	
	
	// These are adjusted by using either the horizontal or vertical
	// displacement of the sprite.  Also, "lbc" is short for "local block
	// coord".
	//vec2_s32& horiz_adjusted_cb_top_corner_lbc 
	//	= adjusted_corner_lbc_arr[0];
	//vec2_s32& horiz_adjusted_cb_bot_corner_lbc
	//	= adjusted_corner_lbc_arr[1];
	//vec2_s32& vert_adjusted_cb_top_corner_lbc
	//	= adjusted_corner_lbc_arr[2];
	//vec2_s32& vert_adjusted_cb_bot_corner_lbc
	//	= adjusted_corner_lbc_arr[3];
	
	// Blocks intersected by the adjusted
	block_coll_result*& horiz_adjusted_cb_top_corner_bcr = bcr_ptr_arr[2];
	block_coll_result*& horiz_adjusted_cb_bot_corner_bcr = bcr_ptr_arr[3];
	block_coll_result*& vert_adjusted_cb_top_corner_bcr = bcr_ptr_arr[4];
	block_coll_result*& vert_adjusted_cb_bot_corner_bcr = bcr_ptr_arr[5];
	
	
	the_bcr_group.get_corner_stuff( bcr_ptr_arr_helper,
		bool_as_u32_arr_helper );
	
	the_bcr_group.get_coll_box_related_stuff( *this, 
		adjusted_corner_lbc_arr_helper, bcr_ptr_arr_helper );
	
	the_bcr_group.get_side_blocked_stuff(bool_as_u32_arr_helper);
	
	
	
	// Shorthands
	const bool horiz_adjusted_tc_is_top_corner = ( top_corner_bcr 
		== horiz_adjusted_cb_top_corner_bcr );
	const bool horiz_adjusted_bc_is_bot_corner = ( bot_corner_bcr 
		== horiz_adjusted_cb_bot_corner_bcr );
	const bool vert_adjusted_tc_is_top_corner = ( top_corner_bcr 
		== vert_adjusted_cb_top_corner_bcr );
	const bool vert_adjusted_bc_is_bot_corner = ( bot_corner_bcr 
		== vert_adjusted_cb_bot_corner_bcr );
	
	// More shorthands
	const bool h_and_t_non_air = ( horiz_adjusted_tc_is_top_corner
		&& top_corner_is_non_air );
	const bool h_and_b_non_air = ( horiz_adjusted_bc_is_bot_corner
		&& bot_corner_is_non_air );
	const bool v_and_t_non_air = ( vert_adjusted_tc_is_top_corner
		&& top_corner_is_non_air );
	const bool v_and_b_non_air = ( vert_adjusted_bc_is_bot_corner
		&& bot_corner_is_non_air );
	
	
	auto regular_vert_side_is_blocked_response = [&]() -> void
	{
		if (moving_left)
		{
			block_coll_response_left_16x32(the_bcr_group);
		}
		else if (moving_right)
		{
			block_coll_response_right_16x32(the_bcr_group);
		}
	};
	
	bool did_push_for_left = false, did_push_for_right = false, 
		did_push_for_top = false, did_push_for_bot = false;
	
	if ( h_and_t_non_air || top_side_other_than_corner_is_blocked )
	{
		// We're dealing with one block that is a ceiling and/or a vertical
		// wall 
		if (!top_side_other_than_corner_is_blocked)
		{
			if (h_and_t_non_air)
			{
				
			}
		}
	}
	if ( !did_push_for_top && ( h_and_b_non_air 
		|| bot_side_other_than_corner_is_blocked ) )
	{
		block_coll_response_bot_16x32(the_bcr_group);
	}
	
	if ( !did_push_for_top && !did_push_for_bot )
	{
		set_curr_on_ground(false);
		
		if ( top_corner_is_non_air 
			|| vert_side_below_top_corner_is_blocked )
		{
			regular_vert_side_is_blocked_response();
		}
	}
	
	
	
}
void sprite::block_collision_stuff_32x16()
{
	
}
void sprite::block_collision_stuff_32x32()
{
	
}
