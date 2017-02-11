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


#include "sprite_class.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../gfx_manager_class.hpp"

#include "sprite_allocator_class.hpp"

#include "../../general_utility_stuff/misc_utility_funcs.hpp"

#include "../level_stuff/active_level_class.hpp"

#include "sprite_manager_class.hpp"
#include "../../gba_specific_stuff/button_stuff.hpp"

#include "../level_stuff/sublevel_class.hpp"
#include "../coll_lseg_classes.hpp"


const sprite_const_params sprite::the_const_params;

const fixed24p8 sprite::cpg_on_slope_threshold_abs = {0x400};

// coll_point_group threshold
const vec2_f24p8 sprite::cpg_16x32_threshold_abs = { {0x400}, 
	{0x480} };

//const fixed24p8 sprite::grav_acc = {0x80};
//const fixed24p8 sprite::grav_acc = {0x40};
//const fixed24p8 sprite::grav_acc = {0x60};
const fixed24p8 sprite::grav_acc = {0x50};
//const fixed24p8 sprite::max_y_vel = {0x400};
const fixed24p8 sprite::max_y_vel = {0x300};
//const fixed24p8 sprite::max_y_vel = {0x280};



vec2_f24p8 sprite::prev_prev_on_screen_pos; 
prev_curr_pair<vec2_f24p8> sprite::on_screen_pos;
vec2_s32 sprite::prev_prev_on_screen_pos_s32;
prev_curr_pair<vec2_s32> sprite::on_screen_pos_s32;
prev_curr_pair<vec2_s32> sprite::camera_pos_pc_pair_s32;

vec2<bool> sprite::temp_debug_thing;

vec2_f24p8 sprite::on_screen_pos_diff_abs;
vec2_s32 sprite::on_screen_pos_s32_diff_abs;
vec2_f24p8 sprite::camera_pos_diff_abs;
vec2_s32 sprite::camera_pos_s32_diff_abs;
//prev_curr_pair<s32> sprite::tallest_height_val;


sprite::sprite()
{
	shared_constructor_code_part_1();
}
sprite::sprite( bool facing_left )
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2(facing_left);
}
sprite::sprite( const vec2_f24p8& s_in_level_pos, 
	const prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left )
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2( s_in_level_pos, camera_pos_pc_pair, 
		facing_left );
}
sprite::sprite( const vec2_f24p8& s_in_level_pos, 
	const vec2_u32& the_level_size_2d, 
	prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left )
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2( s_in_level_pos, the_level_size_2d, 
		camera_pos_pc_pair, facing_left );
}


void sprite::shared_constructor_code_part_1()
{
	// uh-oh, it looks like this overwrites the vtable pointer for the
	// sprite!
	//memfill32( this, 0, sizeof(sprite) / sizeof(u32) );
	
	the_sprite_type = get_const_sprite_type();;
	the_sprite_ipg = NULL;
	
	memfill32( &the_oam_entry, 0, sizeof(oam_entry) / sizeof(u32) );
	
	
	set_initial_shape_size();
	the_oam_entry.set_tile_number(get_curr_tile_slot());
	the_oam_entry.set_pal_number(get_palette_slot());
	
	clear_and_set_bits( the_oam_entry.attr2, obj_attr2_prio_mask, 
		obj_attr2_prio_1 );
	
	in_level_pos.prev = vec2_f24p8( (fixed24p8){0}, (fixed24p8){0} );
	in_level_pos.curr = vel = in_level_pos.prev;
	
	max_vel_x_abs_val = accel_x = (fixed24p8){0};
	
	set_initial_coll_box_stuff();
	
	on_ground.prev = on_ground.curr = is_jumping = false;
	
	invin_frame_timer = 0;
	
	arr_memfill32( misc_data_u, 0, misc_data_size * 2 );
	
	//vram_chunk_index = old_vram_chunk_index;
	
	
	update_f24p8_positions();
}
void sprite::shared_constructor_code_part_2( bool facing_left )
{
	if ( facing_left )
	{
		the_oam_entry.enable_hflip();
	}
}


