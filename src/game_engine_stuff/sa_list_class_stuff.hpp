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
	
	int next_node_index;
	
} __attribute__((_align4));



template< typename type, u32 max_size_plus_1 >
class sa_forward_list
{
//protected:		// variables
public:		// variables
	int front_node_index;
	
public:		// variables
	sa_list_node<type> the_array[max_size_plus_1];
	sa_free_list<max_size_plus_1> the_free_index_stack;
	
public:		// functions
	inline sa_forward_list()
	{
		clear();
	}
	inline sa_list_node<type>* front()
	{
		return &the_array[front_node_index];
	}
	
	inline sa_list_node<type>* get_next_node( sa_list_node<type>* pos )
	{
		if ( pos->next_node_index != -1 )
		{
			return &the_array[pos->next_node_index];
		}
		else
		{
			return &the_array[0];
		}
	}
	
	inline bool node_is_at_end( sa_list_node<type>* curr_node )
	{
		return the_array[curr_node->next_node_index].next_node_index == 0;
	}
	
	
	inline constexpr u32 get_max_size_plus_1() const
	{
		return max_size_plus_1;
	}
	
	
	inline void clear()
	{
		the_array[0].the_data = type();
		the_array[0].next_node_index = 0;
		
		for ( u32 i=1; i<max_size_plus_1; ++i )
		{
			the_array[i].the_data = type();
			the_array[i].next_node_index = -1;
		}
		
		memfill32( the_free_index_stack.the_array, 0, 
			sizeof(the_free_index_stack.the_array) / sizeof(u32) );
		the_free_index_stack.curr_index = 0;
		
		for ( int i=the_free_index_stack.get_size()-1; i>0; --i )
		{
			the_free_index_stack.push(i);
		}
		
		front_node_index = the_free_index_stack.pop();
	}
	
	inline void insert_after( sa_list_node<type>* pos, 
		const type& to_insert )
	{
		// Special code is used for inserting an element at the end of the
		// list.
		if ( pos->next_node_index == -1 )
		{
			pos->next_node_index = the_free_index_stack.pop();
			get_next_node(pos)->the_data = to_insert;
			get_next_node(pos)->next_node_index = -1;
		}
		else
		{
			int old_next_free_index = pos->next_node_index;
			
			pos->next_node_index = the_free_index_stack.pop();
			sa_list_node<type>* new_next_node = get_next_node(pos);
			
			new_next_node->the_data = to_insert;
			new_next_node->next_node_index = old_next_free_index;
		}
		
	}
	
	inline void erase_after( sa_list_node<type>* pos )
	{
		the_free_index_stack.push(pos->next_node_index);
		
		int new_next_node_index = get_next_node(pos)->next_node_index;
		
		get_next_node(pos)->the_data = type();
		get_next_node(pos)->next_node_index = -1;
		
		pos->next_node_index = new_next_node_index;
		
	}
	
	// This function 
	inline void push_front( const type& to_push )
	{
		int old_front_node_index = front_node_index;
		front_node_index = the_free_index_stack.pop();
		
		front()->the_data = to_push;
		front()->next_node_index = old_front_node_index;
	}
	
	
	// This function removes the first element of the list, including
	// deleting its data, and also changes front_node_index appropriately.
	inline void pop_front()
	{
		the_free_index_stack.push(front_node_index);
		
		int new_front_node_index = front()->next_node_index;
		
		front()->the_data = type();
		front()->next_node_index = -1;
		
		front_node_index = new_front_node_index;
		
	}
	
	
	
} __attribute__((_align4));



// This is a template class for a statically allocated array of
// modifiable singly-linked lists.  "sa" is short for 
// "statically allocated".
template< typename type, u32 arr_size, u32 num_list_elems >
class sa_array_of_forward_lists
{
public:		// variables
	sa_list_node<type>* the_outer_array[arr_size];
	sa_list_node<type> the_inner_array[num_list_elems];
	sa_free_list<num_list_elems> the_free_index_stack;
	
	
public:		// functions
	
	
} __attribute__((_align4));


#endif		// sa_list_class_stuff_hpp
