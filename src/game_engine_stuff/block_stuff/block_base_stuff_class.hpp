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


#ifndef block_base_stuff_class_hpp
#define block_base_stuff_class_hpp

class BlockStuffConstParams
{
public:		// variables
	u32 metatile_number = 0;
	u32 palette_number = 0;
	u32 metatile_graphics_slot = metatile_number;
	block_behavior_type behavior_type = bbvt_solid;
	
} __attribute__((_ALIGN4));


class BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static const u32 metatile_number = 0;
	//static const u32 palette_number = 0;
	//static const u32 metatile_graphics_slot = metatile_number;
	//static constexpr block_behavior_type behavior_type = bbvt_solid;
	
	// Slope stuff
	static constexpr u32 height_mask_size = num_pixels_per_block_row;
	
	static const u32 * const height_mask_ptr_arr[lim_bbvt];
	
	static const u32 air_height_mask[height_mask_size];
	static const u32 solid_height_mask[height_mask_size];
	
	// 45 degree angle slope height mask
	static const u32 slope_p16_p16_height_mask[height_mask_size];
	
	// 135 degree angle slope height mask
	static const u32 slope_n16_p16_height_mask[height_mask_size];
	
	// Approximately 26.57 degrees angle slope short Block height mask
	static const u32 slope_p32_p16_short_height_mask[height_mask_size];
	
	// Approximately 26.57 degrees angle slope tall Block height mask
	static const u32 slope_p32_p16_tall_height_mask[height_mask_size];
	
	// Approximately 153.43 degrees angle slope, with two blocks
	static const u32 slope_n32_p16_tall_height_mask[height_mask_size];
	
	static const u32 slope_n32_p16_short_height_mask[height_mask_size];
	
	
public:		// functions
	virtual const BlockStuffConstParams& get_const_params() const;
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
	virtual block_behavior_type get_behavior_type();
	
	virtual void strongly_hit_response( Block& the_block, 
		const vec2_s32& coord );
	
	virtual void finish_initializing_using_persistent_data
		( Block& the_block );
	
	
} __attribute__((_ALIGN4));


#endif		// block_base_stuff_class_hpp
