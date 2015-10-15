#ifndef array_helper_class_hpp
#define array_helper_class_hpp



#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"


// This is a VERY thin wrapper class for working with 1D arrays
template < typename type >
class array_helper
{
public:			// variables
	type* the_array;
	
protected:		// variables
	u32 size;
	
public:			// functions
	array_helper()
		: the_array(NULL), size(0)
	{
	}
	
	array_helper( type* s_the_array, u32 s_size )
		: the_array(s_the_array), size(s_size)
	{
	}
	
	void init( type* s_the_array, u32 s_size )
	{
		the_array = s_the_array;
		size = s_size;
	}
	
	
	void operator = ( array_helper<type>& to_copy )
	{
		the_array = to_copy.the_array;
		size = to_copy.size;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	u32 get_size() const
	{
		return size;
	}
	
	type& data_at( u32 offset )
	{
		return the_array [offset];
	}
	
	
};


#endif		// array_helper_class_hpp
