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


#include "sprite_class.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../gfx_manager_class.hpp"

#include "sprite_allocator_class.hpp"

#include "../misc_utility_funcs.hpp"

#include "../level_stuff/active_level_class.hpp"

const oam_entry::shape_size sprite::the_initial_shape_size 
	= oam_entry::ss_16x16;

const vec2_f24p8 sprite::the_initial_coll_box_size
	= { {14 << fixed24p8::shift}, {14 << fixed24p8::shift} },
	sprite::the_initial_cb_pos_offset 
	= { {1 << fixed24p8::shift}, {1 << fixed24p8::shift} };

const vec2_f24p8 sprite::the_initial_in_level_pos_offset
	= { {0 << fixed24p8::shift}, {0 << fixed24p8::shift} };

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
	const bg_point& camera_pos, bool facing_left )
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2( s_in_level_pos, camera_pos, 
		facing_left );
}
sprite::sprite( const vec2_f24p8& s_in_level_pos, 
	const vec2_u32& the_level_size_2d, bg_point& camera_pos,
	bool facing_left )
{
	shared_constructor_code_part_1();
	shared_constructor_code_part_2( s_in_level_pos, the_level_size_2d, 
		camera_pos, facing_left );
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
	
	in_level_pos = vel = vec2_f24p8( (fixed24p8){0}, (fixed24p8){0} );
	max_vel_x_abs_val = accel_x = (fixed24p8){0};
	
	set_initial_coll_box_stuff();
	
	on_ground = is_jumping = false;
	
	invin_frame_timer = 0;
	
	memfill32( misc_data_u, 0, misc_data_size * 2 );
	
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
	( const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos, 
	bool facing_left )
{
	shared_constructor_code_part_2(facing_left);
	in_level_pos = s_in_level_pos - get_the_initial_in_level_pos_offset();
	
	update_f24p8_positions();
	update_on_screen_pos(camera_pos);
}

void sprite::shared_constructor_code_part_3()
{
}

// This form of shared_constructor_code() is primarily intended to be
// used by the_player.
void sprite::shared_constructor_code_part_2
	( const vec2_f24p8& s_in_level_pos, const vec2_u32& the_level_size_2d, 
	bg_point& camera_pos, bool facing_left )
{
	shared_constructor_code_part_2(facing_left);
	in_level_pos = s_in_level_pos - get_the_initial_in_level_pos_offset();
	
	update_f24p8_positions();
	update_on_screen_pos(camera_pos);
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



void sprite::update_on_screen_pos( const bg_point& camera_pos )
{
	vec2_f24p8 temp_on_screen_pos = get_on_screen_pos(camera_pos);
	//vec2_s32 temp_on_screen_pos = get_on_screen_pos_s32(camera_pos);
	
	////if ( !did_update_prev_on_screen_pos_this_frame )
	//{
	//	//did_update_prev_on_screen_pos_this_frame = true;
	//	
	//	on_screen_pos.back_up_and_update(temp_on_screen_pos);
	//	
	//	if ( on_screen_pos.has_changed() 
	//		&& the_sprite_ipg->type == st_door )
	//	{
	//		temp_debug_thing = true;
	//	}
	//	
	//}
	
	
	//vec2_f24p8 temp_on_screen_pos;
	//
	//temp_on_screen_pos.x.data = in_level_pos.x.data - camera_pos.x.data;
	//temp_on_screen_pos.y.data = in_level_pos.y.data - camera_pos.y.data;
	
	vec2_u32 ss_vec2 = get_shape_size_as_vec2();
	vec2_f24p8 offset( make_f24p8(ss_vec2.x), make_f24p8(ss_vec2.y) );
	
	// Check whether the sprite is on screen.
	if ( temp_on_screen_pos.x + offset.x >= (fixed24p8){0} 
		&& temp_on_screen_pos.x <= make_f24p8(screen_width)
		&& temp_on_screen_pos.y + offset.y >= (fixed24p8){0}
		&& temp_on_screen_pos.y <= make_f24p8(screen_height) )
	{
		the_oam_entry.show_non_affine();
		
		the_oam_entry.set_x_coord(temp_on_screen_pos.x.round_to_int());
		the_oam_entry.set_y_coord(temp_on_screen_pos.y.round_to_int());
	}
	else
	{
		// Hide the sprite if it's not on screen
		the_oam_entry.hide_non_affine();
	}
}


void sprite::camera_follow_basic( bg_point& camera_pos )
{
	vec2_f24p8 temp_on_screen_pos = get_on_screen_pos(camera_pos);
	
	fixed24p8 on_screen_bottom_pos = temp_on_screen_pos.y 
		+ make_f24p8(get_shape_size_as_vec2().y);
	
	if ( ( temp_on_screen_pos.x <= make_f24p8(100) && vel.x.data < 0 ) 
		|| ( temp_on_screen_pos.x >= make_f24p8(140) && vel.x.data > 0 ) )
	{
		camera_pos.x += vel.x;
	}
	
	//if ( ( temp_on_screen_pos.y <= make_f24p8(20) && vel.y.data < 0 ) 
	//	|| ( temp_on_screen_pos.y >= make_f24p8(80) && vel.y.data > 0 ) )
	//{
	//	camera_pos.y += vel.y.trunc_to_int();
	//}
	
	auto camera_pos_y_updater = [&]( bool add ) -> void
	{
		if (!on_ground)
		{
			camera_pos.y += vel.y;
		}
		else
		{
			if (!add)
			{
				camera_pos.y += {-0x400};
			}
			else //if (add)
			{
				camera_pos.y += {0x400};
			}
		}
	};
	
	if ( temp_on_screen_pos.y <= make_f24p8(20) )
	{
		camera_pos_y_updater(false);
	}
	else if ( on_screen_bottom_pos >= make_f24p8(60) )
	{
		if ( vel.y >= (fixed24p8){0} )
		{
			camera_pos_y_updater(true);
		}
	}
	
}

void sprite::center_camera_almost( bg_point& camera_pos ) const
{
	//camera_pos.x = ( in_level_pos.x 
	//	- (fixed24p8){ screen_width << 7 } ).trunc_to_int();
	//camera_pos.y = ( in_level_pos.y 
	//	- (fixed24p8){ screen_height << 7 } ).trunc_to_int();
	
	camera_pos.x = in_level_pos.x - (fixed24p8){ screen_width << 7 };
	camera_pos.y = in_level_pos.y - (fixed24p8){ screen_height << 7 };
}




//void sprite::block_collision_stuff()
//{
//	sprite_stuff_array[the_sprite_type]->block_collision_stuff(*this);
//}




vec2_u32 sprite::get_shape_size_as_vec2_raw() const
{
	
	switch (the_shape_size)
	{
		// Square shapes
		case oam_entry::ss_8x8:
			return { 8, 8 };
		case oam_entry::ss_16x16:
			return { 16, 16 };
		case oam_entry::ss_32x32:
			return { 32, 32 };
		case oam_entry::ss_64x64:
			return { 64, 64 };
		
		// Horizontal shapes
		case oam_entry::ss_16x8:
			return { 16, 8 };
		case oam_entry::ss_32x8:
			return { 32, 8 };
		case oam_entry::ss_32x16:
			return { 32, 16 };
		case oam_entry::ss_64x32:
			return { 64, 32 };
		
		// Vertical shapes
		case oam_entry::ss_8x16:
			return { 8, 16 };
		case oam_entry::ss_8x32:
			return { 8, 32 };
		case oam_entry::ss_16x32:
			return { 16, 32 };
		case oam_entry::ss_32x64:
			return { 32, 64 };
	}
	
}


void sprite::update_part_1()
{
	//did_update_prev_on_screen_pos_this_frame = false;
	//temp_debug_thing = false;
	
	update_f24p8_positions();
	block_collision_stuff();
}


// The player_sprite_stuff class is the primary user of this function.
void sprite::update_part_2( bg_point& camera_pos, 
	const vec2_u32& the_level_size_2d )
{
}


void sprite::update_part_2( const bg_point& camera_pos, 
	int& next_oam_index )
{
	gfx_update();
	
	
	
	update_on_screen_pos(camera_pos);
	
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
	return the_palette_slot;
}
const u32 sprite::get_curr_relative_tile_slot()
{
	return the_relative_metatile_slot * num_active_gfx_tiles;
}



// This is a dummy function that child classes implement.
void sprite::block_collision_stuff()
{
	//sprite_stuff_array[the_sprite_type]->block_collision_stuff(*this);
}


// This is a dummy function that child classes implement (probably just
// player_sprite_stuff).
void sprite::handle_jumping_stuff( u32 is_jump_key_hit, 
	u32 is_jump_key_held )
{
}



void sprite::get_basic_block_coll_results_16x16
	( coll_point_group& the_pt_group, block_coll_result& lt_coll_result,
	block_coll_result& lb_coll_result, block_coll_result& tl_coll_result,
	block_coll_result& tm_coll_result, block_coll_result& tr_coll_result,
	block_coll_result& rt_coll_result, block_coll_result& rb_coll_result,
	block_coll_result& bl_coll_result, block_coll_result& bm_coll_result,
	block_coll_result& br_coll_result )
{
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x16()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x16_coll_point_names(X)
	#undef X
}

void sprite::get_basic_block_coll_results_16x32
	( coll_point_group& the_pt_group, 
	block_coll_result& lt_coll_result, block_coll_result& lm_coll_result,
	block_coll_result& lb_coll_result, block_coll_result& tl_coll_result,
	block_coll_result& tm_coll_result, block_coll_result& tr_coll_result,
	block_coll_result& rt_coll_result, block_coll_result& rm_coll_result,
	block_coll_result& rb_coll_result, block_coll_result& bl_coll_result,
	block_coll_result& bm_coll_result, block_coll_result& br_coll_result )
{
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x32()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x32_coll_point_names(X)
	#undef X
}




// 16x16 sprites
void sprite::block_coll_response_left_16x16
	( const block_coll_result& lt_coll_result,
	const block_coll_result& lb_coll_result )
{
	in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 ) * 16 ) 
		- cb_pos_offset.x;
	
	// Don't let the sprite speed up while in the air and horizontally
	// colliding with a block.
	if ( !on_ground && vel.x < (fixed24p8){0x00} )
	{
		vel.x = {0x00};
	}
}
void sprite::block_coll_response_top_16x16
	( const block_coll_result& tl_coll_result,
	const block_coll_result& tm_coll_result,
	const block_coll_result& tr_coll_result )
{
	in_level_pos.y = make_f24p8( ( tl_coll_result.coord.y + 1 ) * 16 ) 
		- cb_pos_offset.y;
	
	if ( vel.y < (fixed24p8){0x00} )
	{
		vel.y = {0x00};
	}
	//jump_hold_timer = 0;
	is_jumping = false;
}

