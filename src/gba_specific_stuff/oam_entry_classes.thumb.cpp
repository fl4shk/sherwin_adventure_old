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


#include "attribute_defines.hpp"
#include "oam_entry_classes.hpp"

// I'm tempted to put these two arrays in _iwram.
oam_entry oam_mirror[oam_mirror_size];
//oam_entry_affine* const oam_mirror_aff = (oam_entry_affine*)oam_mirror ;


const vec2_u32 oam_entry::ss_to_vec2_arr[ss_count]
= {
	// Square shapes
	{ 8, 8 }, { 16, 16 }, { 32, 32 }, { 64, 64 },
	
	// Horizontal shapes
	{ 16, 8 }, { 32, 8 }, { 32, 16 }, { 64, 32 },
	
	// Vertical shapes
	{ 8, 16 }, { 8, 32 }, { 16, 32 }, { 32, 64 },
};

const vec2_u32 oam_entry::ss_enum_to_ss_attrs_arr[ss_count]
= {
	// Square shapes
	{ obj_attr0_shape_square, obj_attr1_size_0 }, 
	{ obj_attr0_shape_square, obj_attr1_size_1 }, 
	{ obj_attr0_shape_square, obj_attr1_size_2 }, 
	{ obj_attr0_shape_square, obj_attr1_size_3 },
	
	// Horizontal shapes
	{ obj_attr0_shape_horizontal, obj_attr1_size_0 }, 
	{ obj_attr0_shape_horizontal, obj_attr1_size_1 }, 
	{ obj_attr0_shape_horizontal, obj_attr1_size_2 }, 
	{ obj_attr0_shape_horizontal, obj_attr1_size_3 },
	
	// Vertical shapes
	{ obj_attr0_shape_vertical, obj_attr1_size_0 }, 
	{ obj_attr0_shape_vertical, obj_attr1_size_1 }, 
	{ obj_attr0_shape_vertical, obj_attr1_size_2 }, 
	{ obj_attr0_shape_vertical, obj_attr1_size_3 },
};

const oam_entry::shape_size oam_entry::ss_attrs_no_shift_to_ss_enum_arr_2d
	[num_attr0_shapes][num_attr1_sizes]
= {
	// Square shapes
	{ ss_8x8, ss_16x16, ss_32x32, ss_64x64 },
	
	// Horizontal shapes
	{ ss_16x8, ss_32x8, ss_32x16, ss_64x32 },
	
	// Vertical shapes
	{ ss_8x16, ss_8x32, ss_16x32, ss_32x64 },
};


void oam_entry::set_shape_size( oam_entry::shape_size n_shape_size )
{
	u32 temp_attr0 = attr0, temp_attr1 = attr1;
	
	if ( n_shape_size < 0 || n_shape_size >= ss_count )
	{
		const vec2_u32& ss_attrs_vec2 = ss_enum_to_ss_attrs_arr[0];
		
		clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
			ss_attrs_vec2.x );
		clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
			ss_attrs_vec2.y );
	}
	else
	{
		const vec2_u32& ss_attrs_vec2 = ss_enum_to_ss_attrs_arr
			[n_shape_size];
		
		clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
			ss_attrs_vec2.x );
		clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
			ss_attrs_vec2.y );
	}
	
	
	attr0 = (u16)( temp_attr0 & 0xffff );
	attr1 = (u16)( temp_attr1 & 0xffff );
	
}



oam_entry::shape_size oam_entry::get_shape_size() const
{
	u32 attr0_shape_no_shift = get_bits( attr0, obj_attr0_shape_mask,
		obj_attr0_shape_shift );
	u32 attr1_size_no_shift = get_bits( attr0, obj_attr1_size_mask,
		obj_attr1_size_shift );
	
	// Error checking
	if ( attr0_shape_no_shift >= num_attr0_shapes 
		|| attr1_size_no_shift >= num_attr1_sizes )
	{
		return ss_attrs_no_shift_to_ss_enum_arr_2d[0][0];
	}
	else
	{
		return ss_attrs_no_shift_to_ss_enum_arr_2d[attr0_shape_no_shift]
			[attr1_size_no_shift];
	}
}

void oam_entry::set_shape_size_with_vec2( const vec2_u32& n_shape_size )
{
	switch ( n_shape_size.x )
	{
		default:
		case 8:
			switch ( n_shape_size.y )
			{
				default:
				case 8:
					set_shape_size(ss_8x8);
					break;
				case 16:
					set_shape_size(ss_8x16);
					break;
				case 32:
					set_shape_size(ss_8x32);
					break;
			}
		
		case 16:
			switch ( n_shape_size.y )
			{
				default:
				case 16:
					set_shape_size(ss_16x16);
					break;
				case 8:
					set_shape_size(ss_16x8);
					break;
				case 32:
					set_shape_size(ss_16x32);
					break;
			}
		
		case 32:
			switch ( n_shape_size.y )
			{
				default:
				case 32:
					set_shape_size(ss_32x32);
					break;
				case 8:
					set_shape_size(ss_32x8);
					break;
				case 16:
					set_shape_size(ss_32x16);
					break;
				case 64:
					set_shape_size(ss_32x64);
					break;
			}
		
		case 64:
			switch ( n_shape_size.y )
			{
				default:
				case 64:
					set_shape_size(ss_64x64);
					break;
				case 32:
					set_shape_size(ss_64x32);
					break;
			}
		
	}
}


vec2_u32 oam_entry::get_shape_size_as_vec2() const
{
	return ss_to_vec2_arr[get_shape_size()];
}


