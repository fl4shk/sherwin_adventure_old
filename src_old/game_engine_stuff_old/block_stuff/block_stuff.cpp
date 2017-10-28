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


//#include "block_stuff.hpp"
#include "../level_stuff/active_level_class.hpp"

#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/dma_stuff.hpp"

#define X(name) \
	name the_##name;
LIST_OF_BLOCK_STUFF_CLASSES(X)
#undef X

std::array<BlockBaseStuff*, lim_bt> block_stuff_array
= {
	#define X(name) \
		&the_##name,
	LIST_OF_BLOCK_STUFF_CLASSES(X)
	#undef X
};



bool bbvt_is_left_slope(block_behavior_type behavior_type)
{
	switch (behavior_type)
	{
		#define X(name) \
			\
			case bbvt_slope_##name: \
				return true; \
				break;

		LIST_OF_LEFT_SLOPE_CONFIGURATIONS(X)
		#undef X

		default:
			return false;
			break;
	}
}


bool bbvt_is_right_slope(block_behavior_type behavior_type)
{
	switch (behavior_type)
	{
		#define X(name) \
			\
			case bbvt_slope_##name: \
				return true; \
				break;

		LIST_OF_RIGHT_SLOPE_CONFIGURATIONS(X)
		#undef X

		default:
			return false;
			break;
	}
}



bool get_left_following_slope_bbvt(block_behavior_type any_slope_bbvt_in, 
	block_behavior_type& some_slope_bbvt_out, s32& blk_crd_y_pos_offset)
{
	switch (any_slope_bbvt_in)
	{
		// 45 degree angle slope (up and To the right)
		case bbvt_slope_p16_p16:
			some_slope_bbvt_out = bbvt_slope_p16_p16;
			blk_crd_y_pos_offset = 1;
			break;

		// 135 degree angle slope (up and To the left)
		case bbvt_slope_n16_p16:
			some_slope_bbvt_out = bbvt_slope_n16_p16;
			blk_crd_y_pos_offset = -1;
			break;

		// Approximately 26.57 degrees angle slope, with two blocks (up and
		// To the right)
		case bbvt_slope_p32_p16_short:
			some_slope_bbvt_out = bbvt_slope_p32_p16_tall;
			blk_crd_y_pos_offset = 1;
			break;

		case bbvt_slope_p32_p16_tall:
			some_slope_bbvt_out = bbvt_slope_p32_p16_short;
			blk_crd_y_pos_offset = 0;
			break;


		// Approximately 153.43 degrees angle slope, with two blocks (up
		// and To the left)
		case bbvt_slope_n32_p16_tall:
			some_slope_bbvt_out = bbvt_slope_n32_p16_short;
			blk_crd_y_pos_offset = -1;
			break;

		case bbvt_slope_n32_p16_short:
			some_slope_bbvt_out = bbvt_slope_n32_p16_short;
			blk_crd_y_pos_offset = 0;
			break;

		default:
			return false;
	}

	return true;
}
bool get_right_following_slope_bbvt(block_behavior_type any_slope_bbvt_in, 
	block_behavior_type& some_slope_bbvt_out, s32& blk_crd_y_pos_offset)
{
	switch (any_slope_bbvt_in)
	{
		// 45 degree angle slope (up and To the right)
		case bbvt_slope_p16_p16:
			some_slope_bbvt_out = bbvt_slope_p16_p16;
			blk_crd_y_pos_offset = -1;
			break;

		// 135 degree angle slope (up and To the left)
		case bbvt_slope_n16_p16:
			some_slope_bbvt_out = bbvt_slope_n16_p16;
			blk_crd_y_pos_offset = 1;
			break;

		// Approximately 26.57 degrees angle slope, with two blocks (up and
		// To the right)
		case bbvt_slope_p32_p16_short:
			some_slope_bbvt_out = bbvt_slope_p32_p16_tall;
			blk_crd_y_pos_offset = 0;
			break;

		case bbvt_slope_p32_p16_tall:
			some_slope_bbvt_out = bbvt_slope_p32_p16_short;
			blk_crd_y_pos_offset = -1;
			break;


		// Approximately 153.43 degrees angle slope, with two blocks (up
		// and To the left)
		case bbvt_slope_n32_p16_tall:
			some_slope_bbvt_out = bbvt_slope_n32_p16_short;
			blk_crd_y_pos_offset = -1;
			break;

		case bbvt_slope_n32_p16_short:
			some_slope_bbvt_out = bbvt_slope_n32_p16_short;
			blk_crd_y_pos_offset = 0;
			break;

		default:
			return false;
	}

	return true;
}
