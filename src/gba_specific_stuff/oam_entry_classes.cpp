// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andrew Clark (FL4SHK).
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


namespace sherwin_adventure
{

namespace gba
{

// I'm tempted To put these two arrays in _iwram.
OamEntry oam_mirror[oam_mirror_size];
//OamEntryAffine* const OAM_MIRROR_AFF = (OamEntryAffine*)oam_mirror ;


const Vec2U32 OamEntry::ss_to_vec2_arr[lim_ss]
= {
	// Square shapes
	{ 8, 8 }, { 16, 16 }, { 32, 32 }, { 64, 64 },

	// Horizontal shapes
	{ 16, 8 }, { 32, 8 }, { 32, 16 }, { 64, 32 },

	// Vertical shapes
	{ 8, 16 }, { 8, 32 }, { 16, 32 }, { 32, 64 },
};

const Vec2U32 OamEntry::ss_enum_to_ss_attrs_arr[lim_ss]
= {
	// Square shapes
	{ OBJ_ATTR0_SHAPE_SQUARE, OBJ_ATTR1_SIZE_0 }, 
	{ OBJ_ATTR0_SHAPE_SQUARE, OBJ_ATTR1_SIZE_1 }, 
	{ OBJ_ATTR0_SHAPE_SQUARE, OBJ_ATTR1_SIZE_2 }, 
	{ OBJ_ATTR0_SHAPE_SQUARE, OBJ_ATTR1_SIZE_3 },

	// Horizontal shapes
	{ OBJ_ATTR0_SHAPE_HORIZONTAL, OBJ_ATTR1_SIZE_0 }, 
	{ OBJ_ATTR0_SHAPE_HORIZONTAL, OBJ_ATTR1_SIZE_1 }, 
	{ OBJ_ATTR0_SHAPE_HORIZONTAL, OBJ_ATTR1_SIZE_2 }, 
	{ OBJ_ATTR0_SHAPE_HORIZONTAL, OBJ_ATTR1_SIZE_3 },

	// Vertical shapes
	{ OBJ_ATTR0_SHAPE_VERTICAL, OBJ_ATTR1_SIZE_0 }, 
	{ OBJ_ATTR0_SHAPE_VERTICAL, OBJ_ATTR1_SIZE_1 }, 
	{ OBJ_ATTR0_SHAPE_VERTICAL, OBJ_ATTR1_SIZE_2 }, 
	{ OBJ_ATTR0_SHAPE_VERTICAL, OBJ_ATTR1_SIZE_3 },
};

//const OamEntry::shape_size OamEntry::ss_attrs_no_shift_to_ss_enum_arr_2d
//	[num_attr0_shapes][num_attr1_sizes]
//= {
//	// Square shapes
//	{ ss_8x8, ss_16x16, ss_32x32, ss_64x64 },
//
//	// Horizontal shapes
//	{ ss_16x8, ss_32x8, ss_32x16, ss_64x32 },
//
//	// Vertical shapes
//	{ ss_8x16, ss_8x32, ss_16x32, ss_32x64 },
//};


void OamEntry::set_shape_size(OamEntry::shape_size n_shape_size)
{
	u32 temp_attr0 = attr0, temp_attr1 = attr1;

	if (n_shape_size < 0 || n_shape_size >= lim_ss)
	{
		const Vec2U32& ss_attrs_vec2 = ss_enum_to_ss_attrs_arr[0];

		clear_and_set_bits(temp_attr0, OBJ_ATTR0_SHAPE_MASK,
			ss_attrs_vec2.x);
		clear_and_set_bits(temp_attr1, OBJ_ATTR1_SIZE_MASK,
			ss_attrs_vec2.y);
	}
	else
	{
		const Vec2U32& ss_attrs_vec2 = ss_enum_to_ss_attrs_arr
			[n_shape_size];

		clear_and_set_bits(temp_attr0, OBJ_ATTR0_SHAPE_MASK,
			ss_attrs_vec2.x);
		clear_and_set_bits(temp_attr1, OBJ_ATTR1_SIZE_MASK,
			ss_attrs_vec2.y);
	}


	attr0 = (u16)(temp_attr0 & 0xffff);
	attr1 = (u16)(temp_attr1 & 0xffff);

}



OamEntry::shape_size OamEntry::get_shape_size() const
{
	u32 attr0_shape_no_shift = get_bits(attr0, OBJ_ATTR0_SHAPE_MASK,
		OBJ_ATTR0_SHAPE_SHIFT);
	u32 attr1_size_no_shift = get_bits(attr1, OBJ_ATTR1_SIZE_MASK,
		OBJ_ATTR1_SIZE_SHIFT);

	// Error checking
	if (attr0_shape_no_shift >= num_attr0_shapes 
		|| attr1_size_no_shift >= num_attr1_sizes)
	{
		//return ss_attrs_no_shift_to_ss_enum_arr_2d[0][0];
		return shape_size(0);
	}
	else
	{
		//return ss_attrs_no_shift_to_ss_enum_arr_2d[attr0_shape_no_shift]
		//	[attr1_size_no_shift];

		// Multiply by num_attr1_sizes because the expression becomes a
		// single shift and an add instead of a shift and two adds.
		return shape_size(attr0_shape_no_shift * num_attr1_sizes 
			+ attr1_size_no_shift);
	}
}

void OamEntry::set_shape_size_with_vec2(const Vec2U32& n_shape_size)
{
	switch (n_shape_size.x)
	{
		default:
		case 8:
			switch (n_shape_size.y)
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
			switch (n_shape_size.y)
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
			switch (n_shape_size.y)
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
			switch (n_shape_size.y)
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


Vec2U32 OamEntry::get_shape_size_as_vec2() const
{
	return ss_to_vec2_arr[get_shape_size()];
}

}

}
