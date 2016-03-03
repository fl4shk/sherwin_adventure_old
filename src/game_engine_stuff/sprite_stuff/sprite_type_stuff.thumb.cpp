// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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

#define X(name) name##_sprite_stuff the_##name##_sprite_stuff;
list_of_main_sprite_types(X)
#undef X


std::array< sprite_base_stuff*, st_count > sprite_stuff_array
= {
	// The Default Sprite (also used for when there is no sprite in the
	// slot).
	&the_sprite_base_stuff,
	
	#define X(name) &the_##name##_sprite_stuff,
	list_of_main_sprite_types(X)
	#undef X
};


#include "sprite_class.hpp"


