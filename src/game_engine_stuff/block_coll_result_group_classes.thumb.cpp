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


block_coll_result::block_coll_result( const vec2_s32& s_coord )
	: coord(s_coord)
{
	the_block = &active_level::the_block_data_at_coord(coord);
}
block_coll_result::block_coll_result( const vec2_f24p8& s_coord_f24p8 )
	: block_coll_result(active_level::get_block_coord_of_point
	(s_coord_f24p8))
{
}


// The maximum number of blocks intersected by a sprite, per dimension.
// The value of ( 3, 3 ) corresponds to a 32x32 sprite.  Definitely
// change these two values (among other things) if there is every any
// infrastructure for sprites larger than 32x32 pixels.
//const vec2_u32 block_coll_result_group::shared_max_size_2d( 3, 3 );




block_coll_result_group::block_coll_result_group
	( const coll_box& the_coll_box )
{
	
}
block_coll_result_group::block_coll_result_group
	( const block_coll_result_group& to_copy )
{
	*this = to_copy;
}
block_coll_result_group& block_coll_result_group::operator = 
	( const block_coll_result_group& to_copy )
{
	memcpy32( bcr_arr_2d_helper_data, to_copy.bcr_arr_2d_helper_data, 
		sizeof(bcr_arr_2d_helper_data) / sizeof(u32) );
	real_size_2d = to_copy.real_size_2d;
	bcr_arr_2d_helper = to_copy.bcr_arr_2d_helper;
	
	return *this;
}


