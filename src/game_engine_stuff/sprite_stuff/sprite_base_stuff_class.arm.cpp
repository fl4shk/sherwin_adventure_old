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


#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"

#include "sprite_manager_class.hpp"



void sprite_base_stuff::get_basic_block_coll_results_left_16x16
	( coll_point_group& the_pt_group, block_coll_result& lt_coll_result, 
	block_coll_result& lb_coll_result )
{
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x16()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x16_left_side_coll_point_names(X)
	#undef X
}
void sprite_base_stuff::get_basic_block_coll_results_top_16x16
	( coll_point_group& the_pt_group, block_coll_result& tl_coll_result, 
	block_coll_result& tm_coll_result, block_coll_result& tr_coll_result ) 
	
{
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x16()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x16_top_side_coll_point_names(X)
	#undef X
}
void sprite_base_stuff::get_basic_block_coll_results_right_16x16
	( coll_point_group& the_pt_group, block_coll_result& rt_coll_result, 
	block_coll_result& rb_coll_result )
{
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x16()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x16_right_side_coll_point_names(X)
	#undef X
}
void sprite_base_stuff::get_basic_block_coll_results_bot_16x16
	( coll_point_group& the_pt_group, block_coll_result& bl_coll_result, 
	block_coll_result& bm_coll_result, block_coll_result& br_coll_result )
{
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x16()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x16_bottom_side_coll_point_names(X)
	#undef X
}


void sprite_base_stuff::get_basic_block_coll_results_left_16x32
	( coll_point_group& the_pt_group, block_coll_result& lt_coll_result, 
	block_coll_result& lm_coll_result, block_coll_result& lb_coll_result )
{
	// DON'T change this function unless in the future a 16x32 hitbox uses
	// more than three left side collision points
	
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x32()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x32_left_side_coll_point_names(X)
	#undef X
}
void sprite_base_stuff::get_basic_block_coll_results_top_16x32
	( coll_point_group& the_pt_group, block_coll_result& tl_coll_result, 
	block_coll_result& tm_coll_result, block_coll_result& tr_coll_result )
{
	// DON'T change this function unless in the future a 16x32 hitbox uses
	// more than three top side collision points
	
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x32()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x32_top_side_coll_point_names(X)
	#undef X
}
void sprite_base_stuff::get_basic_block_coll_results_right_16x32
	( coll_point_group& the_pt_group, block_coll_result& rt_coll_result,
	block_coll_result& rm_coll_result, block_coll_result& rb_coll_result )
{
	// DON'T change this function unless in the future a 16x32 hitbox uses
	// more than three right side collision points
	
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x32()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x32_right_side_coll_point_names(X)
	#undef X
}
void sprite_base_stuff::get_basic_block_coll_results_bot_16x32
	( coll_point_group& the_pt_group, block_coll_result& bl_coll_result, 
	block_coll_result& bm_coll_result, block_coll_result& br_coll_result )
{
	// DON'T change this function unless in the future a 16x32 hitbox uses
	// more than three bottom side collision points
	
	#define X(name) \
		name##_coll_result.coord \
			= active_level::get_block_coord_of_point \
			(the_pt_group.get_pt_##name##_16x32()); \
		name##_coll_result.type \
			= active_level::get_block_type_at_coord \
			(name##_coll_result.coord);
	list_of_16x32_bottom_side_coll_point_names(X)
	#undef X
}



// 16x16 sprites
void sprite_base_stuff::block_coll_response_left_16x16( sprite& the_sprite,
	const block_coll_result& lt_coll_result,
	const block_coll_result& lb_coll_result )
{
	the_sprite.in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 )
		* 16 ) - the_sprite.cb_pos_offset.x;
}
void sprite_base_stuff::block_coll_response_top_16x16( sprite& the_sprite, 
	const block_coll_result& tl_coll_result,
	const block_coll_result& tm_coll_result,
	const block_coll_result& tr_coll_result )
{
	the_sprite.in_level_pos.y = make_f24p8( ( tl_coll_result.coord.y + 1 )
		* 16 ) - the_sprite.cb_pos_offset.y;
	
	if ( the_sprite.vel.y < (fixed24p8){0x00} )
	{
		the_sprite.vel.y = {0x00};
	}
	//the_sprite.jump_hold_timer = 0;
	the_sprite.is_jumping = false;
}

void sprite_base_stuff::block_coll_response_right_16x16
	( sprite& the_sprite, const block_coll_result& rt_coll_result,
	const block_coll_result& rb_coll_result )
{
	the_sprite.in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 ) 
		- the_sprite.the_coll_box.size.x - the_sprite.cb_pos_offset.x;
		//- make_f24p8(the_sprite.get_shape_size_as_vec2().x);
}

