// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#ifndef orientable_reflectable_coll_box_class_hpp
#define orientable_reflectable_coll_box_class_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "fixed_classes.hpp"

#include "vec2_class.hpp"
#include "trigonometry_funcs.hpp"


//class oriented_coll_box
//{
//public:		// enums
//	enum reflection_type { rt_none, rt_horiz, rt_vert, rt_horiz_vert }
//		__attribute__((_align4));
//	
//protected:		// variables
//	reflection_type the_reflection_type;
//	u32 angle;
//	
//public:		// variables
//	static constexpr u32 max_angle = 0x4000;
//	
//	// regular_pos is the position of the top left corner of the
//	// oriented_coll_box when it is neither rotated nor reflected
//	// about an axis.  Also, regular_pos is used when 
//	vec2_f24p8 regular_pos;
//	
//	vec2_f24p8 size;
//	
//public:		// functions
//	
//	inline u32 get_angle() const
//	{
//		return angle;
//	}
//	inline void set_angle( u32 n_angle )
//	{
//		angle = n_angle;
//	}
//	
//	
//} __attribute__((_align4));

//// The positive y axis is assumed to point downward, which is why the
//// sin() function calls have or don't have a negative sign.
//inline void create_clockwise_rotation_mat2x2d
//	( double angle_in_degrees )
//{
//	data_11 = data_22 = cos( deg_to_rad(angle_in_degrees) );
//	data_12 = -sin( deg_to_rad(angle_in_degrees) );
//	data_21 = -data_12;
//}
//
//inline vec2d operator * ( const vec2d& the_column_vec2d )
//{
//	vec2d ret;
//	
//	ret.x = ( data_11 * the_column_vec2d.x ) 
//		+ ( data_12 * the_column_vec2d.y );
//	ret.y = ( data_21 * the_column_vec2d.x ) 
//		+ ( data_22 * the_column_vec2d.y );
//	
//	return ret;
//}

class orientable_reflectable_coll_box
{
public:		// enums
	enum reflection_type { rt_none, rt_horiz, rt_vert, rt_horiz_vert }
		__attribute__((_align4));
	
protected:		// variables
	reflection_type the_reflection_type;
	u32 angle_in_degrees;
	
public:		// variables
	//static constexpr double max_angle = 90.0f;
	
	// regular_pos is the position of the top left corner of the
	// orientable_reflectable_coll_box when it is neither rotated nor
	// reflected about an axis.
	vec2_f24p8 regular_pos;
	
	vec2_f24p8 size_2d;
	
public:		// functions
	inline orientable_reflectable_coll_box() 
		: the_reflection_type(rt_none), angle_in_degrees(0),
		regular_pos({ {0}, {0} }), size_2d({ {0}, {0} })
	{
	}
	
	inline orientable_reflectable_coll_box
		( const vec2_f24p8& s_regular_pos, 
		const vec2_f24p8& s_size_2d ) : the_reflection_type(rt_none),
		angle_in_degrees(0.0f), regular_pos(s_regular_pos),
		size_2d(s_size_2d)
	{
	}
	
	inline orientable_reflectable_coll_box
		( reflection_type s_the_reflection_type, u32 s_angle_in_degrees,
		const vec2_f24p8& s_regular_pos, const vec2_f24p8& s_size_2d )
	{
		the_reflection_type = s_the_reflection_type;
		set_angle_in_degrees(s_angle_in_degrees);
		regular_pos = s_regular_pos;
		size_2d = s_size_2d;
	}
	
	
	inline reflection_type get_reflection_type() const
	{
		return the_reflection_type;
	}
	inline void set_reflection_type
		( reflection_type n_the_reflection_type )
	{
		the_reflection_type = n_the_reflection_type;
	}
	inline void reset_reflection_type()
	{
		// This function MIGHT need to be made more complicated in the
		// future.
		the_reflection_type = rt_none;
	}
	
	// This does a "hard" enable.
	inline void enable_horiz_reflection()
	{
		if ( the_reflection_type == rt_none )
		{
			the_reflection_type = rt_horiz;
		}
		else if ( the_reflection_type == rt_vert )
		{
			the_reflection_type = rt_horiz_vert;
		}
	}
	
	// This does a "hard" enable.
	inline void enable_vert_reflection()
	{
		if ( the_reflection_type == rt_none )
		{
			the_reflection_type = rt_vert;
		}
		else if ( the_reflection_type == rt_horiz )
		{
			the_reflection_type = rt_horiz_vert;
		}
	}
	
	// This does a "hard" disable.
	inline void disable_horiz_reflection()
	{
		if ( the_reflection_type == rt_horiz )
		{
			the_reflection_type = rt_none;
		}
		else if ( the_reflection_type == rt_horiz_vert )
		{
			the_reflection_type = rt_vert;
		}
	}
	
