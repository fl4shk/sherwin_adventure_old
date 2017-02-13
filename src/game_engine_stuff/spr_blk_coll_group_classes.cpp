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
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#include "coll_box_class.hpp"
#include "spr_blk_coll_group_classes.hpp"

s32 spr_blk_coll_group_base::blk_crd_pos_x_for_left_hs;
s32 spr_blk_coll_group_base::blk_crd_pos_x_for_right_hs;

s32 spr_blk_coll_group_base::blk_crd_pos_y_for_top_hs;
s32 spr_blk_coll_group_base::blk_crd_pos_y_for_mid_hs;
s32 spr_blk_coll_group_base::blk_crd_pos_y_for_bot_hs;

//fixed24p8 spr_blk_coll_group_base::hs_width;

fixed24p8 spr_blk_coll_group_base::pos_x_for_left_vs;
fixed24p8 spr_blk_coll_group_base::pos_x_for_mid_vs;
fixed24p8 spr_blk_coll_group_base::pos_x_for_right_vs;

s32 spr_blk_coll_group_base::blk_crd_pos_x_for_left_vs;
s32 spr_blk_coll_group_base::blk_crd_pos_x_for_mid_vs;
s32 spr_blk_coll_group_base::blk_crd_pos_x_for_right_vs;

s32 spr_blk_coll_group_base::blk_crd_pos_y_for_top_vs;
fixed24p8 spr_blk_coll_group_base::pos_y_for_bot_vs;

////const fixed24p8 spr_blk_coll_group_base::offset_x_for_any_hs_left
////	= make_f24p8(2);
//const fixed24p8 spr_blk_coll_group_base::offset_x_for_any_hs_left
//	= make_f24p8(0);
//const fixed24p8 spr_blk_coll_group_base::offset_x_for_any_hs_right
//	= make_f24p8(-spr_blk_coll_group_base::offset_x_for_any_hs_left.data);

const fixed24p8 spr_blk_coll_group_base::vs_height_non_bot_mid_og
	= make_f24p8(num_pixels_per_block_dim);
const fixed24p8 spr_blk_coll_group_base::vs_height_bot_mid_og
	= vs_height_non_bot_mid_og;

//const fixed24p8 spr_blk_coll_group_base::vs_height_top
//	= spr_blk_coll_group_base::offset_y_for_top_vs + make_f24p8(2);
// In-air bot vertical sensors stretch a small number of pixels vertically
// outside s_coll_box
const fixed24p8 spr_blk_coll_group_base::vs_height_bot_ia
	= custom_abs(spr_blk_coll_group_base::offset_y_for_bot_vs) 
	+ make_f24p8(1);
//const fixed24p8 spr_blk_coll_group_base::vs_height_bot_ia
//	= custom_abs(spr_blk_coll_group_base::offset_y_for_bot_vs) 
//	- make_f24p8(1);
//const fixed24p8 spr_blk_coll_group_base::vs_height_bot_ia
//	= spr_blk_coll_group_base::offset_y_for_top_vs + make_f24p8(4);
//const fixed24p8 spr_blk_coll_group_base::vs_height_bot_ia
//	= spr_blk_coll_group_base::offset_y_for_top_vs + make_f24p8(8);

//const fixed24p8 spr_blk_coll_group_base::offset_y_for_top_vs
//	= make_f24p8(4);
const fixed24p8 spr_blk_coll_group_base::offset_y_for_bot_vs
	= make_f24p8(-4);
//const fixed24p8 spr_blk_coll_group_base::offset_y_for_bot_vs
//	= make_f24p8(-2);
//const fixed24p8 spr_blk_coll_group_base::offset_y_for_bot_vs
//	= (fixed24p8){-spr_blk_coll_group_base::offset_y_for_top_vs.data};



