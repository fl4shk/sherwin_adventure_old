#include "../level_stuff/active_level_class.hpp"
#include "../misc_types.hpp"


const u32 exclam_block_stuff::get_metatile_number()
{
	return metatile_number;
}
const u32 exclam_block_stuff::get_palette_number()
{
	return palette_number;
}
const u32 exclam_block_stuff::get_metatile_graphics_slot()
{
	return metatile_graphics_slot;
}
void exclam_block_stuff::strongly_hit_response( block& the_block, 
	const vec2_s32& coord )
{
	active_level::horiz_sublevel_block_data_2d.data_at(coord).type 
		= bt_dud;
	
	active_level::persistent_block_data_arrays
		[active_level::the_current_active_sublevel_index]
		[the_block.persistent_data_index] = is_bt_dud;
}
void exclam_block_stuff::finish_initializing_using_persistent_data
	( block& the_block )
{
	if ( active_level::persistent_block_data_arrays
		[active_level::the_current_active_sublevel_index]
		[the_block.persistent_data_index] == is_bt_dud )
	{
		the_block.type = bt_dud;
	}
}


