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


#ifndef generic_funcptr_stuff_hpp
#define generic_funcptr_stuff_hpp


#include "vec2_class.hpp"
#include "misc_types.hpp"

#include <utility>


// These were originally Intended To be used by the SaListBackend and
// externally_allocated_sa_list classes, but they are of course free To use
// for other things.
typedef void (*generic_void_1arg_fp)(void*);
typedef void (*GenericVoid2ArgFp)(void*, void*);
typedef void (*GenericVoid3ArgFp)(void*, void*, void*);
typedef void (*GenericVoid4ArgFp)(void*, void*, void*, void*);
typedef u32 (*Genericu32_2ArgFp)(void*, void*);


// This Is for function pointers To pass To qsort()
typedef int (*QscmpFp)(const void*, const void*);



typedef void* (*GenericVoidPtr1ArgFp)(void*);
typedef s16* (*Generics16Ptr1ArgFp)(void*);

typedef Vec2s16* (*GenericVec2s16Ptr1ArgFp)(void*);


// This X macro Is strictly used for working around what appears To be a
// bug in my text editor's ctags stuff.
#define LIST_OF_TYPES_TO_MAKE_PTR_TYPEDEFS_FOR(macro) \
	macro(void) macro(s16) macro(Vec2s16)

#define GENERATE_PTR_TYPEDEF(type) \
typedef type* type##_ptr;

LIST_OF_TYPES_TO_MAKE_PTR_TYPEDEFS_FOR(GENERATE_PTR_TYPEDEF)

#undef GENERATE_PTR_TYPEDEF
#undef LIST_OF_TYPES_TO_MAKE_PTR_TYPEDEFS_FOR



template<typename type >
inline generic_void_1arg_fp get_generic_void_1arg_fp
	(void (*to_cast)(type*))
{
	return reinterpret_cast<generic_void_1arg_fp>(to_cast);
}
template<typename type_1, typename type_2 >
inline GenericVoid2ArgFp get_generic_void_2arg_fp
	(void (*to_cast)(type_1*, type_2*))
{
	return reinterpret_cast<GenericVoid2ArgFp>(to_cast);
}
template<typename type_1, typename type_2, typename type_3 >
inline GenericVoid3ArgFp get_generic_void_3arg_fp
	(void (*to_cast)(type_1*, type_2*, type_3*))
{
	return reinterpret_cast<GenericVoid3ArgFp>(to_cast);
}
template<typename type_1, typename type_2, typename type_3, 
	typename type_4 >
inline GenericVoid4ArgFp get_generic_void_4arg_fp
	(void (*to_cast)(type_1*, type_2*, type_3*, type_4*))
{
	return reinterpret_cast<GenericVoid4ArgFp>(to_cast);
}




// Make things even more generic
template<typename ret_type, typename type_1 >
inline auto get_other_1arg_fp(ret_type (*to_cast)(type_1*))
{
	return reinterpret_cast<ret_type (*)(void*)>(to_cast);
}

template<typename ret_type, typename type_1, typename type_2 >
inline auto get_other_2arg_fp(ret_type (*to_cast)(type_1*, type_2*))
{
	return reinterpret_cast<ret_type (*)(void*, void*)>(to_cast);
}


template<typename ret_type, typename type_1 >
inline auto get_other_1arg_fp(ret_type (*to_cast)(const type_1*))
{
	return reinterpret_cast<ret_type (*)(const void*)>(to_cast);
}

template<typename ret_type, typename type_1, typename type_2 >
inline auto get_other_2arg_fp
	(ret_type (*to_cast)(const type_1*, const type_2*))
{
	return reinterpret_cast<ret_type (*)(const void*, const void*)>
		(to_cast);
}



template<typename type_1, typename type_2 >
inline auto get_generic_u32_2arg_fp(u32 (*to_cast)(type_1*, type_2*))
{
	return get_other_2arg_fp(to_cast);
}