void spr_blk_coll_group_base::init_static_vars( const coll_box& s_coll_box )
{
	blk_crd_pos_x_for_left_hs = conv_pix_crd_to_blk_crd(s_coll_box.left()
		.floor_to_int());
	//pos_x_for_right_hs = s_coll_box.get_x_center();
	blk_crd_pos_x_for_right_hs = conv_pix_crd_to_blk_crd(s_coll_box.right()
		.floor_to_int());
	
	static const fixed24p8 offset_y_for_bot_hs 
		= (fixed24p8){ ( s_coll_box.size.y.data / 4 )
		+ ( s_coll_box.size.y.data / 16 ) };
	//static const fixed24p8 offset_y_for_bot_hs 
	//	= (fixed24p8){ ( s_coll_box.size.y.data / 4 )
	//	+ ( s_coll_box.size.y.data / 8 )
	//	+ ( s_coll_box.size.y.data / 16 ) };
	static const fixed24p8 offset_y_for_top_hs 
		= (fixed24p8){-offset_y_for_bot_hs.data};
	
	blk_crd_pos_y_for_top_hs = conv_pix_crd_to_blk_crd
		( ( s_coll_box.get_y_center() + offset_y_for_top_hs )
		.floor_to_int() );
	blk_crd_pos_y_for_mid_hs = conv_pix_crd_to_blk_crd
		(s_coll_box.get_y_center().floor_to_int());
	blk_crd_pos_y_for_bot_hs = conv_pix_crd_to_blk_crd
		( ( s_coll_box.get_y_center() + offset_y_for_bot_hs )
		.floor_to_int() );
	
	//hs_width = s_coll_box.half_width();
	
	static const fixed24p8 offset_x_for_left_vs
		= (fixed24p8){ s_coll_box.size.x.data / 4 };
	//static const fixed24p8 offset_x_for_left_vs
	//	= (fixed24p8){ ( s_coll_box.size.x.data / 8 ) 
	//	+ ( s_coll_box.size.x.data / 16 ) };
	//static const fixed24p8 offset_x_for_left_vs
	//	= (fixed24p8){ ( s_coll_box.size.x.data / 8 ) };
	//static const fixed24p8 offset_x_for_left_vs
	//	= (fixed24p8){ ( s_coll_box.size.x.data / 4 )
	//	+ ( s_coll_box.size.x.data / 8 ) };
	//static const fixed24p8 offset_x_for_left_vs
	//	= (fixed24p8){ ( s_coll_box.size.x.data / 4 )
	//	+ ( s_coll_box.size.x.data / 8 )
	//	+ ( s_coll_box.size.x.data / 16 ) };
	static const fixed24p8 offset_x_for_right_vs
		= (fixed24p8){-offset_x_for_left_vs.data};
	
	pos_x_for_left_vs = s_coll_box.left() + offset_x_for_left_vs;
	pos_x_for_mid_vs = s_coll_box.get_x_center();
	pos_x_for_right_vs = s_coll_box.right() + offset_x_for_right_vs;
	
	blk_crd_pos_x_for_left_vs = conv_pix_crd_to_blk_crd(pos_x_for_left_vs
		.floor_to_int());
	blk_crd_pos_x_for_mid_vs = conv_pix_crd_to_blk_crd(pos_x_for_mid_vs
		.floor_to_int());
	blk_crd_pos_x_for_right_vs = conv_pix_crd_to_blk_crd(pos_x_for_right_vs
		.floor_to_int());
	
	//pos_y_for_top_vs = s_coll_box.top() + offset_y_for_top_vs
	//	- vs_height_top;
	blk_crd_pos_y_for_top_vs = conv_pix_crd_to_blk_crd( s_coll_box.top()
		.floor_to_int() + 1 );
	pos_y_for_bot_vs = s_coll_box.bot() + offset_y_for_bot_vs;
}

const s32 spr_blk_coll_group_base::get_blk_crd_pos_x_for_left_hs()
{
	//return s_coll_box.left();
	return blk_crd_pos_x_for_left_hs;
}
const s32 spr_blk_coll_group_base::get_blk_crd_pos_x_for_right_hs()
{
	//return s_coll_box.get_x_center();
	return blk_crd_pos_x_for_right_hs;
}


// "hs" means "horizontal sensor"
// "og" means "on ground"
const s32 spr_blk_coll_group_base::get_blk_crd_pos_y_for_top_hs()
{
	//return s_coll_box.get_y_center() + offset_y_for_top_hs;
	//return s_coll_box.get_y_center() + offset_y_for_top_hs;
	return blk_crd_pos_y_for_top_hs;
}
const s32 spr_blk_coll_group_base::get_blk_crd_pos_y_for_mid_hs()
{
	//return s_coll_box.get_y_center();
	return blk_crd_pos_y_for_mid_hs;
}
const s32 spr_blk_coll_group_base::get_blk_crd_pos_y_for_bot_hs()
{
	//return s_coll_box.get_y_center() + offset_y_for_bot_hs;
	//return s_coll_box.get_y_center() 
	//	+ (fixed24p8){ ( s_coll_box.size.y.data / 4 )
	//	+ ( s_coll_box.size.y.data / 8 )
	//	+ ( s_coll_box.size.y.data / 16 ) };
	//return s_coll_box.get_y_center() 
	//	+ (fixed24p8){ ( s_coll_box.size.y.data / 4 )
	//	+ ( s_coll_box.size.y.data / 16 ) };
	return blk_crd_pos_y_for_bot_hs;
}

