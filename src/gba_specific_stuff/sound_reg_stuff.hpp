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


#ifndef gba_specific_stuff__slash__sound_reg_stuff_hpp
#define gba_specific_stuff__slash__sound_reg_stuff_hpp


#include "../game_engine_stuff/misc_types.hpp"
#include "attribute_defines.hpp"
#include "memory_map.hpp"



// DMA Sound Control/Mixing (R/W)
#define REG_SOUNDCNT_H		*((vu16*)(MEM_IO + 0x82))

// Sound on/off (R/W)
#define REG_SOUNDCNT_X		*((vu16*)(MEM_IO + 0x84))


// Sound A FIFO, Data 0 and Data 1 (W)
#define REG_FIFO_A_L		*((vu16*)(MEM_IO + 0xa0))
// Sound A FIFO, Data 2 and Data 3 (W)
#define REG_FIFO_A_H		*((vu16*)(MEM_IO + 0xa2))


// Sound B FIFO, Data 0 and Data 1 (W)
#define REG_FIFO_B_L		*((vu16*)(MEM_IO + 0xa4))
// Sound B FIFO, Data 2 and Data 3 (W)
#define REG_FIFO_B_H		*((vu16*)(MEM_IO + 0xa6))




// Defines for REG_SOUNDCNT_H

// 25% Volume for the GBC-compatible channels
#define CHANNEL_GBC_VOL_25				(0x0 << 0)
// 50% Volume
#define CHANNEL_GBC_VOL_50				(0x1 << 0)
// 100% Volume
#define CHANNEL_GBC_VOL_100				(0x2 << 0)

#define CHANNEL_GBC_VOL_MASK			(0x0003)


// DMA Sound A Volume

// 50% Volume for DMA Sound A
#define DMA_SOUND_A_VOL_50				(0x0 << 2)
// 100% Volume
#define DMA_SOUND_A_VOL_100				(0x1 << 2)

#define DMA_SOUND_A_VOL_MASK			(0x0004)



// DMA Sound B Volume

// 50% Volume for DMA Sound B
#define DMA_SOUND_B_VOL_50				(0x0 << 3)
// 100% Volume
#define DMA_SOUND_B_VOL_100				(0x1 << 3)

#define DMA_SOUND_B_VOL_MASK			(0x0008)



// DMA Sound A RIGHT (for stereo sound)
#define DMA_SOUND_A_RIGHT_DISABLE		(0x0 << 8)
#define DMA_SOUND_A_RIGHT_ENABLE		(0x1 << 8)

#define DMA_SOUND_A_RIGHT_MASK			(0x0100)


// DMA Sound A LEFT (for stereo sound)
#define DMA_SOUND_A_LEFT_DISABLE		(0x0 << 9)
#define DMA_SOUND_A_LEFT_ENABLE			(0x1 << 9)

#define DMA_SOUND_A_LEFT_MASK			(0x0200)



// DMA Sound A Timer Select (Timer 0 or Timer 1)
#define DMA_SOUND_A_USE_TIMER_0			(0x0 << 10)
#define DMA_SOUND_A_USE_TIMER_1			(0x1 << 10)

#define DMA_SOUND_A_TIMER_SELECT_MASK	(0x0400)


// DMA Sound A Reset FIFO
#define DMA_SOUND_A_RESET_FIFO			(0x1 << 11)





// DMA Sound B RIGHT (for stereo sound)
#define DMA_SOUND_B_RIGHT_DISABLE		(0x0 << 12)
#define DMA_SOUND_B_RIGHT_ENABLE		(0x1 << 12)

#define DMA_SOUND_B_RIGHT_MASK			(0x1000)


// DMA Sound B LEFT (for stereo sound)
#define DMA_SOUND_B_LEFT_DISABLE		(0x0 << 13)
#define DMA_SOUND_B_LEFT_ENABLE			(0x1 << 13)

#define DMA_SOUND_B_LEFT_MASK			(0x2000)



// DMA Sound B Timer Select (Timer 0 or Timer 1)
#define DMA_SOUND_B_USE_TIMER_0			(0x0 << 14)
#define DMA_SOUND_B_USE_TIMER_1			(0x1 << 14)

#define DMA_SOUND_B_TIMER_SELECT_MASK	(0x4000)


// DMA Sound A Reset FIFO
#define DMA_SOUND_B_RESET_FIFO			(0x1 << 15)




// FIFO Master Switch for REG_SOUNDCNT_X
#define SOUND_FIFO_DISABLE				(0x0 << 7)
#define SOUND_FIFO_ENABLE				(0x1 << 7)





#endif		// gba_specific_stuff__slash__sound_reg_stuff_hpp
