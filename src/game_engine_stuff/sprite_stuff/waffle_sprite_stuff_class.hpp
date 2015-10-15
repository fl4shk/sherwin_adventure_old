#ifndef waffle_sprite_stuff_class_hpp
#define waffle_sprite_stuff_class_hpp


class waffle_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static constexpr u32 move_timer_start = 128;
	
	enum udata_index { udi_initial_pos_was_set, };
	enum sdata_index { sdi_initial_pos_x, sdi_initial_pos_y, 
		sdi_move_timer, };
	
public:		// functions
	//virtual void init( sprite& the_powerup, bool facing_left );
	virtual const sprite_type get_sprite_type() const
		__attribute__((_iwram_code));
	
	
	virtual void update_part_1( sprite& the_powerup )
		__attribute__((_iwram_code));
	
	
	// Graphics stuff
	//virtual void gfx_update( sprite& the_powerup )
	//	__attribute__((_iwram_code));
	
	virtual const sprite_gfx_category get_gfx_category
		( sprite& the_powerup ) __attribute__((_iwram_code));
	virtual const u32 get_curr_relative_tile_slot( sprite& the_powerup )
		__attribute__((_iwram_code));
	
	
	// Physics and collision stuff
	virtual void block_collision_stuff( sprite& the_powerup );
	
	
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
