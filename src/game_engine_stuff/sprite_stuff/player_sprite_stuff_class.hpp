#ifndef player_sprite_stuff_class_hpp
#define player_sprite_stuff_class_hpp

//#include "../gfx_manager_class.hpp"
#include "../gfx_manager_class.hpp"

#include "../../gfx/sherwin_gfx.h"

class player_sprite_stuff : public sprite_base_stuff
{
public:		// enums
	// "Global" graphics frames
	enum frame
	{
		// Not a real frame, just a way to hide the player
		frm_invisible = 0, 
		
		// Standing frame
		frm_stand = 1, 
		
		// Walking frames
		frm_walk_0 = 2, 
		frm_walk_1 = 3,
		
	} __attribute__((_align4));
	
	// This enum allows multiple frame_slot's to be represented by the same
	// frame, which is used, for example, in the walking animation.
	enum frame_slot 
	{ 
		// Invisible
		frm_slot_invisible, 
		
		// Standing
		frm_slot_stand,
		
		// Walking/running 
		frm_slot_walk_0,
		frm_slot_walk_1, 
		frm_slot_walk_2, 
		frm_slot_walk_3,
		
		// frm_slot_count is the amount of frame_slot's.  It is
		// automatically updated by the compiler.
		frm_slot_count,
		
	} __attribute__((_align4));
	
	
	// Indices to the_player.misc_data_s
	enum sdata_index { sdi_walk_frame_timer } __attribute__((_align4));
	enum udata_index { udi_active_walk_frame_slot }
		__attribute__((_align4));
	
	
public:		// variables
	// Static variables
	
	static fixed24p8 speed __attribute__((_iwram));
	static bool use_16x16 __attribute__((_iwram));
	static bool run_toggle __attribute__((_iwram));
	//static bool running __attribute__((_iwram));
	
	static s32 max_hp __attribute__((_iwram));
	static s32 remaining_hp __attribute__((_iwram));
	
	// Physics/logic constants
	static constexpr fixed24p8 jump_vel = {-0x400};
	static constexpr s32 max_jump_hold_timer = 16;
	static constexpr s32 walk_frame_timer_end = 4;
	static constexpr s32 run_frame_timer_end = 2;
	
	static constexpr fixed24p8 walk_speed = {0x100};
	static constexpr fixed24p8 max_run_speed = {0x200};
	
	// A constant array that is intended to be indexed with a frame_slot,
	// such that a frame_slot can be mapped to a frame.
	static constexpr u32 frame_slot_to_frame_arr_size = frm_slot_count;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
	
	// Graphics constants
	static constexpr sprite_type the_sprite_type = st_player;
	static constexpr sprite_palette_slot the_palette_slot = sps_player;
	
	static const u32 the_relative_metatile_slot_arr_size;
	static const u32 the_relative_metatile_slot_arr[];
	
	static constexpr u32 num_active_gfx_tiles 
		= gfx_manager::num_tiles_in_ss_16x32;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(sherwin_gfxTiles));
	
	static const oam_entry::shape_size the_initial_shape_size 
		= oam_entry::ss_16x32;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
	
public:		// functions
	virtual void init( sprite& the_player, bool facing_left=true );
	virtual void init( sprite& the_player, 
		const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, bg_point& camera_pos,
		bool facing_left=true );
	
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	virtual void gfx_update( sprite& the_player );
	virtual void update_part_1( sprite& the_player );
	virtual void update_part_2( sprite& the_player, bg_point& camera_pos,
		const vec2_u32& the_level_size_2d ) __attribute__((_iwram_code));
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot( sprite& the_player );
	
	inline virtual const sprite_palette_slot get_palette_slot 
		( sprite& the_player )
	{
		return the_palette_slot;
	}
	virtual const u32 get_curr_relative_tile_slot( sprite& the_player );
	
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
	}
	
	inline virtual const oam_entry::shape_size get_the_initial_shape_size() 
		const
	{
		return the_initial_shape_size;
	}
	
	inline virtual const vec2_f24p8& get_the_initial_coll_box_size() const
	{
		return the_initial_coll_box_size;
	}
	inline virtual const vec2_f24p8& get_the_initial_cb_pos_offset() const
	{
		return the_initial_cb_pos_offset;
	}
	
	
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
