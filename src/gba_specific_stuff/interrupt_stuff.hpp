#ifndef interrupt_stuff_hpp
#define interrupt_stuff_hpp

#include "../game_engine_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "attribute_defines.hpp"
#include "dma_stuff.hpp"
#include "timer_stuff.hpp"


// The Interrupt Enable Register (R/W)
#define reg_ie *((vu16*)(mem_io + 0x0200))

// The Interrupt Request Flags/IRQ Acknowledge Register (R/W)
#define reg_if *((vu16*)(mem_io + 0x0202))

// The Interrupt Master Enable Register (R/W)
#define reg_ime *((vu32*)(mem_io + 0x0208))


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
#define irq_vblank ( 0x1 << intr_vblank )
#define irq_hblank ( 0x1 << intr_hblank )
#define irq_vcount ( 0x1 << intr_vcount )

#define irq_timer0 ( 0x1 << intr_timer0 )
#define irq_timer1 ( 0x1 << intr_timer1 )
#define irq_timer2 ( 0x1 << intr_timer2 )
#define irq_timer3 ( 0x1 << intr_timer3 )

#define irq_com ( 0x1 << intr_com )

#define irq_dma0 ( 0x1 << intr_dma0 )
#define irq_dma1 ( 0x1 << intr_dma1 )
#define irq_dma2 ( 0x1 << intr_dma2 )
#define irq_dma3 ( 0x1 << intr_dma3 )

#define irq_keypad ( 0x1 << intr_keypad )

#define irq_gamepak ( 0x1 << intr_gamepak )

#define irq_mask ( (u16)(0x3fff) )



/* ---- End of Defines for the flags of IE and IF ---- */


//static constexpr u32 num_interrupt_types = intr_amount;


/* ---- Inline Functions for IME ---- */
inline void ime_disable()
{
	reg_ime = 0x0000;
}

inline void ime_enable()
{
	reg_ime = 0x0001;
}
/* ---- End of Inline Functions for IME ---- */


// Function Pointer for Interrupt Service Routines
typedef void (*isr_funcptr)(void);

// This is a pointer to the main ISR (an ARM mode function btw), which MUST
// be set properly for interrupts to work!
#define reg_isr_main *((volatile isr_funcptr*)(mem_iwram + 0x7ffc))

// Some BIOS calls require interrupts, which have to be acknowledged by
// using this register (I still think it's weird that there are registers
// in what I thought was IWRAM).
#define reg_ifbios *((vu16*)(mem_iwram + 0x7ff8))



// These extern "C" functions are for maxmod compatibility.  They were
// written based on devkitARM's interrupt code, but using my own custom
// "libgba" code instead.  I suppose that means I should include
// devkitARM's license with this project.
extern "C"
{
	// Also
	extern isr_funcptr isr_table [intr_amount];
	
	void irqEnable( int mask );
	
	void irqSet( int mask, isr_funcptr func );
	
	
}


void irq_init();

void irq_dummy() __attribute__((_iwram_code));


void isr_main() __attribute__((_iwram_code));

//#define isr_main_counter *((vu16*)(mem_ewram + 0x8000))
//#define isr_main_arr0 ((vu16*)(mem_ewram + 0x8002))
//static const u32 isr_main_arr0_size = 0x20;



inline void nocash_soft_break()
{
	asm __volatile__ 
	(
		"mov r11, r11\n\t"
	);
}

#endif		// interrupt_stuff_hpp
