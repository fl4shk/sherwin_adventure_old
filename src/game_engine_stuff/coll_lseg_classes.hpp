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


#ifndef coll_lseg_classes_hpp
#define coll_lseg_classes_hpp


#include "../general_utility_stuff/fixed_classes.hpp"
#include "../general_utility_stuff/vec2_class.hpp"
#include "block_coll_result_group_classes.hpp"

class horiz_coll_lseg;
class vert_coll_lseg;


//class generic_coll_lseg
//{
//public:		// variables
//	static constexpr size_t num_end_points = 2;
//	std::array< vec2_f24p8, num_end_points > end_points;
//	
//public:		// functions
//	inline generic_coll_lseg()
//	{
//	}
//	inline generic_coll_lseg( const vec2_f24p8& s_end_pt_0, 
//		const vec2_f24p8& s_end_pt_1 ) : end_points{ s_end_pt_0, 
//		s_end_pt_1 }
//	{
//	}
//	inline generic_coll_lseg( const generic_coll_lseg& to_copy )
//	{
//		*this = to_copy;
//	}
//	
//	inline generic_coll_lseg& operator = 
//		( const generic_coll_lseg& to_copy )
//	{
//		end_points = to_copy.end_points;
//		
//		return *this;
//	}
//	
//	bool intersects( const generic_coll_lseg& to_check, 
//		vec2_f24p8* ret=NULL ) const __attribute__((_iwram_code));
//	
//} __attribute__((_align4));


class coll_lseg_extras
{
protected:		// functions
	static bool collinear_lsegs_intersect( const fixed24p8& a_0, 
		const fixed24p8& a_1, const fixed24p8& b_0, const fixed24p8& b_1 );
	
	friend class horiz_coll_lseg;
	friend class vert_coll_lseg;
	
} __attribute__((_align4));



// Horizontal line segment
class horiz_coll_lseg
{
protected:		// variables
	vec2_f24p8 internal_left_pt;
	fixed24p8 internal_length;
	
public:		// functions
	inline horiz_coll_lseg()
	{
	}
	inline horiz_coll_lseg( const vec2_f24p8& s_left_pt, 
		const fixed24p8& s_length ) : internal_left_pt(s_left_pt),
		internal_length(s_length)
	{
	}
	inline horiz_coll_lseg( const vec2_s32& s_left_pt, 
		const fixed24p8& s_length )
		: internal_left_pt( make_f24p8(s_left_pt.x), 
		make_f24p8(s_left_pt.y) ), internal_length(s_length)
	{
	}
	inline horiz_coll_lseg( const horiz_coll_lseg& to_copy )
	{
		*this = to_copy;
	}
	
	inline horiz_coll_lseg& operator = ( const horiz_coll_lseg& to_copy )
	{
		left_pt() = to_copy.left_pt();
		length() = to_copy.length();
		return *this;
	}
	
	inline vec2_f24p8& left_pt()
	{
		return internal_left_pt;
	}
	inline const vec2_f24p8& left_pt() const
	{
		return internal_left_pt;
	}
	inline fixed24p8& length()
	{
		return internal_length;
	}
	inline const fixed24p8& length() const
	{
		return internal_length;
	}
	inline const vec2_f24p8 right_pt() const
	{
		return left_pt() + vec2_f24p8( length(), make_f24p8(0) );
	}
	
	inline bool intersects( const horiz_coll_lseg& to_check ) const
	{
		if ( left_pt().y == to_check.left_pt().y )
		{
			return coll_lseg_extras::collinear_lsegs_intersect
				( left_pt().x, right_pt().x, to_check.left_pt().x, 
				to_check.right_pt().x );
		}
		
		return false;
	}
	//inline bool intersects( const vert_coll_lseg& to_check ) const;
	
} __attribute__((_align4));


class vert_coll_lseg
{
protected:		// variables
	vec2_f24p8 internal_top_pt;
	fixed24p8 internal_length;
	
public:		// functions
	inline vert_coll_lseg()
	{
	}
	inline vert_coll_lseg( const vec2_f24p8& s_top_pt, 
		const fixed24p8& s_length ) : internal_top_pt(s_top_pt),
		internal_length(s_length)
	{
	}
	inline vert_coll_lseg( const vec2_s32& s_top_pt, 
		const fixed24p8& s_length )
		: internal_top_pt( make_f24p8(s_top_pt.x), 
		make_f24p8(s_top_pt.y) ), internal_length(s_length)
	{
	}
	inline vert_coll_lseg( const vert_coll_lseg& to_copy )
	{
		*this = to_copy;
	}
	
	inline vert_coll_lseg& operator = ( const vert_coll_lseg& to_copy )
	{
		top_pt() = to_copy.top_pt();
		length() = to_copy.length();
		return *this;
	}
	
	inline vec2_f24p8& top_pt()
	{
		return internal_top_pt;
	}
	inline const vec2_f24p8& top_pt() const
	{
		return internal_top_pt;
	}
	inline fixed24p8& length()
	{
		return internal_length;
	}
	inline const fixed24p8& length() const
	{
		return internal_length;
	}
	inline const vec2_f24p8 bot_pt() const
	{
		return top_pt() + vec2_f24p8( make_f24p8(0), length() );
	}
	
