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
#include "sa_stack_classes.hpp"



template< typename type >
class sa_list_node
{
public:		// variables
	type the_data __attribute__((_align4));
	//s32 next_node_index, prev_node_index;
	s16 next_node_index, prev_node_index;
	
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
	
	inline sa_list_node( const type& data_to_copy, s32 s_next_node_index,
		s32 s_prev_node_index ) : the_data(data_to_copy), 
		next_node_index((s16)s_next_node_index),
		prev_node_index((s16)s_prev_node_index)
	{
	}
	
} __attribute__((_align4));



//template< typename type >
//class sa_list_backend
//{
////public:		// variables
//protected:		// variables
//	int* ptr_to_front_node_index;
//	sa_list_node<type>* the_node_array;
//	sa_free_list_backend* ptr_to_the_free_list_backend;
//	u32 total_num_nodes;
//	
//public:		// functions
//	inline sa_list_backend() : ptr_to_front_node_index(0),
//		the_node_array(0), ptr_to_the_free_list_backend(0),
//		total_num_nodes(0)
//	{
//	}
//	inline sa_list_backend( int* s_ptr_to_front_node_index, 
//		sa_list_node<type>* s_the_node_array, 
//		sa_free_list_backend* s_ptr_to_the_free_list_backend,
//		u32 s_total_num_nodes ) :
//		ptr_to_front_node_index(s_ptr_to_front_node_index), 
//		the_node_array(s_the_node_array),
//		ptr_to_the_free_list_backend(s_ptr_to_the_free_list_backend),
//		total_num_nodes(s_total_num_nodes)
//	{
//	}
//	
//	inline ~sa_list_backend()
//	{
//		fully_deallocate();
//	}
//	
//	inline void init( int* n_ptr_to_front_node_index, 
//		sa_list_node<type>* n_the_node_array, 
//		sa_free_list_backend* n_ptr_to_the_free_list_backend,
//		u32 n_total_num_nodes )
//	{
//		ptr_to_front_node_index = n_ptr_to_front_node_index;
//		the_node_array = n_the_node_array;
//		ptr_to_the_free_list_backend = n_ptr_to_the_free_list_backend;
//		total_num_nodes = n_total_num_nodes;
//	}
//	
//	inline int& get_front_node_index()
//	{
//		return *ptr_to_front_node_index;
//	}
//	inline const int get_front_node_index() const
//	{
//		return *ptr_to_front_node_index;
//	}
//	
//	inline sa_list_node<type>* get_the_node_array()
//	{
//		return the_node_array;
//	}
//	inline const sa_list_node<type>* get_the_node_array() const
//	{
//		return the_node_array;
//	}
//	
//	inline sa_free_list_backend& get_the_free_list_backend()
//	{
//		return *ptr_to_the_free_list_backend;
//	}
//	inline const sa_free_list_backend& get_the_free_list_backend() const
//	{
//		return *ptr_to_the_free_list_backend;
//	}
//	
//	inline u32 get_total_num_nodes() const
//	{
//		return total_num_nodes;
//	}
//	
//	
//	
//	inline sa_list_node<type>& get_node_at( int node_index )
//	{
//		return get_the_node_array()[node_index];
//	}
//	inline sa_list_node<type>& front()
//	{
//		return get_node_at(get_front_node_index());
//	}
//	
//	inline sa_list_node<type>& get_next_node_after_node_index
//		( int node_index )
//	{
//		return get_node_at(get_node_at(node_index)
//			.next_node_index);
//	}
//	inline sa_list_node<type>& get_prev_node_before_node_index
//		( int node_index )
//	{
//		return get_node_at(get_node_at(node_index)
//			.prev_node_index);
//	}
//	
//	
//	
//	void fully_deallocate() __attribute__((noinline))
//	{
//		int& the_front_node_index = get_front_node_index();
//		//while ( get_front_node_index() != -1 )
//		while ( the_front_node_index >= 0 )
//		{
//			//erase_at(get_front_node_index());
//			erase_at(the_front_node_index);
//		}
//	}
//	
//	int push_front( const type& to_push )
//	{
//		// If there's nothing in the list
//		if ( get_front_node_index() == -1 )
//		{
//			get_front_node_index() = get_the_free_list_backend()
//				.peek_top();
//			get_the_free_list_backend().pop();
//			
//			front().the_data = to_push;
//			
//			// These two operations are for good measure, and they might
//			// not actually be necessary.
//			front().next_node_index = -1;
//			front().prev_node_index = -1;
//		}
//		// If there's at least one element in the list
//		else
//		{
//			int old_front_node_index = get_front_node_index();
//			get_front_node_index() = get_the_free_list_backend()
//				.peek_top();
//			get_the_free_list_backend().pop();
//			
//			get_node_at(old_front_node_index).prev_node_index 
//				= get_front_node_index();
//			
//			front().the_data = to_push;
//			front().next_node_index = old_front_node_index;
//			
//			// This operation is for good measure, and it might not
//			// actually be necessary.
//			front().prev_node_index = -1;
//		}
//		
//		return get_front_node_index();
//	}
//	
//	int push_front_new( const type& to_push ) __attribute__((noinline))
//	{
//		int& the_front_node_index = get_front_node_index();
//		int old_front_node_index = the_front_node_index;
//		
//		
//		//sa_list_node<type>& the_old_front_node 
//		//	= get_node_at(old_front_node_index);
//		
//		sa_free_list_backend& the_free_list_backend 
//			= get_the_free_list_backend();
//		
//		//the_front_node_index = get_the_free_list_backend().peek_top();
//		//get_the_free_list_backend().pop();
//		
//		the_front_node_index = the_free_list_backend.peek_top();
//		the_free_list_backend.pop();
//		
//		
//		sa_list_node<type>& the_front_node 
//			= get_node_at(the_front_node_index);
//		
//		
//		int new_next_node_index = -1;
//		
//		// If there's nothing in the list
//		//if ( the_front_node_index < 0 )
//		if ( old_front_node_index < 0 )
//		{
//			
//		}
//		// If there's at least one element in the list
//		else
//		{
//			new_next_node_index = old_front_node_index;
//			
//			get_node_at(old_front_node_index).prev_node_index
//				= the_front_node_index;
//		}
//		
//		
//		
//		the_front_node.the_data = to_push;
//		the_front_node.next_node_index = new_next_node_index;
//		the_front_node.prev_node_index = -1;
//		
//		return the_front_node_index;
//	}
//	
//	int insert_before_old( int node_index, const type& to_insert )
//	{
//		int old_prev_node_index = get_node_at(node_index)
//			.prev_node_index;
//		//int old_next_node_index = get_node_at(node_index)
//		//	.next_node_index;
//		
//		// If node_index == front_node_index
//		//if ( old_prev_node_index == -1 )
//		if ( node_index == get_front_node_index() )
//		{
//			return push_front(to_insert);
//		}
//		else
//		{
//			//int new_node_index = get_the_free_list_backend().pop();
//			int new_node_index = get_the_free_list_backend().peek_top();
//			get_the_free_list_backend().pop();
//			
//			get_node_at(old_prev_node_index).next_node_index
//				= new_node_index;
//			
//			get_node_at(new_node_index).the_data = to_insert;
//			get_node_at(new_node_index).prev_node_index 
//				= old_prev_node_index;
//			get_node_at(new_node_index).next_node_index 
//				= node_index;
//			
//			get_node_at(node_index).prev_node_index 
//				= new_node_index;
//			
//			return new_node_index;
//		}
//		
//		//return node_index;
//		//return new_node_index;
//	}
//	
//	int insert_before( int node_index, const type& to_insert )
//		__attribute__((noinline))
//	{
//		//int old_prev_node_index = get_node_at(node_index)
//		//	.prev_node_index;
//		////int old_next_node_index = get_node_at(node_index)
//		////	.next_node_index;
//		
//		// If node_index == front_node_index
//		//if ( old_prev_node_index == -1 )
//		if ( node_index == get_front_node_index() )
//		{
//			return push_front(to_insert);
//		}
//		else
//		{
//			sa_list_node<type>& node_at_node_index 
//				= get_node_at(node_index);
//			
//			const int old_prev_node_index 
//				= node_at_node_index.prev_node_index;
//			
//			const int new_node_index = get_the_free_list_backend()
//				.peek_top();
//			get_the_free_list_backend().pop();
//			
//			
//			sa_list_node<type>& node_at_new_node_index
//				= get_node_at(new_node_index);
//			
//			
//			get_node_at(old_prev_node_index).next_node_index
//				= new_node_index;
//			
//			node_at_new_node_index.the_data = to_insert;
//			node_at_new_node_index.prev_node_index = old_prev_node_index;
//			node_at_new_node_index.next_node_index = node_index;
//			
//			node_at_node_index.prev_node_index = new_node_index;
//			
//			return new_node_index;
//		}
//		
//		//return node_index;
//		//return new_node_index;
//	}
//	
//	
//	int insert_after_old( int node_index, const type& to_insert )
//	{
//		//int old_prev_node_index = get_node_at(node_index)
//		//	.prev_node_index;
//		int old_next_node_index = get_node_at(node_index)
//			.next_node_index;
//		
//		//int new_node_index = get_the_free_list_backend().pop();
//		int new_node_index = get_the_free_list_backend().peek_top();
//		get_the_free_list_backend().pop();
//		
//		// Special code is used for inserting an element at the end of the
//		// list.
//		if ( old_next_node_index == -1 )
//		{
//			get_node_at(node_index).next_node_index = new_node_index;
//			
//			get_node_at(new_node_index).the_data = to_insert;
//			get_node_at(new_node_index).next_node_index = -1;
//			get_node_at(new_node_index).prev_node_index = node_index;
//		}
//		else
//		{
//			get_node_at(old_next_node_index).prev_node_index
//				= new_node_index;
//			
//			get_node_at(node_index).next_node_index = new_node_index;
//			
//			get_node_at(new_node_index).the_data = to_insert;
//			get_node_at(new_node_index).next_node_index 
//				= old_next_node_index;
//			get_node_at(new_node_index).prev_node_index = node_index;
//		}
//		
//		//return node_index;
//		return new_node_index;
//	}
//	
//	int insert_after( int node_index, const type& to_insert )
//		__attribute__((noinline))
//	{
//		////int old_prev_node_index = get_node_at(node_index)
//		////	.prev_node_index;
//		//int old_next_node_index = get_node_at(node_index)
//		//	.next_node_index;
//		sa_list_node<type>& node_at_node_index = get_node_at(node_index);
//		const int old_next_node_index = node_at_node_index.next_node_index;
//		
//		//int new_node_index = get_the_free_list_backend().pop();
//		const int new_node_index = get_the_free_list_backend().peek_top();
//		get_the_free_list_backend().pop();
//		
//		
//		node_at_node_index.next_node_index = new_node_index;
//		
//		sa_list_node<type>& node_at_new_node_index 
//			= get_node_at(new_node_index);
//		
//		int new_next_node_index = -1;
//		
//		// Special code is used for inserting an element at the end of the
//		// list.
//		//if ( old_next_node_index < 0 )
//		//{
//		//	
//		//}
//		//else
//		if ( old_next_node_index >= 0 )
//		{
//			get_node_at(old_next_node_index).prev_node_index 
//				= new_node_index;
//			new_next_node_index = old_next_node_index;
//		}
//		
//		node_at_new_node_index.the_data = to_insert;
//		node_at_new_node_index.next_node_index = new_next_node_index;
//		node_at_new_node_index.prev_node_index = node_index;
//		
//		
//		//return node_index;
//		return new_node_index;
//	}
//	
//	void erase_at_old( int node_index )
//	{
//		int old_prev_node_index = get_node_at(node_index)
//			.prev_node_index,
//			old_next_node_index = get_node_at(node_index)
//			.next_node_index;
//		
//		// Special code is used for erasing an element at the beginning of
//		// the list.
//		//if ( old_prev_node_index == -1 )
//		if ( node_index == get_front_node_index() )
//		{
//			//int old_front_node_index = get_front_node_index();
//			
//			get_node_at(get_front_node_index()).the_data = type();
//			get_node_at(get_front_node_index()).next_node_index = -1;
//			get_node_at(get_front_node_index()).prev_node_index = -1;
//			
//			get_the_free_list_backend().push(get_front_node_index());
//			
//			get_front_node_index() = old_next_node_index;
//			
//			if ( old_next_node_index != -1 )
//			{
//				front().prev_node_index = -1;
//			}
//		}
//		else 
//		{
//			get_node_at(node_index).the_data = type();
//			get_node_at(node_index).next_node_index = -1;
//			get_node_at(node_index).prev_node_index = -1;
//			get_the_free_list_backend().push(node_index);
//			
//			if ( old_next_node_index != -1 )
//			{
//				get_node_at(old_prev_node_index).next_node_index
//					= old_next_node_index;
//				get_node_at(old_next_node_index).prev_node_index
//					= old_prev_node_index;
//			}
//			else
//			{
//				get_node_at(old_prev_node_index).next_node_index 
//					= -1;
//			}
//		}
//		
//	}
//	
//	void erase_at( int node_index ) __attribute__((noinline))
//	{
//		//int old_prev_node_index = get_node_at(node_index)
//		//	.prev_node_index,
//		//	old_next_node_index = get_node_at(node_index)
//		//	.next_node_index;
//		
//		sa_list_node<type>& node_at_node_index = get_node_at(node_index);
//		
//		const int old_prev_node_index = node_at_node_index.prev_node_index,
//			old_next_node_index = node_at_node_index.next_node_index;
//		
//		int& the_front_node_index = get_front_node_index();
//		const int old_front_node_index = the_front_node_index;
//		
//		//node_at_node_index.the_data = type();
//		//node_at_node_index.next_node_index = -1;
//		//node_at_node_index.prev_node_index = -1;
//		node_at_node_index = sa_list_node<type>();
//		
//		get_the_free_list_backend().push(node_index);
//		
//		if ( node_index == old_front_node_index )
//		{
//			the_front_node_index = old_next_node_index;
//			
//			if ( old_next_node_index >= 0 )
//			{
//				//front().prev_node_index = -1;
//				get_node_at(the_front_node_index).prev_node_index = -1;
//			}
//		}
//		else
//		{
//			sa_list_node<type>& old_prev_node 
//				= get_node_at(old_prev_node_index);
//			
//			if ( old_next_node_index >= 0 )
//			{
//				old_prev_node.next_node_index = old_next_node_index;
//				get_node_at(old_next_node_index).prev_node_index
//					= old_prev_node_index;
//			}
//			else
//			{
//				old_prev_node.next_node_index = -1;
//			}
//		}
//	}
//	
//	
//	int insertion_sort_old()
//	{
//		// Don't do anything if this list has zero or one nodes.
//		if ( get_front_node_index() == -1 )
//		{
//			return get_front_node_index();
//		}
//		if ( front().next_node_index == -1 )
//		{
//			return get_front_node_index();
//		}
//		
//		//externally_allocated_sa_list< type, total_num_nodes >
//		//	sorted_list( ptr_to_the_node_array, ptr_to_the_free_list );
//		int temp_front_node_index = -1;
//		sa_list_backend<type> sorted_list( &temp_front_node_index, 
//			the_node_array, ptr_to_the_free_list_backend, 
//			total_num_nodes );
//		
//		int curr_node_index = sorted_list.get_front_node_index();
//		
//		for ( int i=get_front_node_index();
//			i!=-1;  )
//			//i=get_node_at(i).next_node_index )
//		{
//			
//			//get_the_free_list_backend().debug_print();
//			
//			int index_of_node_with_lowest_value = i;
//			
//			// Find the lowest
//			for ( int j=index_of_node_with_lowest_value;
//				j!=-1;
//				j=get_node_at(j).next_node_index )
//			{
//				if ( get_node_at(j).the_data 
//					< get_node_at(index_of_node_with_lowest_value)
//					.the_data )
//				{
//					index_of_node_with_lowest_value = j;
//				}
//			}
//			
//			type data_to_push = get_node_at
//				(index_of_node_with_lowest_value).the_data;
//			
//			if ( i == index_of_node_with_lowest_value )
//			{
//				i = get_node_at(i).next_node_index;
//			}
//			
//			erase_at(index_of_node_with_lowest_value);
//			
//			if ( sorted_list.get_front_node_index() == -1 )
//			{
//				sorted_list.push_front(data_to_push);
//				curr_node_index = sorted_list.get_front_node_index();
//			}
//			else
//			{
//				sorted_list.insert_after( curr_node_index, data_to_push );
//				curr_node_index = sorted_list.get_node_at
//					(curr_node_index).next_node_index;
//			}
//			
//		}
//		
//		
//		get_front_node_index() = sorted_list.get_front_node_index();
//		
//		sorted_list.get_front_node_index() = -1;
//		
//		return get_front_node_index();
//	}
//	
//	
//	int insertion_sort() __attribute__((noinline))
//	{
//		int& the_front_node_index = get_front_node_index();
//		
//		// Don't do anything if this list has zero or one nodes.
//		if ( the_front_node_index < 0 )
//		{
//			return the_front_node_index;
//		}
//		if ( get_node_at(the_front_node_index).next_node_index < 0 )
//		{
//			return the_front_node_index;
//		}
//		
//		int temp_front_node_index = -1;
//		sa_list_backend<type> sorted_list( &temp_front_node_index, 
//			the_node_array, ptr_to_the_free_list_backend, 
//			total_num_nodes );
//		
//		int curr_node_index = temp_front_node_index;
//		
//		for ( int i=the_front_node_index;
//			i!=-1;  )
//			//i=get_node_at(i).next_node_index )
//		{
//			
//			//get_the_free_list_backend().debug_print();
//			
//			int index_low = i;
//			
//			sa_list_node<type>* node_at_j;
//			
//			// Find the lowest value at or after i.
//			for ( int j=index_low;
//				j!=-1; 
//				j=node_at_j->next_node_index )
//			{
//				node_at_j = &get_node_at(j);
//				
//				if ( node_at_j->the_data 
//					< get_node_at(index_low).the_data )
//				{
//					index_low = j;
//				}
//			}
//			
//			sa_list_node<type>& node_at_index_low = get_node_at(index_low);
//			const type data_to_move = node_at_index_low.the_data;
//			
//			if ( i == index_low )
//			{
//				i = node_at_index_low.next_node_index;
//			}
//			
//			erase_at(index_low);
//			
//			if ( temp_front_node_index < 0 )
//			{
//				sorted_list.push_front(data_to_move);
//				curr_node_index = temp_front_node_index;
//			}
//			else
//			{
//				sorted_list.insert_after( curr_node_index, data_to_move );
//				curr_node_index = sorted_list.get_node_at(curr_node_index)
//					.next_node_index;
//				
//			}
//			
//		}
//		
//		
//		the_front_node_index = temp_front_node_index;
//		
//		temp_front_node_index = -1;
//		
//		
//		return the_front_node_index;
//	}
//	
//	
//	
//} __attribute__((_align4));
//
//
//
//template< typename type, u32 total_num_nodes >
//class externally_allocated_sa_list
//{
//protected:		// variables
//	sa_list_backend<type> the_sa_list_backend;
//	
////protected:		// variables
//public:		// variables
//	int front_node_index;
//	
//public:		// variables
//	//array< sa_list_node<type>, total_num_nodes >* ptr_to_the_node_array;
//	sa_list_node<type>* the_node_array;
//	sa_free_list<total_num_nodes>* ptr_to_the_free_list;
//	
//	
//public:		// functions
//	
//	inline externally_allocated_sa_list() : the_sa_list_backend(), 
//		front_node_index(-1), the_node_array(NULL), 
//		ptr_to_the_free_list(NULL)
//	{
//	}
//	
//	inline externally_allocated_sa_list
//		( sa_list_node<type>* s_the_node_array,
//		sa_free_list<total_num_nodes>* s_ptr_to_the_free_list )
//		: front_node_index(-1)
//	{
//		the_node_array = s_the_node_array;
//		ptr_to_the_free_list = s_ptr_to_the_free_list;
//		init_the_sa_list_backend();
//	}
//	
//	inline ~externally_allocated_sa_list()
//	{
//		fully_deallocate();
//	}
//	
//	inline void init_the_sa_list_backend()
//	{
//		the_sa_list_backend.init( &get_front_node_index(), 
//			get_the_node_array(), 
//			&get_the_free_list().the_sa_free_list_backend,
//			get_total_num_nodes() );
//	}
//	
//	inline int& get_front_node_index()
//	{
//		return front_node_index;
//	}
//	inline const int get_front_node_index() const
//	{
//		return front_node_index;
//	}
//	
//	
//	//inline void set_ptr_to_the_node_array( array< sa_list_node<type>, 
//	//	total_num_nodes >* n_ptr_to_the_node_array )
//	//{
//	//	ptr_to_the_node_array = n_ptr_to_the_node_array;
//	//}
//	//inline array< sa_list_node<type>, total_num_nodes >& 
//	//	get_the_node_array()
//	//{
//	//	return *ptr_to_the_node_array;
//	//}
//	
//	inline void set_the_node_array( sa_list_node<type>* n_the_node_array )
//	{
//		the_node_array = n_the_node_array;
//	}
//	inline sa_list_node<type>* get_the_node_array()
//	{
//		return the_node_array;
//	}
//	
//	
//	inline void set_ptr_to_the_free_list( sa_free_list<total_num_nodes>*
//		n_ptr_to_the_free_list )
//	{
//		ptr_to_the_free_list = n_ptr_to_the_free_list;
//	}
//	inline sa_free_list<total_num_nodes>& get_the_free_list()
//	{
//		return *ptr_to_the_free_list;
//	}
//	
//	
//	inline sa_list_node<type>& get_node_at( int node_index )
//	{
//		return get_the_node_array()[node_index];
//	}
//	inline sa_list_node<type>& front()
//	{
//		return get_node_at(front_node_index);
//	}
//	
//	inline sa_list_node<type>& get_next_node_after_node_index
//		( int node_index )
//	{
//		return get_node_at(get_node_at(node_index)
//			.next_node_index);
//	}
//	inline sa_list_node<type>& get_prev_node_before_node_index
//		( int node_index )
//	{
//		return get_node_at(get_node_at(node_index)
//			.prev_node_index);
//	}
//	
//	inline u32 get_total_num_nodes() const
//	{
//		return total_num_nodes;
//		//return the_sa_list_backend.get_total_num_nodes();
//	}
//	
//	
//	inline void fully_deallocate()
//	{
//		the_sa_list_backend.fully_deallocate();
//	}
//	
//	int push_front( const type& to_push )
//	{
//		return the_sa_list_backend.push_front(to_push);
//	}
//	
//	
//	int insert_before( int node_index, const type& to_insert )
//	{
//		return the_sa_list_backend.insert_before( node_index, to_insert );
//	}
//	
//	int insert_after( int node_index, const type& to_insert )
//	{
//		return the_sa_list_backend.insert_after( node_index, to_insert );
//	}
//	
//	void erase_at( int node_index )
//	{
//		the_sa_list_backend.erase_at(node_index);
//	}
//	
//	// This function is dangerous!  There might not be enough nodes left in
//	// the extreme case!
//	inline void move_node_before_basic( int original_node_index, 
//		int new_node_index )
//	{
//		type data_to_move = get_node_at(original_node_index)
//			.the_data;
//		
//		insert_before( new_node_index, data_to_move );
//		erase_at(original_node_index);
//	}
//	
//	
//	inline int insertion_sort()
//	{
//		return the_sa_list_backend.insertion_sort();
//	}
//	
//} __attribute__((_align4));



