// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andrew Clark (FL4SHK).
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


#ifndef general_utility_stuff__slash__sa_array_of_lists_class_hpp
#define general_utility_stuff__slash__sa_array_of_lists_class_hpp

#include "stack_classes.hpp"


namespace sherwin_adventure
{
namespace containers
{

template<typename Type>
class _alignas_regular SaListNode
{
public:		// variables and constants
	static constexpr s16 link_null = -1;

	Type data;
	s16 index = link_null;
	s16 next = link_null, prev = link_null;

public:		// functions
	inline SaListNode()
	{
	}

};


template<typename Type, size_t __num_lists, 
	size_t __max_num_non_head_nodes>
class _alignas_regular SaArrayOfLists
{
public:		// classes
	class ListIterator
	{
	private:		// variables
		SaListNode<Type>* __node = nullptr;
		SaListNode<Type> * const __nodes_arr = nullptr;

	public:		// functions
		inline ListIterator(SaListNode<Type>* s_node, 
			SaListNode<Type> * const s_nodes_arr)
			: __node(s_node), __nodes_arr(s_nodes_arr)
		{
		}
		inline ListIterator(const ListIterator& to_copy) = default;

		inline ListIterator& operator = (const ListIterator& to_copy) 
			= default;

		inline SaListNode<Type>& operator * () const
		{
			return *__node;
		}
		inline SaListNode<Type>* operator -> () const
		{
			return __node;
		}
		inline ListIterator operator ++ ()
		{
			__node = &(__nodes_arr[__node->next]);

			return *this;
		}
		inline ListIterator operator -- ()
		{
			__node = &(__nodes_arr[__node->prev]);

			return *this;
		}


		inline operator bool() const
		{
			return __node ? true : false;
		}
		inline bool operator == (const ListIterator& to_cmp) const
		{
			return __node == to_cmp.__node;
		}
		inline bool operator != (const ListIterator& to_cmp) const
		{
			return !(*this == to_cmp);
		}
	};

public:		// constants
	static constexpr size_t max_num_nodes = __num_lists 
		+ __max_num_non_head_nodes;

protected:		// variables
	std::array<SaListNode<Type>, max_num_nodes> __nodes_arr;

	// This wastes a little bit of space
	SaFreeList<max_num_nodes> __free_list;


public:		// functions
	[[gnu::noinline]]
	SaArrayOfLists()
	{
		for (auto& iter : nodes_arr())
		{
			iter.data = Type();
		}

		for (size_t i=0; i<num_lists(); ++i)
		{
			const auto index = free_list().peek_top_and_pop();
			auto some_head = node_at(index);
			some_head->data = Type();
			some_head->index = index;
			some_head->next = some_head->index;
			some_head->prev = some_head->index;
		}
	}

	inline auto some_begin(size_t which_list)
	{
		return ListIterator(node_at(head_at(which_list)->next), 
			__nodes_arr.data());
	}
	inline auto some_end(size_t which_list)
	{
		return ListIterator(head_at(which_list), 
			__nodes_arr.data());
	}


	inline SaListNode<Type>* node_at(s16 index)
	{
		return &nodes_arr().at(index);
	}

	inline SaListNode<Type>* head_at(size_t which_list)
	{
		return node_at(get_head_index(which_list));
	}

	inline auto* mknode(size_t which_list)
	{
		auto some_head = head_at(which_list);
		auto some_prev = node_at(some_head->prev);


		const auto n_index = free_list().peek_top_and_pop();
		auto ret = node_at(n_index);

		ret->data = Type();
		ret->index = n_index;

		ret->next = some_head->index;
		ret->prev = some_head->prev;

		some_head->prev = ret->index;
		some_prev->next = ret->index;

		return ret;
	}
	inline void rmnode(SaListNode<Type>* p)
	{
		rmnode(p->index);
	}

	inline void rmnode(s16 index)
	{
		// Don't remove heads
		if (!index_is_head(index))
		{
			delink_at(index);
			free_list().push(index);
		}
	}


	gen_getter_by_val(num_lists);
	gen_getter_by_val(max_num_non_head_nodes);
	gen_getter_by_con_ref(nodes_arr);
	gen_getter_by_con_ref(free_list);



protected:		// functions
	inline bool index_is_head(s16 index) const
	{
		// index = nodes_arr().size() - 1 - which_list
		// which_list = nodes_arr().size() - 1 - index
		return ((nodes_arr().size() - 1 - index) < num_lists());
	}
	inline s16 get_head_index(size_t which_list) const
	{
		return (nodes_arr().size() - 1 - which_list);
	}

	inline void delink_at(s16 index)
	{
		auto* some_node = node_at(index);

		const auto some_next = some_node->next,
			some_prev = some_node->prev;
		node_at(some_prev)->next = some_next;
		node_at(some_next)->prev = some_prev;
	}

	gen_getter_by_ref(nodes_arr);
	gen_getter_by_ref(free_list);

};


}
}


#endif		// general_utility_stuff__slash__sa_array_of_lists_class_hpp
