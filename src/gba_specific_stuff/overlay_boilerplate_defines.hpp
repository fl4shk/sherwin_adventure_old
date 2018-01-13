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


#ifndef gba_specific_stuff__slash__overlay_boilerplate_defines_hpp
#define gba_specific_stuff__slash__overlay_boilerplate_defines_hpp


#define PPCAT_NX(a, b) a ## b
#define PPCAT(a, b) PPCAT_NX(a, b)
#define STRINGIZE_NX(a) #a
#define STRINGIZE(a) STRINGIZE_NX(a)

// EWRAM data linker overlay
#define _EWRAM_OVERLAY(num) gnu::section(STRINGIZE(PPCAT(.data, \
	num)))
#define _EWRAM_OVERLAY_PREFIX(num) PPCAT(__data,num)

#define _EWRAM_OVERLAY_SECTION_ROM_START(num) \
	PPCAT(_EWRAM_OVERLAY_PREFIX(num),_rom_start__)
#define _EWRAM_OVERLAY_SECTION_EWRAM_START(num) \
	PPCAT(_EWRAM_OVERLAY_PREFIX(num),_ewram_start__)
#define _EWRAM_OVERLAY_SECTION_END(num) \
	PPCAT(_EWRAM_OVERLAY_PREFIX(num),_ewram_end__)

#define _EXPOSE_EWRAM_OVERLAY(num) \
extern "C" size_t _EWRAM_OVERLAY_SECTION_ROM_START(num); \
extern "C" size_t _EWRAM_OVERLAY_SECTION_EWRAM_START(num); \
extern "C" size_t _EWRAM_OVERLAY_SECTION_END(num);


// IWRAM data linker overlay
#define _IWRAM_OVERLAY(num) gnu::section(STRINGIZE(PPCAT(.iwram_data, \
	num)))
#define _IWRAM_OVERLAY_PREFIX(num) PPCAT(__iwram_data,num)

#define _IWRAM_OVERLAY_SECTION_ROM_START(num) \
	PPCAT(_IWRAM_OVERLAY_PREFIX(num),_rom_start__)
#define _IWRAM_OVERLAY_SECTION_IWRAM_START(num) \
	PPCAT(_IWRAM_OVERLAY_PREFIX(num),_iwram_start__)
#define _IWRAM_OVERLAY_SECTION_END(num) \
	PPCAT(_IWRAM_OVERLAY_PREFIX(num),_iwram_end__)

#define _EXPOSE_IWRAM_OVERLAY(num) \
extern "C" size_t _IWRAM_OVERLAY_SECTION_ROM_START(num); \
extern "C" size_t _IWRAM_OVERLAY_SECTION_IWRAM_START(num); \
extern "C" size_t _IWRAM_OVERLAY_SECTION_END(num);


// BSS linker overlay
//#define _BSS_OVERLAY(num) gnu::section(".bss" #num)
#define _BSS_OVERLAY(num) gnu::section(STRINGIZE(PPCAT(.bss,num)))

#define _BSS_OVERLAY_PREFIX(num) PPCAT(__bss,num)

#define _BSS_OVERLAY_SECTION_START(num) \
	PPCAT(_BSS_OVERLAY_PREFIX(num),_start__)
#define _BSS_OVERLAY_SECTION_END(num) \
	PPCAT(_BSS_OVERLAY_PREFIX(num),_end__)

#define _EXPOSE_BSS_OVERLAY(num) \
extern "C" size_t _BSS_OVERLAY_SECTION_START(num); \
extern "C" size_t _BSS_OVERLAY_SECTION_END(num);


// IWRAM BSS linker overlay
#define _IWRAM_BSS_OVERLAY(num) gnu::section(STRINGIZE(PPCAT(.iwram_bss,num)))

#define _IWRAM_BSS_OVERLAY_PREFIX(num) PPCAT(__iwram_bss,num)

