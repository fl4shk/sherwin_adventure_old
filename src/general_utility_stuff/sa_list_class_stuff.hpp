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


#ifndef sa_list_class_stuff_hpp
#define sa_list_class_stuff_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
//#include "sa_dyn_array_class.hpp"
#include "sa_stack_classes.hpp"

#include "../gba_specific_stuff/asm_funcs.hpp"

#include "generic_funcptr_stuff.hpp"
#include "dyn_arr_class.hpp"
#include "prev_curr_pair_class.hpp"

#include <type_traits>
#include <functional>


// FL4SHK Note on April 8, 2017:  
// WHY did I bother making this So unnecessarily complicated?
// Reminder To myself:  DON'T do That!
namespace SaListStuff
{

// A non-template class Intended To be used by the ListBackend class.
class NodeContents
{
public:		// constants
	static constexpr size_t vec2_index_for_next_index = vec2_index_for_x,
		vec2_index_for_prev_index = vec2_index_for_y;
	
public:		// variables
	void* data_ptr;
	
	Vec2s16* index_pair_ptr;
	
public:		// functions
	// This Is safe So long as data_ptr Is the first member variable of the
	// NodeContents class.
	inline void* get_node_as_void_ptr()
	{
		return data_ptr;
	}
	
	template<typename type >
	inline type* cast_data_ptr()
	{
		return static_cast<type*>(data_ptr);
	}
	
	inline Vec2s16& get_index_pair()
	{
		return *index_pair_ptr;
	}
	
	inline s16& next_index()
	{
		return get_index_pair()[vec2_index_for_next_index];
	}
	inline s16& prev_index()
	{
		return get_index_pair()[vec2_index_for_prev_index];
	}
	
} __attribute__((_align4));




// Store only the original index of the Node and a void pointer To its
// data.  This Is Intended for use in array-based sorting algorithms That
// only change how nodes are linked.
class NodeDataAndIndex
{
public:		// variables
	void* data_ptr = NULL;
	s32 index = -1;
	
public:		// functions
	inline NodeDataAndIndex()
	{
	}
	
	inline NodeDataAndIndex(void* s_data_ptr, s32 s_index) 
		: data_ptr(s_data_ptr), index(s_index)
	{
	}
	
	
	inline s32 get_index() const
	{
		return index;
	}
	
} __attribute__((_align4));



typedef DynArr<NodeDataAndIndex> NdaiDynArr;



template<typename type >
class Node
{
public:		// variables
	type data __attribute__((_align4)) = type();
	Vec2s16 index_pair = { -1, -1 };
	
public:		// functions
	inline Node()
	{
	}
	
	
	template<typename type_in_vec2 >
	inline Node(const type& data_to_copy, 
		Vec2<type_in_vec2> s_index_pair) : data(data_to_copy)
	{
		next_index() = get_next_index_from_vec2(s_index_pair);
		prev_index() = get_prev_index_from_vec2(s_index_pair);
	}
	
	inline s16& next_index()
	{
		return index_pair
			[NodeContents::vec2_index_for_next_index];
	}
	inline s16& prev_index()
	{
		return index_pair
			[NodeContents::vec2_index_for_prev_index];
	}
	
	
protected:		// functions
	template<typename type_in_vec2 >
	static inline s16 get_next_index_from_vec2
		(const Vec2<type_in_vec2>& n_index_pair)
	{
		return static_cast<s16>(n_index_pair
			[NodeContents::vec2_index_for_next_index]);
	}
	template<typename type_in_vec2 >
	static inline s16 get_prev_index_from_vec2
		(const Vec2<type_in_vec2>& n_index_pair)
	{
		return static_cast<s16>(n_index_pair
			[NodeContents::vec2_index_for_prev_index]);
	}
	
	
} __attribute__((_align4));




// This Is basically a queue stored in an external circular buffer That
// doesn't permit erasing elements.
class CircBufHelper
{
protected:		// variables
	s32* the_array = NULL;
	
	// The maximum size of the_array, the number of used elements in the
	// array, and the TRUE start and end indices of the_array.
	size_t max_size = 0, real_size = 0, head = 0, tail = 0;
	
public:		// classes
	class Iterator
	{
	public:		// enums
		enum class IndexType : u32
		{
			it_other,
			it_head,
			it_tail,
			
		} _ALIGNAS_REGULAR;
		
	protected:  // variables
		CircBufHelper *const cbuf_helper_ptr;
		size_t pos;
		IndexType the_index_type;
		
	public:		// functions
		inline Iterator(CircBufHelper* s_cbuf_helper_ptr, 
			size_t s_pos, 
			IndexType s_the_index_type=IndexType::it_other) 
			: cbuf_helper_ptr(s_cbuf_helper_ptr), pos(s_pos),
			the_index_type(s_the_index_type)
		{
		}
		
		inline CircBufHelper *const get_cbuf_helper_ptr() const
		{
			return cbuf_helper_ptr;
		}
		inline size_t get_pos() const
		{
			return pos;
		}
		inline IndexType get_index_type() const
		{
			return the_index_type;
		}
		
		inline bool operator == (const Iterator& other) const
		{
			return !(*this != other);
		}
		
		// Required for a range-based for loop
		inline bool operator != (const Iterator& other) const
		{
			//return (pos != other.pos) || ((pos == other.pos)
			//	&& (get_is_head() != other.get_is_head()));
			
			if (get_pos() != other.get_pos())
			{
				return true;
			}
			
			return same_pos_not_equals(other);
		}
		
	protected:		// functions
		
		inline bool same_pos_not_equals (const Iterator& other) const
		{
			// At this point, Is Is known That pos == other.pos
			if (get_cbuf_helper_ptr() != other.get_cbuf_helper_ptr())
			{
				return true;
			}
			
			// At this point, it Is known That pos == other.pos, and both
			// iterators are from the same CircBufHelper.
			if (get_cbuf_helper_ptr()->get_real_size() == 0)
			{
				return false;
			}
			
			if (get_index_type() != other.get_index_type())
			{
				return true;
			}
			
			
			// At this point, it Is known That both iterators are at the
			// head of the same CircBufHelper, So they are equal.
			return false;
		}
		
	public:		// functions
		
		inline const s32 operator * () const
		{
			//return cbuf_helper_ptr->the_array[pos];
			return cbuf_helper_ptr->at(pos);
		}
		
		const Iterator& operator ++ ()
		{
			auto get_corrected_other_pos = [&](const size_t other_pos) 
				-> size_t
			{
				//get_pos() >= get_cbuf_helper_ptr()->get_max_size() 
				if (other_pos >= get_cbuf_helper_ptr()->get_max_size())
				{
					return 0;
				}
				return other_pos;
			};
			
			
			if (get_cbuf_helper_ptr()->get_real_size() > 1)
			{
				const size_t updated_pos = get_corrected_other_pos
					(get_pos() + 1);
				
				if (get_index_type() == IndexType::it_head)
				{
					the_index_type = IndexType::it_other;
					pos = updated_pos; 
				}
				else if (get_pos() == get_cbuf_helper_ptr()->get_tail())
				{
					the_index_type = IndexType::it_tail;
				}
				else
				{
					pos = updated_pos;
				}
			}
			else
			{
				// PROPERLY handle iterators.
				if (get_cbuf_helper_ptr()->get_real_size() == 1)
				{
					the_index_type = IndexType::it_tail;
				}
			}
			
			
			return *this;
		}
		
		
		
	} __attribute__((_align4));
	
