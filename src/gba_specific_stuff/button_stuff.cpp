// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andrew Clark (FL4SHK).
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


#include "attribute_defines.hpp"
#include "button_stuff.hpp"
#include "../general_utility_stuff/prev_curr_pair_class.hpp"

namespace sherwin_adventure
{

namespace gba
{

// Global variables To hold the key state
//vu16 __key_curr [[_EWRAM]] = 0,
//	__key_prev [[_EWRAM]] = 0;

volatile PrevCurrPair<vu16> __key_state [[_iwram]] 
	= { 0, 0 };


bool soft_reset_keys_down()
{
	if ((key_hit(KEY_A) && key_hit_or_held(KEY_B) 
		&& key_hit_or_held(KEY_SELECT) && key_hit_or_held(KEY_START))
		|| (key_hit_or_held(KEY_A) && key_hit(KEY_B)
		&& key_hit_or_held(KEY_SELECT) && key_hit_or_held(KEY_START))
		|| (key_hit_or_held(KEY_A) && key_hit_or_held(KEY_B)
		&& key_hit(KEY_SELECT) && key_hit_or_held(KEY_START))
		|| (key_hit_or_held(KEY_A) && key_hit_or_held(KEY_B) 
		&& key_hit_or_held(KEY_SELECT) && key_hit(KEY_START)))
	{
		return true;
	}

	return false;

}

}

}
