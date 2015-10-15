#include "sprite_manager_class.hpp"

#include "../../gba_specific_stuff/button_stuff.hpp"
#include "../../gba_specific_stuff/interrupt_stuff.hpp"



sprite sprite_manager::the_player __attribute__((_iwram));

std::array< sprite, sprite_manager::max_num_sprites > 
	sprite_manager::the_sprites; //__attribute__((_iwram));


void sprite_manager::init_the_player ( const vec2_f24p8& s_in_level_pos, 
	const vec2_u32& the_level_size_2d, bg_point& camera_pos )
{
	sprite_stuff_array[st_player]->init( the_player,
		s_in_level_pos, the_level_size_2d, camera_pos );
}


void sprite_manager::init_horiz_level_sprite_ipg_lists
	( const sprite_init_param_group* the_ext_sprite_ipg_arr, 
	u32 the_ext_sprite_ipg_arr_size )
{
	for ( u32 i=0; i<the_ext_sprite_ipg_arr_size; ++i )
	{
		if ( the_ext_sprite_ipg_arr[i].type != st_default )
		{
			active_level::horiz_level_sprite_ipg_lists 
				[the_ext_sprite_ipg_arr[i].initial_block_grid_x_coord]
				.push_front(the_ext_sprite_ipg_arr[i]);
		}
	}
	
	
	for ( auto iter = active_level::horiz_level_sprite_ipg_lists.begin(); 
		iter != active_level::horiz_level_sprite_ipg_lists.end(); 
		++iter )
	{
		if ( !iter->empty() )
		{
			iter->sort();
		}
	}
	
}

void sprite_manager::some_sprite_init_thing()
{
	
	sprite_stuff_array[st_waffle]->init(the_sprites[0]);
	
	the_sprites[0].in_level_pos = the_player.in_level_pos;
	
	the_sprites[0].update_f24p8_positions();
	the_sprites[0].update_on_screen_pos(bgofs_mirror[0].curr);
	the_sprites[0].copy_the_oam_entry_to_oam_mirror(1);
	
	for ( u32 i=1; i<the_sprites.size(); ++i )
	{
		sprite& the_spr = the_sprites[i];
		sprite& the_prev_spr = the_sprites[i - 1];
		
		sprite_stuff_array[st_muffin]->init(the_spr);
		
		the_spr.in_level_pos = the_prev_spr.in_level_pos 
			+ vec2_s32( 0x1000, 0 );
		
		the_spr.update_f24p8_positions();
		the_spr.update_on_screen_pos(bgofs_mirror[0].curr);
		
		the_spr.copy_the_oam_entry_to_oam_mirror(i + 1);
		
	}
}


void sprite_manager::initial_sprite_spawning_from_level_data
	( const vec2_u32& the_level_size_2d, bg_point& camera_pos, 
	int& next_oam_index )
{
	sprite_init_param_group* player_ipg = NULL;
	
	// Find the player's level data
	for ( auto which_list=active_level::horiz_level_sprite_ipg_lists
			.begin();
		which_list!=active_level::horiz_level_sprite_ipg_lists.end();
		++which_list )
	{
		for ( auto which_node=which_list->begin(); 
			which_node!=which_list->end();
			++which_node )
		{
			if ( which_node->type == st_player )
			{
				// Spawn the player.
				if ( player_ipg == NULL )
				{
					player_ipg = &(*which_node);
					
					// Mark the player as active
					player_ipg->spawn_state = sss_active;
				}
				
				// Kill st_player sprites if there's more than one in the
				// level data.
				else
				{
					which_node->spawn_state = sss_dead;
				}
			}
		}
	}
	
	
	vec2_f24p8 player_initial_in_level_pos
		= { make_f24p8( player_ipg->initial_block_grid_x_coord << 4 ),
		make_f24p8( player_ipg->initial_block_grid_y_coord << 4 ) };
	
	init_the_player( player_initial_in_level_pos, the_level_size_2d,
		camera_pos );
	//next_debug_u32 = (vu32)(player_ipg);
	//next_debug_u32 = player_ipg->type;
	//nocash_soft_break();
	
	
	
	auto which_spr = the_sprites.begin();
	
	// Convert 
	vec2_f24p8 camera_pos_f24p8;
	camera_pos_f24p8.x = make_f24p8(camera_pos.x);
	camera_pos_f24p8.y = make_f24p8(camera_pos.y);
	
	// Convert the position of the camera to block grid coordinates
	vec2_f24p8 camera_block_grid_pos;
	camera_block_grid_pos.x = make_f24p8( camera_pos.x >> 4 );
	camera_block_grid_pos.y = make_f24p8( camera_pos.y >> 4 );
	
	
	for ( auto which_list=active_level::horiz_level_sprite_ipg_lists
			.begin();
		which_list!=active_level::horiz_level_sprite_ipg_lists.end();
		++which_list )
	{
		for ( auto which_node=which_list->begin(); 
			which_node!=which_list->end(); 
			++which_node )
		{
			vec2_u32 spr_block_grid_coord;
			spr_block_grid_coord.x = which_node->initial_block_grid_x_coord;
			spr_block_grid_coord.y = which_node->initial_block_grid_y_coord;
			
			vec2_f24p8 spr_in_level_pos;
			spr_in_level_pos.x = make_f24p8( spr_block_grid_coord.x * 16 );
			spr_in_level_pos.y = make_f24p8( spr_block_grid_coord.y * 16 );
			
			vec2_f24p8 spr_on_screen_pos;
			spr_on_screen_pos.x = spr_in_level_pos.x - camera_pos_f24p8.x;
			spr_on_screen_pos.y = spr_in_level_pos.y - camera_pos_f24p8.y;
			
			// Don't spawn the sprite if it's HORIZONTALLY off-screen
			if ( !( spr_on_screen_pos.x.data >= 0 
				&& spr_on_screen_pos.x.data <= ( screen_width << 8 ) ) )
			{
				continue;
			}
			
			// Don't spawn the sprite if it corresponds to the player's
			// level data
			if ( which_node->type == st_player )
			{
				continue;
			}
			
			
			while ( which_spr->the_sprite_type != st_default 
				&& which_spr != the_sprites.end() )
			{
				++which_spr;
			}
			
			which_spr->reinit_with_sprite_ipg( &(*which_node) );
			
			//++which_spr;
			
			if ( which_spr == the_sprites.end() )
			{
				break;
			}
		}
		
		if ( which_spr == the_sprites.end() )
		{
			break;
		}
	}
	
	
	// sprite_manager::the_player uses OAM index 0.
	next_oam_index = 1;
	
	// Run each active sprite's update_part_1() function.
	for ( u32 i=0; i<the_sprites.size(); ++i )
	{
		sprite& the_spr = the_sprites[i];
		
		if ( the_spr.the_sprite_type != st_default )
		{
			sprite_stuff_array[the_spr.the_sprite_type]
				->update_part_1(the_spr);
		}
	}
	
	// Run each active sprite's update_part_2() function.
	for ( u32 i=0; i<the_sprites.size(); ++i )
	{
		sprite& the_spr = the_sprites[i];
		
		if ( the_spr.the_sprite_type != st_default )
		{
			sprite_stuff_array[the_spr.the_sprite_type]
				->update_part_2( the_spr, bgofs_mirror[0].curr,
				next_oam_index );
		}
	}
	
}


