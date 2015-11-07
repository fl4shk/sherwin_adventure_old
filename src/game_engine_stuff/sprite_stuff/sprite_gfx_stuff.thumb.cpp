#include "sprite_gfx_stuff.hpp"


#include "../../gba_specific_stuff/bg_reg_stuff.hpp"
#include "../../gba_specific_stuff/oam_entry_defines.hpp"
#include "../../gba_specific_stuff/asm_funcs.hpp"
#include "../misc_bitwise_funcs.hpp"
#include "../block_stuff/block_stuff.hpp"

#include "../debug_vars.hpp"

#include "sprite_class.hpp"

#include "../../gfx/sherwin_gfx.h"
#include "../../gfx/the_powerup_gfx.h"
#include "../../gfx/the_block_like_sprites_gfx.h"
#include "../../gfx/the_golem_enemy_gfx.h"


//u32 sprite_gfx_manager::next_free_sprite_vram_slot;
//u32 sprite_gfx_manager::sprite_gfx_category_first_vram_slot_list
//	[sgc_count];

const u16* sprite_gfx_manager::temp_gfx_pointer_arr[] 
	= { sherwin_gfxTiles, the_powerup_gfxTiles,
	the_block_like_sprites_gfxTiles, the_block_like_sprites_gfxTiles,
	the_golem_enemy_gfxTiles, the_golem_enemy_gfxTiles,
	the_golem_enemy_gfxTiles };
const u32 sprite_gfx_manager::temp_gfx_pointer_arr_size 
	= sizeof(sprite_gfx_manager::temp_gfx_pointer_arr) 
	/ sizeof(const u16*);

void sprite_gfx_manager::upload_default_sprite_palettes()
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
	
	// The block-like sprites' palettes
	memcpy32( &(obj_pal_ram[sgc_block_like_0 * mul_val]),
		the_block_like_sprites_gfxPal, the_block_like_sprites_gfxPalLen 
		/ sizeof(u32) );
	
	// The golems and other enemys' palettes
	memcpy32( &(obj_pal_ram[sgc_enemy_0 * mul_val]),
		the_golem_enemy_gfxPal, the_golem_enemy_gfxPalLen / sizeof(u32) );
	
}

void sprite_gfx_manager::upload_sprite_tiles_to_vram
	( sprite& the_sprite )
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
	
	memcpy32( &(((tile*)obj_tile_vram)[the_sprite.get_vram_chunk_index()
			* num_tiles_in_ss_32x32]),
		
		&(((tile*)temp_gfx_pointer_arr
			[sbs_ptr->get_gfx_category(the_sprite)])
			[sbs_ptr->get_curr_relative_tile_slot(the_sprite)]),
		
		//sizeof(tile) * num_tiles_in_ss_32x32 / sizeof(u32) );
		sizeof(tile) * sbs_ptr->get_num_active_gfx_tiles() / sizeof(u32) );
}

//void sprite_gfx_manager::allocate_sprite_vram_and_copy_sprite_tiles_old
//	( const u16* tiles, u32 tiles_len, 
//	sprite_gfx_category the_gfx_category )
//{
//	// Copy the sprite graphics to VRAM
//	memcpy32( &( obj_tile_vram[next_free_sprite_vram_slot] ), 
//		tiles, tiles_len / sizeof(u32) );
//	sprite_gfx_category_first_vram_slot_list[the_gfx_category] 
//		= next_free_sprite_vram_slot;
//	
//	// Allocate VRAM for the sprite graphics
//	next_free_sprite_vram_slot += tiles_len / sizeof(u16);
//	//next_free_sprite_vram_slot += tiles_len / sizeof(tile);
//}
//
//
//void sprite_gfx_manager::upload_default_sprite_graphics_old()
//{
//	//memcpy32( obj_tile_vram, the_spritesTiles,
//	//	the_spritesTilesLen / sizeof(u32) );
//	
//	// Initialize the global sprite VRAM allocation variables.
//	next_free_sprite_vram_slot = 0;
//	memfill32( sprite_gfx_category_first_vram_slot_list, 0, sgc_count );
//	
//	
//	// Copy the player's graphics to VRAM
//	allocate_sprite_vram_and_copy_sprite_tiles_old( sherwin_gfxTiles,
//		sherwin_gfxTilesLen, sgc_player );
//	
//	// Copy the powerups' tiles to VRAM
//	allocate_sprite_vram_and_copy_sprite_tiles_old( the_powerup_gfxTiles,
//		the_powerup_gfxTilesLen, sgc_powerup );
//}



