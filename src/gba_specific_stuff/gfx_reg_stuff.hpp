// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
// 
// Sherwin's Adventure is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef gfx_reg_stuff_hpp
#define gfx_reg_stuff_hpp

#include "../game_engine_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "../game_engine_stuff/vec2_class.hpp"
#include "../game_engine_stuff/prev_curr_pair_class.hpp"
#include "../game_engine_stuff/misc_bitwise_funcs.hpp"


/* ---- Some Helper Structs ---- */

// ---- Character/Tile Stuffs ----
// tile 8x8@4bpp:  32 bytes; 8 ints
struct tile
{
	static const u32 arrsize = 8;
	u32 data[arrsize];
};
typedef tile tile4;

// d-tile:  double-sized tile (8bpp)
struct tile8
{
	static const u32 arrsize = 16;
	u32 data[arrsize];
};


static const u32 charblock_size = 0x200;
typedef tile charblock[charblock_size];

static const u32 charblock8_size = 0x100;
typedef tile8 charblock8[charblock8_size];

#define tile_ram		( (charblock*)(mem_vram) )
#define tile8_ram		( (charblock8*)(mem_vram) )


#define bg_tile_vram ( (vu16*)(tile_ram[0]) )
#define bg_tile_vram_as_tiles ( (volatile tile*)(tile_ram[0]) )

// Do note that obj_tile_vram consists of TWO charblocks, or 1024 4bpp
// tiles of 8x8 pixels (512 8bpp tiles of 8x8 pixels).
#define obj_tile_vram ( (vu16*)(tile_ram[4]) )
#define obj_tile_vram_as_tiles ( (volatile tile*)(tile_ram[4]) )

// ---- End of Character/Tile Stuffs ----


// ---- Screen-Entry Stuffs ----

// Screen entry conceptual typedef
typedef u16 scr_entry;

// Regular map offsets
//struct bg_point
//{
//	//s16 x, y;
//	u16 x, y;
//} __attribute__((aligned(4)));
typedef vec2_s16 bg_point;


// Screenblock struct.  There are 32 (0x20) tiles per row, and 32 (0x20)
// tiles per column.
static constexpr u32 screenblock_size = 0x400;
static constexpr u32 screenblock_xsize = 0x20, screenblock_ysize = 0x20;
static constexpr vec2_u32 screenblock_size_2d 
	= { screenblock_xsize, screenblock_ysize };
typedef scr_entry screenblock[screenblock_size];


// Screen-entry mapping: se_ram[y][x] is SBB y, entry x
#define se_ram ((screenblock*)mem_vram)



// -- Defines for Screen Entries --

// Tile Index of the SE
#define se_id( n ) ( ( n ) & 0x3ff )
#define se_id_mask ( (u16)(0x03ff) )

// SE Flipping
#define se_no_flip ( 0x0 << 0xa )
#define se_hflip ( 0x1 << 0xa )
#define se_vflip ( 0x2 << 0xa )
#define se_flip_mask ( (u16)(0x0c00) )

// SE Palette Bank for 16-color mode
#define se_palbank( n ) ( ( ( n ) & 0xf ) << 0xc )
#define se_palbank_mask ( (u16)(0xf000) )


// -- End of Defines for Screen Entries --

// ---- End of Screen-Entry Stuffs ----

/* ---- End of Some Helper Structs ---- */



/* ---- Palette RAM Stuffs ---- */
#define bg_pal_ram ((vu16*)(mem_bg_pal))
#define obj_pal_ram ((vu16*)(mem_obj_pal))

static const u32 pal_ram_size = 0x200;
static const u32 bg_pal_ram_size = 0x200;
static const u32 obj_pal_ram_size = 0x200;

static const u32 pal_ram_size_in_u16 = pal_ram_size / sizeof(u16);
static const u32 bg_pal_ram_size_in_u16 = bg_pal_ram_size / sizeof(u16);
static const u32 obj_pal_ram_size_in_u16 = obj_pal_ram_size / sizeof(u16);

