// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#ifndef eyes_block_stuff_classes_hpp
#define eyes_block_stuff_classes_hpp

class eyes_block_stuff : public block_base_stuff
{
public:		// enums
	enum persistent_data_state { is_eyes, is_bt_dud } alignas_regular;
	
public:		// variables
	static const u32 metatile_number = 3;
	static const u32 palette_number = 0;
	static const u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	virtual const u32 get_metatile_number();
	virtual const u32 get_palette_number();
	virtual const u32 get_metatile_graphics_slot();
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord );
	
	virtual void finish_initializing_using_persistent_data
		( block& the_block );
	
} __attribute__((_align4));


class eyes_block_with_st_waffle_stuff : public eyes_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord );
	
} __attribute__((_align4));

class eyes_block_with_st_muffin_stuff : public eyes_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord );
	
} __attribute__((_align4));

class eyes_block_with_st_fire_muffin_stuff : public eyes_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord );
	
} __attribute__((_align4));

class eyes_block_with_st_ice_muffin_stuff : public eyes_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord );
	
} __attribute__((_align4));

class eyes_block_with_st_chocolate_muffin_stuff : public eyes_block_stuff
{
public:		// functions
	virtual void strongly_hit_response( block& the_block, 
		const vec2_s32& coord );
	
} __attribute__((_align4));


#endif		// eyes_block_stuff_classes_hpp
