#ifndef player_sprite_stuff_class_hpp
#define player_sprite_stuff_class_hpp

#include "sprite_gfx_stuff.hpp"

class player_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static fixed24p8 speed;
	static bool use_16x16;
	static bool run_toggle;
	
	static constexpr fixed24p8 jump_vel = {-0x400};
	static const s32 max_jump_hold_timer = 16;
	
	static const sprite_gfx_category the_gfx_category = sgc_player;
	static const u32 relative_tile_slot = 1 * num_tiles_in_ss_16x32;
	
	
public:		// functions
	virtual void init( sprite& the_player, bool facing_left=true );
	virtual void init( sprite& the_player, 
		const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, bg_point& camera_pos,
		bool facing_left=true );
	
	virtual const sprite_type get_sprite_type() const
		__attribute__((_iwram_code));
	
	virtual void gfx_update( sprite& the_player );
	virtual void update_part_1( sprite& the_player );
	virtual void update_part_2( sprite& the_player, bg_point& camera_pos,
		const vec2_u32& the_level_size_2d ) __attribute__((_iwram_code));
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot( sprite& the_player );
	
	virtual const sprite_gfx_category get_gfx_category 
		( sprite& the_player );
	virtual const u32 get_curr_relative_tile_slot( sprite& the_player );
	
	// Physics and collision stuff
	virtual void block_collision_stuff( sprite& the_player )
		__attribute__((_iwram_code));
	
	virtual void block_coll_response_top_16x16( sprite& the_player,
		const block_coll_result& tl_coll_result, 
		const block_coll_result& tm_coll_result,
		const block_coll_result& tr_coll_result )
		__attribute__((_iwram_code));
	virtual void block_coll_response_top_16x32( sprite& the_player,
		const block_coll_result& tl_coll_result, 
		const block_coll_result& tm_coll_result,
		const block_coll_result& tr_coll_result )
		__attribute__((_iwram_code));
	
	virtual void handle_jumping_stuff( sprite& the_player, u32
		is_jump_key_hit, u32 is_jump_key_held )
		__attribute__((_iwram_code));
	
	
	
protected:		// functions
	//virtual void block_collision_stuff_16x16( sprite& the_player )
	//	__attribute__((_iwram_code));
	//virtual void block_collision_stuff_16x32( sprite& the_player )
	//	__attribute__((_iwram_code));
	
	
	
} __attribute__((_align4));



#endif		// player_sprite_stuff_class_hpp
