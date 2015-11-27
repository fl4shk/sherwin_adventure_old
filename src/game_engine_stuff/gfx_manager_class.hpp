#ifndef gfx_manager_class_hpp
#define gfx_manager_class_hpp


#include "sprite_stuff/sprite_gfx_stuff.hpp"
#include "block_stuff/block_stuff.hpp"


class gfx_manager
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
	
	
	
	static const u32 bgofs_mirror_size = 4;
	
	static prev_curr_pair<bg_point> bgofs_mirror[bgofs_mirror_size]
		__attribute__((_iwram));
	
	// Current component arrays, stored in EWRAM as fixed24p8's for speed
	// and accuracy reasons.
	static constexpr u32 bg_fade_curr_component_arr_size 
		= num_colors_in_8_palettes;
	static fixed24p8 bg_fade_curr_red_arr
		[bg_fade_curr_component_arr_size] __attribute__((_ewram)),
	bg_fade_curr_green_arr
		[bg_fade_curr_component_arr_size] __attribute__((_ewram)),
	bg_fade_curr_blue_arr
		[bg_fade_curr_component_arr_size] __attribute__((_ewram));

	static constexpr u32 obj_fade_curr_component_arr_size 
		= num_colors_in_8_palettes;
	static fixed24p8 obj_fade_curr_red_arr
		[obj_fade_curr_component_arr_size] __attribute__((_ewram)),
	obj_fade_curr_green_arr
		[obj_fade_curr_component_arr_size] __attribute__((_ewram)),
	obj_fade_curr_blue_arr
		[obj_fade_curr_component_arr_size] __attribute__((_ewram));
	
	
	// Fade out/in step amounts.
	static constexpr u32 bg_fade_step_amount_arr_size 
		= num_colors_in_8_palettes;
	static fixed24p8 bg_fade_red_step_amount_arr
		[bg_fade_step_amount_arr_size] __attribute__((_ewram)),
	bg_fade_green_step_amount_arr
		[bg_fade_step_amount_arr_size] __attribute__((_ewram)),
	bg_fade_blue_step_amount_arr
		[bg_fade_step_amount_arr_size] __attribute__((_ewram));
	
	static constexpr u32 obj_fade_step_amount_arr_size 
		= num_colors_in_8_palettes;
	static fixed24p8 obj_fade_red_step_amount_arr
		[obj_fade_step_amount_arr_size] __attribute__((_ewram)),
	obj_fade_green_step_amount_arr
		[obj_fade_step_amount_arr_size] __attribute__((_ewram)),
	obj_fade_blue_step_amount_arr
		[obj_fade_step_amount_arr_size] __attribute__((_ewram));
	
	
	// Sprite VRAM allocation stuff
	
	// 64 max sprites on screen at once should be plenty.  Sprite
	// VRAM will be allocated in chunks of 32x32 pixels, or 8 tiles of 8x8
	// pixels.  It's unlikely that any sprites larger than 32x32 would be
	// needed.  Also, this is only the case for 4bpp graphics.
	static constexpr u32 max_num_32x32_metatiles = 64;
	
	// Sprite palette stuff
	
	static u16 obj_pal_mirror[obj_pal_ram_size_in_u16] 
		__attribute__((_ewram));
	
public:		// functions
	
	static inline void back_up_bgofs_mirror()
	{
		bgofs_mirror[0].back_up();
		bgofs_mirror[1].back_up();
		bgofs_mirror[2].back_up();
		bgofs_mirror[3].back_up();
	}

	static inline void copy_bgofs_mirror_to_registers()
	{
		//memcpy32( reg_bgofs, bgofs_mirror,
		//	( bgofs_mirror_size * sizeof(bg_point) ) / sizeof(u32) );
		
		reg_bgofs[0] = bgofs_mirror[0].curr;
		reg_bgofs[1] = bgofs_mirror[1].curr;
		reg_bgofs[2] = bgofs_mirror[2].curr;
		reg_bgofs[3] = bgofs_mirror[3].curr;
	}
	
	
	// Block graphics stuff
	//static inline u32 get_metatile_number_of_block_type
	//	( block_type the_block_type ) __attribute__((always_inline));
	
	
	static inline u32 get_metatile_number_of_block_type
		( block_type the_block_type )
	{
		//if ( the_block_type < 0 
		//	|| the_block_type >= block_type::bt_count )
		//{
		//	return block_stuff_array[bt_air]->get_metatile_number();
		//}
		//else
		//{
		//	return block_stuff_array[the_block_type]
		//		->get_metatile_number();
		//}
		
		return block_stuff_array[the_block_type]->get_metatile_number();
	}
	
	
	
	//static inline const u32 get_graphics_slot_of_block_type 
	//	( block_type the_block_type ) __attribute__((always_inline));
	
	
	static inline const u32 get_graphics_slot_of_block_type 
		( block_type the_block_type )
	{
		// This assumes that EVERY block uses 4 graphics slots in VRAM
		//return ( the_block_type * 4 );
		return block_stuff_array[the_block_type]
			->get_metatile_graphics_slot() * num_tiles_in_ss_16x16;
	}
	
	//static inline u32 get_palette_number_of_block_type
	//	( block_type the_block_type ) __attribute__((always_inline));
	
	
	static inline u32 get_palette_number_of_block_type
		( block_type the_block_type )
	{
		//if ( the_block_type < 0 
		//	|| the_block_type >= block_type::bt_count )
		//{
		//	return block_stuff_array[bt_air]->get_palette_number();
		//}
		//else
		//{
		//	return block_stuff_array[the_block_type]->get_palette_number();
		//}
		
		return block_stuff_array[the_block_type]->get_palette_number();
	}
	
	
	static void update_block_graphics_in_vram
		( const unsigned short* the_tiles ) __attribute__((_iwram_code));
	
	
	// Sprite graphics stuff
	
	
	static void upload_default_sprite_palettes_to_obj_pal_ram(); 
		//__attribute__((_iwram_code));
	
	static void upload_default_sprite_palettes_to_obj_pal_mirror();
		//__attribute__((_iwram_code));
	static void copy_obj_pal_mirror_to_obj_pal_ram();
		//__attribute__((_iwram_code));
	
	
	static void upload_sprite_tiles_to_vram( sprite& the_sprite )
		__attribute__((_iwram_code));
	
	
	
	
	
	
} __attribute__((_align4));




#endif		// gfx_manager_class_hpp
