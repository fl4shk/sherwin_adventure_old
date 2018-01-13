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


#include "interrupt_stuff.hpp"
#include "gfx_reg_stuff.hpp"
#include "maxmod.h"


#include "../general_utility_stuff/debug_vars.hpp"

using namespace gba;

extern "C"
{

volatile IrsFuncptr isr_table[intr_amount] [[_bss]];


// This Is for maxmod compatibility
void irqEnable(int mask)
{
	//REG_IME = 0;
	ime_disable();

	if (mask & IRQ_VBLANK)
	{
		REG_DISPSTAT |= DSTAT_VBL_IRQ;
	}
	if (mask & IRQ_HBLANK)
	{
		REG_DISPSTAT |= DSTAT_HBL_IRQ;
	}
	if (mask & IRQ_VCOUNT)
	{
		REG_DISPSTAT |= DSTAT_VCT_IRQ;
	}

	REG_IE |= mask;

	//REG_IME = 1;
	ime_enable();
}

// This Is also for maxmod compatibility, written somewhat differently
// from That used in libgba.
//void irqSet(int mask, IrsFuncptr func)
void irqSet(int mask, u32 func_addr)
{

	switch (mask)
	{
		case IRQ_VBLANK:
			isr_table[intr_vblank] = (void (*)())func_addr;
			break;

		case IRQ_HBLANK:
			isr_table[intr_hblank] = (void (*)())func_addr;
			break;

		case IRQ_VCOUNT:
			isr_table[intr_vcount] = (void (*)())func_addr;
			break;

		case IRQ_TIMER0:
			isr_table[intr_timer0] = (void (*)())func_addr;
			break;

		case IRQ_TIMER1:
			isr_table[intr_timer1] = (void (*)())func_addr;
			break;

		case IRQ_TIMER2:
			isr_table[intr_timer2] = (void (*)())func_addr;
			break;

		case IRQ_TIMER3:
			isr_table[intr_timer3] = (void (*)())func_addr;
			break;

		case IRQ_COM:
			isr_table[intr_com] = (void (*)())func_addr;
			break;

		case IRQ_DMA0:
			isr_table[intr_dma0] = (void (*)())func_addr;
			break;

		case IRQ_DMA1:
			isr_table[intr_dma1] = (void (*)())func_addr;
			break;

		case IRQ_DMA2:
			isr_table[intr_dma2] = (void (*)())func_addr;
			break;

		case IRQ_DMA3:
			isr_table[intr_dma3] = (void (*)())func_addr;
			break;

		case IRQ_KEYPAD:
			isr_table[intr_keypad] = (void (*)())func_addr;
			break;

		case IRQ_GAMEPAK:
			isr_table[intr_gamepak] = (void (*)())func_addr;
			break;

		default:
			break;
	}


}

}

namespace sherwin_adventure
{

namespace gba
{

void irq_dummy()
{
}

void irq_init()
{

	// Clear REG_IME (for safety or something)
	ime_disable();

	for (u32 i=0; i<intr_amount; ++i)
	{
		isr_table[i] = &irq_dummy;
	}

	// Clear REG_IE (for safety or something)
	REG_IE &= ~(IRQ_MASK);


	// Now we enable VBlank Interrupts in REG_IE
	REG_IE |= IRQ_VBLANK;

	// To do this, we also have To enable VBlank IRQs in REG_DISPSTAT
	REG_DISPSTAT |= DSTAT_VBL_IRQ;

	//irqEnable(IRQ_VBLANK);

	//irqSet(IRQ_VBLANK, mmVBlank);
	//irqSet(IRQ_VBLANK, reinterpret_cast<IrsFuncptr>
	//	(&maxmod_vblank_updater_func));

	//irqSet(IRQ_VBLANK, (u32)mmVBlank);
	//irqEnable(IRQ_VBLANK);
	//mmSetVBlankHandler(reinterpret_cast<void*>
	//	(&maxmod_vblank_updater_func));


	// We will use isr_main() as the primary Interrupt Service Routine

	REG_ISR_MAIN = isr_main;


	// Set REG_IME
	ime_enable();

}


// This function Is currently only Intended To service the VBlank
// and Timer 0 interrupts.  I might add support for other interrupts later
// on, but there Is currently no need.
void isr_main()
{
	// Before we leave this function, we have To acknowledge That VBlank
	// IRQ was serviced.
	if (REG_IF & IRQ_VBLANK)
	{
		//mmFrame();
		isr_table[intr_vblank]();

		// Acknowledge the VBlank interrupt.
		REG_IFBIOS = IRQ_VBLANK;
		REG_IF = IRQ_VBLANK;
	}


	if (REG_IF & IRQ_TIMER0)
	{
		isr_table[intr_timer0]();

		// Acknowledge the timer 0 interrupt.
		REG_IFBIOS = IRQ_TIMER0;
		REG_IF = IRQ_TIMER0;
	}
}

}

}
