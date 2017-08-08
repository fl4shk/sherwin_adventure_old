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


#ifndef sa_stack_class_hpp
#define sa_stack_class_hpp

#include "misc_types.hpp"
//#include "../gba_specific_stuff/attribute_defines.hpp"
//#include "../gba_specific_stuff/asm_funcs.hpp"
#include "array_helper_class.hpp"

#include <array>
using std::array;

//#include "sa_list_class_stuff.hpp"
//#include "extended_sa_list_class_stuff.hpp"

namespace SaListStuff
{

template<typename Type, u32 total_num_nodes> 
	class RegularListBase;
template<typename Type, u32 total_num_nodes, u32 num_lists>
	class SaArrayOfLists;

} // end of namespace SaListStuff



#define ARR_BYTE_INDEX_MACRO(the_type_size, index_to_array_of_types) \
	the_type_size * index_to_array_of_types

#define ARR_BYTE_SIZE_MACRO(Type, the_num_arr_elems) \
	ARR_BYTE_INDEX_MACRO(sizeof(Type), the_num_arr_elems)
template<typename Type>
inline size_t arr_byte_size(size_t the_num_arr_elems)
{
	return (sizeof(Type) * the_num_arr_elems);
}


// A backend To a statically allocated stack of plain old data 
class SaPodStackBackend
{
protected:		// variables
	u8* the_array_u8;
	u32* next_index_ptr;
	u32 type_size, num_elems;
	
public:		// functions
	SaPodStackBackend();
	SaPodStackBackend(u8* s_the_array_u8, u32* s_next_index_ptr, 
		u32 s_type_size, u32 s_num_elems);
	SaPodStackBackend(const SaPodStackBackend& to_copy);
	
	inline u8* get_array_u8()
	{
		return the_array_u8;
	}
	inline const u8* get_array_u8() const
	{
		return the_array_u8;
	}
	
	inline u32& get_next_index()
	{
		return *next_index_ptr;
	}
	inline const u32 get_next_index() const
	{
		return *next_index_ptr;
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
		return (get_next_index() <= get_size());
	}
	inline bool can_pop() const
	{
		return (get_next_index()> 0);
	}
	
	inline void push(const u8* to_push_u8)
	{
		//the_array[next_index++] = to_push;
		write_to_the_array_u8(to_push_u8, get_next_index()++);
	}
	
	//virtual void pop();
	inline void pop()
	{
		--get_next_index();
	}
	
protected:		// functions
	void write_to_the_array_u8(const u8* to_write_u8, u32 non_u8_index);
	
} __attribute__((_align4));



// Since an SaFreeList uses plain old data (ints), it Can use a backend
// That Is derived from the SaPodStackBackend class.
class SaFreeListBackend : public SaPodStackBackend
{
public:		// constants
	//static constexpr u32 the_const_type_size = sizeof(int);
	static constexpr u32 the_const_type_size = sizeof(int);
	
public:		// functions
	SaFreeListBackend();
	SaFreeListBackend(u8* s_the_array_u8, 
		u32* s_next_index_ptr, u32 s_num_elems);
	SaFreeListBackend(s16* s_the_array, 
		u32* s_next_index_ptr, u32 s_num_elems);
	SaFreeListBackend(const SaFreeListBackend& to_copy);
	
	void init();
	
	inline u32 get_const_type_size() const
	{
		return the_const_type_size;
	}
	
	//inline int* get_array()
	//{
	//	int* ret = (int*)get_array_u8();
	//	return ret;
	//}
	//inline const int* get_array() const
	//{
	//	int* ret = (int*)get_array_u8();
	//	return ret;
	//}
	inline s16* get_array()
	{
		s16* ret = (s16*)get_array_u8();
		return ret;
	}
	inline const s16* get_array() const
	{
		s16* ret = (s16*)get_array_u8();
		return ret;
	}
	
	inline void push(s32 to_push)
	{
		get_array()[get_next_index()++] = (s16)to_push;
	}
	//inline void pop() override
	//{
	//	get_array()[get_next_index()-1] = -1;
	//	
	//	SaPodStackBackend::pop();
	//}
	
	inline s16& peek_top()
	{
		return get_array()[get_next_index()-1];
		//return get_array()[get_next_index()];
	}
	inline const s32 peek_top() const
	{
		return get_array()[get_next_index()-1];
		//return get_array()[get_next_index()];
	}
	//inline s16& peek_next()
	//{
	//	return get_array()[get_next_index()-2];
	//}
	//inline const s32 peek_next() const
	//{
	//	return get_array()[get_next_index()-2];
	//}
	
	
	// A wrapper function just in case it's ever forgotten what To do.
	inline s16& peek_top_and_pop()
	{
		s16& ret = peek_top();
		
		pop();
		
		return ret;
	}
	
} __attribute__((_align4));





// A backend To a more generic statically allocated stack which Is used
// because it reduces the number of template parameters.
template<typename Type>
class SaStackBackend
{
public:		// variables
	//Type* the_array;
	//u32 num_elems;
	ArrayHelper<Type> the_array_helper;
	u32* next_index_ptr;
	
public:		// functions
	SaStackBackend() : the_array_helper(), next_index_ptr(NULL)
	{
	}
	
