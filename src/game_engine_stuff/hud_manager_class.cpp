// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
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


#include "hud_manager_class.hpp"
#include "level_stuff/active_level_manager_class.hpp"

//#include <string>
//#include <sstream>
//using namespace std;

#include <stdlib.h>
#include <string.h>

#include "sprite_stuff/sprite_type_includes.hpp"

bool HudManager::hud_was_generated;

scr_entry HudManager::bg1_screenblock_mirror[screenblock_size];

ArrayCsz_2dHelper<scr_entry, screenblock_xsize, screenblock_ysize > 
	HudManager::bg1_screenblock_2d(SE_RAM[bg1_sbb]);
ArrayCsz_2dHelper<scr_entry, screenblock_xsize, screenblock_ysize > 
	HudManager::bg1_screenblock_mirror_2d(bg1_screenblock_mirror);

const char HudManager::char_to_plottable_char_arr
	[char_to_plottable_char_arr_size]
	= { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', '!', '"', '#', '$', '%', '&', '\'', '(',
	')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D',
	'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
	'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|',
	'}', '~', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ' };
	

//void HudManager::plot_char_8x16_to_screenblock_mirror(u32 the_char, 
//	u32 pos_x, u32 pos_y)
//{
//	bg1_screenblock_mirror_2d.at(pos_x, pos_y)
//		= GfxManager::hud_vram_as_tiles_start_offset
//		+ (((char)the_char - ' ') * GfxManager::num_tiles_in_ss_8x16)
//		| SE_PALBANK(bgps_in_level_hud);
//	
//	bg1_screenblock_mirror_2d.at(pos_x, pos_y + 1)
//		= GfxManager::hud_vram_as_tiles_start_offset
//		+ (((char)the_char - ' ') * GfxManager::num_tiles_in_ss_8x16 
//		+ 1) | SE_PALBANK(bgps_in_level_hud);
//}

//void HudManager::plot_char_8x8_to_screenblock_mirror(u32 the_char,
//	u32 pos_x, u32 pos_y)
//{
//	//// Don't plot ASCII control codes.
//	//if (the_char < ' ')
//	//{
//	//	return;
//	//}
//	
//	//// Plot ASCII control codes as ' '.
//	//if (the_char < ' ')
//	//{
//	//	bg1_screenblock_mirror_2d.at(pos_x, pos_y)
//	//		= GfxManager::hud_vram_as_tiles_start_offset
//	//		| SE_PALBANK(bgps_in_level_hud);
//	//	return;
//	//}
//	//
//	//bg1_screenblock_mirror_2d.at(pos_x, pos_y)
//	//	= GfxManager::hud_vram_as_tiles_start_offset
//	//	+ ((char)the_char - ' ') | SE_PALBANK(bgps_in_level_hud);
//	
//	bg1_screenblock_mirror_2d.at(pos_x, pos_y)
//		= (GfxManager::hud_vram_as_tiles_start_offset
//		+ (char_to_plottable_char_arr[(u32)((u8)the_char)] - ' '))
//		| SE_PALBANK(bgps_in_level_hud);
//}

void HudManager::plot_horiz_str_8x8_to_screenblock_mirror
	(const char* str, u32 str_size, u32& plot_x, u32& plot_y)
{
	
	for (u32 i=0; i<str_size; ++i)
	{
		if (plot_x >= screenblock_xsize)
		{
			plot_x = 0;
			++plot_y;
		}
		
		bg1_screenblock_mirror_2d.at(plot_x, plot_y)
			= (GfxManager::hud_vram_as_tiles_start_offset
			+ (char_to_plottable_char_arr[(u32)(str[i])] - ' '))
			| SE_PALBANK(bgps_in_level_hud);
		
		++plot_x;
	}
	
}


void HudManager::update_hud_in_screenblock_mirror_2d()
{
	if (!hud_was_generated)
	{
		hud_was_generated = true;
		
		memfill32(bg1_screenblock_mirror, 0,
			sizeof(bg1_screenblock_mirror) / sizeof(u32));
	}
	
	//memfill32(bg1_screenblock_mirror, 0,
	//	sizeof(bg1_screenblock_mirror) / sizeof(u32));
	
	
	static const char sherwin_str[] = "SHERWIN:";
	//static const u32 sherwin_str_size = sizeof(sherwin_str) - 1;
	static const u32 sherwin_str_size = strlen(sherwin_str);
	
	u32 plot_x = 2;
	u32 plot_y = 0;
	
	
	//for (u32 i=0; i<sherwin_str_size; ++i)
	//{
	//	plot_char_8x8_to_screenblock_mirror(sherwin_str[i], plot_x, 0);
	//	++plot_x;
	//}
	
	plot_horiz_str_8x8_to_screenblock_mirror(sherwin_str,
		sherwin_str_size, plot_x, plot_y);
	
	
	//u32 some_number_str_curr_size = 0;
	
	static constexpr u32 some_number_str_max_size = 5;
	char some_number_str[some_number_str_max_size];
	
	//char temp_buf[some_number_str_max_size];
	
	//for (u32 i=0; i<some_number_str_max_size; ++i)
	//{
	//	some_number_str[i] = '\0';
	//	temp_buf[i] = '\0';
	//}
	
	
	s32 to_convert = (PlayerSprite::remaining_hp < 0)
		? 0 : PlayerSprite::remaining_hp;
	//s32 to_convert = 10;
	
	//for (;;)
	//{
	//	for (u32 i=0; i<some_number_str_max_size; ++i)
	//	{
	//		temp_buf[i] = '\0';
	//	}
	//	
	//	u32 rem = to_convert % 10;
	//	to_convert /= 10;
	//	//some_number_str = (char)('0' + rem) + some_number_str;
	//	
	//	temp_buf[0] = (char)('0' + rem);
	//	strcat(temp_buf, some_number_str); 
	//	strcpy(some_number_str, temp_buf);
	//	
	//	++some_number_str_curr_size;
	//	
	//	if (to_convert == 0)
	//	{
	//		break;
	//	}
	//}
	
	u32 some_number_str_curr_size = snprintf(some_number_str, 
		some_number_str_max_size, "%i", to_convert);
	
	
	////for (u32 i=0; i<some_number_str_curr_size; ++i)
	//for (u32 i=0; i<some_number_str_max_size; ++i)
	//{
	//	plot_char_8x8_to_screenblock_mirror(some_number_str[i], plot_x, 0);
	//	++plot_x;
	//}
	//plot_horiz_str_8x8_to_screenblock_mirror(some_number_str,
	//	some_number_str_curr_size, plot_x, plot_y);
	plot_horiz_str_8x8_to_screenblock_mirror(some_number_str,
		some_number_str_max_size, plot_x, plot_y);
	
	auto print_num_debug = [&](u32 some_num) -> void
	{
		//plot_x -= some_number_str_curr_size;
		plot_x -= some_number_str_max_size;
		++plot_y;
		//some_number_str_curr_size = 0;
		for (u32 i=0; i<some_number_str_max_size; ++i)
		{
			some_number_str[i] = '\0';
		}
		some_number_str_curr_size = snprintf(some_number_str,
			some_number_str_max_size, "%i", some_num);
		
		//for (;;)
		//{
		//	for (u32 i=0; i<some_number_str_max_size; ++i)
		//	{
		//		temp_buf[i] = '\0';
		//	}
		//	
		//	u32 rem = some_num % 10;
		//	some_num /= 10;
		//	//some_number_str = (char)('0' + rem) + some_number_str;
		//	
		//	temp_buf[0] = (char)('0' + rem);
		//	strcat(temp_buf, some_number_str); 
		//	strcpy(some_number_str, temp_buf);
		//	
		//	++some_number_str_curr_size;
		//	
		//	if (some_num == 0)
		//	{
		//		break;
		//	}
		//}
		
		//plot_horiz_str_8x8_to_screenblock_mirror(some_number_str,
		//	some_number_str_curr_size, plot_x, plot_y);
		plot_horiz_str_8x8_to_screenblock_mirror(some_number_str,
			some_number_str_max_size, plot_x, plot_y);
	};
	
	
	////print_num_debug(Sprite::tallest_height_val.curr);
	//print_num_debug(SpriteManager::the_player->the_oam_entry
	//	.attr0);
	//print_num_debug(SpriteManager::the_player->the_oam_entry
	//	.attr0);
	//print_num_debug(debug_s32_arr[0]);
	
	//print_num_debug(SpriteManager::the_player->the_oam_entry
	//	.attr1);
	//print_num_debug(SpriteManager::the_player->the_oam_entry
	//	.get_tile_number());
	//print_num_debug(debug_s32_arr[1]);
	
	//print_num_debug(SpriteManager::the_player_oam_index);
	//print_num_debug(SpriteManager::the_player
	//	->get_prev_on_ground());
	//print_num_debug(SpriteManager::the_player
	//	->get_curr_on_ground());
	//print_num_debug(SpriteManager::the_player
	//	->get_prev_on_slope());
	//print_num_debug(SpriteManager::the_player
	//	->get_curr_on_slope());
	
	//print_num_debug(debug_s32_arr[0]);
	//print_num_debug(debug_s32_arr[1]);
	//print_num_debug(debug_s32_arr[2]);
	//print_num_debug(debug_s32_arr[3]);
	print_num_debug(SpriteManager::num_active_sprites);
}



void HudManager::copy_hud_from_array_csz_2d_helper_to_vram()
{
	memcpy32(HudManager::bg1_screenblock_2d.the_array,
		HudManager::bg1_screenblock_mirror_2d.the_array,
		sizeof(scr_entry) * HudManager::bg1_screenblock_mirror_2d
		.get_size() / sizeof(u32));
}


