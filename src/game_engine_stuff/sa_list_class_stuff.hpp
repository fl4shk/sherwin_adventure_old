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


#ifndef sa_list_class_stuff_hpp
#define sa_list_class_stuff_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
//#include "sa_dyn_array_class.hpp"
#include "sa_stack_class.hpp"




template< typename type >
class sa_list_node
{
public:		// variables
	type the_data;
	int next_node_index, prev_node_index;
	
public:		// functions
	inline sa_list_node() : the_data(type()), next_node_index(-1),
		prev_node_index(-1)
	{
	}
	
	//inline sa_list_node()
	//{
	//	the_data = type();
	//	next_node_index = -1;
	//	prev_node_index = -1;
	//}
	
	inline sa_list_node( const type& data_to_copy, int s_next_node_index,
		int s_prev_node_index ) : the_data(data_to_copy), 
		next_node_index(s_next_node_index),
		prev_node_index(s_prev_node_index)
	{
	}
	
} __attribute__((_align4));


template< typename type, u32 total_num_nodes >
class externally_allocated_sa_list
{
//protected:		// variables
public:		// variables
	int front_node_index;
	
public:		// variables
	array< sa_list_node<type>, total_num_nodes >* ptr_to_the_node_array;
	sa_free_list<total_num_nodes>* ptr_to_the_free_list;
	
	
public:		// functions
	
	inline externally_allocated_sa_list() : front_node_index(-1), 
		ptr_to_the_node_array(NULL), ptr_to_the_free_list(NULL)
	{
	}
	
	inline externally_allocated_sa_list( array< sa_list_node<type>,
		total_num_nodes >* s_ptr_to_the_node_array,
		sa_free_list<total_num_nodes>* s_ptr_to_the_free_list )
		: front_node_index(-1)
	{
		ptr_to_the_node_array = s_ptr_to_the_node_array;
		ptr_to_the_free_list = s_ptr_to_the_free_list;
	}
	
	virtual inline ~externally_allocated_sa_list()
	{
		fully_deallocate();
	}
	
	inline void fully_deallocate()
	{
		while ( front_node_index != -1 )
		{
			erase_at(front_node_index);
		}
	}
	
	
	inline void set_ptr_to_the_node_array( array< sa_list_node<type>, 
		total_num_nodes >* n_ptr_to_the_node_array )
	{
		ptr_to_the_node_array = n_ptr_to_the_node_array;
	}
	inline array< sa_list_node<type>, total_num_nodes >& 
		get_the_node_array()
	{
		return *ptr_to_the_node_array;
	}
	
	
	inline void set_ptr_to_the_free_list( sa_free_list<total_num_nodes>*
		n_ptr_to_the_free_list )
	{
		ptr_to_the_free_list = n_ptr_to_the_free_list;
	}
	inline sa_free_list<total_num_nodes>& get_the_free_list()
	{
		return *ptr_to_the_free_list;
	}
	
	
	inline sa_list_node<type>& get_node_at_node_index( int node_index )
	{
		return get_the_node_array()[node_index];
	}
	inline sa_list_node<type>& front()
	{
		return get_node_at_node_index(front_node_index);
	}
	
	inline sa_list_node<type>& get_next_node_after_node_index
		( int node_index )
	{
		return get_node_at_node_index(get_node_at_node_index(node_index)
			.next_node_index);
	}
	inline sa_list_node<type>& get_prev_node_before_node_index
		( int node_index )
	{
		return get_node_at_node_index(get_node_at_node_index(node_index)
			.prev_node_index);
	}
	
	inline void push_front( const type& to_push )
	{
		// If there's nothing in the list
		if ( front_node_index == -1 )
		{
			front_node_index = get_the_free_list().peek_top();
			get_the_free_list().pop();
			
			front().the_data = to_push;
			
			// These two operations are for good measure, and they might
			// not actually be necessary.
			front().next_node_index = -1;
			front().prev_node_index = -1;
		}
		// If there's at least one element in the list
		else
		{
			
			int old_front_node_index = front_node_index;
			front_node_index = get_the_free_list().peek_top();
			get_the_free_list().pop();
			
			get_node_at_node_index(old_front_node_index).prev_node_index 
				= front_node_index;
			
			front().the_data = to_push;
			front().next_node_index = old_front_node_index;
			
			// This operation is for good measure, and it might not
			// actually be necessary.
			front().prev_node_index = -1;
		}
	}
	
	
	inline void insert_before( int node_index, const type& to_insert )
	{
		int old_prev_node_index = get_node_at_node_index(node_index)
			.prev_node_index;
		//int old_next_node_index = get_node_at_node_index(node_index)
		//	.next_node_index;
		
		// If node_index == front_node_index
		//if ( old_prev_node_index == -1 )
		if ( node_index == front_node_index )
		{
			push_front(to_insert);
		}
		else
		{
			//int new_node_index = get_the_free_list().pop();
			int new_node_index = get_the_free_list().peek_top();
			get_the_free_list().pop();
			
			get_node_at_node_index(old_prev_node_index).next_node_index
				= new_node_index;
			
			get_node_at_node_index(new_node_index).the_data = to_insert;
			get_node_at_node_index(new_node_index).prev_node_index 
				= old_prev_node_index;
			get_node_at_node_index(new_node_index).next_node_index 
				= node_index;
			
			get_node_at_node_index(node_index).prev_node_index 
				= new_node_index;
		}
	}
	
