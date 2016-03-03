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


//#include "block_stuff.hpp"
#include "../level_stuff/active_level_class.hpp"

#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/dma_stuff.hpp"

#define X(name) name the_##name;
list_of_block_stuff_classes(X)
#undef X

std::array< block_base_stuff*, bt_count > block_stuff_array
= {
	#define X(name) &the_##name,
	list_of_block_stuff_classes(X)
	#undef X
};





