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

#include "../gba_specific_stuff/asm_funcs.hpp"

#include "generic_funcptr_stuff.hpp"



// A non-template class intended to be used by the sa_list_backend class.
class sa_list_node_contents
{
public:		// constants
	static constexpr size_t 
		index_for_next_node_index = vec2_s16::the_index_for_x,
		index_for_prev_node_index = vec2_s16::the_index_for_y;
	
public:		// variables
	void* ptr_to_the_data;
	
	vec2_s16* ptr_to_node_index_pair;
	
public:		// functions
	// This is safe so long as the_data is the first member variable of the
	// sa_list_node class.
	inline void* get_sa_list_node_as_void_ptr()
	{
		return ptr_to_the_data;
	}
	
	template< typename type >
	inline type* cast_ptr_to_the_data()
	{
		return static_cast<type*>(ptr_to_the_data);
	}
	
	inline s16& next_node_index()
	{
		return (*ptr_to_node_index_pair)[index_for_next_node_index];
	}
	inline s16& prev_node_index()
	{
		return (*ptr_to_node_index_pair)[index_for_prev_node_index];
	}
	
} __attribute__((_align4));


template< typename type >
class sa_list_node
{
public:		// constants
	static constexpr size_t index_for_next_node_index 
		= sa_list_node_contents::index_for_next_node_index,
		index_for_prev_node_index 
		= sa_list_node_contents::index_for_prev_node_index;
	
public:		// variables
	type the_data __attribute__((_align4)) = type();
	//vec2_s32 node_index_pair = { -1, -1 };
	vec2_s16 node_index_pair = { -1, -1 };
	
public:		// functions
	inline sa_list_node()
	{
	}
	
	//inline sa_list_node()
	//{
	//	the_data = type();
	//	next_node_index = -1;
	//	prev_node_index = -1;
	//}
	
	template< typename type_in_vec2 >
	inline sa_list_node( const type& data_to_copy, 
		vec2<type_in_vec2> s_node_index_pair ) : the_data(data_to_copy)
	{
		next_node_index() = get_next_node_index_from_vec2
			(s_node_index_pair);
	}
	
	inline s16& next_node_index()
	{
		return node_index_pair[index_for_next_node_index];
	}
	inline s16& prev_node_index()
	{
		return node_index_pair[index_for_prev_node_index];
	}
	
	
protected:		// functions
	template< typename type_in_vec2 >
	static inline s16 get_next_node_index_from_vec2
		( const vec2<type_in_vec2>& the_vec2 )
	{
		return static_cast<s16>(the_vec2[index_for_next_node_index]);
	}
	template< typename type_in_vec2 >
	static inline s16 get_prev_node_index_from_vec2
		( const vec2<type_in_vec2>& the_vec2 )
	{
		return static_cast<s16>(the_vec2[index_for_prev_node_index]);
	}
	
	
} __attribute__((_align4));




// A group of functions to use as function pointers in the sa_list_backend
// class.
template< typename type >
class sa_list_extras
{
protected:		// functions
	static void specific_type_copy( type* instance_a, 
		type* instance_b )
	{
		*instance_a = *instance_b;
	}
	static void specific_type_move( type* instance_a,
		type* instance_b )
	{
		*instance_a = std::move(*instance_b);
	}
	static void specific_type_reset( type* to_reset )
	{
		*to_reset = type();
	}
	static u32 specific_type_less( type* instance_a, type* instance_b )
	{
		return ( (*instance_a) < (*instance_b) );
	}
	
	static void* get_sa_list_node_data( sa_list_node<type>* to_get_from )
	{
		return &to_get_from->the_data;
	}
	static vec2_s16* get_sa_list_node_index_pair
		( sa_list_node<type>* to_get_from )
	{
		return &to_get_from->node_index_pair;
	}
	static void conv_node_to_contents( sa_list_node_contents* ret,
		sa_list_node<type>* to_convert )
	{
		ret->ptr_to_the_data = &to_convert->the_data;
		ret->ptr_to_node_index_pair = &to_convert->node_index_pair;
	}
	
	
public:		// functions
	// This is the first time I've used an "auto" return type much, but it
	// makes plenty of sense for this case.
	static inline auto get_the_specific_type_copy_fp()
	{
		return get_generic_void_2arg_fp(&specific_type_copy);
	}
	static inline auto get_the_specific_type_move_fp()
	{
		return get_generic_void_2arg_fp(&specific_type_move);
	}
	static inline auto get_the_specific_type_reset_fp()
	{
		return get_generic_void_1arg_fp(&specific_type_reset);
	}
	static inline auto get_the_specific_type_less_fp()
	{
		return get_generic_u32_2arg_fp(&specific_type_less);
	}
	