template< typename type >
class externally_allocated_sa_list
{
//public:		// variables
protected:		// variables
	//int* ptr_to_front_node_index;
	s32 front_node_index;
	sa_list_node<type>* the_node_array;
	sa_free_list_backend* ptr_to_the_free_list_backend;
	u32 total_num_nodes;
	
public:		// functions
	inline externally_allocated_sa_list() : front_node_index(-1),
		the_node_array(0), ptr_to_the_free_list_backend(0),
		total_num_nodes(0)
	{
	}
	inline externally_allocated_sa_list
		( sa_list_node<type>* s_the_node_array, 
		sa_free_list_backend* s_ptr_to_the_free_list_backend,
		u32 s_total_num_nodes ) : front_node_index(-1),
		the_node_array(s_the_node_array),
		ptr_to_the_free_list_backend(s_ptr_to_the_free_list_backend),
		total_num_nodes(s_total_num_nodes)
	{
	}
	
	inline ~externally_allocated_sa_list()
	{
		fully_deallocate();
	}
	
	inline void init( sa_list_node<type>* n_the_node_array, 
		sa_free_list_backend* n_ptr_to_the_free_list_backend,
		u32 n_total_num_nodes )
	{
		the_node_array = n_the_node_array;
		ptr_to_the_free_list_backend = n_ptr_to_the_free_list_backend;
		total_num_nodes = n_total_num_nodes;
	}
	
