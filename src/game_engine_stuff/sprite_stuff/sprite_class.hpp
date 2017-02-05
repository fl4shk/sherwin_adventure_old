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


#ifndef sprite_class_hpp
#define sprite_class_hpp

#include "sprite_type_stuff.hpp"
#include "../level_stuff/sprite_level_data_stuff.hpp"

#include "../../gfx/sherwin_gfx.h"

#include "../block_coll_result_group_classes.hpp"

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
	
	// These two things are used for FAST sprite allocation via a
	// sa_free_list_backend member variable in a sprite_allocator instance.
	int the_arr_index;
	friend class sprite_allocator;
	
public:		// constants
	
	static const fixed24p8 cpg_on_slope_threshold_abs;
	
	// coll_point_group threshold
	static const vec2_f24p8 cpg_16x32_threshold_abs;
	
	static const fixed24p8 grav_acc;
	static const fixed24p8 max_y_vel;
	
	
	static const sprite_type the_const_sprite_type;
	static const sprite_palette_slot the_palette_slot;
	
	static const u32 the_relative_metatile_slot,
		num_active_gfx_tiles;
	static const tile* tile_arr;
	static const oam_entry::shape_size the_initial_shape_size;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
	// This is used to correct the initial in-level position for sprites
	// that are normally considered to be of a certain size but that use
	// larger graphics for some frames.  An example of this is the
	// st_player sprite_type, which is normally considered to be a 16x32
	// sprite but uses 32x32 graphics in some cases, like during the
	// pickaxe swing animation.
	static const vec2_f24p8 the_initial_in_level_pos_offset;
	
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
	prev_curr_pair<vec2_f24p8> in_level_pos;
	
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
	prev_curr_pair<bool> on_ground;
	
	
	//// jump_hold_timer is used to keep track of for how much longer the
	//// sprite can jump, if the sprite even does so.  This coul
	//s32 jump_hold_timer;
	
	bool is_jumping;
	
	
	prev_curr_pair<bool> on_slope;
	
	// Invincibility frames timer, enabled after taking damage.
	s32 invin_frame_timer;
	
	
	
	// Two arrays of miscellaneous sprite data.  The way these arrays are
	// used varies by the type of sprite.  Also, since a more natural
	// sprite type system is going to be used, they could be gotten rid of
	// and replaced with variables that only 
	static constexpr u32 misc_data_size = 8;
	u32 misc_data_u[misc_data_size];
	s32 misc_data_s[misc_data_size];
	
	
	// These are mainly for debugging.
	//bool did_update_prev_on_screen_pos_this_frame;
	//vec2_f24p8 prev_on_screen_pos, curr_on_screen_pos;
	//prev_curr_pair<vec2_f24p8> on_screen_pos;
	//prev_curr_pair<vec2_s32> on_screen_pos_s32;
	
	static vec2_f24p8 prev_prev_on_screen_pos; 
	static prev_curr_pair<vec2_f24p8> on_screen_pos;
	static vec2_s32 prev_prev_on_screen_pos_s32;
	static prev_curr_pair<vec2_s32> on_screen_pos_s32;
	static prev_curr_pair<vec2_s32> camera_pos_pc_pair_s32;
	
	static vec2<bool> temp_debug_thing;
	
	static vec2_f24p8 on_screen_pos_diff_abs;
	static vec2_s32 on_screen_pos_s32_diff_abs;
	static vec2_f24p8 camera_pos_diff_abs;
	static vec2_s32 camera_pos_s32_diff_abs;
	