	static inline auto get_the_get_node_data_fp()
	{
		return get_generic_void_ptr_1arg_fp(&get_sa_list_node_data);
	}
	static inline auto get_the_get_node_index_pair_fp()
	{
		return get_generic_vec2_s16_ptr_1arg_fp
			(&get_sa_list_node_index_pair);
	}
	static inline auto get_the_conv_node_to_contents_fp()
	{
		return get_generic_void_2arg_fp(&conv_node_to_contents);
	}
	
} __attribute__((_align4));


// This class exists because C++ templates CAN generate too much code.  Oh,
// and I can put code in IWRAM this way!
class sa_list_backend
{
protected:		// types
	
protected:		// variables
	s32 front_node_index = -1;
	
	// the_node_array as a void pointer.
	void* the_node_array = 0;
	
	sa_free_list_backend* ptr_to_the_free_list_backend = 0;
	
	u32 total_num_nodes = 0;
	
	// sa_list_node stuff
	u32 specific_type_size = 0, 
		whole_node_size = 0;
	
	
	// Function pointers used by various functions
	
	// Pointers to the copying and moving functions (created using the
	// assignment operators of the specific type)
	generic_void_2arg_fp specific_type_copy_fp = 0, 
		specific_type_move_fp = 0;
	// A pointer to the 
	generic_void_1arg_fp specific_type_reset_fp = 0;
	// A pointer to the less function (created by using the less operator
	// of the specific type)
	generic_u32_2arg_fp specific_type_less_fp = 0;
	
	generic_void_ptr_1arg_fp get_node_data_fp = 0;
	generic_vec2_s16_ptr_1arg_fp get_node_index_pair_fp = 0;
	
	generic_void_2arg_fp conv_node_to_contents_fp = 0;
	
	
	template< typename type > friend class externally_allocated_sa_list;
	
protected:		// functions
	inline sa_list_backend()
	{
	}
	// Dang, I had no idea it'd be this nice to get types automatically
	// this way.
	inline sa_list_backend( void* s_the_node_array, 
		sa_free_list_backend* s_ptr_to_the_free_list_backend,
		u32 s_total_num_nodes, u32 s_specific_type_size,
		u32 s_whole_node_size, 
		
		decltype(specific_type_copy_fp) s_specific_type_copy_fp, 
		decltype(specific_type_move_fp) s_specific_type_move_fp,
		decltype(specific_type_reset_fp) s_specific_type_reset_fp, 
		decltype(specific_type_less_fp) s_specific_type_less_fp, 
		
		decltype(get_node_data_fp) s_get_node_data_fp, 
		decltype(get_node_index_pair_fp) s_get_node_index_pair_fp,
		decltype(conv_node_to_contents_fp) s_conv_node_to_contents_fp )
	{
		init( s_the_node_array, s_ptr_to_the_free_list_backend,
			s_total_num_nodes, s_specific_type_size, s_whole_node_size,
			s_specific_type_copy_fp, 
			s_specific_type_move_fp,
			s_specific_type_reset_fp,
			s_specific_type_less_fp,
			
			s_get_node_data_fp, 
			s_get_node_index_pair_fp,
			s_conv_node_to_contents_fp );
	}
	
	void init( void* n_the_node_array, 
		sa_free_list_backend* n_ptr_to_the_free_list_backend,
		u32 n_total_num_nodes, u32 n_specific_type_size,
		u32 n_whole_node_size, 
		
		decltype(specific_type_copy_fp) n_specific_type_copy_fp, 
		decltype(specific_type_move_fp) n_specific_type_move_fp, 
		decltype(specific_type_reset_fp) n_specific_type_reset_fp,
		decltype(specific_type_less_fp) n_specific_type_less_fp, 
		
		decltype(get_node_data_fp) n_get_node_data_fp, 
		decltype(get_node_index_pair_fp) n_get_node_index_pair_fp,
		decltype(conv_node_to_contents_fp) n_conv_node_to_contents_fp );
	
	
	inline s32& get_front_node_index()
	{
		return front_node_index;
	}
	inline const s32 get_front_node_index() const
	{
		return front_node_index;
	}
	
	inline void* get_the_node_array()
	{
		return the_node_array;
	}
	inline const void* get_the_node_array() const
	{
		return the_node_array;
	}
	