	inline s32& get_front_node_index()
	{
		return front_node_index;
	}
	inline const s32 get_front_node_index() const
	{
		return front_node_index;
	}
	
	inline sa_list_node<type>* get_the_node_array()
	{
		return the_node_array;
	}
	inline const sa_list_node<type>* get_the_node_array() const
	{
		return the_node_array;
	}
	
	inline sa_free_list_backend& get_the_free_list_backend()
	{
		return *ptr_to_the_free_list_backend;
	}
	inline const sa_free_list_backend& get_the_free_list_backend() const
	{
		return *ptr_to_the_free_list_backend;
	}
	
	inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	
	
	inline sa_list_node<type>& get_node_at( s32 node_index )
	{
		return get_the_node_array()[node_index];
	}
	inline sa_list_node<type>& front()
	{
		return get_node_at(get_front_node_index());
	}
	
	inline sa_list_node<type>& get_next_node_after_node_index
		( s32 node_index )
	{
		return get_node_at(get_node_at(node_index)
			.next_node_index);
	}
	inline sa_list_node<type>& get_prev_node_before_node_index
		( s32 node_index )
	{
		return get_node_at(get_node_at(node_index)
			.prev_node_index);
	}
	
	
	
	void fully_deallocate() __attribute__((noinline))
	{
		s32& the_front_node_index = get_front_node_index();
		//while ( get_front_node_index() != -1 )
		while ( the_front_node_index >= 0 )
		{
			//erase_at(get_front_node_index());
			erase_at(the_front_node_index);
		}
	}
	
