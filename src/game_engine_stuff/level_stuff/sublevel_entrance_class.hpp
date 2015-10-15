#ifndef sublevel_entrance_class_hpp
#define sublevel_entrance_class_hpp

#include "../../gba_specific_stuff/attribute_defines.hpp"
#include "../vec2_class.hpp"

enum sublevel_entrance_type
{
	sle_start_of_level,
	
	sle_from_warp_block,
	
	// The number of level entrance types is automatically updated by the
	// compiler via the le_count enum id
	sle_count,
} __attribute__((_align4));


class sublevel_entrance
{
public:		// variables
	
	sublevel_entrance_type type;
	
	vec2_f24p8 in_level_pos;
	
} __attribute__((_align4));


#endif		// sublevel_entrance_class_hpp
