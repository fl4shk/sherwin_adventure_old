#include "sprite_type_stuff.hpp"


sprite_base_stuff the_sprite_base_stuff;
player_sprite_stuff the_player_sprite_stuff;
waffle_sprite_stuff the_waffle_sprite_stuff;
muffin_sprite_stuff the_muffin_sprite_stuff;
fire_muffin_sprite_stuff the_fire_muffin_sprite_stuff;
ice_muffin_sprite_stuff the_ice_muffin_sprite_stuff;
chocolate_muffin_sprite_stuff the_chocolate_muffin_sprite_stuff;
warp_block_sprite_stuff the_warp_block_sprite_stuff;


sprite_base_stuff* sprite_stuff_array[st_count] __attribute__((_iwram))
= {
	
	// The Default Sprite (also used for when there is no sprite in the
	// slot).
	&the_sprite_base_stuff,
	
	// The Player
	&the_player_sprite_stuff,
	
	// Powerup Sprites
	&the_waffle_sprite_stuff,
	
	&the_muffin_sprite_stuff,
	&the_fire_muffin_sprite_stuff,
	&the_ice_muffin_sprite_stuff,
	&the_chocolate_muffin_sprite_stuff,
	
	// Block-like Sprites
	&the_warp_block_sprite_stuff,
	
};


#include "sprite_class.hpp"




const sprite_type muffin_sprite_stuff::get_sprite_type() const
{
	return st_muffin;
}

// Graphics stuff
//void muffin_sprite_stuff::gfx_update( sprite& the_powerup )
//{
//	the_powerup.the_oam_entry.set_tile_number 
//		( get_curr_tile_slot(the_powerup) );
//	the_powerup.the_oam_entry.set_pal_number 
//		( get_gfx_category(the_powerup) );
//}


const sprite_gfx_category muffin_sprite_stuff::get_gfx_category
	( sprite& the_powerup )
{
	return sgc_powerup;
}
const u32 muffin_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_powerup )
{
	return 1 * num_tiles_in_ss_16x16;
}



const sprite_type fire_muffin_sprite_stuff::get_sprite_type() const
{
	return st_fire_muffin;
}


// Graphics stuff
//void fire_muffin_sprite_stuff::gfx_update( sprite& the_powerup )
//{
//	the_powerup.the_oam_entry.set_tile_number 
//		( get_curr_tile_slot(the_powerup) );
//	the_powerup.the_oam_entry.set_pal_number 
//		( get_gfx_category(the_powerup) );
//}

const sprite_gfx_category fire_muffin_sprite_stuff::get_gfx_category
	( sprite& the_powerup )
{
	return sgc_powerup;
}
const u32 fire_muffin_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_powerup )
{
	return 2 * num_tiles_in_ss_16x16;
}






const sprite_type ice_muffin_sprite_stuff::get_sprite_type() const
{
	return st_ice_muffin;
}


// Graphics stuff
//void ice_muffin_sprite_stuff::gfx_update( sprite& the_powerup )
//{
//	the_powerup.the_oam_entry.set_tile_number 
//		( get_curr_tile_slot(the_powerup) );
//	the_powerup.the_oam_entry.set_pal_number 
//		( get_gfx_category(the_powerup) );
//}

const sprite_gfx_category ice_muffin_sprite_stuff::get_gfx_category
	( sprite& the_powerup )
{
	return sgc_powerup;
}
const u32 ice_muffin_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_powerup )
{
	return 3 * num_tiles_in_ss_16x16;
}



const sprite_type chocolate_muffin_sprite_stuff::get_sprite_type() const
{
	return st_chocolate_muffin;
}


// Graphics stuff
//void chocolate_muffin_sprite_stuff::gfx_update( sprite& the_powerup )
//{
//	the_powerup.the_oam_entry.set_tile_number 
//		( get_curr_tile_slot(the_powerup) );
//	the_powerup.the_oam_entry.set_pal_number 
//		( get_gfx_category(the_powerup) );
//}

const sprite_gfx_category chocolate_muffin_sprite_stuff::get_gfx_category
	( sprite& the_powerup )
{
	return sgc_powerup;
}
const u32 chocolate_muffin_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_powerup )
{
	return 4 * num_tiles_in_ss_16x16;
}



const sprite_type warp_block_sprite_stuff::get_sprite_type() const
{
	return st_warp_block;
}


// Graphics stuff
//void warp_block_sprite_stuff::gfx_update( sprite& the_powerup )
//{
//	the_powerup.the_oam_entry.set_tile_number 
//		( get_curr_tile_slot(the_powerup) );
//	the_powerup.the_oam_entry.set_pal_number 
//		( get_gfx_category(the_powerup) );
//}

const sprite_gfx_category warp_block_sprite_stuff::get_gfx_category
	( sprite& the_powerup )
{
	return sgc_block_like_0;
}
const u32 warp_block_sprite_stuff::get_curr_relative_tile_slot 
	( sprite& the_powerup )
{
	return 0 * num_tiles_in_ss_16x16;
}

