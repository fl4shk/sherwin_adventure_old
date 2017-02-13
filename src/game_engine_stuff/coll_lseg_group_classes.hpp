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


#ifndef coll_lseg_group_classes_hpp
#define coll_lseg_group_classes_hpp

#include "coll_lseg_classes.hpp"

// A (to be) abstract class for a group of line segments for use with
// sprites so that they can detect and respond to collisions with blocks
class coll_lseg_group_base
{
public:		// classes
	class horiz_coll_tuple
	{
	public:		// variables
		bcr_lseg_group bcrlg;
		horiz_coll_lseg clseg;
	} __attribute__((_align4));
	
	
	class vert_coll_tuple
	{
	public:		// variables
		bcr_lseg_group bcrlg;
		vert_coll_lseg clseg;
	} __attribute__((_align4));
	
protected:		// variables and constants
	array_helper<horiz_coll_tuple> horiz_ctups;
	array_helper<vert_coll_tuple> vert_top_ctups;
	array_helper<vert_coll_tuple> vert_bot_ctups;
	
	static const fixed24p8 offset_x_for_any_hs_left;
	static const fixed24p8 offset_x_for_any_hs_right;
	
	static const fixed24p8 offset_x_for_left_vs;
	static const fixed24p8 offset_x_for_right_vs;
	
	static const fixed24p8 vs_height_non_bot_mid_og;
	static const fixed24p8 vs_height_bot_mid_og;
	static const fixed24p8 vs_height_top;
	static const fixed24p8 vs_height_bot_ia;
	
	static const fixed24p8 offset_y_for_top_vs;
	static const fixed24p8 offset_y_for_bot_vs;
	
	
public:		// functions
	inline const horiz_coll_tuple& get_horiz_ctup( u32 index ) const
	{
		return horiz_ctups[index];
	}
	inline const vert_coll_tuple& get_vert_top_ctup( u32 index ) const
	{
		return vert_top_ctups[index];
	}
	inline const vert_coll_tuple& get_vert_bot_ctup( u32 index ) const
	{
		return vert_bot_ctups[index];
	}
	
	inline horiz_coll_tuple& get_horiz_ctup( u32 index )
	{
		return horiz_ctups[index];
	}
	inline vert_coll_tuple& get_vert_top_ctup( u32 index )
	{
		return vert_top_ctups[index];
	}
	inline vert_coll_tuple& get_vert_bot_ctup( u32 index )
	{
		return vert_bot_ctups[index];
	}
	
	virtual const size_t get_num_horiz_ctups() const = 0;
	virtual const size_t get_num_vert_top_ctups() const = 0;
	virtual const size_t get_num_vert_bot_ctups() const = 0;
	
	virtual const size_t get_hi_left_top() const = 0;
	virtual const size_t get_hi_left_bot() const = 0;
	virtual const size_t get_hi_right_top() const = 0;
	virtual const size_t get_hi_right_bot() const = 0;
	
	virtual const size_t get_vi_top_left() const = 0;
	virtual const size_t get_vi_top_right() const = 0;
	
protected:		// functions
	static const fixed24p8 get_pos_x_for_left_hs
		( const coll_box& s_coll_box );
	static const fixed24p8 get_pos_x_for_right_hs
		( const coll_box& s_coll_box );
	
	// "hs" means "horizontal sensor"
	// "og" means "on ground"
	static const fixed24p8 get_pos_y_for_top_hs
		( const coll_box& s_coll_box );
	static const fixed24p8 get_pos_y_for_mid_hs
		( const coll_box& s_coll_box );
	static const fixed24p8 get_pos_y_for_bot_hs
		( const coll_box& s_coll_box );
	
	static const horiz_coll_lseg get_left_top_hs
		( const coll_box& s_coll_box );
	static const horiz_coll_lseg get_left_mid_hs
		( const coll_box& s_coll_box );
	static const horiz_coll_lseg get_left_bot_hs
		( const coll_box& s_coll_box );
	
	static const horiz_coll_lseg get_right_top_hs
		( const coll_box& s_coll_box );
	static const horiz_coll_lseg get_right_mid_hs
		( const coll_box& s_coll_box );
	static const horiz_coll_lseg get_right_bot_hs
		( const coll_box& s_coll_box );
	