	s32 push_front_old( const type& to_push )
	{
		// If there's nothing in the list
		if ( get_front_node_index() == -1 )
		{
			get_front_node_index() = get_the_free_list_backend()
				.peek_top();
			get_the_free_list_backend().pop();
			
			front().the_data = to_push;
			
			// These two operations are for good measure, and they might
			// not actually be necessary.
			front().next_node_index = -1;
			front().prev_node_index = -1;
		}
		// If there's at least one element in the list
		else
		{
			s32 old_front_node_index = get_front_node_index();
			get_front_node_index() = get_the_free_list_backend()
				.peek_top();
			get_the_free_list_backend().pop();
			
			get_node_at(old_front_node_index).prev_node_index 
				= get_front_node_index();
			
			front().the_data = to_push;
			front().next_node_index = old_front_node_index;
			
			// This operation is for good measure, and it might not
			// actually be necessary.
			front().prev_node_index = -1;
		}
		
		return get_front_node_index();
	}
	
	s32 push_front( const type& to_push ) __attribute__((noinline))
	{
		s32& the_front_node_index = get_front_node_index();
		s32 old_front_node_index = the_front_node_index;
		
		
		//sa_list_node<type>& the_old_front_node 
		//	= get_node_at(old_front_node_index);
		
		sa_free_list_backend& the_free_list_backend 
			= get_the_free_list_backend();
		
		//the_front_node_index = get_the_free_list_backend().peek_top();
		//get_the_free_list_backend().pop();
		
		the_front_node_index = the_free_list_backend.peek_top();
		the_free_list_backend.pop();
		
		
		sa_list_node<type>& the_front_node 
			= get_node_at(the_front_node_index);
		
		
		s32 new_next_node_index = -1;
		
		// If there's nothing in the list
		//if ( the_front_node_index < 0 )
		if ( old_front_node_index < 0 )
		{
			
		}
		// If there's at least one element in the list
		else
		{
			new_next_node_index = old_front_node_index;
			
			get_node_at(old_front_node_index).prev_node_index
				= the_front_node_index;
		}
		
		
		
		the_front_node.the_data = to_push;
		the_front_node.next_node_index = new_next_node_index;
		the_front_node.prev_node_index = -1;
		
		return the_front_node_index;
	}
	