static const u32 num_colors_in_8_palettes = pal_ram_size_in_u16;
static const u32 num_colors_per_palette = 16;

/* ---- End of Palette RAM Stuffs ---- */



/* ---- Graphics-related Registers ---- */

// Display Register Address Defines
#define reg_dispcnt *((vu16*)(mem_io + 0x0000))
#define reg_dispstat *((vu16*)(mem_io + 0x0004))
#define reg_vcount *((vu16*)(mem_io + 0x0006))

// LCD I/O BG Control Registers
#define reg_bgcnt ((vu16*)(mem_io + 0x0008))
#define reg_bg0cnt ( reg_bgcnt[0] )
#define reg_bg1cnt ( reg_bgcnt[1] )
#define reg_bg2cnt ( reg_bgcnt[2] )
#define reg_bg3cnt ( reg_bgcnt[3] )

// LCD I/O BG Scrolling Registers
#define reg_bgofs ((bg_point*)(mem_io + 0x0010))

#define reg_bghofs_n(n) *((vu16*)(mem_io + 0x0010 + 0x04 * n))
#define reg_bgvofs_n(n) *((vu16*)(mem_io + 0x0012 + 0x04 * n))


// Alpha Blending Registers
#define reg_bldcnt *((vu16*)(mem_io + 0x0050))
#define reg_bldalpha *((vu16*)(mem_io + 0x0052))
#define reg_bldy *((vu16*)(mem_io + 0x0054))


/* ---- End of Graphics-related Registers ---- */


// The width and height of the screen, in pixels
//#define screen_width 240
//#define screen_height 160
static const u32 screen_width = 240;
static const u32 screen_height = 160;

static const vec2_u32 screen_size_2d = { screen_width, screen_height };

// The width and height of the screen, in tiles
static const u32 screen_width_in_tiles = 30;
static const u32 screen_height_in_tiles = 20;

static const vec2_u32 screen_size_in_tiles_2d = { screen_width_in_tiles, 
	screen_height_in_tiles };

// The width and height of the screen, in blocks
static const u32 screen_width_in_blocks = 15;
static const u32 screen_height_in_blocks = 10;

static const vec2_u32 screen_size_in_blocks_2d = { screen_width_in_blocks, 
	screen_height_in_blocks };

static const u32 num_pixels_per_tile_row = 8;
static const u32 num_pixels_per_tile_col = 8;
static const u32 num_pixels_per_tile_row_or_column = 8;
static const u32 num_pixels_per_tile = num_pixels_per_tile_row 
	* num_pixels_per_tile_col;

static const u32 num_pixels_per_block_row = 16;
static const u32 num_pixels_per_block_col = 16;
static const u32 num_pixels_per_block_row_or_column = 16;


/* ---- Display Register Value Defines ---- */
//  Bitwise OR these values together

// Defines for reg_dispcnt
//   Video Mode (Select ONLY ONE)
#define dcnt_mode0 0x0000
#define dcnt_mode1 0x0001
#define dcnt_mode2 0x0002
#define dcnt_mode3 0x0003
#define dcnt_mode4 0x0004
#define dcnt_mode5 0x0005
#define dcnt_mode_mask ( (u16)(0x0007) )

//   BG Mode 4 and 5 Page Flipping
#define dcnt_page_0 ( 0x0000 << 0x4 )
#define dcnt_page_1 ( 0x0001 << 0x4 )
#define dcnt_page_mask ( (u16)(0x0010) )

//   OBJ Character VRAM Mapping (Select ONLY ONE)
#define dcnt_obj_2d ( 0x0000 << 0x6 )
#define dcnt_obj_1d ( 0x0001 << 0x6 )
#define dcnt_obj_dim_mask ( (u16)(0x0040) )

//   Forced Blank (Select ONLY ONE)
#define dcnt_blank_off ( 0x0000 << 0x7 )
#define dcnt_blank_on ( 0x0001 << 0x7 )
#define dcnt_blank_mask ( (u16)(0x0080) )

