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


#include "../sprite_type_stuff.hpp"
#include "../sprite_type_includes.hpp"

#include "../sprite_class.hpp"

#include "../../../gba_specific_stuff/button_stuff.hpp"
#include "../../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../../level_stuff/active_level_manager_class.hpp"
#include "../sprite_manager_class.hpp"

#include "../../gfx_manager_class.hpp"

#include "../sprite_allocator_class.hpp"

const SpriteConstParams PlayerSprite::the_const_params
= {
	// the_const_sprite_type
	StPlayer, 

	// the_palette_slot
	sps_player, 

	// the_relative_metatile_slot (not used by the PlayerSprite class)
	0,

	// num_active_gfx_tiles
	GfxManager::num_tiles_in_ss_16x32,

	// tile_arr 
	const_cast<Tile*>(reinterpret_cast<const Tile*>(sherwin_gfxTiles)),

	// the_initial_shape_size
	OamEntry::ss_16x32,
	//OamEntry::ss_16x16,
	//OamEntry::ss_8x8,

	// the_initial_coll_box_size
	{ {11 << Fixed24p8::get_shift() }, {28 << Fixed24p8::get_shift() } },
	//{ {11 << Fixed24p8::get_shift() }, {14 << Fixed24p8::get_shift() } },
	//{ {8 << Fixed24p8::get_shift() }, {8 << Fixed24p8::get_shift() } },

	// the_initial_cb_pos_offset
	{ {2 << Fixed24p8::get_shift() }, {4 << Fixed24p8::get_shift() } },
	//{ {0}, {0} },

	// the_initial_in_level_pos_offset
	{ {0 << Fixed24p8::get_shift()}, {0 << Fixed24p8::get_shift()} }
};



//Fixed24p8 PlayerSprite::speed;
bool PlayerSprite::use_16x16;
bool PlayerSprite::run_toggle;

s32 PlayerSprite::max_hp;
s32 PlayerSprite::remaining_hp;


// Pickaxe stuff
bool PlayerSprite::swinging_pickaxe;
u32 PlayerSprite::pickaxe_sprite_slot;

bool PlayerSprite::warped_this_frame;
bool PlayerSprite::warped_to_other_sublevel_this_frame;

// Physics/logic constants
const Fixed24p8 PlayerSprite::jump_vel = {-0x400};
//const Fixed24p8 PlayerSprite::jump_vel = {-0x300};
const Fixed24p8 PlayerSprite::jump_grav_acc = {0x1b};

//const s32 PlayerSprite::max_jump_hold_timer = 16;
//const s32 PlayerSprite::max_jump_hold_timer = 20;
const s32 PlayerSprite::max_jump_hold_timer = 24;
const s32 PlayerSprite::walk_frame_timer_end = 5;
const s32 PlayerSprite::run_frame_timer_end = 3;

//const s32 PlayerSprite::pickaxe_swing_frame_timer_end = 4;
//const s32 PlayerSprite::pickaxe_swing_frame_timer_end = 2;
const s32 PlayerSprite::pickaxe_swing_start_frame_timer_end = 10;
const s32 PlayerSprite::pickaxe_swing_frame_timer_end = 1;
const s32 PlayerSprite::pickaxe_swing_final_frame_timer_end = 10;

const Fixed24p8 PlayerSprite::walk_speed = {0x100};
//const Fixed24p8 PlayerSprite::max_run_speed = {0x200};
//const Fixed24p8 PlayerSprite::max_run_speed = {0x300};
//const Fixed24p8 PlayerSprite::max_run_speed = {0x380};
const Fixed24p8 PlayerSprite::max_run_speed = {0x300};
//const Fixed24p8 PlayerSprite::run_accel_x_abs_val = {0x40};
const Fixed24p8 PlayerSprite::run_accel_x_abs_val = {0x08};


// Graphics constants

// A constant array That Is Intended To be indexed with a frame_slot,
// such That a frame_slot Can be mapped To a frame. 
const PlayerSprite::frame PlayerSprite::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size] 
= { 
	// Invisible
	frm_invisible, 

	// Standing
	frm_stand,

	// Walking/running
	frm_stand, frm_walk_0, frm_walk_1, frm_walk_0,

	// Swinging a weapon, on the ground, while not moving
	frm_weapon_swing_ground_still_0, frm_weapon_swing_ground_still_1,
	frm_weapon_swing_ground_still_2, frm_weapon_swing_ground_still_3,
	frm_weapon_swing_ground_still_4, frm_weapon_swing_ground_still_5,

	// Two taller weapon swinging frames, which could be used as part
	// of item throwing animations instead of
	// frm_weapon_swing_ground_still_4 and
	// frm_weapon_swing_ground_still_5.
	frm_weapon_swing_ground_still_4_tall,
	frm_weapon_swing_ground_still_5_tall,

	// Swinging a weapon, on the ground, but also moving, row 0
	frm_weapon_swing_ground_moving_0_row_0, 
	frm_weapon_swing_ground_moving_1_row_0,
	frm_weapon_swing_ground_moving_2_row_0,
	frm_weapon_swing_ground_moving_3_row_0,
	frm_weapon_swing_ground_moving_4_row_0,
	frm_weapon_swing_ground_moving_5_row_0,

	// Swinging a weapon, on the ground, but also moving, row 1
	frm_weapon_swing_ground_moving_0_row_1,
	frm_weapon_swing_ground_moving_1_row_1,
	frm_weapon_swing_ground_moving_2_row_1,
	frm_weapon_swing_ground_moving_3_row_1,
	frm_weapon_swing_ground_moving_4_row_1,
	frm_weapon_swing_ground_moving_5_row_1,

	// Swinging a weapon, on the ground, but also moving, row 2
	frm_weapon_swing_ground_moving_0_row_2,
	frm_weapon_swing_ground_moving_1_row_2,
	frm_weapon_swing_ground_moving_2_row_2,
	frm_weapon_swing_ground_moving_3_row_2,
	frm_weapon_swing_ground_moving_4_row_2,
	frm_weapon_swing_ground_moving_5_row_2,

	// Swinging a weapon, in the air (uses the same graphics as the
	// ones for weapon swing, on the ground, but also moving, row 2).
	frm_weapon_swing_ground_moving_0_row_2,
	frm_weapon_swing_ground_moving_1_row_2,
	frm_weapon_swing_ground_moving_2_row_2,
	frm_weapon_swing_ground_moving_3_row_2,
	frm_weapon_swing_ground_moving_4_row_2,
	frm_weapon_swing_ground_moving_5_row_2,
};



