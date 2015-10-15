#include "../level_stuff/active_level_class.hpp"
#include "../misc_types.hpp"

const u32 block_base_stuff::get_metatile_number()
{
	return metatile_number;
}
const u32 block_base_stuff::get_palette_number()
{
	return palette_number;
}
const u32 block_base_stuff::get_metatile_graphics_slot()
{
	return metatile_graphics_slot;
}
void block_base_stuff::strongly_hit_response( block& the_block, 
	const vec2_s32& coord )
{
}
