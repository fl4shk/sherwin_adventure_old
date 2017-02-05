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


#ifndef sprite_level_data_stuff_hpp
#define sprite_level_data_stuff_hpp

//#include "../sa_stack_class.hpp"
#include "../sprite_stuff/sprite_type_stuff.hpp"

// This is pretty self explanatory, right?  Sprites that are not active can
// be spawned.  Sprites that are active can't be spawned.  Sprites that are
// dead can't be spawned.
enum sprite_spawn_state
{
	sss_not_active,
	sss_active,
	sss_dead,
	
} __attribute__((_align4));



class sprite_init_param_group
{
public:		// variables
	// The type of sprite
	//const sprite_type type;
	sprite_type type;
	
	// The initial in-level x coordinate, divided by 16
	//const u32 initial_block_grid_x_coord;
	u32 initial_block_grid_x_coord;
	
	// The initial in-level y coordinate, divided by 16
	//const u32 initial_block_grid_y_coord;
	u32 initial_block_grid_y_coord;
	
	// Here is a s
	//const bool facing_right;
	bool facing_right;
	
	// Here are extra parameters that are used in different ways depending
	// on the type of sprite.
	//const u32 extra_param_0;
	//const u32 extra_param_1;
	//const u32 extra_param_2;
	//const u32 extra_param_3;
	u32 extra_param_0;
	u32 extra_param_1;
	u32 extra_param_2;
	u32 extra_param_3;
	
	// The despawned/spawned/dead information is merged into the
	// sprite_init_param_group class.  For sprite_init_param_group's in
	// ROM, this is supposed to be set to sss_not_active.
	sprite_spawn_state spawn_state;
	
public:		// functions
	
	
	inline bool operator == ( const sprite_init_param_group& other ) const
	{
		return ( ( initial_block_grid_x_coord 
			== other.initial_block_grid_x_coord )
			&& ( initial_block_grid_y_coord 
			== other.initial_block_grid_y_coord ) );
	}
	inline bool operator != ( const sprite_init_param_group& other ) const
	{
		return !( *this == other );
	}
	
	// This function is included so that an std::forward_list of
	// sprite_init_param_group's can be sorted in ascending order by the
	// std::forward_list::sort() method.  The sorting is to be done based
	// on the initial_block_grid_x_coord parameter, followed by the
	// initial_block_grid_y_coord parameter.
	inline bool operator < ( const sprite_init_param_group& other ) const
	{
		if ( initial_block_grid_x_coord 
			< other.initial_block_grid_x_coord)
		{
			return true;
		}
		else if ( initial_block_grid_x_coord
			> other.initial_block_grid_x_coord )
		{
			return false;
		}
		//else if ( initial_block_grid_x_coord 
		//	== other.initial_block_grid_x_coord )
		//{
		//	return ( initial_block_grid_y_coord 
		//		< other.initial_block_grid_y_coord );
		//}
		
		return ( initial_block_grid_y_coord 
			< other.initial_block_grid_y_coord );
	}
	
	inline bool operator > ( const sprite_init_param_group& other ) const
	{
		if ( initial_block_grid_x_coord 
			> other.initial_block_grid_x_coord)
		{
			return true;
		}
		else if ( initial_block_grid_x_coord
			< other.initial_block_grid_x_coord )
		{
			return false;
		}
		//else if ( initial_block_grid_x_coord 
		//	== other.initial_block_grid_x_coord )
		//{
		//	return ( initial_block_grid_y_coord 
		//		< other.initial_block_grid_y_coord );
		//}
		
		return ( initial_block_grid_y_coord 
			> other.initial_block_grid_y_coord );
	}
	
	inline bool operator <= ( const sprite_init_param_group& other ) const
	{
		return ( (*this) < other || (*this) == other );
	}
	inline bool operator >= ( const sprite_init_param_group& other ) const
	{
		return ( (*this) > other || (*this) == other );
	}
	
	
} __attribute__((_align4));







#endif		// sprite_level_data_stuff_hpp