const vec2_s32 spr_blk_coll_group_base::get_left_top_hs_blk_crd_pos()
{
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(s_coll_box),
	//	get_pos_y_for_top_hs(s_coll_box) ), 
	//	s_coll_box.half_width() );
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(),
	//	get_pos_y_for_top_hs() ), hs_width );
	
	return vec2_s32( get_blk_crd_pos_x_for_left_hs(),
		get_blk_crd_pos_y_for_top_hs() );
}
const vec2_s32 spr_blk_coll_group_base::get_left_mid_hs_blk_crd_pos()
{
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(s_coll_box),
	//	get_pos_y_for_mid_hs(s_coll_box) ), 
	//	s_coll_box.half_width() );
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(),
	//	get_pos_y_for_mid_hs() ), hs_width );
	return vec2_s32( get_blk_crd_pos_x_for_left_hs(), 
		get_blk_crd_pos_y_for_mid_hs() );
}
const vec2_s32 spr_blk_coll_group_base::get_left_bot_hs_blk_crd_pos()
{
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(s_coll_box),
	//	get_pos_y_for_bot_hs(s_coll_box) ), 
	//	s_coll_box.half_width() );
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_left_hs(),
	//	get_pos_y_for_bot_hs() ), hs_width );
	return vec2_s32( get_blk_crd_pos_x_for_left_hs(), 
		get_blk_crd_pos_y_for_bot_hs() );
}

const vec2_s32 spr_blk_coll_group_base::get_right_top_hs_blk_crd_pos()
{
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(s_coll_box),
	//	get_pos_y_for_top_hs(s_coll_box) ), 
	//	s_coll_box.half_width() );
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(),
	//	get_pos_y_for_top_hs() ), hs_width );
	return vec2_s32( get_blk_crd_pos_x_for_right_hs(), 
		get_blk_crd_pos_y_for_top_hs() );
}
const vec2_s32 spr_blk_coll_group_base::get_right_mid_hs_blk_crd_pos()
{
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(s_coll_box),
	//	get_pos_y_for_mid_hs(s_coll_box) ), 
	//	s_coll_box.half_width() );
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(),
	//	get_pos_y_for_mid_hs() ), hs_width );
	return vec2_s32( get_blk_crd_pos_x_for_right_hs(), 
		get_blk_crd_pos_y_for_mid_hs() );
}
const vec2_s32 spr_blk_coll_group_base::get_right_bot_hs_blk_crd_pos()
{
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(s_coll_box),
	//	get_pos_y_for_bot_hs(s_coll_box) ), 
	//	s_coll_box.half_width() );
	//return horiz_coll_lseg( vec2_f24p8( get_pos_x_for_right_hs(),
	//	get_pos_y_for_bot_hs() ), hs_width );
	return vec2_s32( get_blk_crd_pos_x_for_right_hs(), 
		get_blk_crd_pos_y_for_bot_hs() );
}


// "ia" means "in air"
// "vs" means "vertical sensor"
const fixed24p8 spr_blk_coll_group_base::get_pos_x_for_left_vs()
{
	//return s_coll_box.left() + offset_x_for_left_vs;
	//return s_coll_box.left() + (fixed24p8){ s_coll_box.size.x.data / 4 };
	return pos_x_for_left_vs;
}
const fixed24p8 spr_blk_coll_group_base::get_pos_x_for_mid_vs()
{
	//return s_coll_box.get_x_center();
	return pos_x_for_mid_vs;
}
const fixed24p8 spr_blk_coll_group_base::get_pos_x_for_right_vs()
{
	//return s_coll_box.right() + offset_x_for_right_vs;
	//return s_coll_box.right() 
	//	- (fixed24p8){ s_coll_box.size.x.data / 4 };
	return pos_x_for_right_vs;
}