void sprite::shared_constructor_code_part_2
	( const vec2_f24p8& s_in_level_pos, 
	const prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left )
{
	shared_constructor_code_part_2(facing_left);
	//in_level_pos.curr = s_in_level_pos 
	//	- get_the_initial_in_level_pos_offset();
	set_curr_in_level_pos( s_in_level_pos 
		- get_the_initial_in_level_pos_offset() );
	
	update_f24p8_positions();
	update_on_screen_pos(camera_pos_pc_pair);
}


// This form of shared_constructor_code() is primarily intended to be
// used by the_player.
void sprite::shared_constructor_code_part_2
	( const vec2_f24p8& s_in_level_pos, const vec2_u32& the_level_size_2d, 
	prev_curr_pair<bg_point>& camera_pos_pc_pair, bool facing_left )
{
	shared_constructor_code_part_2(facing_left);
	//in_level_pos = s_in_level_pos - get_the_initial_in_level_pos_offset();
	set_curr_in_level_pos( s_in_level_pos 
		- get_the_initial_in_level_pos_offset() );
	
	
	update_f24p8_positions();
	update_on_screen_pos(camera_pos_pc_pair);
}

void sprite::shared_constructor_code_part_3()
{
	debug_arr_group::debug_f8p8_arr_helper.at(0) = make_f8p8(3);
}

void* sprite::operator new( size_t size, 
	sprite_allocator& the_sprite_allocator )
{
	return the_sprite_allocator.allocate_sprite();
}


//sprite::sprite( u32 s_vram_chunk_index, 
//	sprite_init_param_group* s_the_sprite_ipg )
//{
//	switch ( s_the_sprite_ipg->spawn_state )
//	{
//		case sss_not_active:
//			memfill32( this, 0, sizeof(sprite) / sizeof(u32) );
//			
//			the_sprite_ipg = s_the_sprite_ipg;
//			the_sprite_ipg->spawn_state = sss_active;
//			
//			the_sprite_type = the_sprite_ipg->type;
//			in_level_pos.x = make_f24p8
//				( the_sprite_ipg->initial_block_grid_x_coord * 16 );
//			in_level_pos.y = make_f24p8
//				( the_sprite_ipg->initial_block_grid_y_coord * 16 );
//			
//			sprite_stuff_array[the_sprite_type]->shared_constructor_code( *this, 
//				!the_sprite_ipg->facing_right );
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



void sprite::update_on_screen_pos
	( const prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	vec2_f24p8 temp_on_screen_pos = get_on_screen_pos
		(camera_pos_pc_pair.curr);
	
	vec2_u32 ss_vec2 = get_shape_size_as_vec2();
	vec2_f24p8 offset( make_f24p8(ss_vec2.x), make_f24p8(ss_vec2.y) );
	
	
	//// Round to the nearest whole number.
	s16 temp_x = temp_on_screen_pos.x.to_int_for_on_screen();
	s16 temp_y = temp_on_screen_pos.y.to_int_for_on_screen();
	
	the_oam_entry.set_x_coord(temp_x);
	the_oam_entry.set_y_coord(temp_y);
	
	
	// Check whether the sprite is on screen.
	if ( temp_on_screen_pos.x + offset.x >= (fixed24p8){0} 
		&& temp_on_screen_pos.x <= make_f24p8(screen_width)
		&& temp_on_screen_pos.y + offset.y >= (fixed24p8){0}
		&& temp_on_screen_pos.y <= make_f24p8(screen_height) )
	{
		the_oam_entry.show_non_affine();
	}
	else
	{
		// Hide the sprite if it's not on screen
		the_oam_entry.hide_non_affine();
	}
}