void sprite::block_coll_response_right_16x16
	( const block_coll_result& rt_coll_result,
	const block_coll_result& rb_coll_result )
{
	in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 ) 
		- the_coll_box.size.x - cb_pos_offset.x;
		//- make_f24p8(get_shape_size_as_vec2().x);
	
	// Don't let the sprite speed up while in the air and horizontally
	// colliding with a block.
	if ( !on_ground && vel.x > (fixed24p8){0x00} )
	{
		vel.x = {0x00};
	}
}

void sprite::non_slope_block_coll_response_bot_16x16
	( const block_coll_result& bl_coll_result,
	const block_coll_result& bm_coll_result, 
	const block_coll_result& br_coll_result )
{
	if ( vel.y >= (fixed24p8){0} )
	{
		in_level_pos.y = make_f24p8( bl_coll_result.coord.y * 16 ) 
			//- ( the_coll_box.size.y +
			//cb_pos_offset.y );
			- make_f24p8(get_shape_size_as_vec2().y);
		vel.y = {0x00};
		on_ground = true;
		//jump_hold_timer = 0;
		is_jumping = false;
	}
}
//block_type sprite::slope_block_coll_response_bot_16x16
//	( coll_point_group& the_pt_group,
//	block_coll_result& bm_coll_result,
//	block_coll_result& bl_coll_result,
//	block_coll_result& br_coll_result, bool hitting_tltr )
//{
//	return bt_air;
//}