////const Vec2F24p8 PlayerSprite::the_initial_coll_box_size 
////	= { {12 << Fixed24p8::get_shift() }, {29 << Fixed24p8::get_shift() } },
////	PlayerSprite::the_initial_cb_pos_offset 
////	= { {2 << Fixed24p8::get_shift() }, {3 << Fixed24p8::get_shift() } };
////const Vec2F24p8 PlayerSprite::the_initial_coll_box_size 
////	= { {12 << Fixed24p8::get_shift() }, {27 << Fixed24p8::get_shift() } },
////	PlayerSprite::the_initial_cb_pos_offset 
////	= { {2 << Fixed24p8::get_shift() }, {5 << Fixed24p8::get_shift() } };
////const Vec2F24p8 PlayerSprite::the_initial_coll_box_size 
////	= { {12 << Fixed24p8::get_shift() }, {28 << Fixed24p8::get_shift() } },
////	PlayerSprite::the_initial_cb_pos_offset 
////	= { {2 << Fixed24p8::get_shift() }, {4 << Fixed24p8::get_shift() } };
//const Vec2F24p8 PlayerSprite::the_initial_coll_box_size 
//	= { {11 << Fixed24p8::get_shift() }, {28 << Fixed24p8::get_shift() } },
//	PlayerSprite::the_initial_cb_pos_offset 
//	= { {2 << Fixed24p8::get_shift() }, {4 << Fixed24p8::get_shift() } };
//
//const Vec2F24p8 PlayerSprite::the_initial_in_level_pos_offset
//	= { {0 << Fixed24p8::get_shift()}, {0 << Fixed24p8::get_shift()} };
//
////const Vec2F24p8 PlayerSprite::the_initial_coll_box_size 
////	= { {12 << Fixed24p8::get_shift() }, {29 << Fixed24p8::get_shift() } },
////	PlayerSprite::the_initial_cb_pos_offset 
////	= { {(2 + 8) << Fixed24p8::get_shift() }, {3 << Fixed24p8::get_shift() } };
////
////const Vec2F24p8 PlayerSprite::the_initial_in_level_pos_offset
////	= { {8 << Fixed24p8::get_shift()}, {0 << Fixed24p8::get_shift()} };

PlayerSprite::PlayerSprite(const Vec2F24p8& s_in_level_pos, 
	const Vec2u32& the_level_size_2d, 
	PrevCurrPair<BgPoint>& camera_pos_pc_pair, bool facing_left)
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2(s_in_level_pos, the_level_size_2d, 
		camera_pos_pc_pair, facing_left);
	shared_constructor_code_part_3();
}


//void PlayerSprite::shared_constructor_code_part_2(bool facing_left)
//{
//	Sprite::shared_constructor_code_part_2(facing_left);
//}

void PlayerSprite::shared_constructor_code_part_2
	(const Vec2F24p8& s_in_level_pos, const Vec2u32& the_level_size_2d,
	PrevCurrPair<BgPoint>& camera_pos_pc_pair, bool facing_left)
{
	Sprite::shared_constructor_code_part_2(facing_left);

	//in_level_pos = s_in_level_pos - get_initial_in_level_pos_offset();
	set_curr_in_level_pos(s_in_level_pos 
		- get_initial_in_level_pos_offset());


	update_f24p8_positions();
	update_on_screen_pos(camera_pos_pc_pair);

	center_camera_almost(camera_pos_pc_pair.curr);
	ActiveLevelManager::correct_bg0_scroll_mirror(the_level_size_2d);
	update_on_screen_pos(camera_pos_pc_pair);
	copy_the_oam_entry_to_oam_mirror
		(SpriteManager::the_player_oam_index);

	clear_and_set_bits(the_oam_entry.attr2, OBJ_ATTR2_PRIO_MASK, 
		OBJ_ATTR2_PRIO_1);
}

void PlayerSprite::shared_constructor_code_part_3()
{
	//Sprite::shared_constructor_code_part_1();

	//the_sprite_type = get_const_sprite_type();

	// This Is for slope testing stuffs
	//set_shape_size(OamEntry::ss_16x16);
	////the_coll_box.size = { 12 << Fixed24p8::get_shift(),
	////	13 << Fixed24p8::get_shift() };
	////cb_pos_offset = { 2 << Fixed24p8::get_shift(),
	////	3 << Fixed24p8::get_shift() };
	//the_coll_box.size = { 16 << Fixed24p8::get_shift(),
	//	16 << Fixed24p8::get_shift() };
	//cb_pos_offset = { 0 << Fixed24p8::get_shift(),
	//	0 << Fixed24p8::get_shift() };

	swinging_pickaxe = false;
	pickaxe_sprite_slot = -1;

	max_vel_x_abs_val = max_run_speed;
}

