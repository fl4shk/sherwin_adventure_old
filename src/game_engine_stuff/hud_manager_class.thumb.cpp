#include "hud_manager_class.hpp"
#include "level_stuff/active_level_manager_class.hpp"

//#include <string>
//#include <sstream>
//using namespace std;

#include <stdlib.h>
#include <string.h>


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
	//// Don't plot ASCII control codes.
	//if ( the_char < ' ' )
	//{
	//	return;
	//}
	
	// Plot ASCII control codes as ' '.
	if ( the_char < ' ' )
	{
		bg1_screenblock_mirror_2d.data_at( pos_x, pos_y )
			= gfx_manager::hud_vram_as_tiles_start_offset
			| se_palbank(bgps_in_level_hud);
		return;
	}
	
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
	
	
	static const char sherwin_str[] = "SHERWIN:";
	//static const u32 sherwin_str_size = sizeof(sherwin_str) - 1;
	static const u32 sherwin_str_size = strlen(sherwin_str);
	
	u32 plot_x = 2;
	
	for ( u32 i=0; i<sherwin_str_size; ++i )
	{
		plot_char_8x8_to_screenblock_mirror( sherwin_str[i], plot_x, 0 );
		++plot_x;
	}
	
	
	const u32 player_hp_str_max_size = 5;
	char player_hp_str[player_hp_str_max_size];
	u32 player_hp_str_curr_size = 0;
	
	char temp_buf[player_hp_str_max_size];
	
	for ( u32 i=0; i<player_hp_str_max_size; ++i )
	{
		player_hp_str[i] = '\0';
	}
	
	
	s32 to_convert = ( player_sprite_stuff::remaining_hp < 0 )
		? 0 : player_sprite_stuff::remaining_hp;
	//s32 to_convert = 10;
	
	for (;;)
	{
		for ( u32 i=0; i<player_hp_str_max_size; ++i )
		{
			temp_buf[i] = '\0';
		}
		
		u32 rem = to_convert % 10;
		to_convert /= 10;
		//player_hp_str = (char)( '0' + rem ) + player_hp_str;
		
		temp_buf[0] = (char)( '0' + rem );
		strcat( temp_buf, player_hp_str ); 
		strcpy( player_hp_str, temp_buf );
		
		++player_hp_str_curr_size;
		
		if ( to_convert == 0 )
		{
			break;
		}
	}
	
	//for ( u32 i=0; i<player_hp_str_curr_size; ++i )
	for ( u32 i=0; i<player_hp_str_max_size; ++i )
	{
		plot_char_8x8_to_screenblock_mirror( player_hp_str[i], plot_x, 0 );
		++plot_x;
	}
	
}

void hud_manager::copy_hud_from_array_2d_helper_to_vram()
{
	memcpy32( hud_manager::bg1_screenblock_2d.the_array,
		hud_manager::bg1_screenblock_mirror_2d.the_array,
		sizeof(scr_entry) * hud_manager::bg1_screenblock_mirror_2d
		.get_size() / sizeof(u32) );
}


