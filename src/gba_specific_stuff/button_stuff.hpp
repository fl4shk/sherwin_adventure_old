// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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


#ifndef button_stuff_hpp
#define button_stuff_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"

#include "../general_utility_stuff/prev_curr_pair_class.hpp"

// This stuff is shamelessly taken from TONC.
//extern vu16 __key_curr, __key_prev;
//extern vu16 __key_state.curr, __key_state.prev;
extern volatile prev_curr_pair<vu16> __key_state;


// Current Key States
#define reg_keyinput *((vu16*)(mem_io + 0x0130))

// Stuff for Key Interrupts
#define reg_keycnt *((vu16*)(mem_io + 0x0132))


#define key_a ( 0x1 << 0x0 )
#define key_b ( 0x1 << 0x1 )
#define key_select ( 0x1 << 0x2 )
#define key_start ( 0x1 << 0x3 )
#define key_right ( 0x1 << 0x4 )
#define key_left ( 0x1 << 0x5 )
#define key_up ( 0x1 << 0x6 )
#define key_down ( 0x1 << 0x7 )
#define key_r ( 0x1 << 0x8 )
#define key_l ( 0x1 << 0x9 )

#define key_mask 0x03ff


// Polling function
inline void key_poll()
{
	__key_state.prev = __key_state.curr;
	__key_state.curr = (~reg_keyinput) & key_mask;
}

void key_test();

// Basic state checks
inline u32 key_curr_state()
{
	return __key_state.curr;
}

inline u32 key_prev_state()
{
	return __key_state.prev;
}

inline u32 key_is_down( u32 key )
{
	return __key_state.curr & key;
}

inline u32 key_is_up( u32 key )
{
	return (~__key_state.curr) & key;
}

inline u32 key_was_down( u32 key )
{
	return __key_state.prev & key;
}

inline u32 key_was_up( u32 key )
{
	return (~__key_state.prev) & key;
}



// Transitional state checks

// Key is changing state.
inline u32 key_transit( u32 key )
{
	return ( __key_state.curr ^ __key_state.prev ) & key;
}

// Key is held (down now and before).
inline u32 key_held( u32 key )
{
	return ( __key_state.curr & __key_state.prev ) & key;
}

// Key is being hit (down now, but not before).
inline u32 key_hit( u32 key )
{
	return ( __key_state.curr & (~__key_state.prev) ) & key;
}

// Key is being released (up now but down before)
inline u32 key_released( u32 key )
{
	return ( (~__key_state.curr) & __key_state.prev ) & key;
}

inline bool key_hit_or_held( u32 key )
{
	return ( ( (bool)key_hit(key) ) || ( (bool)key_held(key) ) );
}

bool soft_reset_keys_down(); //__attribute__((_iwram_code));



#endif		// button_stuff_hpp
