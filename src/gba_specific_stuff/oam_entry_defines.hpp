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


#ifndef gba_specific_stuff__slash__oam_entry_defines_hpp
#define gba_specific_stuff__slash__oam_entry_defines_hpp




// -- Object Attribute 0 Stuff --

// Object Y-Coordinate
#define OBJ_ATTR0_Y_COORD(n)			(n & 0x00ff)

#define OBJ_ATTR0_Y_COORD_MASK			(0x00ff)
#define OBJ_ATTR0_Y_COORD_SHIFT			(0)


// Object Affine Flag
#define OBJ_ATTR0_AFFINE_OFF			(0 << 8)
#define OBJ_ATTR0_AFFINE_ON				(1 << 8)

#define OBJ_ATTR0_AFFINE_MASK			(0x0100)
#define OBJ_ATTR0_AFFINE_SHIFT			(8)


// Object Double-Size Flag (When Affine Flag Set)
#define OBJ_ATTR0_DOUBLE_SIZE_OFF		(0x0 << 9)
#define OBJ_ATTR0_DOUBLE_SIZE_ON		(0x1 << 9)

#define OBJ_ATTR0_DOUBLE_SIZE_MASK		(0x0200)
#define OBJ_ATTR0_DOUBLE_SIZE_SHIFT		(9)


// Object Disable Flag (When Affine Flag Cleared)
#define OBJ_ATTR0_DISABLE_OFF			(0x0 << 9)
#define OBJ_ATTR0_DISABLE_ON			(0x1 << 9)

#define OBJ_ATTR0_DISABLE_MASK			(0x0200)
#define OBJ_ATTR0_DISABLE_SHIFT			(9)


// Object Mode (Normal, Semi-Transparent, OBJ Window)
#define OBJ_ATTR0_MODE_NORMAL				(0x0 << 10)
#define OBJ_ATTR0_MODE_SEMITRANSPARENT		(0x1 << 10)
#define OBJ_ATTR0_MODE_OBJWINDOW			(0x2 << 10)

#define OBJ_ATTR0_MODE_MASK					(0x0600)
#define OBJ_ATTR0_MODE_SHIFT				(10)


// Object Mosaic
#define OBJ_ATTR0_MOSAIC_OFF			(0x0 << 12)
#define OBJ_ATTR0_MOSAIC_ON				(0x1 << 12)

#define OBJ_ATTR0_MOSAIC_MASK			(0x1000)
#define OBJ_ATTR0_MOSAIC_SHIFT			(12)


// Palette Stuff:  16 palettes of 16 colors each, or one large palette with
// 256 colors
#define OBJ_ATTR0_PAL16					(0x0 << 13)
#define OBJ_ATTR0_PAL256				(0x1 << 13)

#define OBJ_ATTR0_PAL_MASK				(0x2000)
#define OBJ_ATTR0_PAL_SHIFT				(13)


// Object Shape (Square, Horizontal, or Vertical)
#define OBJ_ATTR0_SHAPE_SQUARE					(0x0 << 14)
#define OBJ_ATTR0_SHAPE_HORIZONTAL				(0x1 << 14)
#define OBJ_ATTR0_SHAPE_VERTICAL				(0x2 << 14)

#define OBJ_ATTR0_SHAPE_MASK					(0xc000)
#define OBJ_ATTR0_SHAPE_SHIFT					(14)

#define OBJ_ATTR0_SHAPE_SQUARE_NO_SHIFT			(0x0)
#define OBJ_ATTR0_SHAPE_HORIZONTAL_NO_SHIFT		(0x1)
#define OBJ_ATTR0_SHAPE_VERTICAL_NO_SHIFT		(0x2)

// -- End of Object Attribute 0 Stuff -- 



// -- Object Attribute 1 Stuff --

// Object X-Coordinate
#define OBJ_ATTR1_X_COORD(n)			(n & 0x01ff)

#define OBJ_ATTR1_X_COORD_MASK			(0x01ff)
#define OBJ_ATTR1_X_COORD_SHIFT			(0)


// Object Affine Parameter Slot (When Affine Flag Set)
#define OBJ_ATTR1_AFFINE_PARAM_SLOT(n)			((n & 0x1f) << 9)

#define OBJ_ATTR1_AFFINE_PARAM_SLOT_MASK		(0x3e00)
#define OBJ_ATTR1_AFFINE_PARAM_SLOT_SHIFT		(9)


// Object Horizontal Flip (When Affine Flag Cleared)
#define OBJ_ATTR1_HFLIP_OFF				(0x0 << 12)
#define OBJ_ATTR1_HFLIP_ON				(0x1 << 12)

#define OBJ_ATTR1_HFLIP_MASK			(0x1000)
#define OBJ_ATTR1_HFLIP_SHIFT			(12)


// Object Vertical Flip (When Affine Flag Cleared)
#define OBJ_ATTR1_VFLIP_OFF				(0x0 << 13)
#define OBJ_ATTR1_VFLIP_ON				(0x1 << 13)

#define OBJ_ATTR1_VFLIP_MASK			(0x2000)
#define OBJ_ATTR1_VFLIP_SHIFT			(13)


// Object Size
#define OBJ_ATTR1_SIZE_0				(0x0 << 14)
#define OBJ_ATTR1_SIZE_1				(0x1 << 14)
#define OBJ_ATTR1_SIZE_2				(0x2 << 14)
#define OBJ_ATTR1_SIZE_3				(0x3 << 14)

#define OBJ_ATTR1_SIZE_MASK				(0xc000)
#define OBJ_ATTR1_SIZE_SHIFT			(14)

#define OBJ_ATTR1_SIZE_0_NO_SHIFT		(0x0)
#define OBJ_ATTR1_SIZE_1_NO_SHIFT		(0x1)
#define OBJ_ATTR1_SIZE_2_NO_SHIFT		(0x2)
#define OBJ_ATTR1_SIZE_3_NO_SHIFT		(0x3)

// -- End of Object Attribute 1 Stuff --



// -- Object Attribute 2 Stuff --

// Object Tile Number
#define OBJ_ATTR2_TILE_NUMBER(n)		(n & 0x03ff)

#define OBJ_ATTR2_TILE_NUMBER_MASK		(0x03ff)
#define OBJ_ATTR2_TILE_NUMBER_SHIFT		(0)


// Object Priority Relative To BG and Other Objects
#define OBJ_ATTR2_PRIO(n)			((n & 0x3) << 10)

#define OBJ_ATTR2_PRIO_0				(0x0 << 10)
#define OBJ_ATTR2_PRIO_1				(0x1 << 10)
#define OBJ_ATTR2_PRIO_2				(0x2 << 10)
#define OBJ_ATTR2_PRIO_3				(0x3 << 10)

#define OBJ_ATTR2_PRIO_MASK			(0x0c00)
#define OBJ_ATTR2_PRIO_SHIFT			(10)


// Object Palette Number (Not used in 256 color/1 palette mode)
#define OBJ_ATTR2_PAL_NUM(n)			((n & 0xf) << 12)

#define OBJ_ATTR2_PAL_NUM_MASK			(0xf000)
#define OBJ_ATTR2_PAL_NUM_SHIFT			(12)



// -- End of Object Attribute 2 Stuff --


#endif		// gba_specific_stuff__slash__oam_entry_defines_hpp
