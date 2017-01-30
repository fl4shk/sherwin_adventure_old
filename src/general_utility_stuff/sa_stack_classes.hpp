// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
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


#ifndef sa_stack_class_hpp
#define sa_stack_class_hpp

#include "misc_types.hpp"
//#include "../gba_specific_stuff/attribute_defines.hpp"
//#include "../gba_specific_stuff/asm_funcs.hpp"
#include "array_helper_class.hpp"

#include <array>
using std::array;




#define arr_byte_index_macro( the_type_size, index_to_array_of_types ) \
	the_type_size * index_to_array_of_types

#define arr_byte_size_macro( type, the_num_arr_elems ) \
	arr_byte_index_macro( sizeof(type), the_num_arr_elems )
template< typename type >
inline size_t arr_byte_size( size_t the_num_arr_elems )
{
	return ( sizeof(type) * the_num_arr_elems );
}


// A backend to a statically allocated stack of plain old data 
class sa_pod_stack_backend
{
protected:		// variables
	u8* ptr_to_the_array_u8;
	u32* ptr_to_next_index;
	u32 type_size, num_elems;
	
public:		// functions
	sa_pod_stack_backend();
	sa_pod_stack_backend( u8* s_ptr_to_the_array_u8, 
		u32* s_ptr_to_next_index, u32 s_type_size, u32 s_num_elems );
	
	inline u8* get_the_array_u8()
	{
		return ptr_to_the_array_u8;
	}
	inline const u8* get_the_array_u8() const
	{
		return ptr_to_the_array_u8;
	}
	
	inline u32& get_next_index()
	{
		return *ptr_to_next_index;
	}
	inline const u32 get_next_index() const
	{
		return *ptr_to_next_index;
	}
	
	inline const u32 get_type_size() const
	{
		return type_size;
	}
	inline const u32 get_size() const
	{
		return num_elems;
	}
	
	inline bool can_push() const
	{
		return ( get_next_index() <= get_size() );
	}
	inline bool can_pop() const
	{
		return ( get_next_index() > 0 );
	}
	
	inline void push( const u8* to_push_u8 )
	{
		//the_array[next_index++] = to_push;
		write_to_the_array_u8( to_push_u8, get_next_index()++ );
	}
	
	virtual void pop();
	
protected:		// functions
	void write_to_the_array_u8( const u8* to_write_u8, u32 non_u8_index );
	
} __attribute__((_align4));



// Since an sa_free_list uses plain old data (ints), it can use a backend
// that is derived from the sa_pod_stack_backend class.
class sa_free_list_backend : public sa_pod_stack_backend
{
public:		// constants
	//static constexpr u32 the_const_type_size = sizeof(int);
	static constexpr u32 the_const_type_size = sizeof(int);
	
public:		// functions
	sa_free_list_backend();
	sa_free_list_backend( u8* s_ptr_to_the_array_u8, 
		u32* s_ptr_to_next_index, u32 s_num_elems );
	sa_free_list_backend( s16* s_ptr_to_the_array, 
		u32* s_ptr_to_next_index, u32 s_num_elems );
	
	void init();
	
	inline u32 get_the_const_type_size() const
	{
		return the_const_type_size;
	}
	
	//inline int* get_the_array()
	//{
	//	int* ret = (int*)get_the_array_u8();
	//	return ret;
	//}
	//inline const int* get_the_array() const
	//{
	//	int* ret = (int*)get_the_array_u8();
	//	return ret;
	//}
	inline s16* get_the_array()
	{
		s16* ret = (s16*)get_the_array_u8();
		return ret;
	}
	inline const s16* get_the_array() const
	{
		s16* ret = (s16*)get_the_array_u8();
		return ret;
	}
	
	inline void push( s32 to_push )
	{
		get_the_array()[get_next_index()++] = (s16)to_push;
	}
	inline void pop() override
	{
		get_the_array()[get_next_index()-1] = -1;
		
		sa_pod_stack_backend::pop();
	}
	
	inline s16& peek_top()
	{
		return get_the_array()[get_next_index()-1];
	}
	inline const s32 peek_top() const
	{
		return get_the_array()[get_next_index()-1];
	}
	
} __attribute__((_align4));





// A backend to a more generic statically allocated stack which is used
// because it reduces the number of template parameters
template< typename type >
class sa_stack_backend
{
public:		// variables
	//type* ptr_to_the_array;
	//u32 num_elems;
	array_helper<type> the_array_helper;
	u32* ptr_to_next_index;
	
public:		// functions
	sa_stack_backend() : the_array_helper(), ptr_to_next_index(NULL)
	{
	}
	
	sa_stack_backend( type* s_ptr_to_the_array, u32 s_num_elems, 
		u32* s_ptr_to_next_index ) 
		: the_array_helper( s_ptr_to_the_array, s_num_elems ), 
		ptr_to_next_index(s_ptr_to_next_index)
	{
	}
	
