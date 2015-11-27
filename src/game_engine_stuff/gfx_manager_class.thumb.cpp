//#include "sprite_gfx_stuff.hpp"
#include "gfx_manager_class.hpp"


#include "../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../gba_specific_stuff/oam_entry_defines.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "misc_bitwise_funcs.hpp"
#include "block_stuff/block_stuff.hpp"

#include "debug_vars.hpp"

#include "sprite_stuff/sprite_class.hpp"

#include "../gfx/sherwin_gfx.h"
#include "../gfx/the_powerup_gfx.h"
//#include "../gfx/the_block_like_sprites_gfx.h"
#include "../gfx/the_door_gfx.h"
#include "../gfx/the_golem_enemy_gfx.h"

prev_curr_pair<bg_point> gfx_manager::bgofs_mirror[bgofs_mirror_size];

// Current component arrays, stored in EWRAM as fixed24p8's for speed and
// accuracy reasons.
fixed24p8 gfx_manager::bg_fade_curr_red_arr
	[bg_fade_curr_component_arr_size],
gfx_manager::bg_fade_curr_green_arr
	[bg_fade_curr_component_arr_size],
gfx_manager::bg_fade_curr_blue_arr
	[bg_fade_curr_component_arr_size];

fixed24p8 gfx_manager::obj_fade_curr_red_arr
	[obj_fade_curr_component_arr_size],
gfx_manager::obj_fade_curr_green_arr
	[obj_fade_curr_component_arr_size],
gfx_manager::obj_fade_curr_blue_arr
	[obj_fade_curr_component_arr_size];


// Fade out/in step amounts.
fixed24p8 gfx_manager::bg_fade_red_step_amount_arr
	[bg_fade_step_amount_arr_size],
gfx_manager::bg_fade_green_step_amount_arr
	[bg_fade_step_amount_arr_size],
gfx_manager::bg_fade_blue_step_amount_arr
	[bg_fade_step_amount_arr_size];

fixed24p8 gfx_manager::obj_fade_red_step_amount_arr
	[obj_fade_step_amount_arr_size],
gfx_manager::obj_fade_green_step_amount_arr
	[obj_fade_step_amount_arr_size],
gfx_manager::obj_fade_blue_step_amount_arr
	[obj_fade_step_amount_arr_size];


u16 gfx_manager::obj_pal_mirror[obj_pal_ram_size_in_u16];


void gfx_manager::update_block_graphics_in_vram
	( const unsigned short* the_tiles )
{
	// Note:  this function currently does multiple VRAM graphics updates
	// whenever more than one block_type use the same graphics_slot.
	for ( u32 i=0; i<block_type::bt_count; ++i )
	{
		u32 graphics_slot = get_graphics_slot_of_block_type 
			( (block_type)i );
		u32 metatile_number = get_metatile_number_of_block_type
			( (block_type)i );
		
		//dma3_cpy( &( bg_tile_vram[graphics_slot * 16]), 
		//	&( the_tiles 
		//		[metatile_number * 16 * 4] ),
		//	16 * 4, 0 );
		
		//memcpy32( &(bg_tile_vram[graphics_slot * 16]),
		//	&(the_tiles[metatile_number * 16 * 4]),
		//	16 * 4 / sizeof(u16) );
		
		memcpy32( &(bg_tile_vram_as_tiles[graphics_slot]),
			&((reinterpret_cast<const tile*>(the_tiles))
			[metatile_number * num_tiles_in_ss_16x16]),
			sizeof(tile) * num_tiles_in_ss_16x16 / sizeof (u32) );
	}
}



