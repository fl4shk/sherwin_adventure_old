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


#ifndef waffle_sprite_class_hpp
#define waffle_sprite_class_hpp

#include "../../../gfx/the_powerup_gfx.h"


class WaffleSprite : public Sprite
{
public:		// enums
	// These are used To access misc_data_u and misc_data_s
	enum udata_index { udi_initial_pos_was_set, } _alignas_regular;
	enum sdata_index { sdi_initial_pos_x, sdi_initial_pos_y, 
		sdi_move_timer, } _alignas_regular;
	
public:		// variables
	static const SpriteConstParams the_const_params;
	
	static constexpr u32 move_timer_start = 128;
	
	
public:		// functions
	inline WaffleSprite(bool facing_left)
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	void update_part_2();
	
	inline virtual const SpriteConstParams& get_const_params() const
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
		(const BlockCollResult& lt_coll_result, 
		const BlockCollResult& lb_coll_result);
	
	virtual void block_coll_response_right_old
		(const BlockCollResult& rt_coll_result,
		const BlockCollResult& rb_coll_result);
	
	
	virtual void block_coll_response_left
		(const SprBlkCollGroupBase::HorizCollTuple& hs);
	virtual void block_coll_response_right
		(const SprBlkCollGroupBase::HorizCollTuple& hs);
	
} __attribute__((_align4));


#endif		// waffle_sprite_class_hpp