	friend const s32 Iterator::operator * () const;
	
public:		// functions
	CircBufHelper(s32* s_the_array, size_t s_max_size)
		: the_array(s_the_array), max_size(s_max_size)
	{
		//// Don't call reset() here since it's called by
		//// insertion_sort_inner_loop.
		//reset();
	}
	
	CircBufHelper& operator = (const CircBufHelper& to_copy)
	{
		the_array = to_copy.the_array;
		max_size = to_copy.max_size;
		head = to_copy.head;
		tail = to_copy.tail;
		
		return *this;
	}
	inline void reset()
	{
		arr_memfill32(the_array, -1, get_max_size());
		head = tail = 0;
	}
	
	inline size_t get_max_size() const
	{
		return max_size;
	}
	inline size_t get_head() const
	{
		return head;
	}
	inline size_t get_tail() const
	{
		return tail;
	}
	inline size_t get_real_size() const
	{
		return real_size;
	}
	inline s32 at(size_t offset) const
	{
		return the_array[offset];
	}
	
	inline Iterator begin()
	{
		return Iterator(this, get_head(), Iterator::IndexType::it_head);
	}
	inline Iterator end()
	{
		return Iterator(this, get_tail(), Iterator::IndexType::it_tail);
	}
	
	void push(s32 to_push)
	{
		auto get_corrected_other_pos = [&](const size_t other_pos) 
			-> size_t
		{
			if (other_pos >= get_max_size())
			{
				return 0;
			}
			return other_pos;
		};
		
		
		// Update real_size
		if (get_real_size() < get_max_size())
		{
			++real_size;
		}
		
		if (get_real_size() == 1)
		{
			the_array[get_tail()] = to_push;
			
			return;
		}
		
		
		tail = get_corrected_other_pos(get_tail() + 1);
		the_array[get_tail()] = to_push;
		
		if (get_real_size() == get_max_size())
		{
			head = get_corrected_other_pos(get_tail() + 1);
		}
		
		
	}
	
} __attribute__((_align4));

class ExtrasFpGroup
{
public:		// typedefs
	typedef void (*sis_fp)(NdaiDynArr&, const size_t, const size_t);
	
public:		// function pointers
	// Function pointers used by various functions in the ListBackend
	// class.
	
	GenericVoid2ArgFp specific_type_copy_fp = NULL;
	GenericVoid2ArgFp specific_type_move_fp = NULL;
	generic_void_1arg_fp specific_type_reset_fp = NULL;
	GenericVoid2ArgFp specific_type_swap_fp = NULL;
	
	
	Genericu32_2ArgFp specific_type_less_fp = NULL;
	Genericu32_2ArgFp specific_type_greater_fp = NULL;
	QscmpFp specific_type_qscmp_fp = NULL;
	
	
	GenericVoidPtr1ArgFp get_node_data_fp = NULL;
	GenericVec2s16Ptr1ArgFp get_index_pair_fp = NULL;
	GenericVoid2ArgFp conv_node_to_contents_fp = NULL;
	GenericVoid2ArgFp insertion_sort_inner_loop_fp = NULL;
	
	sis_fp subarr_insertion_sort_fp = NULL;
	
	
	
	//// The only reason this static_assert Is wrapped inside a class That
	//// has nothing else in it Is To work around a bug in a Vim plugin That
	//// I use (Taghighlight specifically).  I don't have any idea why this
	//// Is even an issue, but oh well.
	//class WrappedStaticAsserts
	//{
	//public:		// functions
	//	inline WrappedStaticAsserts()
	//	{
	//		static_assert(std::is_trivially_copyable<ExtrasFpGroup>
	//			::value,
	//			"Can't use struct_memcpy() in ExtrasFpGroup::operator = "
	//			"() !");
	//	}
	//} __attribute__((_align4));
	
public:		// functions
	inline ExtrasFpGroup()
	{
	}
	inline ExtrasFpGroup(GenericVoid2ArgFp s_specific_type_copy_fp,
		GenericVoid2ArgFp s_specific_type_move_fp,
		generic_void_1arg_fp s_specific_type_reset_fp,
		GenericVoid2ArgFp s_specific_type_swap_fp,
		
		Genericu32_2ArgFp s_specific_type_less_fp,
		Genericu32_2ArgFp s_specific_type_greater_fp,
		QscmpFp s_specific_type_qscmp_fp,
		
		GenericVoidPtr1ArgFp s_get_node_data_fp,
		GenericVec2s16Ptr1ArgFp s_get_index_pair_fp,
		GenericVoid2ArgFp s_conv_node_to_contents_fp,
		GenericVoid2ArgFp s_insertion_sort_inner_loop_fp,
		sis_fp s_subarr_insertion_sort_fp)
	{
		specific_type_copy_fp = s_specific_type_copy_fp;
		specific_type_move_fp = s_specific_type_move_fp;
		specific_type_reset_fp = s_specific_type_reset_fp;
		specific_type_swap_fp = s_specific_type_swap_fp;
		
		
		specific_type_less_fp = s_specific_type_less_fp;
		specific_type_greater_fp = s_specific_type_greater_fp;
		specific_type_qscmp_fp = s_specific_type_qscmp_fp;
		
		
		get_node_data_fp = s_get_node_data_fp;
		get_index_pair_fp = s_get_index_pair_fp;
		conv_node_to_contents_fp = s_conv_node_to_contents_fp;
		insertion_sort_inner_loop_fp = s_insertion_sort_inner_loop_fp;
		subarr_insertion_sort_fp = s_subarr_insertion_sort_fp;
	}
	
