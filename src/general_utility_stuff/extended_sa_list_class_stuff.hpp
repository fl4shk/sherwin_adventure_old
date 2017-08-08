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

namespace SaListStuff
{

// This Is a template class Intended for use as a BASE CLASS for classes
// That act as statically-allocated linked lists.  Since some (or possibly 
// all) of the derived classes use only some of the non-constructor member
// functions, 
template<typename Type, u32 total_num_nodes>
class RegularListBase
{
//protected:		// variables
public:		// variables
	ExternallyAllocatedList<Type> the_externally_allocated_list;
	Node<Type> node_array[total_num_nodes];
	SaFreeList<total_num_nodes> the_free_list;
	
	s32& front_index;
	s32& back_index;
	
public:		// functions
	
	
protected:		// functions
	// This may be the first time I've ever made a constructor protected.
	inline RegularListBase() : the_externally_allocated_list
		(node_array, &the_free_list.the_sa_free_list_backend, 
		get_total_num_nodes()), front_index(the_externally_allocated_list
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
	
	inline Node<Type>* get_node_array()
	{
		return node_array;
	}
	inline const Node<Type>* get_node_array() const
	{
		return node_array;
	}
	
	inline SaFreeList<total_num_nodes>& get_free_list()
	{
		return the_free_list;
	}
	inline const SaFreeList<total_num_nodes>& get_free_list() const
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
	
	inline Node<Type>& get_node_at(s32 index)
	{
		return get_node_array()[index];
	}
	inline Node<Type>& front()
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
	
	
	inline s32 push_front(const Type& to_push)
	{
		return the_externally_allocated_list.push_front(to_push);
	}
	inline s32 push_front(Type&& to_push)
	{
		return the_externally_allocated_list.push_front
			(std::move(to_push));
	}
	inline s32 push_back(const Type& to_push)
	{
		return the_externally_allocated_list.push_back(to_push);
	}
	inline s32 push_back(Type&& to_push)
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
	
	
	inline s32 insert_before(s32 index, const Type& to_insert)
	{
		return the_externally_allocated_list.insert_before(index,
			to_insert);
	}
	inline s32 insert_before(s32 index, Type&& to_insert)
	{
		return the_externally_allocated_list.insert_before(index,
			std::move(to_insert));
	}
	
	
	inline s32 insert_after(s32 index, const Type& to_insert)
	{
		return the_externally_allocated_list.insert_after(index,
			to_insert);
	}
	inline s32 insert_after(s32 index, Type&& to_insert)
	{
		return the_externally_allocated_list.insert_after(index,
			std::move(to_insert));
	}
	
	
	inline void erase_at(s32 index)
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


template<typename Type, u32 total_num_nodes>
class RegularList : public RegularListBase<Type, total_num_nodes>
{
public:		// typedefs
	typedef RegularListBase<Type, total_num_nodes> Base;
	
public:		// functions
	inline RegularList() : Base()
	{
	}
	
	inline s32& get_front_index()
	{
		return Base::get_front_index();
	}
	inline const s32 get_front_index() const
	{
		return Base::get_front_index();
	}
	inline s32& get_back_index()
	{
		return Base::get_back_index();
	}
	inline const s32 get_back_index() const
	{
		return Base::get_back_index();
	}
	
	inline Node<Type>* get_node_array()
	{
		return Base::get_node_array();
	}
	inline const Node<Type>* get_node_array() const
	{
		return Base::get_node_array();
	}
	
	inline SaFreeList<total_num_nodes>& get_free_list()
	{
		return Base::get_free_list();
	}
	inline const SaFreeList<total_num_nodes>& get_free_list() const
	{
		return Base::get_free_list();
	}
	constexpr inline u32 get_node_array_size() const
	{
		return get_total_num_nodes();
	}
	constexpr inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	inline Node<Type>& get_node_at(s32 index)
	{
		return Base::get_node_at(index);
	}
	inline Node<Type>& front()
	{
		//return get_node_at(get_front_index());
		return Base::front();
	}
	
	inline void fully_deallocate()
	{
		Base::fully_deallocate();
	}
	inline void fully_deallocate_via_unlink()
	{
		Base::fully_deallocate_via_unlink();
	}
	
	
	inline s32 push_front(const Type& to_push)
	{
		return Base::push_front(to_push);
	}
	inline s32 push_front(Type&& to_push)
	{
		return Base::push_front(std::move(to_push));
	}
	inline s32 push_back(const Type& to_push)
	{
		return Base::push_back(to_push);
	}
	inline s32 push_back(Type&& to_push)
	{
		return Base::push_back(std::move(to_push));
	}
	
	inline s32 pop_front_basic()
	{
		return Base::pop_front_basic();
	}
	inline s32 pop_back_basic()
	{
		return Base::pop_back_basic();
	}
	
	
	inline s32 insert_before(s32 index, const Type& to_insert)
	{
		return Base::insert_before(index,
			to_insert);
	}
	inline s32 insert_before(s32 index, Type&& to_insert)
	{
		return Base::insert_before(index,
			std::move(to_insert));
	}
	
	
	inline s32 insert_after(s32 index, const Type& to_insert)
	{
		return Base::insert_after(index,
			to_insert);
	}
	inline s32 insert_after(s32 index, Type&& to_insert)
	{
		return Base::insert_after(index,
			std::move(to_insert));
	}
	
	
	inline void erase_at(s32 index)
	{
		Base::erase_at(index);
	}
	inline s32 insertion_sort_old_2()
	{
		return Base::insertion_sort_old_2();
	}
	inline s32 insertion_sort_old_3()
	{
		return Base::insertion_sort_old_3();
	}
	inline s32 insertion_sort()
	{
		return Base::insertion_sort();
	}
	inline s32 merge_sort_via_array()
	{
		return Base::merge_sort_via_array();
	}
	inline s32 merge_sort_via_array_2()
	{
		return Base::merge_sort_via_array_2();
	}
	
} __attribute__((_align4));


// This class Is Intended To always be sorted, though it does not have To
// be in some cases.
template<typename Type, u32 total_num_nodes>
class SortedAlwaysList 
	: public RegularListBase<Type, total_num_nodes>
{
public:		// typedefs
	typedef RegularListBase<Type, total_num_nodes> Base;
	
public:		// functions
	inline SortedAlwaysList() : Base()
	{
	}
	
	inline s32& get_front_index()
	{
		return Base::get_front_index();
	}
	inline const s32 get_front_index() const
	{
		return Base::get_front_index();
	}
	inline s32& get_back_index()
	{
		return Base::get_back_index();
	}
	inline const s32 get_back_index() const
	{
		return Base::get_back_index();
	}
	
	inline Node<Type>* get_node_array()
	{
		return Base::get_node_array();
	}
	inline const Node<Type>* get_node_array() const
	{
		return Base::get_node_array();
	}
	
	inline SaFreeList<total_num_nodes>& get_free_list()
	{
		return Base::get_free_list();
	}
	inline const SaFreeList<total_num_nodes>& get_free_list() const
	{
		return Base::get_free_list();
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
		Base::fully_deallocate();
	}
	inline void fully_deallocate_via_unlink()
	{
		Base::fully_deallocate_via_unlink();
	}
	
	
	inline Node<Type>& get_node_at(s32 index)
	{
		return Base::get_node_at(index);
	}
	inline Node<Type>& front()
	{
		//return get_node_at(get_front_index());
		return Base::front();
	}
	
	inline s32 push_front(const Type& to_push)
	{
		return Base::push_front(to_push);
	}
	inline s32 push_front(Type&& to_push)
	{
		return Base::push_front(std::move(to_push));
	}
	inline s32 push_back(const Type& to_push)
	{
		return Base::push_back(to_push);
	}
	inline s32 push_back(Type&& to_push)
	{
		return Base::push_back(std::move(to_push));
	}
	
	inline s32 pop_front_basic()
	{
		return Base::pop_front_basic();
	}
	inline s32 pop_back_basic()
	{
		return Base::pop_back_basic();
	}
	
	inline s32 insert_and_sort(const Type& to_insert)
	{
		push_front(to_insert);
		
		//return Base::insertion_sort();
		return merge_sort_via_array_2();
	}
	inline s32 insert_and_sort(Type&& to_insert)
	{
		push_front(std::move(to_insert));
		
		//return Base::insertion_sort();
		return merge_sort_via_array_2();
	}
	
	
	// There Is no need To sort the list after erasing a single Node.  This
	// Is because the list was already sorted To begin with.
	inline void erase_at(s32 index)
	{
		Base::erase_at(index);
	}
	inline s32 insertion_sort_old_2()
	{
		return Base::insertion_sort_old_2();
	}
	inline s32 insertion_sort_old_3()
	{
		return Base::insertion_sort_old_3();
	}
	inline s32 insertion_sort()
	{
		return Base::insertion_sort();
	}
	inline s32 merge_sort_via_array()
	{
		return Base::merge_sort_via_array();
	}
	inline s32 merge_sort_via_array_2()
	{
		return Base::merge_sort_via_array_2();
	}
	
} __attribute__((_align4));

} // end of namespace SaListStuff

#endif		// extended_list_class_stuff_hpp
