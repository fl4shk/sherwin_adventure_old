// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
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



// This Is a class That controls the spawning, despawning, and killing of
// sprites.  The Sprite list stuff Is part of the ActiveLevel class.
class SpriteManager
{
public:		// variables
	
	static constexpr u32 max_num_player_secondary_sprites = 4;
	//static constexpr u32 max_num_player_secondary_sprites = 10;
	
	static constexpr u32 max_num_secondary_sprites = 10;
	
	static constexpr u32 max_num_player_sprites = 1;
	
	//static constexpr u32 max_num_regular_sprites = 40;
	//static constexpr u32 max_num_regular_sprites = 30;
	static constexpr u32 max_num_regular_sprites = 20;
	
	static constexpr u32 max_num_pseudo_bg_sprites = 10;
	
	
	
	//// The array of pointers To secondary active sprites That are "claimed"
	//// by the_player.
	//static std::array< Sprite*, max_num_player_secondary_sprites >
	//	the_player_secondary_sprites;
	//
	//// The array of pointers To secondary active sprites, not counting
	//// those "claimed" by the_player.
	//static std::array< Sprite*, max_num_secondary_sprites > 
	//	the_secondary_sprites;
	
	// -- Switch To linear_memory_allocator --
	static Sprite* the_player;
	
	//// The array of pointers To REGULAR active sprites, not counting
	//// the_player.
	//static std::array< Sprite*, max_num_regular_sprites > the_sprites;
	
	
	
	//// An array of Player secondary sprites To allocate from
	//static std::array< Sprite, max_num_player_secondary_sprites > 
	//	the_player_secondary_sprites;
	//
	//// An array of secondary sprites To allocate from, other than the ones
	//// used by the_player 
	//static std::array< Sprite, max_num_secondary_sprites > 
	//	the_secondary_sprites;
	//
	//// The array of REGULAR active sprites, not counting the_player.
	//static std::array< Sprite, max_num_regular_sprites > 
	//	the_sprites;
	
	
	
	// This Is for speeding up allocation and deallocation
	// -- Switch To linear_memory_allocator --
	static s16 the_player_secondary_sprites_free_list_arr
		[max_num_player_secondary_sprites];
	// -- Switch To linear_memory_allocator --
	static s16 the_secondary_sprites_free_list_arr
		[max_num_secondary_sprites];
	// -- Switch To linear_memory_allocator --
	static s16 the_player_free_list_arr
		[max_num_player_sprites];
	// -- Switch To linear_memory_allocator --
	static s16 the_sprites_free_list_arr
		[max_num_regular_sprites];
	// -- Switch To linear_memory_allocator --
	static s16 the_pseudo_bg_sprites_free_list_arr
		[max_num_pseudo_bg_sprites];
	
	
	// Temporarily use regular arrays To make debugging easier.
	// An array of Player secondary sprites To allocate from
	// -- Switch To linear_memory_allocator --
	static Sprite the_player_secondary_sprites
		[max_num_player_secondary_sprites];
	
	// An array of secondary sprites To allocate from, other than the ones
	// used by the_player 
	// -- Switch To linear_memory_allocator --
	static Sprite the_secondary_sprites[max_num_secondary_sprites];
	
	// An array of a single Player To allocate from
	// -- Switch To linear_memory_allocator --
	static Sprite the_allocatable_player[max_num_player_sprites];
	
	// The array of REGULAR active sprites, not counting the_player.
	// -- Switch To linear_memory_allocator --
	static Sprite the_sprites[max_num_regular_sprites]
		__attribute__((_IWRAM));
	
	// The array of pseudo-background sprites, which are ONLY checked for
	// intersection with the_player (and possibly Player secondary sprites)
	// -- Switch To linear_memory_allocator --
	static Sprite the_pseudo_bg_sprites[max_num_pseudo_bg_sprites];
	
	
	
	
	// The sprite_allocators
	// -- Switch To linear_memory_allocator --
	static SpriteAllocator the_player_secondary_sprites_allocator,
		the_secondary_sprites_allocator, the_player_sprite_allocator, 
		the_sprites_allocator, the_pseudo_bg_sprites_allocator;
	