void sprite_manager::initial_sprite_spawning_from_level_data_old
	( const bg_point& camera_pos, int& next_oam_index )
{
	auto iter3 = the_sprites.begin();
	
	vec2_f24p8 camera_pos_f24p8;
	camera_pos_f24p8.x = make_f24p8(camera_pos.x);
	camera_pos_f24p8.y = make_f24p8(camera_pos.y);
	
	vec2_f24p8 camera_block_grid_pos;
	camera_block_grid_pos.x = make_f24p8( camera_pos.x >> 4 );
	camera_block_grid_pos.y = make_f24p8( camera_pos.y >> 4 );
	
	
	for ( auto iter=active_level::horiz_level_sprite_ipg_lists.begin();
		iter!=active_level::horiz_level_sprite_ipg_lists.end();
		++iter )
	{
		for ( auto iter2=iter->begin(); iter2!=iter->end(); ++iter2 )
		{
			vec2_u32 spr_block_grid_coord;
			spr_block_grid_coord.x = iter2->initial_block_grid_x_coord;
			spr_block_grid_coord.y = iter2->initial_block_grid_y_coord;
			
			vec2_f24p8 spr_in_level_pos;
			spr_in_level_pos.x = make_f24p8( spr_block_grid_coord.x * 16 );
			spr_in_level_pos.y = make_f24p8( spr_block_grid_coord.y * 16 );
			
			vec2_f24p8 spr_on_screen_pos;
			spr_on_screen_pos.x = spr_in_level_pos.x - camera_pos_f24p8.x;
			spr_on_screen_pos.y = spr_in_level_pos.y - camera_pos_f24p8.y;
			
			
			if ( !( spr_on_screen_pos.x.data >= 0 
				&& spr_on_screen_pos.y.data >= 0
				&& spr_on_screen_pos.x.data <= ( screen_width << 8 )
				&& spr_on_screen_pos.y.data <= ( screen_height << 8 ) ) )
			{
				continue;
			}
			
			
			while ( iter3->the_sprite_type != st_default 
				&& iter3 != the_sprites.end() )
			{
				++iter3;
			}
			
			// Apparently reinit_with_sprite_ipg is bugged?
			iter3->reinit_with_sprite_ipg( &(*iter2) );
			
			//++iter3;
			
			if ( iter3 == the_sprites.end() )
			{
				break;
			}
		}
		
		if ( iter3 == the_sprites.end() )
		{
			break;
		}
	}
	
	next_oam_index = 1;
	
	for ( u32 i=0; i<the_sprites.size(); ++i )
	{
		sprite& the_spr = the_sprites[i];
		
		if ( the_spr.the_sprite_type != st_default )
		{
			sprite_stuff_array[the_spr.the_sprite_type]
				->update_part_1(the_spr);
		}
	}
	
	for ( u32 i=0; i<the_sprites.size(); ++i )
	{
		sprite& the_spr = the_sprites[i];
		
		if ( the_spr.the_sprite_type != st_default )
		{
			sprite_stuff_array[the_spr.the_sprite_type]
				->update_part_2( the_spr, bgofs_mirror[0].curr,
				next_oam_index );
		}
	}
	
	
}





