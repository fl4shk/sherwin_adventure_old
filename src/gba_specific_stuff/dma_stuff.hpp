#ifndef dma_stuff_hpp
#define dma_stuff_hpp

#include "../game_engine_stuff/misc_types.hpp"
#include "memory_map.hpp"


/* ---- DMA Registers ---- */
// -- DMA Source Addresses --
// DMA 0 Source Address (Internal Memory)
#define reg_dma0sad *((vu32*)(mem_io + 0x00b0))
// DMA 1 Source Address (Any Memory)
#define reg_dma1sad *((vu32*)(mem_io + 0x00bc))
// DMA 2 Source Address (Any Memory)
#define reg_dma2sad *((vu32*)(mem_io + 0x00c8))
// DMA 3 Source Address (Any Memory)
#define reg_dma3sad *((vu32*)(mem_io + 0x00d4))


// -- DMA Destination Addresses --
// DMA 0 Destination Address (Internal Memory)
#define reg_dma0dad *((vu32*)(mem_io + 0x00b4))
// DMA 1 Destination Address (Internal Memory)
#define reg_dma1dad *((vu32*)(mem_io + 0x00c0))
// DMA 2 Destination Address (Internal Memory)
#define reg_dma2dad *((vu32*)(mem_io + 0x00cc))
// DMA 3 Destination Address (Any Memory)
#define reg_dma3dad *((vu32*)(mem_io + 0x00d8))


// -- DMA Control --
// DMA 0 Control
#define reg_dma0cnt *((vu32*)(mem_io + 0xb8))
// DMA 1 Control
#define reg_dma1cnt *((vu32*)(mem_io + 0xc4))
// DMA 2 Control
#define reg_dma2cnt *((vu32*)(mem_io + 0xd0))
// DMA 3 Control
#define reg_dma3cnt *((vu32*)(mem_io + 0xdc))
/* ---- End of DMA Registers ---- */


/* ---- #defines for DMACNT Registers ---- */
// Number of 16-bit or 32-bit Transfers 
#define dma_data_count( n ) ( n & 0xffff )
#define dma_data_count_mask ( (u32)(0x0000ffff) )

// -- Destination Adjustment --
// Increment After Each Transfer (Default)
#define dma_dst_inc ( 0x0 << 0x15 )
// Decrement After Each Transfer
#define dma_dst_dec ( 0x1 << 0x15 )
// No Destination Adjustment (Address is Fixed)
#define dma_dst_fixed ( 0x2 << 0x15 )
// Increment the Destination During Transfer, and Reset It
#define dma_dst_reload ( 0x3 << 0x15 )

#define dma_dst_mask ( (u32)(0x00600000) )


// -- Source Adjustment --
// Increment After Each Transfer
#define dma_src_inc ( 0x0 << 0x17 )
// Decrement After Each Transfer
#define dma_src_dec ( 0x1 << 0x17 )
// No Source Adjustment (Address is Fixed)
#define dma_src_fixed ( 0x2 << 0x17 )

#define dma_src_mask ( (u32)(0x01800000) )


// -- Repeat Flag --
// No Repeat at VBlank/HBlank (if set to those modes)
#define dma_repeat_off ( 0x0 << 0x19 )
// Repeat the DMA at VBlank/HBlank (if set to those modes)
#define dma_repeat_on ( 0x1 << 0x19 )

#define dma_repeat_mask ( (u32)(0x02000000) )


// -- Chunk Size (Copy by halfword or word) --
// 16-bit Chunk Size
#define dma_16 ( 0x0 << 0x1a )
// 32-bit Chunk Size
#define dma_32 ( 0x1 << 0x1a )

#define dma_chunk_size_mask ( (u32)(0x04000000) )


// -- Timing Mode (When the Transfer Should Start) --
// Start Immediately
#define dma_now ( 0x0 << 0x1c )
// Start at VBlank
#define dma_at_vblank ( 0x1 << 0x1c )
// Start at HBlank
#define dma_at_hblank ( 0x2 << 0x1c )
// Start at Refresh (Some Audio Stuffs)
#define dma_at_refresh ( 0x3 << 0x1c )
#define dma12_fifo ( 0x3 << 0x1c )

#define dma_timing_mask ( (u32)(0x30000000) )


// -- Interrupt Request --
// Don't Raise an Interrupt when Finished
#define dma_irq_off ( 0x0 << 0x1e )
// Raise an Interrupt when Finished
#define dma_irq_on ( 0x1 << 0x1e )

#define dma_irq_mask ( (u32)(0x40000000) )


// -- Enable the DMA Transfer for this Channel --
#define dma_enable ( 0x1 << 0x1f )
/* ---- End of #defines for DMACNT Registers ---- */


// Mirrors for the DMACNT registers
extern vu32 dma0cnt_mirror, dma1cnt_mirror, dma2cnt_mirror, dma3cnt_mirror;


/* ---- Wrapper Functions for DMA Copies ---- */

// These functions are extern "C" so that my assembly can access them
extern "C"
{

//void dma3_cpy( volatile void* dst, const void* src, u32 count, u32 mode )
//__attribute__((noinline));
void dma3_cpy( volatile void* dst, const void* src, u32 count, u32 mode );

void dma0_cpy( volatile void* dst, const void* src, u32 count, u32 mode );


//void dma3_fill( volatile void* dst, vu32 src, u32 count ) 
//	__attribute__((noinline));

void dma3_fill( volatile void* dst, vu32 src, u32 count );

}

/* ---- End of Wrapper Functions for DMA Copies ---- */



#endif		// dma_stuff_hpp
