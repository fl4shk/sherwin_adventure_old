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


#ifndef spr_blk_coll_group_classes_hpp
#define spr_blk_coll_group_classes_hpp

#include "coll_lseg_classes.hpp"

// An abstract base class for a group of line segments for use with sprites
// So That they Can detect and respond To collisions with blocks
class SprBlkCollGroupBase
{
public:		// enums
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
	enum vert_index_bot
	{
		vi_bot_mid,
		vi_bot_left,
		vi_bot_right,



		lim_vi_bot,
	};

public:		// classes
	// Left and right sides use this
	class HorizCollTuple
	{
	public:		// variables
		//BcrLsegGroup bcrlg;
		//HorizCollLseg clseg;
		BlockCollResult bcr;
		Vec2s32 blk_crd_pos;
	} __attribute__((_align4));

	// Top side uses this
	class VertTopCollTuple : public HorizCollTuple
	{
	};

	// Bottom side uses this
	class VertBotCollTuple
	{
	public:		// variables
		BcrLsegGroup bcrlg;
		VertCollLseg clseg;
	} __attribute__((_align4));

protected:		// variables and constants
	static constexpr size_t num_horiz_ctups = lim_hi;
	static constexpr size_t num_vert_bot_ctups = lim_vi_bot;
	static constexpr size_t max_num_horiz_ctups = num_horiz_ctups;
	static constexpr size_t max_num_vert_top_ctups = num_vert_bot_ctups;
	static constexpr size_t max_num_vert_bot_ctups = num_vert_bot_ctups;

	//ArrayHelper<HorizCollTuple> horiz_ctups;
	//ArrayHelper<VertTopCollTuple> vert_top_ctups;
	//ArrayHelper<VertBotCollTuple> vert_bot_ctups;
	static HorizCollTuple horiz_ctups[max_num_horiz_ctups]
		__attribute__((_iwram));
	static VertTopCollTuple vert_top_ctups[max_num_vert_top_ctups]
		__attribute__((_iwram));
	static VertBotCollTuple vert_bot_ctups[max_num_vert_bot_ctups]
		__attribute__((_iwram));

	static Vec2<bool> size_is_tiny __attribute__((_iwram));
	static bool internal_on_ground __attribute__((_iwram));


	static s32 blk_crd_pos_x_for_left_hs __attribute__((_iwram));
	static s32 blk_crd_pos_x_for_right_hs __attribute__((_iwram));

	static s32 blk_crd_pos_y_for_top_hs __attribute__((_iwram));
	static s32 blk_crd_pos_y_for_mid_hs __attribute__((_iwram));
	static s32 blk_crd_pos_y_for_bot_hs __attribute__((_iwram));

	//static Fixed24p8 hs_width __attribute__((_iwram));

	static Fixed24p8 pos_x_for_left_vs __attribute__((_iwram));
	static Fixed24p8 pos_x_for_mid_vs __attribute__((_iwram));
	static Fixed24p8 pos_x_for_right_vs __attribute__((_iwram));

	static s32 blk_crd_pos_x_for_left_vs __attribute__((_iwram));
	static s32 blk_crd_pos_x_for_mid_vs __attribute__((_iwram));
	static s32 blk_crd_pos_x_for_right_vs __attribute__((_iwram));

	static s32 blk_crd_pos_y_for_top_vs __attribute__((_iwram));
	static Fixed24p8 pos_y_for_bot_vs __attribute__((_iwram));

	static Fixed24p8 vs_height_bot_ia __attribute__((_iwram));
	static Fixed24p8 offset_y_for_bot_vs __attribute__((_iwram));


	//static const Fixed24p8 offset_x_for_any_hs_left;
	//static const Fixed24p8 offset_x_for_any_hs_right;

	//static const Fixed24p8 offset_x_for_left_vs;
	//static const Fixed24p8 offset_x_for_right_vs;

	static const Fixed24p8 vs_height_non_bot_mid_og;
	static const Fixed24p8 vs_height_bot_mid_og;
	//static const Fixed24p8 vs_height_top;
	//static const Fixed24p8 vs_height_bot_ia;

	//static const Fixed24p8 offset_y_for_top_vs;
	//static const Fixed24p8 offset_y_for_bot_vs;



public:		// functions
	inline const HorizCollTuple& get_horiz_ctup(u32 index) const
	{
		return horiz_ctups[index];
	}
	inline const VertTopCollTuple& get_vert_top_ctup(u32 index) const
	{
		return vert_top_ctups[index];
	}
	inline const VertBotCollTuple& get_vert_bot_ctup(u32 index) const
	{
		return vert_bot_ctups[index];
	}

	inline HorizCollTuple& get_horiz_ctup(u32 index)
	{
		return horiz_ctups[index];
	}
	inline VertTopCollTuple& get_vert_top_ctup(u32 index)
	{
		return vert_top_ctups[index];
	}
	inline VertBotCollTuple& get_vert_bot_ctup(u32 index)
	{
		return vert_bot_ctups[index];
	}

	static inline const Vec2<bool>& get_size_is_tiny()
	{
		return size_is_tiny;
	}
	static inline bool get_on_ground()
	{
		return internal_on_ground;
	}

	//virtual const size_t get_num_horiz_ctups() const = 0;
	virtual const size_t get_num_vert_top_ctups() const = 0;
	//virtual const size_t get_num_vert_bot_ctups() const = 0;
	static inline constexpr size_t get_num_horiz_ctups()
	{
		return num_horiz_ctups;
	}
	static inline constexpr size_t get_num_vert_bot_ctups()
	{
		return num_vert_bot_ctups;
	}

