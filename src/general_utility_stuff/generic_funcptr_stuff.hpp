// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andrew Clark (FL4SHK).
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


#ifndef general_utility_stuff__slash__generic_funcptr_stuff_hpp
#define general_utility_stuff__slash__generic_funcptr_stuff_hpp


#include "vec2_class.hpp"
#include "misc_types.hpp"

#include <utility>

namespace sherwin_adventure
{

namespace misc_util
{

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

typedef Vec2S16* (*GenericVec2S16Ptr1ArgFp)(void*);


// This X macro Is strictly used for working around what appears To be a
// bug in my text editor's ctags stuff.
#define LIST_OF_TYPES_TO_MAKE_PTR_TYPEDEFS_FOR(macro) \
	macro(void) macro(s16) macro(Vec2S16)

#define GENERATE_PTR_TYPEDEF(Type) \
typedef Type* Type##Ptr;

LIST_OF_TYPES_TO_MAKE_PTR_TYPEDEFS_FOR(GENERATE_PTR_TYPEDEF)

#undef GENERATE_PTR_TYPEDEF
#undef LIST_OF_TYPES_TO_MAKE_PTR_TYPEDEFS_FOR



template<typename Type>
inline generic_void_1arg_fp get_generic_void_1arg_fp
	(void (*to_cast)(Type*))
{
	return reinterpret_cast<generic_void_1arg_fp>(to_cast);
}
template<typename type_1, typename type_2>
inline GenericVoid2ArgFp get_generic_void_2arg_fp
	(void (*to_cast)(type_1*, type_2*))
{
	return reinterpret_cast<GenericVoid2ArgFp>(to_cast);
}
template<typename type_1, typename type_2, typename type_3>
inline GenericVoid3ArgFp get_generic_void_3arg_fp
	(void (*to_cast)(type_1*, type_2*, type_3*))
{
	return reinterpret_cast<GenericVoid3ArgFp>(to_cast);
}
template<typename type_1, typename type_2, typename type_3, 
	typename type_4>
inline GenericVoid4ArgFp get_generic_void_4arg_fp
	(void (*to_cast)(type_1*, type_2*, type_3*, type_4*))
{
	return reinterpret_cast<GenericVoid4ArgFp>(to_cast);
}




// Make things even more generic
template<typename ret_type, typename type_1>
inline auto get_other_1arg_fp(ret_type (*to_cast)(type_1*))
{
	return reinterpret_cast<ret_type (*)(void*)>(to_cast);
}

template<typename ret_type, typename type_1, typename type_2>
inline auto get_other_2arg_fp(ret_type (*to_cast)(type_1*, type_2*))
{
	return reinterpret_cast<ret_type (*)(void*, void*)>(to_cast);
}


template<typename ret_type, typename type_1>
inline auto get_other_1arg_fp(ret_type (*to_cast)(const type_1*))
{
	return reinterpret_cast<ret_type (*)(const void*)>(to_cast);
}

template<typename ret_type, typename type_1, typename type_2>
inline auto get_other_2arg_fp
	(ret_type (*to_cast)(const type_1*, const type_2*))
{
	return reinterpret_cast<ret_type (*)(const void*, const void*)>
		(to_cast);
}



template<typename type_1, typename type_2>
inline auto get_generic_u32_2arg_fp(u32 (*to_cast)(type_1*, type_2*))
{
	return get_other_2arg_fp(to_cast);
}

template<typename Type>
inline auto get_qscmp_fp(int (*to_cast)(const Type*, const Type*))
{
	return get_other_2arg_fp(to_cast);
}

template<typename Type>
inline auto get_generic_void_ptr_1arg_fp(voidPtr (*to_cast)(Type*))
{
	return get_other_1arg_fp(to_cast);
}

template<typename Type>
inline auto get_generic_s16_ptr_1arg_fp(s16Ptr (*to_cast)(Type*))
{
	return get_other_1arg_fp(to_cast);
}

template<typename Type>
inline auto get_generic_vec2_s16_ptr_1arg_fp
	(Vec2S16Ptr (*to_cast)(Type*))
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


template<typename Type>
inline void generic_binary_func_backend(Type* a, Type* b,
	void (*the_fp)(Type*, Type*))
{
	generic_binary_func_shared_backend
		(const_cast<Type*>(a), const_cast<Type*>(b), 
		reinterpret_cast<GenericVoid2ArgFp>(the_fp));
}
template<typename Type>
inline void generic_binary_func_backend(const Type* a, Type* b,
	void (*the_fp)(const Type*, Type*))
{
	generic_binary_func_shared_backend
		(const_cast<Type*>(a), const_cast<Type*>(b), 
		reinterpret_cast<GenericVoid2ArgFp>(the_fp));
}
template<typename Type>
inline void generic_binary_func_backend(Type* a, const Type* b,
	void (*the_fp)(Type*, const Type*))
{
	generic_binary_func_shared_backend
		(const_cast<Type*>(a), const_cast<Type*>(b),
		reinterpret_cast<GenericVoid2ArgFp>(the_fp));
}
// Not sure I'll ever use this
template<typename Type>
inline void generic_binary_func_backend(const Type* a, const Type* b,
	void (*the_fp)(const Type*, const Type*))
{
	generic_binary_func_shared_backend
		(const_cast<Type*>(a), const_cast<Type*>(b), 
		reinterpret_cast<GenericVoid2ArgFp>(the_fp));
}


template<typename Type>
inline u32 generic_u32_func_backend(Type* a, Type* b,
	u32 (*the_fp)(Type*, Type*))
{
	return generic_u32_func_shared_backend
		(const_cast<Type*>(a), const_cast<Type*>(b), 
		reinterpret_cast<Genericu32_2ArgFp>(the_fp));
}
template<typename Type>
inline u32 generic_u32_func_backend(const Type* a, Type* b,
	u32 (*the_fp)(const Type*, Type*))
{
	return generic_u32_func_shared_backend
		(const_cast<Type*>(a), const_cast<Type*>(b), 
		reinterpret_cast<Genericu32_2ArgFp>(the_fp));
}
template<typename Type>
inline u32 generic_u32_func_backend(Type* a, const Type* b,
	u32 (*the_fp)(Type*, const Type*))
{
	return generic_u32_func_shared_backend
		(const_cast<Type*>(a), const_cast<Type*>(b), 
		reinterpret_cast<Genericu32_2ArgFp>(the_fp));
}
template<typename Type>
inline u32 generic_u32_func_backend(const Type* a, const Type* b,
	u32 (*the_fp)(const Type*, const Type*))
{
	return generic_u32_func_shared_backend
		(const_cast<Type*>(a), const_cast<Type*>(b), 
		reinterpret_cast<Genericu32_2ArgFp>(the_fp));
}



//inline void generic_copy_func_backend(void* a, const void* b, 
//	void (*copy_func)(void*, const void*))
//{
//	generic_binary_func_backend(a, b, copy_func);
//}



template<typename Type>
inline void generic_copy(Type& a, const Type& b)
{
	generic_binary_func_backend<Type>(&a, &b, 
		[](Type* a2, const Type* b2){ *a2 = *b2; });
}


template<typename Type>
inline void generic_move(Type& a, Type&& b)
{
	generic_binary_func_backend<Type>(&a, &b, 
		[](Type* a2, Type* b2){ *a2 = std::move(*b2); });
}


template<typename Type>
inline u32 generic_less(const Type& a, const Type& b)
{
	return generic_u32_func_backend<Type>(&a, &b, 
		[](const Type* a2, const Type* b2) -> u32
		{ return ((*a2) < (*b2)); });
}

}

}



#endif		// general_utility_stuff__slash__generic_funcptr_stuff_hpp
