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


#include "../../level_stuff/active_level_class.hpp"
#include "../../../general_utility_stuff/misc_types.hpp"
#include "../../sprite_stuff/sprite_manager_class.hpp"


const BlockStuffConstParams
	EyesBlockStuff::the_const_params
= {
	// metatile_number
	3,

	// palette_number
	0,

	// metatile_graphics_slot
	3,
};

void EyesBlockStuff::strongly_hit_response(Block& the_block, 
	const Vec2s32& coord)
{
	ActiveLevel::horiz_sublevel_block_data_2d.at(coord).type 
		= bt_dud;
	//ActiveLevel::persistent_block_data_arrays

	ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] = is_bt_dud;
}

void EyesBlockStuff::finish_initializing_using_persistent_data
	(Block& the_block)
{
	if (ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] == is_bt_dud)
	{
		the_block.type = bt_dud;
	}
}

//void EyesBlockStuff::strongly_hit_response(Block& the_block, 
//	const Vec2s32& coord)
//{
//	constexpr sprite_type the_spawnable_sprite_type = StWaffle;
//	ActiveLevel::horiz_sublevel_block_data_2d.at(coord).type = bt_dud;
//
//	Vec2s32 spawn_block_grid_coord = Vec2s32(coord.x, coord.y - 1);
//	Vec2F24p8 spawn_in_level_pos = Vec2F24p8
//		(make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
//		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col));
//
//	SpriteManager::spawn_a_sprite_basic(the_spawnable_sprite_type,
//		spawn_in_level_pos, GfxManager::bgofs_mirror[0], false);
//
//}

void EyesBlockWithStWaffleStuff::strongly_hit_response
	(Block& the_block, const Vec2s32& coord)
{
	constexpr sprite_type the_spawnable_sprite_type = StWaffle;
	ActiveLevel::horiz_sublevel_block_data_2d.at(coord).type 
		= bt_dud;

	Vec2s32 spawn_block_grid_coord = Vec2s32(coord.x, coord.y - 1);
	Vec2F24p8 spawn_in_level_pos = Vec2F24p8
		(make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col));

	SpriteManager::spawn_a_sprite_basic(the_spawnable_sprite_type, 
		spawn_in_level_pos, GfxManager::bgofs_mirror[0], false);

	ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] = EyesBlockStuff::is_bt_dud;

}

void EyesBlockWithStMuffinStuff::strongly_hit_response
	(Block& the_block, const Vec2s32& coord)
{
	constexpr sprite_type the_spawnable_sprite_type = StMuffin;
	ActiveLevel::horiz_sublevel_block_data_2d.at(coord).type 
		= bt_dud;

	Vec2s32 spawn_block_grid_coord = Vec2s32(coord.x, coord.y - 1);
	Vec2F24p8 spawn_in_level_pos = Vec2F24p8
		(make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col));

	SpriteManager::spawn_a_sprite_basic(the_spawnable_sprite_type, 
		spawn_in_level_pos, GfxManager::bgofs_mirror[0], false);

	ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] = EyesBlockStuff::is_bt_dud;
}

void EyesBlockWithStFireMuffinStuff::strongly_hit_response
	(Block& the_block, const Vec2s32& coord)
{
	constexpr sprite_type the_spawnable_sprite_type = StFireMuffin;
	ActiveLevel::horiz_sublevel_block_data_2d.at(coord).type 
		= bt_dud;

	Vec2s32 spawn_block_grid_coord = Vec2s32(coord.x, coord.y - 1);
	Vec2F24p8 spawn_in_level_pos = Vec2F24p8
		(make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col));

	SpriteManager::spawn_a_sprite_basic(the_spawnable_sprite_type, 
		spawn_in_level_pos, GfxManager::bgofs_mirror[0], false);

	ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] = EyesBlockStuff::is_bt_dud;
}

void EyesBlockWithStIceMuffinStuff::strongly_hit_response
	(Block& the_block, const Vec2s32& coord)
{
	constexpr sprite_type the_spawnable_sprite_type = StIceMuffin;
	ActiveLevel::horiz_sublevel_block_data_2d.at(coord).type 
		= bt_dud;

	Vec2s32 spawn_block_grid_coord = Vec2s32(coord.x, coord.y - 1);
	Vec2F24p8 spawn_in_level_pos = Vec2F24p8
		(make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col));

	SpriteManager::spawn_a_sprite_basic(the_spawnable_sprite_type, 
		spawn_in_level_pos, GfxManager::bgofs_mirror[0], false);

	ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] = EyesBlockStuff::is_bt_dud;
}

void EyesBlockWithStChocolateMuffinStuff::strongly_hit_response
	(Block& the_block, const Vec2s32& coord)
{
	constexpr sprite_type the_spawnable_sprite_type = StChocolateMuffin;
	ActiveLevel::horiz_sublevel_block_data_2d.at(coord).type 
		= bt_dud;

	Vec2s32 spawn_block_grid_coord = Vec2s32(coord.x, coord.y - 1);
	Vec2F24p8 spawn_in_level_pos = Vec2F24p8
		(make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col));

	SpriteManager::spawn_a_sprite_basic(the_spawnable_sprite_type, 
		spawn_in_level_pos, GfxManager::bgofs_mirror[0], false);

	ActiveLevel::persistent_block_data_arrays
		[ActiveLevel::the_current_active_sublevel_index]
		[the_block.persistent_data_index] = EyesBlockStuff::is_bt_dud;
}



