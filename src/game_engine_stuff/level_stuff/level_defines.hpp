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


#ifndef level_defines_hpp
#define level_defines_hpp


#include "../../general_utility_stuff/misc_types.hpp"


// WARNING:  Changing max_num_sublevels_per_level will change the number of
// arrays of persistent block data that are allocated in the active_level
// class.
// With max_num_sublevels_per_level == 8, 32 kiB of EWRAM are used by
// active_level::persistent_block_data_arrays.

constexpr u32 max_num_sublevels_per_level = 8;



#endif		// level_defines_hpp