//   Screen Display BG0 (Select ONLY ONE)
#define dcnt_bg0_off ( 0x0000 << 0x8 )
#define dcnt_bg0_on ( 0x0001 << 0x8 )
#define dcnt_bg0_onoff_mask ( (u16)(0x0100) )

//   Screen Display BG1 (Select ONLY ONE)
#define dcnt_bg1_off ( 0x0000 << 0x9 )
#define dcnt_bg1_on ( 0x0001 << 0x9 )
#define dcnt_bg1_onoff_mask ( (u16)(0x0200) )

//   Screen Display BG2 (Select ONLY ONE)
#define dcnt_bg2_off ( 0x0000 << 0xa )
#define dcnt_bg2_on ( 0x0001 << 0xa )
#define dcnt_bg2_onoff_mask ( (u16)(0x0400) )

//   Screen Display BG3 (Select ONLY ONE)
#define dcnt_bg3_off ( 0x0000 << 0xb )
#define dcnt_bg3_on ( 0x0001 << 0xb )
#define dcnt_bg3_onoff_mask ( (u16)(0x0800) )

//   Screen Display OBJ (Select ONLY ONE)
#define dcnt_obj_off ( 0x0000 << 0xc )
#define dcnt_obj_on ( 0x0001 << 0xc )
#define dcnt_obj_onoff_mask ( (u16)(0x1000) )

//   Window 0 Display (Select ONLY ONE)
#define dcnt_win0_off ( 0x0000 << 0xd )
#define dcnt_win0_on ( 0x0001 << 0xd )
#define dcnt_win0_onoff_mask ( (u16)(0x2000) )

//   Window 1 Display (Select ONLY ONE)
#define dcnt_win1_off ( 0x0000 << 0xe )
#define dcnt_win1_on ( 0x0001 << 0xe )
#define dcnt_win1_onoff_mask ( (u16)(0x4000) )

//   OBJ Window Display (Select ONLY ONE)
#define dcnt_winobj_off ( 0x0000 << 0xf )
#define dcnt_winobj_on ( 0x0001 << 0xf )
#define dcnt_winobj_onoff_mask ( (u16)(0x8000) )

/* ---- End of Display Register Value Defines ---- */



/* ---- Defines for reg_dispstat ---- */

//   VBlank status (Read Only)
#define dstat_in_vbl ( 0x0001 << 0x0 )

//   HBlank status (Read Only)
#define dstat_in_hbl ( 0x0001 << 0x1 )

//   VCount trigger status (Read Only ?)
#define dstat_in_vct ( 0x0001 << 0x2 )

//   VBlank IRQ Enable
#define dstat_vbl_irq ( 0x0001 << 0x3 )

//   HBlank IRQ Enable
#define dstat_hbl_irq ( 0x0001 << 0x4 )

//   VCount IRQ Enable
#define dstat_vct_irq ( 0x0001 << 0x5 )

//   VCount trigger value
#define dstat_vct(x) ( x << 0x8 )

/* ---- End of Defines for reg_dispstat ---- */



/* ---- Defines for reg_bgXcnt (X = 0, 1, 2, or 3) ---- */

// BG Priority.  Higher Priority BGs are drawn FIRST.  If there are any
// BGs with the same priority, then BG0 has the highest priority, and BG3
// has the lowest.
#define bgcnt_prio( n ) ( n & 0x1 )
#define bgcnt_prio_mask ( (u16)(0x0001) )

// Character Base Block (Virtually Worthless)
#define bgcnt_cbb( n ) ( ( n & 0x3 ) << 0x2 )
#define bgcnt_cbb_mask ( (u16)(0x000c) )

// Mosaic Flag (I don't think I'll use it)
#define bgcnt_mosaic_off ( 0x0 << 0x6 )
#define bgcnt_mosaic_on ( 0x1 << 0x6 )
#define bgcnt_mosaic_mask ( (u16)(0x0040) )