void sprite_base_stuff::non_slope_block_coll_response_bot_16x16
	( sprite& the_sprite, const block_coll_result& bl_coll_result,
	const block_coll_result& bm_coll_result, 
	const block_coll_result& br_coll_result )
{
	if ( the_sprite.vel.y >= (fixed24p8){0} )
	{
		the_sprite.in_level_pos.y = make_f24p8( bl_coll_result.coord.y 
			* 16 ) 
			//- ( the_sprite.the_coll_box.size.y +
			//the_sprite.cb_pos_offset.y );
			- make_f24p8(the_sprite.get_shape_size_as_vec2().y);
		the_sprite.vel.y = {0x00};
		the_sprite.on_ground = true;
		//the_sprite.jump_hold_timer = 0;
		the_sprite.is_jumping = false;
	}
}
//block_type sprite_base_stuff::slope_block_coll_response_bot_16x16
//	( sprite& the_sprite, coll_point_group& the_pt_group,
//	block_coll_result& bm_coll_result,
//	block_coll_result& bl_coll_result,
//	block_coll_result& br_coll_result, bool hitting_tltr )
//{
//	return bt_air;
//}

block_type sprite_base_stuff::slope_block_coll_response_bot_16x16
	( sprite& the_sprite, coll_point_group& the_pt_group, 
	block_coll_result& bl_coll_result, block_coll_result& bm_coll_result,
	block_coll_result& br_coll_result, bool hitting_tltr )
{
	vec2_f24p8& pt_bm = the_pt_group.get_pt_bm_16x16(),
		& pt_bl = the_pt_group.get_pt_bl_16x16(),
		& pt_br = the_pt_group.get_pt_br_16x16();
	
	// pt_bm, pt_bl, and pt_br converted to the relative coordinate system
	// of the block, with units of WHOLE pixels, with NO subpixels.
	vec2_s32 pt_bm_block_rel_trunc,
		pt_bl_block_rel_trunc,
		pt_br_block_rel_trunc;
	
	// These % operators will be converted to & operators by the
	// compiler
	pt_bm_block_rel_trunc.x = pt_bm.x.trunc_to_int() 
		% num_pixels_per_block_row;
	pt_bm_block_rel_trunc.y = pt_bm.y.trunc_to_int()
		% num_pixels_per_block_col;
	
	pt_bl_block_rel_trunc.x = pt_bl.x.trunc_to_int() 
		% num_pixels_per_block_row;
	pt_bl_block_rel_trunc.y = pt_bl.y.trunc_to_int()
		% num_pixels_per_block_col;
	
	pt_br_block_rel_trunc.x = pt_br.x.trunc_to_int() 
		% num_pixels_per_block_row;
	pt_br_block_rel_trunc.y = pt_br.y.trunc_to_int()
		% num_pixels_per_block_col;
	
	
	// The block y coord points above collision points
	const s32 pt_above_pt_bm_block_coord_y = bm_coll_result.coord.y - 1, 
		pt_above_pt_bl_block_coord_y = bl_coll_result.coord.y - 1,
		pt_above_pt_br_block_coord_y = br_coll_result.coord.y - 1;
	
	// Height mask values for the points to check
	s32 pt_bm_height_mask_value = -1, 
		pt_bl_height_mask_value = -1,
		pt_br_height_mask_value = -1;
	
	// Basically, these pointers are used as aliases for long variable
	// names.
	
	// 45 degree angle slope
	const u32* height_mask_p16_p16
		= grass_slope_p16_p16_block_stuff::height_mask;
	
	// 135 degree angle slope
	const u32* height_mask_n16_p16
		= grass_slope_n16_p16_block_stuff::height_mask;
	
	// Approximately 26.57 degrees angle slope, with two blocks
	const u32* height_mask_p32_p16_short
		= grass_slope_p32_p16_short_block_stuff::height_mask;
	const u32* height_mask_p32_p16_tall
		= grass_slope_p32_p16_tall_block_stuff::height_mask;
	
	// Approximately 153.43 degrees angle slope, with two blocks
	const u32* height_mask_n32_p16_tall
		= grass_slope_n32_p16_tall_block_stuff::height_mask;
	const u32* height_mask_n32_p16_short
		= grass_slope_n32_p16_short_block_stuff::height_mask;
	
	auto find_height_mask_value_normal = [&]
		( const block_coll_result& the_coll_result, 
		s32& height_mask_value, const vec2_s32& pt_block_rel_trunc, 
		s32 pt_above_pt_block_coord_y ) -> void
	{
		// Find height_mask_value.
		
		// 45 degree angle slope
		if ( the_coll_result.type == bt_grass_slope_p16_p16 )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_p16_p16[pt_block_rel_trunc.x];
		}
		// 135 degree angle slope
		else if ( the_coll_result.type == bt_grass_slope_n16_p16 )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_n16_p16[pt_block_rel_trunc.x];
		}
		// Approximately 26.57 degrees angle slope, with two blocks
		else if ( the_coll_result.type == bt_grass_slope_p32_p16_short )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_p32_p16_short
				[pt_block_rel_trunc.x];
		}
		else if ( the_coll_result.type == bt_grass_slope_p32_p16_tall )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_p32_p16_tall
				[pt_block_rel_trunc.x];
		}
		
		// Approximately 153.43 degrees angle slope, with two blocks
		else if ( the_coll_result.type == bt_grass_slope_n32_p16_tall )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_n32_p16_tall
				[pt_block_rel_trunc.x];
		}
		else if ( the_coll_result.type == bt_grass_slope_n32_p16_short )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_n32_p16_short
				[pt_block_rel_trunc.x];
		}
		
		// If the point doesn't intersect a slope block, then check whether
		// the block at the block coord ABOVE the point is a slope
		else
		{
			block_type above_block_type 
				= active_level::get_block_type_at_coord
				( vec2_s32( the_coll_result.coord.x,
				pt_above_pt_block_coord_y ) );
			//next_debug_s32 = above_block_type;
			
			// 45 degree angle slope
			if ( above_block_type == bt_grass_slope_p16_p16 )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_p16_p16
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			// 135 degree angle slope
			else if ( above_block_type == bt_grass_slope_n16_p16 )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_n16_p16
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			// Approximately 26.57 degrees angle slope, with two blocks
			else if ( above_block_type == bt_grass_slope_p32_p16_short )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_p32_p16_short
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			else if ( above_block_type == bt_grass_slope_p32_p16_tall )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_p32_p16_tall
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			
			// Approximately 153.43 degrees angle slope, with two blocks
			else if ( above_block_type == bt_grass_slope_n32_p16_tall )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_n32_p16_tall
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			else if ( above_block_type == bt_grass_slope_n32_p16_short )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_n32_p16_short
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			else
			{
				//show_debug_str_s32("welp");
				//height_mask_value = 0;
			}
		}
	};
	
	auto respond_to_collision = [&]( const coll_point_group& the_pt_group, 
		const block_coll_result& the_coll_result, 
		const s32 height_mask_value, const vec2_s32& pt_block_rel_trunc )
	{
		//next_debug_s32 = num_pixels_per_block_col - pt_block_rel_trunc.y;
		//next_debug_s32 = height_mask_value;
		
		// Check whether the_sprite is inside the slope.
		if ( ( (s32)num_pixels_per_block_col - (s32)pt_block_rel_trunc.y )
			<= height_mask_value )
		{
			//show_debug_str_s32("wow ");
			if ( the_sprite.vel.y >= (fixed24p8){0}
				//&& the_sprite.jump_hold_timer == 0 )
				&& !the_sprite.is_jumping )
			{
				the_sprite.in_level_pos.y = make_f24p8
					( ( the_coll_result.coord.y + 1 )
					* num_pixels_per_block_col - height_mask_value )
					- make_f24p8( the_sprite.get_shape_size_as_vec2().y );
					//- ( the_sprite.the_coll_box.size.y 
					//+ the_sprite.cb_pos_offset );
				
				the_sprite.vel.y = {0x00};
				the_sprite.on_ground = true;
				
				if ( the_sprite.vel.x != (fixed24p8){0} && hitting_tltr )
				{
					the_sprite.in_level_pos.y += make_f24p8(1);
				}
				
			}
		}
		else if ( pt_block_rel_trunc.y == 0 )
		{
			//show_debug_str_s32("okay");
			//the_sprite.in_level_pos.y = make_f24p8
			//	( ( the_coll_result.coord.y + 1 )
			//	* num_pixels_per_block_col - height_mask_value )
			//	- the_sprite.the_coll_box.size.y;
			
			//the_sprite.in_level_pos.y += make_f24p8(1);
			the_sprite.on_ground = false;
			
		}
		else if ( the_sprite.vel.y <= (fixed24p8){0} )
		{
			//show_debug_str_s32("hmmm");
			the_sprite.on_ground = false;
		}
		else
		{
			//show_debug_str_s32("hmm2");
			//the_sprite.on_ground = true;
			the_sprite.on_ground = false;
		}
		
		//show_debug_str_s32("dbst");
		
		//next_debug_s32 = pt_block_rel_trunc.y;
		//next_debug_s32 = (s32)num_pixels_per_block_col
		//	- pt_block_rel_trunc.y;
		//show_debug_str_s32( ( ( (s32)num_pixels_per_block_col
		//	- pt_block_rel_trunc.y ) <= height_mask_value ) 
		//	? "true" : "fals" );
		//next_debug_s32 = (u32)height_mask_value;
		
		//show_debug_str_s32("dben");
		
	};
	
	
	find_height_mask_value_normal( bm_coll_result, pt_bm_height_mask_value,
		pt_bm_block_rel_trunc, pt_above_pt_bm_block_coord_y );
	
	find_height_mask_value_normal( bl_coll_result, pt_bl_height_mask_value,
		pt_bl_block_rel_trunc, pt_above_pt_bl_block_coord_y );
	
	find_height_mask_value_normal( br_coll_result, pt_br_height_mask_value,
		pt_br_block_rel_trunc, pt_above_pt_br_block_coord_y );
	
	//show_debug_str_s32("hstr");
	//next_debug_s32 = pt_bm_height_mask_value;
	//next_debug_s32 = pt_bl_height_mask_value;
	//next_debug_s32 = pt_br_height_mask_value;
	//show_debug_str_s32("hend");
	
	// Find the highest number height_mask_value
	if ( pt_bm_height_mask_value >= pt_bl_height_mask_value
		&& pt_bm_height_mask_value >= pt_br_height_mask_value 
		//&& ( bm_coll_result.type == bt_grass_slope_n16_p16 
		//|| bm_coll_result.type == bt_grass_slope_p16_p16 ) )
		&& bt_is_slope(bm_coll_result.type) )
	{
		// Using pt_bm_height_mask_value
		//show_debug_str_s32("bm  ");
		respond_to_collision( the_pt_group, bm_coll_result, 
			pt_bm_height_mask_value, pt_bm_block_rel_trunc );
		
		return bm_coll_result.type;
	}
	else if ( pt_bl_height_mask_value > pt_bm_height_mask_value
		&& pt_bl_height_mask_value >= pt_br_height_mask_value )
	{
		// Using pt_bl_height_mask_value
		//show_debug_str_s32("bl  ");
		respond_to_collision( the_pt_group, bl_coll_result, 
			pt_bl_height_mask_value, pt_bl_block_rel_trunc );
		
		return bl_coll_result.type;
	}
	else if ( pt_br_height_mask_value > pt_bm_height_mask_value
		&& pt_br_height_mask_value > pt_bl_height_mask_value )
	{
		// Using pt_br_height_mask_value
		//show_debug_str_s32("br  ");
		respond_to_collision( the_pt_group, br_coll_result, 
			pt_br_height_mask_value, pt_br_block_rel_trunc );
		
		return br_coll_result.type;
	}
	else
	{
		//next_debug_s32 = 0xeebbaacc;
		//if ( the_sprite.vel.y >= (fixed24p8){0} )
		//
		//if ( the_sprite.on_ground )
		//{
		//	the_sprite.vel.y = {0x00};
		//	the_sprite.on_ground = true;
		//}
		return bt_air;
	}
	
	
	
}


