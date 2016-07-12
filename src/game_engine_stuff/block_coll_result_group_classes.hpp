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


#ifndef block_coll_result_group_classes_hpp
#define block_coll_result_group_classes_hpp


#include "block_stuff/block_stuff.hpp"

#include "coll_point_extras.hpp"
#include "coll_point_group_classes.hpp"

class block_coll_result
{
public:		// variables
	vec2_s32 coord;
	//block_type type;
	block* the_block;
	
public:		// functions
	inline block_type get_block_type() const
	{
		return the_block->get_block_type();
	}
	
} __attribute__((_align4));



class block_coll_result_group_base
{
public:		// variables
	static const u32 max_num_block_coll_results 
		= coll_point_group_base::max_num_coll_points;
	block_coll_result the_array[max_num_block_coll_results];
	
public:		// functions
	block_coll_result_group_base();
	block_coll_result_group_base
		( const block_coll_result_group_base& to_copy );
	
	block_coll_result_group_base& operator = 
		( const block_coll_result_group_base& to_copy );
	
} __attribute__((_align4));

class block_coll_result_group_16x16 : public block_coll_result_group_base
{
public:		// functions
	block_coll_result_group_16x16
		( const coll_point_group_16x16& the_pt_group );
	block_coll_result_group_16x16
		( const block_coll_result_group_base& to_copy );
	
	
	inline block_coll_result& get_bcr_lt()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_lt]; }
	inline block_coll_result& get_bcr_lb()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_lb]; }
	
	inline block_coll_result& get_bcr_rt()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_rt]; }
	inline block_coll_result& get_bcr_rb()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_rb]; }
	
	inline block_coll_result& get_bcr_tl()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_tl]; }
	inline block_coll_result& get_bcr_tm()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_tm]; }
	inline block_coll_result& get_bcr_tr()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_tr]; }
	
	inline block_coll_result& get_bcr_bl()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_bl]; }
	inline block_coll_result& get_bcr_bm()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_bm]; }
	inline block_coll_result& get_bcr_br()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_br]; }
	
	inline block_coll_result& get_bcr_mt()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_mt]; }
	inline block_coll_result& get_bcr_mb()
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_mb]; }
	
	
	inline const block_coll_result& get_bcr_lt() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_lt]; }
	inline const block_coll_result& get_bcr_lb() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_lb]; }
	
	inline const block_coll_result& get_bcr_rt() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_rt]; }
	inline const block_coll_result& get_bcr_rb() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_rb]; }
	
	inline const block_coll_result& get_bcr_tl() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_tl]; }
	inline const block_coll_result& get_bcr_tm() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_tm]; }
	inline const block_coll_result& get_bcr_tr() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_tr]; }
	
	inline const block_coll_result& get_bcr_bl() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_bl]; }
	inline const block_coll_result& get_bcr_bm() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_bm]; }
	inline const block_coll_result& get_bcr_br() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_br]; }
	
	inline const block_coll_result& get_bcr_mt() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_mt]; }
	inline const block_coll_result& get_bcr_mb() const
		{ return the_array[coll_point_group_base::arr_ind_16x16_pt_mb]; }
	
} __attribute__((_align4));


class block_coll_result_group_16x32 : public block_coll_result_group_base
{
public:		// functions
	block_coll_result_group_16x32
		( const coll_point_group_16x32& the_pt_group );
	block_coll_result_group_16x32
		( const block_coll_result_group_base& to_copy );
	
	
	inline block_coll_result& get_bcr_lt()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_lt]; }
	inline block_coll_result& get_bcr_lm()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_lm]; }
	inline block_coll_result& get_bcr_lb()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_lb]; }
	
	inline block_coll_result& get_bcr_rt()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_rt]; }
	inline block_coll_result& get_bcr_rm()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_rm]; }
	inline block_coll_result& get_bcr_rb()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_rb]; }
	
	inline block_coll_result& get_bcr_tl()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_tl]; }
	inline block_coll_result& get_bcr_tm()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_tm]; }
	inline block_coll_result& get_bcr_tr()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_tr]; }
	
	inline block_coll_result& get_bcr_bl()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_bl]; }
	inline block_coll_result& get_bcr_bm()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_bm]; }
	inline block_coll_result& get_bcr_br()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_br]; }
	
	inline block_coll_result& get_bcr_mt()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_mt]; }
	inline block_coll_result& get_bcr_mm()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_mm]; }
	inline block_coll_result& get_bcr_mb()
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_mb]; }
	
	
	
	inline const block_coll_result& get_bcr_lt() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_lt]; }
	inline const block_coll_result& get_bcr_lm() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_lm]; }
	inline const block_coll_result& get_bcr_lb() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_lb]; }
	
	inline const block_coll_result& get_bcr_rt() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_rt]; }
	inline const block_coll_result& get_bcr_rm() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_rm]; }
	inline const block_coll_result& get_bcr_rb() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_rb]; }
	
	inline const block_coll_result& get_bcr_tl() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_tl]; }
	inline const block_coll_result& get_bcr_tm() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_tm]; }
	inline const block_coll_result& get_bcr_tr() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_tr]; }
	
	inline const block_coll_result& get_bcr_bl() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_bl]; }
	inline const block_coll_result& get_bcr_bm() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_bm]; }
	inline const block_coll_result& get_bcr_br() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_br]; }
	
	inline const block_coll_result& get_bcr_mt() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_mt]; }
	inline const block_coll_result& get_bcr_mm() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_mm]; }
	inline const block_coll_result& get_bcr_mb() const
		{ return the_array[coll_point_group_base::arr_ind_16x32_pt_mb]; }
	
} __attribute__((_align4));




#endif		// block_coll_result_group_classes_hpp