	// This does a "hard" disable.
	inline void disable_vert_reflection()
	{
		if ( the_reflection_type == rt_vert )
		{
			the_reflection_type = rt_none;
		}
		else if ( the_reflection_type == rt_horiz_vert )
		{
			the_reflection_type = rt_horiz;
		}
	}
	
	
	inline u32 get_angle_in_degrees() const
	{
		return angle_in_degrees;
	}
	inline void set_angle_in_degrees( u32 n_angle_in_degrees )
	{
		angle_in_degrees = n_angle_in_degrees;
	}
	
	
	inline vec2_f24p8 get_lt_corner_in_local_coords() const
	{
		return (vec2_f24p8){ {0}, {0} };
	}
	inline vec2_f24p8 get_rt_corner_in_local_coords() const
	{
		return (vec2_f24p8){ size_2d.x, {0} };
	}
	inline vec2_f24p8 get_lb_corner_in_local_coords() const
	{
		return (vec2_f24p8){ {0}, size_2d.y };
	}
	inline vec2_f24p8 get_rb_corner_in_local_coords() const
	{
		return (vec2_f24p8){ size_2d.x, size_2d.y };
	}
	
	
	inline vec2_f24p8 get_lt_corner_in_world_coords() const
	{
		return regular_pos;
	}
	inline vec2_f24p8 get_rt_corner_in_world_coords() const
	{
		return convert_point_in_local_coords_to_world_coords
			(get_rt_corner_in_local_coords());
	}
	inline vec2_f24p8 get_lb_corner_in_world_coords() const
	{
		return convert_point_in_local_coords_to_world_coords
			(get_lb_corner_in_local_coords());
	}
	inline vec2_f24p8 get_rb_corner_in_world_coords() const
	{
		return convert_point_in_local_coords_to_world_coords
			(get_rb_corner_in_local_coords());
	}
	
	
	// Convert from world coords to local coords.
	inline vec2_f24p8 convert_point_to_local_coords
		( const vec2_f24p8& point_in_world_coords ) const
	{
		// This subtraction is the key to allowing rotations about corners
		// other than the top-left corner.
		//vec2_f24p8 ret = { point_in_world_coords.x - regular_pos.x,
		//	point_in_world_coords.y - regular_pos.y };
		vec2_f24p8 ret = point_in_world_coords - regular_pos;
		
		
		// Create a 2x2 rotation matrix.
		static constexpr u32 mat2x2_arr_size = 4;
		fixed8p8 the_rotation_mat2x2_arr[mat2x2_arr_size];
		
		fixed8p8& data_11 = the_rotation_mat2x2_arr[0];
		fixed8p8& data_12 = the_rotation_mat2x2_arr[1];
		fixed8p8& data_21 = the_rotation_mat2x2_arr[2];
		fixed8p8& data_22 = the_rotation_mat2x2_arr[3];
		
		data_11 = data_22 = lut_cos_f8p8(angle_in_degrees);
		data_12 = -lut_sin_f8p8(angle_in_degrees);
		data_21 = data_12;
		
		//ret = the_rotation_mat2x2 * ret;
		
		ret.x = ( data_11 * ret.x ) + ( data_12 * ret.y );
		ret.y = ( data_21 * ret.x ) + ( data_22 * ret.y );
		
		if ( the_reflection_type == rt_none )
		{
		}
		else if ( the_reflection_type == rt_horiz )
		{
			//ret.horiz_reflect();
			ret.y = -ret.y;
		}
		else if ( the_reflection_type == rt_vert )
		{
			//ret.vert_reflect();
			ret.x = -ret.x;
		}
		else if ( the_reflection_type == rt_horiz_vert )
		{
			//ret.horiz_vert_reflect();
			ret.y = -ret.y;
			ret.x = -ret.x;
		}
		
		return ret;
	}
	
	// Convert from local coords to world coords.
	inline vec2_f24p8 convert_point_in_local_coords_to_world_coords
		( const vec2_f24p8& point_in_local_coords ) const
	{
		vec2_f24p8 ret = point_in_local_coords;
		
		if ( the_reflection_type == rt_none )
		{
		}
		else if ( the_reflection_type == rt_horiz )
		{
			//ret.horiz_reflect();
			ret.y = -ret.y;
		}
		else if ( the_reflection_type == rt_vert )
		{
			//ret.vert_reflect();
			ret.x = -ret.x;
		}
		else if ( the_reflection_type == rt_horiz_vert )
		{
			//ret.horiz_vert_reflect();
			ret.y = -ret.y;
			ret.x = -ret.x;
		}
		
		static constexpr u32 mat2x2_arr_size = 4;
		fixed8p8 the_rotation_mat2x2_arr[mat2x2_arr_size];
		
		fixed8p8& data_11 = the_rotation_mat2x2_arr[0];
		fixed8p8& data_12 = the_rotation_mat2x2_arr[1];
		fixed8p8& data_21 = the_rotation_mat2x2_arr[2];
		fixed8p8& data_22 = the_rotation_mat2x2_arr[3];
		
		// cos(-x) = cos(x)
		data_11 = data_22 = lut_cos_f8p8(angle_in_degrees);
		
		// sin(-x) = -sin(x)
		data_12 = lut_sin_f8p8(angle_in_degrees);
		data_21 = -data_12;
		
		//ret = the_rotation_mat2x2 * ret;
		ret.x = ( data_11 * ret.x ) + ( data_12 * ret.y );
		ret.y = ( data_21 * ret.x ) + ( data_22 * ret.y );
		
		ret += regular_pos;
		
		return ret;
	}
	
	inline int contains( const vec2_f24p8& point_in_world_coords ) const
	{
		vec2_f24p8 point_in_local_coords = convert_point_to_local_coords
			(point_in_world_coords);
		
		if ( point_in_local_coords.x >= (fixed24p8){0}
			&& point_in_local_coords.x <= size_2d.x
			&& point_in_local_coords.y >= (fixed24p8){0}
			&& point_in_local_coords.y <= size_2d.y )
		{
			return true;
		}
		
		return false;
	}
	
} __attribute__((_align4));


#endif		// orientable_reflectable_coll_box_class_hpp