	// Active sprites
	// -- Switch To linear_memory_allocator --
	static u32 num_active_player_secondary_sprites, num_active_sprites, 
		num_active_secondary_sprites, num_active_pseudo_bg_sprites;
	static std::array< Sprite*, max_num_player_secondary_sprites >
		the_active_player_secondary_sprites __attribute__((_EWRAM));
	static std::array< Sprite*, max_num_secondary_sprites >
		the_active_secondary_sprites __attribute__((_EWRAM));
	static std::array< Sprite*, max_num_regular_sprites > 
		the_active_sprites __attribute__((_IWRAM));
	static std::array< Sprite*, max_num_pseudo_bg_sprites > 
		the_active_pseudo_bg_sprites __attribute__((_EWRAM));
	
	
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
	
	static constexpr u32 
		the_pseudo_bg_sprites_starting_vram_chunk_index
		= the_active_sprites_starting_vram_chunk_index 
		+ max_num_regular_sprites;
	
	
	
	
	// OAM indices and VRAM chunk indices are shared.
	static constexpr u32 the_player_secondary_sprites_starting_oam_index 
		= the_player_secondary_sprites_starting_vram_chunk_index;
	
	static constexpr u32 the_secondary_sprites_starting_oam_index 
		= the_secondary_sprites_starting_vram_chunk_index;
	
	static constexpr u32 the_player_oam_index 
		= the_player_vram_chunk_index;
	
	static constexpr u32 the_active_sprites_starting_oam_index
		= the_active_sprites_starting_vram_chunk_index;
	
	static constexpr u32 the_pseudo_bg_sprites_starting_oam_index
		= the_pseudo_bg_sprites_starting_vram_chunk_index;
	
	
	static int next_oam_index;
	
public:		// functions
	
	static Sprite* allocate_sprite( SpriteAllocator& the_sprite_allocator, 
		sprite_type the_sprite_type, bool facing_left );
	static Sprite* allocate_sprite( SpriteAllocator& the_sprite_allocator, 
		sprite_type the_sprite_type, const vec2_f24p8& s_in_level_pos,
		const PrevCurrPair<bg_point>& camera_pos, bool facing_left );
	
	//static void reinit_sprite_with_sprite_ipg( Sprite*& the_sprite, 
	//	SpriteAllocator& the_sprite_allocator, 
	//	SpriteInitParamGroup* s_the_sprite_ipg );
	////static void reinit_sprite_with_sprite_ipg( Sprite*& the_sprite, 
	////	SpriteAllocator& the_sprite_allocator, u32 s_vram_chunk_index, 
	////	SpriteInitParamGroup* s_the_sprite_ipg );
	
	static Sprite* reinit_sprite_with_sprite_ipg( Sprite& the_sprite, 
		SpriteAllocator& the_sprite_allocator, 
		SpriteInitParamGroup* s_the_sprite_ipg );
	
	//static void reinit_sprite_by_spawning( Sprite*& the_sprite, 
	//	SpriteAllocator& the_sprite_allocator,
	//	sprite_type s_the_sprite_type, const vec2_f24p8& s_in_level_pos, 
	//	const PrevCurrPair<bg_point>& camera_pos, 
	//	bool facing_left=true );
	static Sprite* reinit_sprite_by_spawning( Sprite& the_sprite, 
		SpriteAllocator& the_sprite_allocator,
		sprite_type s_the_sprite_type, const vec2_f24p8& s_in_level_pos, 
		const PrevCurrPair<bg_point>& camera_pos, 
		bool facing_left=true );
	
	
	static s32 spawn_a_player_secondary_sprite_basic
		( sprite_type the_sprite_type, const vec2_f24p8& s_in_level_pos, 
		const PrevCurrPair<bg_point>& camera_pos_pc_pair, 
		bool facing_left=false );
	
