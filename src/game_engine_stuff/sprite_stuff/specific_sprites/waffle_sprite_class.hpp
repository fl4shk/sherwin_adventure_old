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
// General Public License FOR more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef waffle_sprite_class_hpp
#define waffle_sprite_class_hpp

#include "../../../gfx/the_powerup_gfx.h"


class waffle_sprite : public sprite
{
public:		// enums
	// These are used to access misc_data_u and misc_data_s
	enum udata_index { udi_initial_pos_was_set, } _ALIGNAS_REGULAR;
	enum sdata_index { sdi_initial_pos_x, sdi_initial_pos_y, 
		sdi_move_timer, } _ALIGNAS_REGULAR;
	
public:		// variables
	static const sprite_const_params the_const_params;
	
	static constexpr u32 move_timer_start = 128;
	
	
public:		// functions
	inline waffle_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	void update_part_2();
	
	inline virtual const sprite_const_params& get_const_params() const
	{
		return the_const_params;
	}
	
	// Physics and collision stuff
	inline virtual void block_collision_stuff()
	{
		block_collision_stuff_16x16();
	}
	
	
protected:		// functions
	virtual void block_coll_response_left_old
		( const block_coll_result& lt_coll_result, 
		const block_coll_result& lb_coll_result );
	
	virtual void block_coll_response_right_old
		( const block_coll_result& rt_coll_result,
		const block_coll_result& rb_coll_result );
	
	
	virtual void block_coll_response_left
		( const spr_blk_coll_group_base::horiz_coll_tuple& hs );
	virtual void block_coll_response_right
		( const spr_blk_coll_group_base::horiz_coll_tuple& hs );
	
} __attribute__((_ALIGN4));


#endif		// waffle_sprite_class_hpp
