#ifndef sa_stack_class_hpp
#define sa_stack_class_hpp


#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"


template< typename type, u32 size >
class sa_stack
{
public:		// variables
	type the_array[size];
	u32 curr_index;
	
public:		// functions
	inline sa_stack() : curr_index(0)
	{
		memfill32( the_array, type(), size * sizeof(type) );
	}
	
	inline void push( const type& to_push )
	{
		the_array[curr_index++] = to_push;
	}
	
	inline const type& pop()
	{
		return the_array[--curr_index];
	}
	
	inline const type& peek_top() const
	{
		return the_array[curr_index-1];
	}
	
	inline type& peek_top()
	{
		return the_array[curr_index-1];
	}
	
	inline u32 get_size() const
	{
		return size;
	}
	
} __attribute__((_align4));


template< u32 size >
class sa_free_list : public sa_stack< int, size >
{
public:		// variables
	
	
public:		// functions
	inline sa_free_list()
	{
		for ( int i=size-1; i>=0; --i )
		{
			sa_stack< int, size >::push(i);
		}
	}
	
} __attribute__((_align4));





#endif		// sa_stack_class_hpp
