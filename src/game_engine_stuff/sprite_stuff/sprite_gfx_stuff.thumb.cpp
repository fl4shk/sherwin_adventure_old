#include "sprite_gfx_stuff.hpp"


#include "../../gba_specific_stuff/bg_reg_stuff.hpp"
#include "../../gba_specific_stuff/oam_entry_defines.hpp"
#include "../../gba_specific_stuff/asm_funcs.hpp"
#include "../misc_bitwise_funcs.hpp"
#include "../block_stuff/block_stuff.hpp"

#include "../debug_vars.hpp"


#include "../../gfx/sherwin_gfx.h"
#include "../../gfx/the_powerup_gfx.h"


u32 next_free_sprite_vram_slot __attribute__((_iwram));
u32 sprite_gfx_category_first_vram_slot_list[sgc_count] 
	__attribute__((_iwram));

void upload_default_sprite_palettes()
{
	//memcpy32( obj_pal_ram, the_spritesPal, 
	//	the_spritesPalLen / sizeof(u32) );
	
	// The player's palettes
	memcpy32( &( obj_pal_ram[sgc_player * 16] ), sherwin_gfxPal, 
		sherwin_gfxPalLen / sizeof(u32) );
	
	// The powerups' palettes
	memcpy32( &( obj_pal_ram[sgc_powerup * 16] ), the_powerup_gfxPal,
		the_powerup_gfxPalLen / sizeof(u32) );
	
	// The block-like sprites' palettes
	//memcpy32( &( obj_pal_ram[sgc_block_like_0 * 16], the_
}


void allocate_sprite_vram_and_copy_sprite_tiles( const u16* tiles, 
	u32 tiles_len, sprite_gfx_category the_gfx_category )
{
	// Copy the sprite graphics to VRAM
	memcpy32( &( obj_tile_vram[next_free_sprite_vram_slot] ), 
		tiles, tiles_len / sizeof(u32) );
	sprite_gfx_category_first_vram_slot_list[the_gfx_category] 
		= next_free_sprite_vram_slot;
	
	// Allocate VRAM for the sprite graphics
	next_free_sprite_vram_slot += tiles_len / sizeof(u16);
	//next_free_sprite_vram_slot += tiles_len / sizeof(tile);
}




void upload_default_sprite_graphics()
{
	//memcpy32( obj_tile_vram, the_spritesTiles,
	//	the_spritesTilesLen / sizeof(u32) );
	
	// Initialize the global sprite VRAM allocation variables.
	next_free_sprite_vram_slot = 0;
	memfill32( sprite_gfx_category_first_vram_slot_list, 0, sgc_count );
	
	
	// Copy the player's graphics to VRAM
	allocate_sprite_vram_and_copy_sprite_tiles( sherwin_gfxTiles,
		sherwin_gfxTilesLen, sgc_player );
	
	// Copy the powerups' tiles to VRAM
	allocate_sprite_vram_and_copy_sprite_tiles( the_powerup_gfxTiles,
		the_powerup_gfxTilesLen, sgc_powerup );
	
	
	
}