	inline void insert_after( int node_index, const type& to_insert )
	{
		//int old_prev_node_index = get_node_at_node_index(node_index)
		//	.prev_node_index;
		int old_next_node_index = get_node_at_node_index(node_index)
			.next_node_index;
		
		//int new_node_index = get_the_free_list().pop();
		int new_node_index = get_the_free_list().peek_top();
		get_the_free_list().pop();
		
		// Special code is used for inserting an element at the end of the
		// list.
		if ( old_next_node_index == -1 )
		{
			get_node_at_node_index(node_index).next_node_index 
				= new_node_index;
			
			get_node_at_node_index(new_node_index).the_data = to_insert;
			get_node_at_node_index(new_node_index).next_node_index = -1;
			get_node_at_node_index(new_node_index).prev_node_index 
				= node_index;
		}
		else
		{
			get_node_at_node_index(node_index).next_node_index 
				= new_node_index;
			
			get_node_at_node_index(new_node_index).the_data = to_insert;
			get_node_at_node_index(new_node_index).next_node_index 
				= old_next_node_index;
			get_node_at_node_index(new_node_index).prev_node_index
				= node_index;
		}
	}
	
	inline void erase_at( int node_index )
	{
		int old_prev_node_index = get_node_at_node_index(node_index)
			.prev_node_index,
			old_next_node_index = get_node_at_node_index(node_index)
			.next_node_index;
		
		// Special code is used for erasing an element at the beginning of
		// the list.
		//if ( old_prev_node_index == -1 )
		if ( node_index == front_node_index )
		{
			//int old_front_node_index = front_node_index;
			
			get_node_at_node_index(front_node_index).the_data = type();
			get_node_at_node_index(front_node_index).next_node_index = -1;
			get_node_at_node_index(front_node_index).prev_node_index = -1;
			
			get_the_free_list().push(front_node_index);
			
			front_node_index = old_next_node_index;
			
			if ( old_next_node_index != -1 )
			{
				front().prev_node_index = -1;
			}
		}
		else 
		{
			get_node_at_node_index(node_index).the_data = type();
			get_node_at_node_index(node_index).next_node_index = -1;
			get_node_at_node_index(node_index).prev_node_index = -1;
			get_the_free_list().push(node_index);
			
			if ( old_next_node_index != -1 )
			{
				get_node_at_node_index(old_prev_node_index).next_node_index
					= old_next_node_index;
				get_node_at_node_index(old_next_node_index).prev_node_index
					= old_prev_node_index;
			}
			else
			{
				get_node_at_node_index(old_prev_node_index).next_node_index 
					= -1;
			}
		}
		
	}
	
	// This function is dangerous!  There might not be enough nodes left in
	// the extreme case!
	inline void move_node_before_basic( int original_node_index, 
		int new_node_index )
	{
		type data_to_move = get_node_at_node_index(original_node_index)
			.the_data;
		
		insert_before( new_node_index, data_to_move );
		erase_at(original_node_index);
	}
	
	
	inline void insertion_sort()
	{
		// Don't do anything if this list has zero or one nodes.
		if ( front_node_index == -1 )
		{
			return;
		}
		if ( front().next_node_index == -1 )
		{
			return;
		}
		
		externally_allocated_sa_list< type, total_num_nodes >
			sorted_list( ptr_to_the_node_array, ptr_to_the_free_list );
		
		int curr_node_index = sorted_list.front_node_index;
		
		for ( int i=front_node_index;
			i!=-1;  )
			//i=get_node_at_node_index(i).next_node_index )
		{
			
			//get_the_free_list().debug_print();
			
			int index_of_node_with_lowest_value = i;
			
			// Find the lowest
			for ( int j=index_of_node_with_lowest_value;
				j!=-1;
				j=get_node_at_node_index(j).next_node_index )
			{
				if ( get_node_at_node_index(j).the_data 
					< get_node_at_node_index
					(index_of_node_with_lowest_value).the_data )
				{
					index_of_node_with_lowest_value = j;
				}
				
			}
			
			type data_to_push = get_node_at_node_index
				(index_of_node_with_lowest_value).the_data;
			
			if ( i == index_of_node_with_lowest_value )
			{
				i = get_node_at_node_index(i).next_node_index;
			}
			
			erase_at(index_of_node_with_lowest_value);
			
			if ( sorted_list.front_node_index == -1 )
			{
				sorted_list.push_front(data_to_push);
				curr_node_index = sorted_list.front_node_index;
			}
			else
			{
				sorted_list.insert_after( curr_node_index, data_to_push );
				curr_node_index = sorted_list.get_node_at_node_index
					(curr_node_index).next_node_index;
			}
			
		}
		
		
		front_node_index = sorted_list.front_node_index;
		
		sorted_list.front_node_index = -1;
		
	}
	
} __attribute__((_align4));


// This is a template class for a statically allocated array of modifiable
// doubly-linked lists.  "sa" is short for "statically allocated".
template< typename type, u32 total_num_nodes, u32 num_lists >
class sa_array_of_lists
{
public:		// variables
	array< externally_allocated_sa_list< type, total_num_nodes >, 
		num_lists > the_array;
	array< sa_list_node<type>, total_num_nodes > the_node_array;
	sa_free_list<total_num_nodes> the_free_list;
	
public:		// functions
	
	inline sa_array_of_lists()
	{
		for ( auto& the_list : the_array )
		{
			the_list.set_ptr_to_the_node_array(&the_node_array);
			the_list.set_ptr_to_the_free_list(&the_free_list);
		}
	}
	
	inline constexpr u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	inline constexpr u32 get_num_lists() const
	{
		return num_lists;
	}
	
} __attribute__((_align4));






#endif		// sa_list_class_stuff_hpp