template<typename type >
inline auto get_qscmp_fp(int (*to_cast)(const type*, const type*))
{
	return get_other_2arg_fp(to_cast);
}

template<typename type >
inline auto get_generic_void_ptr_1arg_fp(void_ptr (*to_cast)(type*))
{
	return get_other_1arg_fp(to_cast);
}

template<typename type >
inline auto get_generic_s16_ptr_1arg_fp(s16_ptr (*to_cast)(type*))
{
	return get_other_1arg_fp(to_cast);
}

template<typename type >
inline auto get_generic_vec2_s16_ptr_1arg_fp
	(vec2_s16_ptr (*to_cast)(type*))
{
	return get_other_1arg_fp(to_cast);
}



extern "C"
{
void generic_binary_func_shared_backend(void* a, void* b,
	GenericVoid2ArgFp the_fp);

u32 generic_u32_func_shared_backend(void* a, void* b,
	Genericu32_2ArgFp the_fp);
}


template<typename type >
inline void generic_binary_func_backend(type* a, type* b,
	void (*the_fp)(type*, type*))
{
	generic_binary_func_shared_backend
		(const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<GenericVoid2ArgFp>(the_fp));
}
template<typename type >
inline void generic_binary_func_backend(const type* a, type* b,
	void (*the_fp)(const type*, type*))
{
	generic_binary_func_shared_backend
		(const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<GenericVoid2ArgFp>(the_fp));
}
template<typename type >
inline void generic_binary_func_backend(type* a, const type* b,
	void (*the_fp)(type*, const type*))
{
	generic_binary_func_shared_backend
		(const_cast<type*>(a), const_cast<type*>(b),
		reinterpret_cast<GenericVoid2ArgFp>(the_fp));
}
// Not sure I'll ever use this
template<typename type >
inline void generic_binary_func_backend(const type* a, const type* b,
	void (*the_fp)(const type*, const type*))
{
	generic_binary_func_shared_backend
		(const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<GenericVoid2ArgFp>(the_fp));
}


template<typename type >
inline u32 generic_u32_func_backend(type* a, type* b,
	u32 (*the_fp)(type*, type*))
{
	return generic_u32_func_shared_backend
		(const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<Genericu32_2ArgFp>(the_fp));
}
template<typename type >
inline u32 generic_u32_func_backend(const type* a, type* b,
	u32 (*the_fp)(const type*, type*))
{
	return generic_u32_func_shared_backend
		(const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<Genericu32_2ArgFp>(the_fp));
}
template<typename type >
inline u32 generic_u32_func_backend(type* a, const type* b,
	u32 (*the_fp)(type*, const type*))
{
	return generic_u32_func_shared_backend
		(const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<Genericu32_2ArgFp>(the_fp));
}
template<typename type >
inline u32 generic_u32_func_backend(const type* a, const type* b,
	u32 (*the_fp)(const type*, const type*))
{
	return generic_u32_func_shared_backend
		(const_cast<type*>(a), const_cast<type*>(b), 
		reinterpret_cast<Genericu32_2ArgFp>(the_fp));
}



//inline void generic_copy_func_backend(void* a, const void* b, 
//	void (*copy_func)(void*, const void*))
//{
//	generic_binary_func_backend(a, b, copy_func);
//}



template<typename type >
inline void generic_copy(type& a, const type& b)
{
	generic_binary_func_backend<type>(&a, &b, 
		[](type* a2, const type* b2){ *a2 = *b2; });
}


template<typename type >
inline void generic_move(type& a, type&& b)
{
	generic_binary_func_backend<type>(&a, &b, 
		[](type* a2, type* b2){ *a2 = std::move(*b2); });
}


template<typename type >
inline u32 generic_less(const type& a, const type& b)
{
	return generic_u32_func_backend<type>(&a, &b, 
		[](const type* a2, const type* b2) -> u32
		{ return ((*a2) < (*b2)); });
}




#endif		// generic_funcptr_stuff_hpp
