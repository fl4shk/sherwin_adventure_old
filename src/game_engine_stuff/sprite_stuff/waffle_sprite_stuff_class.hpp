#ifndef waffle_sprite_stuff_class_hpp
#define waffle_sprite_stuff_class_hpp


class waffle_sprite_stuff : public sprite_base_stuff
{
public:		// enums
	// These are used to access misc_data_u and misc_data_s
	enum udata_index { udi_initial_pos_was_set, } __attribute__((_align4));
	enum sdata_index { sdi_initial_pos_x, sdi_initial_pos_y, 
		sdi_move_timer, } __attribute__((_align4));
	
public:		// variables
	static constexpr sprite_type the_sprite_type = st_waffle;
	static constexpr sprite_gfx_category the_gfx_category = sgc_powerup;
	static constexpr u32 the_relative_metatile_slot = 0, 
		num_active_gfx_tiles = sprite_gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr u32 move_timer_start = 128;
	
	//static const ();
	
public:		// functions
	//virtual void init( sprite& the_powerup, bool facing_left );
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	
	virtual void update_part_1( sprite& the_powerup )
		__attribute__((_iwram_code));
	
	
	// Graphics stuff
	//virtual void gfx_update( sprite& the_powerup )
	//	__attribute__((_iwram_code));
	
	inline virtual const sprite_gfx_category get_gfx_category
		( sprite& the_powerup )
	{
		return the_gfx_category;
	}
	inline const u32 get_curr_relative_tile_slot( sprite& the_powerup )
	{
		return the_relative_metatile_slot * num_active_gfx_tiles;
	}
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	
	
	// Physics and collision stuff
	inline virtual void block_collision_stuff( sprite& the_powerup )
	{
		block_collision_stuff_16x16(the_powerup);
	}
	
	
protected:		// functions
	virtual void block_coll_response_left_16x16( sprite& the_sprite, 
		const block_coll_result& lt_coll_result,
		const block_coll_result& lb_coll_result )
		__attribute__((_iwram_code));
	
	virtual void block_coll_response_right_16x16( sprite& the_sprite, 
		const block_coll_result& rt_coll_result,
		const block_coll_result& rb_coll_result )
		__attribute__((_iwram_code));
	
} __attribute__((_align4));


#endif		// waffle_sprite_stuff_class_hpp