	inline ExtrasFpGroup(const ExtrasFpGroup& to_copy)
	{
		*this = to_copy;
	}
	
	
	inline GenericVoid2ArgFp get_specific_type_copy_fp() const
	{
		return specific_type_copy_fp;
	}
	inline GenericVoid2ArgFp get_specific_type_move_fp() const
	{
		return specific_type_move_fp;
	}
	inline generic_void_1arg_fp get_specific_type_reset_fp() const
	{
		return specific_type_reset_fp;
	}
	inline GenericVoid2ArgFp get_specific_type_swap_fp() const
	{
		return specific_type_swap_fp;
	}
	
	
	inline Genericu32_2ArgFp get_specific_type_less_fp() const
	{
		return specific_type_less_fp;
	}
	inline Genericu32_2ArgFp get_specific_type_greater_fp() const
	{
		return specific_type_greater_fp;
	}
	inline QscmpFp get_specific_type_qscmp_fp() const
	{
		return specific_type_qscmp_fp;
	}
	
	
	inline GenericVoidPtr1ArgFp get_get_node_data_fp() const
	{
		return get_node_data_fp;
	}
	inline GenericVec2s16Ptr1ArgFp get_get_index_pair_fp() const
	{
		return get_index_pair_fp;
	}
	inline GenericVoid2ArgFp get_conv_node_to_contents_fp() const
	{
		return conv_node_to_contents_fp;
	}
	inline GenericVoid2ArgFp get_insertion_sort_inner_loop_fp() const
	{
		return insertion_sort_inner_loop_fp;
	}
	inline sis_fp get_subarr_insertion_sort_fp() const
	{
		return subarr_insertion_sort_fp;
	}
	
} __attribute__((_align4));


// A group of functions To use as function pointers in the ListBackend
// class.
template<typename type >
class ListExtras
{
protected:		// functions To point To
	static void specific_type_copy(type* a, type* b)
		__attribute__((_text_hot_section))
	{
		*a = *b;
	}
	static void specific_type_move(type* a, type* b)
		__attribute__((_text_hot_section))
	{
		*a = std::move(*b);
	}
	static void specific_type_reset(type* to_reset)
		__attribute__((_text_hot_section))
	{
		*to_reset = type();
	}
	static void specific_type_swap(type* a, type* b)
		__attribute__((_text_hot_section))
	{
		//type temp = std::move(*a);
		//*a = std::move(*b);
		//*b = std::move(temp);
		std::swap(*a, *b);
	}
	
	static u32 specific_type_less(type* a, type* b)
		__attribute__((_text_hot_section))
	{
		return ((*a) < (*b));
	}
	static u32 specific_type_greater(type* a, type* b)
		__attribute__((_text_hot_section))
	{
		return ((*a) > (*b));
	}
	
	// qsort() comparison function
	static int specific_type_qscmp(const type* a, const type* b)
		__attribute__((_text_hot_section))
	{
		if ((*a) < (*b))
		{
			return -1;
		}
		else if ((*a) == (*b))
		{
			return 0;
		}
		else // if ((*a) > (*b))
		{
			return 1;
		}
	}
	
	static void* get_node_data(Node<type>* to_get_from)
		__attribute__((_text_hot_section))
	{
		return &to_get_from->data;
	}
	static Vec2s16* get_sa_list_index_pair(Node<type>* to_get_from)
		__attribute__((_text_hot_section))
	{
		return &to_get_from->index_pair;
	}
	static void conv_node_to_contents(NodeContents* ret,
		Node<type>* to_convert) __attribute__((_text_hot_section))
	{
		ret->data_ptr = &to_convert->data;
		ret->index_pair_ptr = &to_convert->index_pair;
	}
	
	
	// Instead of having the ENTIRE insertion_sort function be duplicated
	// for EVERY externally_allocated_sa_list instantiation, only duplicate
	// the inner loop.  This seems pretty good To me.
	//
	// Note:  old_il_cbuf_helper Is a CIRCULAR BUFFER helper That allows
	// keeping track of a FIXED NUMBER of indices To nodes for sorting
	// purposes.
	static void insertion_sort_inner_loop(Node<type>* node_array, 
		s32* index_low_ptr) //__attribute__((_text_hot_section))
	{
		Node<type>* node_at_j;
		
		s32& index_low = *index_low_ptr;
		
		type* data_at_index_low = &(node_array[index_low].data);
		
		// Find the lowest value at or after i.
		for (s32 j=index_low;
			j!=-1; 
			j=node_at_j->next_index())
		{
			//node_at_j = &get_node_at(j);
			node_at_j = &(node_array[j]);
			
			//if (node_at_j->data 
			//	< get_node_at(index_low).data)
			if ((node_at_j->data) < (*data_at_index_low))
			{
				index_low = j;
				
				data_at_index_low = &(node_at_j->data);
			}
		}
		
	}
	
	
	static void subarr_insertion_sort(NdaiDynArr& arr_a,
		const size_t subarr_offset, const size_t subarr_size)
		//__attribute__((_text_hot_section))
	{
		size_t curr_offset = subarr_offset;
		
		
		for (size_t i=1; i<subarr_size; ++i)
		{
			size_t j = ++curr_offset;
			
			while (j > 0 && *(type*)arr_a[j - 1].data_ptr
				> *(type*)arr_a[j].data_ptr)
			{
				type temp = std::move(*(type*)arr_a[j - 1].data_ptr);
				
				*(type*)arr_a[j - 1].data_ptr 
					= std::move(*(type*)arr_a[j].data_ptr);
				*(type*)arr_a[j].data_ptr = std::move(temp);
				
				--j;
			}
		}
	}
	
	
	
public:		// function pointer stuff
	// This Is the first time I've used an "auto" return type much, but it
	// makes plenty of sense for this case.
	static inline auto get_specific_type_copy_fp()
	{
		return get_generic_void_2arg_fp(&specific_type_copy);
	}
	static inline auto get_specific_type_move_fp()
	{
		return get_generic_void_2arg_fp(&specific_type_move);
	}
	static inline auto get_specific_type_reset_fp()
	{
		return get_generic_void_1arg_fp(&specific_type_reset);
	}
	
	static inline auto get_specific_type_swap_fp()
	{
		return get_generic_void_2arg_fp(&specific_type_swap);
	}
	
	
	
	static inline auto get_specific_type_less_fp()
	{
		return get_generic_u32_2arg_fp(&specific_type_less);
	}
	static inline auto get_specific_type_greater_fp()
	{
		return get_generic_u32_2arg_fp(&specific_type_greater);
	}
	static inline auto get_specific_type_qscmp_fp()
	{
		return get_qscmp_fp(&specific_type_qscmp);
	}
	
	
	static inline auto get_get_node_data_fp()
	{
		return get_generic_void_ptr_1arg_fp(&get_node_data);
	}
	static inline auto get_get_index_pair_fp()
	{
		return get_generic_vec2_s16_ptr_1arg_fp
			(&get_sa_list_index_pair);
	}
	static inline auto get_conv_node_to_contents_fp()
	{
		return get_generic_void_2arg_fp(&conv_node_to_contents);
	}
	
	static inline auto get_insertion_sort_inner_loop_fp()
	{
		return get_generic_void_2arg_fp(&insertion_sort_inner_loop);
	}
	static inline ExtrasFpGroup::sis_fp get_subarr_insertion_sort_fp()
	{
		//return reinterpret_cast<ExtrasFpGroup::sis_fp>
		//	(&subarr_insertion_sort);
		return &subarr_insertion_sort;
	}
	
