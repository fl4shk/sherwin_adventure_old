// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License FOR more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef bios_function_wrappers_hpp
#define bios_function_wrappers_hpp

#include "attribute_defines.hpp"
#include "../general_utility_stuff/misc_types.hpp"
#include "interrupt_stuff.hpp"


/* ---- The BIOS Call Numbers ---- */
// SoftReset
#define bios_soft_reset 0x00
// RegisterRamReset
#define bios_register_ram_reset 0x01
// Halt
#define bios_halt 0x02
// Stop
#define bios_stop 0x03
// IntrWait
#define bios_intr_wait 0x04
// VBlankIntrWait
#define bios_vblank_intr_wait 0x05
// Div
#define bios_div 0x06
// DivArm
#define bios_div_arm 0x07


// Sqrt
#define bios_sqrt 0x08
// ArcTan
#define bios_arctan 0x09
// ArcTan2
#define bios_arctan2 0x0a
// CPUSet
#define bios_cpu_set 0x0b
// CPUFastSet
#define bios_cpu_fast_set 0x0c
// BiosChecksum
#define bios_bios_checksum 0x0d
// BgAffineSet
#define bios_bg_affine_set 0x0e
// ObjAffineSet
#define bios_obj_affine_set 0x0f



// BitUnPack
#define bios_bit_unpack 0x10
// LZ77UnCompWRAM
#define bios_lz77_uncomp_wram 0x11
// LZ77UnCompVRAM
#define bios_lz77_uncomp_vram 0x12
// HuffUnComp
#define bios_huff_uncomp 0x13
// RLUnCompWRAM
#define bios_rl_uncomp_wram 0x14
// RLUnCompVRAM
#define bios_rl_uncomp_vram 0x15
// Diff8bitUnFilterWRAM
#define bios_diff_8bit_unfilter_wram 0x16
// Diff8bitUnFilterVRAM
#define bios_diff_8bit_unfilter_vram 0x17



// Diff16bitUnFilter
#define bios_diff_16bit_unfilter 0x18
// SoundBiasChange
#define bios_sound_bias_change 0x19
// SoundDriverInit
#define bios_sound_driver_init 0x1a
// SoundDriverMain
#define bios_sound_driver_main 0x1b
// SoundDriverMode
#define bios_sound_driver_mode 0x1c
// SoundDriverVSync
#define bios_sound_driver_vsync 0x1d
// SoundChannelClear
#define bios_sound_channel_clear 0x1e
// MIDIKey2Freq
#define bios_midi_key_2_freq 0x1f


// MusicPlayerOpen
#define bios_music_player_open 0x20
// MusicPlayerStart
#define bios_music_player_start 0x21
// MusicPlayerStop
#define bios_music_player_stop 0x22
// MusicPlayerContinue
#define bios_music_player_continue 0x23
// MusicPlayerFadeOut
#define bios_music_player_fade_out 0x24
// MultiBoot
#define bios_multiboot 0x25
// HardReset
#define bios_hard_reset 0x26
// CustomHalt
#define bios_custom_halt 0x27


// SoundDriverVSyncOff
#define bios_sound_driver_vsync_off 0x28
// SoundDriverVSyncOn
#define bios_sound_driver_vsync_on 0x29
// GetJumpList
#define bios_get_jump_list 0x2a
/* ---- End of The BIOS Call Numbers ---- */


//#if !defined ( __thumb__)
#if defined ( __thumb__)
#define swi_call( x ) asm volatile("swi\t"#x ::: "r0","r1","r2","r3")
#else
#define swi_call( x ) asm volatile("swi\t"#x"<<16" ::: "r0","r1","r2","r3")
#endif


class bios_div_result
{
public:		// variables
	s32 quotient;
	s32 remainder;
	u32 quotient_abs;
	
} __attribute__((_ALIGN4));



inline void bios_do_soft_reset()
{
	swi_call(0x00);
}

inline void bios_do_register_ram_reset( u32 r0_value )
{
	asm __volatile__
	(
		"mov r0, %0\n\t"
		"swi 0x01\n\t"
		: 						// outputs
		: "r" (r0_value & 0xff)	// inputs
		: "r0"					// clobbers
	);
}

inline void bios_do_full_soft_reset()
{
	//bios_do_register_ram_reset(0x1c);
	//bios_do_register_ram_reset(0x18);
	bios_do_soft_reset();
}


inline void bios_wait_for_vblank()
{
	swi_call(0x05);
}


inline s32 bios_do_div( s32 numerator, s32 denominator )
{
	//nocash_soft_break();
	
	s32 ret;
	
	if ( denominator == 0 )
	{
		ret = 0;
	}
	else
	{
		asm __volatile__
		(
			"mov r0, %1\n\t"
			"mov r1, %2\n\t"
			"swi 0x06\n\t"
			"mov %0, r0\n\t"
			: "=r" (ret)							// outputs
			: "r" (numerator), "r" (denominator)	// inputs
			: "r0", "r1"							// clobbers
		);
	}
	
	return ret;
	
}

inline void bios_do_div( s32 numerator, s32 denominator, 
	bios_div_result& the_div_result )
{
	
	if ( denominator == 0 )
	{
		the_div_result.quotient = 0;
		the_div_result.remainder = 0;
		the_div_result.quotient_abs = 0;
	}
	else
	{
		asm __volatile__
		(
			"mov r0, %3\n\t"
			"mov r1, %4\n\t"
			"swi 0x06\n\t"
			"mov %0, r0\n\t"
			"mov %1, r1\n\t"
			"mov %2, r3\n\t"
			
			: "=r" (the_div_result.quotient), 
			"=r" (the_div_result.remainder), 
			"=r" (the_div_result.quotient_abs)		// outputs
			: "r" (numerator), "r" (denominator)	// inputs
			: "r0", "r1", "r2", "r3"				// clobbers
		);
	}
}




inline u16 bios_do_sqrt( u32 r0_value )
{
	u32 ret;
	
	asm __volatile__
	(
		"mov r0, %1\n\t"
		"swi 0x08\n\t"
		"mov %0, r0\n\t"
		: "=r" (ret)		// outputs
		: "r" (r0_value)	// inputs
		: "r0"				// clobbers
	);
	
	return (u16)ret;
	
}

inline void bios_do_lz77_uncomp_wram( const void* src, void* dst )
{
	//bios_lz77_uncomp_wram
	
	asm __volatile__
	(
		"mov r0, %0\n\t"
		"mov r1, %1\n\t"
		"swi 0x11\n\t"
		:								// outputs
		: "r"(src), "r"(dst)			// inputs
		: "r0", "r1" 					// clobbers
	);
}

inline void bios_do_lz77_uncomp_wram( const void* src, volatile void* dst )
{
	bios_do_lz77_uncomp_wram( src, (void*)dst );
}

inline void bios_do_lz77_uncomp_vram( const void* src, void* dst )
{
	//bios_lz77_uncomp_vram
	
	asm __volatile__
	(
		"mov r0, %0\n\t"
		"mov r1, %1\n\t"
		"swi 0x12\n\t"
		:								// outputs
		: "r"(src), "r"(dst)			// inputs
		: "r0", "r1" 					// clobbers
	);
}

inline void bios_do_lz77_uncomp_vram( const void* src, volatile void* dst )
{
	bios_do_lz77_uncomp_vram( src, (void*)dst );
}


inline void bios_do_hard_reset()
{
	swi_call(0x26);
}





#endif		// bios_function_wrappers_hpp