block_type sprite::slope_block_coll_response_bot_16x16
	( coll_point_group& the_pt_group, 
	block_coll_result& bl_coll_result, block_coll_result& bm_coll_result,
	block_coll_result& br_coll_result, bool hitting_tltr )
{
	#define X(name) \
		vec2_f24p8& pt_##name = the_pt_group.get_pt_##name##_16x16();
	list_of_16x16_slope_stuff_coll_point_names(X)
	#undef X
	
	
	// pt_bm, pt_bl, and pt_br converted to the relative coordinate system
	// of the block, with units of WHOLE pixels, with NO subpixels.  The %
	// operators will be converted to & operators by the compiler.
	#define X(name) \
		vec2_s32 pt_##name##_block_rel_round \
			= vec2_s32( pt_##name.x.round_to_int() \
			% num_pixels_per_block_row, pt_##name.y.round_to_int() \
			% num_pixels_per_block_col );
	list_of_16x16_slope_stuff_coll_point_names(X)
	#undef X
	
	
	// The block y coord points above collision points
	#define X(name) \
		const s32 pt_above_pt_##name##_block_coord_y \
			= name##_coll_result.coord.y - 1;
	list_of_16x16_slope_stuff_coll_point_names(X)
	#undef X
	
	// Height mask values for the points to check
	#define X(name) \
		s32 pt_##name##_height_mask_value = -1;
	list_of_16x16_slope_stuff_coll_point_names(X)
	#undef X
		
	
	// Basically, these pointers are used as aliases for long variable
	// names.
	#define X(name) \
	const u32* height_mask_##name \
		= grass_slope_##name##_block_stuff::height_mask;
	list_of_slope_configurations(X)
	#undef X
	
	auto find_height_mask_value_normal = [&]
		( const block_coll_result& the_coll_result, 
		s32& height_mask_value, const vec2_s32& pt_block_rel_round, 
		s32 pt_above_pt_block_coord_y ) -> void
	{
		// Find height_mask_value.
		
		if (false)
		{
		}
		#define X(name) \
		else if ( the_coll_result.type == bt_grass_slope_##name ) \
		{ \
			/* show_debug_str_s32("norm"); */ \
			height_mask_value = height_mask_##name \
				[pt_block_rel_round.x]; \
		}
		list_of_slope_configurations(X)
		#undef X
		
		// If the point doesn't intersect a slope block, then check whether
		// the block at the block coord ABOVE the point is a slope
		else
		{
			block_type above_block_type 
				= active_level::get_block_type_at_coord
				( vec2_s32( the_coll_result.coord.x,
				pt_above_pt_block_coord_y ) );
			//next_debug_s32 = above_block_type;
			
			if (false)
			{
			}
			#define X(name) \
			else if ( above_block_type == bt_grass_slope_##name ) \
			{ \
				/* show_debug_str_s32("abov"); */ \
				height_mask_value = height_mask_##name \
					[pt_block_rel_round.x] + num_pixels_per_block_col; \
			}
			list_of_slope_configurations(X)
			#undef X
			
			else
			{
				//show_debug_str_s32("welp");
				//height_mask_value = 0;
			}
		}
	};
	
	auto respond_to_collision = [&]( const coll_point_group& the_pt_group, 
		const block_coll_result& the_coll_result, 
		const s32 height_mask_value, const vec2_s32& pt_block_rel_round )
	{
		//next_debug_s32 = num_pixels_per_block_col - pt_block_rel_round.y;
		//next_debug_s32 = height_mask_value;
		
		// Check whether the_sprite is inside the slope.
		if ( ( (s32)num_pixels_per_block_col - (s32)pt_block_rel_round.y )
			<= height_mask_value )
		{
			//show_debug_str_s32("wow ");
			if ( vel.y >= (fixed24p8){0} )
				//&& jump_hold_timer == 0 )
				//&& !is_jumping )
			{
				in_level_pos.y = make_f24p8
					( ( the_coll_result.coord.y + 1 )
					* num_pixels_per_block_col - height_mask_value )
					- make_f24p8( get_shape_size_as_vec2().y );
					//- ( the_coll_box.size.y + cb_pos_offset );
				
				vel.y = {0x00};
				on_ground = true;
				
				if ( vel.x != (fixed24p8){0} && hitting_tltr )
				{
					in_level_pos.y += make_f24p8(1);
				}
				
			}
		}
		else if ( pt_block_rel_round.y == 0 )
		{
			//show_debug_str_s32("okay");
			//in_level_pos.y = make_f24p8( ( the_coll_result.coord.y + 1 )
			//	* num_pixels_per_block_col - height_mask_value )
			//	- the_coll_box.size.y;
			
			//in_level_pos.y += make_f24p8(1);
			on_ground = false;
			
		}
		else if ( vel.y < (fixed24p8){0} )
		{
			//show_debug_str_s32("hmmm");
			on_ground = false;
		}
		else if ( vel.y == (fixed24p8){0} )
		{
			//in_level_pos.y = make_f24p8( ( the_coll_result.coord.y + 1 )
			//	* num_pixels_per_block_col - height_mask_value )
			//	- make_f24p8( get_shape_size_as_vec2().y );
			//	//- ( the_coll_box.size.y + cb_pos_offset );
			
			//if ( pt_block_rel_round.y == 1 )
			//{
			//	in_level_pos.y += make_f24p8(3);
			//}
			
			//in_level_pos.y += make_f24p8(2);
			
			//vel.y = make_f24p8(2);
			
			//vel.y = {0x00};
			on_ground = true;
			
			if ( vel.x != (fixed24p8){0} && hitting_tltr )
			{
				in_level_pos.y += make_f24p8(1);
			}
		}
		
		
		else
		{
			//show_debug_str_s32("hmm2");
			//on_ground = true;
			on_ground = false;
			
		}
		
		
		//show_debug_str_s32("dbst");
		
		//next_debug_s32 = pt_block_rel_round.y;
		//next_debug_s32 = (s32)num_pixels_per_block_col
		//	- pt_block_rel_round.y;
		//show_debug_str_s32( ( ( (s32)num_pixels_per_block_col
		//	- pt_block_rel_round.y ) <= height_mask_value ) 
		//	? "true" : "fals" );
		//next_debug_s32 = (u32)height_mask_value;
		
		//show_debug_str_s32("dben");
		
	};
	
	
	find_height_mask_value_normal( bm_coll_result, pt_bm_height_mask_value,
		pt_bm_block_rel_round, pt_above_pt_bm_block_coord_y );
	
	find_height_mask_value_normal( bl_coll_result, pt_bl_height_mask_value,
		pt_bl_block_rel_round, pt_above_pt_bl_block_coord_y );
	
	find_height_mask_value_normal( br_coll_result, pt_br_height_mask_value,
		pt_br_block_rel_round, pt_above_pt_br_block_coord_y );
	
	
	//s32 the_greatest_height_mask_value = max3( pt_bm_height_mask_value,
	//	pt_bl_height_mask_value, pt_br_height_mask_value );
	
	s32 the_greatest_height_mask_value = max_va( pt_bm_height_mask_value,
		pt_bl_height_mask_value, pt_br_height_mask_value );
	
	
	if ( the_greatest_height_mask_value == pt_bm_height_mask_value )
	{
		respond_to_collision( the_pt_group, bm_coll_result,
			pt_bm_height_mask_value, pt_bm_block_rel_round );
		
		return bm_coll_result.type;
	}
	else if ( the_greatest_height_mask_value == pt_bl_height_mask_value )
	{
		respond_to_collision( the_pt_group, bl_coll_result,
			pt_bl_height_mask_value, pt_bl_block_rel_round );
		
		return bl_coll_result.type;
	}
	else if ( the_greatest_height_mask_value == pt_br_height_mask_value )
	{
		respond_to_collision( the_pt_group, br_coll_result,
			pt_br_height_mask_value, pt_br_block_rel_round );
		
		return br_coll_result.type;
	}
	
	
	
	//show_debug_str_s32("hstr");
	//next_debug_s32 = pt_bm_height_mask_value;
	//next_debug_s32 = pt_bl_height_mask_value;
	//next_debug_s32 = pt_br_height_mask_value;
	//show_debug_str_s32("hend");
	
	// Find the highest number height_mask_value
	
	//if ( pt_bm_height_mask_value >= pt_bl_height_mask_value
	//	&& pt_bm_height_mask_value >= pt_br_height_mask_value 
	//	&& ( bt_is_slope(bm_coll_result.type)
	//	|| bt_is_slope(active_level::get_block_type_at_coord
	//	((vec2_s32){ bm_coll_result.coord.x, 
	//	pt_above_pt_bm_block_coord_y } ) ) ) )
	//{
	//	// Using pt_bm_height_mask_value
	//	//show_debug_str_s32("bm  ");
	//	respond_to_collision( the_pt_group, bm_coll_result, 
	//		pt_bm_height_mask_value, pt_bm_block_rel_round );
	//	
	//	return bm_coll_result.type;
	//}
	//if ( pt_bl_height_mask_value >= pt_bm_height_mask_value
	//	&& pt_bl_height_mask_value >= pt_br_height_mask_value 
	//	&& ( bt_is_slope(bl_coll_result.type) 
	//	|| bt_is_slope(active_level::get_block_type_at_coord
	//	((vec2_s32){ bl_coll_result.coord.x, 
	//	pt_above_pt_bl_block_coord_y } ) ) ) )
	//{
	//	// Using pt_bl_height_mask_value
	//	//show_debug_str_s32("bl  ");
	//	respond_to_collision( the_pt_group, bl_coll_result, 
	//		pt_bl_height_mask_value, pt_bl_block_rel_round );
	//	
	//	return bl_coll_result.type;
	//}
	//if ( pt_br_height_mask_value >= pt_bm_height_mask_value
	//	&& pt_br_height_mask_value >= pt_bl_height_mask_value 
	//	&& ( bt_is_slope(br_coll_result.type) 
	//	|| bt_is_slope(active_level::get_block_type_at_coord
	//	((vec2_s32){ br_coll_result.coord.x, 
	//	pt_above_pt_br_block_coord_y } ) ) ) )
	//{
	//	// Using pt_br_height_mask_value
	//	//show_debug_str_s32("br  ");
	//	respond_to_collision( the_pt_group, br_coll_result, 
	//		pt_br_height_mask_value, pt_br_block_rel_round );
	//	
	//	return br_coll_result.type;
	//}
	
	{
		//next_debug_s32 = 0xeebbaacc;
		//if ( vel.y >= (fixed24p8){0} )
		
		//if ( on_ground )
		//{
		//	vel.y = {0x00};
		//	on_ground = true;
		//}
		return bt_air;
	}
	
	
}


// 16x32 sprites
void sprite::block_coll_response_left_16x32
	( const block_coll_result& lt_coll_result,
	const block_coll_result& lm_coll_result, 
	const block_coll_result& lb_coll_result )
{
	//show_debug_str_s32("bkle");
	//show_debug_str_s32("    ");
	in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 ) * 16 ) 
		- cb_pos_offset.x;
	
	
	// Don't let the sprite speed up while in the air and horizontally
	// colliding with a block.
	if ( !on_ground && vel.x < (fixed24p8){0x00} )
	{
		vel.x = {0x00};
	}
}
void sprite::block_coll_response_top_16x32
	( const block_coll_result& tl_coll_result,
	const block_coll_result& tm_coll_result, 
	const block_coll_result& tr_coll_result )
{
	//show_debug_str_s32("bkto");
	//show_debug_str_s32("    ");
	block_coll_response_top_16x16( tl_coll_result, 
		tm_coll_result, tr_coll_result );
}
void sprite::block_coll_response_right_16x32
	( const block_coll_result& rt_coll_result,
	const block_coll_result& rm_coll_result, 
	const block_coll_result& rb_coll_result )
{
	//show_debug_str_s32("bkri");
	//show_debug_str_s32("    ");
	in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 ) 
		- the_coll_box.size.x - cb_pos_offset.x;
		//- get_shape_size_as_vec2().x );
	
	// Don't let the sprite speed up while in the air and horizontally
	// colliding with a block.
	if ( !on_ground && vel.x > (fixed24p8){0x00} )
	{
		vel.x = {0x00};
	}
}
void sprite::non_slope_block_coll_response_bot_16x32
	( const block_coll_result& bl_coll_result,
	const block_coll_result& bm_coll_result, 
	const block_coll_result& br_coll_result )
{
	//show_debug_str_s32("bkbo");
	//show_debug_str_s32("    ");
	non_slope_block_coll_response_bot_16x16( bl_coll_result, 
		bm_coll_result, br_coll_result );
}
block_type sprite::slope_block_coll_response_bot_16x32
	( coll_point_group& the_pt_group, 
	block_coll_result& bl_coll_result, block_coll_result& bm_coll_result,
	block_coll_result& br_coll_result, bool hitting_tltr )
{
	#define X(name) \
		vec2_f24p8& pt_##name = the_pt_group.get_pt_##name##_16x32();
	list_of_16x32_slope_stuff_coll_point_names(X)
	#undef X
	
	
	// pt_bm, pt_bl, and pt_br converted to the relative coordinate system
	// of the block, with units of WHOLE pixels, with NO subpixels.  The %
	// operators will be converted to & operators by the compiler.
	#define X(name) \
		vec2_s32 pt_##name##_block_rel_round \
			= vec2_s32( pt_##name.x.round_to_int() \
			% num_pixels_per_block_row, pt_##name.y.round_to_int() \
			% num_pixels_per_block_col );
	list_of_16x32_slope_stuff_coll_point_names(X)
	#undef X
	
	
	// The block y coord points above collision points
	#define X(name) \
		const s32 pt_above_pt_##name##_block_coord_y \
			= name##_coll_result.coord.y - 1;
	list_of_16x32_slope_stuff_coll_point_names(X)
	#undef X
	
	// Height mask values for the points to check
	#define X(name) \
		s32 pt_##name##_height_mask_value = -1;
	list_of_16x32_slope_stuff_coll_point_names(X)
	#undef X
		
	
	// Basically, these pointers are used as aliases for long variable
	// names.
	#define X(name) \
	const u32* height_mask_##name \
		= grass_slope_##name##_block_stuff::height_mask;
	list_of_slope_configurations(X)
	#undef X
	
	auto find_height_mask_value_normal = [&]
		( const block_coll_result& the_coll_result, 
		s32& height_mask_value, const vec2_s32& pt_block_rel_round, 
		s32 pt_above_pt_block_coord_y ) -> void
	{
		// Find height_mask_value.
		
		if (false)
		{
		}
		#define X(name) \
		else if ( the_coll_result.type == bt_grass_slope_##name ) \
		{ \
			/* show_debug_str_s32("norm"); */ \
			height_mask_value = height_mask_##name \
				[pt_block_rel_round.x]; \
		}
		list_of_slope_configurations(X)
		#undef X
		
		// If the point doesn't intersect a slope block, then check whether
		// the block at the block coord ABOVE the point is a slope
		else
		{
			block_type above_block_type 
				= active_level::get_block_type_at_coord
				( vec2_s32( the_coll_result.coord.x,
				pt_above_pt_block_coord_y ) );
			//next_debug_s32 = above_block_type;
			
			if (false)
			{
			}
			#define X(name) \
			else if ( above_block_type == bt_grass_slope_##name ) \
			{ \
				/* show_debug_str_s32("abov"); */ \
				height_mask_value = height_mask_##name \
					[pt_block_rel_round.x] + num_pixels_per_block_col; \
			}
			list_of_slope_configurations(X)
			#undef X
			
			else
			{
				//show_debug_str_s32("welp");
				//height_mask_value = 0;
			}
		}
	};
	
	auto respond_to_collision = [&]( const coll_point_group& the_pt_group, 
		const block_coll_result& the_coll_result, 
		const s32 height_mask_value, const vec2_s32& pt_block_rel_round )
	{
		//next_debug_s32 = num_pixels_per_block_col - pt_block_rel_round.y;
		//next_debug_s32 = height_mask_value;
		
		// Check whether the_sprite is inside the slope.
		if ( ( (s32)num_pixels_per_block_col - (s32)pt_block_rel_round.y )
			<= height_mask_value )
		{
			//show_debug_str_s32("wow ");
			if ( vel.y >= (fixed24p8){0} )
				//&& jump_hold_timer == 0 )
				//&& !is_jumping )
			{
				in_level_pos.y = make_f24p8( ( the_coll_result.coord.y 
					+ 1 ) * num_pixels_per_block_col - height_mask_value )
					- make_f24p8( get_shape_size_as_vec2().y );
					//- ( the_coll_box.size.y 
					//+ cb_pos_offset );
				
				vel.y = {0x00};
				on_ground = true;
				
				if ( vel.x != (fixed24p8){0} && hitting_tltr )
				{
					in_level_pos.y += make_f24p8(1);
				}
				
			}
		}
		else if ( pt_block_rel_round.y == 0 )
		{
			//show_debug_str_s32("okay");
			//in_level_pos.y = make_f24p8
			//	( ( the_coll_result.coord.y + 1 )
			//	* num_pixels_per_block_col - height_mask_value )
			//	- the_coll_box.size.y;
			
			//in_level_pos.y += make_f24p8(1);
			on_ground = false;
			
		}
		else if ( vel.y < (fixed24p8){0} )
		{
			//show_debug_str_s32("hmmm");
			on_ground = false;
		}
		else if ( vel.y == (fixed24p8){0} )
		{
			//in_level_pos.y = make_f24p8
			//	( ( the_coll_result.coord.y + 1 )
			//	* num_pixels_per_block_col - height_mask_value )
			//	- make_f24p8( get_shape_size_as_vec2().y );
			//	//- ( the_coll_box.size.y 
			//	//+ cb_pos_offset );
			
			//if ( pt_block_rel_round.y == 1 )
			//{
			//	in_level_pos.y += make_f24p8(3);
			//}
			
			//in_level_pos.y += make_f24p8(2);
			
			//vel.y = make_f24p8(2);
			
			//vel.y = {0x00};
			on_ground = true;
			
			if ( vel.x != (fixed24p8){0} && hitting_tltr )
			{
				in_level_pos.y += make_f24p8(1);
			}
		}
		
		
		else
		{
			//show_debug_str_s32("hmm2");
			//on_ground = true;
			on_ground = false;
			
		}
		
		
		//show_debug_str_s32("dbst");
		
		//next_debug_s32 = pt_block_rel_round.y;
		//next_debug_s32 = (s32)num_pixels_per_block_col
		//	- pt_block_rel_round.y;
		//show_debug_str_s32( ( ( (s32)num_pixels_per_block_col
		//	- pt_block_rel_round.y ) <= height_mask_value ) 
		//	? "true" : "fals" );
		//next_debug_s32 = (u32)height_mask_value;
		
		//show_debug_str_s32("dben");
		
	};
	
	
	find_height_mask_value_normal( bm_coll_result, pt_bm_height_mask_value,
		pt_bm_block_rel_round, pt_above_pt_bm_block_coord_y );
	
	find_height_mask_value_normal( bl_coll_result, pt_bl_height_mask_value,
		pt_bl_block_rel_round, pt_above_pt_bl_block_coord_y );
	
	find_height_mask_value_normal( br_coll_result, pt_br_height_mask_value,
		pt_br_block_rel_round, pt_above_pt_br_block_coord_y );
	
	
	//s32 the_greatest_height_mask_value = max3( pt_bm_height_mask_value,
	//	pt_bl_height_mask_value, pt_br_height_mask_value );
	
	s32 the_greatest_height_mask_value = max_va( pt_bm_height_mask_value,
		pt_bl_height_mask_value, pt_br_height_mask_value );
	
	
	if ( the_greatest_height_mask_value == pt_bm_height_mask_value )
	{
		respond_to_collision( the_pt_group, bm_coll_result,
			pt_bm_height_mask_value, pt_bm_block_rel_round );
		
		return bm_coll_result.type;
	}
	else if ( the_greatest_height_mask_value == pt_bl_height_mask_value )
	{
		respond_to_collision( the_pt_group, bl_coll_result,
			pt_bl_height_mask_value, pt_bl_block_rel_round );
		
		return bl_coll_result.type;
	}
	else if ( the_greatest_height_mask_value == pt_br_height_mask_value )
	{
		respond_to_collision( the_pt_group, br_coll_result,
			pt_br_height_mask_value, pt_br_block_rel_round );
		
		return br_coll_result.type;
	}
	
	
	
	//show_debug_str_s32("hstr");
	//next_debug_s32 = pt_bm_height_mask_value;
	//next_debug_s32 = pt_bl_height_mask_value;
	//next_debug_s32 = pt_br_height_mask_value;
	//show_debug_str_s32("hend");
	
	// Find the highest number height_mask_value
	
	//if ( pt_bm_height_mask_value >= pt_bl_height_mask_value
	//	&& pt_bm_height_mask_value >= pt_br_height_mask_value 
	//	&& ( bt_is_slope(bm_coll_result.type)
	//	|| bt_is_slope(active_level::get_block_type_at_coord
	//	((vec2_s32){ bm_coll_result.coord.x, 
	//	pt_above_pt_bm_block_coord_y } ) ) ) )
	//{
	//	// Using pt_bm_height_mask_value
	//	//show_debug_str_s32("bm  ");
	//	respond_to_collision( the_pt_group, bm_coll_result, 
	//		pt_bm_height_mask_value, pt_bm_block_rel_round );
	//	
	//	return bm_coll_result.type;
	//}
	//if ( pt_bl_height_mask_value >= pt_bm_height_mask_value
	//	&& pt_bl_height_mask_value >= pt_br_height_mask_value 
	//	&& ( bt_is_slope(bl_coll_result.type) 
	//	|| bt_is_slope(active_level::get_block_type_at_coord
	//	((vec2_s32){ bl_coll_result.coord.x, 
	//	pt_above_pt_bl_block_coord_y } ) ) ) )
	//{
	//	// Using pt_bl_height_mask_value
	//	//show_debug_str_s32("bl  ");
	//	respond_to_collision( the_pt_group, bl_coll_result, 
	//		pt_bl_height_mask_value, pt_bl_block_rel_round );
	//	
	//	return bl_coll_result.type;
	//}
	//if ( pt_br_height_mask_value >= pt_bm_height_mask_value
	//	&& pt_br_height_mask_value >= pt_bl_height_mask_value 
	//	&& ( bt_is_slope(br_coll_result.type) 
	//	|| bt_is_slope(active_level::get_block_type_at_coord
	//	((vec2_s32){ br_coll_result.coord.x, 
	//	pt_above_pt_br_block_coord_y } ) ) ) )
	//{
	//	// Using pt_br_height_mask_value
	//	//show_debug_str_s32("br  ");
	//	respond_to_collision( the_pt_group, br_coll_result, 
	//		pt_br_height_mask_value, pt_br_block_rel_round );
	//	
	//	return br_coll_result.type;
	//}
	
	{
		//next_debug_s32 = 0xeebbaacc;
		//if ( vel.y >= (fixed24p8){0} )
		
		//if ( on_ground )
		//{
		//	vel.y = {0x00};
		//	on_ground = true;
		//}
		return bt_air;
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
	bg_point& camera_pos, const vec2_u32& the_level_size_2d )
{
	
}




void sprite::block_collision_stuff_16x16()
{
	// The collision points
	coll_point_group the_pt_group;
	
	generate_coll_point_group_16x16( *this, the_pt_group );
	
	// The block_coll_result's
	block_coll_result lt_coll_result, lb_coll_result, tl_coll_result,
		tm_coll_result, tr_coll_result, rt_coll_result, rb_coll_result,
		bl_coll_result, bm_coll_result, br_coll_result ;
	
	// Get the block_coll_result's
	get_basic_block_coll_results_16x16( the_pt_group, lt_coll_result,
		lb_coll_result, tl_coll_result, tm_coll_result, tr_coll_result,
		rt_coll_result, rb_coll_result, bl_coll_result, bm_coll_result,
		br_coll_result );
	
	
	// Lambda functions for non-slope block collision response
	auto any_left_response = [&]() -> void
	{
		block_coll_response_left_16x16( lt_coll_result, lb_coll_result );
	};
	
	auto any_top_response = [&]() -> void
	{
		block_coll_response_top_16x16( tl_coll_result, tm_coll_result, 
			tr_coll_result );
	};
	
	auto any_right_response = [&]() -> void
	{
		block_coll_response_right_16x16( rt_coll_result, rb_coll_result );
	};
	
	auto any_non_slope_bot_response = [&]() -> void
	{
		non_slope_block_coll_response_bot_16x16( bl_coll_result, 
			bm_coll_result, br_coll_result );
	};
	
	//show_debug_str_s32( on_ground ? "ongn" : "offg" );
	
	// When not dealing with slopes, this method is used.
	if ( !bt_is_left_slope(bl_coll_result.type)
		&& !bt_is_slope(bm_coll_result.type)
		&& !bt_is_right_slope(br_coll_result.type)
		&& !bt_is_left_slope(lb_coll_result.type)
		&& !bt_is_right_slope(rb_coll_result.type) )
	{
		//show_debug_str_s32("nslp");
		//show_debug_str_s32("    ");
		
		if ( tl_coll_result.type != bt_air 
			|| tr_coll_result.type != bt_air )
		{
			//show_debug_str_s32("tltr");
			//show_debug_str_s32("    ");
			
			if ( lt_coll_result.type != bt_air )
			{
				//show_debug_str_s32("left");
				//show_debug_str_s32("1t  ");
				any_left_response();
			}
			if ( rt_coll_result.type != bt_air )
			{
				//show_debug_str_s32("righ");
				//show_debug_str_s32("1t  ");
				any_right_response();
			}
			
			any_top_response();
			
			
		}
		else if ( bl_coll_result.type != bt_air
			|| br_coll_result.type != bt_air )
		{
			//show_debug_str_s32("blbr");
			//show_debug_str_s32("    ");
			
			any_non_slope_bot_response();
			
			if ( bt_is_neither_air_nor_slope(lt_coll_result.type) )
			{
				//show_debug_str_s32("left");
				//show_debug_str_s32("1b  ");
				any_left_response();
			}
			if ( bt_is_neither_air_nor_slope(rt_coll_result.type) )
			{
				//show_debug_str_s32("righ");
				//show_debug_str_s32("1b  ");
				any_right_response();
			}
		}
		else
		{
			//show_debug_str_s32("leri");
			//show_debug_str_s32("    ");
			
			on_ground = false;
			
			if ( lt_coll_result.type != bt_air 
				|| lb_coll_result.type != bt_air )
			{
				any_left_response();
			}
			
			else if ( rt_coll_result.type != bt_air 
				|| rb_coll_result.type != bt_air )
			{
				any_right_response();
			}
			
		}
		
	}
	// When dealing with slopes, this method is used.
	else
	{
		//show_debug_str_s32("slop");
		//show_debug_str_s32("    ");
		
		if ( bt_is_neither_air_nor_slope(tl_coll_result.type) 
			|| bt_is_neither_air_nor_slope(tr_coll_result.type) )
		{
			//show_debug_str_s32("tltr");
			//show_debug_str_s32("    ");
			
			// Disable jumping
			if ( vel.y < (fixed24p8){0} )
			{
				in_level_pos.y -= vel.y;
				vel.y = (fixed24p8){0};
				on_ground = true;
				//jump_hold_timer = 0;
				is_jumping = false;
			}
			
			// Don't let the_sprite move through walls
			if ( lt_coll_result.type != bt_air 
				|| lb_coll_result.type != bt_air )
			{
				if ( vel.x < (fixed24p8){0} )
				{
					//vel.x = make_f24p8(4);
					in_level_pos.x -= vel.x;
				}
			}
			if ( rt_coll_result.type != bt_air 
				|| rb_coll_result.type != bt_air )
			{
				if ( vel.x > (fixed24p8){0} )
				{
					//vel.x = make_f24p8(-4);
					in_level_pos.x -= vel.x;
				}
			}
			
			slope_block_coll_response_bot_16x16( the_pt_group,
				bl_coll_result, bm_coll_result, br_coll_result, true );
		}
		else if ( bl_coll_result.type != bt_air
			|| br_coll_result.type != bt_air 
			|| lb_coll_result.type != bt_air 
			|| rb_coll_result.type != bt_air )
		{
			//show_debug_str_s32("blbr");
			//show_debug_str_s32("    ");
			
			block_type the_slope_block_type 
				= slope_block_coll_response_bot_16x16( the_pt_group, 
				bl_coll_result, bm_coll_result, br_coll_result );
			
			//show_debug_str_s32("bt  ");
			//next_debug_s32 = the_slope_block_type;
			
			// Don't let the_sprite move through walls
			if ( bt_is_neither_air_nor_slope(lt_coll_result.type)
				|| ( bt_is_neither_air_nor_slope(lb_coll_result.type) 
				&& the_slope_block_type != bt_grass_slope_n16_p16) )
			{
				if ( bt_is_neither_air_nor_slope(lb_coll_result.type) 
					&& the_slope_block_type != bt_grass_slope_n16_p16 )
				{
					//show_debug_str_s32("lb  ");
				}
				
				//show_debug_str_s32("left");
				//show_debug_str_s32("2b  ");
				any_left_response();
			}
			if ( bt_is_neither_air_nor_slope(rt_coll_result.type)
				|| ( bt_is_neither_air_nor_slope(rb_coll_result.type) 
				&& the_slope_block_type != bt_grass_slope_p16_p16 ) )
			{
				if ( bt_is_neither_air_nor_slope(rb_coll_result.type) 
					&& the_slope_block_type != bt_grass_slope_p16_p16 )
				{
					//show_debug_str_s32("rb  ");
				}
				
				//show_debug_str_s32("righ");
				//show_debug_str_s32("2b  ");
				any_right_response();
			}
		}
		else
		{
			//show_debug_str_s32("leri");
			
			on_ground = false;
			
			if ( lt_coll_result.type != bt_air 
				|| lb_coll_result.type != bt_air )
			{
				any_left_response();
			}
			
			else if ( rt_coll_result.type != bt_air 
				|| rb_coll_result.type != bt_air )
			{
				any_right_response();
			}
			
		}
		
	}
	//show_debug_str_s32( on_ground ? "ongn" : "offg" );
}

void sprite::block_collision_stuff_16x32()
{
	// The collision points
	coll_point_group the_pt_group;
	
	generate_coll_point_group_16x32( *this, the_pt_group );
	
	// The block_coll_result's
	block_coll_result lt_coll_result, lm_coll_result, lb_coll_result, 
		tl_coll_result, tm_coll_result, tr_coll_result, rt_coll_result,
		rm_coll_result, rb_coll_result, bl_coll_result, bm_coll_result, 
		br_coll_result;
	
	// Get the block_coll_result's
	get_basic_block_coll_results_16x32( the_pt_group, lt_coll_result,
		lm_coll_result, lb_coll_result, tl_coll_result, tm_coll_result,
		tr_coll_result, rt_coll_result, rm_coll_result, rb_coll_result,
		bl_coll_result, bm_coll_result, br_coll_result );
	
	
	// Lambda functions for non-slope block collision response
	auto any_left_response = [&]() -> void
	{
		block_coll_response_left_16x32( lt_coll_result, lm_coll_result, 
			lb_coll_result );
	};
	
	auto any_top_response = [&]() -> void
	{
		block_coll_response_top_16x32( tl_coll_result, tm_coll_result, 
			tr_coll_result );
	};
	
	auto any_right_response = [&]() -> void
	{
		block_coll_response_right_16x32( rt_coll_result, rm_coll_result, 
			rb_coll_result );
	};
	
	auto any_non_slope_bot_response = [&]() -> void
	{
		non_slope_block_coll_response_bot_16x32( bl_coll_result, 
			bm_coll_result, br_coll_result );
	};
	
	//show_debug_str_s32( on_ground ? "ongn" : "offg" );
	
	// When not dealing with slopes, this method is used.
	if ( !bt_is_left_slope(bl_coll_result.type)
		&& !bt_is_slope(bm_coll_result.type)
		&& !bt_is_right_slope(br_coll_result.type)
		&& !bt_is_left_slope(lb_coll_result.type)
		&& !bt_is_right_slope(rb_coll_result.type) )
		//&& !bt_is_left_slope(lm_coll_result.type)
		//&& !bt_is_right_slope(rm_coll_result.type) )
	{
		if ( tl_coll_result.type != bt_air 
			|| tr_coll_result.type != bt_air )
		{
			//show_debug_str_s32("tltr");
			
			if ( lt_coll_result.type != bt_air )
			{
				//show_debug_str_s32("left");
				//show_debug_str_s32("1t  ");
				any_left_response();
			}
			if ( rt_coll_result.type != bt_air )
			{
				//show_debug_str_s32("righ");
				//show_debug_str_s32("1t  ");
				any_right_response();
			}
			
			any_top_response();
			
			
		}
		else if ( bl_coll_result.type != bt_air
			|| br_coll_result.type != bt_air )
		{
			//show_debug_str_s32("blbr");
			
			any_non_slope_bot_response();
			
			if ( bt_is_neither_air_nor_slope(lt_coll_result.type)
				|| bt_is_neither_air_nor_slope(lm_coll_result.type) )
			{
				//show_debug_str_s32("left");
				//show_debug_str_s32("1b  ");
				any_left_response();
			}
			if ( bt_is_neither_air_nor_slope(rt_coll_result.type)
				|| bt_is_neither_air_nor_slope(rm_coll_result.type) )
			{
				//show_debug_str_s32("righ");
				//show_debug_str_s32("1b  ");
				any_right_response();
			}
		}
		else
		{
			//show_debug_str_s32("leri");
			
			on_ground = false;
			
			if ( lt_coll_result.type != bt_air 
				|| lm_coll_result.type != bt_air
				|| lb_coll_result.type != bt_air )
			{
				any_left_response();
			}
			
			else if ( rt_coll_result.type != bt_air 
				|| rm_coll_result.type != bt_air
				|| rb_coll_result.type != bt_air )
			{
				any_right_response();
			}
			
		}
		
	}
	// When dealing with slopes, this method is used.
	else
	{
		//show_debug_str_s32("slop");
		
		// (future thing if tall slopes are added)
		//if ( bt_is_neither_air_nor_tall_slope(tl_coll_result.type) 
		//	|| bt_is_neither_air_nor_tall_slope(tr_coll_result.type) )
		if ( tl_coll_result.type != bt_air
			|| tr_coll_result.type != bt_air )
		{
			//show_debug_str_s32("tltr");
			
			// Disable jumping
			if ( vel.y < (fixed24p8){0} )
			{
				in_level_pos.y -= vel.y;
				vel.y = (fixed24p8){0};
				on_ground = true;
				//jump_hold_timer = 0;
				is_jumping = false;
			}
			
			// Don't let the_sprite move through walls
			if ( lt_coll_result.type != bt_air 
				|| lm_coll_result.type != bt_air
				|| lb_coll_result.type != bt_air )
			{
				if ( vel.x < (fixed24p8){0} )
				{
					//vel.x = make_f24p8(4);
					in_level_pos.x -= vel.x;
				}
			}
			if ( rt_coll_result.type != bt_air 
				|| rm_coll_result.type != bt_air
				|| rb_coll_result.type != bt_air )
			{
				if ( vel.x > (fixed24p8){0} )
				{
					//vel.x = make_f24p8(-4);
					in_level_pos.x -= vel.x;
				}
			}
			
			slope_block_coll_response_bot_16x32( the_pt_group,
				bl_coll_result, bm_coll_result, br_coll_result, true );
		}
		else if ( bl_coll_result.type != bt_air
			|| br_coll_result.type != bt_air 
			|| lb_coll_result.type != bt_air 
			|| rb_coll_result.type != bt_air )
		{
			//show_debug_str_s32("blbr");
			
			block_type the_slope_block_type 
				= slope_block_coll_response_bot_16x32( the_pt_group, 
				bl_coll_result, bm_coll_result, br_coll_result );
			
			//show_debug_str_s32("bt  ");
			//next_debug_s32 = the_slope_block_type;
			
			
			// Don't let the_sprite move through walls
			if ( bt_is_neither_air_nor_slope(lt_coll_result.type)
				|| bt_is_neither_air_nor_slope(lm_coll_result.type)
				|| ( bt_is_neither_air_nor_slope(lb_coll_result.type) 
				&& the_slope_block_type != bt_grass_slope_n16_p16) )
			{
				if ( bt_is_neither_air_nor_slope(lb_coll_result.type) 
					&& the_slope_block_type != bt_grass_slope_n16_p16 )
				{
					//show_debug_str_s32("lb  ");
				}
				
				//show_debug_str_s32("left");
				//show_debug_str_s32("2b  ");
				any_left_response();
			}
			if ( bt_is_neither_air_nor_slope(rt_coll_result.type)
				|| bt_is_neither_air_nor_slope(rm_coll_result.type)
				|| ( bt_is_neither_air_nor_slope(rb_coll_result.type) 
				&& the_slope_block_type != bt_grass_slope_p16_p16 ) )
			{
				if ( bt_is_neither_air_nor_slope(rb_coll_result.type) 
					&& the_slope_block_type != bt_grass_slope_p16_p16 )
				{
					//show_debug_str_s32("rb  ");
				}
				
				//show_debug_str_s32("righ");
				//show_debug_str_s32("2b  ");
				any_right_response();
			}
		}
		else
		{
			//show_debug_str_s32("leri");
			
			on_ground = false;
			
			if ( lt_coll_result.type != bt_air 
				|| lm_coll_result.type != bt_air
				|| lb_coll_result.type != bt_air )
			{
				any_left_response();
			}
			
			else if ( rt_coll_result.type != bt_air 
				|| rm_coll_result.type != bt_air
				|| rb_coll_result.type != bt_air )
			{
				any_right_response();
			}
			
		}
		
	}
	//show_debug_str_s32( on_ground ? "ongn" : "offg" );
	
	
}

void sprite::block_collision_stuff_32x16()
{
	
}
void sprite::block_collision_stuff_32x32()
{
	
}



void sprite::block_collision_stuff_strongly_hit_stuff_only_16x16()
{
	// The collision points
	coll_point_group the_pt_group;
	
	generate_coll_point_group_16x16( *this, the_pt_group );
	
	// The block_coll_result's
	block_coll_result lt_coll_result, lb_coll_result, tl_coll_result,
		tm_coll_result, tr_coll_result, rt_coll_result, rb_coll_result,
		bl_coll_result, bm_coll_result, br_coll_result;
	
	// Get the block_coll_result's
	get_basic_block_coll_results_16x16( the_pt_group, lt_coll_result,
		lb_coll_result, tl_coll_result, tm_coll_result, tr_coll_result,
		rt_coll_result, rb_coll_result, bl_coll_result, bm_coll_result,
		br_coll_result );
	
	block_coll_response_left_16x16( lt_coll_result, lb_coll_result );
	block_coll_response_top_16x16( tl_coll_result, tm_coll_result, 
		tr_coll_result );
	block_coll_response_right_16x16( rt_coll_result, rb_coll_result );
	non_slope_block_coll_response_bot_16x16( bl_coll_result, 
		bm_coll_result, br_coll_result );
}

void sprite::block_collision_stuff_strongly_hit_stuff_only_16x32()
{
	// The collision points
	coll_point_group the_pt_group;
	
	generate_coll_point_group_16x32( *this, the_pt_group );
	
	// The block_coll_result's
	block_coll_result lt_coll_result, lm_coll_result, lb_coll_result, 
		tl_coll_result, tm_coll_result, tr_coll_result, rt_coll_result, 
		rm_coll_result, rb_coll_result, bl_coll_result, bm_coll_result,
		br_coll_result;
	
	// Get the block_coll_result's
	get_basic_block_coll_results_16x32( the_pt_group, lt_coll_result, 
		lm_coll_result, lb_coll_result, tl_coll_result, tm_coll_result,
		tr_coll_result, rt_coll_result, rm_coll_result, rb_coll_result,
		bl_coll_result, bm_coll_result, br_coll_result );
	
	
	block_coll_response_left_16x32( lt_coll_result, lm_coll_result, 
		lb_coll_result );
	block_coll_response_top_16x32( tl_coll_result, tm_coll_result, 
		tr_coll_result );
	block_coll_response_right_16x32( rt_coll_result, rm_coll_result, 
		rb_coll_result );
	non_slope_block_coll_response_bot_16x32( bl_coll_result, 
		bm_coll_result, br_coll_result );
}

void sprite::block_collision_stuff_strongly_hit_stuff_only_32x16()
{
	
}

void sprite::block_collision_stuff_strongly_hit_stuff_only_32x32()
{
	
}

