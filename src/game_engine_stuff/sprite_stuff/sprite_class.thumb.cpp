#include "sprite_class.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"
#include "../gfx_manager_class.hpp"

sprite::sprite()
{
	//the_sprite_type = st_player;
	
	//in_level_pos = { 0, 0 };
	//vel = { 0, 0 };
	
	//on_ground = false;
	//jump_hold_timer = 0;
	
	//the_oam_entry = { 0, 0, 0, 0 };
	
	//set_shape_size(oam_entry::ss_16x16);
	//
	//the_regular_coll_box.pos = { 0, 0 };
	//the_regular_coll_box.size = { make_f24p8(16), make_f24p8(16) };
	//
	//cb_pos_offset = { 0, 0 };
	
	//memfill32( misc_data_u, 0, misc_data_size );
	//memfill32( misc_data_s, 0, misc_data_size );
	
	u32 old_vram_chunk_index = vram_chunk_index;
	
	memfill32( this, 0, sizeof(sprite) / sizeof(u32) );
	
	the_oam_entry.set_tile_number(0);
	the_oam_entry.set_pal_number(sps_player);
	
	set_shape_size(oam_entry::ss_16x16);
	the_regular_coll_box.size = { 14 << fixed24p8::shift, 
		14 << fixed24p8::shift };
	cb_pos_offset = { 1 << fixed24p8::shift, 1 << fixed24p8::shift };
	
	vram_chunk_index = old_vram_chunk_index;
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
//			sprite_stuff_array[the_sprite_type]->init( *this, 
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

void sprite::reinit_with_sprite_ipg
	( sprite_init_param_group* s_the_sprite_ipg )
{
	u32 old_vram_chunk_index = vram_chunk_index;
	
	switch ( s_the_sprite_ipg->spawn_state )
	{
		case sss_not_active:
			memfill32( this, 0, sizeof(sprite) / sizeof(u32) );
			
			the_sprite_ipg = s_the_sprite_ipg;
			the_sprite_ipg->spawn_state = sss_active;
			
			the_sprite_type = the_sprite_ipg->type;
			in_level_pos.x = make_f24p8
				( the_sprite_ipg->initial_block_grid_x_coord * 16 );
			in_level_pos.y = make_f24p8
				( the_sprite_ipg->initial_block_grid_y_coord * 16 );
			
			sprite_stuff_array[the_sprite_type]->init( *this,
				!the_sprite_ipg->facing_right );
			
			vram_chunk_index = old_vram_chunk_index;
			break;
			
		case sss_active:
		case sss_dead:
		default:
			break;
		
	}
}

void sprite::reinit_with_sprite_ipg( u32 s_vram_chunk_index,
	sprite_init_param_group* s_the_sprite_ipg )
{
	switch ( s_the_sprite_ipg->spawn_state )
	{
		case sss_not_active:
			memfill32( this, 0, sizeof(sprite) / sizeof(u32) );
			
			the_sprite_ipg = s_the_sprite_ipg;
			the_sprite_ipg->spawn_state = sss_active;
			
			the_sprite_type = the_sprite_ipg->type;
			in_level_pos.x = make_f24p8
				( the_sprite_ipg->initial_block_grid_x_coord * 16 );
			in_level_pos.y = make_f24p8
				( the_sprite_ipg->initial_block_grid_y_coord * 16 );
			
			sprite_stuff_array[the_sprite_type]->init( *this,
				!the_sprite_ipg->facing_right );
			
			vram_chunk_index = s_vram_chunk_index;
			break;
			
		case sss_active:
		case sss_dead:
		default:
			break;
		
	}
}




void sprite::update_on_screen_pos( const bg_point& camera_pos )
{
	vec2_f24p8 on_screen_pos_f24p8;
	
	on_screen_pos_f24p8.x = ( in_level_pos.x - make_f24p8(camera_pos.x) );
	on_screen_pos_f24p8.y = ( in_level_pos.y - make_f24p8(camera_pos.y) );
	
	vec2_u32 ss_vec2 = get_shape_size_as_vec2();
	vec2_f24p8 offset;
	offset.x = make_f24p8(ss_vec2.x);
	offset.y = make_f24p8(ss_vec2.y);
	
	if ( on_screen_pos_f24p8.x + offset.x >= (fixed24p8){0} 
		&& on_screen_pos_f24p8.x <= make_f24p8(screen_width)
		&& on_screen_pos_f24p8.y + offset.y >= (fixed24p8){0}
		&& on_screen_pos_f24p8.y <= make_f24p8(screen_height) )
	{
		the_oam_entry.show_non_affine();
			
		the_oam_entry.set_x_coord 
			( on_screen_pos_f24p8.x.round_to_int() );
		the_oam_entry.set_y_coord 
			( on_screen_pos_f24p8.y.round_to_int() );
	}
	else
	{
		// Hide the sprite if it's not on screen
		the_oam_entry.hide_non_affine();
	}
}


void sprite::camera_follow_basic( bg_point& camera_pos )
{
	vec2_f24p8 on_screen_pos = get_on_screen_pos(camera_pos);
	
	fixed24p8 on_screen_bottom_pos = on_screen_pos.y 
		+ make_f24p8(get_shape_size_as_vec2().y);
	
	if ( ( on_screen_pos.x <= make_f24p8(100) && vel.x.data < 0 ) 
		|| ( on_screen_pos.x >= make_f24p8(140) && vel.x.data > 0 ) )
	{
		camera_pos.x += vel.x.round_to_int();
	}
	
	//if ( ( on_screen_pos.y <= make_f24p8(20) && vel.y.data < 0 ) 
	//	|| ( on_screen_pos.y >= make_f24p8(80) && vel.y.data > 0 ) )
	//{
	//	camera_pos.y += vel.y.round_to_int();
	//}
	
	
	if ( on_screen_pos.y <= make_f24p8(20) )
	{
		if (!on_ground)
		{
			camera_pos.y += vel.y.round_to_int();
		}
		else
		{
			camera_pos.y -= 4;
		}
	}
	else if ( on_screen_bottom_pos >= make_f24p8(60) )
	{
		if ( vel.y.data >= 0 )
		{
			if (!on_ground)
			{
				camera_pos.y += vel.y.round_to_int();
			}
			else
			{
				camera_pos.y += 4;
			}
		}
	}
}

void sprite::center_camera_almost( bg_point& camera_pos ) const
{
	camera_pos.x = ( in_level_pos.x 
		- (fixed24p8){ screen_width << 7 } ).round_to_int();
	camera_pos.y = ( in_level_pos.y 
		- (fixed24p8){ screen_height << 7 } ).round_to_int();
}




void sprite::block_collision_stuff()
{
	sprite_stuff_array[the_sprite_type]->block_collision_stuff(*this);
}




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
