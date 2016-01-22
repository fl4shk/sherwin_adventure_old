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


#ifndef player_sprite_stuff_class_hpp
#define player_sprite_stuff_class_hpp

#include "../gfx_manager_class.hpp"

#include "../../gfx/sherwin_gfx.h"

class player_sprite_stuff : public sprite_base_stuff
{
public:		// enums
	// "Global" graphics frames
	enum frame
	{
		// Not a real frame, just a way to hide the player
		frm_invisible, 
		
		// Standing frame
		frm_stand, 
		
		// Walking frames
		frm_walk_0, 
		frm_walk_1,
		
		// Weapon swinging frames, on the ground, while not moving
		frm_weapon_swing_ground_still_0,
		frm_weapon_swing_ground_still_1,
		frm_weapon_swing_ground_still_2,
		frm_weapon_swing_ground_still_3,
		frm_weapon_swing_ground_still_4,
		frm_weapon_swing_ground_still_5,
		
		// Two taller weapon swinging frames, which could be used as part
		// of item throwing animations instead of
		// frm_weapon_swing_ground_still_4 and
		// frm_weapon_swing_ground_still_5.
		frm_weapon_swing_ground_still_4_tall,
		frm_weapon_swing_ground_still_5_tall,
		
		// Weapon swinging frames, on the ground, but also moving, row 0
		frm_weapon_swing_ground_moving_0_row_0,
		frm_weapon_swing_ground_moving_1_row_0,
		frm_weapon_swing_ground_moving_2_row_0,
		frm_weapon_swing_ground_moving_3_row_0,
		frm_weapon_swing_ground_moving_4_row_0,
		frm_weapon_swing_ground_moving_5_row_0,
		
		// Weapon swinging frames, on the ground, but also moving, row 1
		frm_weapon_swing_ground_moving_0_row_1,
		frm_weapon_swing_ground_moving_1_row_1,
		frm_weapon_swing_ground_moving_2_row_1,
		frm_weapon_swing_ground_moving_3_row_1,
		frm_weapon_swing_ground_moving_4_row_1,
		frm_weapon_swing_ground_moving_5_row_1,
		
		// Weapon swinging frames, on the ground, but also moving, row 2
		frm_weapon_swing_ground_moving_0_row_2,
		frm_weapon_swing_ground_moving_1_row_2,
		frm_weapon_swing_ground_moving_2_row_2,
		frm_weapon_swing_ground_moving_3_row_2,
		frm_weapon_swing_ground_moving_4_row_2,
		frm_weapon_swing_ground_moving_5_row_2,
		
		
	} __attribute__((_align4));
	
	// This enum allows multiple frame_slot's to be represented by the same
	// frame, which is used, for example, in the walking animation.  Also,
	// the reason this is necessary is that so which frame is currently
	// active can be determined.  If two frames in the enum share a value,
	// it is impossible to tell where in the walk cycle the player's
	// animation is.
	enum frame_slot 
	{ 
		// Invisible
		frm_slot_invisible, 
		
		// Standing
		frm_slot_stand,
		
		// Walking/running 
		frm_slot_walk_0,
		frm_slot_walk_1, 
		frm_slot_walk_2, 
		frm_slot_walk_3,
		
		// Swinging a weapon, on the ground, while not moving
		frm_slot_weapon_swing_ground_still_0,
		frm_slot_weapon_swing_ground_still_1,
		frm_slot_weapon_swing_ground_still_2,
		frm_slot_weapon_swing_ground_still_3,
		frm_slot_weapon_swing_ground_still_4,
		frm_slot_weapon_swing_ground_still_5,
		
		// Two taller weapon swinging frames, which could be used as part
		// of item throwing animations instead of
		// frm_slot_weapon_swing_ground_still_4 and
		// frm_slot_weapon_swing_ground_still_5.
		frm_slot_weapon_swing_ground_still_4_tall,
		frm_slot_weapon_swing_ground_still_5_tall,
		
		// Swinging a weapon, on the ground, but also moving, row 0
		frm_slot_weapon_swing_ground_moving_0_row_0,
		frm_slot_weapon_swing_ground_moving_1_row_0,
		frm_slot_weapon_swing_ground_moving_2_row_0,
		frm_slot_weapon_swing_ground_moving_3_row_0,
		frm_slot_weapon_swing_ground_moving_4_row_0,
		frm_slot_weapon_swing_ground_moving_5_row_0,
		
		// Swinging a weapon, on the ground, but also moving, row 1
		frm_slot_weapon_swing_ground_moving_0_row_1,
		frm_slot_weapon_swing_ground_moving_1_row_1,
		frm_slot_weapon_swing_ground_moving_2_row_1,
		frm_slot_weapon_swing_ground_moving_3_row_1,
		frm_slot_weapon_swing_ground_moving_4_row_1,
		frm_slot_weapon_swing_ground_moving_5_row_1,
		
		// Swinging a weapon, on the ground, but also moving, row 2
		frm_slot_weapon_swing_ground_moving_0_row_2,
		frm_slot_weapon_swing_ground_moving_1_row_2,
		frm_slot_weapon_swing_ground_moving_2_row_2,
		frm_slot_weapon_swing_ground_moving_3_row_2,
		frm_slot_weapon_swing_ground_moving_4_row_2,
		frm_slot_weapon_swing_ground_moving_5_row_2,
		
