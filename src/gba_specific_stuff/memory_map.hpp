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


#ifndef gba_specific_stuff__slash__memory_map_hpp
#define gba_specific_stuff__slash__memory_map_hpp

#include "../general_utility_stuff/misc_types.hpp"


#define MEM_EWRAM 0x02000000
#define MEM_IWRAM 0x03000000
#define MEM_SRAM 0x0e000000


#define MEM_IO 0x04000000
#define MEM_PAL_RAM 0x05000000
#define MEM_VRAM 0x06000000
#define MEM_OAM 0x07000000


#define MEM_VRAM_PAGE_0 0x06000000
#define MEM_VRAM_PAGE_1 0x0600a000



// The start of BG Palette RAM
#define MEM_BG_PAL 0x05000000

// The start of OBJ Palette RAM
#define MEM_OBJ_PAL 0x05000200




#endif		// gba_specific_stuff__slash__memory_map_hpp
