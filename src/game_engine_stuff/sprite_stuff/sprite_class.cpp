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


#include "sprite_class.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../gfx_manager_class.hpp"

#include "sprite_allocator_class.hpp"

#include "../../general_utility_stuff/misc_utility_funcs.hpp"

#include "../level_stuff/active_level_class.hpp"

#include "sprite_manager_class.hpp"
#include "../../gba_specific_stuff/button_stuff.hpp"

#include "../level_stuff/sublevel_class.hpp"
#include "../spr_blk_coll_group_classes.hpp"

//s32 thv_vs_index;

const SpriteConstParams Sprite::the_const_params;

const Fixed24p8 Sprite::cpg_on_slope_threshold_abs = {0x400};

// coll_point_group threshold
const vec2_f24p8 Sprite::cpg_16x32_threshold_abs = { {0x400}, 
	{0x480} };

//const Fixed24p8 Sprite::grav_acc = {0x80};
//const Fixed24p8 Sprite::grav_acc = {0x40};
//const Fixed24p8 Sprite::grav_acc = {0x60};
const Fixed24p8 Sprite::grav_acc = {0x50};
//const Fixed24p8 Sprite::max_y_vel = {0x400};
const Fixed24p8 Sprite::max_y_vel = {0x300};
//const Fixed24p8 Sprite::max_y_vel = {0x280};



vec2_f24p8 Sprite::prev_prev_on_screen_pos; 
PrevCurrPair<vec2_f24p8> Sprite::on_screen_pos;
vec2_s32 Sprite::prev_prev_on_screen_pos_s32;
PrevCurrPair<vec2_s32> Sprite::on_screen_pos_s32;
PrevCurrPair<vec2_s32> Sprite::camera_pos_pc_pair_s32;

Vec2<bool> Sprite::temp_debug_thing;

vec2_f24p8 Sprite::on_screen_pos_diff_abs;
vec2_s32 Sprite::on_screen_pos_s32_diff_abs;
vec2_f24p8 Sprite::camera_pos_diff_abs;
vec2_s32 Sprite::camera_pos_s32_diff_abs;
//PrevCurrPair<s32> Sprite::tallest_height_val;


Sprite::Sprite()
{
	shared_constructor_code_part_1();
}
Sprite::Sprite(bool facing_left)
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2(facing_left);
}
Sprite::Sprite(const vec2_f24p8& s_in_level_pos, 
	const PrevCurrPair<bg_point>& camera_pos_pc_pair, bool facing_left)
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2(s_in_level_pos, camera_pos_pc_pair, 
		facing_left);
}
Sprite::Sprite(const vec2_f24p8& s_in_level_pos, 
	const vec2_u32& the_level_size_2d, 
	PrevCurrPair<bg_point>& camera_pos_pc_pair, bool facing_left)
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2(s_in_level_pos, the_level_size_2d, 
		camera_pos_pc_pair, facing_left);
}


void Sprite::shared_constructor_code_part_1()
{
	// uh-oh, it looks like this overwrites the vtable pointer for the
	// Sprite!
	//memfill32(this, 0, sizeof(Sprite) / sizeof(u32));
	
	the_sprite_type = get_const_sprite_type();;
	the_sprite_ipg = NULL;
	
	memfill32(&the_oam_entry, 0, sizeof(OamEntry) / sizeof(u32));
	
	
	set_initial_shape_size();
	the_oam_entry.set_tile_number(get_curr_tile_slot());
	the_oam_entry.set_pal_number(get_palette_slot());
	
	clear_and_set_bits(the_oam_entry.attr2, obj_attr2_prio_mask, 
		obj_attr2_prio_1);
	
	in_level_pos.prev = vec2_f24p8((Fixed24p8){0}, (Fixed24p8){0});
	in_level_pos.curr = vel = in_level_pos.prev;
	
	max_vel_x_abs_val = accel_x = (Fixed24p8){0};
	
	set_initial_coll_box_stuff();
	
	on_ground.prev = on_ground.curr = is_jumping = false;
	
	invin_frame_timer = 0;
	
	arr_memfill32(misc_data_u, 0, misc_data_size * 2);
	
	//vram_chunk_index = old_vram_chunk_index;
	
	
	update_f24p8_positions();
}
void Sprite::shared_constructor_code_part_2(bool facing_left)
{
	if (facing_left)
	{
		the_oam_entry.enable_hflip();
	}
}