	static inline ExtrasFpGroup get_extras_fp_group()
	{
		return ExtrasFpGroup(get_specific_type_copy_fp(),
			get_specific_type_move_fp(),
			get_specific_type_reset_fp(),
			get_specific_type_swap_fp(),
			
			get_specific_type_less_fp(),
			get_specific_type_greater_fp(),
			get_specific_type_qscmp_fp(),
			
			get_get_node_data_fp(),
			get_get_index_pair_fp(),
			get_conv_node_to_contents_fp(),
			get_insertion_sort_inner_loop_fp(),
			get_subarr_insertion_sort_fp());
	}
	
	
public:		// functions To not point To
	static inline void subarr_insertion_sort(DynArr<type>& arr_a,
		const size_t subarr_offset, const size_t subarr_size)
		__attribute__((always_inline))
	{
		//if (subarr_offset + subarr_size >= real_num_nodes)
		//{
		//	subarr_size = real_num_nodes - subarr_offset;
		//}
		
		size_t curr_offset = subarr_offset;
		
		for (size_t i=1; i<subarr_size; ++i)
		{
			size_t j = ++curr_offset;
			
			while (j > 0 && (arr_a[j - 1] > arr_a[j]))
			{
				std::swap(arr_a[j], arr_a[j - 1]);
				
				--j;
			}
		}
	}
	
	
} __attribute__((_align4));





// This class Exists because C++ templates CAN generate too much code.  Oh,
// and I Can put code in IWRAM this way!
class ListBackend
{
protected:		// variables
	size_t size = 0;
	
	s32 front_index = -1, back_index = -1;
	
	// node_array as a void pointer.
	void* node_array = NULL;
	
	SaFreeListBackend* the_free_list_backend_ptr = NULL;
	
	
	u32 total_num_nodes = 0;
	
	// Node stuff
	u32 specific_type_size = 0, 
		whole_node_size = 0;
	
	
	ExtrasFpGroup the_extras_fp_group;
	
	template<typename type > friend class ExternallyAllocatedList;
	
protected:		// functions
	inline ListBackend() : size(0)
	{
	}
	// Dang, I had no idea it'd be this nice To get types automatically
	// this way.
	inline ListBackend(void* s_node_array, 
		SaFreeListBackend* s_the_free_list_backend_ptr,
		u32 s_total_num_nodes, u32 s_specific_type_size,
		u32 s_whole_node_size, 
		
		const ExtrasFpGroup& s_the_extras_fp_group)
	{
		init(s_node_array, s_the_free_list_backend_ptr,
			s_total_num_nodes, s_specific_type_size, s_whole_node_size,
			s_the_extras_fp_group);
	}
	inline ListBackend(ListBackend& to_copy)
	{
		init(to_copy);
	}
	
	void init(void* n_node_array, 
		SaFreeListBackend* n_the_free_list_backend_ptr,
		u32 n_total_num_nodes, u32 n_specific_type_size,
		u32 n_whole_node_size, 
		
		const ExtrasFpGroup& n_the_extras_fp_group);
	
	inline void init(ListBackend& to_copy)
	{
		init(to_copy.get_node_array(), 
			to_copy.get_free_list_backend_ptr(),
			to_copy.get_total_num_nodes(), 
			to_copy.get_specific_type_size(),
			to_copy.get_whole_node_size(), 
			
			to_copy.get_extras_fp_group());
	}
	
	
	inline size_t& get_size()
	{
		return size;
	}
	inline const size_t get_size() const
	{
		return size;
	}
	
	inline s32& get_front_index()
	{
		return front_index;
	}
	inline const s32 get_front_index() const
	{
		return front_index;
	}
	inline s32& get_back_index()
	{
		return back_index;
	}
	inline const s32 get_back_index() const
	{
		return back_index;
	}
	
	inline void* get_node_array()
	{
		return node_array;
	}
	inline const void* get_node_array() const
	{
		return node_array;
	}
	
	inline SaFreeListBackend* get_free_list_backend_ptr()
	{
		return the_free_list_backend_ptr;
	}
	inline const SaFreeListBackend* get_free_list_backend_ptr()
		const
	{
		return the_free_list_backend_ptr;
	}
	inline SaFreeListBackend& get_free_list_backend()
	{
		return *get_free_list_backend_ptr();
	}
	inline const SaFreeListBackend& get_free_list_backend() const
	{
		return *get_free_list_backend_ptr();
	}
	
	inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	inline u32 get_specific_type_size() const
	{
		return specific_type_size;
	}
	inline u32 get_whole_node_size() const
	{
		return whole_node_size;
	}
	
	inline const ExtrasFpGroup& get_extras_fp_group()
	{
		return the_extras_fp_group;
	}
	
	
	
	inline uintptr_t get_node_addr_at(s32 index) const
	{
		return reinterpret_cast<uintptr_t>(get_node_array())
			+ ARR_BYTE_INDEX_MACRO(whole_node_size, index);
	}
	
	
	
	// These three functions are Intended To be used sparingly.  They make
	// most sense To use when their result Is the ONLY part of a Node That
	// Is relevant, and in That case it Is still best To ONLY CALL them
	// ONCE PER NODE.
	inline void* get_node_data_at_index(s32 index)
	{
		return get_node_data_at(get_node_addr_at(index));
	}
	inline Vec2s16* get_index_pair_at_index(s32 index)
	{
		return get_index_pair_at(get_node_addr_at(index));
	}
	inline s16& get_next_index_at_index(s32 index)
	{
		return get_next_index_at(get_node_addr_at(index));
	}
	inline s16& get_prev_index_at_index(s32 index)
	{
		return get_prev_index_at(get_node_addr_at(index));
	}
	
	
	inline void* get_node_data_at(uintptr_t addr)
	{
		return get_extras_fp_group().get_get_node_data_fp()
			(reinterpret_cast<void*>(addr));
	}
	inline Vec2s16* get_index_pair_at(uintptr_t addr)
	{
		return get_extras_fp_group().get_get_index_pair_fp()
			(reinterpret_cast<void*>(addr));
	}
	inline s16& get_next_index_at(uintptr_t addr)
	{
		return ((*get_index_pair_at(addr))
			[NodeContents::vec2_index_for_next_index]);
	}
	inline s16& get_prev_index_at(uintptr_t addr)
	{
		return ((*get_index_pair_at(addr))
			[NodeContents::vec2_index_for_prev_index]);
	}
	
	inline NodeContents get_node_contents_at(s32 index)
	{
		uintptr_t node_addr = get_node_addr_at(index);
		
		//NodeContents ret = { get_node_data_at(node_addr),
		//	get_index_pair_at(node_addr) };
		
		NodeContents ret;
		
		get_extras_fp_group().get_conv_node_to_contents_fp()(&ret, 
			reinterpret_cast<void*>(node_addr));
		
		return ret;
	}
	
	
	// Make sure To call this with Node DATA!
	inline void copy_node_data(void* dst_node_data, 
		const void* src_node_data)
	{
		get_extras_fp_group().get_specific_type_copy_fp()
			(dst_node_data, const_cast<void*>(src_node_data));
	}
	inline void move_node_data(void* dst_node_data, 
		const void* src_node_data)
	{
		get_extras_fp_group().get_specific_type_move_fp()
			(dst_node_data, const_cast<void*>(src_node_data));
	}
	
	
	inline void assign_to_node_data(NodeContents& dst_node_contents, 
		const void* n_data, u32 can_move_value)
	{
		if (!can_move_value)
		{
			copy_node_data(dst_node_contents.data_ptr, n_data);
		}
		else //if (can_move_value)
		{
			move_node_data(dst_node_contents.data_ptr, n_data);
		}
	}
	inline void assign_to_whole_node
		(NodeContents& dst_node_contents, const void* n_data,
		const Vec2s16& n_index_pair, u32 can_move_value)
	{
		assign_to_node_data(dst_node_contents, n_data, 
			can_move_value);
		copy_vec2_s16_via_ptr(*dst_node_contents.index_pair_ptr,
			n_index_pair);
	}
	
	
	// Make sure To call this with Node DATA!
	inline void call_specific_type_swap_func(void* node_a_data, 
		void* node_b_data)
	{
		get_extras_fp_group().get_specific_type_swap_fp()
			(node_a_data, node_b_data);
	}
	inline u32 call_specific_type_less_func(void* node_a_data, 
		void* node_b_data)
	{
		return get_extras_fp_group().get_specific_type_less_fp()
			(node_a_data, node_b_data);
	}
	inline u32 call_specific_type_greater_func(void* node_a_data, 
		void* node_b_data)
	{
		return get_extras_fp_group().get_specific_type_greater_fp()
			(node_a_data, node_b_data);
	}
	inline int call_specific_type_qscmp_func(const void* node_a_data,
		const void* node_b_data)
	{
		return get_extras_fp_group().get_specific_type_qscmp_fp()
			(node_a_data, node_b_data);
	}
	
