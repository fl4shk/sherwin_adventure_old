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


#include "sprite_type_stuff.hpp"
#include "sprite_type_includes.hpp"

const sprite_const_params muffin_sprite::the_const_params
= {
	// the_const_sprite_type
	st_muffin, 
	
	// the_palette_slot
	sps_powerup, 
	
	// the_relative_metatile_slot
	1,
	
	// num_active_gfx_tiles
	gfx_manager::num_tiles_in_ss_16x16,
	
	// tile_arr 
	const_cast<tile*>(reinterpret_cast<const tile*>(the_powerup_gfxTiles)),
};


const sprite_const_params fire_muffin_sprite::the_const_params
= {
	// the_const_sprite_type
	st_fire_muffin, 
	
	// the_palette_slot
	muffin_sprite::the_const_params.the_palette_slot, 
	
	// the_relative_metatile_slot
	2,
	
	// num_active_gfx_tiles
	muffin_sprite::the_const_params.num_active_gfx_tiles,
	
	// tile_arr 
	muffin_sprite::the_const_params.tile_arr,
};


const sprite_const_params ice_muffin_sprite::the_const_params
= {
	// the_const_sprite_type
	st_ice_muffin, 
	
	// the_palette_slot
	muffin_sprite::the_const_params.the_palette_slot, 
	
	// the_relative_metatile_slot
	3,
	
	// num_active_gfx_tiles
	muffin_sprite::the_const_params.num_active_gfx_tiles,
	
	// tile_arr 
	muffin_sprite::the_const_params.tile_arr,
};


const sprite_const_params chocolate_muffin_sprite::the_const_params
= {
	// the_const_sprite_type
	st_chocolate_muffin, 
	
	// the_palette_slot
	muffin_sprite::the_const_params.the_palette_slot, 
	
	// the_relative_metatile_slot
	4,
	
	// num_active_gfx_tiles
	muffin_sprite::the_const_params.num_active_gfx_tiles,
	
	// tile_arr 
	muffin_sprite::the_const_params.tile_arr,
};
