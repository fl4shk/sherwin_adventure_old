// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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


#ifndef timer_stuff_hpp
#define timer_stuff_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "asm_funcs.hpp"


// Timer Counter/Reload, AKA Timer Data (R/W)
#define reg_tm0data				*((vu16*)(MEM_IO + 0x100))
#define reg_tm1data				*((vu16*)(MEM_IO + 0x104))
#define reg_tm2data				*((vu16*)(MEM_IO + 0x108))
#define reg_tm3data				*((vu16*)(MEM_IO + 0x10c))

// Timer Control (R/W)
#define reg_tm0cnt				*((vu16*)(MEM_IO + 0x102))
#define reg_tm1cnt				*((vu16*)(MEM_IO + 0x106))
#define reg_tm2cnt				*((vu16*)(MEM_IO + 0x10a))
#define reg_tm3cnt				*((vu16*)(MEM_IO + 0x10e))


// 32-bit "versions" of the timer registers (R/W)
#define reg_tmcnt_full_arr		((vu32*)(MEM_IO + 0x100))
#define reg_tm0cnt_full			(reg_tmcnt_full_arr[0])
#define reg_tm1cnt_full			(reg_tmcnt_full_arr[1])
#define reg_tm2cnt_full			(reg_tmcnt_full_arr[2])
#define reg_tm3cnt_full			(reg_tmcnt_full_arr[3])




// Prescaler Selection (F/1, F/64, F/256, F/1024)
// F = System Clock (16.78MHz)
#define timer_prescaler_1			(0x0 << 0x0)
#define timer_prescaler_64			(0x1 << 0x0)
#define timer_prescaler_256			(0x2 << 0x0)
#define timer_prescaler_1024		(0x3 << 0x0)

#define timer_prescaler_mask		(0x03)


// Count-up timing (Cascading).  When enabled, the prescaler value Is
// ignored, and instead the time Is incremented each time when the PREVIOUS
// Timer overflows.  This function Can't be used for Timer 0, because Timer
// 0 Is the first timer.
#define timer_cascade_disable		(0x0 << 0x2)
#define timer_cascade_enable		(0x1 << 0x2)

#define timer_cascade_mask			(0x04)


// Timer IRQ Enable		(0=Disable, 1=IRQ on Timer overflow)
#define timer_irq_disable			(0x0 << 0x6)
#define timer_irq_enable			(0x1 << 0x6)

#define timer_irq_mask				(0x40)


// Timer Start/Stop
#define timer_stop					(0x0 << 0x7)
#define timer_operate				(0x1 << 0x7)

#define timer_stop_operate_mask		(0x80)


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



#endif		// timer_stuff_hpp