void sprite::camera_follow_basic
	( prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	bg_point& camera_pos = camera_pos_pc_pair.curr;
	
	const fixed24p8 
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
	
	const fixed24p8 to_add_abs = make_f24p8(4);
	
	vec2_f24p8 temp_on_screen_pos = get_on_screen_pos(camera_pos);
	vec2_f24p8 prev_on_screen_pos = get_prev_in_level_pos()
		- camera_pos_pc_pair.prev;
	
	fixed24p8 on_screen_bottom_pos = temp_on_screen_pos.y 
		+ make_f24p8(get_shape_size_as_vec2().y);
	
	
	if ( ( temp_on_screen_pos.x <= left_limit && vel.x.data < 0 ) 
		|| ( temp_on_screen_pos.x >= right_limit && vel.x.data > 0 ) )
	{
		camera_pos.x += ( get_curr_in_level_pos().x 
			- get_prev_in_level_pos().x );
	}
	
	bool do_update_camera_pos_y = false;
	bool add = false;
	
	if ( temp_on_screen_pos.y <= top_limit )
	{
		do_update_camera_pos_y = true;
	}
	else if ( on_screen_bottom_pos >= bottom_limit 
		&& !get_curr_on_slope() )
	{
		if ( vel.y >= (fixed24p8){0} )
		{
			add = true;
			do_update_camera_pos_y = true;
		}
	}
	else if ( on_screen_bottom_pos <= bottom_limit && get_curr_on_slope() )
	{
		do_update_camera_pos_y = true;
	}
	
	if ( do_update_camera_pos_y )
	{
		if ( !get_curr_on_ground() || ( get_curr_on_ground() 
			&& get_curr_on_slope() ) )
		{
			camera_pos.y += ( get_curr_in_level_pos().y 
				- get_prev_in_level_pos().y );
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

void sprite::center_camera_almost( bg_point& camera_pos ) const
{
	//camera_pos.x = ( in_level_pos.x 
	//	- (fixed24p8){ screen_width << 7 } ).floor_to_int();
	//camera_pos.y = ( in_level_pos.y 
	//	- (fixed24p8){ screen_height << 7 } ).floor_to_int();
	
	camera_pos.x = get_curr_in_level_pos().x 
		- (fixed24p8){ screen_width << 7 };
	camera_pos.y = get_curr_in_level_pos().y 
		- (fixed24p8){ screen_height << 7 };
}




//void sprite::block_collision_stuff()
//{
//	sprite_stuff_array[the_sprite_type]->block_collision_stuff(*this);
//}




vec2_u32 sprite::get_shape_size_as_vec2_raw() const
{
	return oam_entry::ss_to_vec2_arr[the_shape_size];
} 

void sprite::update_part_1()
{
	in_level_pos.back_up();
	on_ground.back_up();
	on_slope.back_up();
	
	set_curr_on_slope(false);
}

void sprite::update_part_2()
{
	update_f24p8_positions();
	block_collision_stuff();
}


// The player_sprite_stuff class is the primary user of this function.
void sprite::update_part_3( prev_curr_pair<bg_point>& camera_pos_pc_pair, 
	const vec2_u32& the_level_size_2d )
{
}



void sprite::update_part_3
	( const prev_curr_pair<bg_point>& camera_pos_pc_pair, 
	int& next_oam_index )
{
	gfx_update();
	
	
	update_on_screen_pos(camera_pos_pc_pair);
	
	copy_the_oam_entry_to_oam_mirror(next_oam_index++);
}


//const u32 sprite::get_curr_tile_slot_old()
//{
//	return 
//		( ( gfx_manager::sprite_palette_slot_first_vram_slot_list 
//		[get_palette_slot()] / sizeof(tile) * sizeof(u16) )
//		+ get_curr_relative_tile_slot() );
//}


// The reason this function takes a sprite instance as a parameter is that
// sprites may use different palettes depending on their state.
const sprite_palette_slot sprite::get_palette_slot()
{
	return get_const_params().the_palette_slot;
}
const u32 sprite::get_curr_relative_tile_slot()
{
	return get_const_params().the_relative_metatile_slot 
		* get_num_active_gfx_tiles();
}



// This used to be a dummy function that child classes would implement.
void sprite::block_collision_stuff()
{
	//sprite_stuff_array[the_sprite_type]->block_collision_stuff(*this);
	if ( the_coll_box.size.x >= make_f24p8(0)
		&& the_coll_box.size.x <= make_f24p8(16)
		&& the_coll_box.size.y > make_f24p8(16 )
		&& the_coll_box.size.y <= make_f24p8(32) )
	{
		block_collision_stuff_16x32();
	}
	else
	{
		block_collision_stuff_16x16();
	}
}


// This is a dummy function that child classes implement (probably just
// player_sprite_stuff).
void sprite::handle_jumping_stuff( u32 is_jump_key_hit, 
	u32 is_jump_key_held )
{
}



void sprite::block_coll_response_left_16x16
	( const bcr_lseg_group& the_bcr_lseg_grp )
{
	push_out_of_left_block(the_bcr_lseg_grp);
	
	// Don't let the sprite speed up while in the air and horizontally
	// colliding with a block.
	if ( !get_curr_on_ground() && vel.x < (fixed24p8){0x00} )
	{
		vel.x = {0x00};
	}
}

void sprite::block_coll_response_right_16x16
	( const bcr_lseg_group& the_bcr_lseg_grp )
{
	push_out_of_right_block(the_bcr_lseg_grp);
	
	// Don't let the sprite speed up while in the air and horizontally
	// colliding with a block.
	if ( !get_curr_on_ground() && vel.x > (fixed24p8){0x00} )
	{
		vel.x = {0x00};
	}
}

void sprite::block_coll_response_top_16x16
	( const bcr_lseg_group& the_bcr_lseg_grp )
{
	push_out_of_top_block(the_bcr_lseg_grp);
	
	if ( vel.y < (fixed24p8){0x00} )
	{
		vel.y = {0x00};
	}
	//jump_hold_timer = 0;
	is_jumping = false;
}

void sprite::block_coll_response_bot_16x16
	( const bcr_lseg_group& the_bcr_lseg_grp )
{
	if ( vel.y >= (fixed24p8){0} )
	{
		push_out_of_bot_block(the_bcr_lseg_grp);
		
		vel.y = {0x00};
		set_curr_on_ground(true);
		is_jumping = false;
	}
}


// 16x32 sprites
void sprite::block_coll_response_left_16x32
	( const bcr_lseg_group& the_bcr_lseg_grp )
{
	push_out_of_left_block(the_bcr_lseg_grp);
	
	// Don't let the sprite speed up while in the air and horizontally
	// colliding with a block.
	if ( !get_curr_on_ground() && vel.x < (fixed24p8){0x00} )
	{
		vel.x = {0x00};
	}
}
void sprite::block_coll_response_right_16x32
	( const bcr_lseg_group& the_bcr_lseg_grp )
{
	push_out_of_right_block(the_bcr_lseg_grp);
	
	// Don't let the sprite speed up while in the air and horizontally
	// colliding with a block.
	if ( !get_curr_on_ground() && vel.x > (fixed24p8){0x00} )
	{
		vel.x = {0x00};
	}
}
void sprite::block_coll_response_top_16x32
	( const bcr_lseg_group& the_bcr_lseg_grp )
{
	push_out_of_top_block(the_bcr_lseg_grp);
	
	if ( vel.y < (fixed24p8){0x00} )
	{
		vel.y = {0x00};
	}
	is_jumping = false;
}
void sprite::block_coll_response_bot_16x32
	( const bcr_lseg_group& the_bcr_lseg_grp )
{
	if ( vel.y >= (fixed24p8){0} )
	{
		push_out_of_bot_block(the_bcr_lseg_grp);
		
		vel.y = {0x00};
		set_curr_on_ground(true);
		is_jumping = false;
	}
}
void sprite::block_coll_response_bot_slope_16x32
	(  s32 tallest_height_val, const vec2_s32& pos )
{
	if ( vel.y >= (fixed24p8){0} )
	{
		push_out_of_bot_slope_block( tallest_height_val, pos );
		
		vel.y = {0x00};
		set_curr_on_ground(true);
		set_curr_on_slope(true);
		is_jumping = false;
	}
}

void sprite::apply_gravity()
{
	vel.y += grav_acc;
	
	if ( vel.y > max_y_vel )
	{
		vel.y = max_y_vel;
	}
}

// Sprite-sprite interaction stuff
void sprite::sprite_interaction_reponse( sprite& the_other_sprite )
{
	
}

// the_player is the primary user of this function
void sprite::sprite_interaction_reponse( sprite& the_other_sprite, 
	prev_curr_pair<bg_point>& camera_pos_pc_pair, 
	const vec2_u32& the_level_size_2d )
{
	
}

//coll_lseg_group_16x32 clseg_grp __attribute__((_ewram));
const size_t clseg_grp_16x32_size = sizeof(coll_lseg_group_16x32);


void sprite::block_collision_stuff_16x16()
{
	
}
void sprite::block_collision_stuff_16x32()
{
	//static coll_lseg_group_16x32 clseg_grp( the_coll_box, 
	//	get_curr_on_ground() ) __attribute__((_ewram));
	//static coll_lseg_group_16x32 clseg_grp __attribute__((_ewram));
	
	//coll_lseg_group_16x32 clseg_grp;
	
	// Don't forget to remove these two lines!
	set_curr_on_ground(true);
	vel.y = (fixed24p8){0};
	
	//clseg_grp.init( the_coll_box, get_curr_on_ground() );
	coll_lseg_group_16x32 clseg_grp( the_coll_box, get_curr_on_ground() );
	
	block_coll_result* horiz_fs_ret_buf[clseg_grp.num_horiz_ctups];
	block_coll_result* vert_fs_ret_buf[clseg_grp.num_vert_ctups];
	block_coll_result* vert_slp_ret_buf[clseg_grp.num_vert_ctups];
	
	vec2_s32 horiz_fs_pos_buf[clseg_grp.num_horiz_ctups];
	vec2_s32 vert_fs_pos_buf[clseg_grp.num_vert_ctups];
	vec2_s32 vert_slp_pos_buf[clseg_grp.num_vert_ctups];
	
	if ( get_curr_on_ground() )
	{
		s32 left_side_fully_solid_og = false, 
			right_side_fully_solid_og = false,
			bot_side_fully_solid_og = false,
			bot_side_slope_og = false;
		
		
		for ( u32 i=clseg_grp.the_hi_left_top_og; 
			i<=clseg_grp.the_hi_left_bot_og; 
			++i )
		{
			horiz_fs_ret_buf[i] = clseg_grp.get_horiz_ctup(i).bcrlg
				.horiz_any_bbvt_is_fully_solid(horiz_fs_pos_buf[i]);
			
			if (horiz_fs_ret_buf[i])
			{
				left_side_fully_solid_og = true;
			}
		}
		
		for ( u32 i=clseg_grp.the_hi_right_top_og;
			i<=clseg_grp.the_hi_right_bot_og;
			++i )
		{
			horiz_fs_ret_buf[i] = clseg_grp.get_horiz_ctup(i).bcrlg
				.horiz_any_bbvt_is_fully_solid(horiz_fs_pos_buf[i]);
			
			if (horiz_fs_ret_buf[i])
			{
				right_side_fully_solid_og = true;
			}
		}
		
		for ( u32 i=clseg_grp.the_vi_bot_left_og; 
			i<=clseg_grp.the_vi_bot_right_og;
			++i )
		{
			vert_fs_ret_buf[i] = clseg_grp.get_vert_ctup(i).bcrlg
				.vert_any_bbvt_is_fully_solid(vert_fs_pos_buf[i]);
			vert_slp_ret_buf[i] = clseg_grp.get_vert_ctup(i).bcrlg
				.vert_any_bbvt_is_slope(vert_slp_pos_buf[i]);
			
			if (vert_fs_ret_buf[i])
			{
				bot_side_fully_solid_og = true;
			}
			if (vert_slp_ret_buf[i])
			{
				bot_side_slope_og = true;
			}
		}
		
		
		
		
		// (Temporarily (?)) permit walking through the vertical side of
		// slopes
		if ( left_side_fully_solid_og
			&& !right_side_fully_solid_og )
		{
			block_coll_response_left_16x32(clseg_grp.get_horiz_ctup
				(clseg_grp.the_hi_left_top_og).bcrlg);
		}
		
		else if ( !left_side_fully_solid_og
			&& right_side_fully_solid_og )
		{
			block_coll_response_right_16x32(clseg_grp.get_horiz_ctup
				(clseg_grp.the_hi_right_top_og).bcrlg);
		}
		
		// Handle slopes in a special way
		if (bot_side_slope_og)
		{
			set_curr_on_slope(true);
			
			//tallest_height_val.back_up();
			//tallest_height_val.curr = -1;
			s32 tallest_height_val = -1;
			s32 thv_vs_index = -1;
			//decltype(clseg_grp)::vert_coll_tuple* thv_vert_sensor_ptr 
			//	= NULL;
			
			for ( u32 i=clseg_grp.the_vi_bot_left_og;
				i<clseg_grp.the_vi_bot_right_og;
				++i )
			{
				if (vert_slp_ret_buf[i])
				{
					const u32 temp_height_val 
						= (block_base_stuff::height_mask_ptr_arr
						[vert_slp_ret_buf[i]->the_bbvt])
						[( clseg_grp.get_vert_ctup(i).clseg.top_pt().x
						.floor_to_int() ) % num_pixels_per_block_dim ];
					//tallest_height_val
					//show_debug_u32_group(temp);
					
					//if ( tallest_height_val.curr < static_cast<s32>(temp) )
					//{
					//	tallest_height_val.curr = temp;
					//}
					
					if ( tallest_height_val 
						< static_cast<s32>(temp_height_val) )
					{
						tallest_height_val = temp_height_val;
						thv_vs_index = i;
						//thv_vert_sensor_ptr = &clseg_grp.get_vert_ctup(i);
					}
				}
			}
			
			//if (thv_vert_sensor_ptr)
			if ( thv_vs_index != -1 )
			{
				//const decltype(clseg_grp)::vert_coll_tuple& thv_vert_sensor
				//	= *thv_vert_sensor_ptr;
				
				//set_curr_on_ground(true);
				//block_coll_response_bot_slope_16x32( thv_vert_sensor.bcrlg,
				//	tallest_height_val, vert_slp_pos_buf[thv_vs_index] );
				block_coll_response_bot_slope_16x32( tallest_height_val, 
					vert_slp_pos_buf[thv_vs_index] );
			}
			
		}
		else
		{
			set_curr_on_slope(false);
			
			// The sprite is now in air if there are no relevant blocks
			// intersected by the vertical sensors
			if (!bot_side_fully_solid_og)
			{
				// This needs to be turned back on eventually
				//set_curr_on_ground(false);
			}
			//else // if (bot_side_fully_solid_og)
			//{
			//	block_coll_response_bot_16x32(clseg_grp.get_vert_ctup
			//		(clseg_grp.the_vi_bot_left_og).bcrlg);
			//}
		}
	}
	else // if ( !get_curr_on_ground() )
	{
		// Don't forget to remove the code at the top of this function that
		// sets on_ground.curr to true every time!
		
	}
	
	////vel.x.data += clg_16x32_size;
	//vel += clseg_grp.horiz_clseg_groups[clseg_grp.hi_left_top].left_pt();
}
void sprite::block_collision_stuff_32x16()
{
	
}
void sprite::block_collision_stuff_32x32()
{
	
}
