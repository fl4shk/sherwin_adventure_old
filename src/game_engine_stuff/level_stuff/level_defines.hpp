// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


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
