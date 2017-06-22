// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef player_sprite_class_hpp
#define player_sprite_class_hpp

#include "../sprite_class.hpp"
#include "../../gfx_manager_class.hpp"

#include "../../../gfx/sherwin_gfx.h"

class PlayerSprite : public Sprite
{
public:		// enums
	// "Global" graphics frames
	enum frame
	{
		// Not a real frame, just a way To hide the Player
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
	} _ALIGNAS_REGULAR;
	
	// This enum allows multiple frame_slot's To be represented by the same
	// frame, which Is used, for example, in the walking animation.  Also,
	// the reason this Is necessary Is That So which frame Is currently
	// active Can be determined.  If two frames in the enum share a value,
	// it Is impossible To tell where in the walk cycle the Player's
	// animation Is.
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
		
		// lim_frm_slot Is the amount of frame_slot's.  It Is
		// automatically updated by the compiler.
		lim_frm_slot,
	} _ALIGNAS_REGULAR;
	
	
	// These are used To access misc_data_u and misc_data_s
	enum udata_index
	{ 
		udi_active_walk_frame_slot, 
		udi_active_pickaxe_swing_frame_slot,
	} _ALIGNAS_REGULAR;
	enum sdata_index
	{
		sdi_walk_frame_timer, 
		sdi_pickaxe_swing_frame_timer,
	} _ALIGNAS_REGULAR;
	
	
public:		// variables
	// Static variables
	
	//static Fixed24p8 speed __attribute__((_IWRAM));
	static bool use_16x16;
	static bool run_toggle;
	
	static s32 max_hp;
	static s32 remaining_hp;
	
	// Pickaxe stuff
	static bool swinging_pickaxe;
	static u32 pickaxe_sprite_slot;
	
	
	static bool warped_this_frame;
	static bool warped_to_other_sublevel_this_frame;
	
	
	
	// Physics/logic constants
	static const Fixed24p8 jump_vel;
	static const Fixed24p8 jump_grav_acc;
	
	static const s32 max_jump_hold_timer;
	static const s32 walk_frame_timer_end;
	static const s32 run_frame_timer_end;
	
	static const s32 pickaxe_swing_start_frame_timer_end;
	static const s32 pickaxe_swing_frame_timer_end;
	static const s32 pickaxe_swing_final_frame_timer_end;
	
	static const Fixed24p8 walk_speed;
	static const Fixed24p8 max_run_speed;
	static const Fixed24p8 run_accel_x_abs_val;
	
	// 0.5 seconds
	static constexpr s32 initial_invin_frame_timer = 30;
	
	// Graphics constants
	
	// A constant array That Is Intended To be indexed with a frame_slot,
	// such That a frame_slot Can be mapped To a frame. 
	static constexpr u32 frame_slot_to_frame_arr_size = lim_frm_slot;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
	
	static const SpriteConstParams the_const_params;
	//static constexpr sprite_type the_const_sprite_type = StPlayer;
	//static constexpr sprite_palette_slot the_palette_slot = sps_player;
	//
	//static constexpr u32 num_active_gfx_tiles 
	//	= GfxManager::num_tiles_in_ss_16x32;
	//
	//static constexpr tile* tile_arr = const_cast<tile*>
	//	(reinterpret_cast<const tile*>(sherwin_gfxTiles));
	//
	//static const OamEntry::shape_size the_initial_shape_size 
	//	= OamEntry::ss_16x32;
	//
	//static const vec2_f24p8 the_initial_coll_box_size,
	//	the_initial_cb_pos_offset;
	//
	//// This Is used To correct the initial in-Level position for sprites
	//// That are normally considered To be of a certain size but That use
	//// larger graphics for some frames.
	//static const vec2_f24p8 the_initial_in_level_pos_offset;
	
	
public:		// functions
	inline PlayerSprite(bool facing_left=false)
	{
		shared_constructor_code_part_1();
		Sprite::shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	//PlayerSprite(bool facing_left);
	//PlayerSprite(const vec2_f24p8& s_in_level_pos, 
	//	const PrevCurrPair<bg_point>& camera_pos, bool facing_left);
	PlayerSprite(const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, 
		PrevCurrPair<bg_point>& camera_pos_pc_pair, bool facing_left);
	
	
	//virtual void shared_constructor_code_part_1();
	//virtual void shared_constructor_code_part_2(bool facing_left=false);
	virtual void shared_constructor_code_part_2
		(const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, 
		PrevCurrPair<bg_point>& camera_pos_pc_pair,
		bool facing_left=false);
	
	virtual void shared_constructor_code_part_3();
	
	inline virtual const SpriteConstParams& get_const_params() const
	{
		return the_const_params;
	}
	
	//inline virtual const sprite_type get_const_sprite_type() const
	//{
	//	return the_const_sprite_type;
	//}
	
	//virtual void gfx_update();
	
	virtual void update_part_1();
	virtual void update_part_2();
	virtual void update_part_3
		(PrevCurrPair<bg_point>& camera_pos_pc_pair,
		const vec2_u32& the_sublevel_size_2d);
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot();
	
	virtual const u32 get_curr_relative_tile_slot();
	
	
	
	// Physics and collision stuff
	virtual void block_collision_stuff();
	
	//virtual void block_coll_response_top_16x16_old
	//	(const BlockCollResult& tl_coll_result, 
	//	const BlockCollResult& tm_coll_result,
	//	const BlockCollResult& tr_coll_result);
	//virtual void block_coll_response_top_16x32_old
	//	(const BlockCollResult& tl_coll_result, 
	//	const BlockCollResult& tm_coll_result,
	//	const BlockCollResult& tr_coll_result);
	
	virtual void handle_jumping_stuff(u32 is_jump_key_hit, 
		u32 is_jump_key_held) __attribute__((_IWRAM_CODE));
	
	
	// Sprite-Sprite interaction stuff
	virtual void sprite_interaction_reponse(Sprite& the_other_sprite, 
		PrevCurrPair<bg_point>& camera_pos, 
		const vec2_u32& the_level_size_2d);
	
	
protected:		// functions
	//virtual void block_collision_stuff_16x16()
	//	__attribute__((_IWRAM_CODE));
	//virtual void block_collision_stuff_16x32()
	//	__attribute__((_IWRAM_CODE));
	
	virtual void update_frames_and_frame_timers();
	
	virtual void update_the_pickaxe();
	
	
	
} __attribute__((_ALIGN4));



#endif		// player_sprite_class_hpp
