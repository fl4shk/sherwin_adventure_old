#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"

#include "sprite_manager_class.hpp"



void sprite_base_stuff::get_basic_block_coll_results_left_16x16
	( coll_point_group& the_pt_group, block_coll_result& lt_coll_result, 
	block_coll_result& lb_coll_result )
{
	lt_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_lt_16x16());
	lt_coll_result.type = active_level::get_block_type_at_coord
		(lt_coll_result.coord);
	
	lb_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_lb_16x16());
	lb_coll_result.type = active_level::get_block_type_at_coord
		(lb_coll_result.coord);
}
void sprite_base_stuff::get_basic_block_coll_results_top_16x16
	( coll_point_group& the_pt_group, block_coll_result& tl_coll_result, 
	block_coll_result& tm_coll_result, block_coll_result& tr_coll_result ) 
	
{
	tl_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_tl_16x16());
	tl_coll_result.type = active_level::get_block_type_at_coord
		(tl_coll_result.coord);
	
	tm_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_tm_16x16());
	tm_coll_result.type = active_level::get_block_type_at_coord
		(tm_coll_result.coord);
	
	tr_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_tr_16x16());
	tr_coll_result.type = active_level::get_block_type_at_coord
		(tr_coll_result.coord);
}
void sprite_base_stuff::get_basic_block_coll_results_right_16x16
	( coll_point_group& the_pt_group, block_coll_result& rt_coll_result, 
	block_coll_result& rb_coll_result )
{
	rt_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_rt_16x16());
	rt_coll_result.type = active_level::get_block_type_at_coord
		(rt_coll_result.coord);
	
	rb_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_rb_16x16());
	rb_coll_result.type = active_level::get_block_type_at_coord
		(rb_coll_result.coord);
}
void sprite_base_stuff::get_basic_block_coll_results_bot_16x16
	( coll_point_group& the_pt_group, block_coll_result& bl_coll_result, 
	block_coll_result& bm_coll_result, block_coll_result& br_coll_result )
{
	bl_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_bl_16x16());
	bl_coll_result.type = active_level::get_block_type_at_coord
		(bl_coll_result.coord);
	
	bm_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_bm_16x16());
	bm_coll_result.type = active_level::get_block_type_at_coord
		(bm_coll_result.coord);
	
	br_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_br_16x16());
	br_coll_result.type = active_level::get_block_type_at_coord
		(br_coll_result.coord);
}


void sprite_base_stuff::get_basic_block_coll_results_left_16x32
	( coll_point_group& the_pt_group, block_coll_result& lt_coll_result, 
	block_coll_result& lm_coll_result, block_coll_result& lb_coll_result )
{
	// DON'T change this function unless in the future a 16x32 hitbox uses
	// more than three left side collision points
	
	lt_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_lt_16x32());
	lt_coll_result.type = active_level::get_block_type_at_coord
		(lt_coll_result.coord);
	
	lm_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_lm_16x32());
	lm_coll_result.type = active_level::get_block_type_at_coord
		(lm_coll_result.coord);
	
	lb_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_lb_16x32());
	lb_coll_result.type = active_level::get_block_type_at_coord
		(lb_coll_result.coord);
	
}
void sprite_base_stuff::get_basic_block_coll_results_top_16x32
	( coll_point_group& the_pt_group, block_coll_result& tl_coll_result, 
	block_coll_result& tm_coll_result, block_coll_result& tr_coll_result )
{
	// DON'T change this function unless in the future a 16x32 hitbox uses
	// more than three top side collision points
	
	tl_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_tl_16x32());
	tl_coll_result.type = active_level::get_block_type_at_coord
		(tl_coll_result.coord);
	
	tm_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_tm_16x32());
	tm_coll_result.type = active_level::get_block_type_at_coord
		(tm_coll_result.coord);
	
	tr_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_tr_16x32());
	tr_coll_result.type = active_level::get_block_type_at_coord
		(tr_coll_result.coord);
	
}
void sprite_base_stuff::get_basic_block_coll_results_right_16x32
	( coll_point_group& the_pt_group, block_coll_result& rt_coll_result,
	block_coll_result& rm_coll_result, block_coll_result& rb_coll_result )
{
	// DON'T change this function unless in the future a 16x32 hitbox uses
	// more than three right side collision points
	
	rt_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_rt_16x32());
	rt_coll_result.type = active_level::get_block_type_at_coord
		(rt_coll_result.coord);
	
	rm_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_rm_16x32());
	rm_coll_result.type = active_level::get_block_type_at_coord
		(rm_coll_result.coord);
	
	rb_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_rb_16x32());
	rb_coll_result.type = active_level::get_block_type_at_coord
		(rb_coll_result.coord);
	
}
void sprite_base_stuff::get_basic_block_coll_results_bot_16x32
	( coll_point_group& the_pt_group, block_coll_result& bl_coll_result, 
	block_coll_result& bm_coll_result, block_coll_result& br_coll_result )
{
	// DON'T change this function unless in the future a 16x32 hitbox uses
	// more than three bottom side collision points
	bl_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_bl_16x32());
	bl_coll_result.type = active_level::get_block_type_at_coord
		(bl_coll_result.coord);
	
	bm_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_bm_16x32());
	bm_coll_result.type = active_level::get_block_type_at_coord
		(bm_coll_result.coord);
	
	br_coll_result.coord = active_level::get_block_coord_of_point 
		(the_pt_group.get_pt_br_16x32());
	br_coll_result.type = active_level::get_block_type_at_coord
		(br_coll_result.coord);
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
	
	the_sprite.vel.y = {0x00};
	the_sprite.jump_hold_timer = 0;
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
		the_sprite.jump_hold_timer = 0;
	}
}
void sprite_base_stuff::slope_block_coll_response_bot_16x16
	( sprite& the_sprite, coll_point_group& the_pt_group,
	block_coll_result& bm_coll_result,
	block_coll_result& bl_coll_result,
	block_coll_result& br_coll_result, bool hitting_tltr )
{
}


