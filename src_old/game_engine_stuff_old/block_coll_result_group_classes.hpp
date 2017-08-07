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


#ifndef block_coll_result_group_classes_hpp
#define block_coll_result_group_classes_hpp

//#include "coll_lseg_classes.hpp"
#include "../general_utility_stuff/range_funcs.hpp"
#include "block_stuff/block_stuff.hpp"

#include "coll_box_class.hpp"
#include "../general_utility_stuff/array_helper_class.hpp"
#include "level_stuff/active_level_class.hpp"

//#include "coll_point_group_classes.hpp"

class HorizCollLseg;
class VertCollLseg;

class BlockCollResult
{
public:		// variables
	//vec2_s32 coord;
	//block_type type;
	Block* the_block __attribute__((_ALIGN4));
	//block_behavior_type the_bbvt __attribute__((_ALIGN4));
	u32 the_bbvt __attribute__((_ALIGN4));
	
public:		// functions
	inline BlockCollResult()
	{
		the_block = &ActiveLevel::blank_block;
		the_bbvt = bbvt_air;
	}
	//inline BlockCollResult()
	//{
	//	memset(this, 0, sizeof(*this));
	//}
	inline BlockCollResult(const vec2_s32& s_blk_coord)
	{
		init(s_blk_coord);
	}
	inline BlockCollResult(const vec2_f24p8& s_coord_f24p8)
	{
		init(s_coord_f24p8);
	}
	inline BlockCollResult(const BlockCollResult& to_copy)
	{
		*this = to_copy;
	}
	
	inline void init(const vec2_s32& s_blk_coord)
	{
		the_block = &ActiveLevel::the_block_at_coord(s_blk_coord);
		the_bbvt = get_behavior_type_of_block_type(get_block_type());
	}
	inline void init(const vec2_f24p8& s_coord_f24p8)
	{
		init(ActiveLevel::get_block_coord_of_point(s_coord_f24p8));
	}
	
	//inline BlockCollResult& operator = 
	//	(const BlockCollResult& to_copy)
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
	
} __attribute__((_ALIGN4));



class Sprite;

//class BcrPtrLine;


class BlockCollResultRectGroup
{
public:		// constants
	// The maximum number of blocks intersected by a Sprite, per dimension.
	// The value of (3, 3) corresponds To a 32x32 Sprite.  Definitely
	// change these two values (among other things) if there Is every any
	// infrastructure for sprites larger than 32x32 pixels.
	//const vec2_u32 BlockCollResultRectGroup::shared_max_size_2d(3, 3);
	static constexpr vec2_u32 max_size_2d = vec2_u32(3, 3);
	//static constexpr vec2_u32 max_size_2d = vec2_u32(80, 80);
	static constexpr u32 max_size = max_size_2d.x * max_size_2d.y;
	
protected:		// variables
	BlockCollResult bcr_arr_csz_2d_helper_data[max_size];
	
	vec2_s32 start_pos;
	
	vec2_s32 real_size_2d;
	
	bool moving_left, moving_right;
	
	static u32 temp_debug_thing;
	
public:		// variables
	//Array_2dHelper<BlockCollResult> bcr_arr_csz_2d_helper;
	ArrayCsz2dHelper<BlockCollResult, max_size_2d.x, max_size_2d.y >
		bcr_arr_csz_2d_helper;
	
	
public:		// functions
	BlockCollResultRectGroup();
	BlockCollResultRectGroup(const CollBox& the_coll_box, 
		u32 s_moving_left, u32 s_moving_right);
	BlockCollResultRectGroup
		(const BlockCollResultRectGroup& to_copy);
	
	BlockCollResultRectGroup& operator = 
		(const BlockCollResultRectGroup& to_copy);
	
	
	inline BlockCollResult& operator () (u32 local_x, u32 local_y)
	{
		return at(local_x, local_y);
	}
	inline BlockCollResult& operator () (const vec2_u32& local_coord)
	{
		return at(local_coord);
	}
	inline BlockCollResult& operator () (const vec2_s32& local_coord)
	{
		return at(local_coord);
	}
	
	inline BlockCollResult& at(u32 local_x, u32 local_y)
	{
		return bcr_arr_csz_2d_helper.at(local_x, local_y);
	}
	inline BlockCollResult& at(const vec2_u32& local_coord)
	{
		return bcr_arr_csz_2d_helper.at(local_coord);
	}
	inline BlockCollResult& at(const vec2_s32& local_coord)
	{
		return bcr_arr_csz_2d_helper.at(local_coord);
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
		//return bcr_arr_csz_2d_helper_data[0].coord.x;
		return start_pos.x;
	}
	inline s32 right() const
	{
		//return left() + real_width() - 1;
		return left() + local_right();
	}
	
