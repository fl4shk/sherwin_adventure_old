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


void oam_entry::set_shape_size( oam_entry::shape_size n_shape_size )
{
	u32 temp_attr0 = attr0, temp_attr1 = attr1;
	
	switch(n_shape_size)
	{
		// Square shapes
		default:
		case ss_8x8:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_square );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_0 );
			break;
		
		case ss_16x16:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_square );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_1 );
			break;
		
		
		case ss_32x32:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_square );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_2 );
			break;
		
		
		case ss_64x64:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_square );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_3 );
			break;
		
		
		// Horizontal shapes
		case ss_16x8:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_horizontal );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_0 );
			break;
		
		
		case ss_32x8:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_horizontal );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_1 );
			break;
		
		
		case ss_32x16:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_horizontal );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_2 );
			break;
		
		
		case ss_64x32:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_horizontal );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_3 );
			break;
		
		
		// Vertical shapes
		case ss_8x16:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_vertical );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_0 );
			break;
		
		
		case ss_8x32:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_vertical );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_1 );
			break;
		
		
		case ss_16x32:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_vertical );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_2 );
			break;
		
		
		case ss_32x64:
			clear_and_set_bits( temp_attr0, obj_attr0_shape_mask,
				obj_attr0_shape_vertical );
			clear_and_set_bits( temp_attr1, obj_attr1_size_mask,
				obj_attr1_size_3 );
			break;
	}
	
	attr0 = (u16)( temp_attr0 & 0xffff );
	attr1 = (u16)( temp_attr1 & 0xffff );
	
}



oam_entry::shape_size oam_entry::get_shape_size() const
{
	u32 attr0_shape = get_bits( attr0, obj_attr0_shape_mask );
	u32 attr1_size = get_bits( attr1, obj_attr1_size_mask );
	
	switch ( attr0_shape )
	{
		default:
		case obj_attr0_shape_square:
			switch ( attr1_size )
			{
				default:
				case obj_attr1_size_0:
					return ss_8x8;
				
				case obj_attr1_size_1:
					return ss_16x16;
				
				case obj_attr1_size_2:
					return ss_32x32;
				
				case obj_attr1_size_3:
					return ss_64x64;
			}
		
		case obj_attr0_shape_horizontal:
			switch ( attr1_size )
			{
				default:
				case obj_attr1_size_0:
					return ss_16x8;
					
				case obj_attr1_size_1:
					return ss_32x8;
					
				case obj_attr1_size_2:
					return ss_32x16;
					
				case obj_attr1_size_3:
					return ss_64x32;
			}
		
		case obj_attr0_shape_vertical:
			switch ( attr1_size )
			{
				default:
				case obj_attr1_size_0:
					return ss_8x16;
					
				case obj_attr1_size_1:
					return ss_8x32;
					
				case obj_attr1_size_2:
					return ss_16x32;
					
				case obj_attr1_size_3:
					return ss_32x64;
			}
		
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
	switch ( get_shape_size() )
	{
		// Square shapes
		case ss_8x8:
			return { 8, 8 };
		case ss_16x16:
			return { 16, 16 };
		case ss_32x32:
			return { 32, 32 };
		case ss_64x64:
			return { 64, 64 };
		
		// Horizontal shapes
		case ss_16x8:
			return { 16, 8 };
		case ss_32x8:
			return { 32, 8 };
		case ss_32x16:
			return { 32, 16 };
		case ss_64x32:
			return { 64, 32 };
		
		// Vertical shapes
		case ss_8x16:
			return { 8, 16 };
		case ss_8x32:
			return { 8, 32 };
		case ss_16x32:
			return { 16, 32 };
		case ss_32x64:
			return { 32, 64 };
	}
}


