#include "sprite_manager_class.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"




void sprite_manager::spawn_sprites_if_needed
	( const prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	
	prev_curr_pair<s32> camera_block_grid_pos_x;
	
	camera_block_grid_pos_x.prev = camera_pos_pc_pair.prev.x >> 4;
	camera_block_grid_pos_x.curr = camera_pos_pc_pair.curr.x >> 4;
	
	
	// "cm_dir" is short for "camera_movement_direction".
	int cm_dir;
	
	if ( camera_block_grid_pos_x.curr > camera_block_grid_pos_x.prev )
	{
		cm_dir = 1;
	}
	else if ( camera_block_grid_pos_x.curr < camera_block_grid_pos_x.prev )
	{
		cm_dir = -1;
	}
	else
	{
		cm_dir = 0;
	}
	
	
	// If the camera moved from left to right, add an offset of the size of
	// the screen in blocks
	if ( cm_dir > 0 )
	{
		camera_block_grid_pos_x.prev += screen_width_in_blocks;
		camera_block_grid_pos_x.curr += screen_width_in_blocks;
	}
	
	
	// Don't spawn any sprites if the camera has not horizontally moved
	// by enough pixels.
	if ( cm_dir == 0 )
	{
		return;
	}
	
	
	u32 next_sprite_index = 0;
	
	// Find a free sprite slot.
	for ( ; next_sprite_index<the_sprites.size(); ++next_sprite_index )
	{
		if ( the_sprites[next_sprite_index].the_sprite_type == st_default )
		{
			break;
		}
	}
	
	// Don't spawn any sprites if too many are active.
	if ( next_sprite_index == the_sprites.size() )
	{
		return;
	}
	
	
	// If the camera moved from left to right
	//if ( camera_block_grid_pos_x.curr > camera_block_grid_pos_x.prev )
	if ( cm_dir > 0 )
	{
		// Spawn whole columns of sprites at a time, regardless of whether
		// they are are veritcally on screen.  This assumes that all levels
		// are horizontal.
		for ( s32 i=camera_block_grid_pos_x.prev;
			i<=camera_block_grid_pos_x.curr;
			++i )
		{
			
			// Spawn sprites from the top of the column to the bottom of
			// the column.
			for ( auto iter=active_level::horiz_level_sprite_ipg_lists[i]
					.begin();
				iter!=active_level::horiz_level_sprite_ipg_lists[i].end();
				++iter )
			{
				// Find the lowest FREE sprite slot, if any.
				while ( ( the_sprites[next_sprite_index].the_sprite_type 
					!= st_default )
					&& ( next_sprite_index != the_sprites.size() ) )
				{
					++next_sprite_index;
				}
				
				// If there isn't a free sprite slot, then stop trying to
				// spawn sprites.
				if ( next_sprite_index == the_sprites.size() )
				{
					break;
				}
				
				the_sprites[next_sprite_index].reinit_with_sprite_ipg
					( &(*iter) );
				
			}
			
			// If there isn't a free sprite slot, then stop trying to spawn
			// sprites.
			if ( next_sprite_index == the_sprites.size() )
			{
				break;
			}
			
		}
	}
	
	// If the camera moved from right to left
	else 
	{
		// Spawn whole columns of sprites at a time, regardless of whether
		// they are are veritcally on screen.  This assumes that all levels
		// are horizontal.
		for ( s32 i=camera_block_grid_pos_x.prev + 5;
			i>=camera_block_grid_pos_x.curr - 1;
			--i )
		{
			if ( i < 0 )
			{
				break;
			}
			
			
			// Spawn sprites from the top of the column to the bottom of
			// the column.
			for ( auto iter=active_level::horiz_level_sprite_ipg_lists[i]
					.begin();
				iter!=active_level::horiz_level_sprite_ipg_lists[i].end();
				++iter )
			{
				
				// Find the lowest FREE sprite slot, if any.
				while ( ( the_sprites[next_sprite_index].the_sprite_type 
					!= st_default )
					&& ( next_sprite_index != the_sprites.size() ) )
				{
					++next_sprite_index;
				}
				
				// If there isn't a free sprite slot, then stop trying to
				// spawn sprites.
				if ( next_sprite_index == the_sprites.size() )
				{
					break;
				}
				
				the_sprites[next_sprite_index].reinit_with_sprite_ipg
					( &(*iter) );
				
			}
			
			// If there isn't a free sprite slot, then stop trying to spawn
			// sprites.
			if ( next_sprite_index == the_sprites.size() )
			{
				break;
			}
			
		}
		
	}
	
}


