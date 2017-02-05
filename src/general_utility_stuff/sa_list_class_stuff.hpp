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


namespace sa_list_stuff
{

// A non-template class intended to be used by the list_backend class.
class node_contents
{
public:		// constants
	static constexpr size_t vec2_index_for_next_index = vec2_index_for_x,
		vec2_index_for_prev_index = vec2_index_for_y;
	
public:		// variables
	void* data_ptr;
	
	vec2_s16* index_pair_ptr;
	
public:		// functions
	// This is safe so long as data_ptr is the first member variable of the
	// node_contents class.
	inline void* get_node_as_void_ptr()
	{
		return data_ptr;
	}
	
	template< typename type >
	inline type* cast_data_ptr()
	{
		return static_cast<type*>(data_ptr);
	}
	
	inline vec2_s16& get_index_pair()
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




// Store only the original index of the node and a void pointer to its
// data.  This is intended for use in array-based sorting algorithms that
// only change how nodes are linked.
class node_data_and_index
{
public:		// variables
	void* data_ptr = NULL;
	s32 index = -1;
	
public:		// functions
	inline node_data_and_index()
	{
	}
	
	inline node_data_and_index( void* s_data_ptr, s32 s_index ) 
		: data_ptr(s_data_ptr), index(s_index)
	{
	}
	
	
	inline s32 get_index() const
	{
		return index;
	}
	
} __attribute__((_align4));


//class ndai_dyn_arr
//{
//protected:		// variables
//	node_data_and_index* arr;
//	
//public:		// functions
//	ndai_dyn_arr( size_t s_size )
//	{
//		arr = new node_data_and_index[s_size];
//	}
//	~ndai_dyn_arr()
//	{
//		delete [] arr;
//	}
//	
//	inline node_data_and_index* get_arr()
//	{
//		return arr;
//	}
//	
//	inline node_data_and_index& operator [] ( size_t index )
//	{
//		return get_arr()[index];
//	}
//	
//} __attribute__((_align4));

typedef dyn_arr<node_data_and_index> ndai_dyn_arr;



template< typename type >
class node
{
//public:		// constants
//	static constexpr size_t vec2_index_for_next_index 
//		= node_contents::vec2_index_for_next_index,
//	vec2_index_for_prev_index 
//		= node_contents::vec2_index_for_prev_index;
	
public:		// variables
	type data __attribute__((_align4)) = type();
	//vec2_s32 index_pair = { -1, -1 };
	vec2_s16 index_pair = { -1, -1 };
	
public:		// functions
	inline node()
	{
	}
	
	//inline node()
	//{
	//	data = type();
	//	next_index = -1;
	//	prev_index = -1;
	//}
	
	template< typename type_in_vec2 >
	inline node( const type& data_to_copy, 
		vec2<type_in_vec2> s_index_pair ) : data(data_to_copy)
	{
		next_index() = get_next_index_from_vec2(s_index_pair);
		prev_index() = get_prev_index_from_vec2(s_index_pair);
	}
	
	inline s16& next_index()
	{
		return index_pair
			[node_contents::vec2_index_for_next_index];
	}
	inline s16& prev_index()
	{
		return index_pair
			[node_contents::vec2_index_for_prev_index];
	}
	
	
protected:		// functions
	template< typename type_in_vec2 >
	static inline s16 get_next_index_from_vec2
		( const vec2<type_in_vec2>& n_index_pair )
	{
		return static_cast<s16>(n_index_pair
			[node_contents::vec2_index_for_next_index]);
	}
	template< typename type_in_vec2 >
	static inline s16 get_prev_index_from_vec2
		( const vec2<type_in_vec2>& n_index_pair )
	{
		return static_cast<s16>(n_index_pair
			[node_contents::vec2_index_for_prev_index]);
	}
	
	
} __attribute__((_align4));




// This is basically a queue stored in an external circular buffer that
// doesn't permit erasing elements.
class circ_buf_helper
{
protected:		// variables
	s32* the_array = NULL;
	
	// The maximum size of the_array, the number of used elements in the
	// array, and the TRUE start and end indices of the_array.
	size_t max_size = 0, real_size = 0, head = 0, tail = 0;
	
	//friend class iterator;
	
public:		// classes
	class iterator
	{
	public:		// enums
		enum class index_type : u32
		{
			it_other,
			it_head,
			it_tail,
			
		} alignas_regular;
		
	protected:  // variables
		circ_buf_helper *const cbuf_helper_ptr;
		size_t pos;
		index_type the_index_type;
		
	public:		// functions
		inline iterator( circ_buf_helper* s_cbuf_helper_ptr, 
			size_t s_pos, 
			index_type s_the_index_type=index_type::it_other ) 
			: cbuf_helper_ptr(s_cbuf_helper_ptr), pos(s_pos),
			the_index_type(s_the_index_type)
		{
		}
		
		inline circ_buf_helper *const get_cbuf_helper_ptr() const
		{
			return cbuf_helper_ptr;
		}
		inline size_t get_pos() const
		{
			return pos;
		}
		inline index_type get_the_index_type() const
		{
			return the_index_type;
		}
		
		inline bool operator == ( const iterator& other ) const
		{
			return !( *this != other );
		}
		
		// Required for a range-based for loop
		inline bool operator != ( const iterator& other ) const
		{
			//return ( pos != other.pos ) || ( ( pos == other.pos )
			//	&& ( get_is_head() != other.get_is_head() ) );
			
			if ( get_pos() != other.get_pos() )
			{
				return true;
			}
			
			return same_pos_not_equals(other);
		}
		
	protected:		// functions
		
		inline bool same_pos_not_equals ( const iterator& other ) const
		{
			// At this point, is is known that pos == other.pos
			if ( get_cbuf_helper_ptr() != other.get_cbuf_helper_ptr() )
			{
				return true;
			}
			
			// At this point, it is known that pos == other.pos, and both
			// iterators are from the same circ_buf_helper.
			if ( get_cbuf_helper_ptr()->get_real_size() == 0 )
			{
				return false;
			}
			
			if ( get_the_index_type() != other.get_the_index_type() )
			{
				return true;
			}
			
			
			// At this point, it is known that both iterators are at the
			// head of the same circ_buf_helper, so they are equal.
			return false;
		}
		
	public:		// functions
		
		inline const s32 operator * () const
		{
			//return cbuf_helper_ptr->the_array[pos];
			return cbuf_helper_ptr->at(pos);
		}
		
		const iterator& operator ++ ()
		{
			auto get_corrected_other_pos = [&]( const size_t other_pos ) 
				-> size_t
			{
				//get_pos() >= get_cbuf_helper_ptr()->get_max_size() 
				if ( other_pos >= get_cbuf_helper_ptr()->get_max_size() )
				{
					return 0;
				}
				return other_pos;
			};
			
			
			if ( get_cbuf_helper_ptr()->get_real_size() > 1 )
			{
				const size_t updated_pos = get_corrected_other_pos
					( get_pos() + 1 );
				
				if ( get_the_index_type() == index_type::it_head )
				{
					the_index_type = index_type::it_other;
					pos = updated_pos; 
				}
				else if ( get_pos() == get_cbuf_helper_ptr()->get_tail() )
				{
					the_index_type = index_type::it_tail;
				}
				else
				{
					pos = updated_pos;
				}
			}
			else
			{
				// PROPERLY handle iterators.
				if ( get_cbuf_helper_ptr()->get_real_size() == 1 )
				{
					the_index_type = index_type::it_tail;
				}
			}
			
			
			return *this;
		}
		
		
		
	} __attribute__((_align4));
	
