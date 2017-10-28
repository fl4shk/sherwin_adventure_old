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
#include "../spr_blk_coll_group_classes.hpp"

class SpriteAllocator;

extern const size_t clseg_grp_16x32_size;

// Not all of these parameters are used by every type of Sprite
class SpriteConstParams
{
public:		// variables
	sprite_type the_const_sprite_type = StDefault;
	sprite_palette_slot the_palette_slot = sps_player;
	u32 the_relative_metatile_slot = 0, 
		num_active_gfx_tiles = GfxManager::num_tiles_in_ss_16x16;
	Tile* tile_arr = const_cast<Tile*>(reinterpret_cast<const Tile*>
		(sherwin_gfxTiles));
	OamEntry::shape_size the_initial_shape_size = OamEntry::ss_16x16;
	Vec2F24p8 the_initial_coll_box_size = { {14 << Fixed24p8::get_shift()}, 
		{14 << Fixed24p8::get_shift()} };

	Vec2F24p8 the_initial_cb_pos_offset = { {1 << Fixed24p8::get_shift()}, 
		{1 << Fixed24p8::get_shift()} };


	// This Is used To correct the initial in-Level position for sprites
	// That are normally considered To be of a certain size but That use
	// larger graphics for some frames.  An example of this Is the
	// StPlayer sprite_type, which Is normally considered To be a 16x32
	// Sprite but uses 32x32 graphics in some cases, like during the
	// pickaxe swing animation.
	Vec2F24p8 the_initial_in_level_pos_offset
		= { {0 << Fixed24p8::get_shift()}, {0 << Fixed24p8::get_shift()} };
} __attribute__((_align4));

////
//class SpriteVolatileMembers
//{
//public:		// variables
//
//} __attribute__((_align4));

//class SpritePhysicsMembers
//{
//public:		// variables
//
//} __attribute__((_align4));

class SprBlkCollGroupBase;
//class SprBlkCollGroupBase::HorizCollTuple;

class Sprite
{
protected:		// variables
	// These are protected variables because they're not normally supposed
	// To change after initialization.
	Vec2u32 the_shape_size_vec2;
	OamEntry::shape_size the_shape_size;

	// Which 32x32 VRAM chunk this Sprite uses, which Is equal To the
	// actual VRAM address divided by
	// GfxManager::num_tiles_in_ss_32x32.  There are a few SPECIAL
	// cases where vram_chunk_index would need To be changed, So
	// set_vram_chunk_index() Exists.
	u32 vram_chunk_index;

	// These two things are used for FAST Sprite allocation via a
	// SaFreeListBackend member variable in a SpriteAllocator instance.
	int the_arr_index;
	friend class SpriteAllocator;

public:		// constants

	static const Fixed24p8 cpg_on_slope_threshold_abs;

	// coll_point_group threshold
	static const Vec2F24p8 cpg_16x32_threshold_abs;

	static const Fixed24p8 grav_acc;
	static const Fixed24p8 max_y_vel;

	static const SpriteConstParams the_const_params;

	//static const sprite_type the_const_sprite_type;
	//static const sprite_palette_slot the_palette_slot;
	//
	//static const u32 the_relative_metatile_slot,
	//	num_active_gfx_tiles;
	//static const Tile* tile_arr;
	//static const OamEntry::shape_size the_initial_shape_size;
	//
	//static const Vec2F24p8 the_initial_coll_box_size,
	//	the_initial_cb_pos_offset;
	//
	//static const Vec2F24p8 the_initial_in_level_pos_offset;

public:		// variables

	// General data

	// The type of Sprite.
	sprite_type the_sprite_type;

	// the_sprite_ipg Is a pointer To the Level data of this Sprite.  Even
	// though the_sprite_ipg Contains an initial sprite_type, it Is
	// normally the case That sprite_init_param_groups are stored in ROM,
	// So attempting To change the_sprite_ipg->type would not work for the
	// purposes of changing the sprite_type of sprites in different slots.
	SpriteInitParamGroup* the_sprite_ipg;

	// Here Is one of the most essential member variables:  an OamEntry To
	// be copied To oam_mirror.
	OamEntry the_oam_entry;




	// Physics and collision and stuff

	// in_level_pos Is the "global" position of the Sprite within the
	// current Level, connected To the top left corner.
	PrevCurrPair<Vec2F24p8> in_level_pos;

	// vel Is the velocity of the Sprite.
	Vec2F24p8 vel;

	// The absolute value of the maximum horizontal velocity of the Sprite
	Fixed24p8 max_vel_x_abs_val;