	s32 insert_before_old( s32 node_index, const type& to_insert )
	{
		s32 old_prev_node_index = get_node_at(node_index)
			.prev_node_index;
		//s32 old_next_node_index = get_node_at(node_index)
		//	.next_node_index;
		
		// If node_index == front_node_index
		//if ( old_prev_node_index == -1 )
		if ( node_index == get_front_node_index() )
		{
			return push_front(to_insert);
		}
		else
		{
			//s32 new_node_index = get_the_free_list_backend().pop();
			s32 new_node_index = get_the_free_list_backend().peek_top();
			get_the_free_list_backend().pop();
			
			get_node_at(old_prev_node_index).next_node_index
				= new_node_index;
			
			get_node_at(new_node_index).the_data = to_insert;
			get_node_at(new_node_index).prev_node_index 
				= old_prev_node_index;
			get_node_at(new_node_index).next_node_index 
				= node_index;
			
			get_node_at(node_index).prev_node_index 
				= new_node_index;
			
			return new_node_index;
		}
		
		//return node_index;
		//return new_node_index;
	}
	
	s32 insert_before( s32 node_index, const type& to_insert )
		__attribute__((noinline))
	{
		//s32 old_prev_node_index = get_node_at(node_index)
		//	.prev_node_index;
		////s32 old_next_node_index = get_node_at(node_index)
		////	.next_node_index;
		
		// If node_index == front_node_index
		//if ( old_prev_node_index == -1 )
		if ( node_index == get_front_node_index() )
		{
			return push_front(to_insert);
		}
		else
		{
			sa_list_node<type>& node_at_node_index 
				= get_node_at(node_index);
			
			const s32 old_prev_node_index 
				= node_at_node_index.prev_node_index;
			
			const s32 new_node_index = get_the_free_list_backend()
				.peek_top();
			get_the_free_list_backend().pop();
			
			
			sa_list_node<type>& node_at_new_node_index
				= get_node_at(new_node_index);
			
			
			get_node_at(old_prev_node_index).next_node_index
				= new_node_index;
			
			node_at_new_node_index.the_data = to_insert;
			node_at_new_node_index.prev_node_index = old_prev_node_index;
			node_at_new_node_index.next_node_index = node_index;
			
			node_at_node_index.prev_node_index = new_node_index;
			
			return new_node_index;
		}
		
		//return node_index;
		//return new_node_index;
	}
	
	
	s32 insert_after_old( s32 node_index, const type& to_insert )
	{
		//s32 old_prev_node_index = get_node_at(node_index)
		//	.prev_node_index;
		s32 old_next_node_index = get_node_at(node_index)
			.next_node_index;
		
		//s32 new_node_index = get_the_free_list_backend().pop();
		s32 new_node_index = get_the_free_list_backend().peek_top();
		get_the_free_list_backend().pop();
		
		// Special code is used for inserting an element at the end of the
		// list.
		if ( old_next_node_index == -1 )
		{
			get_node_at(node_index).next_node_index = new_node_index;
			
			get_node_at(new_node_index).the_data = to_insert;
			get_node_at(new_node_index).next_node_index = -1;
			get_node_at(new_node_index).prev_node_index = node_index;
		}
		else
		{
			get_node_at(old_next_node_index).prev_node_index
				= new_node_index;
			
			get_node_at(node_index).next_node_index = new_node_index;
			
			get_node_at(new_node_index).the_data = to_insert;
			get_node_at(new_node_index).next_node_index 
				= old_next_node_index;
			get_node_at(new_node_index).prev_node_index = node_index;
		}
		
		//return node_index;
		return new_node_index;
	}
	