	SaStackBackend(Type* s_the_array, u32 s_num_elems, 
		u32* s_next_index_ptr) 
		: the_array_helper(s_the_array, s_num_elems), 
		next_index_ptr(s_next_index_ptr)
	{
	}
	
	void init(Type* s_the_array, u32 s_num_elems, 
		u32* s_next_index_ptr)
	{
		the_array_helper.init(s_the_array, s_num_elems);
		next_index_ptr = s_next_index_ptr;
	}
	
	Type* get_array()
	{
		return the_array_helper.the_array;
	}
	const Type* get_array() const
	{
		return the_array_helper.get_array();
	}
	
	inline u32& get_next_index()
	{
		return *next_index_ptr;
	}
	inline const u32 get_next_index() const
	{
		return *next_index_ptr;
	}
	
	inline u32 get_size() const
	{
		return the_array_helper.get_size();
	}
	
	
	void push(const Type& to_push)
	{
		get_array()[get_next_index()++] = to_push;
	}
	
	void pop()
	{
		--get_next_index();
	}
	
	inline Type peek_top()
	{
		return get_array()[get_next_index()-1];
	}
	inline const Type peek_top() const
	{
		return get_array()[get_next_index()-1];
	}
	
	//inline Type peek_next()
	//{
	//	return get_array()[get_next_index()-2];
	//}
	//inline const Type peek_next() const
	//{
	//	return get_array()[get_next_index()-2];
	//}
	
} __attribute__((_align4));



template<typename Type, u32 size>
class SaStack
{
protected:		// variables
	SaStackBackend<Type> the_sa_stack_backend;
	
public:		// variables
	//Type the_array[size];
	array<Type, size> the_array;
	u32 next_index;
	
public:		// functions
	inline SaStack() : the_sa_stack_backend(the_array.data(), get_size(), 
		&next_index), next_index(0)
	{
		//memfill32(the_array.data(), Type(), size * sizeof(Type));
		
		the_array.fill(Type());
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
	
	
	inline void push(const Type& to_push)
	{
		//the_array[next_index++] = to_push;
		the_sa_stack_backend.push(to_push);
	}
	
	//inline virtual const Type pop()
	//{
	//	return the_array[--next_index];
	//}
	
	inline void pop()
	{
		//--next_index;
		the_sa_stack_backend.pop();
	}
	
	inline Type peek_top()
	{
		//return the_array[next_index-1];
		return the_sa_stack_backend.peek_top();
	}
	inline const Type peek_top() const
	{
		//return the_array[next_index-1];
		return the_sa_stack_backend.peek_top();
	}
	
	//inline Type peek_next()
	//{
	//	//return the_array[next_index];
	//	return the_sa_stack_backend.peek_next();
	//}
	//inline const Type peek_next() const
	//{
	//	//return the_array[next_index];
	//	return the_sa_stack_backend.peek_next();
	//}
	
	
} __attribute__((_align4));


template<u32 size>
class OldSaFreeList : public SaStack<int, size>
{
public:		// typedefs
	typedef SaStack<int, size> SpecificSaStack;
	
public:		// functions
	inline OldSaFreeList()
	{
		for (int i=size-1; i>=0; --i)
		{
			SpecificSaStack::push(i);
		}
	}
	
	inline void pop()
	{
		SpecificSaStack::the_array[SpecificSaStack::next_index-1] = -1;
		--SpecificSaStack::next_index;
	}
	
} __attribute__((_align4));


template<u32 size>
class SaFreeList
{
protected:		// variables
	SaFreeListBackend the_sa_free_list_backend;
	
	//template<typename Type> friend class SaListBackend;
	//template<typename Type, u32 total_num_nodes> friend class
	//	externally_allocated_sa_list;
	template<typename Type, u32 total_num_nodes> 
		friend class SaListStuff::RegularListBase;
	template<typename Type, u32 total_num_nodes, u32 num_lists>
		friend class SaListStuff::SaArrayOfLists;
	
protected:		// variables
	//array<int, size> the_array;
	array<s16, size> the_array __attribute__((_align4));
	u32 next_index;
	
public:		// functions
	inline SaFreeList() : the_sa_free_list_backend(the_array.data(), 
		&next_index, get_size())
	{
		//the_sa_free_list_backend.init();
		
		//for (int i=get_size()-1; i>= 0; --i)
		//{
		//	push(i);
		//}
	}
	inline SaFreeList(const SaFreeList<size>& to_copy)
		: the_sa_free_list_backend(the_array.data(), &next_index,
		get_size())
	{
		arr_memcpy(the_array, to_copy.the_array);
	}
	
	//inline SaFreeList<size>& operator = 
	//	(const SaFreeList<size>& to_copy)
	//{
	//	the_sa_free_list_backend
	//}
	
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
	
	
	inline void push(int to_push)
	{
		//the_array[next_index++] = to_push;
		the_sa_free_list_backend.push(to_push);
	}
	
	//inline virtual const Type pop()
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
	
	//inline int peek_next()
	//{
	//	//return the_array[next_index];
	//	return the_sa_free_list_backend.peek_next();
	//}
	//inline const int peek_next() const
	//{
	//	//return the_array[next_index];
	//	return the_sa_free_list_backend.peek_next();
	//}
	
	
} __attribute__((_align4));



#endif		// sa_stack_class_hpp
