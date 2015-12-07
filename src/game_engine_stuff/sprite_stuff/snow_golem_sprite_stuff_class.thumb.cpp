#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"

#include "sprite_manager_class.hpp"

const snow_golem_sprite_stuff::frame
	snow_golem_sprite_stuff::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size]
= {
	// Standing
	frm_stand,
	
	// Throwing a snowball
	frm_throw_0, frm_throw_1, frm_throw_2
};

// Graphics constants
const u32 snow_golem_sprite_stuff::the_relative_metatile_slot_arr[]
	= { frm_stand, frm_throw_0, frm_throw_1, frm_throw_2 };
const u32 snow_golem_sprite_stuff::the_relative_metatile_slot_arr_size
	= sizeof(snow_golem_sprite_stuff::the_relative_metatile_slot_arr)
	/ sizeof(u32);

// This needs to be better fit to snow golem enemies.
const vec2_f24p8 snow_golem_sprite_stuff::the_initial_coll_box_size 
	= { {12 << fixed24p8::shift }, {29 << fixed24p8::shift } },
	snow_golem_sprite_stuff::the_initial_cb_pos_offset 
	= { {2 << fixed24p8::shift }, {3 << fixed24p8::shift } };


void snow_golem_sprite_stuff::update_part_1( sprite& the_enemy )
{
	// Eventually, interesting stuff should happen in this function.
}


// Graphics stuff
const u32 snow_golem_sprite_stuff::get_curr_relative_tile_slot
	( sprite& the_enemy )
{
	// Temporary!
	return frame_slot_to_frame_arr[frm_slot_throw_2] 
		* num_active_gfx_tiles;
}