	inline sa_free_list_backend* get_ptr_to_the_free_list_backend()
	{
		return ptr_to_the_free_list_backend;
	}
	inline const sa_free_list_backend* get_ptr_to_the_free_list_backend()
		const
	{
		return ptr_to_the_free_list_backend;
	}
	inline sa_free_list_backend& get_the_free_list_backend()
	{
		return *get_ptr_to_the_free_list_backend();
	}
	inline const sa_free_list_backend& get_the_free_list_backend() const
	{
		return *get_ptr_to_the_free_list_backend();
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
	
	
	inline uintptr_t get_addr_of_node_at( s32 node_index ) const
	{
		return reinterpret_cast<uintptr_t>(the_node_array)
			+ arr_byte_index_macro( whole_node_size, node_index );
	}
	
	
	
	// These three functions are intended to be used sparingly.  They make
	// most sense to use when their result is the ONLY part of a node that
	// is relevant, and in that case it is still best to ONLY CALL them
	// ONCE.
	inline void* get_node_data_at_node_index( s32 node_index )
	{
		return get_node_data_at(get_addr_of_node_at(node_index));
	}
	inline vec2_s16* get_node_index_pair_at_node_index( s32 node_index )
	{
		return get_node_index_pair_at(get_addr_of_node_at(node_index));
	}
	inline s16& get_next_node_index_at_node_index( s32 node_index )
	{
		return get_next_node_index_at(get_addr_of_node_at
			(node_index));
	}
	inline s16& get_prev_node_index_at_node_index( s32 node_index )
	{
		return get_prev_node_index_at(get_addr_of_node_at
			(node_index));
	}
	
	
	inline void* get_node_data_at( uintptr_t addr )
	{
		return (*get_node_data_fp)(reinterpret_cast<void*>(addr));
	}
	inline vec2_s16* get_node_index_pair_at( uintptr_t addr )
	{
		return (*get_node_index_pair_fp)
			(reinterpret_cast<void*>(addr));
	}
	inline s16& get_next_node_index_at( uintptr_t addr )
	{
		return ((*get_node_index_pair_at(addr))
			[sa_list_node_contents::index_for_next_node_index]);
	}
	inline s16& get_prev_node_index_at( uintptr_t addr )
	{
		return ((*get_node_index_pair_at(addr))
			[sa_list_node_contents::index_for_prev_node_index]);
	}
	
	inline sa_list_node_contents get_node_contents_at( s32 node_index )
	{
		uintptr_t addr_of_node = get_addr_of_node_at(node_index);
		
		//sa_list_node_contents ret = { get_node_data_at(addr_of_node),
		//	get_node_index_pair_at(addr_of_node) };
		
		sa_list_node_contents ret;
		
		(*conv_node_to_contents_fp)( &ret, 
			reinterpret_cast<void*>(addr_of_node) );
		
		return ret;
	}
	
	
	// Make sure to call this with node DATA!
	inline void copy_node_data( void* dst_node_data, void* src_node_data )
	{
		(*specific_type_copy_fp)( dst_node_data,
			const_cast<void*>(src_node_data) );
	}
	inline void copy_node_data( void* dst_node_data, 
		const void* src_node_data )
	{
		(*specific_type_copy_fp)( dst_node_data, 
			const_cast<void*>(src_node_data) );
	}
	inline void move_node_data( void* dst_node_data, void* src_node_data )
	{
		(*specific_type_move_fp)( dst_node_data,
			const_cast<void*>(src_node_data) );
	}
	inline void move_node_data( void* dst_node_data, 
		const void* src_node_data )
	{
		(*specific_type_move_fp)( dst_node_data,
			const_cast<void*>(src_node_data) );
	}
	
	
	//inline void assign_to_whole_node_via_copy
	//	( sa_list_node_contents& dst_node_contents, const void* n_the_data,
	//	const vec2_s16& n_node_index_pair )
	//{
	//	copy_node_data( dst_node_contents.ptr_to_the_data, n_the_data );
	//	copy_vec2_s16_via_ptr( *dst_node_contents.ptr_to_node_index_pair,
	//		n_node_index_pair );
	//}
	//inline void assign_to_whole_node_via_move
	//	( sa_list_node_contents& dst_node_contents,
	//	const void* n_the_data, const vec2_s16& n_node_index_pair )
	//{
	//	move_node_data( dst_node_contents.ptr_to_the_data, n_the_data );
	//	copy_vec2_s16_via_ptr( *dst_node_contents.ptr_to_node_index_pair,
	//		n_node_index_pair );
	//}
	inline void assign_to_whole_node
		( sa_list_node_contents& dst_node_contents, const void* n_the_data,
		const vec2_s16& n_node_index_pair, u32 can_move_value )
	{
		if (!can_move_value)
		{
			copy_node_data( dst_node_contents.ptr_to_the_data, 
				n_the_data );
		}
		else //if (can_move_value)
		{
			move_node_data( dst_node_contents.ptr_to_the_data, 
				n_the_data );
		}
		
		copy_vec2_s16_via_ptr( *dst_node_contents.ptr_to_node_index_pair,
			n_node_index_pair );
	}
	
	
	// Make sure to call this with node DATA!
	inline u32 call_specific_type_less_func( void* node_a_data, 
		void* node_b_data )
	{
		return (*specific_type_less_fp)( const_cast<void*>(node_a_data), 
			const_cast<void*>(node_b_data) );
	}
	inline u32 call_specific_type_less_func( const void* node_a_data, 
		void* node_b_data )
	{
		return (*specific_type_less_fp)( const_cast<void*>(node_a_data), 
			const_cast<void*>(node_b_data) );
	}
	inline u32 call_specific_type_less_func( void* node_a_data, 
		const void* node_b_data )
	{
		return (*specific_type_less_fp)( const_cast<void*>(node_a_data), 
			const_cast<void*>(node_b_data) );
	}
	inline u32 call_specific_type_less_func( const void* node_a_data, 
		const void* node_b_data )
	{
		return (*specific_type_less_fp)( const_cast<void*>(node_a_data), 
			const_cast<void*>(node_b_data) );
	}
	
	s32 push_front( const void* to_push, u32 can_move_value=false ) 
		__attribute__((_iwram_code));
	s32 insert_before( s32 node_index, const void* to_insert,
		u32 can_move_value=false ) __attribute__((_iwram_code));
	s32 insert_after( s32 node_index, const void* to_insert, 
		u32 can_move_value=false ) __attribute__((_iwram_code));
	
	
	inline void erase_at( s32 node_index )
	{
		(*specific_type_reset_fp)(unlink_at(node_index));
	}
	void* unlink_at( s32 node_index ) __attribute__((_iwram_code));
	
	
	s32 merge_sort() __attribute__((_iwram_code));
	
	
} __attribute__((_align4));




template< typename type >
class externally_allocated_sa_list
{
protected:		// typedefs
	typedef sa_list_extras<type> extras_type;
	
//public:		// variables
protected:		// variables
	//s32* ptr_to_front_node_index;
	//s32 front_node_index;
	sa_list_node<type>* the_node_array = 0;
	sa_free_list_backend* ptr_to_the_free_list_backend = 0;
	u32 total_num_nodes = 0;
	