	inline void call_insertion_sort_inner_loop_func(s32& index_low)
	{
		get_extras_fp_group().get_insertion_sort_inner_loop_fp()
			(get_node_array(), &index_low);
	}
	
	
	void fully_deallocate() __attribute__((_iwram_code));
	void fully_deallocate_via_unlink() __attribute__((_iwram_code));
	
	
	
	// This Is used by frontends To the internal_func_move_unlinked_node*
	// functions
	void internal_func_allocate_and_assign_to_node(s32& index, 
		NodeContents& Node, const void* n_data, u32 can_move_value);
		__attribute__((_iwram_code));
	
	
	
	
	
	//// This Is its own function because it's used by both push_front() and
	//// push_back().
	//inline s32 internal_func_push_front_unique_code(s32 to_push_index,
	//	NodeContents node_to_push)
	//{
	//}
	
	// push_front() CAN affect back_index
	inline s32 push_front(const void* to_push, u32 can_move_value=false)
	{
		s32 to_push_index;
		NodeContents node_to_push;
		
		internal_func_allocate_and_assign_to_node(to_push_index,
			node_to_push, to_push, can_move_value);
		
		return internal_func_move_unlinked_node_to_front(to_push_index,
			node_to_push);
	}
	
	// push_back() ALWAYS affects back_index
	inline s32 push_back(const void* to_push, u32 can_move_value=false)
	{
		s32 new_index;
		NodeContents new_node;
		internal_func_allocate_and_assign_to_node(new_index, new_node,
			to_push, can_move_value);
		
		return internal_func_move_unlinked_node_to_back(new_index,
			new_node);
	}
	
	// insert_before() won't affect back_index
	inline s32 insert_before(s32 index, const void* to_insert,
		u32 can_move_value=false)
	{
		s32 to_insert_index;
		NodeContents node_to_insert;
		
		internal_func_allocate_and_assign_to_node(to_insert_index,
			node_to_insert, to_insert, can_move_value);
		
		return internal_func_move_unlinked_node_before(index,
			to_insert_index, node_to_insert);
	}
	// insert_after() CAN affect back_index
	inline s32 insert_after(s32 index, const void* to_insert,
		u32 can_move_value=false)
	{
		s32 to_insert_index;
		NodeContents node_to_insert;
		
		internal_func_allocate_and_assign_to_node(to_insert_index,
			node_to_insert, to_insert, can_move_value);
		
		return internal_func_move_unlinked_node_after(index,
			to_insert_index, node_to_insert);
	}
	
	
	
	
	inline s32 pop_front_basic()
	{
		s32& the_front_index = get_front_index();
		
		erase_at(the_front_index);
		
		return the_front_index;
	}
	inline s32 pop_back_basic()
	{
		s32& the_back_index = get_back_index();
		
		erase_at(the_back_index);
		
		return the_back_index;
	}
	
	//s32 insert_before(s32 index, const void* to_insert,
	//	u32 can_move_value=false);
	//s32 insert_after(s32 index, const void* to_insert,
	//	u32 can_move_value=false);
	
	
	
	// Some of the functions for internal use 
	s32 internal_func_move_unlinked_node_to_front(s32 to_move_index, 
		NodeContents& node_to_move);
		//__attribute__((_iwram_code));
		//__attribute__((noinline));
	inline s32 internal_func_move_unlinked_node_to_back(s32 to_move_index,
		NodeContents& node_to_move)
	{
		// If there's nothing in the list
		if (get_back_index() < 0)
		{
			return internal_func_move_unlinked_node_to_front
				(to_move_index, node_to_move);
		}
		// If there's at least one element in the list
		else // if (get_back_index() >= 0)
		{
			return internal_func_move_unlinked_node_after
				(get_back_index(), to_move_index, node_to_move);
		}
	}
	s32 internal_func_move_unlinked_node_before(s32 to_move_before_index, 
		s32 to_move_index, NodeContents& node_to_move);
		//__attribute__((_iwram_code));
		//__attribute__((noinline));
	s32 internal_func_move_unlinked_node_after(s32 to_move_after_index, 
		s32 to_move_index, NodeContents& node_to_move);
		//__attribute__((_iwram_code));
		//__attribute__((noinline));
	
	
	// Give slightly more flexibility, at the expense of a small amount of
	// speed, To this function by allowing a pointer To the
	// node_at_index be passed To it.
	void* internal_func_unlink_at(s32 index, 
		NodeContents* node_at_index_ptr=NULL);
		//__attribute__((_iwram_code));
		//__attribute__((noinline));
	
	
	//void internal_func_unlink_from_connected_index_at(s32 index, 
	//	u32 index_to_vec2); 
	//	//__attribute__((_iwram_code));
	//
	//inline void unlink_from_next_at(s32 index)
	//{
	//	internal_func_unlink_from_connected_index_at(index, 
	//		NodeContents::vec2_index_for_next_index);
	//}
	//inline void unlink_from_prev_at(s32 index)
	//{
	//	internal_func_unlink_from_connected_index_at(index, 
	//		NodeContents::vec2_index_for_prev_index);
	//}
	
	
	inline void move_linked_node_to_front(s32 to_move_index, 
		NodeContents& node_to_move, ListBackend& dst)
	{
		internal_func_unlink_at(to_move_index, &node_to_move);
		dst.internal_func_move_unlinked_node_to_front(to_move_index, 
			node_to_move);
	}
	inline void move_linked_node_to_back(s32 to_move_index, 
		NodeContents& node_to_move, ListBackend& dst)
	{
		internal_func_unlink_at(to_move_index, &node_to_move);
		dst.internal_func_move_unlinked_node_to_back(to_move_index, 
			node_to_move);
	}
	inline void move_linked_node_before(s32 to_move_before_index,
		s32 to_move_index, NodeContents& node_to_move, 
		ListBackend& dst)
	{
		internal_func_unlink_at(to_move_index, &node_to_move);
		dst.internal_func_move_unlinked_node_before(to_move_before_index, 
			to_move_index, node_to_move);
	}
	inline void move_linked_node_after(s32 to_move_after_index,
		s32 to_move_index, NodeContents& node_to_move, 
		ListBackend& dst)
	{
		internal_func_unlink_at(to_move_index, &node_to_move);
		dst.internal_func_move_unlinked_node_after(to_move_after_index, 
			to_move_index, node_to_move);
	}
	
	
	// End of functions for internal use.
	
