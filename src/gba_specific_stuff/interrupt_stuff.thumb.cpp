#include "interrupt_stuff.hpp"
#include "gfx_reg_stuff.hpp"


extern "C"
{
	isr_funcptr isr_table[intr_amount] __attribute__((_bss));
	
	
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
	void irqSet( int mask, isr_funcptr func )
	{
		switch ( mask )
		{
			case irq_vblank:
				isr_table[intr_vblank] = func;
				break;
				
			case irq_hblank:
				isr_table[intr_hblank] = func;
				break;
				
			case irq_vcount:
				isr_table[intr_vcount] = func;
				break;
				
			case irq_timer0:
				isr_table[intr_timer0] = func;
				break;
			
			case irq_timer1:
				isr_table[intr_timer1] = func;
				break;
			
			case irq_timer2:
				isr_table[intr_timer2] = func;
				break;
			
			case irq_timer3:
				isr_table[intr_timer3] = func;
				break;
			
			case irq_com:
				isr_table[intr_com] = func;
				break;
			
			case irq_dma0:
				isr_table[intr_dma0] = func;
				break;
			
			case irq_dma1:
				isr_table[intr_dma1] = func;
				break;
			
			case irq_dma2:
				isr_table[intr_dma2] = func;
				break;
			
			case irq_dma3:
				isr_table[intr_dma3] = func;
				break;
			
			case irq_keypad:
				isr_table[intr_keypad] = func;
				break;
			
			case irq_gamepak:
				isr_table[intr_gamepak] = func;
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
	
	
	
	// We will use isr_main() as the primary Interrupt Service Routine
	
	reg_isr_main = isr_main;
	
	
	// Set reg_ime
	ime_enable();
	
}


