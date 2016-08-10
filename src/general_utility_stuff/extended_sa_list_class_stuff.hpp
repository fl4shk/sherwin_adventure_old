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


#ifndef extended_sa_list_class_stuff_hpp
#define extended_sa_list_class_stuff_hpp

#include "sa_list_class_stuff.hpp"

// This is a template class intended for use as a BASE CLASS for classes
// that act as statically-allocated linked lists.  Since some (or possibly 
// all) of the derived classes use only some of the non-constructor member
// functions, 
template< typename type, u32 total_num_nodes >
class regular_sa_list_base
{
protected:		// variables
//public:		// variables
	externally_allocated_sa_list<type> the_externally_allocated_sa_list;
	sa_list_node<type> the_node_array[total_num_nodes];
	sa_free_list<total_num_nodes> the_free_list;
	
public:		// functions
	
	
protected:		// functions
	// This may be the first time I've ever made a constructor protected.
	inline regular_sa_list_base() : the_externally_allocated_sa_list
		( the_node_array, &the_free_list.the_sa_free_list_backend, 
		get_total_num_nodes() )
	{
	}
	
	inline s32& get_front_node_index()
	{
		return the_externally_allocated_sa_list.get_front_node_index();
	}
	inline const s32 get_front_node_index() const
	{
		return the_externally_allocated_sa_list.get_front_node_index();
	}
	
	inline sa_list_node<type>* get_the_node_array()
	{
		return the_node_array;
	}
	inline const sa_list_node<type>* get_the_node_array() const
	{
		return the_node_array;
	}
	
	inline sa_free_list<total_num_nodes>& get_the_free_list()
	{
		return the_free_list;
	}
	inline const sa_free_list<total_num_nodes>& get_the_free_list() const
	{
		return the_free_list;
	}
	constexpr inline u32 get_the_node_array_size() const
	{
		return get_total_num_nodes();
	}
	constexpr inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	inline sa_list_node<type>& get_node_at( s32 node_index )
	{
		return get_the_node_array()[node_index];
	}
	inline sa_list_node<type>& front()
	{
		//return get_node_at(get_front_node_index());
		return the_externally_allocated_sa_list.front();
	}
	
	inline void fully_deallocate()
	{
		the_externally_allocated_sa_list.fully_deallocate();
	}
	
	
	inline s32 push_front( const type& to_push )
	{
		return the_externally_allocated_sa_list.push_front(to_push);
	}
	inline s32 push_front( type&& to_push )
	{
		return the_externally_allocated_sa_list.push_front
			(std::move(to_push));
	}
	inline s32 pop_front_basic()
	{
		return the_externally_allocated_sa_list.pop_front_basic();
	}
	
	
	inline s32 insert_before( s32 node_index, const type& to_insert )
	{
		return the_externally_allocated_sa_list.insert_before( node_index,
			to_insert );
	}
	inline s32 insert_before( s32 node_index, type&& to_insert )
	{
		return the_externally_allocated_sa_list.insert_before( node_index,
			std::move(to_insert) );
	}
	
	
	inline s32 insert_after( s32 node_index, const type& to_insert )
	{
		return the_externally_allocated_sa_list.insert_after( node_index,
			to_insert );
	}
	inline s32 insert_after( s32 node_index, type&& to_insert )
	{
		return the_externally_allocated_sa_list.insert_after( node_index,
			std::move(to_insert) );
	}
	
	inline void erase_at( s32 node_index )
	{
		the_externally_allocated_sa_list.erase_at(node_index);
	}
	inline s32 insertion_sort_old_2()
	{
		return the_externally_allocated_sa_list.insertion_sort_old_2();
	}
	inline s32 insertion_sort()
	{
		return the_externally_allocated_sa_list.insertion_sort();
	}
	inline s32 merge_sort()
	{
		return the_externally_allocated_sa_list.merge_sort();
	}
	
} __attribute__((_align4));


