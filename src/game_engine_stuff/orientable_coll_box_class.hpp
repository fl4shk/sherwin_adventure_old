// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
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


#ifndef orientable_coll_box_class_hpp
#define orientable_coll_box_class_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "fixed_classes.hpp"

#include "vec2_class.hpp"
#include "trigonometry_funcs.hpp"


//// The positive y axis Is assumed To point downward, which Is why the
//// sin() function calls have or don't have a negative sign.
//inline void create_clockwise_rotation_mat2x2d
//	(double angle_in_degrees)
//{
//	data_11 = data_22 = cos(deg_to_rad(angle_in_degrees));
//	data_12 = -sin(deg_to_rad(angle_in_degrees));
//	data_21 = -data_12;
//}
//
//inline vec2d operator * (const vec2d& the_column_vec2d)
//{
//	vec2d ret;
//	
//	ret.x = (data_11 * the_column_vec2d.x) 
//		+ (data_12 * the_column_vec2d.y);
//	ret.y = (data_21 * the_column_vec2d.x) 
//		+ (data_22 * the_column_vec2d.y);
//	
//	return ret;
//}

//class OrientableCollBox
//{
//public:		// enums
//	enum origin_corner { oc_lt, oc_rt, oc_lb, oc_rb }
//		__attribute__((_ALIGN4));
//	
//protected:		// variables
//	origin_corner the_origin_corner;
//	u32 angle_in_degrees;
//	
//public:		// variables
//	//static constexpr double max_angle = 90.0f;
//	
//	// regular_pos Is the position of the top left corner of the
//	// OrientableCollBox when it Is neither rotated nor
//	// reflected about an axis.
//	vec2_f24p8 regular_pos;
//	
//	vec2_f24p8 size_2d;
//	
//public:		// functions
//	inline OrientableCollBox() 
//		: the_origin_corner(oc_lt), angle_in_degrees(0),
//		regular_pos({ {0}, {0} }), size_2d({ {0}, {0} })
//	{
//	}
//	
//	inline OrientableCollBox
//		(const vec2_f24p8& s_regular_pos, 
//		const vec2_f24p8& s_size_2d) : the_origin_corner(oc_lt),
//		angle_in_degrees(0), regular_pos(s_regular_pos),
//		size_2d(s_size_2d)
//	{
//	}
//	
//	inline OrientableCollBox
//		(origin_corner s_the_origin_corner, u32 s_angle_in_degrees,
//		const vec2_f24p8& s_regular_pos, const vec2_f24p8& s_size_2d)
//	{
//		the_origin_corner = s_the_origin_corner;
//		set_angle_in_degrees(s_angle_in_degrees);
//		regular_pos = s_regular_pos;
//		size_2d = s_size_2d;
//	}
//	
//	
//	inline origin_corner get_origin_corner() const
//	{
//		return the_origin_corner;
//	}
//	inline void set_origin_corner(origin_corner n_the_origin_corner)
//	{
//		the_origin_corner = n_the_origin_corner;
//	}
//	
//	inline u32 get_angle_in_degrees() const
//	{
//		return angle_in_degrees;
//	}
//	inline void set_angle_in_degrees(u32 n_angle_in_degrees)
//	{
//		angle_in_degrees = n_angle_in_degrees;
//	}
//	
//	
//	inline vec2_f24p8 get_lt_corner_in_local_coords() const
//	{
//		if (the_origin_corner == oc_lt)
//		{
//			return (vec2_f24p8){ {0}, {0} };
//		}
//		else if (the_origin_corner == oc_rt)
//		{
//			return (vec2_f24p8){ -size_2d.x, {0} };
//		}
//		else if (the_origin_corner == oc_lb)
//		{
//			return (vec2_f24p8){ {0}, -size_2d.y };
//		}
//		else if (the_origin_corner == oc_rb)
//		{
//			
//		}
//	}
//	inline vec2_f24p8 get_rt_corner_in_local_coords() const
//	{
//		if (the_origin_corner == oc_lt)
//		{
//			return (vec2_f24p8){ size_2d.x, {0} };
//		}
//	}
//	inline vec2_f24p8 get_lb_corner_in_local_coords() const
//	{
//		if (the_origin_corner == oc_lt)
//		{
//			return (vec2_f24p8){ {0}, size_2d.y };
//		}
//	}
//	inline vec2_f24p8 get_rb_corner_in_local_coords() const
//	{
//		if (the_origin_corner == oc_lt)
//		{
//			return (vec2_f24p8){ size_2d.x, size_2d.y };
//		}
//	}
//	
//	
//	inline vec2_f24p8 get_lt_corner_in_world_coords() const
//	{
//		return regular_pos;
//	}
//	inline vec2_f24p8 get_rt_corner_in_world_coords() const
//	{
//		return convert_point_in_local_coords_to_world_coords
//			(get_rt_corner_in_local_coords());
//	}
//	inline vec2_f24p8 get_lb_corner_in_world_coords() const
//	{
//		return convert_point_in_local_coords_to_world_coords
//			(get_lb_corner_in_local_coords());
//	}
//	inline vec2_f24p8 get_rb_corner_in_world_coords() const
//	{
//		return convert_point_in_local_coords_to_world_coords
//			(get_rb_corner_in_local_coords());
//	}
//	
//	
//	// Convert from world coords To local coords.
//	inline vec2_f24p8 convert_point_to_local_coords
//		(const vec2_f24p8& point_in_world_coords) const
//	{
//		// This subtraction Is the key To allowing rotations about corners
//		// other than the top-left corner.
//		//vec2_f24p8 ret = { point_in_world_coords.x - regular_pos.x,
//		//	point_in_world_coords.y - regular_pos.y };
//		vec2_f24p8 ret; 
//		
//		= point_in_world_coords - regular_pos;
//		
//		
//		// Create a 2x2 rotation matrix.
//		static constexpr u32 mat2x2_arr_size = 4;
//		Fixed8p8 the_rotation_mat2x2_arr[mat2x2_arr_size];
//		
//		Fixed8p8& data_11 = the_rotation_mat2x2_arr[0];
//		Fixed8p8& data_12 = the_rotation_mat2x2_arr[1];
//		Fixed8p8& data_21 = the_rotation_mat2x2_arr[2];
//		Fixed8p8& data_22 = the_rotation_mat2x2_arr[3];
//		
//		data_11 = data_22 = lut_cos_f8p8(angle_in_degrees);
//		data_12 = -lut_sin_f8p8(angle_in_degrees);
//		data_21 = data_12;
//		
//		
//		// Unfortunately, some precision Is lost from these multiplication
//		// operations.
//		
//		//ret = the_rotation_mat2x2 * ret;
//		//ret.x = (ret.x * data_11) + (ret.y * data_12);
//		//ret.y = (ret.x * data_21) + (ret.y * data_22);
//		ret.x = ret.x.guaranteed_f24p8_by_f8p8_multiplication(data_11) 
//			+ ret.y.guaranteed_f24p8_by_f8p8_multiplication(data_12);
//		ret.y = ret.x.guaranteed_f24p8_by_f8p8_multiplication(data_21) 
//			+ ret.y.guaranteed_f24p8_by_f8p8_multiplication(data_22);
//		
//		if (the_reflection_type == rt_none)
//		{
//		}
//		else if (the_reflection_type == rt_horiz)
//		{
//			//ret.horiz_reflect();
//			ret.y = -ret.y;
//		}
//		else if (the_reflection_type == rt_vert)
//		{
//			//ret.vert_reflect();
//			ret.x = -ret.x;
//		}
//		else if (the_reflection_type == rt_horiz_vert)
//		{
//			//ret.horiz_vert_reflect();
//			ret.y = -ret.y;
//			ret.x = -ret.x;
//		}
//		
//		return ret;
//	}
//	
//	// Convert from local coords To world coords.
//	inline vec2_f24p8 convert_point_in_local_coords_to_world_coords
//		(const vec2_f24p8& point_in_local_coords) const
//	{
//		vec2_f24p8 ret = point_in_local_coords;
//		
//		if (the_reflection_type == rt_none)
//		{
//		}
//		else if (the_reflection_type == rt_horiz)
//		{
//			//ret.horiz_reflect();
//			ret.y = -ret.y;
//		}
//		else if (the_reflection_type == rt_vert)
//		{
//			//ret.vert_reflect();
//			ret.x = -ret.x;
//		}
//		else if (the_reflection_type == rt_horiz_vert)
//		{
//			//ret.horiz_vert_reflect();
//			ret.y = -ret.y;
//			ret.x = -ret.x;
//		}
//		
//		static constexpr u32 mat2x2_arr_size = 4;
//		Fixed8p8 the_rotation_mat2x2_arr[mat2x2_arr_size];
//		
//		Fixed8p8& data_11 = the_rotation_mat2x2_arr[0];
//		Fixed8p8& data_12 = the_rotation_mat2x2_arr[1];
//		Fixed8p8& data_21 = the_rotation_mat2x2_arr[2];
//		Fixed8p8& data_22 = the_rotation_mat2x2_arr[3];
//		
//		// cos(-x) = cos(x)
//		data_11 = data_22 = lut_cos_f8p8(angle_in_degrees);
//		
//		// sin(-x) = -sin(x)
//		data_12 = lut_sin_f8p8(angle_in_degrees);
//		data_21 = -data_12;
//		
//		// Unfortunately, some precision Is lost from these multiplication
//		// operations.
//		//ret = the_rotation_mat2x2 * ret;
//		ret.x = ret.x.guaranteed_f24p8_by_f8p8_multiplication(data_11) 
//			+ ret.y.guaranteed_f24p8_by_f8p8_multiplication(data_12);
//		ret.y = ret.x.guaranteed_f24p8_by_f8p8_multiplication(data_21) 
//			+ ret.y.guaranteed_f24p8_by_f8p8_multiplication(data_22);
//		
//		ret += regular_pos;
//		
//		return ret;
//	}
//	
//	inline int Contains(const vec2_f24p8& point_in_world_coords) const
//	{
//		vec2_f24p8 point_in_local_coords = convert_point_to_local_coords
//			(point_in_world_coords);
//		
//		if (point_in_local_coords.x >= (Fixed24p8){0}
//			&& point_in_local_coords.x <= size_2d.x
//			&& point_in_local_coords.y >= (Fixed24p8){0}
//			&& point_in_local_coords.y <= size_2d.y)
//		{
//			return true;
//		}
//		
//		return false;
//	}
//	
//} __attribute__((_ALIGN4));


