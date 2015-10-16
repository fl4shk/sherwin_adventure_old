#include "../level_stuff/active_level_class.hpp"
#include "../misc_types.hpp"
#include "../sprite_stuff/sprite_manager_class.hpp"


const u32 eyes_block_stuff::get_metatile_number()
{
	return metatile_number;
}
const u32 eyes_block_stuff::get_palette_number()
{
	return palette_number;
}
const u32 eyes_block_stuff::get_metatile_graphics_slot()
{
	return metatile_graphics_slot;
}

void eyes_block_stuff::strongly_hit_response( block& the_block, 
	const vec2_s32& coord )
{
	active_level::horiz_level_block_data_2d.data_at(coord).type = bt_dud;
	//active_level::persistent_block_data_arrays
}

//void eyes_block_stuff::strongly_hit_response( block& the_block, 
//	const vec2_s32& coord )
//{
//	constexpr sprite_type the_spawnable_sprite_type = st_waffle;
//	active_level::horiz_level_block_data_2d.data_at(coord).type = bt_dud;
//	
//	vec2_s32 spawn_block_grid_coord = vec2_s32( coord.x, coord.y - 1 );
//	vec2_f24p8 spawn_in_level_pos = vec2_f24p8
//		( make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
//		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col) );
//	
//	sprite_manager::spawn_a_sprite_basic( the_spawnable_sprite_type,
//		spawn_in_level_pos, bgofs_mirror[0].curr, false );
//	
//}

void eyes_block_with_st_waffle_stuff::strongly_hit_response
	( block& the_block, const vec2_s32& coord )
{
	constexpr sprite_type the_spawnable_sprite_type = st_waffle;
	active_level::horiz_level_block_data_2d.data_at(coord).type = bt_dud;
	
	vec2_s32 spawn_block_grid_coord = vec2_s32( coord.x, coord.y - 1 );
	vec2_f24p8 spawn_in_level_pos = vec2_f24p8
		( make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col) );
	
	sprite_manager::spawn_a_sprite_basic( the_spawnable_sprite_type, 
		spawn_in_level_pos, bgofs_mirror[0].curr, false );
}

void eyes_block_with_st_muffin_stuff::strongly_hit_response
	( block& the_block, const vec2_s32& coord )
{
	constexpr sprite_type the_spawnable_sprite_type = st_muffin;
	active_level::horiz_level_block_data_2d.data_at(coord).type = bt_dud;
	
	vec2_s32 spawn_block_grid_coord = vec2_s32( coord.x, coord.y - 1 );
	vec2_f24p8 spawn_in_level_pos = vec2_f24p8
		( make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col) );
	
	sprite_manager::spawn_a_sprite_basic( the_spawnable_sprite_type, 
		spawn_in_level_pos, bgofs_mirror[0].curr, false );
}

void eyes_block_with_st_fire_muffin_stuff::strongly_hit_response
	( block& the_block, const vec2_s32& coord )
{
	constexpr sprite_type the_spawnable_sprite_type = st_fire_muffin;
	active_level::horiz_level_block_data_2d.data_at(coord).type = bt_dud;
	
	vec2_s32 spawn_block_grid_coord = vec2_s32( coord.x, coord.y - 1 );
	vec2_f24p8 spawn_in_level_pos = vec2_f24p8
		( make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col) );
	
	sprite_manager::spawn_a_sprite_basic( the_spawnable_sprite_type, 
		spawn_in_level_pos, bgofs_mirror[0].curr, false );
}

void eyes_block_with_st_ice_muffin_stuff::strongly_hit_response
	( block& the_block, const vec2_s32& coord )
{
	constexpr sprite_type the_spawnable_sprite_type = st_ice_muffin;
	active_level::horiz_level_block_data_2d.data_at(coord).type = bt_dud;
	
	vec2_s32 spawn_block_grid_coord = vec2_s32( coord.x, coord.y - 1 );
	vec2_f24p8 spawn_in_level_pos = vec2_f24p8
		( make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col) );
	
	sprite_manager::spawn_a_sprite_basic( the_spawnable_sprite_type, 
		spawn_in_level_pos, bgofs_mirror[0].curr, false );
}

void eyes_block_with_st_chocolate_muffin_stuff::strongly_hit_response
	( block& the_block, const vec2_s32& coord )
{
	constexpr sprite_type the_spawnable_sprite_type = st_chocolate_muffin;
	active_level::horiz_level_block_data_2d.data_at(coord).type = bt_dud;
	
	vec2_s32 spawn_block_grid_coord = vec2_s32( coord.x, coord.y - 1 );
	vec2_f24p8 spawn_in_level_pos = vec2_f24p8
		( make_f24p8(spawn_block_grid_coord.x * num_pixels_per_block_row), 
		make_f24p8(spawn_block_grid_coord.y * num_pixels_per_block_col) );
	
	sprite_manager::spawn_a_sprite_basic( the_spawnable_sprite_type, 
		spawn_in_level_pos, bgofs_mirror[0].curr, false );
}


