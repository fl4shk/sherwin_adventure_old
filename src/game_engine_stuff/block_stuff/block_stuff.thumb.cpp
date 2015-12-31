//#include "block_stuff.hpp"
#include "../level_stuff/active_level_class.hpp"

#include "../../gba_specific_stuff/gfx_reg_stuff.hpp"
#include "../../gba_specific_stuff/dma_stuff.hpp"

// A graphics-less block that sprites are free to move through.
air_block_stuff the_air_block_stuff;

// A block that looks like a wooden log.  It is indestructible, which
// is quite unlike real life wooden logs.
log_block_stuff the_log_block_stuff;

// A wooden block without anything inside.  It is destroyed (that is,
// replaced with an air block) when strongly hit.
wood_block_stuff the_wood_block_stuff;

// An eyes block without anything inside.  It becomes an empty block
// upon being strongly hit.
eyes_block_stuff the_eyes_block_stuff;

// A block with an exclamation point on it.  The purpose of these
// blocks is yet to be chosen, but I'm thinking that some kind of event
// will happen when one is strongly hit.
exclam_block_stuff the_exclam_block_stuff;

// An empty block that is indestructible.  
dud_block_stuff the_dud_block_stuff;

// Wooden blocks with contents
wood_block_with_bt_dud_stuff 
	the_wood_block_with_bt_dud_stuff;
wood_block_with_st_waffle_stuff 
	the_wood_block_with_st_waffle_stuff;
wood_block_with_st_muffin_stuff 
	the_wood_block_with_st_muffin_stuff;
wood_block_with_st_fire_muffin_stuff 
	the_wood_block_with_st_fire_muffin_stuff;
wood_block_with_st_ice_muffin_stuff 
	the_wood_block_with_st_ice_muffin_stuff;
wood_block_with_st_chocolate_muffin_stuff 
	the_wood_block_with_st_chocolate_muffin_stuff;

// Eyes blocks with contents
eyes_block_with_st_waffle_stuff 
	the_eyes_block_with_st_waffle_stuff;
eyes_block_with_st_muffin_stuff 
	the_eyes_block_with_st_muffin_stuff;
eyes_block_with_st_fire_muffin_stuff 
	the_eyes_block_with_st_fire_muffin_stuff;
eyes_block_with_st_ice_muffin_stuff 
	the_eyes_block_with_st_ice_muffin_stuff;
eyes_block_with_st_chocolate_muffin_stuff 
	the_eyes_block_with_st_chocolate_muffin_stuff;

// Grass/Dirt blocks
grass_single_block_stuff the_grass_single_block_stuff;

grass_top_left_block_stuff the_grass_top_left_block_stuff;
grass_top_middle_block_stuff the_grass_top_middle_block_stuff;
grass_top_right_block_stuff the_grass_top_right_block_stuff;

dirt_middle_left_block_stuff the_dirt_middle_left_block_stuff;
dirt_middle_middle_block_stuff the_dirt_middle_middle_block_stuff;
dirt_middle_right_block_stuff the_dirt_middle_right_block_stuff;

dirt_bottom_left_block_stuff the_dirt_bottom_left_block_stuff;
dirt_bottom_middle_block_stuff the_dirt_bottom_middle_block_stuff;
dirt_bottom_right_block_stuff the_dirt_bottom_right_block_stuff;

// 45 degree angle slope
grass_slope_p16_p16_block_stuff the_grass_slope_p16_p16_block_stuff;

// 135 degree angle slope
grass_slope_n16_p16_block_stuff the_grass_slope_n16_p16_block_stuff;

// Approximately 26.57 degrees angle slope, with two blocks
grass_slope_p32_p16_short_block_stuff 
	the_grass_slope_p32_p16_short_block_stuff;
grass_slope_p32_p16_tall_block_stuff 
	the_grass_slope_p32_p16_tall_block_stuff;

// Approximately 153.43 degrees angle slope, with two blocks
grass_slope_n32_p16_tall_block_stuff 
	the_grass_slope_n32_p16_tall_block_stuff;
grass_slope_n32_p16_short_block_stuff 
	the_grass_slope_n32_p16_short_block_stuff;

// These two blocks are for decoration
grass_in_slope_left_block_stuff the_grass_in_slope_left_block_stuff;
grass_in_slope_right_block_stuff the_grass_in_slope_right_block_stuff;


block_base_stuff* block_stuff_array[bt_count]
= {
	// A graphics-less block that sprites are free to move through.
	&the_air_block_stuff,
	
	// A block that looks like a wooden log.  It is indestructible, which
	// is quite unlike real life wooden logs.
	&the_log_block_stuff,
	
	// A wooden block without anything inside.  It is destroyed (that is,
	// replaced with an air block) when strongly hit.
	&the_wood_block_stuff,
	
	// An eyes block without anything inside.  It becomes an empty block
	// upon being strongly hit.
	&the_eyes_block_stuff,
	
	// A block with an exclamation point on it.  The purpose of these
	// blocks is yet to be chosen, but I'm thinking that some kind of event
	// will happen when one is strongly hit.
	&the_exclam_block_stuff,
	
	// An empty block that is indestructible.  
	&the_dud_block_stuff,
	
	// Wooden blocks with contents
	&the_wood_block_with_bt_dud_stuff,
	&the_wood_block_with_st_waffle_stuff,
	&the_wood_block_with_st_muffin_stuff,
	&the_wood_block_with_st_fire_muffin_stuff,
	&the_wood_block_with_st_ice_muffin_stuff,
	&the_wood_block_with_st_chocolate_muffin_stuff,
	
	// Eyes blocks with contents
	&the_eyes_block_with_st_waffle_stuff,
	&the_eyes_block_with_st_muffin_stuff,
	&the_eyes_block_with_st_fire_muffin_stuff,
	&the_eyes_block_with_st_ice_muffin_stuff,
	&the_eyes_block_with_st_chocolate_muffin_stuff,
	
	// Grass/Dirt blocks
	&the_grass_single_block_stuff,
	
	&the_grass_top_left_block_stuff,
	&the_grass_top_middle_block_stuff,
	&the_grass_top_right_block_stuff,
	
	&the_dirt_middle_left_block_stuff,
	&the_dirt_middle_middle_block_stuff,
	&the_dirt_middle_right_block_stuff,
	
	&the_dirt_bottom_left_block_stuff,
	&the_dirt_bottom_middle_block_stuff,
	&the_dirt_bottom_right_block_stuff,
	
	// 45 degree angle slope
	&the_grass_slope_p16_p16_block_stuff,
	
	// 135 degree angle slope
	&the_grass_slope_n16_p16_block_stuff,
	
	// Approximately 26.57 degrees angle slope, with two blocks
	&the_grass_slope_p32_p16_short_block_stuff,
	&the_grass_slope_p32_p16_tall_block_stuff,
	
	// Approximately 153.43 degrees angle slope, with two blocks
	&the_grass_slope_n32_p16_tall_block_stuff,
	&the_grass_slope_n32_p16_short_block_stuff,
	
	// These two blocks are for decoration
	&the_grass_in_slope_left_block_stuff,
	&the_grass_in_slope_right_block_stuff,
	
	
};





