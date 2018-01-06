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


#ifndef gba_specific_stuff__slash__timer_stuff_hpp
#define gba_specific_stuff__slash__timer_stuff_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "asm_funcs.hpp"


// Timer Counter/Reload, AKA Timer Data (R/W)
#define REG_TM0DATA				*((vu16*)(MEM_IO + 0x100))
#define REG_TM1DATA				*((vu16*)(MEM_IO + 0x104))
#define REG_TM2DATA				*((vu16*)(MEM_IO + 0x108))
#define REG_TM3DATA				*((vu16*)(MEM_IO + 0x10c))

// Timer Control (R/W)
#define REG_TM0CNT				*((vu16*)(MEM_IO + 0x102))
#define REG_TM1CNT				*((vu16*)(MEM_IO + 0x106))
#define REG_TM2CNT				*((vu16*)(MEM_IO + 0x10a))
#define REG_TM3CNT				*((vu16*)(MEM_IO + 0x10e))


// 32-bit "versions" of the timer registers (R/W)
#define REG_TMCNT_FULL_ARR		((vu32*)(MEM_IO + 0x100))
#define REG_TM0CNT_FULL			(REG_TMCNT_FULL_ARR[0])
#define REG_TM1CNT_FULL			(REG_TMCNT_FULL_ARR[1])
#define REG_TM2CNT_FULL			(REG_TMCNT_FULL_ARR[2])
#define REG_TM3CNT_FULL			(REG_TMCNT_FULL_ARR[3])




// Prescaler Selection (F/1, F/64, F/256, F/1024)
// F = System Clock (16.78MHz)
#define TIMER_PRESCALER_1			(0x0 << 0x0)
#define TIMER_PRESCALER_64			(0x1 << 0x0)
#define TIMER_PRESCALER_256			(0x2 << 0x0)
#define TIMER_PRESCALER_1024		(0x3 << 0x0)

#define TIMER_PRESCALER_MASK		(0x03)


// Count-up timing (Cascading).  When enabled, the prescaler value Is
// ignored, and instead the time Is incremented each time when the PREVIOUS
// Timer overflows.  This function Can't be used for Timer 0, because Timer
// 0 Is the first timer.
#define TIMER_CASCADE_DISABLE		(0x0 << 0x2)
#define TIMER_CASCADE_ENABLE		(0x1 << 0x2)

#define TIMER_CASCADE_MASK			(0x04)


// Timer IRQ Enable		(0=Disable, 1=IRQ on Timer overflow)
#define TIMER_IRQ_DISABLE			(0x0 << 0x6)
#define TIMER_IRQ_ENABLE			(0x1 << 0x6)

#define TIMER_IRQ_MASK				(0x40)


// Timer Start/Stop
#define TIMER_STOP					(0x0 << 0x7)
#define TIMER_OPERATE				(0x1 << 0x7)

#define TIMER_STOP_OPERATE_MASK		(0x80)


namespace sherwin_adventure
{

namespace gba
{

// Here Is an extra thing for 
constexpr inline u16 calc_timer_freq(float freq)
{
	//if (freq > 0.0f)
	//{
	//	return 0xffff - (u16)(16.78e6f / freq);
	//}
	//return 0.0f;


	// I REALLY don't know why I am not allowed To use an if-else chain for
	// this.  It seems like an oversight in the design of C++, honestly.
	return (freq > 0.0f) ? 0xffff - (u16)(16.78e6f / freq)
		: ((freq < 0.0f) ? 0xffff - (u16)(16.78e6 / (-freq)) 
			: 0xffff);
}

}

}

#endif		// gba_specific_stuff__slash__timer_stuff_hpp
