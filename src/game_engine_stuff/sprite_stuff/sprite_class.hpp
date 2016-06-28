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


#ifndef sprite_class_hpp
#define sprite_class_hpp

#include "sprite_type_stuff.hpp"
#include "../level_stuff/sprite_level_data_stuff.hpp"


class sprite_allocator;

class sprite
{
protected:		// variables
	// These are protected variables because they're not normally supposed
	// to change after initialization.
	vec2_u32 the_shape_size_vec2;
	oam_entry::shape_size the_shape_size;
	
	// Which 32x32 VRAM chunk this sprite uses, which is equal to the
	// actual VRAM address divided by
	// gfx_manager::num_tiles_in_ss_32x32.  There are a few SPECIAL
	// cases where vram_chunk_index would need to be changed, so
	// set_vram_chunk_index() exists.
	u32 vram_chunk_index;
	
public:		// variables
	
	// General data
	
	// The type of sprite.
	sprite_type the_sprite_type;
	
	// the_sprite_ipg is a pointer to the level data of this sprite.  Even
	// though the_sprite_ipg contains an initial sprite_type, it is
	// normally the case that sprite_init_param_groups are stored in ROM,
	// so attempting to change the_sprite_ipg->type would not work for the
	// purposes of changing the sprite_type of sprites in different slots.
	sprite_init_param_group* the_sprite_ipg;
	
	// Here is one of the most essential member variables:  an oam_entry to
	// be copied to oam_mirror.
	oam_entry the_oam_entry;
	
	
	
	
	// Physics and collision and stuff
	
	// in_level_pos is the "global" position of the sprite within the
	// current level, connected to the top left corner.
	vec2_f24p8 in_level_pos;
	
	// vel is the velocity of the sprite.
	vec2_f24p8 vel;
	
	// The absolute value of the maximum horizontal velocity of the sprite
	fixed24p8 max_vel_x_abs_val;
	
	// The horizontal acceleration of the sprite
	fixed24p8 accel_x;
	
	
	
	// the_coll_box's "pos" member variable is the in-level
	// coordinate of the_coll_box.  Also, the_coll_box is
	// only used for non-oriented sprites.
	coll_box the_coll_box;
	
	// cb_pos_offset is the position of the coll_box relative to
	// in_level_pos.  It is used because most sprites will have a coll_box
	// with a size other than the visible 
	vec2_f24p8 cb_pos_offset;
	
	// on_ground is a flag that tells whether the sprite is on the ground,
	// though that's really obvious.
	bool on_ground;
	
	//// jump_hold_timer is used to keep track of for how much longer the
	//// sprite can jump, if the sprite even does so.  This coul
	//s32 jump_hold_timer;
	
	bool is_jumping;
	
	
	// Invincibility frames timer, enabled after taking damage.
	s32 invin_frame_timer;
	
	
	
	// Two arrays of miscellaneous sprite data.  The way these arrays are
	// used varies by the type of sprite.
	static constexpr u32 misc_data_size = 8;
	u32 misc_data_u[misc_data_size];
	s32 misc_data_s[misc_data_size];
	
	
	// These are mainly for debugging.
	//bool did_update_prev_on_screen_pos_this_frame;
	//vec2_f24p8 prev_on_screen_pos, curr_on_screen_pos;
	//prev_curr_pair<vec2_f24p8> on_screen_pos;
	//bool temp_debug_thing;
	
	
public:		// functions
	
	sprite();
	inline sprite( u32 s_vram_chunk_index )
	{
		sprite();
		
		vram_chunk_index = s_vram_chunk_index;
	}
	
	virtual void shared_constructor_code();
	
	void* operator new( size_t size, 
		sprite_allocator& the_sprite_allocator )
		__attribute__((_iwram_code));
	
	//void operator delete( void* the_sprite, 
	//	sprite_allocator& the_sprite_allocator );
	
	
	
	inline oam_entry::shape_size get_shape_size() const
	{
		return the_shape_size;
	}
	inline const vec2_u32& get_shape_size_as_vec2() const
	{
		return the_shape_size_vec2;
	}
	inline u32 get_vram_chunk_index() const
	{
		return vram_chunk_index;
	}
	inline void set_vram_chunk_index( u32 n_vram_chunk_index )
	{
		vram_chunk_index = n_vram_chunk_index;
	}
	