const s32 spr_blk_coll_group_base::get_blk_crd_pos_x_for_left_vs()
{
	return blk_crd_pos_x_for_left_vs;
}
const s32 spr_blk_coll_group_base::get_blk_crd_pos_x_for_mid_vs()
{
	return blk_crd_pos_x_for_mid_vs;
}
const s32 spr_blk_coll_group_base::get_blk_crd_pos_x_for_right_vs()
{
	return blk_crd_pos_x_for_right_vs;
}

const s32 spr_blk_coll_group_base::get_blk_crd_pos_y_for_top_vs()
{
	//return s_coll_box.top() + offset_y_for_top_vs - vs_height_top;
	return blk_crd_pos_y_for_top_vs;
}
const fixed24p8 spr_blk_coll_group_base::get_pos_y_for_bot_vs()
{
	//return s_coll_box.bot() + offset_y_for_bot_vs;
	return pos_y_for_bot_vs;
}


const vert_coll_lseg spr_blk_coll_group_base::get_bot_left_vs_og()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(s_coll_box), 
	//	get_pos_y_for_bot_vs(s_coll_box) ), vs_height_non_bot_mid_og );
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(), 
		get_pos_y_for_bot_vs() ), vs_height_non_bot_mid_og );
}
const vert_coll_lseg spr_blk_coll_group_base::get_bot_mid_vs_og()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(s_coll_box),
	//	get_pos_y_for_bot_vs(s_coll_box) ), vs_height_bot_mid_og );
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(),
		get_pos_y_for_bot_vs() ), vs_height_bot_mid_og );
}
const vert_coll_lseg spr_blk_coll_group_base::get_bot_right_vs_og()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box), 
	//	get_pos_y_for_bot_vs(s_coll_box) ), vs_height_non_bot_mid_og );
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(), 
		get_pos_y_for_bot_vs() ), vs_height_non_bot_mid_og );
}


const vert_coll_lseg spr_blk_coll_group_base::get_bot_left_vs_ia()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(s_coll_box), 
	//	get_pos_y_for_bot_vs(s_coll_box) ), vs_height_bot_ia );
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(), 
		get_pos_y_for_bot_vs() ), vs_height_bot_ia );
}
const vert_coll_lseg spr_blk_coll_group_base::get_bot_mid_vs_ia()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(s_coll_box),
	//	get_pos_y_for_bot_vs(s_coll_box) ), vs_height_bot_ia );
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(),
		get_pos_y_for_bot_vs() ), vs_height_bot_ia );
}
const vert_coll_lseg spr_blk_coll_group_base::get_bot_right_vs_ia()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box), 
	//	get_pos_y_for_bot_vs(s_coll_box) ), vs_height_bot_ia );
	return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(), 
		get_pos_y_for_bot_vs() ), vs_height_bot_ia );
}



const vec2_s32 spr_blk_coll_group_base::get_top_left_vs_blk_crd_pos()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(s_coll_box),
	//	get_pos_y_for_top_vs(s_coll_box) ), vs_height_top );
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_left_vs(),
	//	get_pos_y_for_top_vs() ), vs_height_top );
	return vec2_s32( get_blk_crd_pos_x_for_left_vs(),
		get_blk_crd_pos_y_for_top_vs() );
}
const vec2_s32 spr_blk_coll_group_base::get_top_mid_vs_blk_crd_pos()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(s_coll_box),
	//	get_pos_y_for_top_vs(s_coll_box) ), vs_height_top );
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_mid_vs(),
	//	get_pos_y_for_top_vs() ), vs_height_top );
	return vec2_s32( get_blk_crd_pos_x_for_mid_vs(),
		get_blk_crd_pos_y_for_top_vs() );
}
const vec2_s32 spr_blk_coll_group_base::get_top_right_vs_blk_crd_pos()
{
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(s_coll_box),
	//	get_pos_y_for_top_vs(s_coll_box) ), vs_height_top );
	//return vert_coll_lseg( vec2_f24p8( get_pos_x_for_right_vs(),
	//	get_pos_y_for_top_vs() ), vs_height_top );
	return vec2_s32( get_blk_crd_pos_x_for_right_vs(),
		get_blk_crd_pos_y_for_top_vs() );
}