	s32 insert_after( s32 node_index, const type& to_insert )
		__attribute__((noinline))
	{
		////s32 old_prev_node_index = get_node_at(node_index)
		////	.prev_node_index;
		//s32 old_next_node_index = get_node_at(node_index)
		//	.next_node_index;
		sa_list_node<type>& node_at_node_index = get_node_at(node_index);
		const s32 old_next_node_index = node_at_node_index.next_node_index;
		
		//s32 new_node_index = get_the_free_list_backend().pop();
		const s32 new_node_index = get_the_free_list_backend().peek_top();
		get_the_free_list_backend().pop();
		
		
		node_at_node_index.next_node_index = new_node_index;
		
		sa_list_node<type>& node_at_new_node_index 
			= get_node_at(new_node_index);
		
		s32 new_next_node_index = -1;
		
		// Special code is used for inserting an element at the end of the
		// list.
		//if ( old_next_node_index < 0 )
		//{
		//	
		//}
		//else
		if ( old_next_node_index >= 0 )
		{
			get_node_at(old_next_node_index).prev_node_index 
				= new_node_index;
			new_next_node_index = old_next_node_index;
		}
		
		node_at_new_node_index.the_data = to_insert;
		node_at_new_node_index.next_node_index = new_next_node_index;
		node_at_new_node_index.prev_node_index = node_index;
		
		
		//return node_index;
		return new_node_index;
	}
	