#define _IWRAM_BSS_OVERLAY_SECTION_START(num) \
	PPCAT(_IWRAM_BSS_OVERLAY_PREFIX(num),_start__)
#define _IWRAM_BSS_OVERLAY_SECTION_END(num) \
	PPCAT(_IWRAM_BSS_OVERLAY_PREFIX(num),_end__)

#define _EXPOSE_IWRAM_BSS_OVERLAY(num) \
extern "C" size_t _IWRAM_BSS_OVERLAY_SECTION_START(num); \
extern "C" size_t _IWRAM_BSS_OVERLAY_SECTION_END(num);




// SRAM linker overlay (potentially not necessary at all)
#define _SRAM_OVERLAY(num) gnu::section(STRINGIZE(PPCAT(.sram, num)))
#define _SRAM_OVERLAY_PREFIX(num) PPCAT(__sram,num)

#define _SRAM_OVERLAY_SECTION_START(num) \
	PPCAT(_SRAM_OVERLAY_PREFIX(num),_start__)
#define _SRAM_OVERLAY_SECTION_END(num) \
	PPCAT(_SRAM_OVERLAY_PREFIX(num),_end__)

#define _EXPOSE_SRAM_OVERLAY(num) \
extern "C" size_t _SRAM_OVERLAY_SECTION_START(num); \
extern "C" size_t _SRAM_OVERLAY_SECTION_END(num);



// EWRAM CODE linker overlay (potentially not necessary at all)
#define _EWRAM_CODE_OVERLAY(num) gnu::section(STRINGIZE(PPCAT(.ewram_code, \
	num)))
#define _EWRAM_CODE_OVERLAY_PREFIX(num) PPCAT(__ewram_code,num)

#define _EWRAM_CODE_OVERLAY_SECTION_ROM_START(num) \
	PPCAT(_EWRAM_CODE_OVERLAY_PREFIX(num),_rom_start__)
#define _EWRAM_CODE_OVERLAY_SECTION_EWRAM_START(num) \
	PPCAT(_EWRAM_CODE_OVERLAY_PREFIX(num),_ewram_start__)
#define _EWRAM_CODE_OVERLAY_SECTION_END(num) \
	PPCAT(_EWRAM_CODE_OVERLAY_PREFIX(num),_ewram_end__)

#define _EXPOSE_EWRAM_CODE_OVERLAY(num) \
extern "C" size_t _EWRAM_CODE_OVERLAY_SECTION_ROM_START(num); \
extern "C" size_t _EWRAM_CODE_OVERLAY_SECTION_EWRAM_START(num); \
extern "C" size_t _EWRAM_CODE_OVERLAY_SECTION_END(num);





// IWRAM CODE linker overlay
#define _IWRAM_CODE_OVERLAY(num) gnu::section(STRINGIZE(PPCAT \
	(.iwram_code, num)))
#define _IWRAM_CODE_OVERLAY_PREFIX(num) PPCAT(__iwram_code,num)

#define _IWRAM_CODE_OVERLAY_SECTION_ROM_START(num) \
	PPCAT(_IWRAM_CODE_OVERLAY_PREFIX(num),_rom_start__)
#define _IWRAM_CODE_OVERLAY_SECTION_IWRAM_START(num) \
	PPCAT(_IWRAM_CODE_OVERLAY_PREFIX(num),_iwram_start__)
#define _IWRAM_CODE_OVERLAY_SECTION_END(num) \
	PPCAT(_IWRAM_CODE_OVERLAY_PREFIX(num),_iwram_end__)

#define _EXPOSE_IWRAM_CODE_OVERLAY(num) \
extern "C" size_t _IWRAM_CODE_OVERLAY_SECTION_ROM_START(num); \
extern "C" size_t _IWRAM_CODE_OVERLAY_SECTION_IWRAM_START(num); \
extern "C" size_t _IWRAM_CODE_OVERLAY_SECTION_END(num);



#endif		// gba_specific_stuff__slash__overlay_boilerplate_defines_hpp
