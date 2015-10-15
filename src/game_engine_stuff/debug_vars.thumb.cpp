#include "debug_vars.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"


u32 curr_debug_s32_index, curr_debug_u32_index, curr_debug_f24p8_index,
	curr_debug_f8p8_index, curr_debug_st_result_index;


vs32 debug_arr_s32[debug_arr_s32_size];
vu32 debug_arr_u32[debug_arr_u32_size];
fixed24p8 debug_arr_f24p8[debug_arr_f24p8_size];
fixed8p8 debug_arr_f8p8[debug_arr_f8p8_size];


void clear_debug_vars()
{
	curr_debug_s32_index = 0;
	curr_debug_u32_index = 0;
	curr_debug_f24p8_index = 0;
	
	memfill32( debug_arr_s32, 0, ( debug_arr_s32_size
		*  sizeof(s32) ) / sizeof(u32) );
	memfill32( debug_arr_u32, 0, debug_arr_u32_size );
	memfill32( debug_arr_f24p8, 0, ( debug_arr_f24p8_size
		*  sizeof(fixed24p8) ) / sizeof(u32) );
	memfill32( debug_arr_f8p8, 0, ( debug_arr_f8p8_size 
		* sizeof(fixed8p8) ) / sizeof(u32) );
}



