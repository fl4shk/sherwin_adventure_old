// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef dyn_arr_class_hpp
#define dyn_arr_class_hpp


#include <utility>
#include <type_traits>

#include "misc_types.hpp"



// This Is a class for dynamic arrays That Can be resized but only by
// calling the resize() function.
template< typename type >
class DynArr
{
protected:		// variables
	size_t size = 0;
	type* arr = NULL;
	
public:		// classes
	//class Iterator
	//{
	//public:		// typedefs
	//	typedef Iterator self_type;
	//	typedef type value_type;
	//	typedef type& reference;
	//	typedef type* pointer;
	//	typedef std::random_access_iterator_tag iterator_category;
	//	typedef s32 difference_type;
	//	
	//protected:		// variables
	//	DynArr<type> *const dyn_arr_ptr;
	//	size_t pos;
	//	
	//public:		// functions
	//	inline Iterator( DynArr<type>* s_dyn_arr_ptr, size_t s_pos )
	//		: dyn_arr_ptr(s_dyn_arr_ptr), pos(s_pos)
	//	{
	//	}
	//	
	//	inline DynArr<type> *const get_dyn_arr_ptr() const
	//	{
	//		return dyn_arr_ptr;
	//	}
	//	inline size_t get_pos() const
	//	{
	//		return pos;
	//	}
	//	
	//	inline Iterator& operator += ( s32 value )
	//	{
	//		s32 temp = pos;
	//		temp += value;
	//		pos = temp;
	//	}
	//	
	//	//inline 
	//	
	//} __attribute__((_ALIGN4));
	
	//class Iterator
	//{
	//public:		// typedefs
	//	
	//	
	//protected:		// variables
	//	DynArr<type> *const dyn_arr_ptr;
	//	s32 pos;
	//	
	//public:		// functions
	//	inline Iterator( DynArr<type>* s_dyn_arr_ptr, s32 s_pos )
	//		: dyn_arr_ptr(s_dyn_arr_ptr), pos(s_pos)
	//	{
	//	}
	//	
	//	inline DynArr<type> *const get_dyn_arr_ptr() const
	//	{
	//		return dyn_arr_ptr;
	//	}
	//	inline s32 get_pos() const
	//	{
	//		return pos;
	//	}
	//	
	//	inline bool operator != ( const Iterator& other ) const
	//	{
	//		if ( get_pos() != other.get_pos() )
	//		{
	//			return true;
	//		}
	//		else if ( get_dyn_arr_ptr() != other.get_dyn_arr_ptr() )
	//		{
	//			return true;
	//		}
	//		else
	//		{
	//			return false;
	//		}
	//	}
	//	
	//	inline Iterator& operator ++ ()
	//	{
	//		++pos;
	//		return *this;
	//	}
	//	inline Iterator& operator -- ()
	//	{
	//		--pos;
	//		return *this;
	//	}
	//	inline Iterator& operator += ( s32 value )
	//	{
	//		pos += value;
	//		return *this;
	//	}
	//	
	//	//inline 
	//	
	//} __attribute__((_ALIGN4));
	
	
public:		// functions
	inline DynArr( size_t s_size=1 ) : size(s_size)
	{
		alloc_arr();
	}
	inline DynArr( const DynArr<type>& to_copy )
	{
		*this = to_copy;
	}
	inline DynArr( DynArr<type>&& to_move )
	{
		*this = std::move(to_move);
	}
	inline ~DynArr()
	{
		dealloc_arr();
	}
	
	
	inline DynArr& operator = ( const DynArr<type>& to_copy )
	{
		dealloc_arr();
		
		size = to_copy.get_size();
		alloc_arr();
		
		copy_to_arr( to_copy.get_arr(), get_size() );
	}
	inline DynArr& operator = ( DynArr<type>&& to_copy )
	{
		size = to_copy.get_size();
		arr = to_copy.get_arr();
		
		to_copy.size = 0;
		to_copy.arr = NULL;
	}
	
	inline type* get_arr()
	{
		return arr;
	}
	inline const type* get_arr() const
	{
		return arr;
	}
	inline size_t get_size() const
	{
		return size;
	}
	
	inline type& operator [] ( size_t index )
	{
		return get_arr()[index];
	}
	inline const type& operator [] ( size_t index ) const
	{
		return get_arr()[index];
	}
	
	inline void resize( size_t n_size )
	{
		DynArr<type> temp_arr(std::move(*this));
		
		size = n_size;
		alloc_arr();
		
		copy_to_arr( temp_arr.get_arr(), temp_arr.get_size() );
		
		*this = std::move(temp_arr);
	}
	
protected:		// functions
	inline void copy_to_arr( type* to_copy, size_t the_size )
	{
		//// Optimization for trivially copyable types... eh screw it I'll
		//// let the compiler do That if it wants.
		//if ( std::is_trivially_copyable<type>::value )
		//{
		//	arr_memcpy( arr, to_copy, the_size );
		//}
		//else
		{
			for ( s32 i=the_size-1; i>=0; --i )
			//for ( size_t i=0; i<the_size; ++i )
			{
				arr[i] = to_copy[i];
			}
		}
	}
	inline void alloc_arr()
	{
		arr = new type[get_size()];
	}
	inline void dealloc_arr()
	{
		delete [] arr;
	}
	
	
} __attribute__((_ALIGN4));




#endif		// dyn_arr_class_hpp
