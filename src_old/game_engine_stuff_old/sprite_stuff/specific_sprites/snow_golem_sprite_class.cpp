// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#include "../sprite_type_stuff.hpp"
#include "../sprite_type_includes.hpp"

#include "../sprite_class.hpp"

#include "../sprite_manager_class.hpp"


// Graphics constants
const SnowGolemSprite::frame SnowGolemSprite::frame_slot_to_frame_arr
	[frame_slot_to_frame_arr_size]
= {
	// Standing
	frm_stand,

	// Throwing a snowball
	frm_throw_0, frm_throw_1, frm_throw_2
};

const SpriteConstParams SnowGolemSprite::the_const_params
= {
	// the_const_sprite_type
	StSnowGolem, 

	// the_palette_slot
	sps_enemy_0, 

	// the_relative_metatile_slot (not used by this class)
	0,

	// num_active_gfx_tiles
	GfxManager::num_tiles_in_ss_16x32,

	// tile_arr 
	const_cast<Tile*>(reinterpret_cast<const Tile*>
		(the_golem_enemy_gfxTiles)),

	// the_initial_shape_size
	OamEntry::ss_16x32,

	// This needs To be better fit To snow golem enemies.
	// the_initial_coll_box_size
	{ {12 << Fixed24p8::get_shift() }, {29 << Fixed24p8::get_shift() } },

	// the_initial_cb_pos_offset
	{ {2 << Fixed24p8::get_shift() }, {3 << Fixed24p8::get_shift() } },
};



void SnowGolemSprite::update_part_2()
{
	// Eventually, interesting stuff should happen in this function.

	u32& frame_stuff_initialized = misc_data_u[udi_frame_stuff_initalized];
	u32& curr_frame_slot = misc_data_u[udi_curr_frame_slot];

	s32& frame_change_timer = misc_data_s[sdi_frame_change_timer];

	// This could just as easily be done in the init() function, but That'd
	// require re-implementing it for this class.
	if (!frame_stuff_initialized)
	{
		frame_stuff_initialized = 1;

		curr_frame_slot = frm_slot_stand;
		frame_change_timer = frame_change_timer_start;
		return;
	}

	--frame_change_timer;

	if (frame_change_timer < 0)
	{
		frame_change_timer = frame_change_timer_start;
		++curr_frame_slot;

		if (curr_frame_slot >= lim_frm_slot)
		{
			curr_frame_slot = 0;
		}
	}

	update_f24p8_positions();
}


// Graphics stuff
const u32 SnowGolemSprite::get_curr_relative_tile_slot()
{
	//// Temporary!
	//return frame_slot_to_frame_arr[frm_slot_throw_2] 
	//	* num_active_gfx_tiles;

	// Temporary!
	u32& curr_frame_slot = misc_data_u[udi_curr_frame_slot];
	return frame_slot_to_frame_arr[curr_frame_slot] 
		* get_num_active_gfx_tiles();
}