	virtual const size_t get_hi_left_top() const = 0;
	virtual const size_t get_hi_left_bot() const = 0;
	virtual const size_t get_hi_right_top() const = 0;
	virtual const size_t get_hi_right_bot() const = 0;

	virtual const size_t get_vi_top_left() const = 0;
	virtual const size_t get_vi_top_right() const = 0;

protected:		// functions
	static const s32 get_blk_crd_pos_x_for_left_hs();
	static const s32 get_blk_crd_pos_x_for_right_hs();

	// "hs" means "horizontal sensor"
	// "og" means "on ground"
	static const s32 get_blk_crd_pos_y_for_top_hs();
	static const s32 get_blk_crd_pos_y_for_mid_hs();
	static const s32 get_blk_crd_pos_y_for_bot_hs();

	static const Vec2s32 get_left_top_hs_blk_crd_pos();
	static const Vec2s32 get_left_mid_hs_blk_crd_pos();
	static const Vec2s32 get_left_bot_hs_blk_crd_pos();

	static const Vec2s32 get_right_top_hs_blk_crd_pos();
	static const Vec2s32 get_right_mid_hs_blk_crd_pos();
	static const Vec2s32 get_right_bot_hs_blk_crd_pos();

	// "ia" means "in air"
	// "vs" means "vertical sensor"
	static const Fixed24p8 get_pos_x_for_left_vs();
	static const Fixed24p8 get_pos_x_for_mid_vs();
	static const Fixed24p8 get_pos_x_for_right_vs();

	static const s32 get_blk_crd_pos_x_for_left_vs();
	static const s32 get_blk_crd_pos_x_for_mid_vs();
	static const s32 get_blk_crd_pos_x_for_right_vs();

	static const s32 get_blk_crd_pos_y_for_top_vs();
	static const Fixed24p8 get_pos_y_for_bot_vs();

	static const Vec2s32 get_top_left_vs_blk_crd_pos();
	static const Vec2s32 get_top_mid_vs_blk_crd_pos();
	static const Vec2s32 get_top_right_vs_blk_crd_pos();

	static const VertCollLseg get_bot_left_vs_og();
	static const VertCollLseg get_bot_mid_vs_og();
	static const VertCollLseg get_bot_right_vs_og();

	static const VertCollLseg get_bot_left_vs_ia();
	static const VertCollLseg get_bot_mid_vs_ia();
	static const VertCollLseg get_bot_right_vs_ia();



} __attribute__((_align4));

// 


// Sprite/Block Collision Group for collision boxes That are at most 16x16
// in size
class SprBlkCollGroup16x16 : public SprBlkCollGroupBase
{
//public:		// enums
protected:		// enums
	enum vert_index_top
	{
		vi_top_left,
		//vi_top_mid,
		vi_top_right,


		lim_vi_top,
	};

protected:		// variables and constants
	static constexpr size_t num_vert_top_ctups = lim_vi_top;
	static_assert(num_vert_top_ctups <= max_num_vert_top_ctups);

public:		// functions
	inline SprBlkCollGroup16x16()
	{
		//init_arr_helpers();
	}
	SprBlkCollGroup16x16(const CollBox& s_coll_box, u32 s_on_ground);
	void init(const CollBox& s_coll_box, u32 s_on_ground)
		__attribute__((_iwram_code,_target_arm));

	//const size_t get_num_horiz_ctups() const;
	const size_t get_num_vert_top_ctups() const;
	//const size_t get_num_vert_bot_ctups() const;

	const size_t get_hi_left_top() const;
	const size_t get_hi_left_bot() const;
	const size_t get_hi_right_top() const;
	const size_t get_hi_right_bot() const;

	const size_t get_vi_top_left() const;
	const size_t get_vi_top_right() const;


protected:		// functions
	//void init_arr_helpers();
	static void init_static_vars(const CollBox& s_coll_box, 
		bool s_on_ground) __attribute__((_iwram_code,_target_arm));


} __attribute__((_align4));

// Sprite/Block Collision Group for collision boxes That are at most 16x32
// in size but larger than 16x16
class SprBlkCollGroup16x32 : public SprBlkCollGroupBase
{
//public:		// enums
protected:		// enums
	enum vert_index_top
	{
		vi_top_left,
		//vi_top_mid,
		vi_top_right,


		lim_vi_top,
	};


protected:		// variables and constants
	static constexpr size_t num_vert_top_ctups = lim_vi_top;
	static_assert(num_vert_top_ctups <= max_num_vert_top_ctups);


public:		// functions
	inline SprBlkCollGroup16x32()
	{
		//init_arr_helpers();
	}
	SprBlkCollGroup16x32(const CollBox& s_coll_box, u32 s_on_ground);
	void init(const CollBox& s_coll_box, u32 s_on_ground)
		__attribute__((_iwram_code,_target_arm));

	//const size_t get_num_horiz_ctups() const;
	const size_t get_num_vert_top_ctups() const;
	//const size_t get_num_vert_bot_ctups() const;

	const size_t get_hi_left_top() const;
	const size_t get_hi_left_bot() const;
	const size_t get_hi_right_top() const;
	const size_t get_hi_right_bot() const;

	const size_t get_vi_top_left() const;
	const size_t get_vi_top_right() const;


protected:		// functions
	//void init_arr_helpers();
	static void init_static_vars(const CollBox& s_coll_box, 
		bool s_on_ground) __attribute__((_iwram_code,_target_arm));

} __attribute__((_align4));




#endif		// spr_blk_coll_group_classes_hpp
