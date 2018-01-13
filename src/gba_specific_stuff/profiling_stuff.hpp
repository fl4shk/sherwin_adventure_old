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


#ifndef gba_specific_stuff__slash__profiling_stuff_hpp
#define gba_specific_stuff__slash__profiling_stuff_hpp


#include "../namespace_using.hpp"
#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "asm_funcs.hpp"
#include "timer_stuff.hpp"
#include "../general_utility_stuff/debug_vars.hpp"


namespace sherwin_adventure
{

namespace gba
{

inline void profile_start()
{
	ASM_COMMENT("Start of profile_start()");


	REG_TM2CNT_FULL = REG_TM3CNT_FULL = 0;

	// Cascade Timer 3 with Timer 2
	REG_TM2CNT = TIMER_OPERATE;
	REG_TM3CNT = TIMER_OPERATE | TIMER_CASCADE_ENABLE;


	ASM_COMMENT("End of profile_start()");
}

inline u32 profile_stop()
{
	// I guess stopping Timer 2 will stop Timer 3 since Timer 3 Is cascaded
	// with Timer 2.
	REG_TM2CNT = 0;

	const u32 ret = ((static_cast<u32>(REG_TM3DATA) << 16) 
		| static_cast<u32>(REG_TM2DATA));


	return ret;
}

inline void show_profile_stop()
{
	ASM_COMMENT("Start of show_profile_stop()");


	DebugArrGroup::write_u32_and_inc(profile_stop());


	ASM_COMMENT("End of show_profile_stop()");
}


// Profile new, delete, new[], delete[], malloc, and free.
[[_iwram_code,_target_arm]]
void profile_dynamic_allocations(size_t num_elems);

}

}

#endif		// gba_specific_stuff__slash__profiling_stuff_hpp
