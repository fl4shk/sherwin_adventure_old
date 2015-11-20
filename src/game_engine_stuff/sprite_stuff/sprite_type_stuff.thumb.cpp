#include "sprite_type_stuff.hpp"


sprite_base_stuff the_sprite_base_stuff;
player_sprite_stuff the_player_sprite_stuff;
waffle_sprite_stuff the_waffle_sprite_stuff;
muffin_sprite_stuff the_muffin_sprite_stuff;
fire_muffin_sprite_stuff the_fire_muffin_sprite_stuff;
ice_muffin_sprite_stuff the_ice_muffin_sprite_stuff;
chocolate_muffin_sprite_stuff the_chocolate_muffin_sprite_stuff;
door_sprite_stuff the_door_sprite_stuff;


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
	
};


#include "sprite_class.hpp"


