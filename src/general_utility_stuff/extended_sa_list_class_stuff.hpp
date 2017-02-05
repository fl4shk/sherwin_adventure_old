// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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

namespace sa_list_stuff
{

// This is a template class intended for use as a BASE CLASS for classes
// that act as statically-allocated linked lists.  Since some (or possibly 
// all) of the derived classes use only some of the non-constructor member
// functions, 
template< typename type, u32 total_num_nodes >
class regular_list_base
{
//protected:		// variables
public:		// variables
	externally_allocated_list<type> the_externally_allocated_list;
	node<type> node_array[total_num_nodes];
	sa_free_list<total_num_nodes> the_free_list;
	
	s32& front_index;
	s32& back_index;
	
public:		// functions
	
	
protected:		// functions
	// This may be the first time I've ever made a constructor protected.
	inline regular_list_base() : the_externally_allocated_list
		( node_array, &the_free_list.the_sa_free_list_backend, 
		get_total_num_nodes() ), front_index(the_externally_allocated_list
		.get_front_index()), back_index(the_externally_allocated_list
		.get_back_index())
	{
	}
	
	inline s32& get_front_index()
	{
		//return the_externally_allocated_list.get_front_index();
		return front_index;
	}
	inline const s32 get_front_index() const
	{
		//return the_externally_allocated_list.get_front_index();
		return front_index;
	}
	inline s32& get_back_index()
	{
		//return the_externally_allocated_list.get_back_index();r
		return back_index;
	}
	inline const s32 get_back_index() const
	{
		//return the_externally_allocated_list.get_back_index();r
		return back_index;
	}
	
	inline node<type>* get_node_array()
	{
		return node_array;
	}
	inline const node<type>* get_node_array() const
	{
		return node_array;
	}
	
	inline sa_free_list<total_num_nodes>& get_the_free_list()
	{
		return the_free_list;
	}
	inline const sa_free_list<total_num_nodes>& get_the_free_list() const
	{
		return the_free_list;
	}
	constexpr inline u32 get_node_array_size() const
	{
		return get_total_num_nodes();
	}
	constexpr inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	inline node<type>& get_node_at( s32 index )
	{
		return get_node_array()[index];
	}
	inline node<type>& front()
	{
		//return get_node_at(get_front_index());
		return the_externally_allocated_list.front();
	}
	
	inline void fully_deallocate()
	{
		the_externally_allocated_list.fully_deallocate();
	}
	inline void fully_deallocate_via_unlink()
	{
		the_externally_allocated_list.fully_deallocate_via_unlink();
	}
	
	
	inline s32 push_front( const type& to_push )
	{
		return the_externally_allocated_list.push_front(to_push);
	}
	inline s32 push_front( type&& to_push )
	{
		return the_externally_allocated_list.push_front
			(std::move(to_push));
	}
	inline s32 push_back( const type& to_push )
	{
		return the_externally_allocated_list.push_back(to_push);
	}
	inline s32 push_back( type&& to_push )
	{
		return the_externally_allocated_list.push_back
			(std::move(to_push));
	}
	
	inline s32 pop_front_basic()
	{
		return the_externally_allocated_list.pop_front_basic();
	}
	inline s32 pop_back_basic()
	{
		return the_externally_allocated_list.pop_back_basic();
	}
	
	
	inline s32 insert_before( s32 index, const type& to_insert )
	{
		return the_externally_allocated_list.insert_before( index,
			to_insert );
	}
	inline s32 insert_before( s32 index, type&& to_insert )
	{
		return the_externally_allocated_list.insert_before( index,
			std::move(to_insert) );
	}
	
	
	inline s32 insert_after( s32 index, const type& to_insert )
	{
		return the_externally_allocated_list.insert_after( index,
			to_insert );
	}
	inline s32 insert_after( s32 index, type&& to_insert )
	{
		return the_externally_allocated_list.insert_after( index,
			std::move(to_insert) );
	}
	
	
	inline void erase_at( s32 index )
	{
		the_externally_allocated_list.erase_at(index);
	}
	inline s32 insertion_sort_old_2()
	{
		return the_externally_allocated_list.insertion_sort_old_2();
	}
	inline s32 insertion_sort_old_3()
	{
		return the_externally_allocated_list.insertion_sort_old_3();
	}
	inline s32 insertion_sort()
	{
		return the_externally_allocated_list.insertion_sort();
	}
	inline s32 merge_sort_via_array()
	{
		return the_externally_allocated_list.merge_sort_via_array();
	}
	inline s32 merge_sort_via_array_2()
	{
		return the_externally_allocated_list.merge_sort_via_array_2();
	}
	
} __attribute__((_align4));


template< typename type, u32 total_num_nodes >
class regular_list : public regular_list_base< type, total_num_nodes >
{
public:		// typedefs
	typedef regular_list_base< type, total_num_nodes > base;
	
public:		// functions
	inline regular_list() : base()
	{
	}
	
	inline s32& get_front_index()
	{
		return base::get_front_index();
	}
	inline const s32 get_front_index() const
	{
		return base::get_front_index();
	}
	inline s32& get_back_index()
	{
		return base::get_back_index();
	}
	inline const s32 get_back_index() const
	{
		return base::get_back_index();
	}
	
	inline node<type>* get_node_array()
	{
		return base::get_node_array();
	}
	inline const node<type>* get_node_array() const
	{
		return base::get_node_array();
	}
	
