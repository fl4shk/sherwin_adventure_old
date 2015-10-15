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
	active_level::horiz_level_block_data_2d.data_at(coord).type = bt_dud;
}