spr_blk_coll_group_16x16::spr_blk_coll_group_16x16
	( const coll_box& s_coll_box, u32 s_on_ground )
{
	init( s_coll_box, s_on_ground );
}

void spr_blk_coll_group_16x16::init( const coll_box& s_coll_box, 
	u32 s_on_ground )
{
	init_arr_helpers();
	
	init_static_vars(s_coll_box);
	
	horiz_ctups[hi_left_top].blk_crd_pos = get_left_top_hs_blk_crd_pos();
	horiz_ctups[hi_left_mid].blk_crd_pos = get_left_mid_hs_blk_crd_pos();
	horiz_ctups[hi_left_bot].blk_crd_pos = get_left_bot_hs_blk_crd_pos();
	
	horiz_ctups[hi_right_top].blk_crd_pos = get_right_top_hs_blk_crd_pos();
	horiz_ctups[hi_right_mid].blk_crd_pos = get_right_mid_hs_blk_crd_pos();
	horiz_ctups[hi_right_bot].blk_crd_pos = get_right_bot_hs_blk_crd_pos();
	
	vert_top_ctups[vi_top_left].blk_crd_pos 
		= get_top_left_vs_blk_crd_pos();
	//vert_top_ctups[vi_top_mid].blk_crd_pos 
	//	= get_top_mid_vs_blk_crd_pos();
	vert_top_ctups[vi_top_right].blk_crd_pos 
		= get_top_right_vs_blk_crd_pos();
	
	if (s_on_ground)
	{
		vert_bot_ctups[vi_bot_left].clseg = get_bot_left_vs_og();
		vert_bot_ctups[vi_bot_mid].clseg = get_bot_mid_vs_og();
		vert_bot_ctups[vi_bot_right].clseg = get_bot_right_vs_og();
	}
	else // if (!s_on_ground)
	{
		vert_bot_ctups[vi_bot_left].clseg = get_bot_left_vs_ia();
		vert_bot_ctups[vi_bot_mid].clseg = get_bot_mid_vs_ia();
		vert_bot_ctups[vi_bot_right].clseg = get_bot_right_vs_ia();
	}
	
	for ( size_t i=0; i<get_num_horiz_ctups(); ++i )
	{
		get_horiz_ctup(i).bcr.init(get_horiz_ctup(i).blk_crd_pos);
	}
	for ( size_t i=0; i<get_num_vert_top_ctups(); ++i )
	{
		get_vert_top_ctup(i).bcr.init(get_vert_top_ctup(i).blk_crd_pos);
	}
	for ( size_t i=0; i<get_num_vert_bot_ctups(); ++i )
	{
		get_vert_bot_ctup(i).bcrlg.init(get_vert_bot_ctup(i).clseg);
	}
	
	
}

void spr_blk_coll_group_16x16::init_arr_helpers()
{
	horiz_ctups.init( horiz_ctups_arr, get_num_horiz_ctups() );
	vert_top_ctups.init( vert_top_ctups_arr, get_num_vert_top_ctups() );
	//vert_bot_ctups.init( vert_bot_ctups_arr, get_num_vert_bot_ctups() );
}


const size_t spr_blk_coll_group_16x16::get_num_horiz_ctups() const
{
	return num_horiz_ctups;
}
const size_t spr_blk_coll_group_16x16::get_num_vert_top_ctups() const
{
	return num_vert_top_ctups;
}
//const size_t spr_blk_coll_group_16x16::get_num_vert_bot_ctups() const
//{
//	return num_vert_bot_ctups;
//}


const size_t spr_blk_coll_group_16x16::get_hi_left_top() const
{
	return hi_left_top;
}
const size_t spr_blk_coll_group_16x16::get_hi_left_bot() const
{
	return hi_left_bot;
}
const size_t spr_blk_coll_group_16x16::get_hi_right_top() const
{
	return hi_right_top;
}
const size_t spr_blk_coll_group_16x16::get_hi_right_bot() const
{
	return hi_right_bot;
}

const size_t spr_blk_coll_group_16x16::get_vi_top_left() const
{
	return vi_top_left;
}
const size_t spr_blk_coll_group_16x16::get_vi_top_right() const
{
	return vi_top_right;
}




spr_blk_coll_group_16x32::spr_blk_coll_group_16x32
	( const coll_box& s_coll_box, u32 s_on_ground )
{
	init( s_coll_box, s_on_ground );
}

