// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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

#include "../game_engine_stuff/debug_vars.hpp"


extern "C" void maxmod_vblank_updater_func();

extern "C"
{
	volatile isr_funcptr isr_table[intr_amount] __attribute__((_bss));
	
	
	// This is for maxmod compatibility
	void irqEnable( int mask )
	{
		//reg_ime = 0;
		ime_disable();
		
		if ( mask & irq_vblank )
		{
			reg_dispstat |= dstat_vbl_irq;
		}
		if ( mask & irq_hblank )
		{
			reg_dispstat |= dstat_hbl_irq;
		}
		if ( mask & irq_vcount )
		{
			reg_dispstat |= dstat_vct_irq;
		}
		
		reg_ie |= mask;
		
		//reg_ime = 1;
		ime_enable();
	}
	
	// This is also for maxmod compatibility, written somewhat differently
	// from that used in libgba.
	//void irqSet( int mask, isr_funcptr func )
	void irqSet( int mask, u32 func_addr )
	{
		
		switch ( mask )
		{
			case irq_vblank:
				isr_table[intr_vblank] = (void (*)())func_addr;
				break;
				
			case irq_hblank:
				isr_table[intr_hblank] = (void (*)())func_addr;
				break;
				
			case irq_vcount:
				isr_table[intr_vcount] = (void (*)())func_addr;
				break;
				
			case irq_timer0:
				isr_table[intr_timer0] = (void (*)())func_addr;
				break;
			
			case irq_timer1:
				isr_table[intr_timer1] = (void (*)())func_addr;
				break;
			
			case irq_timer2:
				isr_table[intr_timer2] = (void (*)())func_addr;
				break;
			
			case irq_timer3:
				isr_table[intr_timer3] = (void (*)())func_addr;
				break;
			
			case irq_com:
				isr_table[intr_com] = (void (*)())func_addr;
				break;
			
			case irq_dma0:
				isr_table[intr_dma0] = (void (*)())func_addr;
				break;
			
			case irq_dma1:
				isr_table[intr_dma1] = (void (*)())func_addr;
				break;
			
			case irq_dma2:
				isr_table[intr_dma2] = (void (*)())func_addr;
				break;
			
			case irq_dma3:
				isr_table[intr_dma3] = (void (*)())func_addr;
				break;
			
			case irq_keypad:
				isr_table[intr_keypad] = (void (*)())func_addr;
				break;
			
			case irq_gamepak:
				isr_table[intr_gamepak] = (void (*)())func_addr;
				break;
			
			default:
				break;
		}
		
		
	}
}

void irq_dummy()
{
}

void irq_init()
{
	
	// Clear reg_ime (for safety or something)
	ime_disable();
	
	for ( u32 i=0; i<intr_amount; ++i )
	{
		isr_table[i] = &irq_dummy;
	}
	
	// Clear reg_ie (for safety or something)
	reg_ie &= ~(irq_mask);
	
	
	// Now we enable VBlank Interrupts in reg_ie
	reg_ie |= irq_vblank;
	
	// To do this, we also have to enable VBlank IRQs in reg_dispstat
	reg_dispstat |= dstat_vbl_irq;
	
	//irqEnable(irq_vblank);
	
	//irqSet( irq_vblank, mmVBlank );
	//irqSet( irq_vblank, reinterpret_cast<isr_funcptr>
	//	(&maxmod_vblank_updater_func) );
	
	//irqSet( irq_vblank, (u32)mmVBlank );
	//irqEnable(irq_vblank);
	//mmSetVBlankHandler( reinterpret_cast<void*>
	//	(&maxmod_vblank_updater_func) );
	
	
	// We will use isr_main() as the primary Interrupt Service Routine
	
	reg_isr_main = isr_main;
	
	
	// Set reg_ime
	ime_enable();
	
}