	// It Is (slightly) faster To just unlink a Node than it Is To erase it
	// because erase_at() ALSO resets the data of the Node.  Use caution
	// when using this function!
	inline void* unlink_at_with_dealloc(s32 index)
	{
		get_free_list_backend().push(index);
		
		return internal_func_unlink_at(index);
	}
	
	inline void erase_at(s32 index)
	{
		get_extras_fp_group().get_specific_type_reset_fp()
			(unlink_at_with_dealloc(index));
	}
	
	
	
	
	//s32 insertion_sort() __attribute__((_iwram_code));
	//s32 insertion_sort() __attribute__((_text_hot_section));
	s32 insertion_sort(); //__attribute__((_iwram_code));
	
	
	
	//// These two functions are slowwwwwww because there Is too much list
	//// traversal.  Thus, I have replaced them with an array of pointers
	//// based method.
	//s32 internal_func_merge(merge_args& args)
	//	__attribute__((_iwram_code));
	//s32 merge_sort() __attribute__((_iwram_code));
	
	
	
	void internal_func_subarr_merge(NodeDataAndIndex* left_subarr,
		const size_t left_subarr_size, NodeDataAndIndex* right_subarr, 
		const size_t right_subarr_size, NodeDataAndIndex* out_subarr);
		//__attribute__((_iwram_code));
	
	// Top-down merge sort using an array of NodeDataAndIndex's.
	s32 merge_sort_via_array(); //__attribute__((_iwram_code));
	
	
	//s32 heapsort_via_array();
	
	
} __attribute__((_align4));





template<typename type >
class ExternallyAllocatedList
{
protected:		// typedefs
	typedef ListExtras<type> ExtrasType;
	
//public:		// variables
protected:		// variables
	//s32* ptr_to_front_index;
	//s32 front_index;
	Node<type>* node_array = 0;
	SaFreeListBackend* the_free_list_backend_ptr = 0;
	u32 total_num_nodes = 0;
	
	
public:		// variables, temporarily public
	ListBackend the_list_backend;
	
public:		// functions
	inline ExternallyAllocatedList() : the_list_backend()
	{
	}
	inline ExternallyAllocatedList
		(Node<type>* s_node_array, 
		SaFreeListBackend* s_the_free_list_backend_ptr,
		u32 s_total_num_nodes)
	{
		init(s_node_array, s_the_free_list_backend_ptr,
			s_total_num_nodes);
	}
	
	inline ~ExternallyAllocatedList()
	{
		fully_deallocate();
	}
	
	
	void init(Node<type>* n_node_array, 
		SaFreeListBackend* n_the_free_list_backend_ptr,
		u32 n_total_num_nodes) __attribute__((noinline))
	{
		node_array = n_node_array;
		the_free_list_backend_ptr = n_the_free_list_backend_ptr;
		total_num_nodes = n_total_num_nodes;
		
		the_list_backend.init(get_node_array(),
			the_free_list_backend_ptr, get_total_num_nodes(),
			sizeof(type), sizeof(Node<type>),
			ExtrasType::get_extras_fp_group());
		
		//static auto specific_type_copy = [](type* a, type* b) -> void 
		//	{ *a = *b; };
		//static auto specific_type_move = [](type* a, type* b) -> void
		//	{ *a = std::move(*b); };
		//static auto specific_type_reset = [](type* a) -> void
		//	{ *a = type(); };
		//static auto specific_type_less = [](type* a, type* b) -> u32
		//	{ return (*a) < (*b); };
		//
		//
		//ASM_COMMENT("the_list_backend.init()");
		//the_list_backend.init(get_node_array(),
		//	the_free_list_backend_ptr, get_total_num_nodes(),
		//	sizeof(type), sizeof(Node<type>),
		//	
		//	reinterpret_cast<GenericVoid2ArgFp>(&specific_type_copy),
		//	reinterpret_cast<GenericVoid2ArgFp>(&specific_type_move),
		//	reinterpret_cast<generic_void_1arg_fp>(&specific_type_reset),
		//	reinterpret_cast<Genericu32_2ArgFp>(&specific_type_less), 
		//	
		//	ExtrasType::get_get_node_data_fp(),
		//	ExtrasType::get_get_index_pair_fp(),
		//	ExtrasType::get_conv_node_to_contents_fp());
	}
	
	inline size_t& get_size()
	{
		return the_list_backend.get_size();
	}
	inline const size_t get_size() const
	{
		return the_list_backend.get_size();
	}
	
	inline s32& get_front_index()
	{
		return the_list_backend.get_front_index();
	}
	inline const s32 get_front_index() const
	{
		return the_list_backend.get_front_index();
	}
	inline s32& get_back_index()
	{
		return the_list_backend.get_back_index();
	}
	inline const s32 get_back_index() const
	{
		return the_list_backend.get_back_index();
	}
	
	inline Node<type>* get_node_array()
	{
		return node_array;
	}
	inline const Node<type>* get_node_array() const
	{
		return node_array;
	}
	
	inline SaFreeListBackend& get_free_list_backend()
	{
		return *the_free_list_backend_ptr;
	}
	inline const SaFreeListBackend& get_free_list_backend() const
	{
		return *the_free_list_backend_ptr;
	}
	
	inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	
	
	inline Node<type>& get_node_at(s32 index)
	{
		return get_node_array()[index];
	}
	inline Node<type>& front()
	{
		return get_node_at(get_front_index());
	}
	
	inline Node<type>& get_next_node_after_index
		(s32 index)
	{
		return get_node_at(get_node_at(index)
			.next_index());
	}
	inline Node<type>& get_prev_node_before_index
		(s32 index)
	{
		return get_node_at(get_node_at(index)
			.prev_index());
	}
	
	
	inline void fully_deallocate()
	{
		the_list_backend.fully_deallocate();
	}
	inline void fully_deallocate_via_unlink()
	{
		the_list_backend.fully_deallocate_via_unlink();
	}
	
	
	inline s32 push_front(const type& to_push)
	{
		return the_list_backend.push_front(&to_push);
	}
	inline s32 push_front(type&& to_push)
	{
		return the_list_backend.push_front(&to_push, true);
	}
	inline s32 push_back(const type& to_push)
	{
		return the_list_backend.push_back(&to_push);
	}
	inline s32 push_back(type&& to_push)
	{
		return the_list_backend.push_back(&to_push, true);
	}
	
	
	inline s32 pop_front_basic()
	{
		return the_list_backend.pop_front_basic();
	}
	inline s32 pop_back_basic()
	{
		return the_list_backend.pop_back_basic();
	}
	