		// Swinging a weapon, in the air (uses the same graphics as the
		// ones for weapon swing, on the ground, but also moving, row 2).
		frm_slot_weapon_swing_air_0,
		frm_slot_weapon_swing_air_1,
		frm_slot_weapon_swing_air_2,
		frm_slot_weapon_swing_air_3,
		frm_slot_weapon_swing_air_4,
		frm_slot_weapon_swing_air_5,
		
		// frm_slot_count is the amount of frame_slot's.  It is
		// automatically updated by the compiler.
		frm_slot_count,
		
	} __attribute__((_align4));
	
	
	// These are used to access misc_data_u and misc_data_s
	enum udata_index { udi_active_walk_frame_slot, 
		udi_active_pickaxe_swing_frame_slot } __attribute__((_align4));
	enum sdata_index { sdi_walk_frame_timer, sdi_pickaxe_swing_frame_timer } 
		__attribute__((_align4));
	
	
public:		// variables
	// Static variables
	
	static fixed24p8 speed __attribute__((_iwram));
	static bool use_16x16 __attribute__((_iwram));
	static bool run_toggle __attribute__((_iwram));
	
	static s32 max_hp __attribute__((_iwram));
	static s32 remaining_hp __attribute__((_iwram));
	
	// Hammer stuff
	static bool swinging_pickaxe __attribute__((_iwram));
	static u32 pickaxe_sprite_slot __attribute__((_iwram));
	
	
	
	
	// Physics/logic constants
	//static constexpr fixed24p8 jump_vel = {-0x400};
	static constexpr fixed24p8 jump_vel = {-0x300};
	//static constexpr s32 max_jump_hold_timer = 16;
	//static constexpr s32 max_jump_hold_timer = 20;
	static constexpr s32 max_jump_hold_timer = 24;
	static constexpr s32 walk_frame_timer_end = 4;
	static constexpr s32 run_frame_timer_end = 2;
	
	//static constexpr s32 pickaxe_swing_frame_timer_end = 4;
	//static constexpr s32 pickaxe_swing_frame_timer_end = 2;
	static constexpr s32 pickaxe_swing_start_frame_timer_end = 8;
	static constexpr s32 pickaxe_swing_frame_timer_end = 1;
	static constexpr s32 pickaxe_swing_final_frame_timer_end = 8;
	
	static constexpr fixed24p8 walk_speed = {0x100};
	static constexpr fixed24p8 max_run_speed = {0x200};
	
	// Graphics constants
	
	// A constant array that is intended to be indexed with a frame_slot,
	// such that a frame_slot can be mapped to a frame. 
	static constexpr u32 frame_slot_to_frame_arr_size = frm_slot_count;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
	
	static constexpr sprite_type the_sprite_type = st_player;
	static constexpr sprite_palette_slot the_palette_slot = sps_player;
	
	static constexpr u32 num_active_gfx_tiles 
		= gfx_manager::num_tiles_in_ss_16x32;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(sherwin_gfxTiles));
	
	static const oam_entry::shape_size the_initial_shape_size 
		= oam_entry::ss_16x32;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
	// This is used to correct the initial in-level position for sprites
	// that are normally considered to be of a certain size but that use
	// larger graphics for some frames.
	static const vec2_f24p8 the_initial_in_level_pos_offset;
	
	
public:		// functions
	virtual void init( sprite& the_player, bool facing_left=true );
	virtual void init( sprite& the_player, 
		const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, bg_point& camera_pos,
		bool facing_left=true );
	
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	//virtual void gfx_update( sprite& the_player );
	virtual void update_part_1( sprite& the_player );
	virtual void update_part_2( sprite& the_player, bg_point& camera_pos,
		const vec2_u32& the_level_size_2d );
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot( sprite& the_player );
	
	inline virtual const sprite_palette_slot get_palette_slot 
		( sprite& the_player )
	{
		return the_palette_slot;
	}
	virtual const u32 get_curr_relative_tile_slot( sprite& the_player );
	
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
	
	inline virtual const vec2_f24p8& get_the_initial_in_level_pos_offset()
		const
	{
		return the_initial_in_level_pos_offset;
	}
	
	
	// Physics and collision stuff
	virtual void block_collision_stuff( sprite& the_player )
		__attribute__((_iwram_code));
	
	virtual void block_coll_response_top_16x16( sprite& the_player, 
		const block_coll_result& tl_coll_result, 
		const block_coll_result& tm_coll_result,
		const block_coll_result& tr_coll_result )
		__attribute__((_iwram_code));
	virtual void block_coll_response_top_16x32( sprite& the_player, 
		const block_coll_result& tl_coll_result, 
		const block_coll_result& tm_coll_result,
		const block_coll_result& tr_coll_result )
		__attribute__((_iwram_code));
	
	virtual void handle_jumping_stuff( sprite& the_player, u32
		is_jump_key_hit, u32 is_jump_key_held )
		__attribute__((_iwram_code));
	
	
	
protected:		// functions
	//virtual void block_collision_stuff_16x16( sprite& the_player )
	//	__attribute__((_iwram_code));
	//virtual void block_collision_stuff_16x32( sprite& the_player )
	//	__attribute__((_iwram_code));
	
	virtual void update_frames_and_frame_timers( sprite& the_player );
	
	virtual void update_the_pickaxe( sprite& the_player );
	
	
	
} __attribute__((_align4));



#endif		// player_sprite_stuff_class_hpp