// 16x32 sprites
void sprite_base_stuff::block_coll_response_left_16x32( sprite& the_sprite,
	const block_coll_result& lt_coll_result,
	const block_coll_result& lm_coll_result, 
	const block_coll_result& lb_coll_result )
{
	//show_debug_str_s32("bkle");
	//show_debug_str_s32("    ");
	the_sprite.in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 ) 
		* 16 ) - the_sprite.cb_pos_offset.x;
	
}
void sprite_base_stuff::block_coll_response_top_16x32( sprite& the_sprite,
	const block_coll_result& tl_coll_result,
	const block_coll_result& tm_coll_result, 
	const block_coll_result& tr_coll_result )
{
	//show_debug_str_s32("bkto");
	//show_debug_str_s32("    ");
	block_coll_response_top_16x16( the_sprite, tl_coll_result, 
		tm_coll_result, tr_coll_result );
}
void sprite_base_stuff::block_coll_response_right_16x32
	( sprite& the_sprite, const block_coll_result& rt_coll_result,
	const block_coll_result& rm_coll_result, 
	const block_coll_result& rb_coll_result )
{
	//show_debug_str_s32("bkri");
	//show_debug_str_s32("    ");
	the_sprite.in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 ) 
		- the_sprite.the_coll_box.size.x - the_sprite.cb_pos_offset.x;
		//- the_sprite.get_shape_size_as_vec2().x );
}
void sprite_base_stuff::non_slope_block_coll_response_bot_16x32
	( sprite& the_sprite, const block_coll_result& bl_coll_result,
	const block_coll_result& bm_coll_result, 
	const block_coll_result& br_coll_result )
{
	//show_debug_str_s32("bkbo");
	//show_debug_str_s32("    ");
	non_slope_block_coll_response_bot_16x16( the_sprite, bl_coll_result, 
		bm_coll_result, br_coll_result );
}
block_type sprite_base_stuff::slope_block_coll_response_bot_16x32
	( sprite& the_sprite, coll_point_group& the_pt_group, 
	block_coll_result& bl_coll_result, block_coll_result& bm_coll_result,
	block_coll_result& br_coll_result, bool hitting_tltr )
{
	vec2_f24p8& pt_bm = the_pt_group.get_pt_bm_16x32(),
		& pt_bl = the_pt_group.get_pt_bl_16x32(),
		& pt_br = the_pt_group.get_pt_br_16x32();
	
	// pt_bm, pt_bl, and pt_br converted to the relative coordinate system
	// of the block, with units of WHOLE pixels, with NO subpixels.
	vec2_s32 pt_bm_block_rel_trunc,
		pt_bl_block_rel_trunc,
		pt_br_block_rel_trunc;
	
	// These % operators will be converted to & operators by the
	// compiler
	pt_bm_block_rel_trunc.x = pt_bm.x.trunc_to_int() 
		% num_pixels_per_block_row;
	pt_bm_block_rel_trunc.y = pt_bm.y.trunc_to_int()
		% num_pixels_per_block_col;
	
	pt_bl_block_rel_trunc.x = pt_bl.x.trunc_to_int() 
		% num_pixels_per_block_row;
	pt_bl_block_rel_trunc.y = pt_bl.y.trunc_to_int()
		% num_pixels_per_block_col;
	
	pt_br_block_rel_trunc.x = pt_br.x.trunc_to_int() 
		% num_pixels_per_block_row;
	pt_br_block_rel_trunc.y = pt_br.y.trunc_to_int()
		% num_pixels_per_block_col;
	
	
	// The block y coord points above collision points
	const s32 pt_above_pt_bm_block_coord_y = bm_coll_result.coord.y - 1, 
		pt_above_pt_bl_block_coord_y = bl_coll_result.coord.y - 1,
		pt_above_pt_br_block_coord_y = br_coll_result.coord.y - 1;
	
	// Height mask values for the points to check
	s32 pt_bm_height_mask_value = -1, 
		pt_bl_height_mask_value = -1,
		pt_br_height_mask_value = -1;
	
	// Basically, these pointers are used as aliases for long variable
	// names.
	
	// 45 degree angle slope
	const u32* height_mask_p16_p16
		= grass_slope_p16_p16_block_stuff::height_mask;
	
	// 135 degree angle slope
	const u32* height_mask_n16_p16
		= grass_slope_n16_p16_block_stuff::height_mask;
	
	// Approximately 26.57 degrees angle slope, with two blocks
	const u32* height_mask_p32_p16_short
		= grass_slope_p32_p16_short_block_stuff::height_mask;
	const u32* height_mask_p32_p16_tall
		= grass_slope_p32_p16_tall_block_stuff::height_mask;
	
	// Approximately 153.43 degrees angle slope, with two blocks
	const u32* height_mask_n32_p16_tall
		= grass_slope_n32_p16_tall_block_stuff::height_mask;
	const u32* height_mask_n32_p16_short
		= grass_slope_n32_p16_short_block_stuff::height_mask;
	
	auto find_height_mask_value_normal = [&]
		( const block_coll_result& the_coll_result, s32& height_mask_value,
		const vec2_s32& pt_block_rel_trunc, s32 pt_above_pt_block_coord_y )
		-> void
	{
		// Find height_mask_value.
		
		// 45 degree angle slope
		if ( the_coll_result.type == bt_grass_slope_p16_p16 )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_p16_p16[pt_block_rel_trunc.x];
		}
		// 135 degree angle slope
		else if ( the_coll_result.type == bt_grass_slope_n16_p16 )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_n16_p16[pt_block_rel_trunc.x];
		}
		// Approximately 26.57 degrees angle slope, with two blocks
		else if ( the_coll_result.type == bt_grass_slope_p32_p16_short )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_p32_p16_short
				[pt_block_rel_trunc.x];
		}
		else if ( the_coll_result.type == bt_grass_slope_p32_p16_tall )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_p32_p16_tall
				[pt_block_rel_trunc.x];
		}
		
		// Approximately 153.43 degrees angle slope, with two blocks
		else if ( the_coll_result.type == bt_grass_slope_n32_p16_tall )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_n32_p16_tall
				[pt_block_rel_trunc.x];
		}
		else if ( the_coll_result.type == bt_grass_slope_n32_p16_short )
		{
			//show_debug_str_s32("norm");
			height_mask_value = height_mask_n32_p16_short
				[pt_block_rel_trunc.x];
		}
		
		// If the point doesn't intersect a slope block, then check whether
		// the block at the block coord ABOVE the point is a slope
		else
		{
			block_type above_block_type 
				= active_level::get_block_type_at_coord
				( vec2_s32( the_coll_result.coord.x,
				pt_above_pt_block_coord_y ) );
			//next_debug_s32 = above_block_type;
			
			// 45 degree angle slope
			if ( above_block_type == bt_grass_slope_p16_p16 )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_p16_p16
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			// 135 degree angle slope
			else if ( above_block_type == bt_grass_slope_n16_p16 )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_n16_p16
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			// Approximately 26.57 degrees angle slope, with two blocks
			else if ( above_block_type == bt_grass_slope_p32_p16_short )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_p32_p16_short
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			else if ( above_block_type == bt_grass_slope_p32_p16_tall )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_p32_p16_tall
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			
			// Approximately 153.43 degrees angle slope, with two blocks
			else if ( above_block_type == bt_grass_slope_n32_p16_tall )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_n32_p16_tall
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			else if ( above_block_type == bt_grass_slope_n32_p16_short )
			{
				//show_debug_str_s32("abov");
				height_mask_value = height_mask_n32_p16_short
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			else
			{
				//show_debug_str_s32("welp");
				//height_mask_value = 0;
			}
		}
	};
	
	auto respond_to_collision = [&]( const coll_point_group& the_pt_group, 
		const block_coll_result& the_coll_result, 
		const s32 height_mask_value, const vec2_s32& pt_block_rel_trunc )
	{
		//next_debug_s32 = num_pixels_per_block_col - pt_block_rel_trunc.y;
		//next_debug_s32 = height_mask_value;
		
		// Check whether the_sprite is inside the slope.
		if ( ( (s32)num_pixels_per_block_col - (s32)pt_block_rel_trunc.y )
			<= height_mask_value )
		{
			//show_debug_str_s32("wow ");
			if ( the_sprite.vel.y >= (fixed24p8){0}
				//&& the_sprite.jump_hold_timer == 0 )
				&& !the_sprite.is_jumping )
			{
				the_sprite.in_level_pos.y = make_f24p8
					( ( the_coll_result.coord.y + 1 )
					* num_pixels_per_block_col - height_mask_value )
					- make_f24p8( the_sprite.get_shape_size_as_vec2().y );
					//- ( the_sprite.the_coll_box.size.y 
					//+ the_sprite.cb_pos_offset );
				
				the_sprite.vel.y = {0x00};
				the_sprite.on_ground = true;
				
				if ( the_sprite.vel.x != (fixed24p8){0} && hitting_tltr )
				{
					the_sprite.in_level_pos.y += make_f24p8(1);
				}
				
			}
		}
		else if ( pt_block_rel_trunc.y == 0 )
		{
			//show_debug_str_s32("okay");
			//the_sprite.in_level_pos.y = make_f24p8
			//	( ( the_coll_result.coord.y + 1 )
			//	* num_pixels_per_block_col - height_mask_value )
			//	- the_sprite.the_coll_box.size.y;
			
			//the_sprite.in_level_pos.y += make_f24p8(1);
			the_sprite.on_ground = false;
			
		}
		else if ( the_sprite.vel.y <= (fixed24p8){0} )
		{
			//show_debug_str_s32("hmmm");
			the_sprite.on_ground = false;
		}
		else
		{
			//show_debug_str_s32("hmm2");
			//the_sprite.on_ground = true;
			the_sprite.on_ground = false;
		}
		
		//show_debug_str_s32("dbst");
		
		//next_debug_s32 = pt_block_rel_trunc.y;
		//next_debug_s32 = (s32)num_pixels_per_block_col
		//	- pt_block_rel_trunc.y;
		//show_debug_str_s32( ( ( (s32)num_pixels_per_block_col
		//	- pt_block_rel_trunc.y ) <= height_mask_value ) 
		//	? "true" : "fals" );
		//next_debug_s32 = (u32)height_mask_value;
		
		//show_debug_str_s32("dben");
		
	};
	
	
	find_height_mask_value_normal( bm_coll_result, pt_bm_height_mask_value,
		pt_bm_block_rel_trunc, pt_above_pt_bm_block_coord_y );
	
	find_height_mask_value_normal( bl_coll_result, pt_bl_height_mask_value,
		pt_bl_block_rel_trunc, pt_above_pt_bl_block_coord_y );
	
	find_height_mask_value_normal( br_coll_result, pt_br_height_mask_value,
		pt_br_block_rel_trunc, pt_above_pt_br_block_coord_y );
	
	//show_debug_str_s32("hstr");
	//next_debug_s32 = pt_bm_height_mask_value;
	//next_debug_s32 = pt_bl_height_mask_value;
	//next_debug_s32 = pt_br_height_mask_value;
	//show_debug_str_s32("hend");
	
	// Find the highest number height_mask_value
	if ( pt_bm_height_mask_value >= pt_bl_height_mask_value
		&& pt_bm_height_mask_value >= pt_br_height_mask_value 
		//&& ( bm_coll_result.type == bt_grass_slope_n16_p16 
		//|| bm_coll_result.type == bt_grass_slope_p16_p16 ) )
		&& bt_is_slope(bm_coll_result.type) )
	{
		// Using pt_bm_height_mask_value
		//show_debug_str_s32("bm  ");
		respond_to_collision( the_pt_group, bm_coll_result, 
			pt_bm_height_mask_value, pt_bm_block_rel_trunc );
		
		return bm_coll_result.type;
	}
	else if ( pt_bl_height_mask_value > pt_bm_height_mask_value
		&& pt_bl_height_mask_value >= pt_br_height_mask_value )
	{
		// Using pt_bl_height_mask_value
		//show_debug_str_s32("bl  ");
		respond_to_collision( the_pt_group, bl_coll_result, 
			pt_bl_height_mask_value, pt_bl_block_rel_trunc );
		
		return bl_coll_result.type;
	}
	else if ( pt_br_height_mask_value > pt_bm_height_mask_value
		&& pt_br_height_mask_value > pt_bl_height_mask_value )
	{
		// Using pt_br_height_mask_value
		//show_debug_str_s32("br  ");
		respond_to_collision( the_pt_group, br_coll_result, 
			pt_br_height_mask_value, pt_br_block_rel_trunc );
		
		return br_coll_result.type;
	}
	else
	{
		//next_debug_s32 = 0xeebbaacc;
		//if ( the_sprite.vel.y >= (fixed24p8){0} )
		
		//if ( the_sprite.on_ground )
		//{
		//	the_sprite.vel.y = {0x00};
		//	the_sprite.on_ground = true;
		//}
		return bt_air;
	}
	
	
}