	// The horizontal acceleration of the Sprite
	Fixed24p8 accel_x;



	// the_coll_box's "pos" member variable Is the in-Level
	// coordinate of the_coll_box.  Also, the_coll_box Is
	// only used for non-oriented sprites.
	CollBox the_coll_box;

	// cb_pos_offset Is the position of the CollBox relative To
	// in_level_pos.  It Is used because most sprites will have a CollBox
	// with a size other than the visible 
	Vec2F24p8 cb_pos_offset;

	// on_ground Is a flag That tells whether the Sprite Is on the ground,
	// though That's really obvious.
	PrevCurrPair<bool> on_ground;


	//// jump_hold_timer Is used To keep track of for how much longer the
	//// Sprite Can jump, if the Sprite even does So.  This coul
	//s32 jump_hold_timer;

	bool is_jumping;


	PrevCurrPair<bool> on_slope;

	// Invincibility frames timer, enabled after taking damage.
	s32 invin_frame_timer;



	// Two arrays of miscellaneous Sprite data.  The way these arrays are
	// used varies by the type of Sprite.  Also, since a more natural
	// Sprite type system Is going To be used, they could be gotten rid of
	// and replaced with variables That only 
	static constexpr u32 misc_data_size = 8;
	u32 misc_data_u[misc_data_size];
	s32 misc_data_s[misc_data_size];


	// These are mainly for debugging.
	//bool did_update_prev_on_screen_pos_this_frame;
	//Vec2F24p8 prev_on_screen_pos, curr_on_screen_pos;
	//PrevCurrPair<Vec2F24p8> on_screen_pos;
	//PrevCurrPair<Vec2s32> on_screen_pos_s32;

	static Vec2F24p8 prev_prev_on_screen_pos; 
	static PrevCurrPair<Vec2F24p8> on_screen_pos;
	static Vec2s32 prev_prev_on_screen_pos_s32;
	static PrevCurrPair<Vec2s32> on_screen_pos_s32;
	static PrevCurrPair<Vec2s32> camera_pos_pc_pair_s32;

	static Vec2<bool> temp_debug_thing;

	static Vec2F24p8 on_screen_pos_diff_abs;
	static Vec2s32 on_screen_pos_s32_diff_abs;
	static Vec2F24p8 camera_pos_diff_abs;
	static Vec2s32 camera_pos_s32_diff_abs;

	//static PrevCurrPair<s32> height_val;

public:		// functions

	Sprite();
	Sprite(bool facing_left);
	Sprite(const Vec2F24p8& s_in_level_pos, 
		const PrevCurrPair<BgPoint>& camera_pos_pc_pair, 
		bool facing_left);
	Sprite(const Vec2F24p8& s_in_level_pos, 
		const Vec2u32& the_level_size_2d, 
		PrevCurrPair<BgPoint>& camera_pos_pc_pair, bool facing_left);


	inline Sprite(u32 s_vram_chunk_index)
	{
		Sprite();

		vram_chunk_index = s_vram_chunk_index;
	}


	// This function Is NOT virtual because because it uses virtual
	// functions.
	void shared_constructor_code_part_1();


	// Derived classes should override this function
	// This Is the default form of shared_constructor_code().
	virtual void shared_constructor_code_part_2(bool facing_left);

	// This form of shared_constructor_code() might eventually become the
	// default form of shared_constructor_code().
	virtual void shared_constructor_code_part_2
		(const Vec2F24p8& s_in_level_pos, 
		const PrevCurrPair<BgPoint>& camera_pos_pc_pair, 
		bool facing_left);

	// This form of shared_constructor_code() Is primarily Intended To be
	// used by the_player.
	virtual void shared_constructor_code_part_2
		(const Vec2F24p8& s_in_level_pos, 
		const Vec2u32& the_level_size_2d, 
		PrevCurrPair<BgPoint>& camera_pos_pc_pair, bool facing_left);

	virtual void shared_constructor_code_part_3();

	void* operator new(size_t size, 
		SpriteAllocator& the_sprite_allocator)
		__attribute__((_iwram_code));

	//void operator delete(void* the_sprite, 
	//	SpriteAllocator& the_sprite_allocator);


	inline const Vec2F24p8& get_prev_in_level_pos() const
	{
		return in_level_pos.prev;
	}
	//inline const Fixed24p8& get_prev_in_level_pos_x() const
	//{
	//	return get_prev_in_level_pos().x;
	//}
	//inline const Fixed24p8& get_prev_in_level_pos_y() const
	//{
	//	return get_prev_in_level_pos().y;
	//}

