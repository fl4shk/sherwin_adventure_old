#include "misc_utility_funcs.hpp"

#include "game_manager_class.hpp"

void halt()
{
	game_manager::curr_game_mode = gm_do_halt;
	
	for (;;)
	{
		bios_wait_for_vblank();
	}
}