//void PlayerSprite::gfx_update()
//{
//	//the_oam_entry.set_tile_number
//	//	(get_curr_tile_slot_old());
//	//the_oam_entry.set_tile_number
//	//	(get_vram_chunk_index() 
//	//	* GfxManager::num_tiles_in_ss_32x32);
//	the_oam_entry.set_tile_number
//		(get_curr_tile_slot());
//
//	the_oam_entry.set_pal_number 
//		(get_palette_slot());
//}

void PlayerSprite::update_part_1()
{
	Sprite::update_part_1();
	warped_this_frame = false;
	warped_to_other_sublevel_this_frame = false;
}


void PlayerSprite::update_part_2() 
{
	gfx_update();

	if (!swinging_pickaxe)
	{
		if (key_hit(KEY_R))
		{
			pickaxe_sprite_slot 
				= SpriteManager::spawn_a_player_secondary_sprite_basic
				(StPlayerPickaxe, get_curr_in_level_pos(),
				GfxManager::bgofs_mirror[0],
				the_oam_entry.get_hflip_status());

			if (pickaxe_sprite_slot != -1)
			{
				swinging_pickaxe = true;
			}

		}

		//else //if (!key_hit(KEY_R))
		//{
		//	// Despawn the pickaxe if the_player Is no longer swinging it.
		//	SpriteManager::the_player_secondary_sprites
		//		[pickaxe_sprite_slot].the_sprite_type = StDefault;
		//
		//	pickaxe_sprite_slot = -1;
		//}
	}

	if (key_hit(KEY_B) && get_curr_on_ground())
	{
		if (!run_toggle)
		{
			run_toggle = true;
		}
		else
		{
			run_toggle = false;
		}
	}

	s32 key_dir = 0;
	s32 vel_x_dir = 0;

	if (vel.x < (Fixed24p8){0})
	{
		vel_x_dir = -1;
	}
	else if (vel.x > (Fixed24p8){0})
	{
		vel_x_dir = 1;
	}

	Fixed24p8 vel_x_abs = custom_abs(vel.x);

	if (key_hit_or_held(KEY_LEFT) && !key_hit_or_held(KEY_RIGHT))
	{
		key_dir = -1;
	}
	else if (key_hit_or_held(KEY_RIGHT) && !key_hit_or_held(KEY_LEFT))
	{
		key_dir = 1;
	}
	else // neither left nor right hit_or_held
	{
		if (vel_x_abs < (Fixed24p8){0x20})
		{
			vel.x = {0};
			accel_x = {0};
		}

		// Don't allow speed changing when in the air
		else if (get_curr_on_ground())
		{
			if (vel_x_abs > (Fixed24p8){0})
			{
				accel_x.data = -vel_x_dir * run_accel_x_abs_val.data * 4;
			}
		}

	}

	if (key_dir != 0)
	{
		// Allow almost instantly turning around (not something That Can be
		// done in real life!)
		if ((key_dir < 0 && vel.x.data > 0)
			|| (key_dir > 0 && vel.x.data < 0))
		{
			vel.x = {0};
		}

		if (run_toggle)
		{
			max_vel_x_abs_val = max_run_speed;

			if (vel_x_abs < walk_speed)
			{
				//accel_x.data = vel_x_dir * walk_speed.data;
				accel_x.data = key_dir * walk_speed.data;
			}
			else
			{
				//accel_x.data = vel_x_dir * run_accel_x_abs_val.data;
				accel_x.data = key_dir * run_accel_x_abs_val.data;
			}

		}
		else //if (!run_toggle)
		{
			//vel.x = -walk_speed;

			max_vel_x_abs_val = walk_speed;

			//accel_x = -walk_speed;
			//accel_x.data = vel_x_dir * walk_speed.data;
			accel_x.data = key_dir * walk_speed.data;
		}


		//if (get_curr_on_ground() && !swinging_pickaxe)
		if (!swinging_pickaxe)
		{
			if (key_dir < 0)
			{
				the_oam_entry.enable_hflip();
			}
			else if (key_dir > 0)
			{
				the_oam_entry.disable_hflip();
			}
		}
	}

	handle_jumping_stuff(key_hit(KEY_A), key_held(KEY_A));


	update_f24p8_positions();

	block_collision_stuff();

	update_the_pickaxe();


}



void PlayerSprite::update_part_3
	(PrevCurrPair<BgPoint>& camera_pos_pc_pair, 
	const Vec2u32& the_sublevel_size_2d)
{
	// These should totally should be replaced by getter functions

	// Walk frame stuff
	s32& walk_frame_timer = misc_data_s[sdi_walk_frame_timer];
	u32& active_walk_frame_slot = misc_data_u
		[udi_active_walk_frame_slot];

	// Pickaxe swing frame stuff
	s32& pickaxe_swing_frame_timer = misc_data_s
		[sdi_pickaxe_swing_frame_timer];
	u32& active_pickaxe_swing_frame_slot = misc_data_u
		[udi_active_pickaxe_swing_frame_slot];

	update_frames_and_frame_timers();


	//for (Sprite* spr : SpriteManager::the_sprites)
	for (Sprite* spr : SpriteManager::the_active_sprites)
	{
		sprite_interaction_reponse(*spr, camera_pos_pc_pair,
			the_sublevel_size_2d);

		if (warped_to_other_sublevel_this_frame)
		{
			break;
		}
	}

	for (Sprite* spr : SpriteManager::the_active_pseudo_bg_sprites)
	{
		sprite_interaction_reponse(*spr, camera_pos_pc_pair,
			the_sublevel_size_2d);

		if (warped_to_other_sublevel_this_frame)
		{
			break;
		}
	}

	update_on_screen_pos(camera_pos_pc_pair);

	if (warped_this_frame && !warped_to_other_sublevel_this_frame)
	{

	}
	else
	{
		camera_follow_basic(camera_pos_pc_pair);
		//center_camera_almost(camera_pos_pc_pair.curr);
	}

	ActiveLevelManager::correct_bg0_scroll_mirror(the_sublevel_size_2d);

	update_on_screen_pos(camera_pos_pc_pair);

	// Despawn sprites if the_player warped from one part of the current
	// Sublevel To another part of the current Sublevel, if they are
	// offscreen.  Also, spawn sprites That are in the new area.
	if (warped_this_frame && !warped_to_other_sublevel_this_frame)
	{
		SpriteManager::despawn_sprites_if_needed(camera_pos_pc_pair.curr);

		SpriteManager::initial_sprite_spawning_shared_code
			(camera_pos_pc_pair);
	}

	if (PlayerSprite::remaining_hp < 0)
	{
		PlayerSprite::remaining_hp = 0;
	}
	else if (PlayerSprite::remaining_hp 
		> PlayerSprite::max_hp)
	{
		PlayerSprite::remaining_hp 
			= PlayerSprite::max_hp;
	}

	copy_the_oam_entry_to_oam_mirror
		(SpriteManager::the_player_oam_index);

	update_the_pickaxe();

	if (invin_frame_timer > 0)
	{
		--invin_frame_timer;
	}
}

