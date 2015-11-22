#include "sprite_gfx_stuff.hpp"


#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/oam_entry_defines.hpp"
#include "../../gba_specific_stuff/asm_funcs.hpp"
#include "../misc_bitwise_funcs.hpp"
#include "../block_stuff/block_stuff.hpp"

#include "../debug_vars.hpp"

#include "sprite_class.hpp"

#include "../../gfx/sherwin_gfx.h"
#include "../../gfx/the_powerup_gfx.h"
//#include "../../gfx/the_block_like_sprites_gfx.h"
#include "../../gfx/the_door_gfx.h"
#include "../../gfx/the_golem_enemy_gfx.h"


u16 sprite_gfx_manager::obj_pal_mirror[obj_pal_ram_size_in_u16];


void sprite_gfx_manager::upload_default_sprite_palettes_to_obj_pal_ram()
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


void sprite_gfx_manager::upload_default_sprite_palettes_to_obj_pal_mirror()
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

void sprite_gfx_manager::copy_obj_pal_mirror_to_obj_pal_ram()
{
	memcpy32( obj_pal_ram, obj_pal_mirror, obj_pal_ram_size 
		/ sizeof(u32) );
}



void sprite_gfx_manager::upload_sprite_tiles_to_vram( sprite& the_sprite )
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





