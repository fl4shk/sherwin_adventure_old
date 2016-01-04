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


sprite_base_stuff the_sprite_base_stuff;
player_sprite_stuff the_player_sprite_stuff;
waffle_sprite_stuff the_waffle_sprite_stuff;
muffin_sprite_stuff the_muffin_sprite_stuff;
fire_muffin_sprite_stuff the_fire_muffin_sprite_stuff;
ice_muffin_sprite_stuff the_ice_muffin_sprite_stuff;
chocolate_muffin_sprite_stuff the_chocolate_muffin_sprite_stuff;
door_sprite_stuff the_door_sprite_stuff;
snow_golem_sprite_stuff the_snow_golem_sprite_stuff;

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
	&the_door_sprite_stuff,
	
	// Enemy sprites
	&the_snow_golem_sprite_stuff,
};


#include "sprite_class.hpp"