void spr_blk_coll_group_16x32::init( const coll_box& s_coll_box, 
	u32 s_on_ground )
{
	init_arr_helpers();
	
	init_static_vars(s_coll_box);
	
	horiz_ctups[hi_left_top].blk_crd_pos = get_left_top_hs_blk_crd_pos();
	horiz_ctups[hi_left_mid].blk_crd_pos = get_left_mid_hs_blk_crd_pos();
	horiz_ctups[hi_left_bot].blk_crd_pos = get_left_bot_hs_blk_crd_pos();
	
	horiz_ctups[hi_right_top].blk_crd_pos = get_right_top_hs_blk_crd_pos();
	horiz_ctups[hi_right_mid].blk_crd_pos = get_right_mid_hs_blk_crd_pos();
	horiz_ctups[hi_right_bot].blk_crd_pos = get_right_bot_hs_blk_crd_pos();
	
	vert_top_ctups[vi_top_left].blk_crd_pos 
		= get_top_left_vs_blk_crd_pos();
	//vert_top_ctups[vi_top_mid].blk_crd_pos 
	//	= get_top_mid_vs_blk_crd_pos();
	vert_top_ctups[vi_top_right].blk_crd_pos 
		= get_top_right_vs_blk_crd_pos();
	
	if (s_on_ground)
	{
		vert_bot_ctups[vi_bot_left].clseg = get_bot_left_vs_og();
		vert_bot_ctups[vi_bot_mid].clseg = get_bot_mid_vs_og();
		vert_bot_ctups[vi_bot_right].clseg = get_bot_right_vs_og();
	}
	else // if (!s_on_ground)
	{
		vert_bot_ctups[vi_bot_left].clseg = get_bot_left_vs_ia();
		vert_bot_ctups[vi_bot_mid].clseg = get_bot_mid_vs_ia();
		vert_bot_ctups[vi_bot_right].clseg = get_bot_right_vs_ia();
	}
	
	for ( size_t i=0; i<get_num_horiz_ctups(); ++i )
	{
		//horiz_ctups[i].bcrlg.init(horiz_ctups[i].clseg);
		get_horiz_ctup(i).bcr.init(get_horiz_ctup(i).blk_crd_pos);
	}
	for ( size_t i=0; i<get_num_vert_top_ctups(); ++i )
	{
		//vert_top_ctups[i].bcrlg.init(vert_top_ctups[i].clseg);
		get_vert_top_ctup(i).bcr.init(get_vert_top_ctup(i).blk_crd_pos);
	}
	for ( size_t i=0; i<get_num_vert_bot_ctups(); ++i )
	{
		//vert_bot_ctups[i].bcrlg.init(vert_bot_ctups[i].clseg);
		get_vert_bot_ctup(i).bcrlg.init(get_vert_bot_ctup(i).clseg);
	}
	
	
}

void spr_blk_coll_group_16x32::init_arr_helpers()
{
	horiz_ctups.init( horiz_ctups_arr, get_num_horiz_ctups() );
	vert_top_ctups.init( vert_top_ctups_arr, get_num_vert_top_ctups() );
	//vert_bot_ctups.init( vert_bot_ctups_arr, get_num_vert_bot_ctups() );
}


const size_t spr_blk_coll_group_16x32::get_num_horiz_ctups() const
{
	return num_horiz_ctups;
}
const size_t spr_blk_coll_group_16x32::get_num_vert_top_ctups() const
{
	return num_vert_top_ctups;
}
//const size_t spr_blk_coll_group_16x32::get_num_vert_bot_ctups() const
//{
//	return num_vert_bot_ctups;
//}


const size_t spr_blk_coll_group_16x32::get_hi_left_top() const
{
	return hi_left_top;
}
const size_t spr_blk_coll_group_16x32::get_hi_left_bot() const
{
	return hi_left_bot;
}
const size_t spr_blk_coll_group_16x32::get_hi_right_top() const
{
	return hi_right_top;
}
const size_t spr_blk_coll_group_16x32::get_hi_right_bot() const
{
	return hi_right_bot;
}

const size_t spr_blk_coll_group_16x32::get_vi_top_left() const
{
	return vi_top_left;
}
const size_t spr_blk_coll_group_16x32::get_vi_top_right() const
{
	return vi_top_right;
}
