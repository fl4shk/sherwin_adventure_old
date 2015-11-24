#ifndef active_level_manager_class_hpp
#define active_level_manager_class_hpp


#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/bios_function_wrappers.hpp"
#include "../array_2d_helper_class.hpp"
#include "../block_stuff/block_stuff.hpp"
#include "active_level_class.hpp"
#include "../sprite_stuff/sprite_manager_class.hpp"


//#define bg0_sbb 31
constexpr u32 bg0_sbb = 28;
constexpr u32 bg1_sbb = 29;
constexpr u32 bg2_sbb = 30;
constexpr u32 bg3_sbb = 31;

#include "level_class.hpp"

#include "../housekeeping.hpp"

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
			( active_level::get_the_current_sublevel_ptr()
			.sprite_ipg_arr_arr_helper.get_the_array(),
			active_level::get_the_current_sublevel_ptr()
			.sprite_ipg_arr_arr_helper.get_size() );
	}
	
	static inline void load_level( const level* n_the_current_level_ptr )
	{
		active_level::the_current_level_ptr = n_the_current_level_ptr;
		load_sublevel_basic(0);
	}
	
	//static inline void initial_sublevel_loading()
	static inline void load_sublevel_basic( u32 n_sublevel_index )
	{
		active_level::the_current_active_sublevel_index = n_sublevel_index;
		
		// Initialize the list of sprite level data.
		init_horiz_sublevel_sprite_ipg_lists();
		
		// Decompress the sublevel's block data into block_data_array.
		bios_do_lz77_uncomp_wram
			( active_level::get_the_current_sublevel_ptr()
			.cmp_bd_arr_helper.the_array, 
			active_level::block_data_array );
		
		for ( u32 i=0; i<active_level::block_data_array_size; ++i )
		{
			block& the_block = active_level::block_data_array[i];
			
			block_stuff_array[the_block.type]
				->finish_initializing_using_persistent_data(the_block);
		}
		
		update_sublevel_in_screenblock_mirror_2d();
		
		//bgofs_mirror[0].prev = bg_point();
		//bgofs_mirror[0].curr = bg_point();
		
		sprite_manager::initial_sprite_spawning_at_start_of_level
			(bgofs_mirror[0].curr);
		
		update_sublevel_in_screenblock_mirror_2d();
		
		//bios_wait_for_vblank();
		//copy_sublevel_from_array_2d_helper_to_vram();
		
		bios_wait_for_vblank();
		vblank_func();
	}
	
	//static inline void load_sublevel_warp_based( u32 n_sublevel_index )
	static inline void load_sublevel_at_intra_sublevel_warp
		( u32 n_sublevel_index, u32 sublevel_entrance_index )
	{
		fade_out_to_black( 5, 6 );
		
		active_level::the_current_active_sublevel_index = n_sublevel_index;
		
		memfill32( oam_mirror, 0, sizeof(oam_entry) * oam_mirror_size 
			/ sizeof(u32) );
		
		bios_wait_for_vblank();
		copy_oam_mirror_to_oam();
		
		
		// Initialize the list of sprite level data.
		init_horiz_sublevel_sprite_ipg_lists();
		
		// Decompress the sublevel's block data into block_data_array.
		bios_do_lz77_uncomp_wram
			( active_level::get_the_current_sublevel_ptr()
			.cmp_bd_arr_helper.the_array, 
			active_level::block_data_array );
		
		for ( u32 i=0; i<active_level::block_data_array_size; ++i )
		{
			block& the_block = active_level::block_data_array[i];
			
			block_stuff_array[the_block.type]
				->finish_initializing_using_persistent_data(the_block);
		}
		
		update_sublevel_in_screenblock_mirror_2d();
		
		
		
		sprite_manager::initial_sprite_spawning_at_intra_sublevel_warp
			( bgofs_mirror[0].curr, sublevel_entrance_index );
		update_sublevel_in_screenblock_mirror_2d();
		
		//bios_wait_for_vblank();
		//copy_sublevel_from_array_2d_helper_to_vram();
		
		bios_wait_for_vblank();
		vblank_func();
		
		// Wait for about 0.25 seconds.
		//wait_for_x_frames(15);
		
		fade_in_from_black( 5, 6 );
		
	}
	
} __attribute__((_align4));





#endif		// active_level_manager_class_hpp
