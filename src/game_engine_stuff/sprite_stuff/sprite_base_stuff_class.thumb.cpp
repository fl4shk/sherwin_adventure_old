// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#include "sprite_type_stuff.hpp"
#include "sprite_class.hpp"

#include "sprite_manager_class.hpp"

const oam_entry::shape_size sprite_base_stuff::the_initial_shape_size 
	= oam_entry::ss_16x16;

const vec2_f24p8 sprite_base_stuff::the_initial_coll_box_size
	= { {14 << fixed24p8::shift}, {14 << fixed24p8::shift} },
	sprite_base_stuff::the_initial_cb_pos_offset 
	= { {1 << fixed24p8::shift}, {1 << fixed24p8::shift} };

const vec2_f24p8 sprite_base_stuff::the_initial_in_level_pos_offset
	= { {0 << fixed24p8::shift}, {0 << fixed24p8::shift} };

void sprite_base_stuff::init( sprite& the_sprite, bool facing_left )
{
	the_sprite.the_sprite_type = get_sprite_type();
	
	the_sprite.the_oam_entry.set_tile_number
		( get_curr_tile_slot(the_sprite) );
	the_sprite.the_oam_entry.set_pal_number 
		( get_palette_slot(the_sprite) );
	
	set_initial_shape_size_of_sprite(the_sprite);
	set_initial_coll_box_stuff_of_sprite(the_sprite);
	
	if ( facing_left )
	{
		the_sprite.the_oam_entry.enable_hflip();
	}
	
	
	clear_and_set_bits( the_sprite.the_oam_entry.attr2, 
		obj_attr2_prio_mask, obj_attr2_prio_1 );
	
}

void sprite_base_stuff::init( sprite& the_sprite, 
	const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos,
	bool facing_left )
{
	init( the_sprite, facing_left );
	the_sprite.in_level_pos = s_in_level_pos 
		- get_the_initial_in_level_pos_offset();
	the_sprite.update_on_screen_pos(camera_pos);
}

void sprite_base_stuff::init( sprite& the_sprite, 
	const vec2_f24p8& s_in_level_pos, const vec2_u32& the_level_size_2d,
	bg_point& camera_pos, bool facing_left )
{
	init( the_sprite, facing_left );
	the_sprite.in_level_pos = s_in_level_pos 
		- get_the_initial_in_level_pos_offset();
	the_sprite.update_on_screen_pos(camera_pos);
	
}


const sprite_type sprite_base_stuff::get_sprite_type() const
{
	return st_default;
}

void sprite_base_stuff::set_initial_shape_size_of_sprite
	( sprite& the_sprite ) const
{
	the_sprite.set_shape_size( get_the_initial_shape_size() );
}

void sprite_base_stuff::set_initial_coll_box_stuff_of_sprite
	( sprite& the_sprite ) const
{
	the_sprite.the_coll_box.size = get_the_initial_coll_box_size();
	the_sprite.cb_pos_offset = get_the_initial_cb_pos_offset();
}


void sprite_base_stuff::gfx_update( sprite& the_sprite )
{
	//the_sprite.the_oam_entry.set_tile_number 
	//	( get_curr_tile_slot_old(the_sprite) );
	
	//the_sprite.the_oam_entry.set_tile_number
	//	( the_sprite.get_vram_chunk_index() 
	//	* gfx_manager::num_tiles_in_ss_32x32 );
	the_sprite.the_oam_entry.set_tile_number
		( get_curr_tile_slot(the_sprite) );
	
	the_sprite.the_oam_entry.set_pal_number 
		( get_palette_slot(the_sprite) );
}


void sprite_base_stuff::update_part_1( sprite& the_sprite )
{
	the_sprite.update_f24p8_positions();
	block_collision_stuff(the_sprite);
}


// The player_sprite_stuff class is the primary user of this function.
void sprite_base_stuff::update_part_2( sprite& the_sprite, 
	bg_point& camera_pos, const vec2_u32& the_level_size_2d )
{
}


void sprite_base_stuff::update_part_2( sprite& the_sprite, 
	const bg_point& camera_pos, int& next_oam_index )
{
	gfx_update(the_sprite);
	the_sprite.update_on_screen_pos(camera_pos);
	the_sprite.copy_the_oam_entry_to_oam_mirror(next_oam_index++);
}


//const u32 sprite_base_stuff::get_curr_tile_slot_old( sprite& the_sprite )
//{
//	return 
//		( ( gfx_manager::sprite_palette_slot_first_vram_slot_list 
//		[get_palette_slot(the_sprite)] / sizeof(tile) * sizeof(u16) )
//		+ get_curr_relative_tile_slot(the_sprite) );
//}

const u32 sprite_base_stuff::get_curr_tile_slot( sprite& the_sprite )
{
	return the_sprite.get_vram_chunk_index() 
		* gfx_manager::num_tiles_in_ss_32x32;
}

// The reason this function takes a sprite instance as a parameter is that
// sprites may use different palettes depending on their state.
const sprite_palette_slot sprite_base_stuff::get_palette_slot
	( sprite& the_sprite )
{
	return the_palette_slot;
}
const u32 sprite_base_stuff::get_curr_relative_tile_slot 
	( sprite& the_sprite )
{
	return the_relative_metatile_slot * num_active_gfx_tiles;
}



// This is a dummy function that child classes implement.
void sprite_base_stuff::block_collision_stuff( sprite& the_sprite )
{
}


// This is a dummy function that child classes implement.
void sprite_base_stuff::handle_jumping_stuff( sprite& the_player, 
	u32 is_jump_key_hit, u32 is_jump_key_held )
{
}