void sprite_manager::despawn_sprites_if_needed
	( const prev_curr_pair<bg_point>& camera_pos_pc_pair )
{
	// Sprites are despawned only when they are HORIZONTALLY too far off
	// screen.
	constexpr s32 max_left = -( ( 2 * 16 ) << 8 ),
		max_right = ( screen_width + 2 * 16 ) << 8;
	
	
	vec2_f24p8 camera_pos_curr_f24p8;
	camera_pos_curr_f24p8.x = make_f24p8(camera_pos_pc_pair.curr.x);
	camera_pos_curr_f24p8.y = make_f24p8(camera_pos_pc_pair.curr.y);
	
	
	for ( auto iter=the_sprites.begin(); iter!=the_sprites.end(); ++iter )
	{
		if ( iter->the_sprite_type != st_default )
		{
			fixed24p8 spr_on_screen_pos_x
				= iter->in_level_pos.x - camera_pos_curr_f24p8.x;
			
			if ( !( spr_on_screen_pos_x.data >= max_left
				&& spr_on_screen_pos_x.data <= max_right ) )
			{
				// I might eventually create iter->despawn() so that
				// sprites can control HOW they despawn
				//iter->despawn();
				
				iter->the_sprite_type = st_default;
				if ( iter->the_sprite_ipg != NULL )
				{
					iter->the_sprite_ipg->spawn_state = sss_not_active;
				}
			}
		}
		
	}
	
}



// This is a temporary function.  It should be replaced by a function that
// inserts sprite spawning parameters into a list.  The sprites from said
// list would be spawned from within the function called
// spawn_sprites_if_needed().
void sprite_manager::spawn_a_sprite_basic ( sprite_type the_sprite_type, 
	const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos, 
	bool facing_left )
{
	u32 next_sprite_index = 0;
	
	// Find a free sprite slot.
	for ( ; next_sprite_index<the_sprites.size(); ++next_sprite_index )
	{
		if ( the_sprites[next_sprite_index].the_sprite_type == st_default )
		{
			break;
		}
	}
	
	// Don't spawn any sprites if too many are active.
	if ( next_sprite_index == the_sprites.size() )
	{
		return;
	}
	
	the_sprites[next_sprite_index].reinit_by_spawning( the_sprite_type,
		s_in_level_pos, camera_pos, facing_left );
	
	
}

void sprite_manager::update_all_sprites
	( const vec2_u32& the_level_size_2d, 
	prev_curr_pair<bg_point>& camera_pos_pc_pair, int& next_oam_index )
{
	sprite_stuff_array[the_player.the_sprite_type]
		->update_part_1(the_player);
	
	next_oam_index = 1;
	
	u32 num_active_sprites = 0;
	
	sprite* the_active_sprites[max_num_sprites];
	
	for ( u32 i=0; i<the_sprites.size(); ++i )
	{
		sprite& the_spr = the_sprites[i];
		if ( the_spr.the_sprite_type != st_default )
		{
			the_active_sprites[num_active_sprites++] = &the_spr;
		}
	}
	
	
	for ( u32 i=0; i<num_active_sprites; ++i )
	{
		sprite& the_spr = *(the_active_sprites[i]);
		sprite_stuff_array[the_spr.the_sprite_type]
			->update_part_1(the_spr);
	}
	
	sprite_stuff_array[the_player.the_sprite_type]->update_part_2
		( the_player, camera_pos_pc_pair.curr, the_level_size_2d );
	
	
	
	for ( u32 i=0; i<num_active_sprites; ++i )
	{
		sprite& the_spr = *(the_active_sprites[i]);
		
		if ( the_spr.the_sprite_type == st_default )
		{
			continue;
		}
		
		sprite_stuff_array[the_spr.the_sprite_type]->update_part_2
			( the_spr, camera_pos_pc_pair.curr, next_oam_index );
		
		if ( i == 0 )
		{
			for ( u32 j=1; j<num_active_sprites; ++j )
			{
				sprite& the_other_spr = *(the_active_sprites[j]);
				
				if ( coll_box_intersects_now( the_spr.the_coll_box,
					the_other_spr.the_coll_box ) )
				{
					debug_arr_f8p8[0] = make_f8p8(8);
				}
			}
		}
		else if ( i > 0 && i < num_active_sprites - 1 )
		{
			for ( u32 j=0; j<i; ++j )
			{
				sprite& the_other_spr = *(the_active_sprites[j]);
				
				if ( coll_box_intersects_now( the_spr.the_coll_box,
					the_other_spr.the_coll_box ) )
				{
					debug_arr_f8p8[0] = make_f8p8(8);
				}
			}
			for ( u32 j=i+1; j<num_active_sprites; ++j )
			{
				sprite& the_other_spr = *(the_active_sprites[j]);
				
				if ( coll_box_intersects_now( the_spr.the_coll_box,
					the_other_spr.the_coll_box ) )
				{
					debug_arr_f8p8[0] = make_f8p8(8);
				}
			}
		}
		
	}
}
