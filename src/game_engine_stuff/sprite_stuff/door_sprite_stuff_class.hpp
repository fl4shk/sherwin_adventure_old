// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#ifndef door_sprite_stuff_class_hpp
#define door_sprite_stuff_class_hpp

#include "../../gfx/the_door_gfx.h"

class sublevel_entrance;

class door_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static constexpr sprite_type the_sprite_type = st_door;
	static constexpr sprite_palette_slot the_palette_slot = sps_door;
	static constexpr u32 the_relative_metatile_slot = 0, 
		num_active_gfx_tiles = gfx_manager::num_tiles_in_ss_16x32;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(the_door_gfxTiles));
	
	static const oam_entry::shape_size the_initial_shape_size 
		= oam_entry::ss_16x32;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
public:		// functions
	virtual void init( sprite& the_door, bool facing_left=false );
	
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	// Graphics stuff
	//virtual void gfx_update( sprite& the_door );
	
	inline virtual const sprite_palette_slot get_palette_slot
		( sprite& the_door )
	{
		return the_palette_slot;
	}
	inline virtual const u32 get_curr_relative_tile_slot
		( sprite& the_door )
	{
		return the_relative_metatile_slot * num_active_gfx_tiles;
	}
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
	}
	
	inline virtual const oam_entry::shape_size get_the_initial_shape_size() 
		const
	{
		return the_initial_shape_size;
	}
	
	inline virtual const vec2_f24p8& get_the_initial_coll_box_size() const
	{
		return the_initial_coll_box_size;
	}
	inline virtual const vec2_f24p8& get_the_initial_cb_pos_offset() const
	{
		return the_initial_cb_pos_offset;
	}
	
	// Initial
	//static const sublevel_entrance& get_dest_sle( sprite& the_door );
	
	
	// Physics and collision stuff
	//// All door sprites are not affected by gravity, and they don't move.
	//virtual void block_collision_stuff( sprite& the_door );
	
	
} __attribute__((_align4));


#endif		// door_sprite_stuff_class_hpp
