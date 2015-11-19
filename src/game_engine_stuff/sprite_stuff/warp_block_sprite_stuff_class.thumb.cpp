#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"
#include "../level_stuff/sublevel_class.hpp"

// Graphics stuff
//void warp_block_sprite_stuff::gfx_update( sprite& the_powerup )
//{
//	the_powerup.the_oam_entry.set_tile_number 
//		( get_curr_tile_slot(the_powerup) );
//	the_powerup.the_oam_entry.set_pal_number 
//		( get_gfx_category(the_powerup) );
//}


// This function needs to be updated to support levels that have multiple 
// sublevels, which is likely to be the usual case.
const sublevel_entrance& warp_block_sprite_stuff::get_dest_sle
	( sprite& the_warp_block )
{
	// the_warp_block.the_sprite_ipg->extra_param_0 contains the
	// destination of the st_warp_block, or at least, it's SUPPOSED to
	// contain the destination.
	
	//next_debug_f24p8.data = active_level::the_current_sublevel_ptr
	//	.sublevel_entrance_arr_arr_helper.the_array
	//	[the_warp_block.the_sprite_ipg->extra_param_0];
	//next_debug_f24p8.data = the_warp_block.the_sprite_ipg->extra_param_0;
	
	//return active_level::the_current_sublevel_ptr_ptr
	//	->sublevel_entrance_arr_arr_helper.the_array
	//	[the_warp_block.the_sprite_ipg->extra_param_0];
	//return active_level::the_current_level_ptr->get_the_sublevels()
	//	[active_level::the_current_active_sublevel_index]
	//	->sublevel_entrance_arr_arr_helper.the_array
	//	[the_warp_block.the_sprite_ipg->extra_param_0];
	return active_level::get_the_current_sublevel_ptr()
		.sublevel_entrance_arr_arr_helper.the_array
		[the_warp_block.the_sprite_ipg->extra_param_0];
}


