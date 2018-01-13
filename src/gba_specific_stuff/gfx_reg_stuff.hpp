// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andrew Clark (FL4SHK).
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


#ifndef gba_specific_stuff__slash__gfx_reg_stuff_hpp
#define gba_specific_stuff__slash__gfx_reg_stuff_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "memory_map.hpp"
#include "../general_utility_stuff/vec2_class.hpp"
#include "../general_utility_stuff/prev_curr_pair_class.hpp"
#include "../general_utility_stuff/misc_bitwise_funcs.hpp"


namespace sherwin_adventure
{

namespace gba
{

/* ---- Some Helper Structs ---- */

// ---- Character/Tile Stuffs ----
// Tile 8x8@4bpp:  32 bytes; 8 ints
struct Tile
{
	static const u32 arrsize = 8;
	u32 data[arrsize];
};
typedef Tile Tile4;

// d-Tile:  double-sized Tile (8bpp)
struct Tile8
{
	static const u32 arrsize = 16;
	u32 data[arrsize];
};


static const u32 charblock_size = 0x200;
typedef Tile Charblock[charblock_size];

static const u32 charblock8_size = 0x100;
typedef Tile8 Charblock8[charblock8_size];

#define TILE_RAM		((Charblock*)(MEM_VRAM))
#define TILE8_RAM		((Charblock8*)(MEM_VRAM))


#define BG_TILE_VRAM ((vu16*)(TILE_RAM[0]))
#define BG_TILE_VRAM_AS_TILES ((volatile Tile*)(TILE_RAM[0]))

// Do note That OBJ_TILE_VRAM consists of TWO charblocks, or 1024 4bpp
// tiles of 8x8 pixels (512 8bpp tiles of 8x8 pixels).
#define OBJ_TILE_VRAM ((vu16*)(TILE_RAM[4]))
#define OBJ_TILE_VRAM_AS_TILES ((volatile Tile*)(TILE_RAM[4]))

// ---- End of Character/Tile Stuffs ----


// ---- Screen-Entry Stuffs ----

// Screen entry conceptual typedef
typedef u16 ScrEntry;

// Regular map offsets
//struct BgPoint
//{
//	//s16 x, y;
//	u16 x, y;
//} [[aligned(4)]];
//typedef Vec2S16 BgPoint;
typedef Vec2F24p8 BgPoint;


// Screenblock struct.  There are 32 (0x20) tiles per row, and 32 (0x20)
// tiles per column.
static constexpr u32 screenblock_size = 0x400;
static constexpr u32 screenblock_xsize = 0x20, screenblock_ysize = 0x20;
static constexpr Vec2U32 screenblock_size_2d(screenblock_xsize, 
	screenblock_ysize);
typedef ScrEntry Screenblock[screenblock_size];


// Screen-entry mapping: SE_RAM[y][x] Is SBB y, entry x
#define SE_RAM ((Screenblock*)MEM_VRAM)



// -- Defines for Screen Entries --

// Tile Index of the SE
#define SE_ID(n) ((n) & 0x3ff)
#define SE_ID_MASK ((u16)(0x03ff))

// SE Flipping
#define SE_NO_FLIP (0x0 << 0xa)
#define SE_HFLIP (0x1 << 0xa)
#define SE_VFLIP (0x2 << 0xa)
#define SE_FLIP_MASK ((u16)(0x0c00))

// SE Palette Bank for 16-color mode
#define SE_PALBANK(n) (((n) & 0xf) << 0xc)
#define SE_PALBANK_MASK ((u16)(0xf000))


// -- End of Defines for Screen Entries --

// ---- End of Screen-Entry Stuffs ----

/* ---- End of Some Helper Structs ---- */



/* ---- Palette RAM Stuffs ---- */
#define BG_PAL_RAM ((vu16*)(MEM_BG_PAL))
#define OBJ_PAL_RAM ((vu16*)(MEM_OBJ_PAL))

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
#define REG_DISPCNT *((vu16*)(MEM_IO + 0x0000))
#define REG_DISPSTAT *((vu16*)(MEM_IO + 0x0004))
#define REG_VCOUNT *((vu16*)(MEM_IO + 0x0006))

// LCD I/O BG Control Registers (W)
#define REG_BGCNT_ARR ((vu16*)(MEM_IO + 0x0008))
#define REG_BG0CNT (REG_BGCNT_ARR[0])
#define REG_BG1CNT (REG_BGCNT_ARR[1])
#define REG_BG2CNT (REG_BGCNT_ARR[2])
#define REG_BG3CNT (REG_BGCNT_ARR[3])

// LCD I/O BG Scrolling Registers
//#define REG_BGOFS ((BgPoint*)(MEM_IO + 0x0010))
// Pretty cool how I Can use my Vec2S16 class for this
#define REG_BGOFS ((Vec2S16*)(MEM_IO + 0x0010))

#define REG_BGHOFS_N(n) *((vu16*)(MEM_IO + 0x0010 + 0x04 * n))
#define REG_BGVOFS_N(n) *((vu16*)(MEM_IO + 0x0012 + 0x04 * n))


// Alpha Blending Registers
#define REG_BLDCNT *((vu16*)(MEM_IO + 0x0050))
#define REG_BLDALPHA *((vu16*)(MEM_IO + 0x0052))
#define REG_BLDY *((vu16*)(MEM_IO + 0x0054))


/* ---- End of Graphics-related Registers ---- */


// The width and height of the screen, in pixels
//#define SCREEN_WIDTH 240
//#define SCREEN_HEIGHT 160
static const u32 SCREEN_WIDTH = 240;
static const u32 SCREEN_HEIGHT = 160;

//static const Vec2U32 screen_size_2d = { SCREEN_WIDTH, SCREEN_HEIGHT };
static const Vec2U32 screen_size_2d(SCREEN_WIDTH, SCREEN_HEIGHT);

// The width and height of the screen, in tiles
static const u32 screen_width_in_tiles = 30;
static const u32 screen_height_in_tiles = 20;

//static const Vec2U32 screen_size_in_tiles_2d = { screen_width_in_tiles, 
//	screen_height_in_tiles };
static const Vec2U32 screen_size_in_tiles_2d(screen_width_in_tiles, 
	screen_height_in_tiles);

// The width and height of the screen, in blocks
static const u32 screen_width_in_blocks = 15;
static const u32 screen_height_in_blocks = 10;

//static const Vec2U32 screen_size_in_blocks_2d = { screen_width_in_blocks, 
//	screen_height_in_blocks };
static const Vec2U32 screen_size_in_blocks_2d(screen_width_in_blocks, 
	screen_height_in_blocks);

static const u32 num_pixels_per_tile_row = 8;
static const u32 num_pixels_per_tile_col = 8;
static const u32 num_pixels_per_tile_row_or_column = 8;
static const u32 num_pixels_per_tile = num_pixels_per_tile_row 
	* num_pixels_per_tile_col;

static const u32 num_pixels_per_block_row = 16;
static const u32 num_pixels_per_block_col = 16;
static const u32 num_pixels_per_block_dim = 16;

template<typename Type>
inline const Type conv_blk_crd_to_pix_crd(Type to_convert)
{
	return to_convert * static_cast<Type>(num_pixels_per_block_dim);
}

template<typename Type>
inline const Type conv_pix_crd_to_blk_local_crd(Type to_convert)
{
	return to_convert % static_cast<Type>(num_pixels_per_block_dim);
}

template<typename Type>
inline const Type conv_pix_crd_to_blk_crd(Type to_convert)
{
	return to_convert / static_cast<Type>(num_pixels_per_block_dim);
}

template<typename Type>
inline const Type conv_slp_height_val_to_offset(Type tallest_height_val)
{
	return static_cast<Type>(num_pixels_per_block_dim) 
		- tallest_height_val;
}

/* ---- Display Register Value Defines ---- */
//  Bitwise OR these values together

// Defines for REG_DISPCNT
//   Video Mode (Select ONLY ONE)
#define DCNT_MODE0 0x0000
#define DCNT_MODE1 0x0001
#define DCNT_MODE2 0x0002
#define DCNT_MODE3 0x0003
#define DCNT_MODE4 0x0004
#define DCNT_MODE5 0x0005
#define DCNT_MODE_MASK ((u16)(0x0007))

//   BG Mode 4 and 5 Page Flipping
#define DCNT_PAGE_0 (0x0000 << 0x4)
#define DCNT_PAGE_1 (0x0001 << 0x4)
#define DCNT_PAGE_MASK ((u16)(0x0010))

//   OBJ Character VRAM Mapping (Select ONLY ONE)
#define DCNT_OBJ_2D (0x0000 << 0x6)
#define DCNT_OBJ_1D (0x0001 << 0x6)
#define DCNT_OBJ_DIM_MASK ((u16)(0x0040))

//   forced Blank (Select ONLY ONE)
#define DCNT_BLANK_OFF (0x0000 << 0x7)
#define DCNT_BLANK_ON (0x0001 << 0x7)
#define DCNT_BLANK_MASK ((u16)(0x0080))

//   Screen Display BG0 (Select ONLY ONE)
#define DCNT_BG0_OFF (0x0000 << 0x8)
#define DCNT_BG0_ON (0x0001 << 0x8)
#define DCNT_BG0_ONOFF_MASK ((u16)(0x0100))

//   Screen Display BG1 (Select ONLY ONE)
#define DCNT_BG1_OFF (0x0000 << 0x9)
#define DCNT_BG1_ON (0x0001 << 0x9)
#define DCNT_BG1_ONOFF_MASK ((u16)(0x0200))

//   Screen Display BG2 (Select ONLY ONE)
#define DCNT_BG2_OFF (0x0000 << 0xa)
#define DCNT_BG2_ON (0x0001 << 0xa)
#define DCNT_BG2_ONOFF_MASK ((u16)(0x0400))

//   Screen Display BG3 (Select ONLY ONE)
#define DCNT_BG3_OFF (0x0000 << 0xb)
#define DCNT_BG3_ON (0x0001 << 0xb)
#define DCNT_BG3_ONOFF_MASK ((u16)(0x0800))

//   Screen Display OBJ (Select ONLY ONE)
#define DCNT_OBJ_OFF (0x0000 << 0xc)
#define DCNT_OBJ_ON (0x0001 << 0xc)
#define DCNT_OBJ_ONOFF_MASK ((u16)(0x1000))

//   Window 0 Display (Select ONLY ONE)
#define DCNT_WIN0_OFF (0x0000 << 0xd)
#define DCNT_WIN0_ON (0x0001 << 0xd)
#define DCNT_WIN0_ONOFF_MASK ((u16)(0x2000))

//   Window 1 Display (Select ONLY ONE)
#define DCNT_WIN1_OFF (0x0000 << 0xe)
#define DCNT_WIN1_ON (0x0001 << 0xe)
#define DCNT_WIN1_ONOFF_MASK ((u16)(0x4000))

//   OBJ Window Display (Select ONLY ONE)
#define DCNT_WINOBJ_OFF (0x0000 << 0xf)
#define DCNT_WINOBJ_ON (0x0001 << 0xf)
#define DCNT_WINOBJ_ONOFF_MASK ((u16)(0x8000))

/* ---- End of Display Register Value Defines ---- */



/* ---- Defines for REG_DISPSTAT ---- */

//   VBlank status (Read Only)
#define DSTAT_IN_VBL (0x0001 << 0x0)

//   HBlank status (Read Only)
#define DSTAT_IN_HBL (0x0001 << 0x1)

//   VCount trigger status (Read Only ?)
#define DSTAT_IN_VCT (0x0001 << 0x2)

//   VBlank IRQ Enable
#define DSTAT_VBL_IRQ (0x0001 << 0x3)

//   HBlank IRQ Enable
#define DSTAT_HBL_IRQ (0x0001 << 0x4)

//   VCount IRQ Enable
#define DSTAT_VCT_IRQ (0x0001 << 0x5)

//   VCount trigger value
#define DSTAT_VCT(x) (x << 0x8)

/* ---- End of Defines for REG_DISPSTAT ---- */



/* ---- Defines for reg_bgXcnt (X = 0, 1, 2, or 3) ---- */

// BG Priority.  Higher Priority BGs are drawn FIRST.  If there are any
// BGs with the same priority, then BG0 has the highest priority, and BG3
// has the lowest.
#define BGCNT_PRIO(n) (n & 0x1)
#define BGCNT_PRIO_MASK ((u16)(0x0001))

// Character Base Block (Virtually Worthless)
#define BGCNT_CBB(n) ((n & 0x3) << 0x2)
#define BGCNT_CBB_MASK ((u16)(0x000c))

// Mosaic Flag (I don't think I'll use it)
#define BGCNT_MOSAIC_OFF (0x0 << 0x6)
#define BGCNT_MOSAIC_ON (0x1 << 0x6)
#define BGCNT_MOSAIC_MASK ((u16)(0x0040))

// Whether the BG Is 4bpp or 8bpp (I'll probably be using 4bpp exclusively)
#define BGCNT_4BPP (0x0 << 0x7)
#define BGCNT_8BPP (0x1 << 0x7)
#define BGCNT_BPP_MASK ((u16)(0x0080))

// Screen Base Block
#define BGCNT_SBB(n) ((n & 0x1f) << 0x8)
#define BGCNT_SBB_MASK ((u16)(0x1f00))

// Affine Wrapping
#define BGCNT_WRAP_OFF (0x0 << 0xd)
#define BGCNT_WRAP_ON (0x1 << 0xd)
#define BGCNT_WRAP_MASK ((u16)(0x2000))

// Regular Background Size in Tiles
#define BGCNT_REG_32X32 (0x0 << 0xe)
#define BGCNT_REG_64X32 (0x1 << 0xe)
#define BGCNT_REG_32X64 (0x2 << 0xe)
#define BGCNT_REG_64X64 (0x3 << 0xe)
#define BGCNT_REG_MASK ((u16)(0xc000))

// Affine Background Size in Tiles
#define BGCNT_AFF_16X16 (0x0 << 0xe)
#define BGCNT_AFF_32X32 (0x1 << 0xe)
#define BGCNT_AFF_64X64 (0x2 << 0xe)
#define BGCNT_AFF_128X128 (0x3 << 0xe)
#define BGCNT_AFF_MASK ((u16)(0xc000))

/* ---- End of Defines for reg_bgXcnt ---- */


/* ---- Defines for REG_BLDCNT ---- */

// The (A) top layers
#define BLDCNT_TOP_BG0 (0x0 << 0x0)
#define BLDCNT_TOP_BG1 (0x1 << 0x0)
#define BLDCNT_TOP_BG2 (0x2 << 0x0)
#define BLDCNT_TOP_BG3 (0x3 << 0x0)
#define BLDCNT_TOP_OBJ (0x4 << 0x0)
#define BLDCNT_TOP_BACKDROP (0x5 << 0x0)
#define BLDCNT_TOP_MASK ((u16)(0x001f))

// The blending mode
#define BLDCNT_BLD_OFF (0x0 << 0x6)
#define BLDCNT_BLD_NORMAL (0x1 << 0x6)
#define BLDCNT_BLD_WHITE (0x2 << 0x6)
#define BLDCNT_BLD_BLACK (0x3 << 0x6)
#define BLDCNT_BLD_MASK ((u16)(0x00c0))

// The (B) bottom layers
#define BLDCNT_BOT_BG0 (0x0 << 0x8)
#define BLDCNT_BOT_BG1 (0x1 << 0x8)
#define BLDCNT_BOT_BG2 (0x2 << 0x8)
#define BLDCNT_BOT_BG3 (0x3 << 0x8)
#define BLDCNT_BOT_OBJ (0x4 << 0x8)
#define BLDCNT_BOT_BACKDROP (0x5 << 0x8)
#define BLDCNT_BOT_MASK ((u16)(0x1f00))

/* ---- End of Defines for REG_BLDCNT ---- */


/* ---- Defines for REG_BLDALPHA ---- */

// Top blend weight.  Only used for normal blending.
#define BLDALPHA_TOP(n) (n & 0x1f)

// Bot blend weight.  Only used for normal blending.
#define BLDALPHA_BOT(n) ((n & 0x1f) << 0x8)

/* ---- End of Defines for REG_BLDALPHA ---- */


/* ---- Defines for REG_BLDALPHA ---- */

// Top blend weight.  Only used for normal blending.
#define BLDY(n) (n & 0x1f)

/* ---- End of Defines for REG_BLDALPHA ---- */



/* ---- Some misc. inline functions ---- */

#define RGB15_RED_SHIFT (0x0)
#define RGB15_GREEN_SHIFT (0x5)
#define RGB15_BLUE_SHIFT (0xa)

#define RGB15_RED_MASK ((u16)0x001f)
#define RGB15_GREEN_MASK ((u16)0x03e0)
#define RGB15_BLUE_MASK ((u16)0x7c00)

#define RGB15_COMPONENT_MAX_VAL (0x1f)

#define RGB15_NUM_COMPONENTS (3)




inline u16 make_rgb15(u32 red, u32 green, u32 blue)
{
	return (((red & RGB15_COMPONENT_MAX_VAL) << RGB15_RED_SHIFT) 
		| ((green & RGB15_COMPONENT_MAX_VAL) << RGB15_GREEN_SHIFT) 
		| ((blue & RGB15_COMPONENT_MAX_VAL) << RGB15_BLUE_SHIFT));
}

inline u32 rgb15_get_red_component(u32 the_rgb15_val)
{
	return get_bits(the_rgb15_val, RGB15_RED_MASK, RGB15_RED_SHIFT);
}
inline u32 rgb15_get_green_component(u32 the_rgb15_val)
{
	return get_bits(the_rgb15_val, RGB15_GREEN_MASK, RGB15_GREEN_SHIFT);
}
inline u32 rgb15_get_blue_component(u32 the_rgb15_val)
{
	return get_bits(the_rgb15_val, RGB15_BLUE_MASK, RGB15_BLUE_SHIFT);
}

inline void clamped_rgb15_component_add(s32& component, s32 amount_to_add, 
	s32 component_max_value=RGB15_COMPONENT_MAX_VAL)
{
	component += amount_to_add;

	if (component > component_max_value )
	{
		component = component_max_value;
	}
	else if (component < 0)
	{
		component = 0;
	}
}

inline void clamped_rgb15_f24p8_component_add(Fixed24p8& component,
	const Fixed24p8& amount_to_add, const Fixed24p8& target_value)
{
	component += amount_to_add;

	if (amount_to_add > (Fixed24p8){0} && component > target_value)
	{
		component = target_value;
	}
	else if (amount_to_add < (Fixed24p8){0} && component < target_value)
	{
		component = target_value;
	}
}

//inline void clamped_rgb15_f8p8_component_add(Fixed8p8& component,
//	const Fixed8p8& amount_to_add, const Fixed8p8& target_value)
//{
//	component += amount_to_add;
//
//	if (amount_to_add > (Fixed8p8){0} && component > target_value)
//	{
//		component = target_value;
//	}
//	else if (amount_to_add < (Fixed8p8){0} && component < target_value)
//	{
//		component = target_value;
//	}
//}




inline void m3_plot(u32 x, u32 y, u32 color)
{
	((vu16*)(MEM_VRAM))[y * SCREEN_WIDTH + x] = color;
}
inline void m4_plot_basic(u32 x, u32 y, u16 two_color_ids, u32 page = 0)
{
	// Plot To Page 0
	if (page == 0)
	{
		((vu16*)(MEM_VRAM_PAGE_0))[y * SCREEN_WIDTH + x] 
			= two_color_ids;
	}

	// Plot To Page 1
	else
	{
		((vu16*)(MEM_VRAM_PAGE_1))[y * SCREEN_WIDTH + x] 
			= two_color_ids;
	}
}


// The reason That color_id Is passed in as a 32-bit variable Is speed.
inline void m4_plot(s32 x, s32 y, u32 color_id, u32 page)
{

	if (!(x >= 0 && x <= (s32)SCREEN_WIDTH 
		&& y >= 0 && y <= (s32)SCREEN_HEIGHT))
	{
		return;
	}

	vu16* vram_area;
	u16 two_color_ids;

	u8 color_id_8bit = color_id & 0xff;


	// Plot To Page 0
	if (page == 0)
	{
		vram_area = (vu16*)(MEM_VRAM_PAGE_0);
	}

	// Plot To Page 1
	else
	{
		vram_area = (vu16*)(MEM_VRAM_PAGE_1);
	}

	two_color_ids = vram_area[(y * SCREEN_WIDTH + x) / sizeof(vu16)];


	// If x Is odd, change the high byte
	if (x & 1)
	{
		// Clear the high byte
		two_color_ids &= 0x00ff;

		// Set the high byte To the new color ID
		two_color_ids |= (color_id_8bit << 8);
	}

	// If x Is even, change the low byte
	else
	{
		// Clear the low byte
		two_color_ids &= 0xff00;

		// Set the low byte To the new color ID
		two_color_ids |= color_id_8bit;
	}

	vram_area[(y * SCREEN_WIDTH + x) / sizeof(vu16)] = two_color_ids;
}


}

}

#endif		// gba_specific_stuff__slash__gfx_reg_stuff_hpp
