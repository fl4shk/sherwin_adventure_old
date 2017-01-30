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



bcr_ptr_line::bcr_ptr_line( block_coll_result_rect_group& the_bcr_group,
	const vec2_s32& s_local_param_pos, u32 s_is_horiz ) 
	: local_param_pos(s_local_param_pos), is_horiz(s_is_horiz)
{
	// If this line of bcr ptr's is a row
	if (get_is_horiz())
	{
		real_size = the_bcr_group.real_width();
		s32 which_row = get_local_param_pos().y;
		
		for ( s32 i=0; i<get_real_size(); ++i )
		{
			at(i) = &the_bcr_group( i, which_row );
		}
	}
	// If this line of bcr ptr's is a column
	else //if (get_is_vert())
	{
		real_size = the_bcr_group.real_height();
		s32 which_col = get_local_param_pos().x;
		
		for ( s32 j=0; j<get_real_size(); ++j )
		{
			at(j) = &the_bcr_group( which_col, j );
		}
	}
	
	init_ptr_arr_helper();
}



