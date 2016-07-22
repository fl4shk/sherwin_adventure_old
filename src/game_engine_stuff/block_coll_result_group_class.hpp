// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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


#ifndef block_coll_result_group_class_hpp
#define block_coll_result_group_class_hpp

#include "range_funcs.hpp"
#include "block_stuff/block_stuff.hpp"

#include "coll_box_class.hpp"
#include "array_helper_class.hpp"

class block_coll_result
{
public:		// variables
	//vec2_s32 coord;
	//block_type type;
	block* the_block __attribute__((_align4));
	//block_behavior_type the_bbvt __attribute__((_align4));
	u32 the_bbvt __attribute__((_align4));
	
public:		// functions
	inline block_coll_result()
	{
	}
	//inline block_coll_result()
	//{
	//	memset( this, 0, sizeof(*this) );
	//}
	block_coll_result( const vec2_s32& s_coord );
	block_coll_result( const vec2_f24p8& s_coord_f24p8 );
	inline block_coll_result( const block_coll_result& to_copy )
	{
		*this = to_copy;
	}
	
	//inline block_coll_result& operator = 
	//	( const block_coll_result& to_copy )
	//{
	//	coord = to_copy.coord;
	//	the_block = to_copy.the_block;
	//	the_bbvt = to_copy.the_bbvt;
	//	
	//	return *this;
	//}
	
	inline block_type get_block_type() const
	{
		return the_block->get_block_type();
	}
	inline block_behavior_type get_bbvt() const
	{
		return (block_behavior_type)the_bbvt;
	}
	
} __attribute__((_align4));



class sprite;

class bcr_ptr_line;

class block_coll_result_group
{
public:		// constants
	// The maximum number of blocks intersected by a sprite, per dimension.
	// The value of ( 3, 3 ) corresponds to a 32x32 sprite.  Definitely
	// change these two values (among other things) if there is every any
	// infrastructure for sprites larger than 32x32 pixels.
	//const vec2_u32 block_coll_result_group::shared_max_size_2d( 3, 3 );
	static constexpr vec2_u32 max_size_2d = vec2_u32( 3, 3 );
	//static constexpr vec2_u32 max_size_2d = vec2_u32( 80, 80 );
	static constexpr u32 max_size = max_size_2d.x * max_size_2d.y;
	
protected:		// variables
	block_coll_result bcr_arr_2d_helper_data[max_size];
	
	vec2_s32 start_pos;
	
	vec2_s32 real_size_2d;
	
	bool moving_left, moving_right;
	
	static u32 temp_debug_thing;
	
public:		// variables
	array_2d_helper<block_coll_result> bcr_arr_2d_helper;
	
	
public:		// functions
	block_coll_result_group();
	block_coll_result_group( const coll_box& the_coll_box, 
		u32 s_moving_left, u32 s_moving_right );
	block_coll_result_group( const block_coll_result_group& to_copy );
	
	block_coll_result_group& operator = 
		( const block_coll_result_group& to_copy );
	
	
	inline block_coll_result& operator () ( u32 local_x, u32 local_y )
	{
		return data_at( local_x, local_y );
	}
	inline block_coll_result& operator () ( const vec2_u32& local_coord )
	{
		return data_at(local_coord);
	}
	inline block_coll_result& operator () ( const vec2_s32& local_coord )
	{
		return data_at(local_coord);
	}
	
	inline block_coll_result& data_at( u32 local_x, u32 local_y )
	{
		return bcr_arr_2d_helper.data_at( local_x, local_y );
	}
	inline block_coll_result& data_at( const vec2_u32& local_coord )
	{
		return bcr_arr_2d_helper.data_at(local_coord);
	}
	inline block_coll_result& data_at( const vec2_s32& local_coord )
	{
		return bcr_arr_2d_helper.data_at(local_coord);
	}
	
	
	
	inline s32 real_width() const
	{
		return real_size_2d.x;
	}
	inline s32 real_height() const
	{
		return real_size_2d.y;
	}
	inline vec2_s32 get_real_size_2d() const
	{
		return real_size_2d;
	}
	
	inline bool get_moving_left() const
	{
		return moving_left;
	}
	inline bool get_moving_right() const
	{
		return moving_right;
	}
	
	
	// Global coordinates
	inline s32 left() const
	{
		//return bcr_arr_2d_helper_data[0].coord.x;
		return start_pos.x;
	}
	inline s32 right() const
	{
		//return left() + real_width() - 1;
		return left() + local_right();
	}
	
	inline s32 top() const
	{
		//return bcr_arr_2d_helper_data[0].coord.y;
		return start_pos.y;
	}
	inline s32 bot() const
	{
		//return top() + real_height() - 1;
		return top() + local_bot();
	}
	