void Sprite::shared_constructor_code_part_2
	(const vec2_f24p8& s_in_level_pos, 
	const PrevCurrPair<bg_point>& camera_pos_pc_pair, bool facing_left)
{
	shared_constructor_code_part_2(facing_left);
	//in_level_pos.curr = s_in_level_pos 
	//	- get_initial_in_level_pos_offset();
	set_curr_in_level_pos(s_in_level_pos 
		- get_initial_in_level_pos_offset());
	
	update_f24p8_positions();
	update_on_screen_pos(camera_pos_pc_pair);
}


// This form of shared_constructor_code() Is primarily Intended To be
// used by the_player.
void Sprite::shared_constructor_code_part_2
	(const vec2_f24p8& s_in_level_pos, const vec2_u32& the_level_size_2d, 
	PrevCurrPair<bg_point>& camera_pos_pc_pair, bool facing_left)
{
	shared_constructor_code_part_2(facing_left);
	//in_level_pos = s_in_level_pos - get_initial_in_level_pos_offset();
	set_curr_in_level_pos(s_in_level_pos 
		- get_initial_in_level_pos_offset());
	
	
	update_f24p8_positions();
	update_on_screen_pos(camera_pos_pc_pair);
}

void Sprite::shared_constructor_code_part_3()
{
	DebugArrGroup::debug_f8p8_arr_helper.at(0) = make_f8p8(3);
}

void* Sprite::operator new(size_t size, 
	SpriteAllocator& the_sprite_allocator)
{
	return the_sprite_allocator.allocate_sprite();
}


//Sprite::Sprite(u32 s_vram_chunk_index, 
//	SpriteInitParamGroup* s_the_sprite_ipg)
//{
//	switch (s_the_sprite_ipg->spawn_state)
//	{
//		case sss_not_active:
//			memfill32(this, 0, sizeof(Sprite) / sizeof(u32));
//			
//			the_sprite_ipg = s_the_sprite_ipg;
//			the_sprite_ipg->spawn_state = sss_active;
//			
//			the_sprite_type = the_sprite_ipg->type;
//			in_level_pos.x = make_f24p8
//				(the_sprite_ipg->initial_block_grid_x_coord * 16);
//			in_level_pos.y = make_f24p8
//				(the_sprite_ipg->initial_block_grid_y_coord * 16);
//			
//			sprite_stuff_array[the_sprite_type]->shared_constructor_code(*this, 
//				!the_sprite_ipg->facing_right);
//			
//			vram_chunk_index = s_vram_chunk_index;
//			break;
//			
//		case sss_active:
//		case sss_dead:
//		default:
//			break;
//		
//	}
//}



void Sprite::update_on_screen_pos
	(const PrevCurrPair<bg_point>& camera_pos_pc_pair)
{
	vec2_f24p8 temp_on_screen_pos = get_on_screen_pos
		(camera_pos_pc_pair.curr);
	
	vec2_u32 ss_vec2 = get_shape_size_as_vec2();
	vec2_f24p8 offset(make_f24p8(ss_vec2.x), make_f24p8(ss_vec2.y));
	
	
	//// Round To the nearest whole number.
	s16 temp_x = temp_on_screen_pos.x.to_int_for_on_screen();
	s16 temp_y = temp_on_screen_pos.y.to_int_for_on_screen();
	
	//if (the_sprite_type == StPlayer)
	//{
	//	show_debug_s32_group(the_oam_entry.get_x_coord(),
	//		the_oam_entry.get_y_coord());
	//}
	the_oam_entry.set_x_coord(temp_x);
	the_oam_entry.set_y_coord(temp_y);
	
	//if (the_sprite_type == StPlayer)
	//{
	//	show_debug_s32_group(the_oam_entry.get_x_coord(),
	//		the_oam_entry.get_y_coord());
	//}
	
	
	// Check whether the Sprite Is on screen.
	if (temp_on_screen_pos.x + offset.x >= (Fixed24p8){0} 
		&& temp_on_screen_pos.x <= make_f24p8(SCREEN_WIDTH)
		&& temp_on_screen_pos.y + offset.y >= (Fixed24p8){0}
		&& temp_on_screen_pos.y <= make_f24p8(SCREEN_HEIGHT))
	{
		the_oam_entry.show_non_affine();
	}
	else
	{
		// Hide the Sprite if it's not on screen
		the_oam_entry.hide_non_affine();
	}
}