class OrientableCollBox
{
public:		// enums
	enum origin_corner { oc_lt, oc_rt, oc_lb, oc_rb }
		__attribute__((_ALIGN4));
	
protected:		// variables
	// the_origin_corner Is protected So That it Can only be changed by
	// set_origin_corner(), which updates origin_corner_pos as needed.
	origin_corner the_origin_corner;
	u32 angle_in_degrees;
	
public:		// variables
	//static constexpr double max_angle = 90.0f;
	
	// origin_corner_pos Is the position of the origin corner of the
	// OrientableCollBox when it Is not rotated.
	vec2_f24p8 origin_corner_pos;
	
	vec2_f24p8 size_2d;
	
public:		// functions
	inline OrientableCollBox() : the_origin_corner(oc_lt), 
		angle_in_degrees(0), origin_corner_pos({ {0}, {0} }), 
		size_2d({ {0}, {0} })
	{
	}
	
	inline OrientableCollBox(const vec2_f24p8& s_origin_corner_pos, 
		const vec2_f24p8& s_size_2d) : the_origin_corner(oc_lt),
		angle_in_degrees(0), origin_corner_pos(s_origin_corner_pos),
		size_2d(s_size_2d)
	{
	}
	
	inline OrientableCollBox(origin_corner s_the_origin_corner, 
		u32 s_angle_in_degrees, const vec2_f24p8& s_origin_corner_pos, 
		const vec2_f24p8& s_size_2d):
		the_origin_corner(s_the_origin_corner),
		angle_in_degrees(s_angle_in_degrees),
		origin_corner_pos(s_origin_corner_pos), size_2d(s_size_2d)
	{
	}
	
	
	inline origin_corner get_origin_corner() const
	{
		return the_origin_corner;
	}
	