	// Corners
	inline vec2_s32 tl_corner() const
	{
		return vec2_s32( left(), top() );
	}
	inline vec2_s32 tr_corner() const
	{
		return vec2_s32( right(), top() );
	}
	inline vec2_s32 bl_corner() const
	{
		return vec2_s32( left(), bot() );
	}
	inline vec2_s32 br_corner() const
	{
		return vec2_s32( right(), bot() );
	}
	
	
	// Local coordinates
	inline s32 local_left() const
	{
		return 0;
	}
	inline s32 local_right() const
	{
		return real_width() - 1;
	}
	
	inline s32 local_top() const
	{
		return 0;
	}
	inline s32 local_bot() const
	{
		return real_height() - 1;
	}
	
	// Corners
	inline vec2_s32 local_tl_corner() const
	{
		return vec2_s32( local_left(), local_top() );
	}
	inline vec2_s32 local_tr_corner() const
	{
		return vec2_s32( local_right(), local_top() );
	}
	inline vec2_s32 local_bl_corner() const
	{
		return vec2_s32( local_left(), local_bot() );
	}
	inline vec2_s32 local_br_corner() const
	{
		return vec2_s32( local_right(), local_bot() );
	}
	
	
	inline bool contains_local_block_x_coord( s32 to_check ) const
	{
		return in_range<s32>( 0, real_size_2d.x, to_check );
	}
	inline bool contains_local_block_y_coord( s32 to_check ) const
	{
		return in_range<s32>( 0, real_size_2d.y, to_check );
	}
	inline bool contains_local_block_coord( const vec2_s32& to_check )
		const
	{
		//return vec2_in_range( vec2_s32( 0, 0 ), real_size_2d, to_check );
		return ( contains_local_block_x_coord(to_check.x) 
			&& contains_local_block_y_coord(to_check.y) );
	}
	
	
	void get_corner_stuff_old
		( array_helper<block_coll_result*>& bcr_ptr_arr_helper, 
		array_helper<u32>& bool_as_u32_arr_helper );
	
	void get_coll_box_related_stuff_old( const sprite& the_sprite,
		array_helper<block_coll_result*>& bcr_ptr_arr_helper );
	
	void get_side_blocked_stuff_old
		( array_helper<u32>& bool_as_u32_arr_helper );
	
protected:		// functions
	inline void init_bcr_arr_2d_helper()
	{
		bcr_arr_2d_helper.init( bcr_arr_2d_helper_data, 
			vec2_u32( real_width(), real_height() ) );
	}
	
	
} __attribute__((_align4));


// A line (i.e. row or column) of pointers to block_coll_result's.
class bcr_ptr_line
{
public:		// constants
	static constexpr u32 max_size = block_coll_result_group::max_size_2d.x;
	
protected:		// variables
	block_coll_result* ptr_arr_helper_data[max_size];
	
	// The real size of the row or column of pointers to
	// block_coll_result's
	s32 real_size;
	
	// The local position that was passed to the bcr_ptr_line
	vec2_s32 local_param_pos;
	
	// Whether this bcr_ptr_line represents a column (false) or a row
	// (true)
	u32 is_horiz;
	
public:		// variables
	array_helper<block_coll_result*> ptr_arr_helper;
	
public:		// functions
	inline bcr_ptr_line() : real_size(max_size), local_param_pos( 0, 0 ), 
		is_horiz(false)
	{
		init_ptr_arr_helper();
	}
	bcr_ptr_line( block_coll_result_group& the_bcr_group,
		const vec2_s32& s_local_param_pos, u32 s_is_horiz );
	
	
	inline block_coll_result*& operator () ( u32 index )
	{
		return data_at(index);
	}
	inline block_coll_result*& data_at( u32 index )
	{
		return ptr_arr_helper.data_at(index);
	}
	
	inline s32 get_real_size() const
	{
		return real_size;
	}
	
	inline const vec2_s32& get_local_param_pos() const
	{
		return local_param_pos;
	}
	
	inline bool get_is_horiz() const
	{
		return is_horiz;
	}
	inline bool get_is_vert() const
	{
		return !is_horiz;
	}
	
	
	
protected:		// functions
	//inline void clear_ptr_arr_helper_data()
	//{
	//	for ( u32 i=0; i<max_size; ++i )
	//	{
	//		ptr_arr_helper_data[i] = NULL;
	//	}
	//}
	inline void init_ptr_arr_helper()
	{
		ptr_arr_helper.init( ptr_arr_helper_data, real_size );
	}
	
	
} __attribute__((_align4));



#endif		// block_coll_result_group_class_hpp
