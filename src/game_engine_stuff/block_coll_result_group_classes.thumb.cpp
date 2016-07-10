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


block_coll_result_group_16x16::block_coll_result_group_16x16
	( const coll_point_group_16x16& the_pt_group )
{
	for ( u32 i=0; 
		i<coll_point_group_base::arr_ind_16x16_count; 
		++i )
	{
		the_array[i].coord = active_level::get_block_coord_of_point
			(the_pt_group.the_array[i]);
		the_array[i].the_block = &active_level::the_block_data_at_coord
			(the_array[i].coord);
	}
}


block_coll_result_group_16x32::block_coll_result_group_16x32
	( const coll_point_group_16x32& the_pt_group )
{
	for ( u32 i=0; 
		i<coll_point_group_base::arr_ind_16x32_count; 
		++i )
	{
		the_array[i].coord = active_level::get_block_coord_of_point
			(the_pt_group.the_array[i]);
		the_array[i].the_block = &active_level::the_block_data_at_coord
			(the_array[i].coord);
	}
}

