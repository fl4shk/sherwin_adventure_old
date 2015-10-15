#ifndef muffin_sprite_stuff_classes_hpp
#define muffin_sprite_stuff_classes_hpp


class muffin_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static constexpr sprite_type the_sprite_type = st_muffin;
	static constexpr sprite_gfx_category the_gfx_category = sgc_powerup;
	static constexpr u32 the_relative_tile_slot = 1, 
		num_gfx_tiles = num_tiles_in_ss_16x16;
	
public:		// functions
	//virtual void init( sprite& the_powerup, bool facing_right=false );
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	// Graphics stuff
	//virtual void gfx_update( sprite& the_powerup );
	
	inline virtual const sprite_gfx_category get_gfx_category
		( sprite& the_powerup )
	{
		return the_gfx_category;
	}
	inline virtual const u32 get_curr_relative_tile_slot
		( sprite& the_powerup )
	{
		return the_relative_tile_slot * num_gfx_tiles;
	}
	
	
	// Physics and collision stuff
	//// All muffin powerups are not affected by gravity, and they don't
	//// move.
	//virtual void block_collision_stuff( sprite& the_powerup );
	
	
} __attribute__((_align4));

class fire_muffin_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static constexpr sprite_type the_sprite_type = st_fire_muffin;
	static constexpr sprite_gfx_category the_gfx_category = sgc_powerup;
	static constexpr u32 the_relative_tile_slot = 2, 
		num_gfx_tiles = num_tiles_in_ss_16x16;
	
public:		// functions
	//virtual void init( sprite& the_powerup, bool facing_right=false );
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	// Graphics stuff
	//virtual void gfx_update( sprite& the_powerup );
	
	inline virtual const sprite_gfx_category get_gfx_category
		( sprite& the_powerup )
	{
		return the_gfx_category;
	}
	virtual const u32 get_curr_relative_tile_slot( sprite& the_powerup )
	{
		return the_relative_tile_slot * num_gfx_tiles;
	}
	
	
	// Physics and collision stuff
	//// All muffin powerups are not affected by gravity, and they don't
	//// move.
	//virtual void block_collision_stuff( sprite& the_powerup );
	
	
} __attribute__((_align4));


class ice_muffin_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static constexpr sprite_type the_sprite_type = st_ice_muffin;
	static constexpr sprite_gfx_category the_gfx_category = sgc_powerup;
	static constexpr u32 the_relative_tile_slot = 3, 
		num_gfx_tiles = num_tiles_in_ss_16x16;
	
public:		// functions
	//virtual void init( sprite& the_powerup, bool facing_right=false );
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	// Graphics stuff
	//virtual void gfx_update( sprite& the_powerup );
	
	inline virtual const sprite_gfx_category get_gfx_category
		( sprite& the_powerup )
	{
		return the_gfx_category;
	}
	inline virtual const u32 get_curr_relative_tile_slot
		( sprite& the_powerup )
	{
		return the_relative_tile_slot * num_gfx_tiles;
	}
	
	
	// Physics and collision stuff
	//// All muffin powerups are not affected by gravity, and they don't
	//// move.
	//virtual void block_collision_stuff( sprite& the_powerup );
	
} __attribute__((_align4));

class chocolate_muffin_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static constexpr sprite_type the_sprite_type = st_chocolate_muffin;
	static constexpr sprite_gfx_category the_gfx_category = sgc_powerup;
	static constexpr u32 the_relative_tile_slot = 4, 
		num_gfx_tiles = num_tiles_in_ss_16x16;
	
public:		// functions
	//virtual void init( sprite& the_powerup, bool facing_right=false );
	inline virtual const sprite_type get_sprite_type() const
	{
		return the_sprite_type;
	}
	
	// Graphics stuff
	//virtual void gfx_update( sprite& the_powerup );
	
	inline virtual const sprite_gfx_category get_gfx_category
		( sprite& the_powerup )
	{
		return the_gfx_category;
	}
	inline virtual const u32 get_curr_relative_tile_slot
		( sprite& the_powerup )
	{
		return the_relative_tile_slot * num_gfx_tiles;
	}
	
	
	// Physics and collision stuff
	//// All muffin powerups are not affected by gravity, and they don't
	//// move.
	//virtual void block_collision_stuff( sprite& the_powerup );
	
} __attribute__((_align4));

#endif		// muffin_sprite_stuff_classes_hpp