	inline void set_shape_size( oam_entry::shape_size n_shape_size )
	{
		the_shape_size = n_shape_size;
		the_oam_entry.set_shape_size(n_shape_size);
		the_shape_size_vec2 = get_shape_size_as_vec2_raw();
	}
	
	inline void update_f24p8_positions()
	{
		vel.x += accel_x;
		
		if ( max_vel_x_abs_val != (fixed24p8){0} )
		{
			if ( vel.x > max_vel_x_abs_val )
			{
				vel.x = max_vel_x_abs_val;
			}
			else if ( vel.x < -max_vel_x_abs_val )
			{
				vel.x = -max_vel_x_abs_val;
			}
		}
		
		in_level_pos += vel;
		the_coll_box.pos = in_level_pos + cb_pos_offset;
	}
	
	inline vec2_f24p8 get_on_screen_pos( const bg_point& camera_pos ) const
	{
		vec2_f24p8 ret( in_level_pos.x 
			- make_f24p8(camera_pos.x.trunc_to_int()), in_level_pos.y
			- make_f24p8(camera_pos.y.trunc_to_int()) );
		
		//ret.x = in_level_pos.x - make_f24p8(camera_pos.x.trunc_to_int());
		////ret.y = in_level_pos.y - camera_pos.y;
		//ret.y = in_level_pos.y - make_f24p8(camera_pos.y.trunc_to_int());
		
		////ret.x = ( in_level_pos.x - make_f24p8(camera_pos.x) );
		////ret.y = ( in_level_pos.y - make_f24p8(camera_pos.y) );
		//
		//ret = in_level_pos - camera_pos;
		//
		////ret.x.data = in_level_pos.x.data - camera_pos.x.data;
		////ret.y.data = in_level_pos.y.data - camera_pos.y.data;
		//
		//
		////ret.x = ( in_level_pos.x 
		////	- make_f24p8(camera_pos.x.true_round_via_trunc()) );
		////ret.y = ( in_level_pos.y 
		////	- make_f24p8(camera_pos.y.true_round_via_trunc()) );
		//
		////ret.x = ( in_level_pos.x 
		////	- make_f24p8(camera_pos.x.trunc_to_int()) );
		////ret.y = ( in_level_pos.y 
		////	- make_f24p8(camera_pos.y.trunc_to_int()) );
		
		return ret;
	}
	
	void update_on_screen_pos( const bg_point& camera_pos )
		__attribute__((_iwram_code));
	
	//inline void update_full( const bg_point& camera_pos )
	//{
	//	//in_level_pos += vel;
	//	//the_coll_box.pos = in_level_pos + cb_pos_offset;
	//	
	//	update_f24p8_positions();
	//	
	//	update_on_screen_pos(camera_pos);
	//	
	//	//sprite_stuff_array[the_sprite_type]
	//	sprite_stuff_array[the_sprite_type]->update(*this);
	//}
	
	void camera_follow_basic( bg_point& camera_pos )
		__attribute__((_iwram_code));
	void center_camera_almost( bg_point& camera_pos ) const
		__attribute__((_iwram_code));
	
	
	//inline void copy_the_oam_entry_to_oam_mirror 
	//	( u32 slot_for_oam_mirror )
	//{
	//	oam_mirror[slot_for_oam_mirror].attr0 = the_oam_entry.attr0;
	//	oam_mirror[slot_for_oam_mirror].attr1 = the_oam_entry.attr1;
	//	oam_mirror[slot_for_oam_mirror].attr2 = the_oam_entry.attr2;
	//}
	
	//void copy_the_oam_entry_to_oam_mirror( u32 slot_for_oam_mirror )
	//	__attribute__((_iwram_code));
	
	inline void copy_the_oam_entry_to_oam_mirror( u32 slot_for_oam_mirror )
	{
		oam_mirror[slot_for_oam_mirror].attr0 = the_oam_entry.attr0;
		oam_mirror[slot_for_oam_mirror].attr1 = the_oam_entry.attr1;
		oam_mirror[slot_for_oam_mirror].attr2 = the_oam_entry.attr2;
	}
	
	void block_collision_stuff() __attribute__((_iwram_code));
	
	
protected:		// functions
	vec2_u32 get_shape_size_as_vec2_raw() const
		__attribute__((_iwram_code));
	
	
} __attribute__((_align4));


#endif		// sprite_class_hpp
