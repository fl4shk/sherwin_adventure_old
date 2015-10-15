#include "attribute_defines.hpp"
#include "button_stuff.hpp"
#include "../game_engine_stuff/prev_curr_pair_class.hpp"


// Global variables to hold the key state
//vu16 __key_curr __attribute__((_ewram)) = 0,
//	__key_prev __attribute__((_ewram)) = 0;

volatile prev_curr_pair<vu16> __key_state __attribute__((_iwram)) 
	= { 0, 0 };


bool soft_reset_keys_down()
{
	if ( ( key_hit(key_a) && key_hit_or_held(key_b) 
		&& key_hit_or_held(key_select) && key_hit_or_held(key_start) )
		|| ( key_hit_or_held(key_a) && key_hit(key_b)
		&& key_hit_or_held(key_select) && key_hit_or_held(key_start) )
		|| ( key_hit_or_held(key_a) && key_hit_or_held(key_b)
		&& key_hit(key_select) && key_hit_or_held(key_start) )
		|| ( key_hit_or_held(key_a) && key_hit_or_held(key_b) 
		&& key_hit_or_held(key_select) && key_hit(key_start) ) )
	{
		return true;
	}
	
	return false;
}
