// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
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


#ifndef coll_box_class_hpp
#define coll_box_class_hpp



#include "../general_utility_stuff/misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "../general_utility_stuff/fixed_classes.hpp"
//#include "level_wrapper_funcs.hpp"

#include "../general_utility_stuff/vec2_class.hpp"

class CollBox;

int coll_box_intersects_now( const CollBox& a, const CollBox& b )
	__attribute__((_IWRAM_CODE,_TARGET_ARM));
//int coll_box_intersects_now_2( const CollBox& a, const CollBox& b )
//	__attribute__((_IWRAM_CODE,_TARGET_ARM));
int coll_box_intersects_now_2( const CollBox& a, const CollBox& b );


class CollBox
{
public:		// variables
	
	// pos Is the position of the top left corner of the CollBox
	vec2_f24p8 pos;
	
	vec2_f24p8 size;
	
	// If this CollBox Is actually a hit_box, then strength > 0.
	u32 strength;
	
public:		// functions
	
	inline Fixed24p8 left() const
	{
		return pos.x;
	}
	
	inline Fixed24p8 right() const
	{
		return pos.x + size.x;
	}
	
	inline Fixed24p8 top() const
	{
		return pos.y;
	}
	
	inline Fixed24p8 bot() const
	{
		return pos.y + size.y;
	}
	
	inline Fixed24p8 half_width() const
	{
		return (Fixed24p8){ size.x.data >> 1 };
	}
	inline Fixed24p8 half_height() const
	{
		return (Fixed24p8){ size.y.data >> 1 };
	}
	inline vec2_f24p8 half_size() const
	{
		return vec2_f24p8( half_width(), half_height() );
	}
	
	inline Fixed24p8 get_x_center() const
	{
		s32 ret_data;
		
		ret_data = pos.x.data + ( size.x.data >> 1 );
		
		return (Fixed24p8){ ret_data };
	}
	
	inline Fixed24p8 get_y_center() const
	{
		s32 ret_data;
		
		ret_data = pos.y.data + ( size.y.data >> 1 );
		
		return (Fixed24p8){ ret_data };
	}
	
	inline int intersects_now( const CollBox& other )
	{
		return coll_box_intersects_now( *this, other );
	}
	
	inline int intersects_now_2( const CollBox& other )
	{
		return coll_box_intersects_now_2( *this, other );
	}
	
	int Contains( const vec2_f24p8& point ) __attribute__((_IWRAM_CODE));
	
	// Note:  This function doesn't check whether right_x > left_x, nor
	// whether bot_y > top_y.  That makes this function less safe than it
	// could have been.
	void set_side_coords( Fixed24p8 left_x, Fixed24p8 right_x,
		Fixed24p8 top_y, Fixed24p8 bot_y );
	
	void get_corners( vec2_f24p8& lt_corner, vec2_f24p8& rt_corner, 
		vec2_f24p8& rb_corner, vec2_f24p8& lb_corner );
	
	void get_block_coords_intersected_by_corners 
		( vec2_s32& lt_block_coord, vec2_s32& rt_block_coord,
		vec2_s32& rb_block_coord, vec2_s32& lb_block_coord );
	
	
	
} __attribute__((_ALIGN4));




#endif		// coll_box_class_hpp
