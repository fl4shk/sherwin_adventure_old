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

// Dummy function to be implemented by classes that inherit from this one,
// if they need it.
void block_base_stuff::strongly_hit_response( block& the_block, 
	const vec2_s32& coord )
{
}

// Dummy function to be implemented by classes that inherit from this one,
// if they need it.
void block_base_stuff::finish_initializing_using_persistent_data
	( block& the_block )
{
}


