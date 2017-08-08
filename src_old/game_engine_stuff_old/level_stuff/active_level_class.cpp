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


#include "active_level_class.hpp"
#include "../sprite_stuff/sprite_class.hpp"
#include "sprite_level_data_stuff.hpp"
#include "sublevel_class.hpp"
#include "active_level_manager_class.hpp"
//#include "../sa_list_class_stuff.hpp"

Block ActiveLevel::blank_block;

const vec2_u32 ActiveLevel::horiz_sublevel_size_2d
	(horiz_sublevel_xsize, horiz_sublevel_ysize);

Block ActiveLevel::block_data_array[block_data_array_size];
//	__attribute__((_ewram));


u16 ActiveLevel::persistent_block_data_arrays[max_num_sublevels]
	[persistent_block_data_array_size]; //__attribute__((_ewram));


//Array_2dHelper<Block> ActiveLevel::horiz_sublevel_block_data_2d 
//	(ActiveLevel::block_data_array, 
//	ActiveLevel::horiz_sublevel_size_2d);
ArrayCsz2dHelper<Block, ActiveLevel::horiz_sublevel_xsize,
	ActiveLevel::horiz_sublevel_ysize > 
	ActiveLevel::horiz_sublevel_block_data_2d(block_data_array);


//std::array<std::forward_list<SpriteInitParamGroup>, 
//	ActiveLevel::horiz_sublevel_xsize > 
//	ActiveLevel::horiz_sublevel_sprite_ipg_lists; 
//	//__attribute__((_ewram));

//std::array<std::array<SpriteInitParamGroup, horiz_sublevel_ysize >, 
//	ActiveLevel::horiz_sublevel_xsize > 
//	ActiveLevel::horiz_sublevel_sprite_ipg_lists; 
//	//__attribute__((_ewram));

SaListStuff::SaArrayOfLists<SpriteInitParamGroup, 
	ActiveLevel::max_num_sprite_ipgs_per_sublevel,
	ActiveLevel::horiz_sublevel_xsize > 
	ActiveLevel::horiz_sublevel_sprite_ipg_lists;


scr_entry ActiveLevel::bg0_screenblock_mirror[screenblock_size];



ArrayCsz2dHelper<scr_entry, screenblock_xsize, screenblock_ysize > 
	ActiveLevel::bg0_screenblock_2d(SE_RAM[BG0_SBB]);
ArrayCsz2dHelper<scr_entry, screenblock_xsize, screenblock_ysize > 
	ActiveLevel::bg0_screenblock_mirror_2d(bg0_screenblock_mirror);

const Level* ActiveLevel::the_current_level_ptr;
u32 ActiveLevel::the_current_active_sublevel_index;



//const SublevelPointer& ActiveLevel::get_curr_sublevel_ptr()
//{
//	return the_current_level_ptr->get_sublevels()
//		[the_current_active_sublevel_index];
//	//// temporary
//	//return the_current_level_ptr->get_sublevels()[0];
//}


