#include "coll_point_group_class.hpp"
#include "sprite_stuff/sprite_class.hpp"

// Thursday, July 23, 2015 (9:35 PM EST) Note: I will use a top middle coll
// point and a bottom middle coll point, starting tomorrow.  

// The top middle coll point will be used for checking the type of block
// that has been hit by a sprite that has jumped.  

// The bottom middle coll point will be used
// as the primary thing for checking if a sprite is on the ground.


// Friday, October 23, 2015 (12:10 PM CST) Lol, I forgot that the first
// comment was there.


void generate_coll_point_group_16x16( const sprite& the_sprite, 
	coll_point_group& the_pt_group )
{
	const coll_box& the_coll_box = the_sprite.the_coll_box;
	
	the_pt_group.correct_num_used_points_16x16();
	
	// The collision points
	vec2_f24p8 & pt_lt = the_pt_group.get_pt_lt_16x16(),
		& pt_lb = the_pt_group.get_pt_lb_16x16(),
		
		& pt_tl = the_pt_group.get_pt_tl_16x16(),
		& pt_tm = the_pt_group.get_pt_tm_16x16(),
		& pt_tr = the_pt_group.get_pt_tr_16x16(),
		
		& pt_rt = the_pt_group.get_pt_rt_16x16(), 
		& pt_rb = the_pt_group.get_pt_rb_16x16(),
		
		& pt_bl = the_pt_group.get_pt_bl_16x16(), 
		& pt_bm = the_pt_group.get_pt_bm_16x16(),
		& pt_br = the_pt_group.get_pt_br_16x16();
	
	
	// Left and Right
	pt_lt.x = pt_lb.x = the_coll_box.left();
	pt_rt.x = pt_rb.x = the_coll_box.right();
	
	pt_lt.y.data = pt_rt.y.data = the_coll_box.top().data 
		+ ( the_coll_box.size.y.data / 4 );
	pt_lb.y.data = pt_rb.y.data = the_coll_box.bot().data 
		- ( the_coll_box.size.y.data / 4 );
	
	
	// Top and Bottom
	//pt_tl.x.data = pt_bl.x.data = the_coll_box.left().data 
	//	+ ( the_coll_box.size.x.data / 4 );
	//pt_tr.x.data = pt_br.x.data = the_coll_box.right().data 
	//	- ( the_coll_box.size.x.data / 4 );
	
	
	pt_tl.x = pt_bl.x = the_coll_box.left() + (fixed24p8){0x400};
	pt_tm.x.data = pt_bm.x.data = the_coll_box.left().data 
		+ ( the_coll_box.size.x.data / 2 );
	pt_tr.x = pt_br.x = the_coll_box.right() - (fixed24p8){0x400};
	
	pt_tl.y = pt_tm.y = pt_tr.y = the_coll_box.top();
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot();
	
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot() 
	//	+ the_sprite.cb_pos_offset.y;
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot() + make_f24p8(2);
	
	pt_bl.y = pt_bm.y = pt_br.y = the_sprite.in_level_pos.y 
		+ make_f24p8( the_sprite.get_shape_size_as_vec2().y + 2 );
	
}


