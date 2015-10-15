#include "active_level_manager_class.hpp"
#include "sprite_level_data_stuff.hpp"


#include "../../gba_specific_stuff/interrupt_stuff.hpp"



u32 active_level_manager::converted_block_tile_ids_0[bt_count],
	active_level_manager::converted_block_tile_ids_1[bt_count],
	active_level_manager::converted_block_tile_ids_2[bt_count],
	active_level_manager::converted_block_tile_ids_3[bt_count];

