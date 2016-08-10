// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#ifndef generic_funcptr_stuff_hpp
#define generic_funcptr_stuff_hpp


#include "vec2_class.hpp"
#include "misc_types.hpp"

#include <utility>


// These were originally intended to be used by the sa_list_backend and
// externally_allocated_sa_list classes, but they are of course free to use
// for other things.
typedef void (*generic_void_1arg_fp)( void* );
typedef void (*generic_void_2arg_fp)( void*, void* );
typedef void (*generic_void_3arg_fp)( void*, void*, void* );
typedef u32 (*generic_u32_2arg_fp)( void*, void* );

typedef void* (*generic_void_ptr_1arg_fp)( void* );
typedef s16* (*generic_s16_ptr_1arg_fp)( void* );

typedef vec2_s16* (*generic_vec2_s16_ptr_1arg_fp)( void* );


// This X macro is strictly used for working around what appears to be a
// bug in my text editor's ctags stuff.
#define list_of_types_to_make_ptr_typedefs_for(macro) \
	macro(void) macro(s16) macro(vec2_s16)

#define generate_ptr_typedef(type) \
typedef type* type##_ptr;

list_of_types_to_make_ptr_typedefs_for(generate_ptr_typedef)

#undef generate_ptr_typedef
#undef list_of_types_to_make_ptr_typedefs_for



template< typename type >
inline auto get_generic_void_1arg_fp( void (*to_cast)( type* ) )
{
	return reinterpret_cast<generic_void_1arg_fp>(to_cast);
}


template< typename type_1, typename type_2 >
inline auto get_generic_void_2arg_fp
	( void (*to_cast)( type_1*, type_2* ) )
{
	return reinterpret_cast<generic_void_2arg_fp>(to_cast);
}


template< typename type_1, typename type_2, typename type_3 >
inline auto get_generic_void_3arg_fp
	( void (*to_cast)( type_1*, type_2*, type_3* ) )
{
	return reinterpret_cast<generic_void_3arg_fp>(to_cast);
}

template< typename type_1, typename type_2 >
inline auto get_generic_u32_2arg_fp
	( u32 (*to_cast)( type_1*, type_2* ) )
{
	return reinterpret_cast<generic_u32_2arg_fp>(to_cast);
}

template< typename type >
inline auto get_generic_void_ptr_1arg_fp
	( void_ptr (*to_cast)( type* ) )
{
	return reinterpret_cast<generic_void_ptr_1arg_fp>(to_cast);
}

template< typename type >
inline auto get_generic_s16_ptr_1arg_fp( s16_ptr (*to_cast)( type* ) )
{
	return reinterpret_cast<generic_s16_ptr_1arg_fp>(to_cast);
}

template< typename type >
inline auto get_generic_vec2_s16_ptr_1arg_fp
	( vec2_s16_ptr (*to_cast)( type* ) )
{
	return reinterpret_cast<generic_vec2_s16_ptr_1arg_fp>(to_cast);
}




extern "C"
{
void generic_binary_func_shared_backend( void* a, void* b,
	generic_void_2arg_fp the_fp );

u32 generic_u32_func_shared_backend( void* a, void* b,
	generic_u32_2arg_fp the_fp );
}


template< typename type >
inline void generic_binary_func_backend( type* a, type* b,
	void (*the_fp)( type*, type* ) )
{
	generic_binary_func_shared_backend
		( const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<generic_void_2arg_fp>(the_fp) );
}
template< typename type >
inline void generic_binary_func_backend( const type* a, type* b,
	void (*the_fp)( const type*, type* ) )
{
	generic_binary_func_shared_backend
		( const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<generic_void_2arg_fp>(the_fp) );
}
template< typename type >
inline void generic_binary_func_backend( type* a, const type* b,
	void (*the_fp)( type*, const type* ) )
{
	generic_binary_func_shared_backend
		( const_cast<type*>(a), const_cast<type*>(b),
		reinterpret_cast<generic_void_2arg_fp>(the_fp) );
}
// Not sure I'll ever use this
template< typename type >
inline void generic_binary_func_backend( const type* a, const type* b,
	void (*the_fp)( const type*, const type* ) )
{
	generic_binary_func_shared_backend
		( const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<generic_void_2arg_fp>(the_fp) );
}


template< typename type >
inline u32 generic_u32_func_backend( type* a, type* b,
	u32 (*the_fp)( type*, type* ) )
{
	return generic_u32_func_shared_backend
		( const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<generic_u32_2arg_fp>(the_fp) );
}
template< typename type >
inline u32 generic_u32_func_backend( const type* a, type* b,
	u32 (*the_fp)( const type*, type* ) )
{
	return generic_u32_func_shared_backend
		( const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<generic_u32_2arg_fp>(the_fp) );
}
template< typename type >
inline u32 generic_u32_func_backend( type* a, const type* b,
	u32 (*the_fp)( type*, const type* ) )
{
	return generic_u32_func_shared_backend
		( const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<generic_u32_2arg_fp>(the_fp) );
}
template< typename type >
inline u32 generic_u32_func_backend( const type* a, const type* b,
	u32 (*the_fp)( const type*, const type* ) )
{
	return generic_u32_func_shared_backend
		( const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<generic_u32_2arg_fp>(the_fp) );
}



//inline void generic_copy_func_backend( void* a, const void* b, 
//	void (*copy_func)( void*, const void* ) )
//{
//	generic_binary_func_backend( a, b, copy_func );
//}



template< typename type >
inline void generic_copy( type& a, const type& b )
{
	generic_binary_func_backend<type>( &a, &b, 
		[]( type* a2, const type* b2 ){ *a2 = *b2; } );
}


template< typename type >
inline void generic_move( type& a, type&& b )
{
	generic_binary_func_backend<type>( &a, &b, 
		[]( type* a2, type* b2 ){ *a2 = std::move(*b2); } );
}


template< typename type >
inline u32 generic_less( const type& a, const type& b )
{
	return generic_u32_func_backend<type>( &a, &b, 
		[]( const type* a2, const type* b2 ) -> u32
		{ return ( (*a2) < (*b2) ); } );
}





#endif		// generic_funcptr_stuff_hpp