	friend const s32 iterator::operator * () const;
	
public:		// functions
	circ_buf_helper( s32* s_the_array, size_t s_max_size )
		: the_array(s_the_array), max_size(s_max_size)
	{
		//// Don't call reset() here since it's called by
		//// insertion_sort_inner_loop.
		//reset();
	}
	
	circ_buf_helper& operator = ( const circ_buf_helper& to_copy )
	{
		the_array = to_copy.the_array;
		max_size = to_copy.max_size;
		head = to_copy.head;
		tail = to_copy.tail;
		
		return *this;
	}
	inline void reset()
	{
		arr_memfill32( the_array, -1, get_max_size() );
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
	inline s32 at( size_t offset ) const
	{
		return the_array[offset];
	}
	
	inline iterator begin()
	{
		return iterator( this, get_head(), iterator::index_type::it_head );
	}
	inline iterator end()
	{
		return iterator( this, get_tail(), iterator::index_type::it_tail );
	}
	
	void push( s32 to_push )
	{
		auto get_corrected_other_pos = [&]( const size_t other_pos ) 
			-> size_t
		{
			if ( other_pos >= get_max_size() )
			{
				return 0;
			}
			return other_pos;
		};
		
		
		// Update real_size
		if ( get_real_size() < get_max_size() )
		{
			++real_size;
		}
		
		if ( get_real_size() == 1 )
		{
			the_array[get_tail()] = to_push;
			
			return;
		}
		
		
		tail = get_corrected_other_pos(get_tail() + 1);
		the_array[get_tail()] = to_push;
		
		if ( get_real_size() == get_max_size() )
		{
			head = get_corrected_other_pos(get_tail() + 1);
		}
		
		
	}
	
} __attribute__((_align4));

class extras_fp_group
{
public:		// typedefs
	typedef void (*sis_fp)( ndai_dyn_arr&, const size_t, const size_t );
	
public:		// function pointers
	// Function pointers used by various functions in the list_backend
	// class.
	
	generic_void_2arg_fp specific_type_copy_fp = NULL;
	generic_void_2arg_fp specific_type_move_fp = NULL;
	generic_void_1arg_fp specific_type_reset_fp = NULL;
	generic_void_2arg_fp specific_type_swap_fp = NULL;
	
	
	generic_u32_2arg_fp specific_type_less_fp = NULL;
	generic_u32_2arg_fp specific_type_greater_fp = NULL;
	qscmp_fp specific_type_qscmp_fp = NULL;
	
	
	generic_void_ptr_1arg_fp get_node_data_fp = NULL;
	generic_vec2_s16_ptr_1arg_fp get_index_pair_fp = NULL;
	generic_void_2arg_fp conv_node_to_contents_fp = NULL;
	generic_void_2arg_fp insertion_sort_inner_loop_fp = NULL;
	
	sis_fp subarr_insertion_sort_fp = NULL;
	
	
	
	//// The only reason this static_assert is wrapped inside a class that
	//// has nothing else in it is to work around a bug in a Vim plugin that
	//// I use (Taghighlight specifically).  I don't have any idea why this
	//// is even an issue, but oh well.
	//class wrapped_static_asserts
	//{
	//public:		// functions
	//	inline wrapped_static_asserts()
	//	{
	//		static_assert( std::is_trivially_copyable<extras_fp_group>
	//			::value,
	//			"Can't use struct_memcpy() in extras_fp_group::operator = "
	//			"() !" );
	//	}
	//} __attribute__((_align4));
	
public:		// functions
	inline extras_fp_group()
	{
	}
	inline extras_fp_group( generic_void_2arg_fp s_specific_type_copy_fp,
		generic_void_2arg_fp s_specific_type_move_fp,
		generic_void_1arg_fp s_specific_type_reset_fp,
		generic_void_2arg_fp s_specific_type_swap_fp,
		
		generic_u32_2arg_fp s_specific_type_less_fp,
		generic_u32_2arg_fp s_specific_type_greater_fp,
		qscmp_fp s_specific_type_qscmp_fp,
		
		generic_void_ptr_1arg_fp s_get_node_data_fp,
		generic_vec2_s16_ptr_1arg_fp s_get_index_pair_fp,
		generic_void_2arg_fp s_conv_node_to_contents_fp,
		generic_void_2arg_fp s_insertion_sort_inner_loop_fp,
		sis_fp s_subarr_insertion_sort_fp )
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
	
	inline extras_fp_group( const extras_fp_group& to_copy )
	{
		*this = to_copy;
	}
	
	//inline extras_fp_group& operator = ( const extras_fp_group& to_copy )
	//{
	//	struct_memcpy( *this, to_copy );
	//	
	//	return *this;
	//}
	
	
	inline generic_void_2arg_fp get_specific_type_copy_fp() const
	{
		return specific_type_copy_fp;
	}
	inline generic_void_2arg_fp get_specific_type_move_fp() const
	{
		return specific_type_move_fp;
	}
	inline generic_void_1arg_fp get_specific_type_reset_fp() const
	{
		return specific_type_reset_fp;
	}
	inline generic_void_2arg_fp get_specific_type_swap_fp() const
	{
		return specific_type_swap_fp;
	}
	
	
	inline generic_u32_2arg_fp get_specific_type_less_fp() const
	{
		return specific_type_less_fp;
	}
	inline generic_u32_2arg_fp get_specific_type_greater_fp() const
	{
		return specific_type_greater_fp;
	}
	inline qscmp_fp get_specific_type_qscmp_fp() const
	{
		return specific_type_qscmp_fp;
	}
	
	
	inline generic_void_ptr_1arg_fp get_get_node_data_fp() const
	{
		return get_node_data_fp;
	}
	inline generic_vec2_s16_ptr_1arg_fp get_get_index_pair_fp() const
	{
		return get_index_pair_fp;
	}
	inline generic_void_2arg_fp get_conv_node_to_contents_fp() const
	{
		return conv_node_to_contents_fp;
	}
	inline generic_void_2arg_fp get_insertion_sort_inner_loop_fp() const
	{
		return insertion_sort_inner_loop_fp;
	}
	inline sis_fp get_subarr_insertion_sort_fp() const
	{
		return subarr_insertion_sort_fp;
	}
	
} __attribute__((_align4));


// A group of functions to use as function pointers in the list_backend
// class.
template< typename type >
class list_extras
{
protected:		// functions to point to
	static void specific_type_copy( type* a, type* b )
		__attribute__((_text_hot_section))
	{
		*a = *b;
	}
	static void specific_type_move( type* a, type* b )
		__attribute__((_text_hot_section))
	{
		*a = std::move(*b);
	}
	static void specific_type_reset( type* to_reset )
		__attribute__((_text_hot_section))
	{
		*to_reset = type();
	}
	static void specific_type_swap( type* a, type* b )
		__attribute__((_text_hot_section))
	{
		//type temp = std::move(*a);
		//*a = std::move(*b);
		//*b = std::move(temp);
		std::swap( *a, *b );
	}
	