void generate_coll_point_group_16x32( const sprite& the_sprite, 
	coll_point_group& the_pt_group )
{
	const coll_box& the_coll_box = the_sprite.the_coll_box;
	
	the_pt_group.correct_num_used_points_16x32();
	
	// The collision_points
	vec2_f24p8 & pt_lt = the_pt_group.get_pt_lt_16x32(),
		& pt_lm = the_pt_group.get_pt_lm_16x32(),
		& pt_lb = the_pt_group.get_pt_lb_16x32(),
		
		& pt_tl = the_pt_group.get_pt_tl_16x32(),
		& pt_tm = the_pt_group.get_pt_tm_16x32(),
		& pt_tr = the_pt_group.get_pt_tr_16x32(),
		
		& pt_rt = the_pt_group.get_pt_rt_16x32(), 
		& pt_rm = the_pt_group.get_pt_rm_16x32(),
		& pt_rb = the_pt_group.get_pt_rb_16x32(),
		
		& pt_bl = the_pt_group.get_pt_bl_16x32(), 
		& pt_bm = the_pt_group.get_pt_bm_16x32(),
		& pt_br = the_pt_group.get_pt_br_16x32();
	
	
	// Left and Right
	pt_lt.x = pt_lm.x = pt_lb.x = the_coll_box.left();
	pt_rt.x = pt_rm.x = pt_rb.x = the_coll_box.right();
	
	pt_lt.y = pt_rt.y = the_coll_box.top() + (fixed24p8){0x480};
	pt_lm.y.data = pt_rm.y.data = the_coll_box.top().data 
		+ ( the_coll_box.size.y.data / 2 );
	pt_lb.y = pt_rb.y = the_coll_box.bot() - (fixed24p8){0x480};
	
	
	// Top and Bottom
	pt_tl.x = pt_bl.x = the_coll_box.left() + (fixed24p8){0x400};
	pt_tm.x.data = pt_bm.x.data = the_coll_box.left().data 
		+ ( the_coll_box.size.x.data / 2 );
	pt_tr.x = pt_br.x = the_coll_box.right() - (fixed24p8){0x400};
	
	pt_tl.y = pt_tm.y = pt_tr.y = the_coll_box.top();
	
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot();
	
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot() 
	//	+ the_sprite.cb_pos_offset.y;
	
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot() + make_f24p8(2);
	pt_bl.y = pt_bm.y = pt_br.y = the_sprite.in_level_pos.y 
		+ make_f24p8( the_sprite.get_shape_size_as_vec2().y + 2 );
	
}

void generate_coll_point_group_32x16( const sprite& the_sprite, 
	coll_point_group& the_pt_group )
{
	const coll_box& the_coll_box = the_sprite.the_coll_box;
	
	// The collision points
	vec2_f24p8 & pt_lt = the_pt_group.get_pt_lt_32x16(),
		& pt_lb = the_pt_group.get_pt_lb_32x16(),
		
		& pt_tl = the_pt_group.get_pt_tl_32x16(),
		& pt_tm = the_pt_group.get_pt_tm_32x16(),
		& pt_tr = the_pt_group.get_pt_tr_32x16(),
		
		& pt_rt = the_pt_group.get_pt_rt_32x16(), 
		& pt_rb = the_pt_group.get_pt_rb_32x16(),
		
		& pt_bl = the_pt_group.get_pt_bl_32x16(), 
		& pt_bm = the_pt_group.get_pt_bm_32x16(),
		& pt_br = the_pt_group.get_pt_br_32x16();
	
	// Left and Right
	pt_lt.x = pt_lb.x = the_coll_box.left();
	pt_rt.x = pt_rb.x = the_coll_box.right();
	
	pt_lt.y.data = pt_rt.y.data = the_coll_box.top().data 
		+ ( the_coll_box.size.y.data / 4 );
	pt_lb.y.data = pt_rb.y.data = the_coll_box.bot().data 
		- ( the_coll_box.size.y.data / 4 );
	
	
	// Top and Bottom
	//pt_tl.x.data = pt_bl.x.data = the_coll_box.left().data 
	//	+ ( the_coll_box.size.x.data / 4 );
	//pt_tr.x.data = pt_br.x.data = the_coll_box.right().data 
	//	- ( the_coll_box.size.x.data / 4 );
	
	
	pt_tl.x = pt_bl.x = the_coll_box.left() + (fixed24p8){0x400};
	pt_tm.x.data = pt_bm.x.data = the_coll_box.left().data 
		+ ( the_coll_box.size.x.data / 2 );
	pt_tr.x = pt_br.x = the_coll_box.right() - (fixed24p8){0x400};
	
	pt_tl.y = pt_tm.y = pt_tr.y = the_coll_box.top();
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot();
	
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot() 
	//	+ the_sprite.cb_pos_offset.y;
	
	//pt_bl.y = pt_bm.y = pt_br.y = the_coll_box.bot() + make_f24p8(2);
	pt_bl.y = pt_bm.y = pt_br.y = the_sprite.in_level_pos.y 
		+ make_f24p8( the_sprite.get_shape_size_as_vec2().y + 2 );
}



