#ifndef coll_point_group_class_hpp
#define coll_point_group_class_hpp

#include "../gba_specific_stuff/attribute_defines.hpp"
#include "vec2_class.hpp"

#include "coll_box_class.hpp"


// This class is primarily used by the collision detection and response
// between sprites and blocks, or at least coll_boxes and blocks.
class coll_point_group
{
public:		// variables
	// The maximum number of collision points, 32, is definitely more than
	// is necessary, but thus far there's not that much need to optimize
	// the number of collision points (also I'm too lazy to put effort into
	// doing so).
	static const u32 total_coll_points = 32;
	u32 num_used_points;
	vec2_f24p8 the_array[total_coll_points];
	
	
public:		// functions
	inline coll_point_group()
	{
		num_used_points = 0;
		memfill32( the_array, 0, sizeof(the_array) 
			/ sizeof(u32) );
	}
	
	inline void push_coll_point( const vec2_f24p8& to_push )
	{
		the_array[num_used_points++] = to_push;
	}
	
	// These functions are on one line due to prevent ridiculousness with
	// the length of this header file.  Also, it just looks cleaner.
	inline vec2_f24p8& get_pt_lt_16x16() { return the_array[0]; }
	inline vec2_f24p8& get_pt_lb_16x16() { return the_array[1]; }
	inline vec2_f24p8& get_pt_tl_16x16() { return the_array[2]; }
	inline vec2_f24p8& get_pt_tm_16x16() { return the_array[3]; }
	inline vec2_f24p8& get_pt_tr_16x16() { return the_array[4]; }
	inline vec2_f24p8& get_pt_rt_16x16() { return the_array[5]; }
	inline vec2_f24p8& get_pt_rb_16x16() { return the_array[6]; }
	inline vec2_f24p8& get_pt_bl_16x16() { return the_array[7]; }
	inline vec2_f24p8& get_pt_bm_16x16() { return the_array[8]; }
	inline vec2_f24p8& get_pt_br_16x16() { return the_array[9]; }
	
	inline void correct_num_used_points_16x16() { num_used_points = 10; }
	
	
	// These functions are on one line due to prevent ridiculousness with
	// the length of this header file.  Also, it just looks cleaner.
	inline vec2_f24p8& get_pt_lt_16x32() { return the_array[0]; }
	inline vec2_f24p8& get_pt_lm_16x32() { return the_array[1]; }
	inline vec2_f24p8& get_pt_lb_16x32() { return the_array[2]; }
	inline vec2_f24p8& get_pt_tl_16x32() { return the_array[3]; }
	inline vec2_f24p8& get_pt_tm_16x32() { return the_array[4]; }
	inline vec2_f24p8& get_pt_tr_16x32() { return the_array[5]; }
	inline vec2_f24p8& get_pt_rt_16x32() { return the_array[6]; }
	inline vec2_f24p8& get_pt_rm_16x32() { return the_array[7]; }
	inline vec2_f24p8& get_pt_rb_16x32() { return the_array[8]; }
	inline vec2_f24p8& get_pt_bl_16x32() { return the_array[9]; }
	inline vec2_f24p8& get_pt_bm_16x32() { return the_array[10]; }
	inline vec2_f24p8& get_pt_br_16x32() { return the_array[11]; }
	
	inline void correct_num_used_points_16x32() { num_used_points = 12; }
	
	
} __attribute__((_align4));

void generate_coll_point_group_16x16( const coll_box& the_coll_box, 
	coll_point_group& the_pt_group ) __attribute__((_iwram_code));

void generate_coll_point_group_16x32( const coll_box& the_coll_box, 
	coll_point_group& the_pt_group ) __attribute__((_iwram_code));

void generate_coll_point_group_32x16( const coll_box& the_coll_box, 
	coll_point_group& the_pt_group ) __attribute__((_iwram_code));

void generate_coll_point_group_32x32( const coll_box& the_coll_box, 
	coll_point_group& the_pt_group ) __attribute__((_iwram_code));


#endif		// coll_point_group_class_hpp
