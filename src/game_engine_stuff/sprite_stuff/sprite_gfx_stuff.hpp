#ifndef sprite_gfx_stuff_hpp
#define sprite_gfx_stuff_hpp

#include "../misc_types.hpp"
#include "../../gba_specific_stuff/attribute_defines.hpp"
#include "../../gba_specific_stuff/bg_reg_stuff.hpp"

#include "../sa_stack_class.hpp"

class sprite;

// There are a total of 16 sprite palettes, each with 15 colors (and one
// transparent "color").
enum sprite_gfx_category
{
	// The player uses sprite palette slot 0
	sgc_player,
	
	// Powerup sprites use sprite palette slot 1
	sgc_powerup,
	
	//// Block-like sprites use sprite palette slots 2 and 3
	//sgc_block_like_0,
	//sgc_block_like_1,
	
	// Door sprites use sprite palette slot 2
	sgc_door,
	
	//// Enemy sprites use sprite palette slots 4, 5, and 6
	// Enemy sprites use sprite palette slots 3, 4, and 5
	sgc_enemy_0,
	sgc_enemy_1,
	sgc_enemy_2,
	
	
	// This is the number of sprite graphics categories, automatically
	// updated by the compiler.  This might count as a simple hack since
	// I'm basically abusing the way enums work.
	sgc_count,
};


class sprite_gfx_manager
{
public:		// variables and constants
	
	static constexpr u32 num_tiles_in_ss_8x8 = ( 8 * 8 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_16x16 = ( 16 * 16 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_32x32 = ( 32 * 32 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_64x64 = ( 64 * 64 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_16x8 = ( 16 * 8 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_32x8 = ( 32 * 8 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_32x16 = ( 32 * 16 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_64x32 = ( 64 * 32 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_8x16 = ( 8 * 16 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_8x32 = ( 8 * 32 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_16x32 = ( 16 * 32 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_32x64 = ( 32 * 64 ) 
		/ num_pixels_per_tile;
	
	
	//static u32 next_free_sprite_vram_slot __attribute__((_iwram));
	//static u32 sprite_gfx_category_first_vram_slot_list[sgc_count]
	//	__attribute__((_iwram));
	
	
	// Sprite VRAM allocation stuff
	
	// 64 max sprites on screen at once should be plenty.  Sprite
	// VRAM will be allocated in chunks of 32x32 pixels, or 8 tiles of 8x8
	// pixels.  It's unlikely that any sprites larger than 32x32 would be
	// needed.  Also, this is only the case for 4bpp graphics.
	static constexpr u32 max_num_32x32_metatiles = 64;
	
	
	//// These are temporary!
	//static const u16* temp_gfx_pointer_arr[];
	//static const u32 temp_gfx_pointer_arr_size;
	
public:		// functions
	
	static void upload_default_sprite_palettes(); 
		//__attribute__((_iwram_code));
	static void upload_sprite_tiles_to_vram( sprite& the_sprite )
		__attribute__((_iwram_code));
	
	//// These two functions rely on the fact that the sprite_gfx_category
	//// enum combines sprite tileset stuff and sprite palette stuff.  
	//static void allocate_sprite_vram_and_copy_sprite_tiles_old
	//	( const u16* tiles, u32 tiles_len, 
	//	sprite_gfx_category the_gfx_category );
	//	//__attribute__((_iwram_code));
	//
	//static void upload_default_sprite_graphics_old(); 
	//	//__attribute__((_iwram_code));
	
	
	
} __attribute__((_align4));


#endif		// sprite_gfx_stuff_hpp