	inline sa_free_list<total_num_nodes>& get_the_free_list()
	{
		return base::get_the_free_list();
	}
	inline const sa_free_list<total_num_nodes>& get_the_free_list() const
	{
		return base::get_the_free_list();
	}
	constexpr inline u32 get_node_array_size() const
	{
		return get_total_num_nodes();
	}
	constexpr inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	inline node<type>& get_node_at( s32 index )
	{
		return base::get_node_at(index);
	}
	inline node<type>& front()
	{
		//return get_node_at(get_front_index());
		return base::front();
	}
	
	inline void fully_deallocate()
	{
		base::fully_deallocate();
	}
	inline void fully_deallocate_via_unlink()
	{
		base::fully_deallocate_via_unlink();
	}
	
	
	inline s32 push_front( const type& to_push )
	{
		return base::push_front(to_push);
	}
	inline s32 push_front( type&& to_push )
	{
		return base::push_front(std::move(to_push));
	}
	inline s32 push_back( const type& to_push )
	{
		return base::push_back(to_push);
	}
	inline s32 push_back( type&& to_push )
	{
		return base::push_back(std::move(to_push));
	}
	
	inline s32 pop_front_basic()
	{
		return base::pop_front_basic();
	}
	inline s32 pop_back_basic()
	{
		return base::pop_back_basic();
	}
	
	
	inline s32 insert_before( s32 index, const type& to_insert )
	{
		return base::insert_before( index,
			to_insert );
	}
	inline s32 insert_before( s32 index, type&& to_insert )
	{
		return base::insert_before( index,
			std::move(to_insert) );
	}
	
	
	inline s32 insert_after( s32 index, const type& to_insert )
	{
		return base::insert_after( index,
			to_insert );
	}
	inline s32 insert_after( s32 index, type&& to_insert )
	{
		return base::insert_after( index,
			std::move(to_insert) );
	}
	
	
	inline void erase_at( s32 index )
	{
		base::erase_at(index);
	}
	inline s32 insertion_sort_old_2()
	{
		return base::insertion_sort_old_2();
	}
	inline s32 insertion_sort_old_3()
	{
		return base::insertion_sort_old_3();
	}
	inline s32 insertion_sort()
	{
		return base::insertion_sort();
	}
	inline s32 merge_sort_via_array()
	{
		return base::merge_sort_via_array();
	}
	inline s32 merge_sort_via_array_2()
	{
		return base::merge_sort_via_array_2();
	}
	
} __attribute__((_align4));


// This class is intended to always be sorted, though it does not have to
// be in some cases.
template< typename type, u32 total_num_nodes >
class sorted_always_list 
	: public regular_list_base< type, total_num_nodes >
{
public:		// typedefs
	typedef regular_list_base< type, total_num_nodes > base;
	
public:		// functions
	inline sorted_always_list() : base()
	{
	}
	
	inline s32& get_front_index()
	{
		return base::get_front_index();
	}
	inline const s32 get_front_index() const
	{
		return base::get_front_index();
	}
	inline s32& get_back_index()
	{
		return base::get_back_index();
	}
	inline const s32 get_back_index() const
	{
		return base::get_back_index();
	}
	
	inline node<type>* get_node_array()
	{
		return base::get_node_array();
	}
	inline const node<type>* get_node_array() const
	{
		return base::get_node_array();
	}
	
	inline sa_free_list<total_num_nodes>& get_the_free_list()
	{
		return base::get_the_free_list();
	}
	inline const sa_free_list<total_num_nodes>& get_the_free_list() const
	{
		return base::get_the_free_list();
	}
	constexpr inline u32 get_node_array_size() const
	{
		return get_total_num_nodes();
	}
	constexpr inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	inline void fully_deallocate()
	{
		base::fully_deallocate();
	}
	inline void fully_deallocate_via_unlink()
	{
		base::fully_deallocate_via_unlink();
	}
	
	
	inline node<type>& get_node_at( s32 index )
	{
		return base::get_node_at(index);
	}
	inline node<type>& front()
	{
		//return get_node_at(get_front_index());
		return base::front();
	}
	
	inline s32 push_front( const type& to_push )
	{
		return base::push_front(to_push);
	}
	inline s32 push_front( type&& to_push )
	{
		return base::push_front(std::move(to_push));
	}
	inline s32 push_back( const type& to_push )
	{
		return base::push_back(to_push);
	}
	inline s32 push_back( type&& to_push )
	{
		return base::push_back(std::move(to_push));
	}
	
	inline s32 pop_front_basic()
	{
		return base::pop_front_basic();
	}
	inline s32 pop_back_basic()
	{
		return base::pop_back_basic();
	}
	
	inline s32 insert_and_sort( const type& to_insert )
	{
		push_front(to_insert);
		
		//return base::insertion_sort();
		return merge_sort_via_array_2();
	}
	inline s32 insert_and_sort( type&& to_insert )
	{
		push_front(std::move(to_insert));
		
		//return base::insertion_sort();
		return merge_sort_via_array_2();
	}
	
	
	// There is no need to sort the list after erasing a single node.  This
	// is because the list was already sorted to begin with.
	inline void erase_at( s32 index )
	{
		base::erase_at(index);
	}
	inline s32 insertion_sort_old_2()
	{
		return base::insertion_sort_old_2();
	}
	inline s32 insertion_sort_old_3()
	{
		return base::insertion_sort_old_3();
	}
	inline s32 insertion_sort()
	{
		return base::insertion_sort();
	}
	inline s32 merge_sort_via_array()
	{
		return base::merge_sort_via_array();
	}
	inline s32 merge_sort_via_array_2()
	{
		return base::merge_sort_via_array_2();
	}
	
} __attribute__((_align4));

} // end of namespace sa_list_stuff

#endif		// extended_list_class_stuff_hpp