	//inline bool intersects( const horiz_coll_lseg& to_check ) const
	//{
	//	return to_check.intersects(*this);
	//}
	inline bool intersects( const vert_coll_lseg& to_check ) const
	{
		if ( top_pt().x == to_check.top_pt().x )
		{
			return coll_lseg_extras::collinear_lsegs_intersect( top_pt().x,
				bot_pt().x, to_check.top_pt().x, to_check.bot_pt().x );
		}
		
		return false;
	}
	
} __attribute__((_align4));



//inline bool horiz_coll_lseg::intersects( const vert_coll_lseg& to_check ) 
//	const
//{
//	return generic_coll_lseg( left_pt(), right_pt() ).intersects
//		( generic_coll_lseg( to_check.top_pt(), to_check.bot_pt() ) );
//}




//class coll_lseg_group_16x16
//{
//} __attribute__((_align4));

// Collision Line Segment Group for collision boxes that are smaller than
// 16x32 but larger than 16x16
class coll_lseg_group_16x32
{
public:		// enums
	
	enum horiz_index
	{
		hi_left_top,
		hi_left_bot,
		
		hi_right_top,
		hi_right_bot,
		
		
		
		lim_hi,
	};
	
	enum vert_index_top
	{
		vi_top_left,
		vi_top_right,
		
		
		lim_vi_top,
	};
	
	enum vert_index_bot
	{
		vi_bot_mid,
		vi_bot_left,
		vi_bot_right,
		
		
		
		lim_vi_bot,
	};
	
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
	
public:		// index constants
	//static constexpr u32 hi_left_top_og = hi_left_top;
	//static constexpr u32 hi_left_bot_og = hi_left_bot;
	//static constexpr u32 hi_right_top_og = hi_right_top;
	//static constexpr u32 hi_right_bot_og = hi_right_bot;
	
	//static constexpr u32 vi_bot_left_og = vi_bot_left;
	//static constexpr u32 vi_bot_mid_og = vi_bot_mid;
	//static constexpr u32 vi_bot_right_og = vi_bot_right;
	
	
	//static constexpr u32 hi_left_top_ia = hi_left_top;
	//static constexpr u32 hi_left_bot_ia = hi_left_bot;
	//static constexpr u32 hi_right_top_ia = hi_right_top;
	//static constexpr u32 hi_right_bot_ia = hi_right_bot;
	
	
	static constexpr u32 vi_top_left_ia = vi_top_left;
	static constexpr u32 vi_top_right_ia = vi_top_right;
	
	//static constexpr u32 vi_bot_left_ia = vi_bot_left;
	//static constexpr u32 vi_bot_mid_ia = vi_bot_mid;
	//static constexpr u32 vi_bot_right_ia = vi_bot_right;
	
	static constexpr size_t num_horiz_ctups = lim_hi,
		num_vert_top_ctups = lim_vi_top, num_vert_bot_ctups = lim_vi_bot;
	
protected:		// variables and constants
	//bcr_lseg_group horiz_bcr_lseg_groups[num_horiz_ctups];
	//bcr_lseg_group vert_bcr_lseg_groups[num_vert_ctups];
	//horiz_coll_lseg horiz_clseg_groups[num_horiz_ctups];
	//vert_coll_lseg vert_clseg_groups[num_vert_ctups];
	horiz_coll_tuple horiz_ctups[num_horiz_ctups];
	vert_coll_tuple vert_top_ctups[num_vert_top_ctups];
	vert_coll_tuple vert_bot_ctups[num_vert_bot_ctups];
	
	u32 internal_on_ground = false;
	
	static const fixed24p8 offset_x_for_any_hs_left;
	static const fixed24p8 offset_x_for_any_hs_right;
	
	static const fixed24p8 offset_y_for_top_hs;
	static const fixed24p8 offset_y_for_bot_hs;
	
	static const fixed24p8 offset_x_for_left_vs;
	static const fixed24p8 offset_x_for_right_vs;
	
	static const fixed24p8 vs_height_non_bot_mid_og;
	static const fixed24p8 vs_height_bot_mid_og;
	static const fixed24p8 vs_height_ia;
	
	static const fixed24p8 offset_y_for_top_vs_ia;
	static const fixed24p8 offset_y_for_bot_vs;
	
public:		// functions
	inline coll_lseg_group_16x32()
	{
	}
	coll_lseg_group_16x32( const coll_box& s_coll_box, u32 s_on_ground );
	void init( const coll_box& s_coll_box, u32 s_on_ground );
	
	
	inline const u32 get_on_ground() const
	{
		return internal_on_ground;
	}
	
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
	
	
protected:		// functions
	static const fixed24p8 get_pos_x_for_left_hs
		( const coll_box& s_coll_box );
	static const fixed24p8 get_pos_x_for_right_hs
		( const coll_box& s_coll_box );
	
	// "hs" means "horizontal sensor"
	// "og" means "on ground"
	static const fixed24p8 get_pos_y_for_top_hs
		( const coll_box& s_coll_box );
		
	static const fixed24p8 get_pos_y_for_bot_hs
		( const coll_box& s_coll_box );
	
	static const horiz_coll_lseg get_left_top_hs
		( const coll_box& s_coll_box );
	static const horiz_coll_lseg get_right_top_hs
		( const coll_box& s_coll_box );
	
	static const horiz_coll_lseg get_left_bot_hs
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
	
	static const fixed24p8 get_pos_y_for_top_vs_ia
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
	
	static const vert_coll_lseg get_top_left_vs_ia
		( const coll_box& s_coll_box );
	static const vert_coll_lseg get_top_right_vs_ia
		( const coll_box& s_coll_box );
	
} __attribute__((_align4));



#endif		// coll_lseg_classes_hpp