// 16x32 sprites
void sprite_base_stuff::block_coll_response_left_16x32( sprite& the_sprite,
	const block_coll_result& lt_coll_result,
	const block_coll_result& lm_coll_result, 
	const block_coll_result& lb_coll_result )
{
	the_sprite.in_level_pos.x = make_f24p8( ( lt_coll_result.coord.x + 1 ) 
		* 16 ) - the_sprite.cb_pos_offset.x;
	
}
void sprite_base_stuff::block_coll_response_top_16x32( sprite& the_sprite,
	const block_coll_result& tl_coll_result,
	const block_coll_result& tm_coll_result, 
	const block_coll_result& tr_coll_result )
{
	block_coll_response_top_16x16( the_sprite, tl_coll_result, 
		tm_coll_result, tr_coll_result );
}
void sprite_base_stuff::block_coll_response_right_16x32
	( sprite& the_sprite, const block_coll_result& rt_coll_result,
	const block_coll_result& rm_coll_result, 
	const block_coll_result& rb_coll_result )
{
	the_sprite.in_level_pos.x = make_f24p8( rt_coll_result.coord.x * 16 ) 
		- the_sprite.the_coll_box.size.x - the_sprite.cb_pos_offset.x;
		//- the_sprite.get_shape_size_as_vec2().x );
}
void sprite_base_stuff::non_slope_block_coll_response_bot_16x32
	( sprite& the_sprite, const block_coll_result& bl_coll_result,
	const block_coll_result& bm_coll_result, 
	const block_coll_result& br_coll_result )
{
	non_slope_block_coll_response_bot_16x16( the_sprite, bl_coll_result, 
		bm_coll_result, br_coll_result );
}
void sprite_base_stuff::slope_block_coll_response_bot_16x32
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
	
	// Basically, these two pointers are used as aliases for long variable
	// names.
	const u32* height_mask_135_degrees
		= grass_slope_135_degrees_block_stuff::height_mask;
	const u32* height_mask_45_degrees
		= grass_slope_45_degrees_block_stuff::height_mask;
	
	auto find_height_mask_value_normal = [&]
		( const block_coll_result& the_coll_result, s32& height_mask_value,
		const vec2_s32& pt_block_rel_trunc, s32 pt_above_pt_block_coord_y )
		-> void
	{
		// Find height_mask_value.
		if ( the_coll_result.type == bt_grass_slope_45_degrees )
		{
			show_debug_str_s32("norm");
			height_mask_value = height_mask_45_degrees
				[pt_block_rel_trunc.x];
		}
		else if ( the_coll_result.type == bt_grass_slope_135_degrees )
		{
			show_debug_str_s32("norm");
			height_mask_value = height_mask_135_degrees
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
			
			if ( above_block_type == bt_grass_slope_45_degrees )
			{
				show_debug_str_s32("abov");
				height_mask_value = height_mask_45_degrees
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			else if ( above_block_type == bt_grass_slope_135_degrees )
			{
				show_debug_str_s32("abov");
				height_mask_value = height_mask_135_degrees
					[pt_block_rel_trunc.x] + num_pixels_per_block_col;
			}
			else
			{
				show_debug_str_s32("welp");
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
			show_debug_str_s32("wow ");
			if ( the_sprite.vel.y >= (fixed24p8){0}
				&& the_sprite.jump_hold_timer == 0 )
			{
				the_sprite.in_level_pos.y = make_f24p8
					( ( the_coll_result.coord.y + 1 )
					* num_pixels_per_block_col - height_mask_value )
					- make_f24p8( the_sprite.get_shape_size_as_vec2().y );
					//- ( the_sprite.the_coll_box.size.y 
					//+ the_sprite.cb_pos_offset );
				
				the_sprite.vel.y = {0x00};
				the_sprite.on_ground = true;
				//the_sprite.jump_hold_timer = max_jump_hold_timer;
				
				if ( the_sprite.vel.x != (fixed24p8){0} && hitting_tltr )
				{
					the_sprite.in_level_pos.y += make_f24p8(1);
				}
				
			}
		}
		else if ( pt_block_rel_trunc.y == 0 )
		{
			show_debug_str_s32("okay");
			//the_sprite.in_level_pos.y = make_f24p8
			//	( ( the_coll_result.coord.y + 1 )
			//	* num_pixels_per_block_col - height_mask_value )
			//	- the_sprite.the_coll_box.size.y;
			
			//the_sprite.in_level_pos.y += make_f24p8(1);
			the_sprite.on_ground = false;
			//the_sprite.jump_hold_timer = 0;
			
		}
		else if ( the_sprite.vel.y <= (fixed24p8){0} )
		{
			show_debug_str_s32("hmmm");
			the_sprite.on_ground = false;
		}
		else
		{
			show_debug_str_s32("hmm2");
			the_sprite.on_ground = true;
		}
		
		show_debug_str_s32("dbst");
		
		next_debug_s32 = pt_block_rel_trunc.y;
		next_debug_s32 = (s32)num_pixels_per_block_col
			- pt_block_rel_trunc.y;
		show_debug_str_s32( ( ( (s32)num_pixels_per_block_col
			- pt_block_rel_trunc.y ) <= height_mask_value ) 
			? "true" : "fals" );
		next_debug_s32 = (u32)height_mask_value;
		
		show_debug_str_s32("dben");
		
	};
	
	
	find_height_mask_value_normal( bm_coll_result, pt_bm_height_mask_value,
		pt_bm_block_rel_trunc, pt_above_pt_bm_block_coord_y );
	
	find_height_mask_value_normal( bl_coll_result, pt_bl_height_mask_value,
		pt_bl_block_rel_trunc, pt_above_pt_bl_block_coord_y );
	
	find_height_mask_value_normal( br_coll_result, pt_br_height_mask_value,
		pt_br_block_rel_trunc, pt_above_pt_br_block_coord_y );
	
	show_debug_str_s32("hstr");
	next_debug_s32 = pt_bm_height_mask_value;
	next_debug_s32 = pt_bl_height_mask_value;
	next_debug_s32 = pt_br_height_mask_value;
	show_debug_str_s32("hend");
	
	// Find the highest number height_mask_value
	if ( pt_bm_height_mask_value >= pt_bl_height_mask_value
		&& pt_bm_height_mask_value >= pt_br_height_mask_value 
		&& ( bm_coll_result.type == bt_grass_slope_135_degrees 
		|| bm_coll_result.type == bt_grass_slope_45_degrees ) )
	{
		// Using pt_bm_height_mask_value
		show_debug_str_s32("bm  ");
		respond_to_collision( the_pt_group, bm_coll_result, 
			pt_bm_height_mask_value, pt_bm_block_rel_trunc );
	}
	else if ( pt_bl_height_mask_value > pt_bm_height_mask_value
		&& pt_bl_height_mask_value >= pt_br_height_mask_value )
	{
		// Using pt_bl_height_mask_value
		show_debug_str_s32("bl  ");
		respond_to_collision( the_pt_group, bl_coll_result, 
			pt_bl_height_mask_value, pt_bl_block_rel_trunc );
	}
	else if ( pt_br_height_mask_value > pt_bm_height_mask_value
		&& pt_br_height_mask_value > pt_bl_height_mask_value )
	{
		// Using pt_br_height_mask_value
		show_debug_str_s32("br  ");
		respond_to_collision( the_pt_group, br_coll_result, 
			pt_br_height_mask_value, pt_br_block_rel_trunc );
	}
	else
	{
		//next_debug_s32 = 0xeebbaacc;
		//if ( the_sprite.vel.y >= (fixed24p8){0} 
		//	&& the_sprite.jump_hold_timer == 0 )
		
		//if ( the_sprite.on_ground )
		//{
		//	the_sprite.vel.y = {0x00};
		//	the_sprite.on_ground = true;
		//}
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
	
	
	block_coll_result 
		lt_coll_result, lb_coll_result, 
		tl_coll_result, tm_coll_result, tr_coll_result, 
		rt_coll_result, rb_coll_result,
		bl_coll_result, bm_coll_result, br_coll_result;
	
	
	get_basic_block_coll_results_left_16x16( the_pt_group, lt_coll_result,
		lb_coll_result );
	get_basic_block_coll_results_right_16x16( the_pt_group, rt_coll_result,
		rb_coll_result );
	
	get_basic_block_coll_results_top_16x16( the_pt_group, tl_coll_result,
		tm_coll_result, tr_coll_result );
	get_basic_block_coll_results_bot_16x16( the_pt_group, bl_coll_result,
		bm_coll_result, br_coll_result );
	
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
	
	
	if ( tl_coll_result.type != bt_air || tr_coll_result.type != bt_air )
	{
		show_debug_str_s32("tltr");
		
		// When not dealing with slopes, this method is used
		//if ( bm_coll_result.type != bt_grass_slope_135_degrees 
		//	&& bm_coll_result.type != bt_grass_slope_45_degrees 
		//	&& bl_coll_result.type != bt_grass_slope_135_degrees 
		//	&& br_coll_result.type != bt_grass_slope_45_degrees 
		//	&& lb_coll_result.type != bt_grass_slope_135_degrees 
		//	&& rb_coll_result.type != bt_grass_slope_45_degrees )
		{
			show_debug_str_s32("nslp");
			
			any_top_response();
			
			if ( lt_coll_result.type != bt_air )
			{
				any_left_response();
			}
			
			else if ( rt_coll_result.type != bt_air )
			{
				any_right_response();
			}
		}
		//else
		//{
		//	show_debug_str_s32("slop");
		//	
		//	if ( the_sprite.vel.y < (fixed24p8){0} )
		//	{
		//		// Disable jumping
		//		the_sprite.in_level_pos.y -= the_sprite.vel.y;
		//		the_sprite.vel.y = (fixed24p8){0};
		//		the_sprite.on_ground = true;
		//		the_sprite.jump_hold_timer = 0;
		//	}
		//	
		//	if ( lt_coll_result.type != bt_air 
		//		|| lb_coll_result.type != bt_air )
		//	{
		//		if ( the_sprite.vel.x < (fixed24p8){0} )
		//		{
		//			//the_sprite.vel.x = make_f24p8(4);
		//			the_sprite.in_level_pos.x -= the_sprite.vel.x;
		//		}
		//	}
		//	
		//	else if ( rt_coll_result.type != bt_air 
		//		|| rb_coll_result.type != bt_air )
		//	{
		//		if ( the_sprite.vel.x > (fixed24p8){0} )
		//		{
		//			//the_sprite.vel.x = make_f24p8(-4);
		//			the_sprite.in_level_pos.x -= the_sprite.vel.x;
		//		}
		//	}
		//	
		//	slope_block_coll_response_bot_16x16( the_sprite, the_pt_group,
		//		bl_coll_result, bm_coll_result, br_coll_result, true );
		//}
		
	}
	
	else if ( bl_coll_result.type != bt_air
		|| br_coll_result.type != bt_air )
	{
		show_debug_str_s32("blbr");
		
		// When not dealing with slopes, this method is used
		//if ( bm_coll_result.type != bt_grass_slope_135_degrees 
		//	&& bm_coll_result.type != bt_grass_slope_45_degrees 
		//	&& bl_coll_result.type != bt_grass_slope_135_degrees 
		//	&& br_coll_result.type != bt_grass_slope_45_degrees 
		//	&& lb_coll_result.type != bt_grass_slope_135_degrees 
		//	&& rb_coll_result.type != bt_grass_slope_45_degrees )
		{
			show_debug_str_s32("nslp");
			
			any_non_slope_bot_response();
			if ( lt_coll_result.type != bt_air)
			{
				any_left_response();
			}
			
			else if ( rt_coll_result.type != bt_air )
			{
				any_right_response();
			}
			
		}
		//// When dealing with slopes, this method is used
		//else
		//{
		//	show_debug_str_s32("slop");
		//	
		//	slope_block_coll_response_bot_16x16( the_sprite, the_pt_group,
		//		bl_coll_result, bm_coll_result, br_coll_result );
		//	
		//	// Don't let the_sprite move through walls
		//	if ( lt_coll_result.type != bt_air )
		//	{
		//		any_left_response();
		//	}
		//	else if ( rt_coll_result.type != bt_air )
		//	{
		//		any_right_response();
		//	}
		//}
		
	}
	else
	{
		show_debug_str_s32("leri");
		
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
	
	show_debug_str_s32( the_sprite.on_ground ? "ongn" : "offg" );
	
	// When not dealing with slopes, this method is used
	if ( bm_coll_result.type != bt_grass_slope_135_degrees 
		&& bm_coll_result.type != bt_grass_slope_45_degrees 
		&& bl_coll_result.type != bt_grass_slope_135_degrees 
		&& br_coll_result.type != bt_grass_slope_45_degrees 
		&& lb_coll_result.type != bt_grass_slope_135_degrees 
		&& rb_coll_result.type != bt_grass_slope_45_degrees )
	{
		show_debug_str_s32("nslp");
		
		if ( tl_coll_result.type != bt_air 
			|| tr_coll_result.type != bt_air )
		{
			show_debug_str_s32("tltr");
			
			if ( lt_coll_result.type != bt_air )
			{
				any_left_response();
			}
			
			else if ( rt_coll_result.type != bt_air )
			{
				any_right_response();
			}
			
			any_top_response();
			
			
		}
		else if ( bl_coll_result.type != bt_air
			|| br_coll_result.type != bt_air )
		{
			show_debug_str_s32("blbr");
			
			any_non_slope_bot_response();
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
		else
		{
			show_debug_str_s32("leri");
			
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
	else
	{
		show_debug_str_s32("slop");
		
		if ( tl_coll_result.type != bt_air 
			|| tr_coll_result.type != bt_air )
		{
			show_debug_str_s32("tltr");
			
			if ( the_sprite.vel.y < (fixed24p8){0} )
			{
				// Disable jumping
				the_sprite.in_level_pos.y -= the_sprite.vel.y;
				the_sprite.vel.y = (fixed24p8){0};
				the_sprite.on_ground = true;
				the_sprite.jump_hold_timer = 0;
			}
			
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
			
			else if ( rt_coll_result.type != bt_air 
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
			show_debug_str_s32("blbr");
			
			slope_block_coll_response_bot_16x32( the_sprite, the_pt_group,
				bl_coll_result, bm_coll_result, br_coll_result );
			
			// Don't let the_sprite move through walls
			if ( lt_coll_result.type != bt_air 
				|| ( lm_coll_result.type != bt_air 
				&& lm_coll_result.type != bt_grass_slope_45_degrees
				&& lm_coll_result.type != bt_grass_slope_135_degrees )
				|| ( lb_coll_result.type != bt_air 
				&& lb_coll_result.type != bt_grass_slope_45_degrees
				&& lb_coll_result.type != bt_grass_slope_135_degrees ) )
			{
				any_left_response();
			}
			if ( rt_coll_result.type != bt_air 
				|| ( rm_coll_result.type != bt_air 
				&& rm_coll_result.type != bt_grass_slope_45_degrees
				&& rm_coll_result.type != bt_grass_slope_135_degrees )
				|| ( rb_coll_result.type != bt_air 
				&& rb_coll_result.type != bt_grass_slope_45_degrees
				&& rb_coll_result.type != bt_grass_slope_135_degrees ) )
			{
				any_right_response();
			}
		}
		else
		{
			show_debug_str_s32("leri");
			
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
	show_debug_str_s32( the_sprite.on_ground ? "ongn" : "offg" );
	
	
}

void sprite_base_stuff::block_collision_stuff_32x16( sprite& the_sprite )
{
	
}
void sprite_base_stuff::block_collision_stuff_32x32( sprite& the_sprite )
{
	
}
