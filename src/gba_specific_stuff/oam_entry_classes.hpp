// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License FOR more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef oam_entry_classes_hpp
#define oam_entry_classes_hpp

#include "gfx_reg_stuff.hpp"
#include "oam_entry_defines.hpp"
#include "dma_stuff.hpp"
#include "asm_funcs.hpp"
#include "../general_utility_stuff/misc_bitwise_funcs.hpp"
#include "../general_utility_stuff/fixed_classes.hpp"


class oam_entry;
class oam_entry_affine;

static const u32 oam_mirror_size = 128;
static const u32 oam_mirror_aff_size = 32;

extern oam_entry oam_mirror[oam_mirror_size];
#define oam_mirror_aff ( (oam_entry_affine*)(oam_mirror) )
//extern oam_entry_affine* const oam_mirror_aff;



// Regular OAM Entries, no affine transformations
class oam_entry
{
public:		// enums
	enum shape_size { ss_8x8, ss_16x16, ss_32x32, ss_64x64, ss_16x8, 
		ss_32x8, ss_32x16, ss_64x32, ss_8x16, ss_8x32, ss_16x32, 
		ss_32x64, lim_ss } alignas(4);
	
public:		// constants
	static constexpr u32 num_attr0_shapes = 3, num_attr1_sizes = 4;
	
	static const vec2_u32 ss_to_vec2_arr[lim_ss];
	
	//static const vec2_u32 attrs_to_ss_arr_2d[4][3];
	static const vec2_u32 ss_enum_to_ss_attrs_arr[lim_ss];
	//static const shape_size ss_attrs_no_shift_to_ss_enum_arr_2d
	//	[num_attr0_shapes][num_attr1_sizes];
	
public:		// variables
	u16 attr0;
	u16 attr1;
	u16 attr2;
	s16 fill;
	
public:		// wrapper functions
	
	s32 get_y_coord() const
	{
		return get_bits( attr0, obj_attr0_y_coord_mask, 
			obj_attr0_y_coord_shift );
	}
	
	void set_y_coord( s32 n_y_coord )
	{
		//clear_and_set_bits( attr0, obj_attr0_y_coord_mask,
		//	obj_attr0_y_coord(n_y_coord) );
		clear_bits( attr0, obj_attr0_y_coord_mask );
		set_bits( attr0, obj_attr0_y_coord(n_y_coord) );
	}
	
	s32 get_x_coord() const
	{
		return get_bits( attr1, obj_attr1_x_coord_mask,
			obj_attr1_x_coord_shift );
	}
	
	void set_x_coord( s32 n_x_coord )
	{
		//clear_and_set_bits( attr1, obj_attr1_x_coord_mask,
		//	obj_attr1_x_coord(n_x_coord) );
		clear_bits( attr1, obj_attr1_x_coord_mask );
		set_bits( attr1, obj_attr1_x_coord(n_x_coord) );
	}
	
	void enable_hflip()
	{
		set_bits( attr1, obj_attr1_hflip_on );
	}
	void disable_hflip()
	{
		clear_bits( attr1, obj_attr1_hflip_mask );
	}
	u32 get_hflip_status() const
	{
		return get_bits( attr1, obj_attr1_hflip_mask, 
			obj_attr1_hflip_shift );
	}
	
	
	void enable_vflip()
	{
		set_bits( attr1, obj_attr1_vflip_on );
	}
	void disable_vflip()
	{
		clear_bits( attr1, obj_attr1_vflip_mask );
	}
	u32 get_vflip_status() const
	{
		return get_bits( attr1, obj_attr1_vflip_mask, 
			obj_attr1_vflip_shift );
	}
	
	
	
	void show_non_affine()
	{
		clear_bits( attr0, 
			( obj_attr0_affine_mask | obj_attr0_disable_mask ) );
	}
	
	void hide_non_affine()
	{
		clear_bits( attr0, 
			( obj_attr0_affine_mask | obj_attr0_disable_mask ) );
		
		set_bits( attr0, obj_attr0_disable_on );
	}
	
	void set_tile_number( u32 n_tile_num )
	{
		clear_and_set_bits( attr2, obj_attr2_tile_number_mask,
			obj_attr2_tile_number(n_tile_num) );
	}
	
	u32 get_tile_number() const
	{
		return get_bits( attr2, obj_attr2_tile_number_mask,
			obj_attr2_tile_number_shift );
	}
	
	void set_pal_number( u32 n_pal_num )
	{
		clear_and_set_bits( attr2, obj_attr2_pal_num_mask,
			obj_attr2_pal_num(n_pal_num) );
	}
	
	u32 get_pal_number() const
	{
		return get_bits( attr2, obj_attr2_pal_num_mask,
			obj_attr2_pal_num_shift );
	}
	
	
	
	
	void set_shape_size( shape_size n_shape_size );
	shape_size get_shape_size() const;
	
	void set_shape_size_with_vec2( const vec2_u32& n_shape_size );
	vec2_u32 get_shape_size_as_vec2() const;
	
	
	
} __attribute__((_ALIGN4));



// A class FOR OAM Affine stuffs
// I could probably change every s16 member variable in this class to a
// fixed8p8, since that's basically what it's supposed to be.
class oam_entry_affine
{
public:		// variables
	static const u32 fill_size = 3;
	
	
	u16 fill0[fill_size];
	fixed8p8 pa;
	
	u16 fill1[fill_size];
	fixed8p8 pb;
	
	u16 fill2[fill_size];
	fixed8p8 pc;
	
	u16 fill3[fill_size];
	fixed8p8 pd;
	
public:		// functions
	
	
} __attribute__((_ALIGN4));



inline void copy_oam_mirror_to_oam()
{
	//dma3_cpy( (vu16*)(MEM_OAM), oam_mirror, 
	//	( oam_mirror_size * sizeof(oam_entry) ) / sizeof(u16), 0 );
	memcpy32( (void*)(MEM_OAM), oam_mirror,
		( oam_mirror_size * sizeof(oam_entry) ) / sizeof(u32) );
}

inline void clear_oam_mirror()
{
	memfill32( oam_mirror, 0, sizeof(oam_mirror) / sizeof(u32) );
}



#endif		// oam_entry_classes_hpp