	inline const Vec2F24p8& get_curr_in_level_pos() const
	{
		return in_level_pos.curr;
	}
	//inline const Fixed24p8& get_curr_in_level_pos_x() const
	//{
	//	return get_curr_in_level_pos().x;
	//}
	//inline const Fixed24p8& get_curr_in_level_pos_y() const
	//{
	//	return get_curr_in_level_pos().y;
	//}

	inline void set_curr_in_level_pos
		(const Vec2F24p8& n_curr_in_level_pos)
	{
		in_level_pos.curr = n_curr_in_level_pos;
	}
	inline void set_curr_in_level_pos_x
		(const Fixed24p8& n_curr_in_level_pos_x)
	{
		in_level_pos.curr.x = n_curr_in_level_pos_x;
	}
	inline void set_curr_in_level_pos_y
		(const Fixed24p8& n_curr_in_level_pos_y)
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

	inline void set_curr_on_ground(bool n_curr_on_ground)
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

	inline void set_curr_on_slope(bool n_curr_on_slope)
	{
		on_slope.curr = n_curr_on_slope;
	}


	inline OamEntry::shape_size get_shape_size() const
	{
		return the_shape_size;
	}
	inline const Vec2u32& get_shape_size_as_vec2() const
	{
		return the_shape_size_vec2;
	}
	inline u32 get_vram_chunk_index() const
	{
		return vram_chunk_index;
	}
	inline void set_vram_chunk_index(u32 n_vram_chunk_index)
	{
		vram_chunk_index = n_vram_chunk_index;
	}

	inline void set_shape_size(OamEntry::shape_size n_shape_size)
	{
		the_shape_size = n_shape_size;
		the_oam_entry.set_shape_size(n_shape_size);
		the_shape_size_vec2 = get_shape_size_as_vec2_raw();
	}

	inline void update_f24p8_positions()
	{
		vel.x += accel_x;

		if (max_vel_x_abs_val != (Fixed24p8){0})
		{
			if (vel.x > max_vel_x_abs_val)
			{
				vel.x = max_vel_x_abs_val;
			}
			else if (vel.x < -max_vel_x_abs_val)
			{
				vel.x = -max_vel_x_abs_val;
			}
		}

		//in_level_pos += vel;
		set_curr_in_level_pos(get_curr_in_level_pos() + vel);
		//the_coll_box.pos = in_level_pos + cb_pos_offset;
		the_coll_box.pos = get_curr_in_level_pos() + cb_pos_offset;
	}


	inline Vec2F24p8 get_on_screen_pos(const BgPoint& camera_pos)
		const
	{
		//Vec2F24p8 ret = in_level_pos - camera_pos;
		//
		//return ret;
		//return in_level_pos - camera_pos;

		//return get_curr_in_level_pos() - camera_pos;

		//return Vec2F24p8(make_f24p8(get_curr_in_level_pos().x
		//	.floor_to_int()), make_f24p8
		//	(get_curr_in_level_pos().y.floor_to_int())) 
		//	- camera_pos;

		//return get_curr_in_level_pos() - Vec2F24p8(make_f24p8
		//	(camera_pos.x.round_to_int()), 
		//	make_f24p8(camera_pos.y.round_to_int()));

		//return Vec2F24p8(make_f24p8(get_curr_in_level_pos().x
		//	.to_int_for_on_screen()), make_f24p8(get_curr_in_level_pos().y
		//	.to_int_for_on_screen()))
		//	- Vec2F24p8(make_f24p8(camera_pos.x.to_int_for_on_screen()),
		//	make_f24p8(camera_pos.y.to_int_for_on_screen()));

		Vec2F24p8 ret(get_curr_in_level_pos());

		if (get_curr_in_level_pos().x != get_prev_in_level_pos().x)
		{
			//ret.x = get_curr_in_level_pos().x;
			ret.x -= camera_pos.x;
		}
		else //if (get_curr_in_level_pos().x 
			//== get_prev_in_level_pos().x)
		{
			//ret.x = make_f24p8(get_curr_in_level_pos().x.floor_to_int());
			ret.x -= make_f24p8(camera_pos.x.to_int_for_on_screen());
		}

		if (get_curr_in_level_pos().y != get_prev_in_level_pos().y)
		{
			//ret.y = get_curr_in_level_pos().y;
			ret.y -= camera_pos.y;
		}
		else //if (get_curr_in_level_pos().y 
			//== get_prev_in_level_pos().y)
		{
			//ret.y = make_f24p8(get_curr_in_level_pos().y.floor_to_int());
			ret.y -= make_f24p8(camera_pos.y.to_int_for_on_screen());
		}

		//ret -= camera_pos;

		return ret;
	}