// Whether the BG is 4bpp or 8bpp (I'll probably be using 4bpp exclusively)
#define bgcnt_4bpp ( 0x0 << 0x7 )
#define bgcnt_8bpp ( 0x1 << 0x7 )
#define bgcnt_bpp_mask ( (u16)(0x0080) )

//Screen Base Block
#define bgcnt_sbb( n ) ( ( n & 0x1f ) << 0x8 )
#define bgcnt_sbb_mask ( (u16)(0x1f00) )

// Affine Wrapping
#define bgcnt_wrap_off ( 0x0 << 0xd )
#define bgcnt_wrap_on ( 0x1 << 0xd )
#define bgcnt_wrap_mask ( (u16)(0x2000) )

// Regular Background Size in Tiles
#define bgcnt_reg_32x32 ( 0x0 << 0xe )
#define bgcnt_reg_64x32 ( 0x1 << 0xe )
#define bgcnt_reg_32x64 ( 0x2 << 0xe )
#define bgcnt_reg_64x64 ( 0x3 << 0xe )
#define bgcnt_reg_mask ( (u16)(0xc000) )

// Affine Background Size in Tiles
#define bgcnt_aff_16x16 ( 0x0 << 0xe )
#define bgcnt_aff_32x32 ( 0x1 << 0xe )
#define bgcnt_aff_64x64 ( 0x2 << 0xe )
#define bgcnt_aff_128x128 ( 0x3 << 0xe )
#define bgcnt_aff_mask ( (u16)(0xc000) )

/* ---- End of Defines for reg_bgXcnt ---- */


/* ---- Defines for reg_bldcnt ---- */

// The (A) top layers
#define bldcnt_top_bg0 ( 0x0 << 0x0 )
#define bldcnt_top_bg1 ( 0x1 << 0x0 )
#define bldcnt_top_bg2 ( 0x2 << 0x0 )
#define bldcnt_top_bg3 ( 0x3 << 0x0 )
#define bldcnt_top_obj ( 0x4 << 0x0 )
#define bldcnt_top_backdrop ( 0x5 << 0x0 )
#define bldcnt_top_mask ( (u16)(0x001f) )

// The blending mode
#define bldcnt_bld_off ( 0x0 << 0x6 )
#define bldcnt_bld_normal ( 0x1 << 0x6 )
#define bldcnt_bld_white ( 0x2 << 0x6 )
#define bldcnt_bld_black ( 0x3 << 0x6 )
#define bldcnt_bld_mask ( (u16)(0x00c0) )

// The (B) bottom layers
#define bldcnt_bot_bg0 ( 0x0 << 0x8 )
#define bldcnt_bot_bg1 ( 0x1 << 0x8 )
#define bldcnt_bot_bg2 ( 0x2 << 0x8 )
#define bldcnt_bot_bg3 ( 0x3 << 0x8 )
#define bldcnt_bot_obj ( 0x4 << 0x8 )
#define bldcnt_bot_backdrop ( 0x5 << 0x8 )
#define bldcnt_bot_mask ( (u16)(0x1f00) )

/* ---- End of Defines for reg_bldcnt ---- */


/* ---- Defines for reg_bldalpha ---- */

// Top blend weight.  Only used for normal blending.
#define bldalpha_top( n ) ( n & 0x1f )

// Bot blend weight.  Only used for normal blending.
#define bldalpha_bot( n ) ( ( n & 0x1f ) << 0x8 )

/* ---- End of Defines for reg_bldalpha ---- */


/* ---- Defines for reg_bldalpha ---- */

// Top blend weight.  Only used for normal blending.
#define bldy( n ) ( n & 0x1f )

/* ---- End of Defines for reg_bldalpha ---- */



/* ---- Some misc. inline functions ---- */

#define rgb15_red_shift ( 0x0 )
#define rgb15_green_shift ( 0x5 )
#define rgb15_blue_shift ( 0xa )

