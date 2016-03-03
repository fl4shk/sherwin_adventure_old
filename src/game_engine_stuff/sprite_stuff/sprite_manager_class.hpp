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


#ifndef sprite_manager_class_hpp
#define sprite_manager_class_hpp

#include "../level_stuff/sprite_level_data_stuff.hpp"
//#include "../level_stuff/active_level_manager_class.hpp"
#include "../level_stuff/active_level_class.hpp"

#include <array>
#include <forward_list>

#include "sprite_class.hpp"

// This is a class that controls the spawning, despawning, and killing of
// sprites.  The sprite list stuff is part of the active_level class.
class sprite_manager
{
public:		// variables
	
	static constexpr u32 max_num_player_secondary_sprites = 4;
	//static constexpr u32 max_num_player_secondary_sprites = 10;
	
	static constexpr u32 max_num_secondary_sprites = 10;
	
	//static constexpr u32 max_num_regular_sprites = 40;
	static constexpr u32 max_num_regular_sprites = 30;
	//static constexpr u32 max_num_regular_sprites = 20;
	
	
	
	static std::array< sprite, max_num_player_secondary_sprites >
		the_player_secondary_sprites;
	
	// The array of secondary active sprites, not counting those "claimed"
	// by the_player.
	static std::array< sprite, max_num_secondary_sprites > 
		the_secondary_sprites;
	
	
	static sprite the_player;
	
	// The array of REGULAR active sprites, not counting the_player.
	static std::array< sprite, max_num_regular_sprites > the_sprites;
	
	
	
	//static constexpr u32 the_player_vram_chunk_index = 1;
	//static constexpr u32 
	//	the_player_secondary_sprites_starting_vram_chunk_index = 2;
	//static constexpr u32 the_active_sprites_starting_vram_chunk_index 
	//	= the_player_secondary_sprites_starting_vram_chunk_index 
	//	+ max_num_player_secondary_sprites;
	//static constexpr u32 the_secondary_sprites_starting_vram_chunk_index
	//	= the_active_sprites_starting_vram_chunk_index 
	//	+ max_num_regular_sprites;
	
	static constexpr u32
		the_player_secondary_sprites_starting_vram_chunk_index = 1;
	
	static constexpr u32 the_secondary_sprites_starting_vram_chunk_index
		= the_player_secondary_sprites_starting_vram_chunk_index
		+ max_num_player_secondary_sprites;
	
	static constexpr u32 the_player_vram_chunk_index 
		= the_secondary_sprites_starting_vram_chunk_index 
		+ max_num_secondary_sprites;
	
	static constexpr u32 the_active_sprites_starting_vram_chunk_index
		= the_player_vram_chunk_index + 1;
	
	
	
	
	// OAM indices and VRAM chunk indices are shared.
	static constexpr u32 the_player_secondary_sprites_starting_oam_index 
		= the_player_secondary_sprites_starting_vram_chunk_index;
	
	static constexpr u32 the_secondary_sprites_starting_oam_index 
		= the_secondary_sprites_starting_vram_chunk_index;
	
	static constexpr u32 the_player_oam_index 
		= the_player_vram_chunk_index;
	
	static constexpr u32 the_active_sprites_starting_oam_index
		= the_active_sprites_starting_vram_chunk_index;
	
	
	static int next_oam_index __attribute__((_iwram));
	
public:		// functions
	
	static void init_the_player ( const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_sublevel_size_2d, bg_point& camera_pos );
	
	// This function initializes the vram_chunk_index of each sprite in
	// the_sprites.
	static inline void init_the_sprite_arrays()
	{
		//u32 vram_chunk_index = 1;
		//
		//for ( sprite& spr : the_sprites )
		//{
		//	spr.set_vram_chunk_index(vram_chunk_index++);
		//}
		
		// Secondary sprites "claimed" by the_player.
		for ( u32 i=0; i<max_num_player_secondary_sprites; ++i )
		{
			the_player_secondary_sprites[i].set_vram_chunk_index( i 
				+ the_player_secondary_sprites_starting_vram_chunk_index );
		}
		
		// Other secondary sprites
		for ( u32 i=0; i<max_num_secondary_sprites; ++i )
		{
			the_secondary_sprites[i].set_vram_chunk_index( i
				+ the_secondary_sprites_starting_vram_chunk_index );
		}
		
		// Regular sprites
		for ( u32 i=0; i<max_num_regular_sprites; ++i )
		{
			the_sprites[i].set_vram_chunk_index( i 
				+ the_active_sprites_starting_vram_chunk_index );
		}
		
	}
	
	
	static void init_horiz_sublevel_sprite_ipg_lists
		( const sprite_init_param_group* the_ext_sprite_ipg_arr, 
		u32 the_ext_sprite_ipg_arr_size );
	