	void update_on_screen_pos
		(const PrevCurrPair<BgPoint>& camera_pos_pc_pair);

	//inline void update_full(const BgPoint& camera_pos)
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
		(PrevCurrPair<BgPoint>& camera_pos_pc_pair);
	void center_camera_almost(BgPoint& camera_pos) const;


	//inline void copy_the_oam_entry_to_oam_mirror 
	//	(u32 slot_for_oam_mirror)
	//{
	//	oam_mirror[slot_for_oam_mirror].attr0 = the_oam_entry.attr0;
	//	oam_mirror[slot_for_oam_mirror].attr1 = the_oam_entry.attr1;
	//	oam_mirror[slot_for_oam_mirror].attr2 = the_oam_entry.attr2;
	//}

	//void copy_the_oam_entry_to_oam_mirror(u32 slot_for_oam_mirror)
	//	__attribute__((_iwram_code));

	inline void copy_the_oam_entry_to_oam_mirror(u32 slot_for_oam_mirror)
	{
		oam_mirror[slot_for_oam_mirror].attr0 = the_oam_entry.attr0;
		oam_mirror[slot_for_oam_mirror].attr1 = the_oam_entry.attr1;
		oam_mirror[slot_for_oam_mirror].attr2 = the_oam_entry.attr2;
	}

	//void block_collision_stuff() __attribute__((_iwram_code));

	inline virtual const SpriteConstParams& get_const_params() const
	{
		return the_const_params;
	}

	inline virtual const sprite_type get_const_sprite_type() const
	{
		return get_const_params().the_const_sprite_type;
	}

	inline virtual const Tile* get_tile_arr() const
	{
		return get_const_params().tile_arr;
	}

	inline virtual void set_initial_shape_size()
	{
		set_shape_size(get_initial_shape_size());
	}
	inline virtual const OamEntry::shape_size get_initial_shape_size() 
		const
	{
		return get_const_params().the_initial_shape_size;
	}

	inline virtual void set_initial_coll_box_stuff()
	{
		the_coll_box.size = get_initial_coll_box_size();
		cb_pos_offset = get_initial_cb_pos_offset();
	}

	inline virtual const Vec2F24p8& get_initial_coll_box_size() const
	{
		return get_const_params().the_initial_coll_box_size;
	}
	inline virtual const Vec2F24p8& get_initial_cb_pos_offset() const
	{
		return get_const_params().the_initial_cb_pos_offset;
	}

	inline virtual const Vec2F24p8& get_initial_in_level_pos_offset()
		const
	{
		return get_const_params().the_initial_in_level_pos_offset;
	}



	//virtual void gfx_update();
	inline void gfx_update()
	{
		//the_oam_entry.set_tile_number 
		//	(get_curr_tile_slot_old());

		//the_oam_entry.set_tile_number
		//	(get_vram_chunk_index() 
		//	* GfxManager::num_tiles_in_ss_32x32);
		the_oam_entry.set_tile_number(get_curr_tile_slot());

		the_oam_entry.set_pal_number(get_palette_slot());
	}


	// This Is used for calling back_up() on some PrevCurrPair instances
	// The PlayerSprite class Overrides this function (but still calls the
	// original) So That the PlayerSprite class Can set warped_this_frame
	// To false.
	virtual void update_part_1() __attribute__((_iwram_code));

	// This used To be update_part_1()
	virtual void update_part_2();


	// update_part_3() used To be update_part_2()
	// The PlayerSprite class Is the primary user of this function.
	virtual void update_part_3
		(PrevCurrPair<BgPoint>& camera_pos_pc_pair,
		const Vec2u32& the_level_size_2d);

	// Sprites other than PlayerSprite use this function.  Some sprites
	// won't need To override this specific version.
	virtual void update_part_3
		(const PrevCurrPair<BgPoint>& camera_pos_pc_pair, 
		int& next_oam_index);




	// Graphics stuff
	//virtual const u32 get_curr_tile_slot_old();

	inline const u32 get_curr_tile_slot()
	{
		return get_vram_chunk_index() 
			* GfxManager::num_tiles_in_ss_32x32;
	}

	virtual const sprite_palette_slot get_palette_slot();
	virtual const u32 get_curr_relative_tile_slot();
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return get_const_params().num_active_gfx_tiles;
	}

	// Physics and collision stuff
	virtual void block_collision_stuff();

	virtual void apply_gravity();
	virtual void handle_jumping_stuff(u32 is_jump_key_hit, 
		u32 is_jump_key_held);


	// Sprite-Sprite interaction stuff
	virtual void sprite_interaction_reponse(Sprite& the_other_sprite);

	// the_player Is the primary user of this function
	virtual void sprite_interaction_reponse(Sprite& the_other_sprite, 
		PrevCurrPair<BgPoint>& camera_pos_pc_pair, 
		const Vec2u32& the_level_size_2d);


