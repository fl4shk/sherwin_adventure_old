#ifndef sprite_gfx_stuff_hpp
#define sprite_gfx_stuff_hpp

#include "../misc_types.hpp"
#include "../../gba_specific_stuff/attribute_defines.hpp"



// There are a total of 16 sprite palettes, each with 15 colors (and one
// transparent "color").
enum sprite_gfx_category
{
	// The player uses sprite palette slot 0
	sgc_player,
	
	// Powerup sprites use sprite palette slot 1
	sgc_powerup,
	
	// Block-like sprites use sprite palette slots 2 and 3
	sgc_block_like_0,
	sgc_block_like_1,
	
	// Enemy sprites use sprite palette slots 4, 5, and 6
	sgc_enemy_0,
	sgc_enemy_1,
	sgc_enemy_2,
	
	
	// This is the number of sprite graphics categories, automatically
	// updated by the compiler.  This might count as a simple hack since
	// I'm basically abusing the way enums work.
	sgc_count,
};


static constexpr u32 num_tiles_in_ss_8x8 = ( 8 * 8 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_16x16 = ( 16 * 16 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_32x32 = ( 32 * 32 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_64x64 = ( 64 * 64 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_16x8 = ( 16 * 8 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_32x8 = ( 32 * 8 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_32x16 = ( 32 * 16 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_64x32 = ( 64 * 32 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_8x16 = ( 8 * 16 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_8x32 = ( 8 * 32 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_16x32 = ( 16 * 32 ) / ( 8 * 8 );
static constexpr u32 num_tiles_in_ss_32x64 = ( 32 * 64 ) / ( 8 * 8 );


extern u32 next_free_sprite_vram_slot;
extern u32 sprite_gfx_category_first_vram_slot_list[sgc_count];


void upload_default_sprite_palettes(); //__attribute__((_iwram_code));


// These two functions rely on the fact that the sprite_gfx_category enum
// combines sprite tileset stuff and sprite palette stuff.  
void allocate_sprite_vram_and_copy_sprite_tiles( const u16* tiles, 
	u32 tiles_len, sprite_gfx_category the_gfx_category );
	//__attribute__((_iwram_code));

void upload_default_sprite_graphics(); //__attribute__((_iwram_code));



#endif		// sprite_gfx_stuff_hpp
