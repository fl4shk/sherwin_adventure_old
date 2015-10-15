#ifndef warp_block_sprite_stuff_class_hpp
#define warp_block_sprite_stuff_class_hpp

class warp_block_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static constexpr sprite_type the_sprite_type = st_warp_block;
	static constexpr sprite_gfx_category the_gfx_category 
		= sgc_block_like_0;
	static constexpr u32 the_relative_tile_slot = 0, 
		num_gfx_tiles = num_tiles_in_ss_16x16;
	
public:		// functions
	
	//virtual void init( sprite& the_, bool facing_right=false );
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	// Graphics stuff
	//virtual void gfx_update( sprite& the_warp_block );
	
	inline virtual const sprite_gfx_category get_gfx_category
		( sprite& the_warp_block )
	{
		return the_gfx_category;
	}
	inline virtual const u32 get_curr_relative_tile_slot
		( sprite& the_warp_block )
	{
		return the_relative_tile_slot * num_gfx_tiles;
	}
	
	
	// Physics and collision stuff
	//// All warp block sprites are not affected by gravity, and they don't
	//// move.
	//virtual void block_collision_stuff( sprite& the_warp_block );
	
	
} __attribute__((_align4));


#endif		// warp_block_sprite_stuff_class_hpp