protected:		// functions
	Vec2u32 get_shape_size_as_vec2_raw() const;


	//virtual void block_coll_response_left
	//	(const BcrLsegGroup& the_bcr_lseg_grp);
	//virtual void block_coll_response_right
	//	(const BcrLsegGroup& the_bcr_lseg_grp);
	virtual void block_coll_response_left
		(const SprBlkCollGroupBase::HorizCollTuple& hs);
	virtual void block_coll_response_right
		(const SprBlkCollGroupBase::HorizCollTuple& hs);
	virtual void block_coll_response_top
		(const SprBlkCollGroupBase::VertTopCollTuple& vs);
	virtual void block_coll_response_bot
		(const BcrLsegGroup& the_bcr_lseg_grp);
	virtual void block_coll_response_bot_slope(s32 height_val, 
		s32 blk_crd_y_pos);



	// Finally, some inline functions (probably) every Sprite Can use in
	// their block_coll_response.*() functions
	//inline void push_out_of_left_block
	//	(const BcrLsegGroup& the_bcr_lseg_grp)
	//{
	//	set_curr_in_level_pos_x(make_f24p8
	//		(conv_blk_crd_to_pix_crd(the_bcr_lseg_grp.horiz_left_pos() 
	//		+ 1)) - cb_pos_offset.x);
	//}
	//inline void push_out_of_right_block
	//	(const BcrLsegGroup& the_bcr_lseg_grp)
	//{
	//	set_curr_in_level_pos_x(make_f24p8
	//		(conv_blk_crd_to_pix_crd(the_bcr_lseg_grp.horiz_right_pos()))
	//		- the_coll_box.size.x - cb_pos_offset.x);
	//}
	inline void push_out_of_left_block
		(const Vec2s32& blk_crd_pos)
	{
		set_curr_in_level_pos_x(make_f24p8(conv_blk_crd_to_pix_crd
			(blk_crd_pos.x + 1)) - cb_pos_offset.x);
	}
	inline void push_out_of_right_block
		(const Vec2s32& blk_crd_pos)
	{
		set_curr_in_level_pos_x(make_f24p8(conv_blk_crd_to_pix_crd
			(blk_crd_pos.x)) - the_coll_box.size.x - cb_pos_offset.x);
	}
	inline void push_out_of_top_block
		(const Vec2s32& blk_crd_pos)
	{
		set_curr_in_level_pos_y(make_f24p8(conv_blk_crd_to_pix_crd
			(blk_crd_pos.y + 1) + 1) - cb_pos_offset.y);
	}
	inline void push_out_of_bot_block
		(const BcrLsegGroup& the_bcr_lseg_grp)
	{
		set_curr_in_level_pos_y(make_f24p8
			(conv_blk_crd_to_pix_crd(the_bcr_lseg_grp.vert_bot_pos()))
			- make_f24p8(get_shape_size_as_vec2().y));
	}
	inline void push_out_of_bot_slope_block(s32 height_val, 
		s32 blk_crd_y_pos)
	{
		set_curr_in_level_pos_y(make_f24p8
			((conv_blk_crd_to_pix_crd(blk_crd_y_pos)
			+ conv_slp_height_val_to_offset(height_val)))
			- make_f24p8(get_shape_size_as_vec2().y));
	}


	// Regular Block collision stuff
	virtual void generic_block_collision_stuff
		(SprBlkCollGroupBase& clseg_grp)
		__attribute__((_iwram_code,_target_arm));
	virtual void block_collision_stuff_16x16();
	virtual void block_collision_stuff_16x32();

	// block_collision_stuff_32x16() will likely never be used because it's
	// less believable for one of those To not rotate when on a slope
	virtual void block_collision_stuff_32x16();
	virtual void block_collision_stuff_32x32();

	// Block collision stuff with just strongly hit response 
	//virtual void block_collision_stuff_strongly_hit_stuff_only_16x16();
	//virtual void block_collision_stuff_strongly_hit_stuff_only_16x32();
	//virtual void block_collision_stuff_strongly_hit_stuff_only_32x16();
	//virtual void block_collision_stuff_strongly_hit_stuff_only_32x32();

} __attribute__((_align4));



#endif		// sprite_class_hpp
