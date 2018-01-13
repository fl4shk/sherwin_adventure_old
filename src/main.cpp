// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 Andrew Clark (FL4SHK).
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


#include "gba_specific_stuff/asm_funcs.hpp"

#include "gba_specific_stuff/button_stuff.hpp"
#include "gba_specific_stuff/gfx_reg_stuff.hpp"
#include "gba_specific_stuff/oam_entry_classes.hpp"
#include "gba_specific_stuff/interrupt_stuff.hpp"
#include "gba_specific_stuff/bios_function_wrappers.hpp"
#include "gba_specific_stuff/dma_stuff.hpp"
//#include "gba_specific_stuff/sound_reg_stuff.hpp"
#include "gba_specific_stuff/timer_stuff.hpp"
#include "gba_specific_stuff/profiling_stuff.hpp"


#include "general_utility_stuff/fixed_classes.hpp"
#include "general_utility_stuff/trigonometry_funcs.hpp"
#include "general_utility_stuff/array_2d_helper_classes.hpp"

#include "general_utility_stuff/free_list_allocator_base_class.hpp"
#include "general_utility_stuff/debug_vars.hpp"
#include "general_utility_stuff/sa_array_of_lists_class.hpp"

#include "gba_specific_stuff/interrupt_stuff.hpp"


#include "game_engine_stuff/overlay_loader_stuff.hpp"
#include "game_engine_stuff/subsystem_stuff.hpp"


#include "testing/overlay_testing_stuff.hpp"
#include "testing/game_mode_handler_testing_stuff.hpp"
#include "testing/free_list_allocator_testing_stuff.hpp"
#include "testing/linear_allocator_testing_stuff.hpp"


//[[_iwram_code]] 
//int real_main();
int real_main();






int main()
{
	//test_game_mode_handler();

	//test_free_list_allocator();

	test_linear_allocators();


	return real_main();
}



int real_main()
{
	gba::irq_init();



	for (;;)
	{
		//DebugArrGroup::clear_debug_vars();

		gba::bios_wait_for_vblank();
	}

	return 9000;
}