	inline s32 top() const
	{
		//return bcr_arr_csz_2d_helper_data[0].coord.y;
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
		return vec2_s32(left(), top());
	}
	inline vec2_s32 tr_corner() const
	{
		return vec2_s32(right(), top());
	}
	inline vec2_s32 bl_corner() const
	{
		return vec2_s32(left(), bot());
	}
	inline vec2_s32 br_corner() const
	{
		return vec2_s32(right(), bot());
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
		return vec2_s32(local_left(), local_top());
	}
	inline vec2_s32 local_tr_corner() const
	{
		return vec2_s32(local_right(), local_top());
	}
	inline vec2_s32 local_bl_corner() const
	{
		return vec2_s32(local_left(), local_bot());
	}
	inline vec2_s32 local_br_corner() const
	{
		return vec2_s32(local_right(), local_bot());
	}
	
	
	inline bool contains_local_block_x_coord(s32 to_check) const
	{
		return in_range<s32>(0, real_size_2d.x, to_check);
	}
	inline bool contains_local_block_y_coord(s32 to_check) const
	{
		return in_range<s32>(0, real_size_2d.y, to_check);
	}
	inline bool contains_local_block_coord(const vec2_s32& to_check)
		const
	{
		//return vec2_in_range(vec2_s32(0, 0), real_size_2d, to_check);
		return (contains_local_block_x_coord(to_check.x) 
			&& contains_local_block_y_coord(to_check.y));
	}
	
	
	//void get_corner_stuff_old
	//	(ArrayHelper<BlockCollResult*>& bcr_ptr_arr_helper, 
	//	ArrayHelper<u32>& bool_as_u32_arr_helper)
	//	__attribute__((_TARGET_ARM));
	//
	//void get_coll_box_related_stuff_old(const Sprite& the_sprite,
	//	ArrayHelper<BlockCollResult*>& bcr_ptr_arr_helper)
	//	__attribute__((_TARGET_ARM));
	//
	//void get_side_blocked_stuff_old
	//	(ArrayHelper<u32>& bool_as_u32_arr_helper)
	//	__attribute__((_TARGET_ARM));
	
protected:		// functions
	inline void init_bcr_arr_csz_2d_helper()
	{
		//bcr_arr_csz_2d_helper.init(bcr_arr_csz_2d_helper_data, 
		//	vec2_u32(real_width(), real_height()));
		bcr_arr_csz_2d_helper.init(bcr_arr_csz_2d_helper_data);
	}
	
	
} __attribute__((_ALIGN4));

class BcrLsegGroup
{
public:		// constants
	// This size Is arbitrary, but Intended To be large enough To work with
	static constexpr size_t max_size = 3;
	
public:		// variables
	BlockCollResult bcr_arr[max_size];
	
protected:		// variables
	// The real size of the row or column of pointers To
	// BlockCollResult's
	s32 real_size = max_size;
	
	// The (Block coordinates) position of the left or top That was passed
	// To the BcrLsegGroup
	vec2_s32 start_pos = vec2_s32(0, 0);
	
	// Whether this BcrLsegGroup represents a column (false) or a row
	// (true)
	u32 is_horiz = false;
	
public:		// functions
	inline BcrLsegGroup()
	{
	}
	inline BcrLsegGroup(const HorizCollLseg& the_coll_lseg)
	{
		init(the_coll_lseg);
	}
	inline BcrLsegGroup(const VertCollLseg& the_coll_lseg)
	{
		init(the_coll_lseg);
	}
	
	void init(const HorizCollLseg& the_coll_lseg);
		//__attribute__((_IWRAM_CODE));
	void init(const VertCollLseg& the_coll_lseg)
		__attribute__((_IWRAM_CODE));
	
	BlockCollResult* horiz_any_bbvt_is_fully_solid(vec2_s32& pos);
		//__attribute__((_IWRAM_CODE));
	BlockCollResult* vert_any_bbvt_is_fully_solid(vec2_s32& pos)
		__attribute__((_IWRAM_CODE));
	BlockCollResult* vert_any_bbvt_is_slope(vec2_s32& pos)
		__attribute__((_IWRAM_CODE));
	
	inline BlockCollResult& operator () (u32 index)
	{
		return at(index);
	}
	inline const BlockCollResult& operator () (u32 index) const
	{
		return at(index);
	}
	
	inline BlockCollResult& at(u32 index)
	{
		return bcr_arr[index];
	}
	inline const BlockCollResult& at(u32 index) const
	{
		return bcr_arr[index];
	}
	
	inline BlockCollResult& horiz_left()
	{
		return at(0);
	}
	inline BlockCollResult& horiz_right()
	{
		return at(get_end_pos_offset());
	}
	inline BlockCollResult& vert_top()
	{
		return at(0);
	}
	inline BlockCollResult& vert_bot()
	{
		return at(get_end_pos_offset());
	}
	
	
	inline const BlockCollResult& horiz_left() const
	{
		return at(0);
	}
	inline const BlockCollResult& horiz_right() const
	{
		return at(get_end_pos_offset());
	}
	inline const BlockCollResult& vert_top() const
	{
		return at(0);
	}
	inline const BlockCollResult& vert_bot() const
	{
		return at(get_end_pos_offset());
	}
	
	
	
	inline s32 get_real_size() const
	{
		return real_size;
	}
	
	inline const vec2_s32& get_start_pos() const
	{
		return start_pos;
	}
	inline const vec2_s32 get_horiz_end_pos() const
	{
		return get_start_pos() + get_horiz_offset(get_end_pos_offset());
	}
	inline const vec2_s32 get_vert_end_pos() const
	{
		return get_start_pos() + get_vert_offset(get_end_pos_offset());
	}
	
	inline const vec2_s32 get_horiz_offset(s32 i) const
	{
		return vec2_s32(i, 0);
	}
	inline const vec2_s32 get_vert_offset(s32 i) const
	{
		return vec2_s32(0, i);
	}
	
	inline const s32 horiz_left_pos() const
	{
		return get_start_pos().x;
	}
	inline const s32 horiz_right_pos() const
	{
		return horiz_left_pos() + get_end_pos_offset();
	}
	inline const s32 vert_top_pos() const
	{
		return get_start_pos().y;
	}
	inline const s32 vert_bot_pos() const
	{
		return vert_top_pos() + get_end_pos_offset();
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
	inline const s32 get_end_pos_offset() const
	{
		return get_real_size() - 1;
	}
	
	
} __attribute__((_ALIGN4));





#endif		// block_coll_result_group_classes_hpp
