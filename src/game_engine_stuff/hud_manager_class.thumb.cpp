#include "hud_manager_class.hpp"
#include "level_stuff/active_level_manager_class.hpp"

#include <string>
#include <sstream>
using namespace std;

bool hud_manager::hud_was_generated;

scr_entry hud_manager::bg1_screenblock_mirror[screenblock_size];

array_2d_helper<scr_entry> hud_manager::bg1_screenblock_2d
	( se_ram[bg1_sbb], screenblock_size_2d );
array_2d_helper<scr_entry> hud_manager::bg1_screenblock_mirror_2d 
	( bg1_screenblock_mirror, screenblock_size_2d );

//void hud_manager::plot_char_8x16_to_screenblock_mirror( u32 the_char, 
//	u32 pos_x, u32 pos_y )
//{
//	bg1_screenblock_mirror_2d.data_at( pos_x, pos_y )
//		= gfx_manager::hud_vram_as_tiles_start_offset
//		+ ( ( (char)the_char - ' ' ) * gfx_manager::num_tiles_in_ss_8x16 )
//		| se_palbank(bgps_in_level_hud);
//	
//	bg1_screenblock_mirror_2d.data_at( pos_x, pos_y + 1 )
//		= gfx_manager::hud_vram_as_tiles_start_offset
//		+ ( ( (char)the_char - ' ' ) * gfx_manager::num_tiles_in_ss_8x16 
//		+ 1 ) | se_palbank(bgps_in_level_hud);
//}
void hud_manager::plot_char_8x8_to_screenblock_mirror( u32 the_char,
	u32 pos_x, u32 pos_y )
{
	bg1_screenblock_mirror_2d.data_at( pos_x, pos_y )
		= gfx_manager::hud_vram_as_tiles_start_offset
		+ ( (char)the_char - ' ' ) | se_palbank(bgps_in_level_hud);
}

void hud_manager::update_hud_in_screenblock_mirror_2d()
{
	if (!hud_was_generated)
	{
		hud_was_generated = true;
		
		memfill32( bg1_screenblock_mirror, 0,
			sizeof(bg1_screenblock_mirror) / sizeof(u32) );
	}
	
	
	//static const char to_plot[] = "SHERWIN";
	//static const u32 to_plot_size = sizeof(to_plot) - 1;
	//
	//for ( u32 i=0; i<to_plot_size; ++i )
	//{
	//	plot_char_8x8_to_screenblock_mirror( to_plot[i], 2 + i, 0 );
	//}
	
	string to_plot = "SHERWIN";
	
	for ( u32 i=0; i<to_plot.size(); ++i )
	{
		plot_char_8x8_to_screenblock_mirror( to_plot[i], 1 + i, 0 );
	}
	
	
}

void hud_manager::copy_hud_from_array_2d_helper_to_vram()
{
	memcpy32( hud_manager::bg1_screenblock_2d.the_array,
		hud_manager::bg1_screenblock_mirror_2d.the_array,
		sizeof(scr_entry) * hud_manager::bg1_screenblock_mirror_2d
		.get_size() / sizeof(u32) );
}


