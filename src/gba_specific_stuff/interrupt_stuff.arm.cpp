// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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
//#include "bg_helper_class.hpp"

#include "maxmod.h"




// This function is currently only intended to service the VBlank
// and Timer 0 interrupts.  I might add support for other interrupts later
// on, but there is currently no need.
void isr_main()
{
	// Before we leave this function, we have to acknowledge that VBlank
	// IRQ was serviced.
	if ( reg_if & irq_vblank )
	{
		//mmFrame();
		isr_table[intr_vblank]();
		
		// Acknowledge the VBlank interrupt.
		reg_ifbios = irq_vblank;
		reg_if = irq_vblank;
	}
	
	
	if ( reg_if & irq_timer0 )
	{
		isr_table[intr_timer0]();
		
		// Acknowledge the timer 0 interrupt.
		reg_ifbios = irq_timer0;
		reg_if = irq_timer0;
	}
}