public:		// functions
	
	sprite();
	sprite( bool facing_left );
	sprite( const vec2_f24p8& s_in_level_pos, 
		const prev_curr_pair<bg_point>& camera_pos_pc_pair, 
		bool facing_left );
	sprite( const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, 
		prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left );
	
	
	inline sprite( u32 s_vram_chunk_index )
	{
		sprite();
		
		vram_chunk_index = s_vram_chunk_index;
	}
	
	
	// This function is NOT virtual because because it uses virtual
	// functions.
	void shared_constructor_code_part_1();
	
	
	// Derived classes should override this function
	// This is the default form of shared_constructor_code().
	virtual void shared_constructor_code_part_2( bool facing_left );
	
	// This form of shared_constructor_code() might eventually become the
	// default form of shared_constructor_code().
	virtual void shared_constructor_code_part_2
		( const vec2_f24p8& s_in_level_pos, 
		const prev_curr_pair<bg_point>& camera_pos_pc_pair, 
		bool facing_left );
	
	// This form of shared_constructor_code() is primarily intended to be
	// used by the_player.
	virtual void shared_constructor_code_part_2
		( const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, 
		prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left );
	
	virtual void shared_constructor_code_part_3();
	
	void* operator new( size_t size, 
		sprite_allocator& the_sprite_allocator )
		__attribute__((_iwram_code));
	
	//void operator delete( void* the_sprite, 
	//	sprite_allocator& the_sprite_allocator );
	
	
	inline const vec2_f24p8& get_prev_in_level_pos() const
	{
		return in_level_pos.prev;
	}
	//inline const fixed24p8& get_prev_in_level_pos_x() const
	//{
	//	return get_prev_in_level_pos().x;
	//}
	//inline const fixed24p8& get_prev_in_level_pos_y() const
	//{
	//	return get_prev_in_level_pos().y;
	//}
	
	inline const vec2_f24p8& get_curr_in_level_pos() const
	{
		return in_level_pos.curr;
	}
	//inline const fixed24p8& get_curr_in_level_pos_x() const
	//{
	//	return get_curr_in_level_pos().x;
	//}
	//inline const fixed24p8& get_curr_in_level_pos_y() const
	//{
	//	return get_curr_in_level_pos().y;
	//}
	
	inline void set_curr_in_level_pos
		( const vec2_f24p8& n_curr_in_level_pos )
	{
		in_level_pos.curr = n_curr_in_level_pos;
	}
	inline void set_curr_in_level_pos_x
		( const fixed24p8& n_curr_in_level_pos_x )
	{
		in_level_pos.curr.x = n_curr_in_level_pos_x;
	}
	inline void set_curr_in_level_pos_y
		( const fixed24p8& n_curr_in_level_pos_y )
	{
		in_level_pos.curr.y = n_curr_in_level_pos_y;
	}
	
	inline bool get_prev_on_ground() const
	{
		return on_ground.prev;
	}
	inline bool get_curr_on_ground() const
	{
		return on_ground.curr;
	}
	
	inline void set_curr_on_ground( bool n_curr_on_ground )
	{
		on_ground.curr = n_curr_on_ground;
	}
	
	
	inline bool get_prev_on_slope() const
	{
		return on_slope.prev;
	}
	inline bool get_curr_on_slope() const
	{
		return on_slope.curr;
	}
	
	inline void set_curr_on_slope( bool n_curr_on_slope )
	{
		on_slope.curr = n_curr_on_slope;
	}
	
	
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
		
		//in_level_pos += vel;
		set_curr_in_level_pos( get_curr_in_level_pos() + vel );
		//the_coll_box.pos = in_level_pos + cb_pos_offset;
		the_coll_box.pos = get_curr_in_level_pos() + cb_pos_offset;
	}
	
	
	inline vec2_f24p8 get_on_screen_pos( const bg_point& camera_pos )
		const
	{
		//vec2_f24p8 ret = in_level_pos - camera_pos;
		//
		//return ret;
		//return in_level_pos - camera_pos;
		
		//return get_curr_in_level_pos() - camera_pos;
		
		//return vec2_f24p8( make_f24p8( get_curr_in_level_pos().x
		//	.floor_to_int() ), make_f24p8
		//	( get_curr_in_level_pos().y.floor_to_int() ) ) 
		//	- camera_pos;
		
		//return get_curr_in_level_pos() - vec2_f24p8( make_f24p8
		//	( camera_pos.x.round_to_int() ), 
		//	make_f24p8( camera_pos.y.round_to_int() ) );
		
		//return vec2_f24p8( make_f24p8(get_curr_in_level_pos().x
		//	.to_int_for_on_screen()), make_f24p8(get_curr_in_level_pos().y
		//	.to_int_for_on_screen()) )
		//	- vec2_f24p8( make_f24p8(camera_pos.x.to_int_for_on_screen()),
		//	make_f24p8(camera_pos.y.to_int_for_on_screen()) );
		
		vec2_f24p8 ret(get_curr_in_level_pos());
		
		if ( get_curr_in_level_pos().x != get_prev_in_level_pos().x )
		{
			//ret.x = get_curr_in_level_pos().x;
			ret.x -= camera_pos.x;
		}
		else //if ( get_curr_in_level_pos().x 
			//== get_prev_in_level_pos().x )
		{
			//ret.x = make_f24p8(get_curr_in_level_pos().x.floor_to_int());
			ret.x -= make_f24p8(camera_pos.x.to_int_for_on_screen());
		}
		
		if ( get_curr_in_level_pos().y != get_prev_in_level_pos().y )
		{
			//ret.y = get_curr_in_level_pos().y;
			ret.y -= camera_pos.y;
		}
		else //if ( get_curr_in_level_pos().y 
			//== get_prev_in_level_pos().y )
		{
			//ret.y = make_f24p8(get_curr_in_level_pos().y.floor_to_int());
			ret.y -= make_f24p8(camera_pos.y.to_int_for_on_screen());
		}
		
		//ret -= camera_pos;
		
		return ret;
	}
	
	void update_on_screen_pos
		( const prev_curr_pair<bg_point>& camera_pos_pc_pair );
	
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
	
	void camera_follow_basic
		( prev_curr_pair<bg_point>& camera_pos_pc_pair );
	void center_camera_almost( bg_point& camera_pos ) const;
	
	
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
	
	//void block_collision_stuff() __attribute__((_iwram_code));
	
	inline virtual const sprite_type get_const_sprite_type() const
	{
		return the_const_sprite_type;
	}
	
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
	}
	
	inline virtual void set_initial_shape_size()
	{
		set_shape_size(get_the_initial_shape_size());
	}
	inline virtual const oam_entry::shape_size get_the_initial_shape_size() 
		const
	{
		return the_initial_shape_size;
	}
	
	inline virtual void set_initial_coll_box_stuff()
	{
		the_coll_box.size = get_the_initial_coll_box_size();
		cb_pos_offset = get_the_initial_cb_pos_offset();
	}
	
	inline virtual const vec2_f24p8& get_the_initial_coll_box_size() const
	{
		return the_initial_coll_box_size;
	}
	inline virtual const vec2_f24p8& get_the_initial_cb_pos_offset() const
	{
		return the_initial_cb_pos_offset;
	}
	
	inline virtual const vec2_f24p8& get_the_initial_in_level_pos_offset()
		const
	{
		return the_initial_in_level_pos_offset;
	}
	
	
	
	//virtual void gfx_update();
	inline void gfx_update()
	{
		//the_oam_entry.set_tile_number 
		//	( get_curr_tile_slot_old() );
		
		//the_oam_entry.set_tile_number
		//	( get_vram_chunk_index() 
		//	* gfx_manager::num_tiles_in_ss_32x32 );
		the_oam_entry.set_tile_number(get_curr_tile_slot());
		
		the_oam_entry.set_pal_number(get_palette_slot());
	}
	

	// This is used for calling back_up() on some prev_curr_pair instances
	// The player_sprite class overrides this function (but still calls the
	// original) so that the player_sprite class can set warped_this_frame
	// to false.
	virtual void update_part_1() __attribute__((_iwram_code));
	
	// This used to be update_part_1()
	virtual void update_part_2();
	
	
	// update_part_3() used to be update_part_2()
	// The player_sprite class is the primary user of this function.
	virtual void update_part_3
		( prev_curr_pair<bg_point>& camera_pos_pc_pair,
		const vec2_u32& the_level_size_2d );
	
	// Sprites other than player_sprite use this function.  Some sprites
	// won't need to override this specific version.
	virtual void update_part_3
		( const prev_curr_pair<bg_point>& camera_pos_pc_pair, 
		int& next_oam_index );
	
	
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot_old();
	
	inline const u32 get_curr_tile_slot()
	{
		return get_vram_chunk_index() 
			* gfx_manager::num_tiles_in_ss_32x32;
	}
	
	virtual const sprite_palette_slot get_palette_slot();
	virtual const u32 get_curr_relative_tile_slot();
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	
	// Physics and collision stuff
	virtual void block_collision_stuff();
	
	virtual void apply_gravity();
	virtual void handle_jumping_stuff( u32 is_jump_key_hit, 
		u32 is_jump_key_held );
	
	
	// Sprite-sprite interaction stuff
	virtual void sprite_interaction_reponse( sprite& the_other_sprite );
	
	// the_player is the primary user of this function
	virtual void sprite_interaction_reponse( sprite& the_other_sprite, 
		prev_curr_pair<bg_point>& camera_pos_pc_pair, 
		const vec2_u32& the_level_size_2d );
	
	