template< typename type, u32 total_num_nodes >
class regular_sa_list 
	: public regular_sa_list_base< type, total_num_nodes >
{
public:		// typedefs
	typedef regular_sa_list_base< type, total_num_nodes >
		specific_regular_sa_list_base;
	
public:		// functions
	inline regular_sa_list() : specific_regular_sa_list_base()
	{
	}
	
	inline s32& get_front_node_index()
	{
		return specific_regular_sa_list_base::get_front_node_index();
	}
	inline const s32 get_front_node_index() const
	{
		return specific_regular_sa_list_base::get_front_node_index();
	}
	
	inline sa_list_node<type>* get_the_node_array()
	{
		return specific_regular_sa_list_base::get_the_node_array();
	}
	inline const sa_list_node<type>* get_the_node_array() const
	{
		return specific_regular_sa_list_base::get_the_node_array();
	}
	
	inline sa_free_list<total_num_nodes>& get_the_free_list()
	{
		return specific_regular_sa_list_base::get_the_free_list();
	}
	inline const sa_free_list<total_num_nodes>& get_the_free_list() const
	{
		return specific_regular_sa_list_base::get_the_free_list();
	}
	constexpr inline u32 get_the_node_array_size() const
	{
		return get_total_num_nodes();
	}
	constexpr inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	inline sa_list_node<type>& get_node_at( s32 node_index )
	{
		return specific_regular_sa_list_base::get_node_at(node_index);
	}
	inline sa_list_node<type>& front()
	{
		//return get_node_at(get_front_node_index());
		return specific_regular_sa_list_base::front();
	}
	
	inline void fully_deallocate()
	{
		specific_regular_sa_list_base::fully_deallocate();
	}
	
	
	inline s32 push_front( const type& to_push )
	{
		return specific_regular_sa_list_base::push_front(to_push);
	}
	inline s32 push_front( type&& to_push )
	{
		return specific_regular_sa_list_base::push_front
			(std::move(to_push));
	}
	inline s32 pop_front_basic()
	{
		return specific_regular_sa_list_base::pop_front_basic();
	}
	
	
	inline s32 insert_before( s32 node_index, const type& to_insert )
	{
		return specific_regular_sa_list_base::insert_before( node_index,
			to_insert );
	}
	inline s32 insert_before( s32 node_index, type&& to_insert )
	{
		return specific_regular_sa_list_base::insert_before( node_index,
			std::move(to_insert) );
	}
	
	
	inline s32 insert_after( s32 node_index, const type& to_insert )
	{
		return specific_regular_sa_list_base::insert_after( node_index,
			to_insert );
	}
	inline s32 insert_after( s32 node_index, type&& to_insert )
	{
		return specific_regular_sa_list_base::insert_after( node_index,
			std::move(to_insert) );
	}
	
	
	inline void erase_at( s32 node_index )
	{
		specific_regular_sa_list_base::erase_at(node_index);
	}
	inline s32 insertion_sort_old_2()
	{
		return specific_regular_sa_list_base::insertion_sort_old_2();
	}
	inline s32 insertion_sort()
	{
		return specific_regular_sa_list_base::insertion_sort();
	}
	inline s32 merge_sort()
	{
		return specific_regular_sa_list_base::merge_sort();
	}
	
} __attribute__((_align4));


// For extra fun, this class's name can be abbreviated "sa sa list".  It is
// intended to always be sorted, though it does not have to be in some
// cases.
template< typename type, u32 total_num_nodes >
class sorted_always_sa_list 
	: public regular_sa_list_base< type, total_num_nodes >
{
public:		// typedefs
	typedef regular_sa_list_base< type, total_num_nodes >
		specific_regular_sa_list_base;
	
public:		// functions
	inline sorted_always_sa_list() 
		: specific_regular_sa_list_base()
	{
	}
	
	inline s32& get_front_node_index()
	{
		return specific_regular_sa_list_base::get_front_node_index();
	}
	inline const s32 get_front_node_index() const
	{
		return specific_regular_sa_list_base::get_front_node_index();
	}
	
	inline sa_list_node<type>* get_the_node_array()
	{
		return specific_regular_sa_list_base::get_the_node_array();
	}
	inline const sa_list_node<type>* get_the_node_array() const
	{
		return specific_regular_sa_list_base::get_the_node_array();
	}
	
	inline sa_free_list<total_num_nodes>& get_the_free_list()
	{
		return specific_regular_sa_list_base::get_the_free_list();
	}
	inline const sa_free_list<total_num_nodes>& get_the_free_list() const
	{
		return specific_regular_sa_list_base::get_the_free_list();
	}
	constexpr inline u32 get_the_node_array_size() const
	{
		return get_total_num_nodes();
	}
	constexpr inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	inline void fully_deallocate()
	{
		specific_regular_sa_list_base::fully_deallocate();
	}
	
	
	inline sa_list_node<type>& get_node_at( s32 node_index )
	{
		return specific_regular_sa_list_base::get_node_at(node_index);
	}
	inline sa_list_node<type>& front()
	{
		//return get_node_at(get_front_node_index());
		return specific_regular_sa_list_base::front();
	}
	
	inline s32 push_front( const type& to_push )
	{
		return specific_regular_sa_list_base::push_front(to_push);
	}
	inline s32 push_front( type&& to_push )
	{
		return specific_regular_sa_list_base::push_front
			(std::move(to_push));
	}
	inline s32 pop_front_basic()
	{
		return specific_regular_sa_list_base::pop_front_basic();
	}
	inline s32 insert_and_sort( const type& to_insert )
	{
		specific_regular_sa_list_base::push_front(to_insert);
		
		return specific_regular_sa_list_base::insertion_sort();
	}
	inline s32 insert_and_sort( type&& to_insert )
	{
		specific_regular_sa_list_base::push_front(std::move(to_insert));
		
		return specific_regular_sa_list_base::insertion_sort();
	}
	
	
	// There is no need to sort the list after erasing a single node.  This
	// is because the list was already sorted to begin with.
	inline void erase_at( s32 node_index )
	{
		specific_regular_sa_list_base::erase_at(node_index);
	}
	
	inline s32 insertion_sort_old_2()
	{
		return specific_regular_sa_list_base::insertion_sort_old_2();
	}
	inline s32 insertion_sort()
	{
		return specific_regular_sa_list_base::insertion_sort();
	}
	inline s32 merge_sort()
	{
		return specific_regular_sa_list_base::merge_sort();
	}
	
} __attribute__((_align4));


#endif		// extended_sa_list_class_stuff_hpp