	// This Is a temporary function.  It should be replaced by a function
	// That inserts Sprite spawning parameters into a list.  The sprites
	// from said list would be spawned from within the function called
	// spawn_sprites_if_needed().
	// That said, this Is PROBABLY good enough.
	static s32 spawn_a_sprite_basic( sprite_type the_sprite_type, 
		const vec2_f24p8& s_in_level_pos, 
		const PrevCurrPair<bg_point>& camera_pos_pc_pair, 
		bool facing_left=false );
	
	static s32 spawn_a_secondary_sprite_basic( sprite_type the_sprite_type,
		const vec2_f24p8& s_in_level_pos, 
		const PrevCurrPair<bg_point>& camera_pos_pc_pair, 
		bool facing_left=false );
	
	
	
	
	static void init_the_player ( const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_sublevel_size_2d, 
		PrevCurrPair<bg_point>& camera_pos );
	
	static void clear_the_sprite_arrays();
	
	// This function initializes the vram_chunk_index of each Sprite in
	// the_sprites.
	static inline void init_the_sprite_arrays()
	{
		//u32 vram_chunk_index = 1;
		//
		//for ( Sprite& spr : the_sprites )
		//{
		//	spr.set_vram_chunk_index(vram_chunk_index++);
		//}
		
		// Secondary sprites "claimed" by the_player.
		for ( u32 i=0; i<max_num_player_secondary_sprites; ++i )
		{
			the_player_secondary_sprites[i]
				.set_vram_chunk_index( i 
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
		
		// Regular sprites
		for ( u32 i=0; i<max_num_pseudo_bg_sprites; ++i )
		{
			the_pseudo_bg_sprites[i].set_vram_chunk_index( i 
				+ the_pseudo_bg_sprites_starting_vram_chunk_index );
		}
		
	}
	
	
	static void init_horiz_sublevel_sprite_ipg_lists
		( const SpriteInitParamGroup* the_ext_sprite_ipg_arr, 
		u32 the_ext_sprite_ipg_arr_size );
	
	//static void some_sprite_init_thing();
	
	//static void initial_sprite_spawning_from_sublevel_data
	//	( const vec2_u32& the_sublevel_size_2d, bg_point& camera_pos );
	
	// The 
	static void initial_sprite_spawning_at_start_of_level
		( PrevCurrPair<bg_point>& camera_pos_pc_pair );
	
	static void initial_sprite_spawning_at_intra_sublevel_warp
		( PrevCurrPair<bg_point>& camera_pos, 
		u32 sublevel_entrance_index );
	
	
	
	// This function Is put in IWRAM because when the_player warps around a
	// particular Sublevel without CHANGING sublevels, sprites need To be
	// spawned, which Can be an intensive operation.
	static void initial_sprite_spawning_shared_code
		( PrevCurrPair<bg_point>& camera_pos );
		//__attribute__((_IWRAM_CODE));
	
	
	static void initial_sprite_spawning_from_sublevel_data_old
		( const bg_point& camera_pos );
	
	static void find_all_active_sprites() __attribute__((_IWRAM_CODE));
	
	static void spawn_sprites_if_needed
		( const PrevCurrPair<bg_point>& camera_pos_pc_pair ) 
		__attribute__((_IWRAM_CODE));
	static void despawn_sprites_if_needed( const bg_point& camera_pos ) 
		__attribute__((_IWRAM_CODE));
	
	static void upload_tiles_of_active_sprites_to_vram();
		//__attribute__((_IWRAM_CODE));
	
	// This function Is one of the most intensive, So it Is an ARM function
	// That goes in IWRAM.
	static void update_all_sprites( const vec2_u32& the_sublevel_size_2d,
		PrevCurrPair<bg_point>& camera_pos_pc_pair ) 
		__attribute__((_IWRAM_CODE));
	
} __attribute__((_ALIGN4));




#endif		// sprite_manager_class_hpp
