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


#ifndef waffle_sprite_class_hpp
#define waffle_sprite_class_hpp

#include "../../gfx/the_powerup_gfx.h"


class waffle_sprite : public sprite
{
public:		// enums
	// These are used to access misc_data_u and misc_data_s
	enum udata_index { udi_initial_pos_was_set, } alignas_regular;
	enum sdata_index { sdi_initial_pos_x, sdi_initial_pos_y, 
		sdi_move_timer, } alignas_regular;
	
public:		// variables
	static constexpr sprite_type the_const_sprite_type = st_waffle;
	static constexpr sprite_palette_slot the_palette_slot = sps_powerup;
	static constexpr u32 the_relative_metatile_slot = 0, 
		num_active_gfx_tiles = gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr u32 move_timer_start = 128;
	
	//static const ();
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(the_powerup_gfxTiles));
	
public:		// functions
	inline waffle_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	//virtual void shared_constructor_code( bool facing_left );
	inline virtual const sprite_type get_const_sprite_type() const
	{
		return the_const_sprite_type;
	}
	
	
	virtual void update_part_2();
	
	// Graphics stuff
	//virtual void gfx_update();
	
	inline virtual const sprite_palette_slot get_palette_slot()
	{
		return the_palette_slot;
	}
	inline const u32 get_curr_relative_tile_slot()
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
	
	
	// Physics and collision stuff
	inline virtual void block_collision_stuff()
	{
		block_collision_stuff_16x16();
	}
	
	
protected:		// functions
	virtual void block_coll_response_left_16x16_old
		( const block_coll_result& lt_coll_result, 
		const block_coll_result& lb_coll_result );
	
	virtual void block_coll_response_right_16x16_old
		( const block_coll_result& rt_coll_result,
		const block_coll_result& rb_coll_result );
	
	
	virtual void block_coll_response_left_16x16
		( const block_coll_result_rect_group& the_bcr_rect_group );
	virtual void block_coll_response_right_16x16
		( const block_coll_result_rect_group& the_bcr_rect_group );
	
} __attribute__((_align4));


#endif		// waffle_sprite_class_hpp
