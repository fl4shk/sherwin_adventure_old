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


#ifndef exclam_block_stuff_classes_hpp
#define exclam_block_stuff_classes_hpp

class ExclamBlockStuff : public BlockBaseStuff
{
public:		// enums
	enum persistent_data_state { is_exclam, is_bt_dud } 
		__attribute__((_align4));
	
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static const u32 metatile_number = 4;
	//static const u32 palette_number = 0;
	//static const u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
	virtual void strongly_hit_response(Block& the_block, 
		const vec2_s32& coord);
	
	virtual void finish_initializing_using_persistent_data
		(Block& the_block);
	
} __attribute__((_align4));

#endif		// exclam_block_stuff_classes_hpp
