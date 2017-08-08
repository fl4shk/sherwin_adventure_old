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


#ifndef grass_and_dirt_block_stuff_classes_hpp
#define grass_and_dirt_block_stuff_classes_hpp


class GrassSingleBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 6;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	// Turns out That inline virtual Is not actually inline.
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));

class GrassTopLeftBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 7;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class GrassTopMiddleBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 8;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class GrassTopRightBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 9;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));


class DirtMiddleLeftBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 10;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class DirtMiddleMiddleBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 11;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class DirtMiddleRightBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 12;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));

class DirtBottomLeftBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 13;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class DirtBottomMiddleBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 14;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class DirtBottomRightBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 15;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));

// Slopes
class GrassSlopeP16P16BlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 16;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	//static constexpr block_behavior_type behavior_type 
	//	= bbvt_slope_p16_p16;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class GrassSlopeN16P16BlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 17;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	//static constexpr block_behavior_type behavior_type 
	//	= bbvt_slope_n16_p16;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));

class GrassSlopeP32P16ShortBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 18;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	//static constexpr block_behavior_type behavior_type 
	//	= bbvt_slope_p32_p16_short;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));

class GrassSlopeP32P16TallBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 19;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	//static constexpr block_behavior_type behavior_type 
	//	= bbvt_slope_p32_p16_tall;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));

class GrassSlopeN32P16TallBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 20;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	//static constexpr block_behavior_type behavior_type 
	//	= bbvt_slope_n32_p16_tall;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class GrassSlopeN32P16ShortBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 21;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	//static constexpr block_behavior_type behavior_type 
	//	= bbvt_slope_n32_p16_short;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));

class GrassInSlopeLeftBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 22;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));
class GrassInSlopeRightBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static constexpr u32 metatile_number = 23;
	//static constexpr u32 palette_number = 0;
	//static constexpr u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
} __attribute__((_align4));


#endif		// grass_and_dirt_block_stuff_classes_hpp