	// This Is needed So That origin_corner_pos Can be properly updated
	inline void set_origin_corner
		(origin_corner n_the_origin_corner)
	{
		the_origin_corner = n_the_origin_corner;
		
		if (the_origin_corner == oc_lt)
		{
			origin_corner_pos = get_lt_corner_in_world_coords();
		}
		else if (the_origin_corner == oc_rt)
		{
			origin_corner_pos = get_rt_corner_in_world_coords();
		}
		else if (the_origin_corner == oc_rb)
		{
			origin_corner_pos = get_rb_corner_in_world_coords();
		}
		else //if (the_origin_corner == oc_lb)
		{
			origin_corner_pos = get_lb_corner_in_world_coords();
		}
	}
	
	
	inline u32 get_angle_in_degrees() const
	{
		return angle_in_degrees;
	}
	inline void set_angle_in_degrees(u32 n_angle_in_degrees)
	{
		angle_in_degrees = n_angle_in_degrees;
	}
	
	
	inline vec2_f24p8 get_lt_corner_in_local_coords() const
	{
		vec2_f24p8 ret = { {0}, {0} };
		
		if (the_origin_corner == oc_lt)
		{
		}
		else if (the_origin_corner == oc_rt)
		{
			ret.x -= size_2d.x;
		}
		else if (the_origin_corner == oc_rb)
		{
			ret.x -= size_2d.x;
			ret.y -= size_2d.y;
		}
		else //if (the_origin_corner == oc_lb)
		{
			ret.y -= size_2d.y;
		}
		
		return ret;
		
	}
	inline vec2_f24p8 get_rt_corner_in_local_coords() const
	{
		vec2_f24p8 ret = { size_2d.x, {0} };
		
		if (the_origin_corner == oc_lt)
		{
		}
		else if (the_origin_corner == oc_rt)
		{
			ret.x -= size_2d.x;
		}
		else if (the_origin_corner == oc_rb)
		{
			ret.x -= size_2d.x;
			ret.y -= size_2d.y;
		}
		else //if (the_origin_corner == oc_lb)
		{
			ret.y -= size_2d.y;
		}
		
		return ret;
	}
	inline vec2_f24p8 get_rb_corner_in_local_coords() const
	{
		vec2_f24p8 ret = { size_2d.x, size_2d.y };
		
		if (the_origin_corner == oc_lt)
		{
		}
		else if (the_origin_corner == oc_rt)
		{
			ret.x -= size_2d.x;
		}
		else if (the_origin_corner == oc_rb)
		{
			ret.x -= size_2d.x;
			ret.y -= size_2d.y;
		}
		else //if (the_origin_corner == oc_lb)
		{
			ret.y -= size_2d.y;
		}
		
		return ret;
	}
	inline vec2_f24p8 get_lb_corner_in_local_coords() const
	{
		vec2_f24p8 ret = { {0}, size_2d.y };
		
		if (the_origin_corner == oc_lt)
		{
		}
		else if (the_origin_corner == oc_rt)
		{
			ret.x -= size_2d.x;
		}
		else if (the_origin_corner == oc_rb)
		{
			ret.x -= size_2d.x;
			ret.y -= size_2d.y;
		}
		else //if (the_origin_corner == oc_lb)
		{
			ret.y -= size_2d.y;
		}
		
		return ret;
	}
	
	
	inline vec2_f24p8 get_lt_corner_in_world_coords() const
	{
		return convert_point_from_local_coords_to_world_coords
			(get_lt_corner_in_local_coords());
	}
	inline vec2_f24p8 get_rt_corner_in_world_coords() const
	{
		return convert_point_from_local_coords_to_world_coords
			(get_rt_corner_in_local_coords());
	}
	inline vec2_f24p8 get_rb_corner_in_world_coords() const
	{
		return convert_point_from_local_coords_to_world_coords
			(get_rb_corner_in_local_coords());
	}
	inline vec2_f24p8 get_lb_corner_in_world_coords() const
	{
		return convert_point_from_local_coords_to_world_coords
			(get_lb_corner_in_local_coords());
	}
	
	
	// Convert from world coords To local coords.
	inline vec2_f24p8 convert_point_to_local_coords
		(const vec2_f24p8& point_in_world_coords) const
	{
		// This subtraction Is the key To allowing rotations about corners
		// other than the top-left corner.
		//vec2_f24p8 ret = { point_in_world_coords.x - origin_corner_pos.x,
		//	point_in_world_coords.y - origin_corner_pos.y };
		vec2_f24p8 ret = point_in_world_coords - origin_corner_pos;
		
		//mat2x2d the_rotation_mat2x2d;
		//the_rotation_mat2x2d.create_clockwise_rotation_mat2x2d
		//	(-angle_in_degrees);
		//
		//ret = the_rotation_mat2x2d * ret;
		
		
		// Create a 2x2 rotation matrix.
		
		static constexpr u32 mat2x2_arr_size = 4;
		Fixed8p8 the_rotation_mat2x2_arr[mat2x2_arr_size];
		
		Fixed8p8& data_11 = the_rotation_mat2x2_arr[0];
		Fixed8p8& data_12 = the_rotation_mat2x2_arr[1];
		Fixed8p8& data_21 = the_rotation_mat2x2_arr[2];
		Fixed8p8& data_22 = the_rotation_mat2x2_arr[3];
		
		// cos(-x) = cos(x)
		data_11 = data_22 = lut_cos_f8p8(angle_in_degrees);
		
		// sin(-x) = -sin(x)
		data_12 = lut_sin_f8p8(angle_in_degrees);
		data_21 = -data_12;
		
		// Unfortunately, some precision Is lost from these multiplication
		// operations.
		
		//ret = the_rotation_mat2x2 * ret;
		//ret.x = (ret.x * data_11) + (ret.y * data_12);
		//ret.y = (ret.x * data_21) + (ret.y * data_22);
		ret.x = ret.x.guaranteed_f24p8_by_f8p8_multiplication(data_11) 
			+ ret.y.guaranteed_f24p8_by_f8p8_multiplication(data_12);
		ret.y = ret.x.guaranteed_f24p8_by_f8p8_multiplication(data_21) 
			+ ret.y.guaranteed_f24p8_by_f8p8_multiplication(data_22);
		
		
		return ret;
	}
	