	void erase_at_old( s32 node_index )
	{
		s32 old_prev_node_index = get_node_at(node_index)
			.prev_node_index,
			old_next_node_index = get_node_at(node_index)
			.next_node_index;
		
		// Special code is used for erasing an element at the beginning of
		// the list.
		//if ( old_prev_node_index == -1 )
		if ( node_index == get_front_node_index() )
		{
			//s32 old_front_node_index = get_front_node_index();
			
			get_node_at(get_front_node_index()).the_data = type();
			get_node_at(get_front_node_index()).next_node_index = -1;
			get_node_at(get_front_node_index()).prev_node_index = -1;
			
			get_the_free_list_backend().push(get_front_node_index());
			
			get_front_node_index() = old_next_node_index;
			
			if ( old_next_node_index != -1 )
			{
				front().prev_node_index = -1;
			}
		}
		else 
		{
			get_node_at(node_index).the_data = type();
			get_node_at(node_index).next_node_index = -1;
			get_node_at(node_index).prev_node_index = -1;
			get_the_free_list_backend().push(node_index);
			
			if ( old_next_node_index != -1 )
			{
				get_node_at(old_prev_node_index).next_node_index
					= old_next_node_index;
				get_node_at(old_next_node_index).prev_node_index
					= old_prev_node_index;
			}
			else
			{
				get_node_at(old_prev_node_index).next_node_index 
					= -1;
			}
		}
		
	}
	