#define rgb15_red_mask ( (u16)0x001f )
#define rgb15_green_mask ( (u16)0x03e0 )
#define rgb15_blue_mask ( (u16)0x7c00 )

#define rgb15_component_max_val ( 0x1f )

#define rgb15_num_components ( 3 )




inline u16 make_rgb15( u32 red, u32 green, u32 blue )
{
	return ( ( ( red & rgb15_component_max_val ) << rgb15_red_shift ) 
		| ( ( green & rgb15_component_max_val ) << rgb15_green_shift ) 
		| ( ( blue & rgb15_component_max_val ) << rgb15_blue_shift ) );
}

inline u32 rgb15_get_red_component( u32 the_rgb15_val )
{
	return get_bits( the_rgb15_val, rgb15_red_mask, rgb15_red_shift );
}
inline u32 rgb15_get_green_component( u32 the_rgb15_val )
{
	return get_bits( the_rgb15_val, rgb15_green_mask, rgb15_green_shift );
}
inline u32 rgb15_get_blue_component( u32 the_rgb15_val )
{
	return get_bits( the_rgb15_val, rgb15_blue_mask, rgb15_blue_shift );
}

inline void clamped_rgb15_component_add( s32& component, s32 amount_to_add, 
	s32 component_max_value=rgb15_component_max_val )
{
	component += amount_to_add;
	
	if ( component > component_max_value  )
	{
		component = component_max_value;
	}
	else if ( component < 0 )
	{
		component = 0;
	}
}

inline void clamped_rgb15_f24p8_component_add( fixed24p8& component,
	const fixed24p8& amount_to_add, const fixed24p8& target_value )
{
	component += amount_to_add;
	
	if ( amount_to_add > (fixed24p8){0} && component > target_value )
	{
		component = target_value;
	}
	else if ( amount_to_add < (fixed24p8){0} && component < target_value )
	{
		component = target_value;
	}
}





inline void m3_plot( u32 x, u32 y, u32 color )
{
	( (vu16*)(mem_vram) )[y * screen_width + x] = color;
}
inline void m4_plot_basic( u32 x, u32 y, u16 two_color_ids, u32 page = 0 )
{
	// Plot to Page 0
	if ( page == 0 )
	{
		( (vu16*)(mem_vram_page_0) )[y * screen_width + x] 
			= two_color_ids;
	}
	
	// Plot to Page 1
	else
	{
		( (vu16*)(mem_vram_page_1) )[y * screen_width + x] 
			= two_color_ids;
	}
}


// The reason that color_id is passed in as a 32-bit variable is speed.
inline void m4_plot( s32 x, s32 y, u32 color_id, u32 page )
{
	
	if ( !( x >= 0 && x <= (s32)screen_width 
		&& y >= 0 && y <= (s32)screen_height ) )
	{
		return;
	}
	
	vu16* vram_area;
	u16 two_color_ids;
	
	u8 color_id_8bit = color_id & 0xff;
	
	
	// Plot to Page 0
	if ( page == 0 )
	{
		vram_area = (vu16*)(mem_vram_page_0);
	}
	
	// Plot to Page 1
	else
	{
		vram_area = (vu16*)(mem_vram_page_1);
	}
	
	two_color_ids = vram_area[(y * screen_width + x) / sizeof(vu16)];
	
	
	// If x is odd, change the high byte
	if ( x & 1 )
	{
		// Clear the high byte
		two_color_ids &= 0x00ff;
		
		// Set the high byte to the new color ID
		two_color_ids |= ( color_id_8bit << 8 );
	}
	
	// If x is even, change the low byte
	else
	{
		// Clear the low byte
		two_color_ids &= 0xff00;
		
		// Set the low byte to the new color ID
		two_color_ids |= color_id_8bit;
	}
	
	vram_area[(y * screen_width + x) / sizeof(vu16)] = two_color_ids;
}







#endif		// gfx_reg_stuff_hpp