	static u32 specific_type_less( type* a, type* b )
		__attribute__((_text_hot_section))
	{
		return ( (*a) < (*b) );
	}
	static u32 specific_type_greater( type* a, type* b )
		__attribute__((_text_hot_section))
	{
		return ( (*a) > (*b) );
	}
	
	// qsort() comparison function
	static int specific_type_qscmp( const type* a, const type* b )
		__attribute__((_text_hot_section))
	{
		if ( (*a) < (*b) )
		{
			return -1;
		}
		else if ( (*a) == (*b) )
		{
			return 0;
		}
		else // if ( (*a) > (*b) )
		{
			return 1;
		}
	}
	
	static void* get_node_data( node<type>* to_get_from )
		__attribute__((_text_hot_section))
	{
		return &to_get_from->data;
	}
	static vec2_s16* get_sa_list_index_pair( node<type>* to_get_from )
		__attribute__((_text_hot_section))
	{
		return &to_get_from->index_pair;
	}
	static void conv_node_to_contents( node_contents* ret,
		node<type>* to_convert ) __attribute__((_text_hot_section))
	{
		ret->data_ptr = &to_convert->data;
		ret->index_pair_ptr = &to_convert->index_pair;
	}
	
	
	// Instead of having the ENTIRE insertion_sort function be duplicated
	// for EVERY externally_allocated_sa_list instantiation, only duplicate
	// the inner loop.  This seems pretty good to me.
	//
	// Note:  old_il_cbuf_helper is a CIRCULAR BUFFER helper that allows
	// keeping track of a FIXED NUMBER of indices to nodes for sorting
	// purposes.
	static void insertion_sort_inner_loop( node<type>* node_array, 
		s32* index_low_ptr ) //__attribute__((_text_hot_section))
	{
		node<type>* node_at_j;
		
		s32& index_low = *index_low_ptr;
		
		type* data_at_index_low = &(node_array[index_low].data);
		
		// Find the lowest value at or after i.
		for ( s32 j=index_low;
			j!=-1; 
			j=node_at_j->next_index() )
		{
			//node_at_j = &get_node_at(j);
			node_at_j = &(node_array[j]);
			
			//if ( node_at_j->data 
			//	< get_node_at(index_low).data )
			if ( (node_at_j->data) < (*data_at_index_low) )
			{
				index_low = j;
				
				data_at_index_low = &(node_at_j->data);
			}
		}
		
	}
	
	
	static void subarr_insertion_sort( ndai_dyn_arr& arr_a,
		const size_t subarr_offset, const size_t subarr_size )
		//__attribute__((_text_hot_section))
	{
		size_t curr_offset = subarr_offset;
		
		
		for ( size_t i=1; i<subarr_size; ++i )
		{
			size_t j = ++curr_offset;
			
			while ( j > 0 && *(type*)arr_a[j - 1].data_ptr
				> *(type*)arr_a[j].data_ptr )
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
	// This is the first time I've used an "auto" return type much, but it
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
	static inline extras_fp_group::sis_fp get_subarr_insertion_sort_fp()
	{
		//return reinterpret_cast<extras_fp_group::sis_fp>
		//	(&subarr_insertion_sort);
		return &subarr_insertion_sort;
	}
	
	static inline extras_fp_group get_extras_fp_group()
	{
		return extras_fp_group( get_specific_type_copy_fp(),
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
			get_subarr_insertion_sort_fp() );
	}
	
	
public:		// functions to not point to
	static inline void subarr_insertion_sort( dyn_arr<type>& arr_a,
		const size_t subarr_offset, const size_t subarr_size )
		__attribute__((always_inline))
	{
		//if ( subarr_offset + subarr_size >= real_num_nodes )
		//{
		//	subarr_size = real_num_nodes - subarr_offset;
		//}
		
		size_t curr_offset = subarr_offset;
		
		for ( size_t i=1; i<subarr_size; ++i )
		{
			size_t j = ++curr_offset;
			
			while ( j > 0 && ( arr_a[j - 1] > arr_a[j] ) )
			{
				std::swap( arr_a[j], arr_a[j - 1] );
				
				--j;
			}
		}
	}
	
	//static void subarr_merge( node_data_and_index* left_subarr, 
	//	const size_t left_subarr_size, node_data_and_index* right_subarr,
	//	const size_t right_subarr_size, node_data_and_index* out_subarr )
	//{
	//	
	//}
	
} __attribute__((_align4));





// This class exists because C++ templates CAN generate too much code.  Oh,
// and I can put code in IWRAM this way!
class list_backend
{
protected:		// variables
	size_t size = 0;
	
	s32 front_index = -1, back_index = -1;
	
	// node_array as a void pointer.
	void* node_array = NULL;
	
	sa_free_list_backend* the_free_list_backend_ptr = NULL;
	
	
	u32 total_num_nodes = 0;
	
	// node stuff
	u32 specific_type_size = 0, 
		whole_node_size = 0;
	
	
	extras_fp_group the_extras_fp_group;
	
	template< typename type > friend class externally_allocated_list;
	
protected:		// functions
	inline list_backend() : size(0)
	{
	}
	// Dang, I had no idea it'd be this nice to get types automatically
	// this way.
	inline list_backend( void* s_node_array, 
		sa_free_list_backend* s_the_free_list_backend_ptr,
		u32 s_total_num_nodes, u32 s_specific_type_size,
		u32 s_whole_node_size, 
		
		const extras_fp_group& s_the_extras_fp_group )
	{
		init( s_node_array, s_the_free_list_backend_ptr,
			s_total_num_nodes, s_specific_type_size, s_whole_node_size,
			s_the_extras_fp_group );
	}
	inline list_backend( list_backend& to_copy )
	{
		init(to_copy);
	}
	
	void init( void* n_node_array, 
		sa_free_list_backend* n_the_free_list_backend_ptr,
		u32 n_total_num_nodes, u32 n_specific_type_size,
		u32 n_whole_node_size, 
		
		const extras_fp_group& n_the_extras_fp_group );
	
	inline void init( list_backend& to_copy )
	{
		init( to_copy.get_node_array(), 
			to_copy.get_the_free_list_backend_ptr(),
			to_copy.get_total_num_nodes(), 
			to_copy.get_specific_type_size(),
			to_copy.get_whole_node_size(), 
			
			to_copy.get_the_extras_fp_group() );
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
	
	inline sa_free_list_backend* get_the_free_list_backend_ptr()
	{
		return the_free_list_backend_ptr;
	}
	inline const sa_free_list_backend* get_the_free_list_backend_ptr()
		const
	{
		return the_free_list_backend_ptr;
	}
	inline sa_free_list_backend& get_the_free_list_backend()
	{
		return *get_the_free_list_backend_ptr();
	}
	inline const sa_free_list_backend& get_the_free_list_backend() const
	{
		return *get_the_free_list_backend_ptr();
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
	
	inline const extras_fp_group& get_the_extras_fp_group()
	{
		return the_extras_fp_group;
	}
	
	
	
	inline uintptr_t get_node_addr_at( s32 index ) const
	{
		return reinterpret_cast<uintptr_t>(get_node_array())
			+ arr_byte_index_macro( whole_node_size, index );
	}
	
	
	
	// These three functions are intended to be used sparingly.  They make
	// most sense to use when their result is the ONLY part of a node that
	// is relevant, and in that case it is still best to ONLY CALL them
	// ONCE PER NODE.
	inline void* get_node_data_at_index( s32 index )
	{
		return get_node_data_at(get_node_addr_at(index));
	}
	inline vec2_s16* get_index_pair_at_index( s32 index )
	{
		return get_index_pair_at(get_node_addr_at(index));
	}
	inline s16& get_next_index_at_index( s32 index )
	{
		return get_next_index_at(get_node_addr_at(index));
	}
	inline s16& get_prev_index_at_index( s32 index )
	{
		return get_prev_index_at(get_node_addr_at(index));
	}
	
	
	inline void* get_node_data_at( uintptr_t addr )
	{
		return get_the_extras_fp_group().get_get_node_data_fp()
			(reinterpret_cast<void*>(addr));
	}
	inline vec2_s16* get_index_pair_at( uintptr_t addr )
	{
		return get_the_extras_fp_group().get_get_index_pair_fp()
			(reinterpret_cast<void*>(addr));
	}
	inline s16& get_next_index_at( uintptr_t addr )
	{
		return ((*get_index_pair_at(addr))
			[node_contents::vec2_index_for_next_index]);
	}
	inline s16& get_prev_index_at( uintptr_t addr )
	{
		return ((*get_index_pair_at(addr))
			[node_contents::vec2_index_for_prev_index]);
	}
	
	inline node_contents get_node_contents_at( s32 index )
	{
		uintptr_t node_addr = get_node_addr_at(index);
		
		//node_contents ret = { get_node_data_at(node_addr),
		//	get_index_pair_at(node_addr) };
		
		node_contents ret;
		
		get_the_extras_fp_group().get_conv_node_to_contents_fp()( &ret, 
			reinterpret_cast<void*>(node_addr) );
		
		return ret;
	}
	
	
	// Make sure to call this with node DATA!
	inline void copy_node_data( void* dst_node_data, 
		const void* src_node_data )
	{
		get_the_extras_fp_group().get_specific_type_copy_fp()
			( dst_node_data, const_cast<void*>(src_node_data) );
	}
	inline void move_node_data( void* dst_node_data, 
		const void* src_node_data )
	{
		get_the_extras_fp_group().get_specific_type_move_fp()
			( dst_node_data, const_cast<void*>(src_node_data) );
	}
	
	
	inline void assign_to_node_data( node_contents& dst_node_contents, 
		const void* n_data, u32 can_move_value )
	{
		if (!can_move_value)
		{
			copy_node_data( dst_node_contents.data_ptr, n_data );
		}
		else //if (can_move_value)
		{
			move_node_data( dst_node_contents.data_ptr, n_data );
		}
	}
	inline void assign_to_whole_node
		( node_contents& dst_node_contents, const void* n_data,
		const vec2_s16& n_index_pair, u32 can_move_value )
	{
		assign_to_node_data( dst_node_contents, n_data, 
			can_move_value );
		copy_vec2_s16_via_ptr( *dst_node_contents.index_pair_ptr,
			n_index_pair );
	}
	
	
	// Make sure to call this with node DATA!
	inline void call_specific_type_swap_func( void* node_a_data, 
		void* node_b_data )
	{
		get_the_extras_fp_group().get_specific_type_swap_fp()
			( node_a_data, node_b_data );
	}
	inline u32 call_specific_type_less_func( void* node_a_data, 
		void* node_b_data )
	{
		return get_the_extras_fp_group().get_specific_type_less_fp()
			( node_a_data, node_b_data );
	}
	inline u32 call_specific_type_greater_func( void* node_a_data, 
		void* node_b_data )
	{
		return get_the_extras_fp_group().get_specific_type_greater_fp()
			( node_a_data, node_b_data );
	}
	inline int call_specific_type_qscmp_func( const void* node_a_data,
		const void* node_b_data )
	{
		return get_the_extras_fp_group().get_specific_type_qscmp_fp()
			( node_a_data, node_b_data );
	}
	
	inline void call_insertion_sort_inner_loop_func( s32& index_low )
	{
		get_the_extras_fp_group().get_insertion_sort_inner_loop_fp()
			( get_node_array(), &index_low );
	}
	
	
	void fully_deallocate() __attribute__((_iwram_code));
	void fully_deallocate_via_unlink() __attribute__((_iwram_code));
	
	
	
	// This is used by frontends to the internal_func_move_unlinked_node*
	// functions
	void internal_func_allocate_and_assign_to_node( s32& index, 
		node_contents& node, const void* n_data, u32 can_move_value );
		__attribute__((_iwram_code));
	
	
	
	
	
	//// This is its own function because it's used by both push_front() and
	//// push_back().
	//inline s32 internal_func_push_front_unique_code( s32 to_push_index,
	//	node_contents node_to_push )
	//{
	//}
	
	// push_front() CAN affect back_index
	inline s32 push_front( const void* to_push, u32 can_move_value=false )
	{
		s32 to_push_index;
		node_contents node_to_push;
		
		internal_func_allocate_and_assign_to_node( to_push_index,
			node_to_push, to_push, can_move_value );
		
		return internal_func_move_unlinked_node_to_front( to_push_index,
			node_to_push );
	}
	
	// push_back() ALWAYS affects back_index
	inline s32 push_back( const void* to_push, u32 can_move_value=false )
	{
		s32 new_index;
		node_contents new_node;
		internal_func_allocate_and_assign_to_node( new_index, new_node,
			to_push, can_move_value );
		
		return internal_func_move_unlinked_node_to_back( new_index,
			new_node );
	}
	
	// insert_before() won't affect back_index
	inline s32 insert_before( s32 index, const void* to_insert,
		u32 can_move_value=false )
	{
		s32 to_insert_index;
		node_contents node_to_insert;
		
		internal_func_allocate_and_assign_to_node( to_insert_index,
			node_to_insert, to_insert, can_move_value );
		
		return internal_func_move_unlinked_node_before( index,
			to_insert_index, node_to_insert );
	}
	// insert_after() CAN affect back_index
	inline s32 insert_after( s32 index, const void* to_insert,
		u32 can_move_value=false )
	{
		s32 to_insert_index;
		node_contents node_to_insert;
		
		internal_func_allocate_and_assign_to_node( to_insert_index,
			node_to_insert, to_insert, can_move_value );
		
		return internal_func_move_unlinked_node_after( index,
			to_insert_index, node_to_insert );
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
	
	//s32 insert_before( s32 index, const void* to_insert,
	//	u32 can_move_value=false );
	//s32 insert_after( s32 index, const void* to_insert,
	//	u32 can_move_value=false );
	
	
	
	// Some of the functions for internal use 
	s32 internal_func_move_unlinked_node_to_front( s32 to_move_index, 
		node_contents& node_to_move );
		//__attribute__((_iwram_code));
		//__attribute__((noinline));
	inline s32 internal_func_move_unlinked_node_to_back( s32 to_move_index,
		node_contents& node_to_move )
	{
		// If there's nothing in the list
		if ( get_back_index() < 0 )
		{
			return internal_func_move_unlinked_node_to_front
				( to_move_index, node_to_move );
		}
		// If there's at least one element in the list
		else // if ( get_back_index() >= 0 )
		{
			return internal_func_move_unlinked_node_after
				( get_back_index(), to_move_index, node_to_move );
		}
	}
	s32 internal_func_move_unlinked_node_before( s32 to_move_before_index, 
		s32 to_move_index, node_contents& node_to_move );
		//__attribute__((_iwram_code));
		//__attribute__((noinline));
	s32 internal_func_move_unlinked_node_after( s32 to_move_after_index, 
		s32 to_move_index, node_contents& node_to_move );
		//__attribute__((_iwram_code));
		//__attribute__((noinline));
	
	
	// Give slightly more flexibility, at the expense of a small amount of
	// speed, to this function by allowing a pointer to the
	// node_at_index be passed to it.
	void* internal_func_unlink_at( s32 index, 
		node_contents* node_at_index_ptr=NULL );
		//__attribute__((_iwram_code));
		//__attribute__((noinline));
	
	
	//void internal_func_unlink_from_connected_index_at( s32 index, 
	//	u32 index_to_vec2 ); 
	//	//__attribute__((_iwram_code));
	//
	//inline void unlink_from_next_at( s32 index )
	//{
	//	internal_func_unlink_from_connected_index_at( index, 
	//		node_contents::vec2_index_for_next_index );
	//}
	//inline void unlink_from_prev_at( s32 index )
	//{
	//	internal_func_unlink_from_connected_index_at( index, 
	//		node_contents::vec2_index_for_prev_index );
	//}
	
	
	inline void move_linked_node_to_front( s32 to_move_index, 
		node_contents& node_to_move, list_backend& dst )
	{
		internal_func_unlink_at( to_move_index, &node_to_move );
		dst.internal_func_move_unlinked_node_to_front( to_move_index, 
			node_to_move );
	}
	inline void move_linked_node_to_back( s32 to_move_index, 
		node_contents& node_to_move, list_backend& dst )
	{
		internal_func_unlink_at( to_move_index, &node_to_move );
		dst.internal_func_move_unlinked_node_to_back( to_move_index, 
			node_to_move );
	}
	inline void move_linked_node_before( s32 to_move_before_index,
		s32 to_move_index, node_contents& node_to_move, 
		list_backend& dst )
	{
		internal_func_unlink_at( to_move_index, &node_to_move );
		dst.internal_func_move_unlinked_node_before( to_move_before_index, 
			to_move_index, node_to_move );
	}
	inline void move_linked_node_after( s32 to_move_after_index,
		s32 to_move_index, node_contents& node_to_move, 
		list_backend& dst )
	{
		internal_func_unlink_at( to_move_index, &node_to_move );
		dst.internal_func_move_unlinked_node_after( to_move_after_index, 
			to_move_index, node_to_move );
	}
	
	
	// End of functions for internal use.
	
	// It is (slightly) faster to just unlink a node than it is to erase it
	// because erase_at() ALSO resets the data of the node.  Use caution
	// when using this function!
	inline void* unlink_at_with_dealloc( s32 index )
	{
		get_the_free_list_backend().push(index);
		
		return internal_func_unlink_at(index);
	}
	
	inline void erase_at( s32 index )
	{
		get_the_extras_fp_group().get_specific_type_reset_fp()
			(unlink_at_with_dealloc(index));
	}
	
	
	
	
	//s32 insertion_sort() __attribute__((_iwram_code));
	//s32 insertion_sort() __attribute__((_text_hot_section));
	s32 insertion_sort(); //__attribute__((_iwram_code));
	
	
	
	//// These two functions are slowwwwwww because there is too much list
	//// traversal.  Thus, I have replaced them with an array of pointers
	//// based method.
	//s32 internal_func_merge( merge_args& args )
	//	__attribute__((_iwram_code));
	//s32 merge_sort() __attribute__((_iwram_code));
	
	
	
	void internal_func_subarr_merge( node_data_and_index* left_subarr,
		const size_t left_subarr_size, node_data_and_index* right_subarr, 
		const size_t right_subarr_size, node_data_and_index* out_subarr );
		//__attribute__((_iwram_code));
	
	// Top-down merge sort using an array of node_data_and_index's.
	s32 merge_sort_via_array(); //__attribute__((_iwram_code));
	
	
	//s32 heapsort_via_array();
	
	
} __attribute__((_align4));





template< typename type >
class externally_allocated_list
{
protected:		// typedefs
	typedef list_extras<type> extras_type;
	
//public:		// variables
protected:		// variables
	//s32* ptr_to_front_index;
	//s32 front_index;
	node<type>* node_array = 0;
	sa_free_list_backend* the_free_list_backend_ptr = 0;
	u32 total_num_nodes = 0;
	
	
public:		// variables, temporarily public
	list_backend the_list_backend;
	
public:		// functions
	inline externally_allocated_list() : the_list_backend()
	{
	}
	inline externally_allocated_list
		( node<type>* s_node_array, 
		sa_free_list_backend* s_the_free_list_backend_ptr,
		u32 s_total_num_nodes )
	{
		init( s_node_array, s_the_free_list_backend_ptr,
			s_total_num_nodes );
	}
	
	inline ~externally_allocated_list()
	{
		fully_deallocate();
	}
	
	
	void init( node<type>* n_node_array, 
		sa_free_list_backend* n_the_free_list_backend_ptr,
		u32 n_total_num_nodes ) __attribute__((noinline))
	{
		node_array = n_node_array;
		the_free_list_backend_ptr = n_the_free_list_backend_ptr;
		total_num_nodes = n_total_num_nodes;
		
		the_list_backend.init( get_node_array(),
			the_free_list_backend_ptr, get_total_num_nodes(),
			sizeof(type), sizeof(node<type>),
			extras_type::get_extras_fp_group() );
		
		//static auto specific_type_copy = []( type* a, type* b ) -> void 
		//	{ *a = *b; };
		//static auto specific_type_move = []( type* a, type* b ) -> void
		//	{ *a = std::move(*b); };
		//static auto specific_type_reset = []( type* a ) -> void
		//	{ *a = type(); };
		//static auto specific_type_less = []( type* a, type* b ) -> u32
		//	{ return (*a) < (*b); };
		//
		//
		//asm_comment("the_list_backend.init()");
		//the_list_backend.init( get_node_array(),
		//	the_free_list_backend_ptr, get_total_num_nodes(),
		//	sizeof(type), sizeof(node<type>),
		//	
		//	reinterpret_cast<generic_void_2arg_fp>(&specific_type_copy),
		//	reinterpret_cast<generic_void_2arg_fp>(&specific_type_move),
		//	reinterpret_cast<generic_void_1arg_fp>(&specific_type_reset),
		//	reinterpret_cast<generic_u32_2arg_fp>(&specific_type_less), 
		//	
		//	extras_type::get_get_node_data_fp(),
		//	extras_type::get_get_index_pair_fp(),
		//	extras_type::get_conv_node_to_contents_fp() );
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
	
	inline node<type>* get_node_array()
	{
		return node_array;
	}
	inline const node<type>* get_node_array() const
	{
		return node_array;
	}
	
	inline sa_free_list_backend& get_the_free_list_backend()
	{
		return *the_free_list_backend_ptr;
	}
	inline const sa_free_list_backend& get_the_free_list_backend() const
	{
		return *the_free_list_backend_ptr;
	}
	
	inline u32 get_total_num_nodes() const
	{
		return total_num_nodes;
	}
	
	
	
	inline node<type>& get_node_at( s32 index )
	{
		return get_node_array()[index];
	}
	inline node<type>& front()
	{
		return get_node_at(get_front_index());
	}
	
	inline node<type>& get_next_node_after_index
		( s32 index )
	{
		return get_node_at(get_node_at(index)
			.next_index());
	}
	inline node<type>& get_prev_node_before_index
		( s32 index )
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
	
	//s32 push_front_old( const type& to_push )
	//{
	//	// If there's nothing in the list
	//	if ( get_front_index() == -1 )
	//	{
	//		get_front_index() = get_the_free_list_backend()
	//			.peek_top();
	//		get_the_free_list_backend().pop();
	//		
	//		front().data = to_push;
	//		
	//		// These two operations are for good measure, and they might
	//		// not actually be necessary.
	//		front().next_index() = -1;
	//		front().prev_index() = -1;
	//	}
	//	// If there's at least one element in the list
	//	else
	//	{
	//		s32 old_front_index = get_front_index();
	//		get_front_index() = get_the_free_list_backend()
	//			.peek_top();
	//		get_the_free_list_backend().pop();
	//		
	//		get_node_at(old_front_index).prev_index() 
	//			= get_front_index();
	//		
	//		front().data = to_push;
	//		front().next_index() = old_front_index;
	//		
	//		// This operation is for good measure, and it might not
	//		// actually be necessary.
	//		front().prev_index() = -1;
	//	}
	//	
	//	return get_front_index();
	//}
	
	
	
	//s32 push_front_old_2( const type& to_push ) __attribute__((noinline))
	//{
	//	s32& the_front_index = get_front_index();
	//	s32 old_front_index = the_front_index;
	//	
	//	sa_free_list_backend& the_free_list_backend 
	//		= get_the_free_list_backend();
	//	
	//	the_front_index = the_free_list_backend.peek_top();
	//	the_free_list_backend.pop();
	//	
	//	
	//	//asm_comment("Before get_node_at(the_front_index)");
	//	
	//	node<type>& the_front_node 
	//		= get_node_at(the_front_index);
	//	
	//	//asm_comment("After get_node_at(the_front_index)");
	//	
	//	
	//	s32 new_next_index = -1;
	//	
	//	// If there's nothing in the list
	//	//if ( the_front_index < 0 )
	//	//if ( old_front_index < 0 )
	//	//{
	//	//	
	//	//}
	//	//// If there's at least one element in the list
	//	//else
	//	if ( old_front_index >= 0 )
	//	{
	//		new_next_index = old_front_index;
	//		
	//		get_node_at(old_front_index).prev_index()
	//			= the_front_index;
	//	}
	//	
	//	
	//	the_front_node.data = to_push;
	//	the_front_node.next_index() = new_next_index;
	//	the_front_node.prev_index() = -1;
	//	
	//	return the_front_index;
	//}
	
	inline s32 push_front( const type& to_push )
	{
		return the_list_backend.push_front(&to_push);
	}
	inline s32 push_front( type&& to_push )
	{
		return the_list_backend.push_front( &to_push, true );
	}
	inline s32 push_back( const type& to_push )
	{
		return the_list_backend.push_back(&to_push);
	}
	inline s32 push_back( type&& to_push )
	{
		return the_list_backend.push_back( &to_push, true );
	}
	
	
	inline s32 pop_front_basic()
	{
		return the_list_backend.pop_front_basic();
	}
	inline s32 pop_back_basic()
	{
		return the_list_backend.pop_back_basic();
	}
	
	//s32 insert_before_old( s32 index, const type& to_insert )
	//{
	//	s32 old_prev_index = get_node_at(index)
	//		.prev_index();
	//	//s32 old_next_index = get_node_at(index)
	//	//	.next_index();
	//	
	//	// If index == front_index
	//	//if ( old_prev_index == -1 )
	//	if ( index == get_front_index() )
	//	{
	//		return push_front(to_insert);
	//	}
	//	else
	//	{
	//		//s32 new_index = get_the_free_list_backend().pop();
	//		s32 new_index = get_the_free_list_backend().peek_top();
	//		get_the_free_list_backend().pop();
	//		
	//		get_node_at(old_prev_index).next_index()
	//			= new_index;
	//		
	//		get_node_at(new_index).data = to_insert;
	//		get_node_at(new_index).prev_index() 
	//			= old_prev_index;
	//		get_node_at(new_index).next_index()
	//			= index;
	//		
	//		get_node_at(index).prev_index() 
	//			= new_index;
	//		
	//		return new_index;
	//	}
	//	
	//	//return index;
	//	//return new_index;
	//}
	
	//s32 insert_before_old_2( s32 index, const type& to_insert )
	//	__attribute__((noinline))
	//{
	//	//s32 old_prev_index = get_node_at(index)
	//	//	.prev_index();
	//	////s32 old_next_index = get_node_at(index)
	//	////	.next_index()
	//	
	//	// If index == front_index
	//	//if ( old_prev_index == -1 )
	//	if ( index == get_front_index() )
	//	{
	//		return push_front(to_insert);
	//	}
	//	else
	//	{
	//		node<type>& node_at_index 
	//			= get_node_at(index);
	//		
	//		const s32 old_prev_index 
	//			= node_at_index.prev_index();
	//		
	//		const s32 new_index = get_the_free_list_backend()
	//			.peek_top();
	//		get_the_free_list_backend().pop();
	//		
	//		
	//		node<type>& node_at_new_index
	//			= get_node_at(new_index);
	//		
	//		
	//		get_node_at(old_prev_index).next_index()
	//			= new_index;
	//		
	//		node_at_new_index.data = to_insert;
	//		node_at_new_index.next_index() = index;
	//		node_at_new_index.prev_index() = old_prev_index;
	//		
	//		node_at_index.prev_index() = new_index;
	//		
	//		return new_index;
	//	}
	//	
	//	//return index;
	//	//return new_index;
	//}
	inline s32 insert_before( s32 index, const type& to_insert )
	{
		return the_list_backend.insert_before( index, &to_insert );
	}
	inline s32 insert_before( s32 index, type&& to_insert )
	{
		return the_list_backend.insert_before( index, &to_insert,
			true );
	}
	
	
	//s32 insert_after_old( s32 index, const type& to_insert )
	//{
	//	//s32 old_prev_index = get_node_at(index)
	//	//	.prev_index();
	//	s32 old_next_index = get_node_at(index)
	//		.next_index();
	//	
	//	//s32 new_index = get_the_free_list_backend().pop();
	//	s32 new_index = get_the_free_list_backend().peek_top();
	//	get_the_free_list_backend().pop();
	//	
	//	// Special code is used for inserting an element at the end of the
	//	// list.
	//	if ( old_next_index == -1 )
	//	{
	//		get_node_at(index).next_index() = new_index;
	//		
	//		get_node_at(new_index).data = to_insert;
	//		get_node_at(new_index).next_index() = -1;
	//		get_node_at(new_index).prev_index() = index;
	//	}
	//	else
	//	{
	//		get_node_at(old_next_index).prev_index()
	//			= new_index;
	//		
	//		get_node_at(index).next_index() = new_index;
	//		
	//		get_node_at(new_index).data = to_insert;
	//		get_node_at(new_index).next_index() 
	//			= old_next_index;
	//		get_node_at(new_index).prev_index() = index;
	//	}
	//	
	//	//return index;
	//	return new_index;
	//}
	
	//s32 insert_after_old_2( s32 index, const type& to_insert )
	//	__attribute__((noinline))
	//{
	//	////s32 old_prev_index = get_node_at(index)
	//	////	.prev_index();
	//	//s32 old_next_index = get_node_at(index)
	//	//	.next_index();
	//	node<type>& node_at_index = get_node_at(index);
	//	const s32 old_next_index = node_at_index
	//		.next_index();
	//	
	//	//s32 new_index = get_the_free_list_backend().pop();
	//	const s32 new_index = get_the_free_list_backend().peek_top();
	//	get_the_free_list_backend().pop();
	//	
	//	
	//	node_at_index.next_index() = new_index;
	//	
	//	node<type>& node_at_new_index 
	//		= get_node_at(new_index);
	//	
	//	s32 new_next_index = -1;
	//	
	//	// Special code is used for inserting an element at the end of the
	//	// list.
	//	//if ( old_next_index < 0 )
	//	//{
	//	//	
	//	//}
	//	//else
	//	if ( old_next_index >= 0 )
	//	{
	//		get_node_at(old_next_index).prev_index() 
	//			= new_index;
	//		new_next_index = old_next_index;
	//	}
	//	
	//	node_at_new_index.data = to_insert;
	//	node_at_new_index.next_index() = new_next_index;
	//	node_at_new_index.prev_index() = index;
	//	
	//	
	//	//return index;
	//	return new_index;
	//}
	inline s32 insert_after( s32 index, const type& to_insert )
	{
		return the_list_backend.insert_after( index, &to_insert );
	}
	inline s32 insert_after( s32 index, type&& to_insert )
	{
		return the_list_backend.insert_after( index, &to_insert, true );
	}
	
	inline void erase_at( s32 index )
	{
		the_list_backend.erase_at(index);
	}
	inline type&& unlink_at_with_dealloc( s32 index )
	{
		return std::move(*static_cast<type*>
			(the_list_backend.unlink_at_with_dealloc(index)));
	}
	
	
	s32 insertion_sort_old_2() 
		__attribute__((_text_hot_section,noinline))
		//__attribute__((noinline))
	{
		s32& the_front_index = get_front_index();
		
		// Don't do anything if this list has zero or one nodes.
		if ( the_front_index < 0 )
		{
			return the_front_index;
		}
		if ( get_node_at(the_front_index).next_index() < 0 )
		{
			return the_front_index;
		}
		
		//s32 temp_front_index = -1;
		//list_backend<type> sorted_list( &temp_front_index, 
		//	node_array, the_free_list_backend_ptr, 
		//	total_num_nodes );
		externally_allocated_list<type> sorted_list( node_array, 
			the_free_list_backend_ptr, get_total_num_nodes() );
		
		s32& temp_front_index = sorted_list.get_front_index();
		
		s32 curr_index = temp_front_index;
		
		for ( s32 i=the_front_index;
			i!=-1;  )
			//i=get_node_at(i).next_index() )
		{
			
			//get_the_free_list_backend().debug_prs32();
			
			s32 index_low = i;
			
			node<type>* node_at_j;
			
			// Find the lowest value at or after i.
			for ( s32 j=index_low;
				j!=-1; 
				j=node_at_j->next_index() )
			{
				node_at_j = &get_node_at(j);
				
				if ( node_at_j->data 
					< get_node_at(index_low).data )
				{
					index_low = j;
				}
			}
			
			node<type>& node_at_index_low = get_node_at(index_low);
			//const type data_to_move = node_at_index_low.data;
			//type* data_to_move = &node_at_index_low.data;
			
			if ( i == index_low )
			{
				i = node_at_index_low.next_index();
			}
			
			//erase_at(index_low);
			type&& data_to_move = unlink_at_with_dealloc(index_low);
			
			if ( temp_front_index < 0 )
			{
				sorted_list.push_front(std::move(data_to_move));
				curr_index = temp_front_index;
			}
			else
			{
				sorted_list.insert_after( curr_index, 
					std::move(data_to_move) );
				curr_index = sorted_list.get_node_at(curr_index)
					.next_index();
			}
			
		}
		
		
		the_front_index = temp_front_index;
		
		temp_front_index = -1;
		
		
		return the_front_index;
	}
	
	
	
	// This is a semi-optimized (though accidentally implemented
	// differently from what was intended) version of
	// insertion_sort_old_2()
	s32 insertion_sort_old_3() __attribute__((noinline))
	{
		s32& the_front_index = get_front_index();
		
		// Don't do anything if this list has zero or one nodes.
		if ( the_front_index < 0 )
		{
			return the_front_index;
		}
		if ( get_node_at(the_front_index).next_index() < 0 )
		{
			return the_front_index;
		}
		
		
		//s32 temp_front_index = -1;
		//sa_list_backend<type> sorted_list( &temp_front_index, 
		//	node_array, ptr_to_the_free_list_backend, 
		//	total_num_nodes );
		externally_allocated_list<type> sorted_list( node_array, 
			the_free_list_backend_ptr, get_total_num_nodes() );
		
		s32& temp_front_index = sorted_list.get_front_index();
		
		
		static constexpr u32 prev_index_low_arr_size = 20;
		s32 prev_index_low_arr[prev_index_low_arr_size];
		
		for ( s32 i=prev_index_low_arr_size-1; i>=0; --i )
		{
			prev_index_low_arr[i] = 0;
		}
		
		
		s32 curr_index = temp_front_index;
		
		for ( s32 i=the_front_index;
			i!=-1; )
			//i=get_node_at(i).next_index() )
		{
			u32 num_extra_low_indices = 0;
			
			
			s32 index_low = i;
			
			node<type>* node_at_j;
			
			type* data_at_index_low = &get_node_at(index_low).data;
			
			// Find the lowest value at or after i.
			for ( s32 j=index_low;
				j!=-1; 
				j=node_at_j->next_index() )
			{
				node_at_j = &get_node_at(j);
				
				if ( node_at_j->data 
					< *data_at_index_low )
				{
					if ( num_extra_low_indices + 1 
						< prev_index_low_arr_size )
					{
						prev_index_low_arr[num_extra_low_indices++]
							= index_low;
					}
					
					index_low = j;
					
					//data_at_index_low = &get_node_at(index_low).the
					data_at_index_low = &node_at_j->data;
				}
			}
			
			node<type>& node_at_index_low = get_node_at(index_low);
			//const type data_to_move = node_at_index_low.data;
			//type&& data_to_move = node_at_index_low.data
			
			if ( i == index_low )
			{
				i = node_at_index_low.next_index();
			}
			
			//erase_at(index_low);
			type&& data_to_move = unlink_at_with_dealloc(index_low);
			
			if ( temp_front_index < 0 )
			{
				sorted_list.push_front(std::move(data_to_move));
				curr_index = temp_front_index;
			}
			else
			{
				sorted_list.insert_after( curr_index, 
					std::move(data_to_move) );
				curr_index = sorted_list.get_node_at(curr_index)
					.next_index();
			}
			
			
			for ( u32 j=0; j<num_extra_low_indices; ++j )
			{
				s32& curr_prev_index_low = prev_index_low_arr[j];
				
				node<type>& node_at_curr_prev_index_low 
					= get_node_at(curr_prev_index_low);
				
				if ( i == curr_prev_index_low )
				{
					i = node_at_curr_prev_index_low.next_index();
				}
				
				type&& curr_data_to_move = unlink_at_with_dealloc
					(curr_prev_index_low);
				
				//if ( temp_front_index < 0 )
				//{
				//	sorted_list.push_front(std::move(data_to_move));
				//	curr_index = temp_front_index;
				//}
				//else
				{
					sorted_list.insert_after( curr_index, 
						std::move(curr_data_to_move) );
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
	inline void internal_func_subarr_merge_2( type* left_subarr,
		const size_t left_subarr_size, type* right_subarr, 
		const size_t right_subarr_size, type* out_subarr )
		__attribute__((always_inline))
	{
		const size_t out_subarr_size = left_subarr_size 
			+ right_subarr_size;
		
		size_t i = 0, j = 0;
		
		for ( size_t k=0; k<out_subarr_size; ++k )
		{
			if ( i >= left_subarr_size )
			{
				out_subarr[k] = right_subarr[j];
				++j;
			}
			else if ( j >= right_subarr_size )
			{
				out_subarr[k] = left_subarr[i];
				++i;
			}
			else // if ( i < left_subarr_size && j < right_subarr_size )
			{
				if ( left_subarr[i] < right_subarr[j] )
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
		
		
		dyn_arr<type> arr_a(real_num_nodes), work_arr(real_num_nodes);
		
		
		{
		
		size_t temp = 0;
		while ( the_front_index >= 0 )
		{
			arr_a[temp++] = std::move(get_node_array()[the_front_index]
				.data);
			
			pop_front_basic();
		}
		
		}
		
		//static constexpr size_t last_subarr_size = 20;
		static constexpr size_t last_subarr_size = 1;
		
		
		if ( last_subarr_size > 1 )
		{
			asm_comment("last_subarr_size > 1; before");
			
			size_t subarr_offset, subarr_size;
			
			// This is an insertion sort of PORTIONS of arr_a.
			for ( subarr_offset=0;
				subarr_offset<real_num_nodes;
				subarr_offset+=subarr_size )
			{
				subarr_size = last_subarr_size;
				
				if ( subarr_offset + subarr_size >= real_num_nodes )
				{
					subarr_size = real_num_nodes - subarr_offset;
				}
				
				extras_type::subarr_insertion_sort( arr_a, subarr_offset,
					subarr_size );
			}
			
			asm_comment("last_subarr_size > 1; after");
		}
		
		
		
		size_t left_subarr_offset = 0, right_subarr_offset = 0;
		type * left_subarr, * right_subarr;
		size_t left_subarr_size = 0, right_subarr_size = 0;
		
		
		static constexpr bool do_swap = true;
		
		bool main_arr_is_arr_a = false;
		prev_curr_pair<dyn_arr<type>*> main_arr_pc_pair,
			secondary_arr_pc_pair;
		
		//if (!do_swap)
		{
			main_arr_pc_pair.prev = main_arr_pc_pair.curr = &arr_a;
			secondary_arr_pc_pair.prev = secondary_arr_pc_pair.curr 
				= &work_arr;
		}
		
		// Avoid recursion
		//for ( size_t subarr_size=first_subarr_size;
		//	subarr_size<real_num_nodes;
		//	subarr_size*=2 )
		for ( size_t subarr_size=real_num_nodes;
			subarr_size>=last_subarr_size;
			subarr_size/=2 )
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
			
			auto get_merge_args = [&]( dyn_arr<type>& specific_arr, 
				size_t n_left_subarr_offset ) -> void
			{
				right_subarr_offset = 0;
				right_subarr = NULL;
				right_subarr_size = 0;
				
				
				left_subarr_offset = n_left_subarr_offset;
				left_subarr = &(specific_arr[left_subarr_offset]);
				left_subarr_size = subarr_size;
				
				
				if ( left_subarr_offset + left_subarr_size 
					>= real_num_nodes )
				{
					left_subarr_size = real_num_nodes - left_subarr_offset;
					return;
				}
				
				
				right_subarr_offset = left_subarr_offset 
					+ left_subarr_size;
				right_subarr = &(specific_arr[right_subarr_offset]);
				right_subarr_size = subarr_size;
				
				if ( right_subarr_offset + right_subarr_size 
					>= real_num_nodes )
				{
					right_subarr_size = real_num_nodes 
						- right_subarr_offset;
				}
				
				
			};
			
			get_merge_args( *main_arr_pc_pair.curr, 0 );
			
			for ( size_t i=0; i<real_num_nodes; i+=subarr_size*2 )
			{
				internal_func_subarr_merge_2( left_subarr, 
					left_subarr_size, right_subarr, right_subarr_size,
					&((*secondary_arr_pc_pair.curr)[i]) );
				
				//if ( i + ( subarr_size * 2 ) < real_num_nodes )
				{
					get_merge_args( *main_arr_pc_pair.curr, 
						i + ( subarr_size * 2 ) );
				}
			}
			
			if (!do_swap)
			{
				for ( s32 i=real_num_nodes-1; i>=0; --i )
				{
					arr_a[i] = work_arr[i];
				}
			}
			
		}
		
		//if ( last_subarr_size > 1 )
		//{
		//	extras_type::subarr_insertion_sort( (*main_arr_pc_pair.prev), 
		//		0, real_num_nodes );
		//}
		
		for ( s32 i=real_num_nodes-1; i>=0; --i )
		{
			//s32 curr_index = (*main_arr_pc_pair.prev)[i]
			push_front((*main_arr_pc_pair.prev)[i]);
		}
		
		//if ( last_subarr_size > 1 )
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



// This is a template class for a statically allocated array of modifiable
// doubly-linked lists.  "sa" is short for "statically allocated".
template< typename type, u32 total_num_nodes, u32 num_lists >
class sa_array_of_lists
{
public:		// variables
	//array< externally_allocated_sa_list< type, total_num_nodes >, 
	//	num_lists > the_array;
	//array< node<type>, total_num_nodes > node_array;
	
	externally_allocated_list<type> ea_list_array[num_lists];
	node<type> node_array[total_num_nodes];
	
	sa_free_list<total_num_nodes> the_free_list;
	
public:		// functions
	
	inline sa_array_of_lists()
	{
		//for ( auto& the_list : easa_list_array )
		//{
		//	the_list.set_node_array(node_array.data());
		//	the_list.set_ptr_to_the_free_list(&the_free_list);
		//	the_list.init_the_list_backend();
		//}
		
		//for ( s32 i=(s32)get_node_array_size()-1; i>=0; --i )
		//{
		//	node_array[i] = node<type>();
		//}
		
		for ( s32 i=(s32)get_the_array_size()-1; i>=0; --i )
		{
			//the_array[i].set_node_array(node_array);
			//the_array[i].set_ptr_to_the_free_list(&the_free_list);
			//the_array[i].init_the_list_backend();
			ea_list_array[i].init( node_array,
				&the_free_list.the_sa_free_list_backend, 
				get_total_num_nodes() );
		}
		
		
	}
	
	constexpr inline u32 get_the_array_size() const
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

} // end of namespace sa_list_stuff


#endif		// sa_list_class_stuff_hpp
