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


#ifndef gba_specific_stuff__slash__button_stuff_hpp
#define gba_specific_stuff__slash__button_stuff_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"

#include "../general_utility_stuff/prev_curr_pair_class.hpp"

#include "../namespace_using.hpp"


namespace sherwin_adventure
{

namespace gba
{
// This stuff Is shamelessly taken from TONC.
//extern vu16 __key_curr, __key_prev;
//extern vu16 __key_state.curr, __key_state.prev;
extern volatile PrevCurrPair<vu16> __key_state;


// Current Key States
#define REG_KEYINPUT *((vu16*)(MEM_IO + 0x0130))

// Stuff for Key Interrupts
#define REG_KEYCNT *((vu16*)(MEM_IO + 0x0132))


#define KEY_A (0x1 << 0x0)
#define KEY_B (0x1 << 0x1)
#define KEY_SELECT (0x1 << 0x2)
#define KEY_START (0x1 << 0x3)
#define KEY_RIGHT (0x1 << 0x4)
#define KEY_LEFT (0x1 << 0x5)
#define KEY_UP (0x1 << 0x6)
#define KEY_DOWN (0x1 << 0x7)
#define KEY_R (0x1 << 0x8)
#define KEY_L (0x1 << 0x9)

#define KEY_MASK 0x03ff


// Polling function
inline void key_poll()
{
	__key_state.prev = __key_state.curr;
	__key_state.curr = (~REG_KEYINPUT) & KEY_MASK;
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

inline u32 key_is_down(u32 key)
{
	return __key_state.curr & key;
}

inline u32 key_is_up(u32 key)
{
	return (~__key_state.curr) & key;
}

inline u32 key_was_down(u32 key)
{
	return __key_state.prev & key;
}

inline u32 key_was_up(u32 key)
{
	return (~__key_state.prev) & key;
}



// Transitional state checks

// Key Is changing state.
inline u32 key_transit(u32 key)
{
	return (__key_state.curr ^ __key_state.prev) & key;
}

// Key Is held (down now and before).
inline u32 key_held(u32 key)
{
	return (__key_state.curr & __key_state.prev) & key;
}

// Key Is being hit (down now, but not before).
inline u32 key_hit(u32 key)
{
	return (__key_state.curr & (~__key_state.prev)) & key;
}

// Key Is being released (up now but down before)
inline u32 key_released(u32 key)
{
	return ((~__key_state.curr) & __key_state.prev) & key;
}

inline bool key_hit_or_held(u32 key)
{
	return (((bool)key_hit(key)) || ((bool)key_held(key)));
}

bool soft_reset_keys_down(); //[[_iwram_code]];




}

}

#endif		// gba_specific_stuff__slash__button_stuff_hpp
