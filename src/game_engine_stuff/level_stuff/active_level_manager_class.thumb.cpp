// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#include "active_level_manager_class.hpp"
#include "sprite_level_data_stuff.hpp"


#include "../../gba_specific_stuff/interrupt_stuff.hpp"



u32 active_level_manager::converted_block_tile_ids_0[bt_count],
	active_level_manager::converted_block_tile_ids_1[bt_count],
	active_level_manager::converted_block_tile_ids_2[bt_count],
	active_level_manager::converted_block_tile_ids_3[bt_count];

