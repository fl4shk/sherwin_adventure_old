#ifndef muffin_sprite_stuff_classes_hpp
#define muffin_sprite_stuff_classes_hpp


#include "../../gfx/the_powerup_gfx.h"

class muffin_sprite_stuff : public sprite_base_stuff
{
public:		// variables
	static constexpr sprite_type the_sprite_type = st_muffin;
	static constexpr sprite_gfx_category the_gfx_category = sgc_powerup;
	static constexpr u32 the_relative_metatile_slot = 1, 
		num_active_gfx_tiles = gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(the_powerup_gfxTiles));
	
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
		return the_relative_metatile_slot * num_active_gfx_tiles;
	}
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
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
	static constexpr u32 the_relative_metatile_slot = 2, 
		num_active_gfx_tiles = gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(the_powerup_gfxTiles));
	
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
		return the_relative_metatile_slot * num_active_gfx_tiles;
	}
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
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
	static constexpr u32 the_relative_metatile_slot = 3, 
		num_active_gfx_tiles = gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(the_powerup_gfxTiles));
	
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
		return the_relative_metatile_slot * num_active_gfx_tiles;
	}
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
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
	static constexpr u32 the_relative_metatile_slot = 4, 
		num_active_gfx_tiles = gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(the_powerup_gfxTiles));
	
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
		return the_relative_metatile_slot * num_active_gfx_tiles;
	}
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
	}
	
	// Physics and collision stuff
	//// All muffin powerups are not affected by gravity, and they don't
	//// move.
	//virtual void block_collision_stuff( sprite& the_powerup );
	
} __attribute__((_align4));

#endif		// muffin_sprite_stuff_classes_hpp
