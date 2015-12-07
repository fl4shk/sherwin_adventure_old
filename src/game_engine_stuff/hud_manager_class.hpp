#ifndef hud_manager_class_hpp
#define hud_manager_class_hpp

#include "../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../gba_specific_stuff/bios_function_wrappers.hpp"
#include "array_2d_helper_class.hpp"
#include "gfx_manager_class.hpp"

class hud_manager
{
public:		// variables
	static bool hud_was_generated __attribute__((_ewram));
	
	static scr_entry bg1_screenblock_mirror[screenblock_size]
		__attribute__((_ewram));
	
	// bg1_screenblock_2d is in VRAM.
	static array_2d_helper<scr_entry> bg1_screenblock_2d;
	
	// bg1_screenblock_mirror_2d is in EWRAM.
	static array_2d_helper<scr_entry> bg1_screenblock_mirror_2d;
	
	static constexpr u32 char_to_plottable_char_arr_size = 0x100;
	static const char char_to_plottable_char_arr
		[char_to_plottable_char_arr_size];
	
public:		// functions
	// For some reason, NOT having these two functions marked as
	// __noinline__ causes problems.
	//static void plot_char_8x16_to_screenblock_mirror( u32 the_char, 
	//	u32 pos_x, u32 pos_y ) __attribute__((_iwram_code, __noinline__));
	
	static void plot_char_8x8_to_screenblock_mirror( u32 the_char,
		u32 pos_x, u32 pos_y ) __attribute__((_iwram_code, __noinline__));
	
	static void update_hud_in_screenblock_mirror_2d();
		__attribute__((_iwram_code));
	
	static void copy_hud_from_array_2d_helper_to_vram();
	
} __attribute__((_align4));


#endif		// hud_manager_class_hpp
