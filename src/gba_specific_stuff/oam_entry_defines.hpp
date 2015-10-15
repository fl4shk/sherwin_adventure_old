#ifndef oam_entry_defines_hpp
#define oam_entry_defines_hpp




// -- Object Attribute 0 Stuff --

// Object Y-Coordinate
#define obj_attr0_y_coord( n )			( n & 0x00ff )

#define obj_attr0_y_coord_mask			( 0x00ff )
#define obj_attr0_y_coord_shift			( 0 )


// Object Affine Flag
#define obj_attr0_affine_off			( 0 << 8 )
#define obj_attr0_affine_on				( 1 << 8 )

#define obj_attr0_affine_mask			( 0x0100 )
#define obj_attr0_affine_shift			( 8 )


// Object Double-Size Flag (When Affine Flag Set)
#define obj_attr0_double_size_off		( 0x0 << 9 )
#define obj_attr0_double_size_on		( 0x1 << 9 )

#define obj_attr0_double_size_mask		( 0x0200 )
#define obj_attr0_double_size_shift		( 9 )


// Object Disable Flag (When Affine Flag Cleared)
#define obj_attr0_disable_off			( 0x0 << 9 )
#define obj_attr0_disable_on			( 0x1 << 9 )

#define obj_attr0_disable_mask			( 0x0200 )
#define obj_attr0_disable_shift			( 9 )


// Object Mode (Normal, Semi-Transparent, OBJ Window )
#define obj_attr0_mode_normal				( 0x0 << 10 )
#define obj_attr0_mode_semitransparent		( 0x1 << 10 )
#define obj_attr0_mode_objwindow			( 0x2 << 10 )

#define obj_attr0_mode_mask					( 0x0600 )
#define obj_attr0_mode_shift				( 10 )


// Object Mosaic
#define obj_attr0_mosaic_off			( 0x0 << 12 )
#define obj_attr0_mosaic_on				( 0x1 << 12 )

#define obj_attr0_mosaic_mask			( 0x1000 )
#define obj_attr0_mosaic_shift			( 12 )


// Palette Stuff:  16 palettes of 16 colors each, or one large palette with
// 256 colors
#define obj_attr0_pal16					( 0x0 << 13 )
#define obj_attr0_pal256				( 0x1 << 13 )

#define obj_attr0_pal_mask				( 0x2000 )
#define obj_attr0_pal_shift				( 13 )


// Object Shape (Square, Horizontal, or Vertical)
#define obj_attr0_shape_square			( 0x0 << 14 )
#define obj_attr0_shape_horizontal		( 0x1 << 14 )
#define obj_attr0_shape_vertical		( 0x2 << 14 )

#define obj_attr0_shape_mask			( 0xc000 )
#define obj_attr0_shape_shift			( 14 )

// -- End of Object Attribute 0 Stuff -- 



// -- Object Attribute 1 Stuff --

// Object X-Coordinate
#define obj_attr1_x_coord( n )			( n & 0x01ff )

#define obj_attr1_x_coord_mask			( 0x01ff )
#define obj_attr1_x_coord_shift			( 0 )


// Object Affine Parameter Slot (When Affine Flag Set)
#define obj_attr1_affine_param_slot( n)			( ( n & 0x1f ) << 9 )

#define obj_attr1_affine_param_slot_mask		( 0x3e00 )
#define obj_attr1_affine_param_slot_shift		( 9 )


// Object Horizontal Flip (When Affine Flag Cleared)
#define obj_attr1_hflip_off				( 0x0 << 12 )
#define obj_attr1_hflip_on				( 0x1 << 12 )

#define obj_attr1_hflip_mask			( 0x1000 )
#define obj_attr1_hflip_shift			( 12 )


// Object Vertical Flip (When Affine Flag Cleared)
#define obj_attr1_vflip_off				( 0x0 << 13 )
#define obj_attr1_vflip_on				( 0x1 << 13 )

#define obj_attr1_vflip_mask			( 0x2000 )
#define obj_attr1_vflip_shift			( 13 )


// Object Size
#define obj_attr1_size_0				( 0x0 << 14 )
#define obj_attr1_size_1				( 0x1 << 14 )
#define obj_attr1_size_2				( 0x2 << 14 )
#define obj_attr1_size_3				( 0x3 << 14 )

#define obj_attr1_size_mask				( 0xc000 )
#define obj_attr1_size_shift			( 14 )

// -- End of Object Attribute 1 Stuff --



// -- Object Attribute 2 Stuff --

// Object Tile Number
#define obj_attr2_tile_number( n )		( n & 0x03ff )

#define obj_attr2_tile_number_mask		( 0x03ff )
#define obj_attr2_tile_number_shift		( 0 )


// Object Priority Relative to BG
#define obj_attr2_bg_prio( n )			( ( n & 0x3 ) << 10 )

#define obj_attr2_bg_prio_0				( 0x0 << 10 )
#define obj_attr2_bg_prio_1				( 0x1 << 10 )
#define obj_attr2_bg_prio_2				( 0x2 << 10 )
#define obj_attr2_bg_prio_3				( 0x3 << 10 )

#define obj_attr2_bg_prio_mask			( 0x0c00 )
#define obj_attr2_bg_prio_shift			( 10 )


// Object Palette Number (Not used in 256 color/1 palette mode)
#define obj_attr2_pal_num( n )			( ( n & 0xf ) << 12 )

#define obj_attr2_pal_num_mask			( 0xf000 )
#define obj_attr2_pal_num_shift			( 12 )



// -- End of Object Attribute 2 Stuff --


#endif		// oam_entry_defines_hpp
