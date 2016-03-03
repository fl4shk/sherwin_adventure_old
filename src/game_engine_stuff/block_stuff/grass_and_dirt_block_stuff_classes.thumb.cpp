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


#include "block_stuff.hpp"

// Slope height masks

// 45 degree angle slope height mask
const u32 
	grass_slope_p16_p16_block_stuff::height_mask[height_mask_size] 
	= { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

// 135 degree angle slope height mask
const u32 
	grass_slope_n16_p16_block_stuff::height_mask[height_mask_size] 
	= { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };


// Approximately 26.57 degrees angle slope short block height mask
const u32
	grass_slope_p32_p16_short_block_stuff::height_mask[height_mask_size]
	= { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7 };
// Approximately 26.57 degrees angle slope tall block height mask
const u32
	grass_slope_p32_p16_tall_block_stuff::height_mask[height_mask_size]
	= { 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15 };

// Approximately 153.43 degrees angle slope, with two blocks
const u32 
	grass_slope_n32_p16_tall_block_stuff::height_mask[height_mask_size]
	= { 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8 };
const u32
	grass_slope_n32_p16_short_block_stuff::height_mask[height_mask_size]
	= { 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0 };
