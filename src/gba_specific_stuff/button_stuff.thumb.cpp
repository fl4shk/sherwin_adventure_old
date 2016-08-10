// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#include "attribute_defines.hpp"
#include "button_stuff.hpp"
#include "../general_utility_stuff/prev_curr_pair_class.hpp"


// Global variables to hold the key state
//vu16 __key_curr __attribute__((_ewram)) = 0,
//	__key_prev __attribute__((_ewram)) = 0;

volatile prev_curr_pair<vu16> __key_state __attribute__((_iwram)) 
	= { 0, 0 };


bool soft_reset_keys_down()
{
	if ( ( key_hit(key_a) && key_hit_or_held(key_b) 
		&& key_hit_or_held(key_select) && key_hit_or_held(key_start) )
		|| ( key_hit_or_held(key_a) && key_hit(key_b)
		&& key_hit_or_held(key_select) && key_hit_or_held(key_start) )
		|| ( key_hit_or_held(key_a) && key_hit_or_held(key_b)
		&& key_hit(key_select) && key_hit_or_held(key_start) )
		|| ( key_hit_or_held(key_a) && key_hit_or_held(key_b) 
		&& key_hit_or_held(key_select) && key_hit(key_start) ) )
	{
		return true;
	}
	
	return false;
}