	void init( type* s_ptr_to_the_array, u32 s_num_elems, 
		u32* s_ptr_to_next_index )
	{
		the_array_helper.init( s_ptr_to_the_array, s_num_elems );
		ptr_to_next_index = s_ptr_to_next_index;
	}
	
	type* get_the_array()
	{
		return the_array_helper.the_array;
	}
	const type* get_the_array() const
	{
		return the_array_helper.get_the_array();
	}
	
	inline u32& get_next_index()
	{
		return *ptr_to_next_index;
	}
	inline const u32 get_next_index() const
	{
		return *ptr_to_next_index;
	}
	
	inline u32 get_size() const
	{
		return the_array_helper.get_size();
	}
	
	
	void push( const type& to_push )
	{
		get_the_array()[get_next_index()++] = to_push;
	}
	
	void pop()
	{
		--get_next_index();
	}
	
	inline type peek_top()
	{
		return get_the_array()[get_next_index()-1];
	}
	inline const type peek_top() const
	{
		return get_the_array()[get_next_index()-1];
	}
	
} __attribute__((_align4));



template< typename type, u32 size >
class sa_stack
{
protected:		// variables
	sa_stack_backend<type> the_sa_stack_backend;
	
public:		// variables
	//type the_array[size];
	array< type, size > the_array;
	u32 next_index;
	
public:		// functions
	inline sa_stack() : the_sa_stack_backend( the_array.data(), get_size(), 
		&next_index ), next_index(0)
	{
		//memfill32( the_array.data(), type(), size * sizeof(type) );
		
		the_array.fill(type());
	}
	
	inline u32& get_next_index()
	{
		return next_index;
	}
	inline const u32 get_next_index() const
	{
		return next_index;
	}
	inline u32 get_size() const
	{
		return size;
	}
	
	
	inline void push( const type& to_push )
	{
		//the_array[next_index++] = to_push;
		the_sa_stack_backend.push(to_push);
	}
	
	//inline virtual const type pop()
	//{
	//	return the_array[--next_index];
	//}
	
	inline void pop()
	{
		//--next_index;
		the_sa_stack_backend.pop();
	}
	
	inline type peek_top()
	{
		//return the_array[next_index-1];
		return the_sa_stack_backend.peek_top();
	}
	inline const type peek_top() const
	{
		//return the_array[next_index-1];
		return the_sa_stack_backend.peek_top();
	}
	
	
} __attribute__((_align4));


template< u32 size >
class old_sa_free_list : public sa_stack< int, size >
{
public:		// typedefs
	typedef sa_stack< int, size > specific_sa_stack;
	
public:		// functions
	inline old_sa_free_list()
	{
		for ( int i=size-1; i>=0; --i )
		{
			specific_sa_stack::push(i);
		}
	}
	
	inline void pop()
	{
		specific_sa_stack::the_array[specific_sa_stack::next_index-1] = -1;
		--specific_sa_stack::next_index;
	}
	
} __attribute__((_align4));


template< u32 size >
class sa_free_list
{
protected:		// variables
	sa_free_list_backend the_sa_free_list_backend;
	
	//template< typename type > friend class sa_list_backend;
	//template< typename type, u32 total_num_nodes > friend class
	//	externally_allocated_sa_list;
	template< typename type, u32 total_num_nodes > 
		friend class regular_sa_list_base;
	template< typename type, u32 total_num_nodes, u32 num_lists >
		friend class sa_array_of_lists;
	
protected:		// variables
	//array< int, size > the_array;
	array< s16, size > the_array __attribute__((_align4));
	u32 next_index;
	
public:		// functions
	inline sa_free_list() : the_sa_free_list_backend( the_array.data(), 
		&next_index, get_size() )
	{
		//the_sa_free_list_backend.init();
		
		//for ( int i=get_size()-1; i>= 0; --i )
		//{
		//	push(i);
		//}
	}
	
	inline u32& get_next_index()
	{
		return the_sa_free_list_backend.get_next_index();
	}
	inline const u32 get_next_index() const
	{
		return the_sa_free_list_backend.get_next_index();
	}
	
	inline u32 get_size() const
	{
		return size;
	}
	
	
	inline void push( int to_push )
	{
		//the_array[next_index++] = to_push;
		the_sa_free_list_backend.push(to_push);
	}
	
	//inline virtual const type pop()
	//{
	//	return the_array[--next_index];
	//}
	
	inline void pop()
	{
		//--next_index;
		the_sa_free_list_backend.pop();
	}
	
	inline int peek_top()
	{
		//return the_array[next_index-1];
		return the_sa_free_list_backend.peek_top();
	}
	inline const int peek_top() const
	{
		//return the_array[next_index-1];
		return the_sa_free_list_backend.peek_top();
	}
	
	
} __attribute__((_align4));



#endif		// sa_stack_class_hpp
