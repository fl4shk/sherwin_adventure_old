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


class coll_lseg_group_base
{
public:		// variables
	array_helper<bcr_line_group> horiz_bcr_lg_arr_helper,
		vert_bcr_lg_arr_helper;
	array_helper<horiz_coll_lseg> horiz_clseg_arr_helper;
	array_helper<vert_coll_lseg> vert_clseg_arr_helper;
	
public:		// functions
	
	
} __attribute__((_align4));


//class coll_lseg_group_16x16 : public coll_lseg_group_base
//{
//protected:		// variables
//	static constexpr size_t
//	bcr_line_group
//	
//public:		// functions
//	
//} __attribute__((_align4));

class coll_lseg_group_16x32 : public coll_lseg_group_base
{
public:		// enums
	
	
protected:		// variables
	bool in_air;
	
public:		// functions
	
} __attribute__((_align4));



#endif		// coll_lseg_classes_hpp