	// Convert from local coords To world coords.
	inline vec2_f24p8 convert_point_from_local_coords_to_world_coords
		(const vec2_f24p8& point_in_local_coords) const
	{
		vec2_f24p8 ret = point_in_local_coords;
		
		//mat2x2d the_rotation_mat2x2d;
		//the_rotation_mat2x2d.create_clockwise_rotation_mat2x2d
		//	(-angle_in_degrees);
		//
		//ret = the_rotation_mat2x2d * ret;
		
		
		// Create a 2x2 rotation matrix.
		static constexpr u32 mat2x2_arr_size = 4;
		Fixed8p8 the_rotation_mat2x2_arr[mat2x2_arr_size];
		
		Fixed8p8& data_11 = the_rotation_mat2x2_arr[0];
		Fixed8p8& data_12 = the_rotation_mat2x2_arr[1];
		Fixed8p8& data_21 = the_rotation_mat2x2_arr[2];
		Fixed8p8& data_22 = the_rotation_mat2x2_arr[3];
		
		data_11 = data_22 = lut_cos_f8p8(angle_in_degrees);
		data_12 = -lut_sin_f8p8(angle_in_degrees);
		data_21 = -data_12;
		
		// Unfortunately, some precision Is lost from these multiplication
		// operations.
		//ret = the_rotation_mat2x2 * ret;
		ret.x = ret.x.guaranteed_f24p8_by_f8p8_multiplication(data_11) 
			+ ret.y.guaranteed_f24p8_by_f8p8_multiplication(data_12);
		ret.y = ret.x.guaranteed_f24p8_by_f8p8_multiplication(data_21) 
			+ ret.y.guaranteed_f24p8_by_f8p8_multiplication(data_22);
		
		
		
		ret = { ret.x + origin_corner_pos.x, ret.y + origin_corner_pos.y };
		
		return ret;
	}
	
	
	inline bool Contains(const vec2_f24p8& point_in_world_coords) const
	{
		vec2_f24p8 point_in_local_coords = convert_point_to_local_coords
			(point_in_world_coords);
		
		vec2_f24p8 lt_corner_in_local_coords 
			= get_lt_corner_in_local_coords();
		
		if (point_in_local_coords.x >= lt_corner_in_local_coords.x
			&& point_in_local_coords.x <= (lt_corner_in_local_coords.x 
			+ size_2d.x)
			&& point_in_local_coords.y >= lt_corner_in_local_coords.y
			&& point_in_local_coords.y <= (lt_corner_in_local_coords.y
			+ size_2d.y))
		{
			return true;
		}
		
		return false;
	}
	
