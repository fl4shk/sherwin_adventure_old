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
	
	static sprite the_player __attribute__((_iwram));
	
	//static constexpr u32 max_num_regular_sprites = 40;
	static constexpr u32 max_num_regular_sprites = 30;
	
	static constexpr u32 the_player_vram_chunk_index = 1;
	static constexpr u32 the_active_sprites_starting_vram_chunk_index = 2;
	
	// The array of active sprites (not counting the_player).  If
	// necessary, an sa_free_list<max_num_regular_sprites> might be used for
	// finding a free index in the future.  However, it is unlikely that
	// doing so will be necessary with a maximum of only
	// max_num_regular_sprites active sprites at once.
	static std::array< sprite, max_num_regular_sprites > the_sprites;
	
	//static 
	
	static int next_oam_index __attribute__((_iwram));
	
public:		// functions
	
	static void init_the_player ( const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_sublevel_size_2d, bg_point& camera_pos );
	
	// This function initializes the vram_chunk_index of each sprite in
	// the_sprites.
	static inline void init_the_array_of_active_sprites()
	{
		//u32 vram_chunk_index = 1;
		//
		//for ( sprite& spr : the_sprites )
		//{
		//	spr.set_vram_chunk_index(vram_chunk_index++);
		//}
		
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
	
	static void initial_sprite_spawning_shared_code
		( bg_point& camera_pos );
	
	
	static void initial_sprite_spawning_from_sublevel_data_old
		( const bg_point& camera_pos );
	
	static void spawn_sprites_if_needed
		( const prev_curr_pair<bg_point>& camera_pos_pc_pair ) 
		__attribute__((_iwram_code));
	static void despawn_sprites_if_needed
		( const prev_curr_pair<bg_point>& camera_pos_pc_pair )
		__attribute__((_iwram_code));
	
	static inline void upload_tiles_of_active_sprites_to_vram()
	{
		// Clear the first 32x32-pixel VRAM chunk
		memfill32( &(((tile*)obj_tile_vram)[0]), 0, sizeof(tile)
			* gfx_manager::num_tiles_in_ss_32x32 / sizeof(u32) );
		
		gfx_manager::upload_sprite_tiles_to_vram(the_player);
		
		for ( sprite& spr : sprite_manager::the_sprites )
		{
			// These two if statements probably accomplish the same goal,
			// which is why one of them is commented out
			//if ( spr.get_vram_chunk_index() != 0 )
			if ( spr.the_sprite_type != st_default )
			{
				gfx_manager::upload_sprite_tiles_to_vram(spr);
			}
		}
	}
	
	// This is a temporary function.  It should be replaced by a function
	// that inserts sprite spawning parameters into a list.  The sprites
	// from said list would be spawned from within the function called
	// spawn_sprites_if_needed().
	// That said, this is PROBABLY good enough.
	static void spawn_a_sprite_basic ( sprite_type the_sprite_type, 
		const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos, 
		bool facing_right=false )
		__attribute__((_iwram_code));
	
	
	
	static void update_all_sprites ( const vec2_u32& the_sublevel_size_2d,
		prev_curr_pair<bg_point>& camera_pos_pc_pair ) 
		__attribute__((_iwram_code));
	
};




#endif		// sprite_manager_class_hpp
