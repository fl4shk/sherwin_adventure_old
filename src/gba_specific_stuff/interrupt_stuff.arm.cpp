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