void Sprite::camera_follow_basic
	(PrevCurrPair<bg_point>& camera_pos_pc_pair)
{
	bg_point& camera_pos = camera_pos_pc_pair.curr;
	
	const Fixed24p8 
		left_limit = make_f24p8(100), 
		
		right_limit = make_f24p8(140), 
		
		top_limit = make_f24p8(20), 
		//top_limit = make_f24p8(28), 
		//top_limit = make_f24p8(30), 
		//top_limit = make_f24p8(60), 
		
		bottom_limit = make_f24p8(60);
		//bottom_limit = make_f24p8(68);
		//bottom_limit = make_f24p8(70);
		//bottom_limit = make_f24p8(80);
	
	const Fixed24p8 to_add_abs = make_f24p8(4);
	
	vec2_f24p8 temp_on_screen_pos = get_on_screen_pos(camera_pos);
	vec2_f24p8 prev_on_screen_pos = get_prev_in_level_pos()
		- camera_pos_pc_pair.prev;
	
	Fixed24p8 on_screen_bottom_pos = temp_on_screen_pos.y 
		+ make_f24p8(get_shape_size_as_vec2().y);
	
	
	if ((temp_on_screen_pos.x <= left_limit && vel.x.data < 0) 
		|| (temp_on_screen_pos.x >= right_limit && vel.x.data > 0))
	{
		camera_pos.x += (get_curr_in_level_pos().x 
			- get_prev_in_level_pos().x);
	}
	
	bool do_update_camera_pos_y = false;
	bool add = false;
	
	if (temp_on_screen_pos.y <= top_limit)
	{
		do_update_camera_pos_y = true;
	}
	else if (on_screen_bottom_pos >= bottom_limit 
		&& !get_curr_on_slope())
	{
		if (vel.y >= (Fixed24p8){0})
		{
			add = true;
			do_update_camera_pos_y = true;
		}
	}
	else if (on_screen_bottom_pos <= bottom_limit && get_curr_on_slope())
	{
		do_update_camera_pos_y = true;
	}
	
	if (do_update_camera_pos_y)
	{
		if (!get_curr_on_ground() || (get_curr_on_ground() 
			&& get_curr_on_slope()))
		{
			camera_pos.y += (get_curr_in_level_pos().y 
				- get_prev_in_level_pos().y);
		}
		else
		{
			if (!add)
			{
				{
					camera_pos.y += -to_add_abs;
				}
			}
			else //if (add)
			{
				{
					camera_pos.y += to_add_abs;
				}
			}
		}
	}
	
}

void Sprite::center_camera_almost(bg_point& camera_pos) const
{
	//camera_pos.x = (in_level_pos.x 
	//	- (Fixed24p8){ SCREEN_WIDTH << 7 }).floor_to_int();
	//camera_pos.y = (in_level_pos.y 
	//	- (Fixed24p8){ SCREEN_HEIGHT << 7 }).floor_to_int();
	
	camera_pos.x = get_curr_in_level_pos().x 
		- (Fixed24p8){ SCREEN_WIDTH << 7 };
	camera_pos.y = get_curr_in_level_pos().y 
		- (Fixed24p8){ SCREEN_HEIGHT << 7 };
}




//void Sprite::block_collision_stuff()
//{
//	sprite_stuff_array[the_sprite_type]->block_collision_stuff(*this);
//}




vec2_u32 Sprite::get_shape_size_as_vec2_raw() const
{
	return OamEntry::ss_to_vec2_arr[the_shape_size];
} 

void Sprite::update_part_1()
{
	in_level_pos.back_up();
	on_ground.back_up();
	on_slope.back_up();
	
	set_curr_on_slope(false);
}

void Sprite::update_part_2()
{
	update_f24p8_positions();
	block_collision_stuff();
}


// The player_sprite_stuff class Is the primary user of this function.
void Sprite::update_part_3(PrevCurrPair<bg_point>& camera_pos_pc_pair, 
	const vec2_u32& the_level_size_2d)
{
}



void Sprite::update_part_3
	(const PrevCurrPair<bg_point>& camera_pos_pc_pair, 
	int& next_oam_index)
{
	gfx_update();
	
	
	update_on_screen_pos(camera_pos_pc_pair);
	
	copy_the_oam_entry_to_oam_mirror(next_oam_index++);
}


//const u32 Sprite::get_curr_tile_slot_old()
//{
//	return 
//		((GfxManager::sprite_palette_slot_first_vram_slot_list 
//		[get_palette_slot()] / sizeof(tile) * sizeof(u16))
//		+ get_curr_relative_tile_slot());
//}


