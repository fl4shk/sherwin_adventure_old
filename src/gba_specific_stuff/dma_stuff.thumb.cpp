#include "dma_stuff.hpp"

vu32 dma0cnt_mirror, dma1cnt_mirror, dma2cnt_mirror, dma3cnt_mirror;


extern "C"
{

// Copy generic data (in units of words or halfwords) using DMA3
//inline void dma_cpy( volatile void* dst, const void* src, u32 count, 
//	u32 mode = 1 )
void dma3_cpy( volatile void* dst, const void* src, u32 count, 
	u32 mode = 1 )
{
	static const u32 chunk_size_arr[2] = { dma_16, dma_32 };
	
	// Store the addresses of src and dst
	reg_dma3sad = (u32)(src);
	reg_dma3dad = (u32)(dst);
	
	//dma3cnt_mirror = dma_data_count(count) | dma_32;
	dma3cnt_mirror = dma_data_count(count) | chunk_size_arr[mode & 0x1];
	reg_dma3cnt = dma3cnt_mirror | dma_enable;
	
	
	
	// We have to wait at least two cycles before we can access DMA
	// registers again.
	asm volatile
	(
		"nop\n\t"
		//"nop\n\t"
	);
	
	
}

void dma0_cpy( volatile void* dst, const void* src, u32 count, 
	u32 mode = 1 )
{
	static const u32 chunk_size_arr[2] = { dma_16, dma_32 };
	
	// Store the addresses of src and dst
	reg_dma0sad = (u32)(src);
	reg_dma0dad = (u32)(dst);
	
	//dma3cnt_mirror = dma_data_count(count) | dma_32;
	dma0cnt_mirror = dma_data_count(count) | chunk_size_arr[mode & 0x1];
	reg_dma0cnt = dma0cnt_mirror | dma_enable;
	
	
	
	// We have to wait at least two cycles before we can access DMA
	// registers again.
	asm volatile
	(
		"nop\n\t"
		//"nop\n\t"
	);
	
	
}


// Fill the destination with a word using DMA3
//inline void dma_fill( volatile void* dst, vu32 src, u32 count )
void dma3_fill( volatile void* dst, vu32 src, u32 count )
{
	// Store the addresses of src and dst
	reg_dma3sad = (u32)((const void *)(&src));
	reg_dma3dad = (u32)(dst);
	
	dma3cnt_mirror = dma_data_count(count) | dma_src_fixed | dma_32;
	reg_dma3cnt = dma3cnt_mirror | dma_enable;
	
	
	
	// We have to wait at least two cycles before we can access DMA
	// registers again.
	asm volatile
	(
		"nop\n\t"
		//"nop\n\t"
	);
	
}

}
