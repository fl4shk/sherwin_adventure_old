#include "active_level_class.hpp"
#include "../sprite_stuff/sprite_class.hpp"
#include "sprite_level_data_stuff.hpp"
#include "sublevel_class.hpp"
#include "active_level_manager_class.hpp"
//#include "../sa_list_class_stuff.hpp"


block active_level::block_data_array[block_data_array_size];
//	__attribute__((_ewram));


u16 active_level::persistent_block_data_arrays[max_num_sublevels]
	[persistent_block_data_array_size]; //__attribute__((_ewram));


array_2d_helper<block> active_level::horiz_sublevel_block_data_2d 
	( active_level::block_data_array, 
	active_level::horiz_sublevel_size_2d );


//std::array< std::forward_list<sprite_init_param_group>, 
//	active_level::horiz_sublevel_xsize > 
//	active_level::horiz_sublevel_sprite_ipg_lists; 
//	//__attribute__((_ewram));

//std::array< std::array< sprite_init_param_group, horiz_sublevel_ysize >, 
//	active_level::horiz_sublevel_xsize > 
//	active_level::horiz_sublevel_sprite_ipg_lists; 
//	//__attribute__((_ewram));

sa_array_of_lists< sprite_init_param_group, 512,
	active_level::horiz_sublevel_xsize > 
	active_level::horiz_sublevel_sprite_ipg_lists;


scr_entry active_level::bg0_screenblock_mirror[screenblock_size];



array_2d_helper<scr_entry> active_level::bg0_screenblock_2d
	( se_ram[bg0_sbb], screenblock_size_2d );
array_2d_helper<scr_entry> active_level::bg0_screenblock_mirror_2d 
	( bg0_screenblock_mirror, screenblock_size_2d );

const level* active_level::the_current_level_ptr;
u32 active_level::the_current_active_sublevel_index;



const sublevel_pointer& active_level::get_the_current_sublevel_ptr()
{
	return the_current_level_ptr->get_the_sublevels()
		[the_current_active_sublevel_index];
	//// temporary
	//return the_current_level_ptr->get_the_sublevels()[0];
}