void PlayerSprite::update_frames_and_frame_timers()
{
	// These should totally should be replaced by getter functions

	// Walk frame stuff
	s32& walk_frame_timer = misc_data_s[sdi_walk_frame_timer];
	u32& active_walk_frame_slot = misc_data_u[udi_active_walk_frame_slot];

	// Hammer swing frame stuff
	s32& pickaxe_swing_frame_timer = misc_data_s
		[sdi_pickaxe_swing_frame_timer];
	u32& active_pickaxe_swing_frame_slot = misc_data_u
		[udi_active_pickaxe_swing_frame_slot];


	if (active_walk_frame_slot < frm_slot_walk_0 
		|| active_walk_frame_slot > frm_slot_walk_3)
	{
		active_walk_frame_slot = frm_slot_walk_0;
	}

	if (!swinging_pickaxe)
	{
		pickaxe_swing_frame_timer = 0;
		active_pickaxe_swing_frame_slot 
			= frm_slot_weapon_swing_ground_still_0;
	}

	if (get_curr_on_ground())
	{
		auto lambda_func_for_else_if = [&](const u32 frame_timer_end)
			-> void
		{
			++walk_frame_timer;

			if (walk_frame_timer >= frame_timer_end)
			{
				walk_frame_timer = 0;

				if (active_walk_frame_slot == frm_slot_walk_0)
				{
					active_walk_frame_slot = frm_slot_walk_1;
				}
				else if (active_walk_frame_slot == frm_slot_walk_1)
				{
					active_walk_frame_slot = frm_slot_walk_2;
				}
				else if (active_walk_frame_slot == frm_slot_walk_2)
				{
					active_walk_frame_slot = frm_slot_walk_3;
				}
				else if (active_walk_frame_slot == frm_slot_walk_3)
				{
					active_walk_frame_slot = frm_slot_walk_0;
				}

			}

		};

		Fixed24p8 vel_x_abs = custom_abs(vel.x);

		// Standing still
		//if (speed == (Fixed24p8){0})
		if (vel.x == (Fixed24p8){0})
		{
			walk_frame_timer = 0;
			//active_walk_frame_slot = frm_slot_walk_1;
			active_walk_frame_slot = frm_slot_walk_0;
		}


		// Walking speed or not-max running speed
		//else if (speed >= walk_speed && speed < max_run_speed)

		//else if ((vel.x >= walk_speed && vel.x < max_run_speed)
		//	|| ((-vel.x) >= walk_speed) && (-vel.x) < max_run_speed)
		//else if ((vel.x >= walk_speed && vel.x < max_run_speed)
		//	|| ((-vel.x) > walk_speed && (-vel.x) < max_run_speed))
		else if (vel_x_abs >= walk_speed && vel_x_abs < max_run_speed)
		{
			lambda_func_for_else_if(walk_frame_timer_end);
		}

		// Max running speed
		//else if (speed == max_run_speed)
		//else if (vel.x == max_run_speed || (-vel.x) == max_run_speed)
		else if (vel_x_abs == max_run_speed)
		{
			lambda_func_for_else_if(run_frame_timer_end);
		}

		else
		{
			// This should NEVER happen, So show a walking frame as a
			// debugging tool
			walk_frame_timer = 0;
			active_walk_frame_slot = frm_slot_walk_3;
		}
	}
	else //if (!get_curr_on_ground())
	{
		active_walk_frame_slot = frm_slot_walk_2;
	}

	if (swinging_pickaxe)
	{
		++pickaxe_swing_frame_timer;

		if (pickaxe_swing_frame_timer >= pickaxe_swing_frame_timer_end)
		{
			if (active_pickaxe_swing_frame_slot
				!= frm_slot_weapon_swing_ground_still_0
				&& active_pickaxe_swing_frame_slot 
				!= frm_slot_weapon_swing_ground_still_5)
			{
				pickaxe_swing_frame_timer = 0;
			}

			switch (active_pickaxe_swing_frame_slot)
			{
				case frm_slot_weapon_swing_ground_still_0:
					if (pickaxe_swing_frame_timer
						>= pickaxe_swing_start_frame_timer_end)
					{
						active_pickaxe_swing_frame_slot 
							= frm_slot_weapon_swing_ground_still_1;
					}
					break;

				case frm_slot_weapon_swing_ground_still_1:
					active_pickaxe_swing_frame_slot 
						= frm_slot_weapon_swing_ground_still_2;
					break;

				case frm_slot_weapon_swing_ground_still_2:
					active_pickaxe_swing_frame_slot 
						= frm_slot_weapon_swing_ground_still_3;
					break;

				case frm_slot_weapon_swing_ground_still_3:
					active_pickaxe_swing_frame_slot 
						= frm_slot_weapon_swing_ground_still_4;
					break;

				case frm_slot_weapon_swing_ground_still_4:
					active_pickaxe_swing_frame_slot 
						= frm_slot_weapon_swing_ground_still_5;
					break;

				case frm_slot_weapon_swing_ground_still_5:
					//active_pickaxe_swing_frame_slot 
					//	= frm_slot_weapon_swing_ground_still_0;

					//if (speed == (Fixed24p8){0} && get_curr_on_ground() 
					//	&& pickaxe_swing_frame_timer 
					//	>= pickaxe_swing_still_final_frame_timer_end)
					//{
					//	pickaxe_swing_frame_timer = 0;
					//	swinging_pickaxe = false;
					//}
					//else if (speed != (Fixed24p8){0} 
					//	|| !get_curr_on_ground())
					//{
					//	pickaxe_swing_frame_timer = 0;
					//	swinging_pickaxe = false;
					//}
					if (pickaxe_swing_frame_timer 
						>= pickaxe_swing_final_frame_timer_end)
					{
						pickaxe_swing_frame_timer = 0;
						swinging_pickaxe = false;
					}

					break;

				default:
					swinging_pickaxe = false;
					break;

			}

		}

		//if (swinging_pickaxe)
		//{
		//	return frame_slot_to_frame_arr
		//		[active_pickaxe_swing_frame_slot] 
		//		* get_num_active_gfx_tiles();
		//}
		//else //if (!swinging_pickaxe)
		//{
		//	return frame_slot_to_frame_arr[active_walk_frame_slot]
		//		* get_num_active_gfx_tiles();
		//}
	}

}

