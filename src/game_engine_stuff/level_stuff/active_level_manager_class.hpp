#ifndef active_level_manager_class_hpp
#define active_level_manager_class_hpp


#include "../../gba_specific_stuff/bg_reg_stuff.hpp"
#include "../../gba_specific_stuff/bios_function_wrappers.hpp"
#include "../array_2d_helper_class.hpp"
#include "../block_stuff/block_stuff.hpp"
#include "active_level_class.hpp"
#include "../sprite_stuff/sprite_manager_class.hpp"

//#define bg0_sbb 31
constexpr u32 bg0_sbb = 31;

#include "level_class.hpp"

class active_level_manager
{
public:		// variables
	
	
	static u32 converted_block_tile_ids_0[bt_count],
		converted_block_tile_ids_1[bt_count],
		converted_block_tile_ids_2[bt_count],
		converted_block_tile_ids_3[bt_count];
	
	
public:		// functions
	
	static scr_entry horiz_sublevel_tile_at_basic( u32 tile_x, 
		u32 tile_y ) __attribute__((_iwram_code));
	static scr_entry horiz_sublevel_tile_at( u32 tile_x, u32 tile_y )
		__attribute__((_iwram_code));
	
	
	
	static inline u32 sublevel_width_in_tiles 
		( array_2d_helper<u16>& the_block_ids_2d )
	{
		return the_block_ids_2d.width() * 2;
	}
	static inline u32 sublevel_height_in_tiles 
		( array_2d_helper<u16>& the_block_ids_2d )
	{
		return the_block_ids_2d.height() * 2;
	}
	
	static inline u32 sublevel_width_in_tiles 
		( const vec2_u32& sublevel_size_in_blocks_2d )
	{
		return sublevel_size_in_blocks_2d.x * 2;
	}
	static inline u32 sublevel_height_in_tiles 
		( const vec2_u32& sublevel_size_in_blocks_2d )
	{
		return sublevel_size_in_blocks_2d.y * 2;
	}
	
	
	static void correct_bg0_scroll_mirror 
		( const vec2_u32& sublevel_size_in_blocks_2d )
		__attribute__((_iwram_code));
	
	static void update_sublevel_in_screenblock_mirror_2d()
		__attribute__((_iwram_code));
	
	static void copy_sublevel_from_array_2d_helper_to_vram()
		__attribute__((_iwram_code));
	
	
	
	//static void init_horiz_sublevel_sprite_ipg_lists
	//	( const sprite_init_param_group* the_ext_sprite_ipg_arr, 
	//	u32 the_ext_sprite_ipg_arr_size )
	//	__attribute__((_iwram_code));
	
	
	static inline void init_horiz_sublevel_sprite_ipg_lists()
	{
		sprite_manager::init_horiz_sublevel_sprite_ipg_lists
			( active_level::the_current_sublevel_ptr
			.sprite_ipg_arr_arr_helper.get_the_array(),
			active_level::the_current_sublevel_ptr
			.sprite_ipg_arr_arr_helper.get_size() );
	}
	
	
	
	static inline void initial_sublevel_loading()
	{
		// Initialize the list of sprite level data.
		init_horiz_sublevel_sprite_ipg_lists();
		
		// Decompress the sublevel's block data into block_data_array.
		bios_do_lz77_uncomp_wram( active_level::the_current_sublevel_ptr
			.cmp_bd_arr_helper.the_array, active_level::block_data_array );
		
		update_sublevel_in_screenblock_mirror_2d();
		
		copy_sublevel_from_array_2d_helper_to_vram();
	}
	
} __attribute__((_align4));





#endif		// active_level_manager_class_hpp