	static void some_sprite_init_thing();
	
	//static void initial_sprite_spawning_from_sublevel_data
	//	( const vec2_u32& the_sublevel_size_2d, bg_point& camera_pos );
	
	// The 
	static void initial_sprite_spawning_at_start_of_level
		( bg_point& camera_pos );
	
	static void initial_sprite_spawning_at_intra_sublevel_warp
		( bg_point& camera_pos, u32 sublevel_entrance_index );
	
	// This function is put in IWRAM because when the_player warps around a
	// particular sublevel without CHANGING sublevels, sprites need to be
	// spawned, which can be an intensive operation.
	static void initial_sprite_spawning_shared_code
		( bg_point& camera_pos ) __attribute__((_iwram_code));
	
	
	static void initial_sprite_spawning_from_sublevel_data_old
		( const bg_point& camera_pos );
	
	static void spawn_sprites_if_needed
		( const prev_curr_pair<bg_point>& camera_pos_pc_pair ) 
		__attribute__((_iwram_code));
	static void despawn_sprites_if_needed
		( const bg_point& camera_pos ) __attribute__((_iwram_code));
	
	static inline void upload_tiles_of_active_sprites_to_vram()
	{
		// Clear the first 32x32-pixel VRAM chunk.  This prevents unused
		// OAM indices from displaying any graphics.  Perhaps this should
		// be optimized to use only a single 8x8-pixel VRAM chunk.
		memfill32( &(((tile*)obj_tile_vram)[0]), 0, sizeof(tile)
			* gfx_manager::num_tiles_in_ss_32x32 / sizeof(u32) );
		
		gfx_manager::upload_sprite_tiles_to_vram(the_player);
		
		auto for_loop_contents = [&]( sprite& spr ) -> void
		{
			// These two if statements probably accomplish the same goal,
			// which is why one of them is commented out
			//if ( spr.get_vram_chunk_index() != 0 )
			if ( spr.the_sprite_type != st_default )
			{
				gfx_manager::upload_sprite_tiles_to_vram(spr);
			}
		};
		
		for ( sprite& spr : sprite_manager::the_player_secondary_sprites )
		{
			for_loop_contents(spr);
		}
		
		for ( sprite& spr : sprite_manager::the_sprites )
		{
			for_loop_contents(spr);
		}
		
		for ( sprite& spr : sprite_manager::the_secondary_sprites )
		{
			for_loop_contents(spr);
		}
	}
	
	static s32 spawn_a_player_secondary_sprite_basic
		( sprite_type the_sprite_type, const vec2_f24p8& s_in_level_pos, 
		const bg_point& camera_pos, bool facing_left=false ) 
		__attribute__((_iwram_code));
	
	// This is a temporary function.  It should be replaced by a function
	// that inserts sprite spawning parameters into a list.  The sprites
	// from said list would be spawned from within the function called
	// spawn_sprites_if_needed().
	// That said, this is PROBABLY good enough.
	static void spawn_a_sprite_basic( sprite_type the_sprite_type, 
		const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos, 
		bool facing_left=false )
		__attribute__((_iwram_code));
	
	static s32 spawn_a_secondary_sprite_basic( sprite_type the_sprite_type,
		const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos, 
		bool facing_left=false ) __attribute__((_iwram_code));
	
	
	static void update_all_sprites( const vec2_u32& the_sublevel_size_2d,
		prev_curr_pair<bg_point>& camera_pos_pc_pair ) 
		__attribute__((_iwram_code));
	
};




#endif		// sprite_manager_class_hpp