	// The separating axis theorem Is being used for this function.
	inline bool intersects_now(const OrientableCollBox& other)
	{
		static constexpr u32 num_corners = 4, num_edges = 4, num_axes = 4;
		
		// this (world coords)
		array<vec2_f24p8, num_corners > corners; 
		array<vec2_f24p8, num_edges > edges; 
		array<vec2_f24p8, num_axes > axes;
		
		vec2_f24p8& lt_corner = corners[0], 
			& rt_corner = corners[1], 
			& rb_corner = corners[2], 
			& lb_corner = corners[3];
		vec2_f24p8& lt_rt_edge = edges[0], 
			& rt_rb_edge = edges[1], 
			& rb_lb_edge = edges[2], 
			& lb_lt_edge = edges[3];
		vec2_f24p8& lt_rt_axis = axes[0], 
			& rt_rb_axis = axes[1], 
			& rb_lb_axis = axes[2], 
			& lb_lt_axis = axes[3];
		
		lt_corner = get_lt_corner_in_world_coords();
		rt_corner = get_rt_corner_in_world_coords();
		rb_corner = get_rb_corner_in_world_coords();
		lb_corner = get_lb_corner_in_world_coords();
		
		lt_rt_edge = (lt_corner - rt_corner);
		rt_rb_edge = (rt_corner - rb_corner);
		rb_lb_edge = (rb_corner - lb_corner);
		lb_lt_edge = (lb_corner - lt_corner);
		
		// These four vectors are NOT of unit length.  They just point in
		// the direction in which the normal vector would point.
		lt_rt_axis = lt_rt_edge.perp();
		rt_rb_axis = rt_rb_edge.perp();
		rb_lb_axis = rb_lb_edge.perp();
		lb_lt_axis = lb_lt_edge.perp();
		
		
		
		// other (world coords)
		array<vec2_f24p8, num_corners > other_corners; 
		array<vec2_f24p8, num_edges > other_edges; 
		array<vec2_f24p8, num_axes > other_axes;
		
		vec2_f24p8& other_lt_corner = other_corners[0], 
			& other_rt_corner = other_corners[1], 
			& other_rb_corner = other_corners[2], 
			& other_lb_corner = other_corners[3];
		vec2_f24p8& other_lt_rt_edge = other_edges[0], 
			& other_rt_rb_edge = other_edges[1], 
			& other_rb_lb_edge = other_edges[2], 
			& other_lb_lt_edge = other_edges[3];
		vec2_f24p8& other_lt_rt_axis = other_axes[0], 
			& other_rt_rb_axis = other_axes[1], 
			& other_rb_lb_axis = other_axes[2], 
			& other_lb_lt_axis = other_axes[3];
		
		other_lt_corner = other.get_lt_corner_in_world_coords();
		other_rt_corner = other.get_rt_corner_in_world_coords();
		other_rb_corner = other.get_rb_corner_in_world_coords();
		other_lb_corner = other.get_lb_corner_in_world_coords();
		
		other_lt_rt_edge = (other_lt_corner - other_rt_corner);
		other_rt_rb_edge = (other_rt_corner - other_rb_corner);
		other_rb_lb_edge = (other_rb_corner - other_lb_corner);
		other_lb_lt_edge = (other_lb_corner - other_lt_corner);
		
		// These four vectors are NOT of unit length.  They just point in
		// the direction in which the normal vector would point.
		other_lt_rt_axis = other_lt_rt_edge.perp();
		other_rt_rb_axis = other_rt_rb_edge.perp();
		other_rb_lb_axis = other_rb_lb_edge.perp();
		other_lb_lt_axis = other_lb_lt_edge.perp();
		
		
		
		// Note:  The axis must be normalized To get an accurate
		// projection.
		auto project = [&](const vec2_f24p8& axis, Fixed24p8& min, 
			Fixed24p8& max, 
			const array<vec2_f24p8, num_corners >& corners_arr) -> void
		{
			min = max = axis.dot_prod(corners_arr.at(0));
			
			for (u32 i=1; i<corners_arr.size(); ++i)
			{
				Fixed24p8 p = axis.dot_prod(corners_arr.at(i));
				
				if (p < min)
				{
					min = p;
				}
				else if (p > max)
				{
					max = p;
				}
			}
		};
		
		auto projections_overlap = [&](Fixed24p8 min, Fixed24p8 max, 
			Fixed24p8 other_min, Fixed24p8 other_max) -> bool
		{
			// First, check whether other_min Is between min and max.
			if (min <= other_min && other_min <= max)
			{
				return true;
			}
			
			// Next, check whether other_max Is between min and max.
			if (min <= other_max && other_max <= max)
			{
				return true;
			}
			
			// Next, check whether min Is between other_min and other_max.
			if (other_min <= min && min <= other_max)
			{
				return true;
			}
			
			// Last, check whether max Is between other_min and other_max.
			if (other_min <= max && max <= other_max)
			{
				return true;
			}
			
			return false;
		};
		
		// loop over axes
		for (const vec2_f24p8& axis : axes)
		{
			Fixed24p8 min, max, other_min, other_max;
			
			// Project both rectangles onto the axis.
			project(axis, min, max, corners);
			project(axis, other_min, other_max, other_corners);
			
			// Do the projections overlap?  If not, then the rectangles
			// definitely don't overlap.
			if (!projections_overlap(min, max, other_min, other_max))
			{
				return false;
			}
		}
		
		// loop over other_axes
		for (const vec2_f24p8& other_axis : other_axes)
		{
			Fixed24p8 min, max, other_min, other_max;
			
			// Project both rectangles onto the axis.
			project(other_axis, min, max, corners);
			project(other_axis, other_min, other_max, other_corners);
			
			// Do the projections overlap?  If not, then the rectangles
			// definitely don't overlap.
			if (!projections_overlap(min, max, other_min, other_max))
			{
				return false;
			}
		}
		
		
		return true;
	}
};


#endif		// orientable_coll_box_class_hpp