	void erase_at( s32 node_index ) __attribute__((noinline))
	{
		//s32 old_prev_node_index = get_node_at(node_index)
		//	.prev_node_index,
		//	old_next_node_index = get_node_at(node_index)
		//	.next_node_index;
		
		sa_list_node<type>& node_at_node_index = get_node_at(node_index);
		
		const s32 old_prev_node_index = node_at_node_index.prev_node_index,
			old_next_node_index = node_at_node_index.next_node_index;
		
		s32& the_front_node_index = get_front_node_index();
		const s32 old_front_node_index = the_front_node_index;
		
		//node_at_node_index.the_data = type();
		//node_at_node_index.next_node_index = -1;
		//node_at_node_index.prev_node_index = -1;
		node_at_node_index = sa_list_node<type>();
		
		get_the_free_list_backend().push(node_index);
		
		if ( node_index == old_front_node_index )
		{
			the_front_node_index = old_next_node_index;
			
			if ( old_next_node_index >= 0 )
			{
				//front().prev_node_index = -1;
				get_node_at(the_front_node_index).prev_node_index = -1;
			}
		}
		else
		{
			sa_list_node<type>& old_prev_node 
				= get_node_at(old_prev_node_index);
			
			if ( old_next_node_index >= 0 )
			{
				old_prev_node.next_node_index = old_next_node_index;
				get_node_at(old_next_node_index).prev_node_index
					= old_prev_node_index;
			}
			else
			{
				old_prev_node.next_node_index = -1;
			}
		}
	}
	
	
	s32 insertion_sort_old()
	{
		// Don't do anything if this list has zero or one nodes.
		if ( get_front_node_index() == -1 )
		{
			return get_front_node_index();
		}
		if ( front().next_node_index == -1 )
		{
			return get_front_node_index();
		}
		
		////externally_allocated_sa_list< type, total_num_nodes >
		////	sorted_list( ptr_to_the_node_array, ptr_to_the_free_list );
		//s32 temp_front_node_index = -1;
		//sa_list_backend<type> sorted_list( &temp_front_node_index, 
		//	the_node_array, ptr_to_the_free_list_backend, 
		//	total_num_nodes );
		externally_allocated_sa_list<type> sorted_list( the_node_array, 
			ptr_to_the_free_list_backend, get_total_num_nodes() );
		
		s32 curr_node_index = sorted_list.get_front_node_index();
		
		for ( s32 i=get_front_node_index();
			i!=-1;  )
			//i=get_node_at(i).next_node_index )
		{
			
			//get_the_free_list_backend().debug_prs32();
			
			s32 index_of_node_with_lowest_value = i;
			
			// Find the lowest
			for ( s32 j=index_of_node_with_lowest_value;
				j!=-1;
				j=get_node_at(j).next_node_index )
			{
				if ( get_node_at(j).the_data 
					< get_node_at(index_of_node_with_lowest_value)
					.the_data )
				{
					index_of_node_with_lowest_value = j;
				}
			}
			
			type data_to_push = get_node_at
				(index_of_node_with_lowest_value).the_data;
			
			if ( i == index_of_node_with_lowest_value )
			{
				i = get_node_at(i).next_node_index;
			}
			
			erase_at(index_of_node_with_lowest_value);
			
			if ( sorted_list.get_front_node_index() == -1 )
			{
				sorted_list.push_front(data_to_push);
				curr_node_index = sorted_list.get_front_node_index();
			}
			else
			{
				sorted_list.insert_after( curr_node_index, data_to_push );
				curr_node_index = sorted_list.get_node_at
					(curr_node_index).next_node_index;
			}
			
		}
		
		
		get_front_node_index() = sorted_list.get_front_node_index();
		
		sorted_list.get_front_node_index() = -1;
		
		return get_front_node_index();
	}
	
	
	s32 insertion_sort() __attribute__((noinline))
	{
		s32& the_front_node_index = get_front_node_index();
		
		// Don't do anything if this list has zero or one nodes.
		if ( the_front_node_index < 0 )
		{
			return the_front_node_index;
		}
		if ( get_node_at(the_front_node_index).next_node_index < 0 )
		{
			return the_front_node_index;
		}
		
		//s32 temp_front_node_index = -1;
		//sa_list_backend<type> sorted_list( &temp_front_node_index, 
		//	the_node_array, ptr_to_the_free_list_backend, 
		//	total_num_nodes );
		externally_allocated_sa_list<type> sorted_list( the_node_array, 
			ptr_to_the_free_list_backend, get_total_num_nodes() );
		
		s32& temp_front_node_index = sorted_list.get_front_node_index();
		
		s32 curr_node_index = temp_front_node_index;
		
		for ( s32 i=the_front_node_index;
			i!=-1;  )
			//i=get_node_at(i).next_node_index )
		{
			
			//get_the_free_list_backend().debug_prs32();
			
			s32 index_low = i;
			
			sa_list_node<type>* node_at_j;
			
			// Find the lowest value at or after i.
			for ( s32 j=index_low;
				j!=-1; 
				j=node_at_j->next_node_index )
			{
				node_at_j = &get_node_at(j);
				
				if ( node_at_j->the_data 
					< get_node_at(index_low).the_data )
				{
					index_low = j;
				}
			}
			
			sa_list_node<type>& node_at_index_low = get_node_at(index_low);
			const type data_to_move = node_at_index_low.the_data;
			
			if ( i == index_low )
			{
				i = node_at_index_low.next_node_index;
			}
			
			erase_at(index_low);
			
			if ( temp_front_node_index < 0 )
			{
				sorted_list.push_front(data_to_move);
				curr_node_index = temp_front_node_index;
			}
			else
			{
				sorted_list.insert_after( curr_node_index, data_to_move );
				curr_node_index = sorted_list.get_node_at(curr_node_index)
					.next_node_index;
			}
			
		}
		
		
		the_front_node_index = temp_front_node_index;
		
		temp_front_node_index = -1;
		
		
		return the_front_node_index;
	}
	
	
	
} __attribute__((_align4));



// This is a template class for a statically allocated array of modifiable
// doubly-linked lists.  "sa" is short for "statically allocated".
template< typename type, u32 total_num_nodes, u32 num_lists >
class sa_array_of_lists
{
public:		// variables
	//array< externally_allocated_sa_list< type, total_num_nodes >, 
	//	num_lists > the_array;
	//array< sa_list_node<type>, total_num_nodes > the_node_array;
	
	externally_allocated_sa_list<type> the_array[num_lists];
	sa_list_node<type> the_node_array[total_num_nodes];
	
	sa_free_list<total_num_nodes> the_free_list;
	
public:		// functions
	
	inline sa_array_of_lists()
	{
		//for ( auto& the_list : the_array )
		//{
		//	the_list.set_the_node_array(the_node_array.data());
		//	the_list.set_ptr_to_the_free_list(&the_free_list);
		//	the_list.init_the_sa_list_backend();
		//}
		
		//for ( s32 i=(s32)get_the_node_array_size()-1; i>=0; --i )
		//{
		//	the_node_array[i] = sa_list_node<type>();
		//}
		
		for ( s32 i=(s32)get_the_array_size()-1; i>=0; --i )
		{
			//the_array[i].set_the_node_array(the_node_array);
			//the_array[i].set_ptr_to_the_free_list(&the_free_list);
			//the_array[i].init_the_sa_list_backend();
			the_array[i].init( the_node_array,
				&the_free_list.the_sa_free_list_backend, 
				get_total_num_nodes() );
		}
		
		
	}
	
	inline constexpr u32 get_the_array_size() const
	{
		return get_num_lists();
	}
	inline constexpr u32 get_the_node_array_size() const
	{
		return get_total_num_nodes();
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
