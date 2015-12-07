#ifndef snow_golem_sprite_stuff_class_hpp
#define snow_golem_sprite_stuff_class_hpp

#include "../../gfx/the_golem_enemy_gfx.h"

class snow_golem_sprite_stuff : public sprite_base_stuff
{
public:		// enums
	// "Global" graphics frames
	enum frame
	{
		// Standing frame
		frm_stand = 0, 
		
		// Snowball throwing frames
		frm_throw_0 = 1, 
		frm_throw_1 = 2,
		frm_throw_2 = 3,
		
	} __attribute__((_align4));
	
	// This enum allows multiple frame_slot's to be represented by the same
	// frame, which is used, for example, in the walking animation.
	enum frame_slot 
	{ 
		// Standing
		frm_slot_stand,
		
		// Throwing a snowball
		frm_slot_throw_0,
		frm_slot_throw_1, 
		frm_slot_throw_2, 
		
		// frm_slot_count is the amount of frame_slot's.  It is
		// automatically updated by the compiler.
		frm_slot_count,
		
	} __attribute__((_align4));
	
	
public:		// variables
	
	// A constant array that is intended to be indexed with a frame_slot,
	// such that a frame_slot can be mapped to a frame.
	static constexpr u32 frame_slot_to_frame_arr_size = frm_slot_count;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
		// Graphics constants
	static constexpr sprite_type the_sprite_type = st_snow_golem;
	static constexpr sprite_palette_slot the_palette_slot = sps_enemy_0;
	
	static const u32 the_relative_metatile_slot_arr_size;
	static const u32 the_relative_metatile_slot_arr[];
	
	static constexpr u32 num_active_gfx_tiles 
		= gfx_manager::num_tiles_in_ss_16x32;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(the_golem_enemy_gfxTiles));
	
	static const oam_entry::shape_size the_initial_shape_size 
		= oam_entry::ss_16x32;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
public:		// functions
	
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	virtual void update_part_1( sprite& the_enemy );
	//virtual void update_part_2( sprite& the_enemy, bg_point& camera_pos,
	//	const vec2_u32& the_level_size_2d ) __attribute__((_iwram_code));
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot( sprite& the_enemy );
	
	inline virtual const sprite_palette_slot get_palette_slot 
		( sprite& the_enemy )
	{
		return the_palette_slot;
	}
	virtual const u32 get_curr_relative_tile_slot( sprite& the_enemy );
	
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
	
} __attribute__((_align4));


#endif		// snow_golem_sprite_stuff_class_hpp
