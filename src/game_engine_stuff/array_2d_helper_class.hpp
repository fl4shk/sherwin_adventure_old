#ifndef array_2d_helper_class_hpp
#define array_2d_helper_class_hpp

#include "misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "vec2_class.hpp"


// This utility class is intended to be used when inherently 2D data is
// stored within a 1D array.
template< typename type >
class array_2d_helper
{
protected:		// variables
	vec2_u32 size_2d;
	u32 size;
	
public:			// variables
	type* the_array;
	
public:			// functions
	array_2d_helper()
		: the_array(0), size_2d({ 0, 0 }), size(0)
	{
	}
	array_2d_helper( type* s_the_array, const vec2_u32& s_size_2d )
		: the_array(s_the_array), size_2d(s_size_2d), 
		size( s_size_2d.x * s_size_2d.y )
	{
	}
	
	void init( type* s_the_array, const vec2_u32& s_size_2d )
	{
		the_array = s_the_array;
		size_2d = s_size_2d;
		size = size_2d.x * size_2d.y;
	}
	
	void operator = ( array_2d_helper<type>& to_copy )
	{
		the_array = to_copy.the_array;
		size_2d = to_copy.size_2d;
		size = to_copy.size;
	}
	
	
	const type* get_the_array() const
	{
		return the_array;
	}
	
	u32 width() const
	{
		return size_2d.x;
	}
	u32 height() const
	{
		return size_2d.y;
	}
	
	const vec2_u32& get_size_2d() const
	{
		return size_2d;
	}
	u32 get_size() const
	{
		return size;
	}
	
	type& data_at( u32 x, u32 y )
	{
		return the_array[ y * size_2d.x + x ];
	}
	type& data_at( const vec2_u32& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	type& data_at( const vec2_s32& offset_2d )
	{
		return the_array[ offset_2d.y * size_2d.x + offset_2d.x ];
	}
	
	
};



#endif		// array_2d_helper_class_hpp