	sa_list_backend the_sa_list_backend;
	
public:		// functions
	inline externally_allocated_sa_list() : the_sa_list_backend()
	{
	}
	inline externally_allocated_sa_list
		( sa_list_node<type>* s_the_node_array, 
		sa_free_list_backend* s_ptr_to_the_free_list_backend,
		u32 s_total_num_nodes )
	{
		init( s_the_node_array, s_ptr_to_the_free_list_backend,
			s_total_num_nodes );
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
		
		the_sa_list_backend.init( get_the_node_array(),
			ptr_to_the_free_list_backend, get_total_num_nodes(),
			sizeof(type), sizeof(sa_list_node<type>),
			extras_type::get_the_specific_type_copy_fp(),
			extras_type::get_the_specific_type_move_fp(),
			extras_type::get_the_specific_type_reset_fp(),
			extras_type::get_the_specific_type_less_fp(), 
			
			extras_type::get_the_get_node_data_fp(),
			extras_type::get_the_get_node_index_pair_fp(),
			extras_type::get_the_conv_node_to_contents_fp() );
	}
	
	inline s32& get_front_node_index()
	{
		return the_sa_list_backend.get_front_node_index();
	}
	inline const s32 get_front_node_index() const
	{
		return the_sa_list_backend.get_front_node_index();
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
			.next_node_index());
	}
	inline sa_list_node<type>& get_prev_node_before_node_index
		( s32 node_index )
	{
		return get_node_at(get_node_at(node_index)
			.prev_node_index());
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
	
	//s32 push_front_old( const type& to_push )
	//{
	//	// If there's nothing in the list
	//	if ( get_front_node_index() == -1 )
	//	{
	//		get_front_node_index() = get_the_free_list_backend()
	//			.peek_top();
	//		get_the_free_list_backend().pop();
	//		
	//		front().the_data = to_push;
	//		
	//		// These two operations are for good measure, and they might
	//		// not actually be necessary.
	//		front().next_node_index() = -1;
	//		front().prev_node_index() = -1;
	//	}
	//	// If there's at least one element in the list
	//	else
	//	{
	//		s32 old_front_node_index = get_front_node_index();
	//		get_front_node_index() = get_the_free_list_backend()
	//			.peek_top();
	//		get_the_free_list_backend().pop();
	//		
	//		get_node_at(old_front_node_index).prev_node_index() 
	//			= get_front_node_index();
	//		
	//		front().the_data = to_push;
	//		front().next_node_index() = old_front_node_index;
	//		
	//		// This operation is for good measure, and it might not
	//		// actually be necessary.
	//		front().prev_node_index() = -1;
	//	}
	//	
	//	return get_front_node_index();
	//}
	
	
	
	//s32 push_front_old_2( const type& to_push ) __attribute__((noinline))
	//{
	//	s32& the_front_node_index = get_front_node_index();
	//	s32 old_front_node_index = the_front_node_index;
	//	
	//	sa_free_list_backend& the_free_list_backend 
	//		= get_the_free_list_backend();
	//	
	//	the_front_node_index = the_free_list_backend.peek_top();
	//	the_free_list_backend.pop();
	//	
	//	
	//	//asm_comment("Before get_node_at(the_front_node_index)");
	//	
	//	sa_list_node<type>& the_front_node 
	//		= get_node_at(the_front_node_index);
	//	
	//	//asm_comment("After get_node_at(the_front_node_index)");
	//	
	//	
	//	s32 new_next_node_index = -1;
	//	
	//	// If there's nothing in the list
	//	//if ( the_front_node_index < 0 )
	//	//if ( old_front_node_index < 0 )
	//	//{
	//	//	
	//	//}
	//	//// If there's at least one element in the list
	//	//else
	//	if ( old_front_node_index >= 0 )
	//	{
	//		new_next_node_index = old_front_node_index;
	//		
	//		get_node_at(old_front_node_index).prev_node_index()
	//			= the_front_node_index;
	//	}
	//	
	//	
	//	the_front_node.the_data = to_push;
	//	the_front_node.next_node_index() = new_next_node_index;
	//	the_front_node.prev_node_index() = -1;
	//	
	//	return the_front_node_index;
	//}
	
	inline s32 push_front( const type& to_push )
	{
		return the_sa_list_backend.push_front(&to_push);
	}
	inline s32 push_front( type&& to_push )
	{
		return the_sa_list_backend.push_front( &to_push, true );
	}
	
	inline s32 pop_front_basic()
	{
		s32& the_front_node_index = get_front_node_index();
		
		erase_at(the_front_node_index);
		
		return the_front_node_index;
	}
	
	//s32 insert_before_old( s32 node_index, const type& to_insert )
	//{
	//	s32 old_prev_node_index = get_node_at(node_index)
	//		.prev_node_index();
	//	//s32 old_next_node_index = get_node_at(node_index)
	//	//	.next_node_index();
	//	
	//	// If node_index == front_node_index
	//	//if ( old_prev_node_index == -1 )
	//	if ( node_index == get_front_node_index() )
	//	{
	//		return push_front(to_insert);
	//	}
	//	else
	//	{
	//		//s32 new_node_index = get_the_free_list_backend().pop();
	//		s32 new_node_index = get_the_free_list_backend().peek_top();
	//		get_the_free_list_backend().pop();
	//		
	//		get_node_at(old_prev_node_index).next_node_index()
	//			= new_node_index;
	//		
	//		get_node_at(new_node_index).the_data = to_insert;
	//		get_node_at(new_node_index).prev_node_index() 
	//			= old_prev_node_index;
	//		get_node_at(new_node_index).next_node_index()
	//			= node_index;
	//		
	//		get_node_at(node_index).prev_node_index() 
	//			= new_node_index;
	//		
	//		return new_node_index;
	//	}
	//	
	//	//return node_index;
	//	//return new_node_index;
	//}
	
	//s32 insert_before_old_2( s32 node_index, const type& to_insert )
	//	__attribute__((noinline))
	//{
	//	//s32 old_prev_node_index = get_node_at(node_index)
	//	//	.prev_node_index();
	//	////s32 old_next_node_index = get_node_at(node_index)
	//	////	.next_node_index()
	//	
	//	// If node_index == front_node_index
	//	//if ( old_prev_node_index == -1 )
	//	if ( node_index == get_front_node_index() )
	//	{
	//		return push_front(to_insert);
	//	}
	//	else
	//	{
	//		sa_list_node<type>& node_at_node_index 
	//			= get_node_at(node_index);
	//		
	//		const s32 old_prev_node_index 
	//			= node_at_node_index.prev_node_index();
	//		
	//		const s32 new_node_index = get_the_free_list_backend()
	//			.peek_top();
	//		get_the_free_list_backend().pop();
	//		
	//		
	//		sa_list_node<type>& node_at_new_node_index
	//			= get_node_at(new_node_index);
	//		
	//		
	//		get_node_at(old_prev_node_index).next_node_index()
	//			= new_node_index;
	//		
	//		node_at_new_node_index.the_data = to_insert;
	//		node_at_new_node_index.prev_node_index() = old_prev_node_index;
	//		node_at_new_node_index.next_node_index() = node_index;
	//		
	//		node_at_node_index.prev_node_index() = new_node_index;
	//		
	//		return new_node_index;
	//	}
	//	
	//	//return node_index;
	//	//return new_node_index;
	//}
	inline s32 insert_before( s32 node_index, const type& to_insert )
	{
		return the_sa_list_backend.insert_before( node_index, &to_insert );
	}
	inline s32 insert_before( s32 node_index, type&& to_insert )
	{
		return the_sa_list_backend.insert_before( node_index, &to_insert,
			true );
	}
	
	
	//s32 insert_after_old( s32 node_index, const type& to_insert )
	//{
	//	//s32 old_prev_node_index = get_node_at(node_index)
	//	//	.prev_node_index();
	//	s32 old_next_node_index = get_node_at(node_index)
	//		.next_node_index();
	//	
	//	//s32 new_node_index = get_the_free_list_backend().pop();
	//	s32 new_node_index = get_the_free_list_backend().peek_top();
	//	get_the_free_list_backend().pop();
	//	
	//	// Special code is used for inserting an element at the end of the
	//	// list.
	//	if ( old_next_node_index == -1 )
	//	{
	//		get_node_at(node_index).next_node_index() = new_node_index;
	//		
	//		get_node_at(new_node_index).the_data = to_insert;
	//		get_node_at(new_node_index).next_node_index() = -1;
	//		get_node_at(new_node_index).prev_node_index() = node_index;
	//	}
	//	else
	//	{
	//		get_node_at(old_next_node_index).prev_node_index()
	//			= new_node_index;
	//		
	//		get_node_at(node_index).next_node_index() = new_node_index;
	//		
	//		get_node_at(new_node_index).the_data = to_insert;
	//		get_node_at(new_node_index).next_node_index() 
	//			= old_next_node_index;
	//		get_node_at(new_node_index).prev_node_index() = node_index;
	//	}
	//	
	//	//return node_index;
	//	return new_node_index;
	//}
	
	//s32 insert_after_old_2( s32 node_index, const type& to_insert )
	//	__attribute__((noinline))
	//{
	//	////s32 old_prev_node_index = get_node_at(node_index)
	//	////	.prev_node_index();
	//	//s32 old_next_node_index = get_node_at(node_index)
	//	//	.next_node_index();
	//	sa_list_node<type>& node_at_node_index = get_node_at(node_index);
	//	const s32 old_next_node_index = node_at_node_index
	//		.next_node_index();
	//	
	//	//s32 new_node_index = get_the_free_list_backend().pop();
	//	const s32 new_node_index = get_the_free_list_backend().peek_top();
	//	get_the_free_list_backend().pop();
	//	
	//	
	//	node_at_node_index.next_node_index() = new_node_index;
	//	
	//	sa_list_node<type>& node_at_new_node_index 
	//		= get_node_at(new_node_index);
	//	
	//	s32 new_next_node_index = -1;
	//	
	//	// Special code is used for inserting an element at the end of the
	//	// list.
	//	//if ( old_next_node_index < 0 )
	//	//{
	//	//	
	//	//}
	//	//else
	//	if ( old_next_node_index >= 0 )
	//	{
	//		get_node_at(old_next_node_index).prev_node_index() 
	//			= new_node_index;
	//		new_next_node_index = old_next_node_index;
	//	}
	//	
	//	node_at_new_node_index.the_data = to_insert;
	//	node_at_new_node_index.next_node_index() = new_next_node_index;
	//	node_at_new_node_index.prev_node_index() = node_index;
	//	
	//	
	//	//return node_index;
	//	return new_node_index;
	//}
	inline s32 insert_after( s32 node_index, const type& to_insert )
	{
		return the_sa_list_backend.insert_after( node_index, &to_insert );
	}
	inline s32 insert_after( s32 node_index, type&& to_insert )
	{
		return the_sa_list_backend.insert_after( node_index, &to_insert,
			true );
	}
	
	//void erase_at_old( s32 node_index )
	//{
	//	s32 old_prev_node_index = get_node_at(node_index)
	//		.prev_node_index(),
	//		old_next_node_index = get_node_at(node_index)
	//		.next_node_index();
	//	
	//	// Special code is used for erasing an element at the beginning of
	//	// the list.
	//	//if ( old_prev_node_index == -1 )
	//	if ( node_index == get_front_node_index() )
	//	{
	//		//s32 old_front_node_index = get_front_node_index();
	//		
	//		get_node_at(get_front_node_index()).the_data = type();
	//		get_node_at(get_front_node_index()).next_node_index() = -1;
	//		get_node_at(get_front_node_index()).prev_node_index() = -1;
	//		
	//		get_the_free_list_backend().push(get_front_node_index());
	//		
	//		get_front_node_index() = old_next_node_index;
	//		
	//		if ( old_next_node_index != -1 )
	//		{
	//			front().prev_node_index() = -1;
	//		}
	//	}
	//	else 
	//	{
	//		get_node_at(node_index).the_data = type();
	//		get_node_at(node_index).next_node_index() = -1;
	//		get_node_at(node_index).prev_node_index() = -1;
	//		get_the_free_list_backend().push(node_index);
	//		
	//		if ( old_next_node_index != -1 )
	//		{
	//			get_node_at(old_prev_node_index).next_node_index()
	//				= old_next_node_index;
	//			get_node_at(old_next_node_index).prev_node_index()
	//				= old_prev_node_index;
	//		}
	//		else
	//		{
	//			get_node_at(old_prev_node_index).next_node_index()
	//				= -1;
	//		}
	//	}
	//	
	//}
	
	//void erase_at_old_2( s32 node_index ) __attribute__((noinline))
	//{
	//	//s32 old_prev_node_index = get_node_at(node_index)
	//	//	.prev_node_index(),
	//	//	old_next_node_index = get_node_at(node_index)
	//	//	.next_node_index();
	//	
	//	sa_list_node<type>& node_at_node_index = get_node_at(node_index);
	//	
	//	const s32 old_prev_node_index = node_at_node_index
	//		.prev_node_index(),
	//		old_next_node_index = node_at_node_index.next_node_index();
	//	
	//	s32& the_front_node_index = get_front_node_index();
	//	const s32 old_front_node_index = the_front_node_index;
	//	
	//	//node_at_node_index.the_data = type();
	//	//node_at_node_index.next_node_index() = -1;
	//	//node_at_node_index.prev_node_index() = -1;
	//	node_at_node_index = sa_list_node<type>();
	//	
	//	get_the_free_list_backend().push(node_index);
	//	
	//	if ( node_index == old_front_node_index )
	//	{
	//		the_front_node_index = old_next_node_index;
	//		
	//		if ( old_next_node_index >= 0 )
	//		{
	//			//front().prev_node_index() = -1;
	//			get_node_at(the_front_node_index).prev_node_index() = -1;
	//		}
	//	}
	//	else
	//	{
	//		sa_list_node<type>& old_prev_node 
	//			= get_node_at(old_prev_node_index);
	//		
	//		if ( old_next_node_index >= 0 )
	//		{
	//			old_prev_node.next_node_index() = old_next_node_index;
	//			get_node_at(old_next_node_index).prev_node_index()
	//				= old_prev_node_index;
	//		}
	//		else
	//		{
	//			old_prev_node.next_node_index() = -1;
	//		}
	//	}
	//}
	inline void erase_at( s32 node_index )
	{
		the_sa_list_backend.erase_at(node_index);
	}
	inline type&& unlink_at( s32 node_index )
	{
		return std::move(*reinterpret_cast<type*>
			(the_sa_list_backend.unlink_at(node_index)));
	}
	
	
	//s32 insertion_sort_old()
	//{
	//	// Don't do anything if this list has zero or one nodes.
	//	if ( get_front_node_index() == -1 )
	//	{
	//		return get_front_node_index();
	//	}
	//	if ( front().next_node_index() == -1 )
	//	{
	//		return get_front_node_index();
	//	}
	//	
	//	////externally_allocated_sa_list< type, total_num_nodes >
	//	////	sorted_list( ptr_to_the_node_array, ptr_to_the_free_list );
	//	//s32 temp_front_node_index = -1;
	//	//sa_list_backend<type> sorted_list( &temp_front_node_index, 
	//	//	the_node_array, ptr_to_the_free_list_backend, 
	//	//	total_num_nodes );
	//	externally_allocated_sa_list<type> sorted_list( the_node_array, 
	//		ptr_to_the_free_list_backend, get_total_num_nodes() );
	//	
	//	s32 curr_node_index = sorted_list.get_front_node_index();
	//	
	//	for ( s32 i=get_front_node_index();
	//		i!=-1;  )
	//		//i=get_node_at(i).next_node_index() )
	//	{
	//		
	//		//get_the_free_list_backend().debug_prs32();
	//		
	//		s32 index_of_node_with_lowest_value = i;
	//		
	//		// Find the lowest
	//		for ( s32 j=index_of_node_with_lowest_value;
	//			j!=-1;
	//			j=get_node_at(j).next_node_index() )
	//		{
	//			if ( get_node_at(j).the_data 
	//				< get_node_at(index_of_node_with_lowest_value)
	//				.the_data )
	//			{
	//				index_of_node_with_lowest_value = j;
	//			}
	//		}
	//		
	//		type data_to_push = get_node_at
	//			(index_of_node_with_lowest_value).the_data;
	//		
	//		if ( i == index_of_node_with_lowest_value )
	//		{
	//			i = get_node_at(i).next_node_index();
	//		}
	//		
	//		erase_at(index_of_node_with_lowest_value);
	//		
	//		if ( sorted_list.get_front_node_index() == -1 )
	//		{
	//			sorted_list.push_front(data_to_push);
	//			curr_node_index = sorted_list.get_front_node_index();
	//		}
	//		else
	//		{
	//			sorted_list.insert_after( curr_node_index, data_to_push );
	//			curr_node_index = sorted_list.get_node_at
	//				(curr_node_index).next_node_index();
	//		}
	//		
	//	}
	//	
	//	
	//	get_front_node_index() = sorted_list.get_front_node_index();
	//	
	//	sorted_list.get_front_node_index() = -1;
	//	
	//	return get_front_node_index();
	//}
	
	
	s32 insertion_sort_old_2() __attribute__((noinline))
	{
		s32& the_front_node_index = get_front_node_index();
		
		// Don't do anything if this list has zero or one nodes.
		if ( the_front_node_index < 0 )
		{
			return the_front_node_index;
		}
		if ( get_node_at(the_front_node_index).next_node_index() < 0 )
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
			//i=get_node_at(i).next_node_index() )
		{
			
			//get_the_free_list_backend().debug_prs32();
			
			s32 index_low = i;
			
			sa_list_node<type>* node_at_j;
			
			// Find the lowest value at or after i.
			for ( s32 j=index_low;
				j!=-1; 
				j=node_at_j->next_node_index() )
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
				i = node_at_index_low.next_node_index();
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
					.next_node_index();
			}
			
		}
		
		
		the_front_node_index = temp_front_node_index;
		
		temp_front_node_index = -1;
		
		
		return the_front_node_index;
	}
	
	
	s32 insertion_sort() __attribute__((noinline))
	{
		s32& the_front_node_index = get_front_node_index();
		
		// Don't do anything if this list has zero or one nodes.
		if ( the_front_node_index < 0 )
		{
			return the_front_node_index;
		}
		if ( get_node_at(the_front_node_index).next_node_index() < 0 )
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
		
		
		static constexpr u32 prev_index_low_arr_size = 20;
		s32 prev_index_low_arr[prev_index_low_arr_size];
		
		for ( s32 i=prev_index_low_arr_size-1; i>=0; --i )
		{
			prev_index_low_arr[i] = 0;
		}
		
		
		s32 curr_node_index = temp_front_node_index;
		
		for ( s32 i=the_front_node_index;
			i!=-1;  )
			//i=get_node_at(i).next_node_index() )
		{
			u32 num_extra_low_indices = 0;
			
			
			s32 index_low = i;
			
			sa_list_node<type>* node_at_j;
			
			type* the_data_at_index_low = &get_node_at(index_low).the_data;
			
			// Find the lowest value at or after i.
			for ( s32 j=index_low;
				j!=-1; 
				j=node_at_j->next_node_index() )
			{
				node_at_j = &get_node_at(j);
				
				if ( node_at_j->the_data 
					< *the_data_at_index_low )
				{
					if ( num_extra_low_indices + 1 
						< prev_index_low_arr_size )
					{
						prev_index_low_arr[num_extra_low_indices++]
							= index_low;
					}
					
					index_low = j;
					
					//the_data_at_index_low = &get_node_at(index_low).the
					the_data_at_index_low = &node_at_j->the_data;
				}
			}
			
			sa_list_node<type>& node_at_index_low = get_node_at(index_low);
			//const type data_to_move = node_at_index_low.the_data;
			//type&& data_to_move = node_at_index_low.the_data
			
			if ( i == index_low )
			{
				i = node_at_index_low.next_node_index();
			}
			
			//erase_at(index_low);
			type&& data_to_move = unlink_at(index_low);
			
			if ( temp_front_node_index < 0 )
			{
				sorted_list.push_front(std::move(data_to_move));
				curr_node_index = temp_front_node_index;
			}
			else
			{
				sorted_list.insert_after( curr_node_index, 
					std::move(data_to_move) );
				curr_node_index = sorted_list.get_node_at(curr_node_index)
					.next_node_index();
			}
			
			
			for ( u32 j=0; j<num_extra_low_indices; ++j )
			{
				s32& curr_prev_index_low = prev_index_low_arr[j];
				
				sa_list_node<type>& node_at_curr_prev_index_low 
					= get_node_at(curr_prev_index_low);
				
				if ( i == curr_prev_index_low )
				{
					i = node_at_curr_prev_index_low.next_node_index();
				}
				
				type&& curr_data_to_move = unlink_at(curr_prev_index_low);
				
				//if ( temp_front_node_index < 0 )
				//{
				//	sorted_list.push_front(std::move(data_to_move));
				//	curr_node_index = temp_front_node_index;
				//}
				//else
				{
					sorted_list.insert_after( curr_node_index, 
						std::move(curr_data_to_move) );
					curr_node_index = sorted_list.get_node_at
						(curr_node_index).next_node_index();
				}
			}
		}
		
		
		the_front_node_index = temp_front_node_index;
		
		temp_front_node_index = -1;
		
		
		return the_front_node_index;
	}
	
	inline s32 merge_sort()
	{
		return the_sa_list_backend.merge_sort();
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
	
	constexpr inline u32 get_the_array_size() const
	{
		return get_num_lists();
	}
	constexpr inline u32 get_the_node_array_size() const
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



#endif		// sa_list_class_stuff_hpp