	// "ia" means "in air"
	// "vs" means "vertical sensor"
	static const fixed24p8 get_pos_x_for_left_vs
		( const coll_box& s_coll_box );
	static const fixed24p8 get_pos_x_for_mid_vs
		( const coll_box& s_coll_box );
	static const fixed24p8 get_pos_x_for_right_vs
		( const coll_box& s_coll_box );
	
	static const fixed24p8 get_pos_y_for_top_vs
		( const coll_box& s_coll_box );
	static const fixed24p8 get_pos_y_for_bot_vs
		( const coll_box& s_coll_box );
	
	
	static const vert_coll_lseg get_bot_left_vs_og
		( const coll_box& s_coll_box );
	static const vert_coll_lseg get_bot_mid_vs_og
		( const coll_box& s_coll_box );
	static const vert_coll_lseg get_bot_right_vs_og
		( const coll_box& s_coll_box );
	
	static const vert_coll_lseg get_bot_left_vs_ia
		( const coll_box& s_coll_box );
	static const vert_coll_lseg get_bot_mid_vs_ia
		( const coll_box& s_coll_box );
	static const vert_coll_lseg get_bot_right_vs_ia
		( const coll_box& s_coll_box );
	
	static const vert_coll_lseg get_top_left_vs
		( const coll_box& s_coll_box );
	static const vert_coll_lseg get_top_mid_vs
		( const coll_box& s_coll_box );
	static const vert_coll_lseg get_top_right_vs
		( const coll_box& s_coll_box );
	
	
} __attribute__((_align4));



//class coll_lseg_group_16x16
//{
//} __attribute__((_align4));

// Collision Line Segment Group for collision boxes that are smaller than
// 16x32 but larger than 16x16
class coll_lseg_group_16x32 : public coll_lseg_group_base
{
//public:		// enums
protected:		// enums
	
	enum horiz_index
	{
		hi_left_top,
		hi_left_mid,
		hi_left_bot,
		
		hi_right_top,
		hi_right_mid,
		hi_right_bot,
		
		
		
		lim_hi,
	};
	
	enum vert_index_top
	{
		vi_top_left,
		vi_top_mid,
		vi_top_right,
		
		
		lim_vi_top,
	};
	
public:		// enums
	enum vert_index_bot
	{
		vi_bot_mid,
		vi_bot_left,
		vi_bot_right,
		
		
		
		lim_vi_bot,
	};
	
protected:		// variables and constants
	static constexpr size_t num_horiz_ctups = lim_hi,
		num_vert_top_ctups = lim_vi_top, num_vert_bot_ctups = lim_vi_bot;
	
	//bcr_lseg_group horiz_bcr_lseg_groups[num_horiz_ctups];
	//bcr_lseg_group vert_bcr_lseg_groups[num_vert_ctups];
	//horiz_coll_lseg horiz_clseg_groups[num_horiz_ctups];
	//vert_coll_lseg vert_clseg_groups[num_vert_ctups];
	horiz_coll_tuple horiz_ctups_arr[num_horiz_ctups];
	vert_coll_tuple vert_top_ctups_arr[num_vert_top_ctups];
	vert_coll_tuple vert_bot_ctups_arr[num_vert_bot_ctups];
	
public:		// functions
	inline coll_lseg_group_16x32()
	{
		init_arr_helpers();
	}
	coll_lseg_group_16x32( const coll_box& s_coll_box, u32 s_on_ground );
	void init( const coll_box& s_coll_box, u32 s_on_ground );
	
	const size_t get_num_horiz_ctups() const;
	const size_t get_num_vert_top_ctups() const;
	const size_t get_num_vert_bot_ctups() const;
	
	const size_t get_hi_left_top() const;
	const size_t get_hi_left_bot() const;
	const size_t get_hi_right_top() const;
	const size_t get_hi_right_bot() const;
	
	const size_t get_vi_top_left() const;
	const size_t get_vi_top_right() const;
	
	
protected:		// functions
	void init_arr_helpers();
	
} __attribute__((_align4));


#endif		// coll_lseg_group_classes_hpp
