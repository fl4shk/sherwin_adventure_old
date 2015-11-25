#include "gfx_reg_stuff.hpp"

#include "../game_engine_stuff/fixed_classes.hpp"

prev_curr_pair<bg_point> bgofs_mirror[bgofs_mirror_size];


// Current component arrays, stored in EWRAM as fixed24p8's for speed and
// accuracy reasons.
fixed24p8 bg_fade_curr_red_arr[bg_fade_curr_component_arr_size];
fixed24p8 bg_fade_curr_green_arr[bg_fade_curr_component_arr_size];
fixed24p8 bg_fade_curr_blue_arr[bg_fade_curr_component_arr_size];

fixed24p8 obj_fade_curr_red_arr[obj_fade_curr_component_arr_size];
fixed24p8 obj_fade_curr_green_arr[obj_fade_curr_component_arr_size];
fixed24p8 obj_fade_curr_blue_arr[obj_fade_curr_component_arr_size];



// Fade out/in step amounts.
fixed24p8 bg_fade_red_step_amount_arr[bg_fade_step_amount_arr_size];
fixed24p8 bg_fade_green_step_amount_arr[bg_fade_step_amount_arr_size];
fixed24p8 bg_fade_blue_step_amount_arr[bg_fade_step_amount_arr_size];

fixed24p8 obj_fade_red_step_amount_arr[obj_fade_step_amount_arr_size];
fixed24p8 obj_fade_green_step_amount_arr[obj_fade_step_amount_arr_size];
fixed24p8 obj_fade_blue_step_amount_arr[obj_fade_step_amount_arr_size];