void sprite_base_stuff::apply_gravity( sprite& the_sprite )
{
	the_sprite.vel.y += grav_acc;
	
	if ( the_sprite.vel.y > max_y_vel )
	{
		the_sprite.vel.y = max_y_vel;
	}
}



void sprite_base_stuff::block_collision_stuff_16x16( sprite& the_sprite )
{
	// The collision points
	coll_point_group the_pt_group;
	
	generate_coll_point_group_16x16( the_sprite, the_pt_group );
	
	// The block_coll_result's
	block_coll_result lt_coll_result, lb_coll_result, tl_coll_result,
		tm_coll_result, tr_coll_result, rt_coll_result, rb_coll_result,
		bl_coll_result, bm_coll_result, br_coll_result;
	
	// Get the block_coll_result's
	get_basic_block_coll_results_left_16x16( the_pt_group, lt_coll_result,
		lb_coll_result );
	get_basic_block_coll_results_right_16x16( the_pt_group, rt_coll_result,
		rb_coll_result );
	
	get_basic_block_coll_results_top_16x16( the_pt_group, tl_coll_result,
		tm_coll_result, tr_coll_result );
	get_basic_block_coll_results_bot_16x16( the_pt_group, bl_coll_result,
		bm_coll_result, br_coll_result );
	
	
	// Lambda functions for non-slope block collision response
	auto any_left_response = [&]() -> void
	{
		block_coll_response_left_16x16( the_sprite, lt_coll_result, 
			lb_coll_result );
	};
	
	auto any_top_response = [&]() -> void
	{
		block_coll_response_top_16x16( the_sprite, tl_coll_result, 
			tm_coll_result, tr_coll_result );
	};
	
	auto any_right_response = [&]() -> void
	{
		block_coll_response_right_16x16( the_sprite, rt_coll_result, 
			rb_coll_result );
	};
	
	auto any_non_slope_bot_response = [&]() -> void
	{
		non_slope_block_coll_response_bot_16x16( the_sprite, 
			bl_coll_result, bm_coll_result, br_coll_result );
	};
	
	//show_debug_str_s32( the_sprite.on_ground ? "ongn" : "offg" );
	
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
			
			the_sprite.on_ground = false;
			
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
			if ( the_sprite.vel.y < (fixed24p8){0} )
			{
				the_sprite.in_level_pos.y -= the_sprite.vel.y;
				the_sprite.vel.y = (fixed24p8){0};
				the_sprite.on_ground = true;
				//the_sprite.jump_hold_timer = 0;
				the_sprite.is_jumping = false;
			}
			
			// Don't let the_sprite move through walls
			if ( lt_coll_result.type != bt_air 
				|| lb_coll_result.type != bt_air )
			{
				if ( the_sprite.vel.x < (fixed24p8){0} )
				{
					//the_sprite.vel.x = make_f24p8(4);
					the_sprite.in_level_pos.x -= the_sprite.vel.x;
				}
			}
			if ( rt_coll_result.type != bt_air 
				|| rb_coll_result.type != bt_air )
			{
				if ( the_sprite.vel.x > (fixed24p8){0} )
				{
					//the_sprite.vel.x = make_f24p8(-4);
					the_sprite.in_level_pos.x -= the_sprite.vel.x;
				}
			}
			
			slope_block_coll_response_bot_16x16( the_sprite, the_pt_group,
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
				= slope_block_coll_response_bot_16x16( the_sprite, 
				the_pt_group, bl_coll_result, bm_coll_result, 
				br_coll_result );
			
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
			
			the_sprite.on_ground = false;
			
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
	//show_debug_str_s32( the_sprite.on_ground ? "ongn" : "offg" );
}

void sprite_base_stuff::block_collision_stuff_16x32( sprite& the_sprite )
{
	// The collision points
	coll_point_group the_pt_group;
	
	generate_coll_point_group_16x32( the_sprite, the_pt_group );
	
	// The block_coll_result's
	block_coll_result lt_coll_result, lm_coll_result, lb_coll_result, 
		tl_coll_result, tm_coll_result, tr_coll_result, rt_coll_result,
		rm_coll_result, rb_coll_result, bl_coll_result, bm_coll_result, 
		br_coll_result;
	
	// Get the block_coll_result's
	get_basic_block_coll_results_left_16x32( the_pt_group, lt_coll_result,
		lm_coll_result, lb_coll_result );
	get_basic_block_coll_results_right_16x32( the_pt_group, rt_coll_result,
		rm_coll_result, rb_coll_result );
	
	get_basic_block_coll_results_top_16x32( the_pt_group, tl_coll_result,
		tm_coll_result, tr_coll_result );
	get_basic_block_coll_results_bot_16x32( the_pt_group, bl_coll_result,
		bm_coll_result, br_coll_result );
	
	
	// Lambda functions for non-slope block collision response
	auto any_left_response = [&]() -> void
	{
		block_coll_response_left_16x32( the_sprite, lt_coll_result, 
			lm_coll_result, lb_coll_result );
	};
	
	auto any_top_response = [&]() -> void
	{
		block_coll_response_top_16x32( the_sprite, tl_coll_result, 
			tm_coll_result, tr_coll_result );
	};
	
	auto any_right_response = [&]() -> void
	{
		block_coll_response_right_16x32( the_sprite, rt_coll_result, 
			rm_coll_result, rb_coll_result );
	};
	
	auto any_non_slope_bot_response = [&]() -> void
	{
		non_slope_block_coll_response_bot_16x32( the_sprite, 
			bl_coll_result, bm_coll_result, br_coll_result );
	};
	
	//show_debug_str_s32( the_sprite.on_ground ? "ongn" : "offg" );
	
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
			//show_debug_str_s32("    ");
			
			the_sprite.on_ground = false;
			
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
		//show_debug_str_s32("    ");
		
		if ( bt_is_neither_air_nor_slope(tl_coll_result.type) 
			|| bt_is_neither_air_nor_slope(tr_coll_result.type) )
		{
			//show_debug_str_s32("tltr");
			//show_debug_str_s32("    ");
			
			// Disable jumping
			if ( the_sprite.vel.y < (fixed24p8){0} )
			{
				the_sprite.in_level_pos.y -= the_sprite.vel.y;
				the_sprite.vel.y = (fixed24p8){0};
				the_sprite.on_ground = true;
				//the_sprite.jump_hold_timer = 0;
				the_sprite.is_jumping = false;
			}
			
			// Don't let the_sprite move through walls
			if ( lt_coll_result.type != bt_air 
				|| lm_coll_result.type != bt_air
				|| lb_coll_result.type != bt_air )
			{
				if ( the_sprite.vel.x < (fixed24p8){0} )
				{
					//the_sprite.vel.x = make_f24p8(4);
					the_sprite.in_level_pos.x -= the_sprite.vel.x;
				}
			}
			if ( rt_coll_result.type != bt_air 
				|| rm_coll_result.type != bt_air
				|| rb_coll_result.type != bt_air )
			{
				if ( the_sprite.vel.x > (fixed24p8){0} )
				{
					//the_sprite.vel.x = make_f24p8(-4);
					the_sprite.in_level_pos.x -= the_sprite.vel.x;
				}
			}
			
			slope_block_coll_response_bot_16x32( the_sprite, the_pt_group,
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
				= slope_block_coll_response_bot_16x32( the_sprite, 
				the_pt_group, bl_coll_result, bm_coll_result, 
				br_coll_result );
			
			//show_debug_str_s32("bt  ");
			next_debug_s32 = the_slope_block_type;
			
			
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
			
			the_sprite.on_ground = false;
			
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
	//show_debug_str_s32( the_sprite.on_ground ? "ongn" : "offg" );
	
	
}

void sprite_base_stuff::block_collision_stuff_32x16( sprite& the_sprite )
{
	
}
void sprite_base_stuff::block_collision_stuff_32x32( sprite& the_sprite )
{
	
}