// This Is very ugly
void PlayerSprite::update_the_pickaxe()
{
	if (pickaxe_sprite_slot == -1)
	{
		return;
	}

	// These should totally should be replaced by getter functions

	//Sprite*& the_pickaxe_ptr = SpriteManager::the_player_secondary_sprites
	//	[pickaxe_sprite_slot];

	Sprite* the_pickaxe_ptr = &(SpriteManager
		::the_player_secondary_sprites[pickaxe_sprite_slot]);
	//Sprite& the_pickaxe = *the_pickaxe_ptr;
	u32& the_pickaxe_frame_slot = the_pickaxe_ptr->misc_data_u
		[PlayerPickaxeSprite::udi_curr_frame_slot];

	if (!swinging_pickaxe)
	{
		//// Despawn the pickaxe if the_player Is no longer swinging it.
		//the_pickaxe.the_sprite_type = StDefault;

		//SpriteManager::the_player_secondary_sprites_allocator
		//	.deallocate_sprite(the_pickaxe_ptr);

		if (the_pickaxe_ptr)
		{
			//SpriteManager::the_player_secondary_sprites_allocator
			//	.deallocate_sprite(the_pickaxe);
			SpriteManager::the_player_secondary_sprites_allocator
				.deallocate_sprite(*the_pickaxe_ptr);
			the_pickaxe_ptr = NULL;
		}

		pickaxe_sprite_slot = -1;
	}
	else if (/* swinging_pickaxe && */ the_pickaxe_ptr)
	{
		u32 active_pickaxe_swing_frame_slot = misc_data_u
			[udi_active_pickaxe_swing_frame_slot];

		if (active_pickaxe_swing_frame_slot 
			>= frm_slot_weapon_swing_ground_still_0 
			&& active_pickaxe_swing_frame_slot 
			<= frm_slot_weapon_swing_ground_still_1)
		{
			if (the_oam_entry.get_hflip_status() 
				&& the_pickaxe_ptr->the_oam_entry.get_hflip_status())
			{
				the_pickaxe_ptr->the_oam_entry.disable_hflip();
			}
			else if (!the_oam_entry.get_hflip_status() 
				&& !the_pickaxe_ptr->the_oam_entry.get_hflip_status())
			{
				the_pickaxe_ptr->the_oam_entry.enable_hflip();
			}
		}
		else
		{
			if (the_oam_entry.get_hflip_status() 
				&& !the_pickaxe_ptr->the_oam_entry.get_hflip_status())
			{
				the_pickaxe_ptr->the_oam_entry.enable_hflip();
			}
			else if (!the_oam_entry.get_hflip_status() 
				&& the_pickaxe_ptr->the_oam_entry.get_hflip_status())
			{
				the_pickaxe_ptr->the_oam_entry.disable_hflip();
			}
		}

		// There should really be arrays To load from for these!
		switch (active_pickaxe_swing_frame_slot)
		{
			case frm_slot_weapon_swing_ground_still_0:
				the_pickaxe_frame_slot 
					= PlayerPickaxeSprite::frm_slot_angle_45;
				if (!the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(-14), make_f24p8(0) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos() 
						+ (Vec2F24p8){ make_f24p8(-14), make_f24p8(0) });
				}
				else //if (the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(14), make_f24p8(0) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(14), make_f24p8(0) });
				}

				the_pickaxe_ptr->update_f24p8_positions();

				break;

			case frm_slot_weapon_swing_ground_still_1:
				the_pickaxe_frame_slot 
					= PlayerPickaxeSprite::frm_slot_angle_23;
				if (!the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(-10), make_f24p8(-2) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(-10), 
						make_f24p8(-2) });
				}
				else //if (the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(10), make_f24p8(-2) };
					the_pickaxe_ptr->set_curr_in_level_pos(
						get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(10), make_f24p8(-2) });
				}
				//if ((speed != (Fixed24p8){0} && get_curr_on_ground())
				//	|| !get_curr_on_ground())
				if ((vel.x != (Fixed24p8){0} && get_curr_on_ground()) 
					|| !get_curr_on_ground())
				{
					//the_pickaxe_ptr->in_level_pos.y -= make_f24p8(1);
					the_pickaxe_ptr->set_curr_in_level_pos_y
						(the_pickaxe_ptr->get_curr_in_level_pos().y 
						- make_f24p8(1));
				}

				the_pickaxe_ptr->update_f24p8_positions();

				break;

			case frm_slot_weapon_swing_ground_still_2:
				the_pickaxe_frame_slot 
					= PlayerPickaxeSprite::frm_slot_angle_0;
				if (!the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(-1), make_f24p8(-4) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(-1), make_f24p8(-4) });
				}
				else //if (the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(1), make_f24p8(-4) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(1), make_f24p8(-4) });
				}
				//if ((speed != (Fixed24p8){0} && get_curr_on_ground())
				//	|| !get_curr_on_ground())
				if ((vel.x != (Fixed24p8){0} && get_curr_on_ground()) 
					|| !get_curr_on_ground())
				{
					//the_pickaxe_ptr->in_level_pos.y -= make_f24p8(1);
					the_pickaxe_ptr->set_curr_in_level_pos_y
						(the_pickaxe_ptr->get_curr_in_level_pos().y 
						- make_f24p8(1));
				}

				the_pickaxe_ptr->update_f24p8_positions();

				break;

			case frm_slot_weapon_swing_ground_still_3:
				the_pickaxe_frame_slot = 
					PlayerPickaxeSprite::frm_slot_angle_23;
				if (!the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(7), make_f24p8(-2) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(7), make_f24p8(-2) });
				}
				else //if (the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(-7), make_f24p8(-2) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(-7), make_f24p8(-2) });
				}
				//if ((speed != (Fixed24p8){0} && get_curr_on_ground())
				//	|| !get_curr_on_ground())
				if ((vel.x != (Fixed24p8){0} && get_curr_on_ground()) 
					|| !get_curr_on_ground())
				{
					//the_pickaxe_ptr->in_level_pos.y -= make_f24p8(1);
					the_pickaxe_ptr->set_curr_in_level_pos_y
						(the_pickaxe_ptr->get_curr_in_level_pos().y 
						- make_f24p8(1));
				}

				the_pickaxe_ptr->update_f24p8_positions();

				break;

			case frm_slot_weapon_swing_ground_still_4:
				the_pickaxe_frame_slot 
					= PlayerPickaxeSprite::frm_slot_angle_45;
				if (!the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(11), make_f24p8(3) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(11), make_f24p8(3) });
				}
				else //if (the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(-11), make_f24p8(3) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(-11), make_f24p8(3) });
				}
				//if ((speed != (Fixed24p8){0} && get_curr_on_ground())
				//	|| !get_curr_on_ground())
				if ((vel.x != (Fixed24p8){0} && get_curr_on_ground()) 
					|| !get_curr_on_ground())
				{
					//the_pickaxe_ptr->in_level_pos.y -= make_f24p8(2);
					the_pickaxe_ptr->set_curr_in_level_pos_y
						(the_pickaxe_ptr->get_curr_in_level_pos().y 
						- make_f24p8(2));
				}

				the_pickaxe_ptr->update_f24p8_positions();

				break;


			case frm_slot_weapon_swing_ground_still_5:
				the_pickaxe_frame_slot 
					= PlayerPickaxeSprite::frm_slot_angle_90;
				if (!the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(14), make_f24p8(17) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(14), make_f24p8(17) });
				}
				else //if (the_oam_entry.get_hflip_status())
				{
					//the_pickaxe_ptr->in_level_pos = in_level_pos
					//	+ (Vec2F24p8){ make_f24p8(-14), make_f24p8(17) };
					the_pickaxe_ptr->set_curr_in_level_pos
						(get_curr_in_level_pos()
						+ (Vec2F24p8){ make_f24p8(-14), 
						make_f24p8(17) });
				}
				//if ((speed != (Fixed24p8){0} && get_curr_on_ground())
				//	|| !get_curr_on_ground())
				if ((vel.x != (Fixed24p8){0} && get_curr_on_ground()) 
					|| !get_curr_on_ground())
				{
					//the_pickaxe_ptr->in_level_pos.y -= make_f24p8(3);
					the_pickaxe_ptr->set_curr_in_level_pos_y
						(the_pickaxe_ptr->get_curr_in_level_pos().y 
						- make_f24p8(3));
				}

				the_pickaxe_ptr->update_f24p8_positions();

				break;

			default:
				break;
		}
	}
}

