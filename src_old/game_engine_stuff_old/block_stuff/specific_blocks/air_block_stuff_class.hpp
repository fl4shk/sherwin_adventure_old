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


#ifndef air_block_stuff_class_hpp
#define air_block_stuff_class_hpp

class AirBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static const u32 metatile_number = 0;
	//static const u32 palette_number = 0;
	//static const u32 metatile_graphics_slot = metatile_number;
	//static constexpr block_behavior_type behavior_type = bbvt_air;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
	virtual void strongly_hit_response(Block& the_block, 
		const vec2_s32& coord);
	
} __attribute__((_align4));

#endif		// air_block_stuff_class_hpp
