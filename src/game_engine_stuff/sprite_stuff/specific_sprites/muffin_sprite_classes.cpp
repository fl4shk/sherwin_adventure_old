// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#include "../sprite_type_stuff.hpp"
#include "../sprite_type_includes.hpp"

const SpriteConstParams MuffinSprite::the_const_params
= {
	// the_const_sprite_type
	StMuffin, 
	
	// the_palette_slot
	sps_powerup, 
	
	// the_relative_metatile_slot
	1,
	
	// num_active_gfx_tiles
	GfxManager::num_tiles_in_ss_16x16,
	
	// tile_arr 
	const_cast<tile*>(reinterpret_cast<const tile*>(the_powerup_gfxTiles)),
};


const SpriteConstParams FireMuffinSprite::the_const_params
= {
	// the_const_sprite_type
	StFireMuffin, 
	
	// the_palette_slot
	MuffinSprite::the_const_params.the_palette_slot, 
	
	// the_relative_metatile_slot
	2,
	
	// num_active_gfx_tiles
	MuffinSprite::the_const_params.num_active_gfx_tiles,
	
	// tile_arr 
	MuffinSprite::the_const_params.tile_arr,
};


const SpriteConstParams IceMuffinSprite::the_const_params
= {
	// the_const_sprite_type
	StIceMuffin, 
	
	// the_palette_slot
	MuffinSprite::the_const_params.the_palette_slot, 
	
	// the_relative_metatile_slot
	3,
	
	// num_active_gfx_tiles
	MuffinSprite::the_const_params.num_active_gfx_tiles,
	
	// tile_arr 
	MuffinSprite::the_const_params.tile_arr,
};


const SpriteConstParams ChocolateMuffinSprite::the_const_params
= {
	// the_const_sprite_type
	StChocolateMuffin, 
	
	// the_palette_slot
	MuffinSprite::the_const_params.the_palette_slot, 
	
	// the_relative_metatile_slot
	4,
	
	// num_active_gfx_tiles
	MuffinSprite::the_const_params.num_active_gfx_tiles,
	
	// tile_arr 
	MuffinSprite::the_const_params.tile_arr,
};