protected:		// functions
	vec2_u32 get_shape_size_as_vec2_raw() const;
	
	// Here are a lot of block collision functions.  It is recommended that
	// they be stored in IWRAM for as much speed as possible.
	void get_basic_block_coll_results_16x16
		( coll_point_group_16x16& the_pt_group, 
		block_coll_result& lt_coll_result,
		block_coll_result& lb_coll_result,
		block_coll_result& tl_coll_result,
		block_coll_result& tm_coll_result,
		block_coll_result& tr_coll_result,
		block_coll_result& rt_coll_result,
		block_coll_result& rb_coll_result,
		block_coll_result& bl_coll_result,
		block_coll_result& bm_coll_result,
		block_coll_result& br_coll_result );
	
	void get_basic_block_coll_results_16x32
		( coll_point_group_16x32& the_pt_group, 
		block_coll_result& lt_coll_result, 
		block_coll_result& lm_coll_result,
		block_coll_result& lb_coll_result,
		block_coll_result& tl_coll_result, 
		block_coll_result& tm_coll_result,
		block_coll_result& tr_coll_result,
		block_coll_result& rt_coll_result,
		block_coll_result& rm_coll_result,
		block_coll_result& rb_coll_result,
		block_coll_result& bl_coll_result, 
		block_coll_result& bm_coll_result,
		block_coll_result& br_coll_result );
	
	
	
	virtual void block_coll_response_left_16x16_old
		( const block_coll_result& lt_coll_result, 
		const block_coll_result& lb_coll_result );
	virtual void block_coll_response_top_16x16_old
		( const block_coll_result& tl_coll_result,
		const block_coll_result& tm_coll_result,
		const block_coll_result& tr_coll_result );
	virtual void block_coll_response_right_16x16_old
		( const block_coll_result& rt_coll_result,
		const block_coll_result& rb_coll_result );
	virtual void non_slope_block_coll_response_bot_16x16_old
		( const block_coll_result& bl_coll_result,
		const block_coll_result& bm_coll_result, 
		const block_coll_result& br_coll_result );
	virtual block_type slope_block_coll_response_bot_16x16_old
		( coll_point_group_16x16& the_pt_group,
		block_coll_result& bl_coll_result,
		block_coll_result& bm_coll_result,
		block_coll_result& br_coll_result, bool hitting_tltr=false );
	
	virtual void block_coll_response_left_16x32_old
		( const block_coll_result& lt_coll_result,
		const block_coll_result& lm_coll_result, 
		const block_coll_result& lb_coll_result );
	virtual void block_coll_response_top_16x32_old
		( const block_coll_result& tl_coll_result,
		const block_coll_result& tm_coll_result, 
		const block_coll_result& tr_coll_result );
	virtual void block_coll_response_right_16x32_old
		( const block_coll_result& rt_coll_result,
		const block_coll_result& rm_coll_result, 
		const block_coll_result& rb_coll_result );
	virtual void non_slope_block_coll_response_bot_16x32_old
		( const block_coll_result& bl_coll_result,
		const block_coll_result& bm_coll_result, 
		const block_coll_result& br_coll_result );
	virtual block_type slope_block_coll_response_bot_16x32_old
		( coll_point_group_16x32& the_pt_group,
		block_coll_result& bl_coll_result,
		block_coll_result& bm_coll_result,
		block_coll_result& br_coll_result, bool hitting_tltr=false );
	
	
	virtual void block_coll_response_left_16x16
		( const block_coll_result_rect_group& the_bcr_rect_group );
	virtual void block_coll_response_right_16x16
		( const block_coll_result_rect_group& the_bcr_rect_group );
	virtual void block_coll_response_top_16x16
		( const block_coll_result_rect_group& the_bcr_rect_group );
	virtual void block_coll_response_bot_16x16
		( const block_coll_result_rect_group& the_bcr_rect_group );
	
	
	virtual void block_coll_response_left_16x32
		( const block_coll_result_rect_group& the_bcr_rect_group );
	virtual void block_coll_response_right_16x32
		( const block_coll_result_rect_group& the_bcr_rect_group );
	virtual void block_coll_response_top_16x32
		( const block_coll_result_rect_group& the_bcr_rect_group );
	virtual void block_coll_response_bot_16x32
		( const block_coll_result_rect_group& the_bcr_rect_group );
	
	
	
	// Finally, some inline functions (probably) every sprite can use in
	// their block_coll_response.*() functions
	inline void push_out_of_left_block
		( const block_coll_result_rect_group& the_bcr_rect_group )
	{
		set_curr_in_level_pos_x( make_f24p8( ( the_bcr_rect_group.left() 
			+ 1 ) * num_pixels_per_block_dim ) - cb_pos_offset.x );
	}
	inline void push_out_of_right_block
		( const block_coll_result_rect_group& the_bcr_rect_group )
	{
		set_curr_in_level_pos_x( make_f24p8( the_bcr_rect_group.right()
			* num_pixels_per_block_dim ) - the_coll_box.size.x 
			- cb_pos_offset.x );
	}
	inline void push_out_of_top_block
		( const block_coll_result_rect_group& the_bcr_rect_group )
	{
		set_curr_in_level_pos_y( make_f24p8( ( the_bcr_rect_group.top() 
			+ 1 ) * num_pixels_per_block_dim ) - cb_pos_offset.y );
	}
	inline void push_out_of_bot_block
		( const block_coll_result_rect_group& the_bcr_rect_group )
	{
		set_curr_in_level_pos_y( make_f24p8( the_bcr_rect_group.bot()
			* num_pixels_per_block_dim ) 
			- make_f24p8(get_shape_size_as_vec2().y) );
	}
	
	
	// Regular block collision stuff
	virtual void block_collision_stuff_16x16_old();
	virtual void block_collision_stuff_16x32_old();
	virtual void block_collision_stuff_32x16_old();
	virtual void block_collision_stuff_32x32_old();
	
	virtual void block_collision_stuff_16x16()
		__attribute__((_iwram_code));
	virtual void block_collision_stuff_16x32()
		__attribute__((_iwram_code));
	virtual void block_collision_stuff_32x16()
		__attribute__((_iwram_code));
	virtual void block_collision_stuff_32x32()
		__attribute__((_iwram_code));
	
	// Block collision stuff with just strongly hit response 
	//virtual void block_collision_stuff_strongly_hit_stuff_only_16x16();
	//virtual void block_collision_stuff_strongly_hit_stuff_only_16x32();
	//virtual void block_collision_stuff_strongly_hit_stuff_only_32x16();
	//virtual void block_collision_stuff_strongly_hit_stuff_only_32x32();
	
} __attribute__((_align4));



#endif		// sprite_class_hpp