	inline s32 insert_before(s32 index, const type& to_insert)
	{
		return the_list_backend.insert_before(index, &to_insert);
	}
	inline s32 insert_before(s32 index, type&& to_insert)
	{
		return the_list_backend.insert_before(index, &to_insert,
			true);
	}
	
	
	
	inline s32 insert_after(s32 index, const type& to_insert)
	{
		return the_list_backend.insert_after(index, &to_insert);
	}
	inline s32 insert_after(s32 index, type&& to_insert)
	{
		return the_list_backend.insert_after(index, &to_insert, true);
	}
	
	inline void erase_at(s32 index)
	{
		the_list_backend.erase_at(index);
	}
	inline type&& unlink_at_with_dealloc(s32 index)
	{
		return std::move(*static_cast<type*>
			(the_list_backend.unlink_at_with_dealloc(index)));
	}
	
	
	s32 insertion_sort_old_2() 
		//__attribute__((_text_hot_section,noinline))
		__attribute__((noinline))
	{
		s32& the_front_index = get_front_index();
		
		// Don't do anything if this list has zero or one nodes.
		if (the_front_index < 0)
		{
			return the_front_index;
		}
		if (get_node_at(the_front_index).next_index() < 0)
		{
			return the_front_index;
		}
		
		ExternallyAllocatedList<type> sorted_list(node_array, 
			the_free_list_backend_ptr, get_total_num_nodes());
		
		s32& temp_front_index = sorted_list.get_front_index();
		
		s32 curr_index = temp_front_index;
		
		for (s32 i=the_front_index;
			i!=-1; )
			//i=get_node_at(i).next_index())
		{
			
			//get_free_list_backend().debug_prs32();
			
			s32 index_low = i;
			
			Node<type>* node_at_j;
			
			// Find the lowest value at or after i.
			for (s32 j=index_low;
				j!=-1; 
				j=node_at_j->next_index())
			{
				node_at_j = &get_node_at(j);
				
				if (node_at_j->data 
					< get_node_at(index_low).data)
				{
					index_low = j;
				}
			}
			
			Node<type>& node_at_index_low = get_node_at(index_low);
			//const type data_to_move = node_at_index_low.data;
			//type* data_to_move = &node_at_index_low.data;
			
			if (i == index_low)
			{
				i = node_at_index_low.next_index();
			}
			
			//erase_at(index_low);
			type&& data_to_move = unlink_at_with_dealloc(index_low);
			
			if (temp_front_index < 0)
			{
				sorted_list.push_front(std::move(data_to_move));
				curr_index = temp_front_index;
			}
			else
			{
				sorted_list.insert_after(curr_index, 
					std::move(data_to_move));
				curr_index = sorted_list.get_node_at(curr_index)
					.next_index();
			}
			
		}
		
		
		the_front_index = temp_front_index;
		
		temp_front_index = -1;
		
		
		return the_front_index;
	}
	
	
	
