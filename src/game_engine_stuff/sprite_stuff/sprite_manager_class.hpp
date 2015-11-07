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
	
	static sprite the_player;
	
	//static constexpr u32 max_num_sprites = 40;
	static constexpr u32 max_num_sprites = 20;
	
	static constexpr u32 the_player_vram_chunk_index = 1;
	static constexpr u32 the_active_sprites_starting_vram_chunk_index = 2;
	
	// The array of active sprites (not counting the_player).  If
	// necessary, an sa_free_list<max_num_sprites> might be used for
	// finding a free index in the future.  However, it is unlikely that
	// doing so will be necessary with a maximum of only max_num_sprites
	// active sprites at once.
	static std::array< sprite, max_num_sprites > the_sprites;
	
	//static 
	
public:		// functions
	
	static void init_the_player ( const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, bg_point& camera_pos );
	
	static inline void init_the_array_of_active_sprites()
	{
		//u32 vram_chunk_index = 1;
		//
		//for ( sprite& spr : the_sprites )
		//{
		//	spr.set_vram_chunk_index(vram_chunk_index++);
		//}
		
		for ( u32 i=0; i<max_num_sprites; ++i )
		{
			the_sprites[i].set_vram_chunk_index( i 
				+ the_active_sprites_starting_vram_chunk_index );
		}
	}
	
	
	static void init_horiz_level_sprite_ipg_lists
		( const sprite_init_param_group* the_ext_sprite_ipg_arr, 
		u32 the_ext_sprite_ipg_arr_size );
	
	
	static void some_sprite_init_thing();
	
	static void initial_sprite_spawning_from_level_data
		( const vec2_u32& the_level_size_2d, bg_point& camera_pos, 
		int& next_oam_index );
	
	
	static void initial_sprite_spawning_from_level_data_old
		( const bg_point& camera_pos, int& next_oam_index );
	
	static void spawn_sprites_if_needed
		( const prev_curr_pair<bg_point>& camera_pos_pc_pair ) 
		__attribute__((_iwram_code));
	static void despawn_sprites_if_needed
		( const prev_curr_pair<bg_point>& camera_pos_pc_pair )
		__attribute__((_iwram_code));
	
	
	// This is a temporary function.  It should be replaced by a function
	// that inserts sprite spawning parameters into a list.  The sprites
	// from said list would be spawned from within the function called
	// spawn_sprites_if_needed().
	static void spawn_a_sprite_basic ( sprite_type the_sprite_type, 
		const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos, 
		bool facing_right=false )
		__attribute__((_iwram_code));
	
	
	
	static void update_all_sprites ( const vec2_u32& the_level_size_2d,
		prev_curr_pair<bg_point>& camera_pos_pc_pair, 
		int& next_oam_index ) __attribute__((_iwram_code));
	
};




#endif		// sprite_manager_class_hpp
