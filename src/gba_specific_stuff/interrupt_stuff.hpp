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


#ifndef gba_specific_stuff__slash__interrupt_stuff_hpp
#define gba_specific_stuff__slash__interrupt_stuff_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "attribute_defines.hpp"
#include "dma_stuff.hpp"
#include "timer_stuff.hpp"


namespace sherwin_adventure
{

namespace gba
{

// The Interrupt Enable Register (R/W)
#define REG_IE *((vu16*)(MEM_IO + 0x0200))

// The Interrupt Request Flags/IRQ Acknowledge Register (R/W)
#define REG_IF *((vu16*)(MEM_IO + 0x0202))

// The Interrupt Master Enable Register (R/W)
#define REG_IME *((vu32*)(MEM_IO + 0x0208))


enum intr_type
{
	intr_vblank = 0x0,
	intr_hblank = 0x1,
	intr_vcount = 0x2,
	intr_timer0 = 0x3,
	intr_timer1 = 0x4,
	intr_timer2 = 0x5,
	intr_timer3 = 0x6,
	intr_com = 0x7,
	intr_dma0 = 0x8,
	intr_dma1 = 0x9,
	intr_dma2 = 0xa,
	intr_dma3 = 0xb,
	intr_keypad = 0xc,
	intr_gamepak = 0xd,

	intr_amount = 0xe,
};


/* ---- Defines for the flags of IE and IF ---- */
#define IRQ_VBLANK (0x1 << intr_vblank)
#define IRQ_HBLANK (0x1 << intr_hblank)
#define IRQ_VCOUNT (0x1 << intr_vcount)

#define IRQ_TIMER0 (0x1 << intr_timer0)
#define IRQ_TIMER1 (0x1 << intr_timer1)
#define IRQ_TIMER2 (0x1 << intr_timer2)
#define IRQ_TIMER3 (0x1 << intr_timer3)

#define IRQ_COM (0x1 << intr_com)

#define IRQ_DMA0 (0x1 << intr_dma0)
#define IRQ_DMA1 (0x1 << intr_dma1)
#define IRQ_DMA2 (0x1 << intr_dma2)
#define IRQ_DMA3 (0x1 << intr_dma3)

#define IRQ_KEYPAD (0x1 << intr_keypad)

#define IRQ_GAMEPAK (0x1 << intr_gamepak)

#define IRQ_MASK ((u16)(0x3fff))



/* ---- End of Defines for the flags of IE and IF ---- */


//static constexpr u32 num_interrupt_types = intr_amount;


/* ---- Inline Functions for IME ---- */
inline void ime_disable()
{
	REG_IME = 0x0000;
}

inline void ime_enable()
{
	REG_IME = 0x0001;
}
/* ---- End of Inline Functions for IME ---- */


// Function Pointer for Interrupt Service Routines
typedef void (*IrsFuncptr)(void);

// This Is a pointer To the main ISR (an ARM mode function btw), which MUST
// be set properly for interrupts To work!
#define REG_ISR_MAIN *((volatile IrsFuncptr*)(MEM_IWRAM + 0x7ffc))

// Some BIOS calls require interrupts, which have To be acknowledged by
// using this register (I still think it's weird That there are registers
// in what I thought was IWRAM).
#define REG_IFBIOS *((vu16*)(MEM_IWRAM + 0x7ff8))

}
}


// These extern "C" functions are for maxmod compatibility.  They were
// written based on devkitARM's interrupt code, but using my own custom
// "libgba" code instead.
extern "C"
{

// Also
extern volatile sherwin_adventure::gba::IrsFuncptr 
	isr_table[sherwin_adventure::gba::intr_amount];

void irqEnable(int mask);

//void irqSet(int mask, IrsFuncptr func);
void irqSet(int mask, u32 func_addr);

}

namespace sherwin_adventure
{

namespace gba
{
void irq_init();

[[_iwram_code]]
void irq_dummy();

[[_iwram_code,_target_arm]]
void isr_main();

//#define ISR_MAIN_COUNTER *((vu16*)(MEM_EWRAM + 0x8000))
//#define ISR_MAIN_ARR0 ((vu16*)(MEM_EWRAM + 0x8002))
//static const u32 isr_main_arr0_size = 0x20;



inline void nocash_soft_break()
{
	asm __volatile__ 
	(
		"mov r11, r11\n\t"
	);
}


}

}

#endif		// gba_specific_stuff__slash__interrupt_stuff_hpp
