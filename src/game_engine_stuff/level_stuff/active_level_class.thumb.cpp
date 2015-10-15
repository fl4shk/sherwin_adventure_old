#include "active_level_class.hpp"
#include "../sprite_stuff/sprite_class.hpp"
#include "sprite_level_data_stuff.hpp"


// This will eat up 64 kiB of EWRAM.
block active_level::block_data_array[block_data_array_size] 
	__attribute__((_ewram));


// This will eat up 32 kiB of EWRAM.
// active_level::persistent_block_data_arrays is a 2D array of extra data.
// Each "row" within this 2D array is to be "claimed" by one of the
// sublevels within a level
u16 active_level::persistent_block_data_arrays[max_num_sublevels]
	[persistent_block_data_array_size] __attribute__((_ewram));


// horiz_level_block_data_2d is an array_2d_helper that wraps the access
// to block_data_array for horizontal levels.  Support for vertical
// levels MIGHT come later.
array_2d_helper<block> active_level::horiz_level_block_data_2d 
	( active_level::block_data_array, active_level::horiz_level_size_2d );


std::array< std::forward_list<sprite_init_param_group>, 
	active_level::horiz_level_xsize > 
	active_level::horiz_level_sprite_ipg_lists __attribute__((_ewram));



