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


#ifndef gba_specific_stuff__slash__dma_stuff_hpp
#define gba_specific_stuff__slash__dma_stuff_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"

#include "../namespace_using.hpp"


/* ---- DMA Registers ---- */
// -- DMA Source Addresses --
// DMA 0 Source Address (Internal Memory)
#define REG_DMA0SAD *((vu32*)(MEM_IO + 0x00b0))
// DMA 1 Source Address (Any Memory)
#define REG_DMA1SAD *((vu32*)(MEM_IO + 0x00bc))
// DMA 2 Source Address (Any Memory)
#define REG_DMA2SAD *((vu32*)(MEM_IO + 0x00c8))
// DMA 3 Source Address (Any Memory)
#define REG_DMA3SAD *((vu32*)(MEM_IO + 0x00d4))


// -- DMA Destination Addresses --
// DMA 0 Destination Address (Internal Memory)
#define REG_DMA0DAD *((vu32*)(MEM_IO + 0x00b4))
// DMA 1 Destination Address (Internal Memory)
#define REG_DMA1DAD *((vu32*)(MEM_IO + 0x00c0))
// DMA 2 Destination Address (Internal Memory)
#define REG_DMA2DAD *((vu32*)(MEM_IO + 0x00cc))
// DMA 3 Destination Address (Any Memory)
#define REG_DMA3DAD *((vu32*)(MEM_IO + 0x00d8))


// -- DMA Control --
// DMA 0 Control
#define REG_DMA0CNT *((vu32*)(MEM_IO + 0xb8))
// DMA 1 Control
#define REG_DMA1CNT *((vu32*)(MEM_IO + 0xc4))
// DMA 2 Control
#define REG_DMA2CNT *((vu32*)(MEM_IO + 0xd0))
// DMA 3 Control
#define REG_DMA3CNT *((vu32*)(MEM_IO + 0xdc))
/* ---- End of DMA Registers ---- */


/* ---- #defines for DMACNT Registers ---- */
// Number of 16-bit or 32-bit Transfers 
#define DMA_DATA_COUNT(n) (n & 0xffff)
#define DMA_DATA_COUNT_MASK ((u32)(0x0000ffff))

// -- Destination Adjustment --
// Increment After Each Transfer (Default)
#define DMA_DST_INC (0x0 << 0x15)
// Decrement After Each Transfer
#define DMA_DST_DEC (0x1 << 0x15)
// No Destination Adjustment (Address Is Fixed)
#define DMA_DST_FIXED (0x2 << 0x15)
// Increment the Destination During Transfer, and Reset It
#define DMA_DST_RELOAD (0x3 << 0x15)

#define DMA_DST_MASK ((u32)(0x00600000))


// -- Source Adjustment --
// Increment After Each Transfer
#define DMA_SRC_INC (0x0 << 0x17)
// Decrement After Each Transfer
#define DMA_SRC_DEC (0x1 << 0x17)
// No Source Adjustment (Address Is Fixed)
#define DMA_SRC_FIXED (0x2 << 0x17)

#define DMA_SRC_MASK ((u32)(0x01800000))


// -- Repeat Flag --
// No Repeat at VBlank/HBlank (if set To those modes)
#define DMA_REPEAT_OFF (0x0 << 0x19)
// Repeat the DMA at VBlank/HBlank (if set To those modes)
#define DMA_REPEAT_ON (0x1 << 0x19)

#define DMA_REPEAT_MASK ((u32)(0x02000000))


// -- Chunk Size (Copy by halfword or word) --
// 16-bit Chunk Size
#define DMA_16 (0x0 << 0x1a)
// 32-bit Chunk Size
#define DMA_32 (0x1 << 0x1a)

#define DMA_CHUNK_SIZE_MASK ((u32)(0x04000000))


// -- Timing Mode (When the Transfer Should Start) --
// Start Immediately
#define DMA_NOW (0x0 << 0x1c)
// Start at VBlank
#define DMA_AT_VBLANK (0x1 << 0x1c)
// Start at HBlank
#define DMA_AT_HBLANK (0x2 << 0x1c)
// Start at Refresh (Some Audio Stuffs)
#define DMA_AT_REFRESH (0x3 << 0x1c)
#define DMA12_FIFO (0x3 << 0x1c)

#define DMA_TIMING_MASK ((u32)(0x30000000))


// -- Interrupt Request --
// Don't Raise an Interrupt when Finished
#define DMA_IRQ_OFF (0x0 << 0x1e)
// Raise an Interrupt when Finished
#define DMA_IRQ_ON (0x1 << 0x1e)

#define DMA_IRQ_MASK ((u32)(0x40000000))


// -- Enable the DMA Transfer for this Channel --
#define DMA_ENABLE (0x1 << 0x1f)
/* ---- End of #defines for DMACNT Registers ---- */


namespace sherwin_adventure
{

namespace gba
{

// Mirrors for the DMACNT registers
extern vu32 dma0cnt_mirror, dma1cnt_mirror, dma2cnt_mirror, dma3cnt_mirror;

}

}


/* ---- Wrapper Functions for DMA Copies ---- */

// These functions are extern "C" So That my assembly Can access them
extern "C"
{

//void dma3_cpy(volatile void* dst, const void* src, u32 count, u32 mode)
//[[gnu::noinline]];
void dma3_cpy(volatile void* dst, const void* src, u32 count, u32 mode);

void dma0_cpy(volatile void* dst, const void* src, u32 count, u32 mode);


//void dma3_fill(volatile void* dst, vu32 src, u32 count) 
//	[[gnu::noinline]];

void dma3_fill(volatile void* dst, vu32 src, u32 count);

}

/* ---- End of Wrapper Functions for DMA Copies ---- */



#endif		// gba_specific_stuff__slash__dma_stuff_hpp
