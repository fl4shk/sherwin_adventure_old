#ifndef level_defines_hpp
#define level_defines_hpp


#include "../misc_types.hpp"


// WARNING:  Changing max_num_sublevels_per_level will change the number
// of arrays of persistent block data that are statically allocated in
// the active_level class.
// With max_num_sublevels_per_level == 8, 32 kiB of EWRAM are used by
// active_level::persistent_block_data_arrays.

constexpr u32 max_num_sublevels_per_level = 8;



#endif		// level_defines_hpp