// The reason this function takes a Sprite instance as a parameter Is That
// sprites may use different palettes depending on their state.
const sprite_palette_slot Sprite::get_palette_slot()
{
	return get_const_params().the_palette_slot;
}
const u32 Sprite::get_curr_relative_tile_slot()
{
	return get_const_params().the_relative_metatile_slot 
		* get_num_active_gfx_tiles();
}



// This used To be a dummy function That child classes would implement.
void Sprite::block_collision_stuff()
{
	//sprite_stuff_array[the_sprite_type]->block_collision_stuff(*this);
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


// This Is a dummy function That child classes implement (probably just
// player_sprite_stuff).
void Sprite::handle_jumping_stuff(u32 is_jump_key_hit, 
	u32 is_jump_key_held)
{
}



// 16x32 sprites
void Sprite::block_coll_response_left
	(const SprBlkCollGroupBase::HorizCollTuple& hs)
{
	push_out_of_left_block(hs.blk_crd_pos);
	
	// Don't let the Sprite speed up while in the air and horizontally
	// colliding with a Block.
	if (!get_curr_on_ground() && vel.x < (Fixed24p8){0x00})
	{
		vel.x = {0x00};
	}
}
void Sprite::block_coll_response_right
	(const SprBlkCollGroupBase::HorizCollTuple& hs)
{
	push_out_of_right_block(hs.blk_crd_pos);
	
	// Don't let the Sprite speed up while in the air and horizontally
	// colliding with a Block.
	if (!get_curr_on_ground() && vel.x > (Fixed24p8){0x00})
	{
		vel.x = {0x00};
	}
}
void Sprite::block_coll_response_top
	(const SprBlkCollGroupBase::VertTopCollTuple& vs)
{
	push_out_of_top_block(vs.blk_crd_pos);
	
	if (vel.y < (Fixed24p8){0x00})
	{
		vel.y = {0x00};
	}
	is_jumping = false;
}
void Sprite::block_coll_response_bot
	(const BcrLsegGroup& the_bcr_lseg_grp)
{
	if (vel.y >= (Fixed24p8){0})
	{
		push_out_of_bot_block(the_bcr_lseg_grp);
		
		vel.y = {0x00};
		set_curr_on_ground(true);
		is_jumping = false;
	}
}
void Sprite::block_coll_response_bot_slope(s32 height_val, 
	s32 blk_crd_y_pos)
{
	if (vel.y >= (Fixed24p8){0})
	{
		push_out_of_bot_slope_block(height_val, blk_crd_y_pos);
		
		vel.y = {0x00};
		set_curr_on_ground(true);
		set_curr_on_slope(true);
		is_jumping = false;
	}
}

void Sprite::apply_gravity()
{
	vel.y += grav_acc;
	
	if (vel.y > max_y_vel)
	{
		vel.y = max_y_vel;
	}
}

// Sprite-Sprite interaction stuff
void Sprite::sprite_interaction_reponse(Sprite& the_other_sprite)
{
	
}

// the_player Is the primary user of this function
void Sprite::sprite_interaction_reponse(Sprite& the_other_sprite, 
	PrevCurrPair<bg_point>& camera_pos_pc_pair, 
	const vec2_u32& the_level_size_2d)
{
	
}

//SprBlkCollGroup16x32 clseg_grp __attribute__((_EWRAM));
const size_t clseg_grp_16x32_size = sizeof(SprBlkCollGroup16x32);


void Sprite::generic_block_collision_stuff
	(SprBlkCollGroupBase& clseg_grp)
{
	static const size_t num_horiz_ctups 
		= clseg_grp.get_num_horiz_ctups();
	static const size_t num_vert_top_ctups 
		= clseg_grp.get_num_vert_top_ctups();
	static const size_t num_vert_bot_ctups 
		= clseg_grp.get_num_vert_bot_ctups();
	
	static const u32 hi_left_top = clseg_grp.get_hi_left_top();
	static const u32 hi_left_bot = clseg_grp.get_hi_left_bot();
	static const u32 hi_right_top = clseg_grp.get_hi_right_top();
	static const u32 hi_right_bot = clseg_grp.get_hi_right_bot();
	
	static const u32 vi_top_left = clseg_grp.get_vi_top_left();
	static const u32 vi_top_right = clseg_grp.get_vi_top_right();
	
	
	
	static constexpr u32 vi_bot_left = clseg_grp.vi_bot_left;
	static constexpr u32 vi_bot_mid = clseg_grp.vi_bot_mid;
	static constexpr u32 vi_bot_right = clseg_grp.vi_bot_right;
	
	
	
	//BlockCollResult horiz_fs_ret_buf[num_horiz_ctups];
	//BlockCollResult* vert_top_fs_ret_buf[num_vert_top_ctups];
	//BlockCollResult* vert_top_slp_ret_buf[num_vert_top_ctups];
	BlockCollResult* vert_bot_fs_ret_buf[num_vert_bot_ctups];
	BlockCollResult* vert_bot_slp_ret_buf[num_vert_bot_ctups];
	
	//vec2_s32 horiz_fs_pos_buf[num_horiz_ctups];
	//vec2_s32 vert_top_fs_pos_buf[num_vert_top_ctups];
	//vec2_s32 vert_top_slp_pos_buf[num_vert_top_ctups];
	vec2_s32 vert_bot_fs_pos_buf[num_vert_bot_ctups];
	vec2_s32 vert_bot_slp_pos_buf[num_vert_bot_ctups];
	
	auto iterate_horiz = [&](const u32 first, const u32 last,
		bool& some_horiz_side_fully_solid) -> void
	{
		for (u32 i=first; i<=last; ++i)
		{
			//horiz_fs_ret_buf[i] = clseg_grp.get_horiz_ctup(i).bcrlg
			//	.horiz_any_bbvt_is_fully_solid(horiz_fs_pos_buf[i]);
			//
			//if (horiz_fs_ret_buf[i])
			//{
			//	some_horiz_side_fully_solid = true;
			//}
			if (bbvt_is_fully_solid(clseg_grp.get_horiz_ctup(i).bcr
				.get_bbvt()))
			{
				some_horiz_side_fully_solid = true;
				return;
			}
		}
	};
	
	auto iterate_vert_top = [&](bool& some_top_side_fully_solid, 
		bool& some_top_side_slope) -> void
	{
		for (u32 i=vi_top_left; i<=vi_top_right; ++i)
		{
			//vert_top_fs_ret_buf[i] = clseg_grp.get_vert_top_ctup(i).bcrlg
			//	.vert_any_bbvt_is_fully_solid(vert_top_fs_pos_buf[i]);
			//vert_top_slp_ret_buf[i] = clseg_grp.get_vert_top_ctup(i).bcrlg
			//	.vert_any_bbvt_is_slope(vert_top_slp_pos_buf[i]);
			//
			//if (vert_top_fs_ret_buf[i])
			//{
			//	some_top_side_fully_solid = true;
			//}
			//if (vert_top_slp_ret_buf[i])
			//{
			//	some_top_side_slope = true;
			//}
			
			if (bbvt_is_fully_solid(clseg_grp.get_vert_top_ctup(i).bcr
				.get_bbvt()))
			{
				some_top_side_fully_solid = true;
			}
			if (bbvt_is_slope(clseg_grp.get_vert_top_ctup(i).bcr
				.get_bbvt()))
			{
				some_top_side_slope = true;
			}
		}
	};
	
	auto iterate_vert_bot = [&](bool& some_bot_side_fully_solid, 
		bool& some_bot_side_slope) -> void
	{
		u32 i;
		for (i=vi_bot_mid; i<vi_bot_left; ++i)
		{
			vert_bot_fs_ret_buf[i] = clseg_grp.get_vert_bot_ctup(i).bcrlg
				.vert_any_bbvt_is_fully_solid(vert_bot_fs_pos_buf[i]);
			vert_bot_slp_ret_buf[i] = clseg_grp.get_vert_bot_ctup(i).bcrlg
				.vert_any_bbvt_is_slope(vert_bot_slp_pos_buf[i]);
			
			if (vert_bot_fs_ret_buf[i])
			{
				some_bot_side_fully_solid = true;
			}
			if (vert_bot_slp_ret_buf[i])
			{
				some_bot_side_slope = true;
			}
		}
		for (; i<=vi_bot_right; ++i)
		{
			vert_bot_slp_ret_buf[i] = clseg_grp.get_vert_bot_ctup(i).bcrlg
				.vert_any_bbvt_is_slope(vert_bot_slp_pos_buf[i]);
			
			if (vert_bot_slp_ret_buf[i])
			{
				some_bot_side_slope = true;
			}
		}
	};
	
	auto get_height_mask_index = [&](u32 vs_index) -> u32
	{
		return conv_pix_crd_to_blk_local_crd(clseg_grp.get_vert_bot_ctup
			(vs_index).clseg.top_pt().x.floor_to_int());
	};
	
	auto get_slope_bcr = [&](u32 vs_index) -> BlockCollResult*
	{
		return vert_bot_slp_ret_buf[vs_index];
	};
	
	auto get_slope_height_val = [&](u32 vs_index, 
		const u32 height_mask_index) -> s32
	{
		return (BlockBaseStuff::height_mask_ptr_arr[get_slope_bcr
			(vs_index)->the_bbvt])[height_mask_index];
	};
	
	auto get_slope_height_val_with_bbvt = [&]
		(block_behavior_type some_bbvt, const u32 height_mask_index) 
		-> s32
	{
		return (BlockBaseStuff::height_mask_ptr_arr[some_bbvt])
			[height_mask_index];
	};
	
	auto assign_slope_height_val_and_y_pos = [&]
		(s32& height_val, s32& hv_vs_blk_crd_y_pos, 
		const s32 temp_height_val, const vec2_s32& pos) -> void
	{
		//const s32 temp_pix_crd_y_pos = conv_blk_crd_to_pix_crd(pos.y)
		//	+ conv_slp_height_val_to_offset(temp_height_val);
		const s32 temp_pix_crd_y_pos = conv_blk_crd_to_pix_crd(pos.y + 1)
			- temp_height_val;
		
		//if (!get_curr_on_ground())
		//{
		//	show_debug_s32_group(temp_pix_crd_y_pos);
		//	show_debug_s32_group(clseg_grp.get_vert_bot_ctup(vi_bot_mid)
		//		.clseg.bot_pt().y.floor_to_int());
		//}
		
		// Prevent instantly teleporting downwards when in the air
		//if (get_curr_on_ground() 
		//	|| clseg_grp.get_vert_bot_ctup(vi_bot_mid).clseg.bot_pt().y 
		//	>= (make_f24p8(temp_pix_crd_y_pos + 1)))
		if (get_curr_on_ground() 
			|| (clseg_grp.get_vert_bot_ctup(vi_bot_mid).clseg.bot_pt().y
			.floor_to_int()) >= (temp_pix_crd_y_pos))
		{
			height_val = temp_height_val;
			hv_vs_blk_crd_y_pos = pos.y;
		}
	};
	
	auto exec_bot_collision_stuff = [&]
		(const bool some_bot_side_fully_solid,
		const bool some_bot_side_slope) -> bool
	{
		// Handle slopes in a special way
		if (some_bot_side_slope)
		{
			s32 height_val = -1;
			s32 hv_vs_blk_crd_y_pos = 9001;
			
			const bool vs_bot_mid_intersects_fs
				= (vert_bot_fs_ret_buf[vi_bot_mid] != NULL);
			
			const u32 height_mask_index_buf[num_vert_bot_ctups]
				= { get_height_mask_index(vi_bot_mid),
				get_height_mask_index(vi_bot_left),
				get_height_mask_index(vi_bot_right) };
			
			
			const vec2_s32& mid_pos = vert_bot_slp_pos_buf[vi_bot_mid];
			const vec2_s32& left_pos = vert_bot_slp_pos_buf[vi_bot_left];
			const vec2_s32& right_pos = vert_bot_slp_pos_buf[vi_bot_right];
			//conv_blk_crd_to_pix_crd
			
			if (vert_bot_slp_ret_buf[vi_bot_mid])
			{
				const s32 temp_height_val = get_slope_height_val
					(vi_bot_mid, height_mask_index_buf[vi_bot_mid]);
				
				assign_slope_height_val_and_y_pos(height_val, 
					hv_vs_blk_crd_y_pos, temp_height_val, mid_pos);
			}
			else // if (!vert_bot_slp_ret_buf[vi_bot_mid])
			{
				if (!vs_bot_mid_intersects_fs)
				{
					// Slightly wasteful
					s32 height_val_buf[num_vert_bot_ctups] 
						= { -1, -1, -1 };
					for (u32 i=vi_bot_left; i<=vi_bot_right; ++i)
					{
						if (vert_bot_slp_ret_buf[i])
						{
							height_val_buf[i] = get_slope_height_val(i,
								height_mask_index_buf[i]);
						}
					}
					
					// Still use the height mask from the slope Block That
					// WOULD have been intersected by the middle sensor if
					// the slope was continuous
					
					block_behavior_type temp_bbvt;
					s32 temp_blk_crd_y_pos_offset;
					
					auto left_slope_response = [&]() -> void
					{
						// The main trick:  force usage of the bottom
						// MIDDLE vertical sensor's Level coordinates x
						// position, and also use the specific height mask
						// That would be EXPECTED To be used if the slope
						// were continuous
						if (get_right_following_slope_bbvt
							(get_slope_bcr(vi_bot_left)->get_bbvt(), 
							temp_bbvt, temp_blk_crd_y_pos_offset))
						{
							const s32 temp_height_val 
								= get_slope_height_val_with_bbvt
								(temp_bbvt,
								height_mask_index_buf[vi_bot_mid]);
							
							assign_slope_height_val_and_y_pos(height_val, 
								hv_vs_blk_crd_y_pos, temp_height_val, 
								left_pos + vec2_s32(0, 
								temp_blk_crd_y_pos_offset));
						}
						else
						{
							//show_debug_s32_group(9001);
						}
					};
					
					auto right_slope_response = [&]() -> void
					{
						// The main trick:  force usage of the bottom
						// MIDDLE vertical sensor's Level coordinates x
						// position, and also use the specific height mask
						// That would be EXPECTED To be used if the slope
						// were continuous
						if (get_left_following_slope_bbvt
							(get_slope_bcr(vi_bot_right)->get_bbvt(), 
							temp_bbvt, temp_blk_crd_y_pos_offset))
						{
							const s32 temp_height_val 
								= get_slope_height_val_with_bbvt
								(temp_bbvt,
								height_mask_index_buf[vi_bot_mid]);
							
							assign_slope_height_val_and_y_pos(height_val, 
								hv_vs_blk_crd_y_pos, temp_height_val, 
								right_pos + vec2_s32(0, 
								temp_blk_crd_y_pos_offset));
						}
						else
						{
							//show_debug_s32_group(9002);
						}
					};
					
					// Figure out the tallest total height value, which
					// includes the Block's position
					if (vert_bot_slp_ret_buf[vi_bot_left] 
						&& !vert_bot_slp_ret_buf[vi_bot_right])
					{
						left_slope_response();
					}
					
					else if (!vert_bot_slp_ret_buf[vi_bot_left]
						&& vert_bot_slp_ret_buf[vi_bot_right])
					{
						right_slope_response();
					}
					
					// Use the tallest height value there Is, including the
					// y position of the slope bcr
					else // if (vert_bot_slp_ret_buf[vi_bot_left]
						// && vert_bot_slp_ret_buf[vi_bot_right])
					{
						// Prioritize Block y positions (use ones That are
						// technically at a LOWER y position (though That
						// appear To be at a HIGHER y position))
						if (left_pos.y < right_pos.y)
						{
							left_slope_response();
						}
						else if (left_pos.y > right_pos.y)
						{
							right_slope_response();
						}
						
						// If the y positions are equal, then clearly the
						// plain old height value should be used for
						// comparison
						else // if (left_pos.y == right_pos.y)
						{
							if (height_val_buf[vi_bot_left] 
								> height_val_buf[vi_bot_right])
							{
								left_slope_response();
							}
							else // if (height_val_buf[vi_bot_left] 
								// <= height_val_buf[vi_bot_right] )
							{
								right_slope_response();
							}
						}
					}
				}
				else // if (vs_bot_mid_intersects_fs)
				{
					// This calls set_curr_on_ground(true)
					block_coll_response_bot(clseg_grp
						.get_vert_bot_ctup(vi_bot_left).bcrlg);
					return true;
				}
			}
			
			if (height_val != -1)
			{
				// This calls set_curr_on_ground(true)
				block_coll_response_bot_slope(height_val, 
					hv_vs_blk_crd_y_pos);
				return true;
			}
		}
		else
		{
			set_curr_on_slope(false);
			
			// The Sprite Is now in air if there are no relevant blocks
			// intersected by the vertical sensors
			if (!some_bot_side_fully_solid)
			{
				//// This needs To be turned back on eventually
				set_curr_on_ground(false);
				return false;
			}
			else // if (some_bot_side_fully_solid)
			{
				// This calls set_curr_on_ground(true)
				block_coll_response_bot(clseg_grp.get_vert_bot_ctup
					(vi_bot_left).bcrlg);
				return true;
			}
		}
		
		return false;
	};
	
	if (get_curr_on_ground())
	{
		bool left_side_fully_solid_og = false, 
			right_side_fully_solid_og = false,
			top_side_fully_solid_og = false,
			top_side_slope_og = false,
			bot_side_fully_solid_og = false,
			bot_side_slope_og = false;
		
		
		iterate_horiz(hi_left_top, hi_left_bot, 
			left_side_fully_solid_og);
		iterate_horiz(hi_right_top, hi_right_bot, 
			right_side_fully_solid_og);
		
		iterate_vert_bot(bot_side_fully_solid_og, bot_side_slope_og);
		
		
		// (Temporarily (?)) permit walking through the vertical side of
		// slopes
		if (left_side_fully_solid_og && !right_side_fully_solid_og)
		{
			block_coll_response_left(clseg_grp.get_horiz_ctup
				(hi_left_top));
		}
		
		else if (!left_side_fully_solid_og && right_side_fully_solid_og)
		{
			block_coll_response_right(clseg_grp.get_horiz_ctup
				(hi_right_top));
		}
		
		//iterate_vert_top(top_side_fully_solid_og, top_side_slope_og);
		//if (top_side_fully_solid_og || top_side_slope_og)
		//{
		//	block_coll_response_top(clseg_grp.get_vert_top_ctup
		//		(vi_top_left));
		//}
		
		exec_bot_collision_stuff(bot_side_fully_solid_og,
			bot_side_slope_og);
	}
	else // if (!get_curr_on_ground())
	{
		// Don't forget To remove the code at the top of this function That
		// sets on_ground.curr To true every time!
		
		bool left_side_fully_solid_ia = false, 
			right_side_fully_solid_ia = false,
			top_side_fully_solid_ia = false,
			top_side_slope_ia = false,
			bot_side_fully_solid_ia = false,
			bot_side_slope_ia = false;
		
		
		iterate_horiz(hi_left_top, hi_left_bot, 
			left_side_fully_solid_ia);
		iterate_horiz(hi_right_top, hi_right_bot, 
			right_side_fully_solid_ia);
		iterate_vert_top(top_side_fully_solid_ia, top_side_slope_ia);
		
		iterate_vert_bot(bot_side_fully_solid_ia, bot_side_slope_ia);
		
		
		
		// (Temporarily (?)) permit walking through the vertical side of
		// slopes
		if (left_side_fully_solid_ia && !right_side_fully_solid_ia)
		{
			block_coll_response_left(clseg_grp.get_horiz_ctup
				(hi_left_top));
		}
		
		else if (!left_side_fully_solid_ia && right_side_fully_solid_ia)
		{
			block_coll_response_right(clseg_grp.get_horiz_ctup
				(hi_right_top));
		}
		
		if ((top_side_fully_solid_ia) || (top_side_slope_ia 
			&& !bot_side_slope_ia))
		{
			//if (!clseg_grp.get_size_is_tiny().y 
			//	|| !get_prev_on_ground())
			{
				block_coll_response_top(clseg_grp.get_vert_top_ctup
					(vi_top_left));
			}
		}
		
		exec_bot_collision_stuff(bot_side_fully_solid_ia,
			bot_side_slope_ia);
	}
	
	////vel.x.data += clg_16x32_size;
	//vel += clseg_grp.horiz_clseg_groups[clseg_grp.hi_left_top].left_pt();
}

SprBlkCollGroup16x16 temp_clseg_grp_16x16 __attribute__((_IWRAM));
SprBlkCollGroup16x32 temp_clseg_grp_16x32 __attribute__((_IWRAM));

void Sprite::block_collision_stuff_16x16()
{
	//SprBlkCollGroup16x16 clseg_grp(the_coll_box, get_curr_on_ground());
	//
	//generic_block_collision_stuff(clseg_grp);
	temp_clseg_grp_16x16.init(the_coll_box, get_curr_on_ground());
	generic_block_collision_stuff(temp_clseg_grp_16x16);
}
void Sprite::block_collision_stuff_16x32()
{
	//SprBlkCollGroup16x32 clseg_grp(the_coll_box, get_curr_on_ground());
	//
	//generic_block_collision_stuff(clseg_grp);
	
	temp_clseg_grp_16x32.init(the_coll_box, get_curr_on_ground());
	generic_block_collision_stuff(temp_clseg_grp_16x32);
}

// block_collision_stuff_32x16() will likely never be used because it's
// less believable for one of those To not rotate when on a slope
void Sprite::block_collision_stuff_32x16()
{
	
}
void Sprite::block_collision_stuff_32x32()
{
	
}
