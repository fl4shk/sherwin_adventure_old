// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#include "../level_stuff/active_level_class.hpp"
#include "../../general_utility_stuff/misc_types.hpp"

const BlockStuffConstParams BlockBaseStuff::the_const_params;

const u32 * const BlockBaseStuff::height_mask_ptr_arr[lim_bbvt]
	= { reinterpret_cast<const u32 * const>
		(&(air_height_mask[0])), 
	reinterpret_cast<const u32 * const>
		(&(solid_height_mask[0])), 
	reinterpret_cast<const u32 * const>
		(&(slope_p16_p16_height_mask[0])),
	reinterpret_cast<const u32 * const>
		(&(slope_n16_p16_height_mask[0])), 
	reinterpret_cast<const u32 * const>
		(&(slope_p32_p16_short_height_mask[0])),
	reinterpret_cast<const u32 * const>
		(&(slope_p32_p16_tall_height_mask[0])), 
	reinterpret_cast<const u32 * const>
		(&(slope_n32_p16_tall_height_mask[0])),
	reinterpret_cast<const u32 * const>
		(&(slope_n32_p16_short_height_mask[0])) };

const u32 BlockBaseStuff::air_height_mask[height_mask_size]
	= { 0, 0, 0, 0, 
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0 };
const u32 BlockBaseStuff::solid_height_mask[height_mask_size]
	= { num_pixels_per_block_dim, num_pixels_per_block_dim, 
		num_pixels_per_block_dim, num_pixels_per_block_dim, 
		num_pixels_per_block_dim, num_pixels_per_block_dim, 
		num_pixels_per_block_dim, num_pixels_per_block_dim,
		num_pixels_per_block_dim, num_pixels_per_block_dim, 
		num_pixels_per_block_dim, num_pixels_per_block_dim,
		num_pixels_per_block_dim, num_pixels_per_block_dim, 
		num_pixels_per_block_dim, num_pixels_per_block_dim };

// Slope height masks

// 45 degree angle slope height mask
const u32 BlockBaseStuff::slope_p16_p16_height_mask[height_mask_size] 
	= { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

// 135 degree angle slope height mask
const u32 BlockBaseStuff::slope_n16_p16_height_mask[height_mask_size] 
	= { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };


// Approximately 26.57 degrees angle slope short Block height mask
const u32 BlockBaseStuff::slope_p32_p16_short_height_mask
	[height_mask_size] 
	= { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7 };
// Approximately 26.57 degrees angle slope tall Block height mask
const u32 BlockBaseStuff::slope_p32_p16_tall_height_mask
	[height_mask_size]
	= { 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15 };

// Approximately 153.43 degrees angle slope, with two blocks
const u32 BlockBaseStuff::slope_n32_p16_tall_height_mask
	[height_mask_size]
	= { 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8 };
const u32 BlockBaseStuff::slope_n32_p16_short_height_mask
	[height_mask_size] 
	= { 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0 };



const BlockStuffConstParams& BlockBaseStuff::get_const_params() const
{
	return the_const_params;
}

const u32 BlockBaseStuff::get_metatile_number()
{
	return get_const_params().metatile_number;
}
const u32 BlockBaseStuff::get_palette_number()
{
	return get_const_params().palette_number;
}
const u32 BlockBaseStuff::get_metatile_graphics_slot()
{
	return get_const_params().metatile_graphics_slot;
}
block_behavior_type BlockBaseStuff::get_behavior_type()
{
	return get_const_params().behavior_type;
}

// Dummy function To be implemented by classes That inherit from this one,
// if they need it.
void BlockBaseStuff::strongly_hit_response( Block& the_block, 
	const vec2_s32& coord )
{
}

// Dummy function To be implemented by classes That inherit from this one,
// if they need it.
void BlockBaseStuff::finish_initializing_using_persistent_data
	( Block& the_block )
{
}