	// This Is a semi-optimized (though accidentally implemented
	// differently from what was Intended) version of
	// insertion_sort_old_2()
	s32 insertion_sort_old_3() __attribute__((noinline))
	{
		s32& the_front_index = get_front_index();
		
		// Don't do anything if this list has zero or one nodes.
		if (the_front_index < 0)
		{
			return the_front_index;
		}
		if (get_node_at(the_front_index).next_index() < 0)
		{
			return the_front_index;
		}
		
		
		//s32 temp_front_index = -1;
		//SaListBackend<type> sorted_list(&temp_front_index, 
		//	node_array, ptr_to_the_free_list_backend, 
		//	total_num_nodes);
		ExternallyAllocatedList<type> sorted_list(node_array, 
			the_free_list_backend_ptr, get_total_num_nodes());
		
		s32& temp_front_index = sorted_list.get_front_index();
		
		
		static constexpr u32 prev_index_low_arr_size = 20;
		s32 prev_index_low_arr[prev_index_low_arr_size];
		
		for (s32 i=prev_index_low_arr_size-1; i>=0; --i)
		{
			prev_index_low_arr[i] = 0;
		}
		
		
		s32 curr_index = temp_front_index;
		
		for (s32 i=the_front_index;
			i!=-1;)
			//i=get_node_at(i).next_index())
		{
			u32 num_extra_low_indices = 0;
			
			
			s32 index_low = i;
			
			Node<type>* node_at_j;
			
			type* data_at_index_low = &get_node_at(index_low).data;
			
			// Find the lowest value at or after i.
			for (s32 j=index_low;
				j!=-1; 
				j=node_at_j->next_index())
			{
				node_at_j = &get_node_at(j);
				
				if (node_at_j->data 
					< *data_at_index_low)
				{
					if (num_extra_low_indices + 1 
						< prev_index_low_arr_size)
					{
						prev_index_low_arr[num_extra_low_indices++]
							= index_low;
					}
					
					index_low = j;
					
					//data_at_index_low = &get_node_at(index_low).the
					data_at_index_low = &node_at_j->data;
				}
			}
			
			Node<type>& node_at_index_low = get_node_at(index_low);
			//const type data_to_move = node_at_index_low.data;
			//type&& data_to_move = node_at_index_low.data
			
			if (i == index_low)
			{
				i = node_at_index_low.next_index();
			}
			
			//erase_at(index_low);
			type&& data_to_move = unlink_at_with_dealloc(index_low);
			
			if (temp_front_index < 0)
			{
				sorted_list.push_front(std::move(data_to_move));
				curr_index = temp_front_index;
			}
			else
			{
				sorted_list.insert_after(curr_index, 
					std::move(data_to_move));
				curr_index = sorted_list.get_node_at(curr_index)
					.next_index();
			}
			
			
			for (u32 j=0; j<num_extra_low_indices; ++j)
			{
				s32& curr_prev_index_low = prev_index_low_arr[j];
				
				Node<type>& node_at_curr_prev_index_low 
					= get_node_at(curr_prev_index_low);
				
				if (i == curr_prev_index_low)
				{
					i = node_at_curr_prev_index_low.next_index();
				}
				
				type&& curr_data_to_move = unlink_at_with_dealloc
					(curr_prev_index_low);
				
				//if (temp_front_index < 0)
				//{
				//	sorted_list.push_front(std::move(data_to_move));
				//	curr_index = temp_front_index;
				//}
				//else
				{
					sorted_list.insert_after(curr_index, 
						std::move(curr_data_to_move));
					curr_index = sorted_list.get_node_at
						(curr_index).next_index();
				}
			}
		}
		
		
		the_front_index = temp_front_index;
		
		temp_front_index = -1;
		
		
		return the_front_index;
	}
	
	
	inline s32 insertion_sort()
	{
		return the_list_backend.insertion_sort();
	}
	
	
	inline s32 merge_sort_via_array()
	{
		return the_list_backend.merge_sort_via_array();
	}
	
	
protected:		// functions
	inline void internal_func_subarr_merge_2(type* left_subarr,
		const size_t left_subarr_size, type* right_subarr, 
		const size_t right_subarr_size, type* out_subarr)
		__attribute__((always_inline))
	{
		const size_t out_subarr_size = left_subarr_size 
			+ right_subarr_size;
		
		size_t i = 0, j = 0;
		
		for (size_t k=0; k<out_subarr_size; ++k)
		{
			if (i >= left_subarr_size)
			{
				out_subarr[k] = right_subarr[j];
				++j;
			}
			else if (j >= right_subarr_size)
			{
				out_subarr[k] = left_subarr[i];
				++i;
			}
			else // if (i < left_subarr_size && j < right_subarr_size)
			{
				if (left_subarr[i] < right_subarr[j])
				{
					out_subarr[k] = left_subarr[i];
					++i;
				}
				else
				{
					out_subarr[k] = right_subarr[j];
					++j;
				}
			}
		}
	}
	
public:		// functions
	s32 merge_sort_via_array_2() 
		__attribute__((noinline))
	{
		s32& the_front_index = get_front_index();
		
		const size_t real_num_nodes = get_size();
		
		
		DynArr<type> arr_a(real_num_nodes), work_arr(real_num_nodes);
		
		
		{
		
		size_t temp = 0;
		while (the_front_index >= 0)
		{
			arr_a[temp++] = std::move(get_node_array()[the_front_index]
				.data);
			
			pop_front_basic();
		}
		
		}
		
		//static constexpr size_t last_subarr_size = 20;
		static constexpr size_t last_subarr_size = 1;
		
		
		if (last_subarr_size > 1)
		{
			ASM_COMMENT("last_subarr_size > 1; before");
			
			size_t subarr_offset, subarr_size;
			
			// This Is an insertion sort of PORTIONS of arr_a.
			for (subarr_offset=0;
				subarr_offset<real_num_nodes;
				subarr_offset+=subarr_size)
			{
				subarr_size = last_subarr_size;
				
				if (subarr_offset + subarr_size >= real_num_nodes)
				{
					subarr_size = real_num_nodes - subarr_offset;
				}
				
				ExtrasType::subarr_insertion_sort(arr_a, subarr_offset,
					subarr_size);
			}
			
			ASM_COMMENT("last_subarr_size > 1; after");
		}
		
		
		
		size_t left_subarr_offset = 0, right_subarr_offset = 0;
		type * left_subarr, * right_subarr;
		size_t left_subarr_size = 0, right_subarr_size = 0;
		
		
		static constexpr bool do_swap = true;
		
		bool main_arr_is_arr_a = false;
		PrevCurrPair<DynArr<type>*> main_arr_pc_pair,
			secondary_arr_pc_pair;
		
		//if (!do_swap)
		{
			main_arr_pc_pair.prev = main_arr_pc_pair.curr = &arr_a;
			secondary_arr_pc_pair.prev = secondary_arr_pc_pair.curr 
				= &work_arr;
		}
		
		// Avoid recursion
		//for (size_t subarr_size=first_subarr_size;
		//	subarr_size<real_num_nodes;
		//	subarr_size*=2)
		for (size_t subarr_size=real_num_nodes;
			subarr_size>=last_subarr_size;
			subarr_size/=2)
		{
			if (do_swap)
			{
				if (main_arr_is_arr_a)
				{
					main_arr_pc_pair.back_up_and_update(&work_arr);
					secondary_arr_pc_pair.back_up_and_update(&arr_a);
					main_arr_is_arr_a = false;
				}
				else // if (!main_arr_is_arr_a)
				{
					main_arr_pc_pair.back_up_and_update(&arr_a);
					secondary_arr_pc_pair.back_up_and_update(&work_arr);
					main_arr_is_arr_a = true;
				}
			}
			
			auto get_merge_args = [&](DynArr<type>& specific_arr, 
				size_t n_left_subarr_offset) -> void
			{
				right_subarr_offset = 0;
				right_subarr = NULL;
				right_subarr_size = 0;
				
				
				left_subarr_offset = n_left_subarr_offset;
				left_subarr = &(specific_arr[left_subarr_offset]);
				left_subarr_size = subarr_size;
				
				
				if (left_subarr_offset + left_subarr_size 
					>= real_num_nodes)
				{
					left_subarr_size = real_num_nodes - left_subarr_offset;
					return;
				}
				
				
				right_subarr_offset = left_subarr_offset 
					+ left_subarr_size;
				right_subarr = &(specific_arr[right_subarr_offset]);
				right_subarr_size = subarr_size;
				
				if (right_subarr_offset + right_subarr_size 
					>= real_num_nodes)
				{
					right_subarr_size = real_num_nodes 
						- right_subarr_offset;
				}
				
				
			};
			
			get_merge_args(*main_arr_pc_pair.curr, 0);
			
			for (size_t i=0; i<real_num_nodes; i+=subarr_size*2)
			{
				internal_func_subarr_merge_2(left_subarr, 
					left_subarr_size, right_subarr, right_subarr_size,
					&((*secondary_arr_pc_pair.curr)[i]));
				
				//if (i + (subarr_size * 2) < real_num_nodes)
				{
					get_merge_args(*main_arr_pc_pair.curr, 
						i + (subarr_size * 2));
				}
			}
			
			if (!do_swap)
			{
				for (s32 i=real_num_nodes-1; i>=0; --i)
				{
					arr_a[i] = work_arr[i];
				}
			}
			
		}
		
		//if (last_subarr_size > 1)
		//{
		//	ExtrasType::subarr_insertion_sort((*main_arr_pc_pair.prev), 
		//		0, real_num_nodes);
		//}
		
		for (s32 i=real_num_nodes-1; i>=0; --i)
		{
			//s32 curr_index = (*main_arr_pc_pair.prev)[i]
			push_front((*main_arr_pc_pair.prev)[i]);
		}
		
		//if (last_subarr_size > 1)
		//{
		//	insertion_sort();
		//}
		
		
		return the_front_index;
	}
	
	//inline s32 heapsort_via_array()
	//{
	//	return the_list_backend.heapsort_via_array();
	//}
	
	
} __attribute__((_align4));



// This Is a template class for a statically allocated array of modifiable
// doubly-linked lists.  "sa" Is short for "statically allocated".
template<typename type, u32 total_num_nodes, u32 num_lists >
class SaArrayOfLists
{
public:		// variables
	ExternallyAllocatedList<type> ea_list_array[num_lists];
	Node<type> node_array[total_num_nodes];
	
	SaFreeList<total_num_nodes> the_free_list;
	
public:		// functions
	
	inline SaArrayOfLists()
	{
		for (s32 i=(s32)get_array_size()-1; i>=0; --i)
		{
			ea_list_array[i].init(node_array,
				&the_free_list.the_sa_free_list_backend, 
				get_total_num_nodes());
		}
		
		
	}
	
	constexpr inline u32 get_array_size() const
	{
		return get_num_lists();
	}
	constexpr inline u32 get_node_array_size() const
	{
		return get_total_num_nodes();
	}
	
	constexpr inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	constexpr inline u32 get_num_lists() const
	{
		return num_lists;
	}
	
} __attribute__((_align4));

} // end of namespace SaListStuff


#endif		// sa_list_class_stuff_hpp