//const u32 PlayerSprite::get_curr_tile_slot()
//{
//	return sprite_palette_slot_first_vram_slot_list 
//		[get_palette_slot()]
//		+ get_curr_relative_tile_slot();
//}

const u32 PlayerSprite::get_curr_relative_tile_slot()
{
	// These should totally should be replaced by getter functions

	// Walk frame stuff
	s32& walk_frame_timer = misc_data_s[sdi_walk_frame_timer];
	u32& active_walk_frame_slot = misc_data_u[udi_active_walk_frame_slot];

	// Hammer swing frame stuff
	s32& pickaxe_swing_frame_timer = misc_data_s
		[sdi_pickaxe_swing_frame_timer];
	u32& active_pickaxe_swing_frame_slot = misc_data_u
		[udi_active_pickaxe_swing_frame_slot];


	// Invincibility frames!
	if (invin_frame_timer > 0)
	{
		switch (invin_frame_timer % 8)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				//the_oam_entry.hide_non_affine();
				return frame_slot_to_frame_arr[frm_slot_invisible]
					* get_num_active_gfx_tiles();
				break;

			case 4:
			case 5:
			case 6:
			case 7:
				//the_oam_entry.show_non_affine();
				break;
		}
	}

	if (!swinging_pickaxe)
	{
		if (get_curr_on_ground())
		{
			Fixed24p8 vel_x_abs = custom_abs(vel.x);

			// Standing still
			//if (speed == (Fixed24p8){0})
			if (vel.x == (Fixed24p8){0})
			{
				return frame_slot_to_frame_arr[frm_slot_walk_0]
					* get_num_active_gfx_tiles();
			}

			// Walking speed or not-max running speed
			//else if (speed >= walk_speed && speed < max_run_speed)
			//else if ((vel.x >= walk_speed && vel.x < max_run_speed)
			//	|| ((-vel.x) >= walk_speed && (-vel.x) < max_run_speed))
			else if (vel_x_abs >= walk_speed 
				&& vel_x_abs < max_run_speed)
			{
				return frame_slot_to_frame_arr[active_walk_frame_slot] 
					* get_num_active_gfx_tiles();
			}

			// Max running speed
			//else if (speed == max_run_speed)
			//else if (vel.x == max_run_speed 
			//	|| (-vel.x) == max_run_speed)
			else if (vel_x_abs == max_run_speed)
			{
				return frame_slot_to_frame_arr[active_walk_frame_slot] 
					* get_num_active_gfx_tiles();
			}

			else
			{
				// This should NEVER happen, So show a walking frame as a
				// debugging tool
				walk_frame_timer = 0;
				active_walk_frame_slot = frm_slot_walk_3;
				return frame_slot_to_frame_arr[active_walk_frame_slot] 
					* get_num_active_gfx_tiles();
			}
		}
		else //if (!get_curr_on_ground())
		{
			return frame_slot_to_frame_arr[frm_slot_walk_2] 
				* get_num_active_gfx_tiles();
		}
	}
	else //if (swinging_pickaxe)
	{
		// This Is So ugly
		switch (active_pickaxe_swing_frame_slot)
		{
			// Yay, another use for X-macros!
			#define LIST_OF_WEAPON_SWING_FRAME_SLOT_NUMBERS(macro) \
				macro(0) macro(1) macro(2) macro(3) macro(4) macro(5)

			#define X(number) \
			\
			case frm_slot_weapon_swing_ground_still_##number: \
				if (get_curr_on_ground()) \
				{ \
					/*if (speed == (Fixed24p8){0})*/ \
					if (vel.x == (Fixed24p8){0}) \
					{ \
						return frame_slot_to_frame_arr \
							[frm_slot_weapon_swing_ground_still_ \
							## number] \
							* get_num_active_gfx_tiles(); \
					} \
					else if (active_walk_frame_slot \
						== frm_slot_walk_0) \
					{ \
						return frame_slot_to_frame_arr \
							[frm_slot_weapon_swing_ground_moving_ \
							## number ## _row_0] \
							* get_num_active_gfx_tiles(); \
					} \
					else if (active_walk_frame_slot == frm_slot_walk_1 \
						|| active_walk_frame_slot == frm_slot_walk_3) \
					{ \
						return frame_slot_to_frame_arr \
							[frm_slot_weapon_swing_ground_moving_ \
							## number ## _row_1] \
							* get_num_active_gfx_tiles(); \
					} \
					else if (active_walk_frame_slot \
						== frm_slot_walk_2) \
					{ \
						return frame_slot_to_frame_arr \
							[frm_slot_weapon_swing_ground_moving_ \
							## number ## _row_2] \
							* get_num_active_gfx_tiles(); \
					} \
				} \
				else /*if (!get_curr_on_ground())*/ \
				{ \
					return frame_slot_to_frame_arr \
						[frm_slot_weapon_swing_air_##number] \
						* get_num_active_gfx_tiles(); \
				} \
				\
				break;

			LIST_OF_WEAPON_SWING_FRAME_SLOT_NUMBERS(X)
			#undef X



			default:
				return frame_slot_to_frame_arr[frm_slot_walk_0];
				break;

		}

	}

	return 9001;
}



// Physics and collision stuff
void PlayerSprite::block_collision_stuff()
{
	// Assume the_player Can only be one of two sizes
	if (the_coll_box.size.x >= make_f24p8(0)
		&& the_coll_box.size.x <= make_f24p8(16)
		&& the_coll_box.size.y > make_f24p8(16)
		&& the_coll_box.size.y <= make_f24p8(32))
	{
		block_collision_stuff_16x32();
	}
	else
	{
		block_collision_stuff_16x16();
	}
}

//void PlayerSprite::block_coll_response_top_16x16_old
//	(const BlockCollResult& tl_coll_result, 
//	const BlockCollResult& tm_coll_result,
//	const BlockCollResult& tr_coll_result)
//{
//	////in_level_pos.y 
//	////	= make_f24p8((tl_coll_result.coord.y + 1) * 16);
//	////	//- cb_pos_offset.y;
//	////in_level_pos.y = make_f24p8((tl_coll_result.coord.y + 1) * 16)
//	////	- cb_pos_offset.y;
//	//set_curr_in_level_pos_y(make_f24p8((tl_coll_result.coord.y + 1) 
//	//	* 16) - cb_pos_offset.y);
//	//
//	//if (vel.y < (Fixed24p8){0x00})
//	//{
//	//	vel.y = {0x00};
//	//}
//	//
//	////jump_hold_timer = 0;
//	//is_jumping = false;
//	//
//	//
//	//block_stuff_array[tl_coll_result.the_block->type]
//	//	->strongly_hit_response(ActiveLevel::the_block_at_coord
//	//	(tl_coll_result.coord), tl_coll_result.coord);
//	//
//	//if (tm_coll_result.coord != tl_coll_result.coord)
//	//{
//	//	block_stuff_array[tm_coll_result.the_block->type]
//	//		->strongly_hit_response(ActiveLevel::the_block_at_coord
//	//		(tm_coll_result.coord), tm_coll_result.coord);
//	//}
//	//
//	//if (tr_coll_result.coord != tl_coll_result.coord 
//	//	&& tr_coll_result.coord != tm_coll_result.coord)
//	//{
//	//	block_stuff_array[tr_coll_result.the_block->type]
//	//		->strongly_hit_response(ActiveLevel::the_block_at_coord
//	//		(tr_coll_result.coord), tr_coll_result.coord);
//	//}
//
//}
//void PlayerSprite::block_coll_response_top_16x32_old
//	(const BlockCollResult& tl_coll_result, 
//	const BlockCollResult& tm_coll_result,
//	const BlockCollResult& tr_coll_result)
//{
//	//block_coll_response_top_16x16_old(tl_coll_result, tm_coll_result, 
//	//	tr_coll_result);
//}



void PlayerSprite::handle_jumping_stuff(u32 is_jump_key_hit, 
	u32 is_jump_key_held)
{
	if (get_curr_on_ground() && is_jump_key_hit)
	{
		vel.y = jump_vel;
		//jump_hold_timer = max_jump_hold_timer;
		is_jumping = true;
		set_curr_on_ground(false);
		set_curr_on_slope(false);
	}
	else if (!get_curr_on_ground())
	{
		if (vel.y < (Fixed24p8){0})
		{
			if (is_jump_key_held)
			{
				vel.y += jump_grav_acc;
			}
			else
			{
				is_jumping = false;

				apply_gravity();
			}
		}
		else
		{
			is_jumping = false;

			apply_gravity();
		}
	}

}



// Sprite-Sprite interaction stuff
// This function SHOULD be passed a SpriteAllocator So That some types of
// sprites, such as powerups, Can be properly despawned!
void PlayerSprite::sprite_interaction_reponse(Sprite& the_other_sprite, 
	PrevCurrPair<BgPoint>& camera_pos_pc_pair, 
	const Vec2u32& the_level_size_2d)
{
	switch (the_other_sprite.the_sprite_type)
	{
		//case StWaffle:
		case StMuffin:
		case StFireMuffin:
		case StIceMuffin:
		case StChocolateMuffin:

			// This Is not proper despawning!
			//if (coll_box_intersects_now(the_coll_box,
			//	the_other_sprite.the_coll_box))
			//{
			//	//nocash_soft_break();
			//	the_other_sprite.the_sprite_type = StDefault;
			//	if (the_other_sprite.the_sprite_ipg != NULL)
			//	{
			//		the_other_sprite.the_sprite_ipg->spawn_state 
			//			= sss_dead;
			//	}
			//
			//	++remaining_hp;
			//}
			break;

		// This should 
		case StDoor:
			if (coll_box_intersects_now(the_coll_box,
				the_other_sprite.the_coll_box) && key_hit(KEY_UP) 
				&& !warped_this_frame)
				//&& get_curr_on_ground())
			{
				warped_this_frame = true;

				//const SublevelEntrance& the_dest_sle 
				//	= warp_block_sprite_stuff::get_dest_sle
				//	(the_other_sprite);

				const SublevelEntrance* the_dest_sle_ptr
					= &(ActiveLevel::the_current_level_ptr
					->get_sublevels()[the_other_sprite.the_sprite_ipg
					->extra_param_1]
					.sublevel_entrance_arr_arr_helper.the_array
					[the_other_sprite.the_sprite_ipg->extra_param_0]);


				if (the_other_sprite.the_sprite_ipg->extra_param_1 
					!= ActiveLevel::the_current_active_sublevel_index)
				{
					ActiveLevelManager
						::load_sublevel_at_intra_sublevel_warp
						(the_other_sprite.the_sprite_ipg->extra_param_1, 
						the_other_sprite.the_sprite_ipg->extra_param_0);

					warped_to_other_sublevel_this_frame = true;
				}

				//in_level_pos.x = the_dest_sle_ptr->in_level_pos.x 
				//	- get_initial_in_level_pos_offset().x;
				//in_level_pos.y = the_dest_sle_ptr->in_level_pos.y
				//	- get_initial_in_level_pos_offset().y;
				set_curr_in_level_pos_x(the_dest_sle_ptr->in_level_pos.x 
					- get_initial_in_level_pos_offset().x);
				set_curr_in_level_pos_y(the_dest_sle_ptr->in_level_pos.y
					- get_initial_in_level_pos_offset().y);

				update_f24p8_positions();
				update_on_screen_pos(camera_pos_pc_pair);

				center_camera_almost(camera_pos_pc_pair.curr);
				ActiveLevelManager::correct_bg0_scroll_mirror
					(the_level_size_2d);
				update_on_screen_pos(camera_pos_pc_pair);

			}
			break;

		case StSnowGolem:
			//if (coll_box_intersects_now(the_coll_box,
			//	the_other_sprite.the_coll_box) 
			//	&& invin_frame_timer == 0)
			//{
			//	--remaining_hp;
			//	invin_frame_timer = initial_invin_frame_timer;
			//}

		default:
			break;
	}

}


