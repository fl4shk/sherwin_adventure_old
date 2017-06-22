// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef coll_lseg_classes_hpp
#define coll_lseg_classes_hpp


#include "../general_utility_stuff/fixed_classes.hpp"
#include "../general_utility_stuff/vec2_class.hpp"
#include "block_coll_result_group_classes.hpp"

class HorizCollLseg;
class VertCollLseg;


//class GenericCollLseg
//{
//public:		// variables
//	static constexpr size_t num_end_points = 2;
//	std::array< vec2_f24p8, num_end_points > end_points;
//	
//public:		// functions
//	inline GenericCollLseg()
//	{
//	}
//	inline GenericCollLseg( const vec2_f24p8& s_end_pt_0, 
//		const vec2_f24p8& s_end_pt_1 ) : end_points{ s_end_pt_0, 
//		s_end_pt_1 }
//	{
//	}
//	inline GenericCollLseg( const GenericCollLseg& to_copy )
//	{
//		*this = to_copy;
//	}
//	
//	inline GenericCollLseg& operator = 
//		( const GenericCollLseg& to_copy )
//	{
//		end_points = to_copy.end_points;
//		
//		return *this;
//	}
//	
//	bool intersects( const GenericCollLseg& to_check, 
//		vec2_f24p8* ret=NULL ) const __attribute__((_IWRAM_CODE));
//	
//} __attribute__((_ALIGN4));


class CollLsegExtras
{
protected:		// functions
	static bool collinear_lsegs_intersect( const Fixed24p8& a_0, 
		const Fixed24p8& a_1, const Fixed24p8& b_0, const Fixed24p8& b_1 );
	
	friend class HorizCollLseg;
	friend class VertCollLseg;
	
} __attribute__((_ALIGN4));



// Horizontal line segment
class HorizCollLseg
{
protected:		// variables
	vec2_f24p8 internal_left_pt;
	Fixed24p8 internal_length;
	
public:		// functions
	inline HorizCollLseg()
	{
	}
	inline HorizCollLseg( const vec2_f24p8& s_left_pt, 
		const Fixed24p8& s_length ) : internal_left_pt(s_left_pt),
		internal_length(s_length)
	{
	}
	inline HorizCollLseg( const vec2_s32& s_left_pt, 
		const Fixed24p8& s_length )
		: internal_left_pt( make_f24p8(s_left_pt.x), 
		make_f24p8(s_left_pt.y) ), internal_length(s_length)
	{
	}
	inline HorizCollLseg( const HorizCollLseg& to_copy )
	{
		*this = to_copy;
	}
	
	inline HorizCollLseg& operator = ( const HorizCollLseg& to_copy )
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
	inline Fixed24p8& length()
	{
		return internal_length;
	}
	inline const Fixed24p8& length() const
	{
		return internal_length;
	}
	inline const vec2_f24p8 right_pt() const
	{
		return left_pt() + vec2_f24p8( length(), make_f24p8(0) );
	}
	
	inline bool intersects( const HorizCollLseg& to_check ) const
	{
		if ( left_pt().y == to_check.left_pt().y )
		{
			return CollLsegExtras::collinear_lsegs_intersect
				( left_pt().x, right_pt().x, to_check.left_pt().x, 
				to_check.right_pt().x );
		}
		
		return false;
	}
	//inline bool intersects( const VertCollLseg& to_check ) const;
	
} __attribute__((_ALIGN4));


class VertCollLseg
{
protected:		// variables
	vec2_f24p8 internal_top_pt;
	Fixed24p8 internal_length;
	
public:		// functions
	inline VertCollLseg()
	{
	}
	inline VertCollLseg( const vec2_f24p8& s_top_pt, 
		const Fixed24p8& s_length ) : internal_top_pt(s_top_pt),
		internal_length(s_length)
	{
	}
	inline VertCollLseg( const vec2_s32& s_top_pt, 
		const Fixed24p8& s_length )
		: internal_top_pt( make_f24p8(s_top_pt.x), 
		make_f24p8(s_top_pt.y) ), internal_length(s_length)
	{
	}
	inline VertCollLseg( const VertCollLseg& to_copy )
	{
		*this = to_copy;
	}
	
	inline VertCollLseg& operator = ( const VertCollLseg& to_copy )
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
	inline Fixed24p8& length()
	{
		return internal_length;
	}
	inline const Fixed24p8& length() const
	{
		return internal_length;
	}
	inline const vec2_f24p8 bot_pt() const
	{
		return top_pt() + vec2_f24p8( make_f24p8(0), length() );
	}
	
	//inline bool intersects( const HorizCollLseg& to_check ) const
	//{
	//	return to_check.intersects(*this);
	//}
	inline bool intersects( const VertCollLseg& to_check ) const
	{
		if ( top_pt().x == to_check.top_pt().x )
		{
			return CollLsegExtras::collinear_lsegs_intersect( top_pt().x,
				bot_pt().x, to_check.top_pt().x, to_check.bot_pt().x );
		}
		
		return false;
	}
	
} __attribute__((_ALIGN4));



//inline bool HorizCollLseg::intersects( const VertCollLseg& to_check ) 
//	const
//{
//	return GenericCollLseg( left_pt(), right_pt() ).intersects
//		( GenericCollLseg( to_check.top_pt(), to_check.bot_pt() ) );
//}




#endif		// coll_lseg_classes_hpp
