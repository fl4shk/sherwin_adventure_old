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


#ifndef gba_specific_stuff__slash__bios_function_wrappers_hpp
#define gba_specific_stuff__slash__bios_function_wrappers_hpp

#include "attribute_defines.hpp"
#include "../general_utility_stuff/misc_types.hpp"
#include "interrupt_stuff.hpp"


/* ---- The BIOS Call Numbers ---- */
// SoftReset
#define BIOS_SOFT_RESET 0x00
// RegisterRamReset
#define BIOS_REGISTER_RAM_RESET 0x01
// Halt
#define BIOS_HALT 0x02
// Stop
#define BIOS_STOP 0x03
// IntrWait
#define BIOS_INTR_WAIT 0x04
// VBlankIntrWait
#define BIOS_VBLANK_INTR_WAIT 0x05
// Div
#define BIOS_DIV 0x06
// DivArm
#define BIOS_DIV_ARM 0x07


// Sqrt
#define BIOS_SQRT 0x08
// ArcTan
#define BIOS_ARCTAN 0x09
// ArcTan2
#define BIOS_ARCTAN2 0x0a
// CPUSet
#define BIOS_CPU_SET 0x0b
// CPUFastSet
#define BIOS_CPU_FAST_SET 0x0c
// BiosChecksum
#define BIOS_BIOS_CHECKSUM 0x0d
// BgAffineSet
#define BIOS_BG_AFFINE_SET 0x0e
// ObjAffineSet
#define BIOS_OBJ_AFFINE_SET 0x0f



// BitUnPack
#define BIOS_BIT_UNPACK 0x10
// LZ77UnCompWRAM
#define BIOS_LZ77_UNCOMP_WRAM 0x11
// LZ77UnCompVRAM
#define BIOS_LZ77_UNCOMP_VRAM 0x12
// HuffUnComp
#define BIOS_HUFF_UNCOMP 0x13
// RLUnCompWRAM
#define BIOS_RL_UNCOMP_WRAM 0x14
// RLUnCompVRAM
#define BIOS_RL_UNCOMP_VRAM 0x15
// Diff8bitUnFilterWRAM
#define BIOS_DIFF_8BIT_UNFILTER_WRAM 0x16
// Diff8bitUnFilterVRAM
#define BIOS_DIFF_8BIT_UNFILTER_VRAM 0x17



// Diff16bitUnFilter
#define BIOS_DIFF_16BIT_UNFILTER 0x18
// SoundBiasChange
#define BIOS_SOUND_BIAS_CHANGE 0x19
// SoundDriverInit
#define BIOS_SOUND_DRIVER_INIT 0x1a
// SoundDriverMain
#define BIOS_SOUND_DRIVER_MAIN 0x1b
// SoundDriverMode
#define BIOS_SOUND_DRIVER_MODE 0x1c
// SoundDriverVSync
#define BIOS_SOUND_DRIVER_VSYNC 0x1d
// SoundChannelClear
#define BIOS_SOUND_CHANNEL_CLEAR 0x1e
// MIDIKey2Freq
#define BIOS_MIDI_KEY_2_FREQ 0x1f


// MusicPlayerOpen
#define BIOS_MUSIC_PLAYER_OPEN 0x20
// MusicPlayerStart
#define BIOS_MUSIC_PLAYER_START 0x21
// MusicPlayerStop
#define BIOS_MUSIC_PLAYER_STOP 0x22
// MusicPlayerContinue
#define BIOS_MUSIC_PLAYER_CONTINUE 0x23
// MusicPlayerFadeOut
#define BIOS_MUSIC_PLAYER_FADE_OUT 0x24
// MultiBoot
#define BIOS_MULTIBOOT 0x25
// HardReset
#define BIOS_HARD_RESET 0x26
// CustomHalt
#define BIOS_CUSTOM_HALT 0x27


// SoundDriverVSyncOff
#define BIOS_SOUND_DRIVER_VSYNC_OFF 0x28
// SoundDriverVSyncOn
#define BIOS_SOUND_DRIVER_VSYNC_ON 0x29
// GetJumpList
#define BIOS_GET_JUMP_LIST 0x2a
/* ---- End of The BIOS Call Numbers ---- */


//#if !defined (__thumb__)
#if defined (__thumb__)
#define SWI_CALL(x) asm volatile("swi\t"#x ::: "r0","r1","r2","r3")
#else
#define SWI_CALL(x) asm volatile("swi\t"#x"<<16" ::: "r0","r1","r2","r3")
#endif


namespace sherwin_adventure
{

namespace gba
{

class _alignas_regular BiosDivResult
{
public:		// variables
	s32 quotient;
	s32 remainder;
	u32 quotient_abs;

};



inline void bios_do_soft_reset()
{
	SWI_CALL(0x00);
}

inline void bios_do_register_ram_reset(u32 r0_value)
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
	SWI_CALL(0x05);
}


inline s32 bios_do_div(s32 numerator, s32 denominator)
{
	//nocash_soft_break();

	s32 ret;

	if (denominator == 0)
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

inline void bios_do_div(s32 numerator, s32 denominator, 
	BiosDivResult& the_div_result)
{

	if (denominator == 0)
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




inline u16 bios_do_sqrt(u32 r0_value)
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

inline void bios_do_lz77_uncomp_wram(const void* src, void* dst)
{
	//BIOS_LZ77_UNCOMP_WRAM

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

inline void bios_do_lz77_uncomp_wram(const void* src, volatile void* dst)
{
	bios_do_lz77_uncomp_wram(src, (void*)dst);
}

inline void bios_do_lz77_uncomp_vram(const void* src, void* dst)
{
	//BIOS_LZ77_UNCOMP_VRAM

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

inline void bios_do_lz77_uncomp_vram(const void* src, volatile void* dst)
{
	bios_do_lz77_uncomp_vram(src, (void*)dst);
}


inline void bios_do_hard_reset()
{
	SWI_CALL(0x26);
}

}

}

#endif		// gba_specific_stuff__slash__bios_function_wrappers_hpp