void gfx_manager::upload_default_sprite_palettes_to_obj_pal_ram()
{
	//memcpy32( obj_pal_ram, the_spritesPal, 
	//	the_spritesPalLen / sizeof(u32) );
	
	static constexpr u32 mul_val = 16;
	
	// The player's palettes
	memcpy32( &( obj_pal_ram[sgc_player * mul_val] ), sherwin_gfxPal, 
		sherwin_gfxPalLen / sizeof(u32) );
	
	// The powerups' palettes
	memcpy32( &( obj_pal_ram[sgc_powerup * mul_val] ), the_powerup_gfxPal,
		the_powerup_gfxPalLen / sizeof(u32) );
	
	//// The block-like sprites' palettes
	//memcpy32( &(obj_pal_ram[sgc_block_like_0 * mul_val]),
	//	the_block_like_sprites_gfxPal, the_block_like_sprites_gfxPalLen 
	//	/ sizeof(u32) );
	
	// The door sprites' palettes
	memcpy32( &(obj_pal_ram[sgc_door * mul_val]), the_door_gfxPal, 
		the_door_gfxPalLen / sizeof(u32) );
	
	// The golems and other enemys' palettes
	memcpy32( &(obj_pal_ram[sgc_enemy_0 * mul_val]),
		the_golem_enemy_gfxPal, the_golem_enemy_gfxPalLen / sizeof(u32) );
}


void gfx_manager::upload_default_sprite_palettes_to_obj_pal_mirror()
{
	//memcpy32( obj_pal_ram, the_spritesPal, 
	//	the_spritesPalLen / sizeof(u32) );
	
	static constexpr u32 mul_val = 16;
	
	// The player's palettes
	memcpy32( &( obj_pal_mirror[sgc_player * mul_val] ), sherwin_gfxPal, 
		sherwin_gfxPalLen / sizeof(u32) );
	
	// The powerups' palettes
	memcpy32( &( obj_pal_mirror[sgc_powerup * mul_val] ), 
		the_powerup_gfxPal, the_powerup_gfxPalLen / sizeof(u32) );
	
	// The door sprites' palettes
	memcpy32( &(obj_pal_mirror[sgc_door * mul_val]), the_door_gfxPal, 
		the_door_gfxPalLen / sizeof(u32) );
	
	// The golems and other enemys' palettes
	memcpy32( &(obj_pal_mirror[sgc_enemy_0 * mul_val]),
		the_golem_enemy_gfxPal, the_golem_enemy_gfxPalLen / sizeof(u32) );
}

void gfx_manager::copy_obj_pal_mirror_to_obj_pal_ram()
{
	memcpy32( obj_pal_ram, obj_pal_mirror, obj_pal_ram_size 
		/ sizeof(u32) );
}



void gfx_manager::upload_sprite_tiles_to_vram( sprite& the_sprite )
{
	// It gets tiring to have to type
	// sprite_stuff_array[the_sprite.the_sprite_type] so much.
	sprite_base_stuff* sbs_ptr = sprite_stuff_array
		[the_sprite.the_sprite_type];
	
	// This memfill32() call isn't strictly necessary, but it makes VRAM
	// look nicer in the VRAM viewer functionality of some emulators.
	memfill32( &(((tile*)obj_tile_vram)[the_sprite.get_vram_chunk_index()
		* num_tiles_in_ss_32x32]), 0, sizeof(tile) * num_tiles_in_ss_32x32
		/ sizeof(u32) );
	
	//memcpy32( &(((tile*)obj_tile_vram)[the_sprite.get_vram_chunk_index()
	//		* num_tiles_in_ss_32x32]),
	//	
	//	&(((tile*)temp_gfx_pointer_arr
	//		[sbs_ptr->get_gfx_category(the_sprite)])
	//		[sbs_ptr->get_curr_relative_tile_slot(the_sprite)]),
	//	
	//	//sizeof(tile) * num_tiles_in_ss_32x32 / sizeof(u32) );
	//	sizeof(tile) * sbs_ptr->get_num_active_gfx_tiles() / sizeof(u32) );
	
	
	memcpy32( &(((tile*)obj_tile_vram)[the_sprite.get_vram_chunk_index()
			* num_tiles_in_ss_32x32]),
		
		//&(((tile*)temp_gfx_pointer_arr
		//	[sbs_ptr->get_gfx_category(the_sprite)])
		//	[sbs_ptr->get_curr_relative_tile_slot(the_sprite)]),
		
		//&(sprite_base_stuff::the_tile_arr
		//	[sbs_ptr->get_curr_relative_tile_slot(the_sprite)]),
		&(sbs_ptr->get_tile_arr()
			[sbs_ptr->get_curr_relative_tile_slot(the_sprite)]),
		
		//sizeof(tile) * num_tiles_in_ss_32x32 / sizeof(u32) );
		sizeof(tile) * sbs_ptr->get_num_active_gfx_tiles() / sizeof(u32) );
}


