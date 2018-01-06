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

#ifndef general_utility_stuff__slash__gen_getter_setter_defines_hpp
#define general_utility_stuff__slash__gen_getter_setter_defines_hpp


// Getters

#ifndef gen_generic_getter_by_val
// By value
#define gen_generic_getter_by_val(prefix, suffix) \
inline decltype(prefix##_##suffix) suffix() const \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_getter_by_val
// By value
#define gen_getter_by_val(suffix) \
gen_generic_getter_by_val(_, suffix)
#endif



#ifndef gen_generic_getter_by_con_ref
// By constant reference
#define gen_generic_getter_by_con_ref(prefix, suffix) \
inline const decltype(prefix##_##suffix)& suffix() const \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_getter_by_con_ref
// By constant reference
#define gen_getter_by_con_ref(suffix) \
gen_generic_getter_by_con_ref(_, suffix)
#endif



#ifndef gen_generic_getter_by_ref
// By reference
#define gen_generic_getter_by_ref(prefix, suffix) \
inline decltype(prefix##_##suffix)& suffix() \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_getter_by_ref
// By reference
#define gen_getter_by_ref(suffix) \
gen_generic_getter_by_ref(_, suffix)
#endif



#ifndef gen_static_generic_getter_by_val
// By value
#define gen_static_generic_getter_by_val(prefix, suffix) \
static inline decltype(prefix##_##suffix) suffix() const \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_static_getter_by_val
// By value
#define gen_static_getter_by_val(suffix) \
gen_static_generic_getter_by_val(_, suffix)
#endif



#ifndef gen_static_generic_getter_by_con_ref
// By constant reference
#define gen_static_generic_getter_by_con_ref(prefix, suffix) \
static inline const decltype(prefix##_##suffix)& suffix() const \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_static_getter_by_con_ref
// By constant reference
#define gen_static_getter_by_con_ref(suffix) \
gen_static_generic_getter_by_con_ref(_, suffix)
#endif



#ifndef gen_static_generic_getter_by_ref
// By reference
#define gen_static_generic_getter_by_ref(prefix, suffix) \
static inline decltype(prefix##_##suffix)& suffix() \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_static_getter_by_ref
// By reference
#define gen_static_getter_by_ref(suffix) \
gen_static_generic_getter_by_ref(_, suffix)
#endif


// Setters

#ifndef gen_generic_setter_by_val
// By value
#define gen_generic_setter_by_val(prefix, suffix) \
inline decltype(prefix##_##suffix) set_##suffix(decltype(prefix##_##suffix) to_copy) \
{ \
	prefix##_##suffix = to_copy; \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_setter_by_val
// By value
#define gen_setter_by_val(suffix) \
gen_generic_setter_by_val(_, suffix)
#endif



#ifndef gen_generic_setter_by_con_ref
// By const reference
#define gen_generic_setter_by_con_ref(prefix, suffix) \
inline const decltype(prefix##_##suffix)& set_##suffix \
	(const decltype(prefix##_##suffix)& to_copy) \
{ \
	prefix##_##suffix = to_copy; \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_setter_by_con_ref
// By const reference
#define gen_setter_by_con_ref(suffix) \
gen_generic_setter_by_con_ref(_, suffix)
#endif



#ifndef gen_generic_setter_by_rval_ref
// By rvalue reference
#define gen_generic_setter_by_rval_ref(prefix, suffix) \
inline const decltype(prefix##_##suffix)& set_##suffix \
	(decltype(prefix##_##suffix)&& to_move) \
{ \
	prefix##_##suffix = std::move(to_move); \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_setter_by_rval_ref
// By rvalue reference
#define gen_setter_by_rval_ref(suffix) \
gen_generic_setter_by_rval_ref(_, suffix)
#endif



#ifndef gen_static_generic_setter_by_val
// By value
#define gen_static_generic_setter_by_val(prefix, suffix) \
static inline decltype(prefix##_##suffix) set_##suffix(decltype(prefix##_##suffix) to_copy) \
{ \
	prefix##_##suffix = to_copy; \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_static_setter_by_val
// By value
#define gen_static_setter_by_val(suffix) \
gen_static_generic_setter_by_val(_, suffix)
#endif



#ifndef gen_static_generic_setter_by_con_ref
// By const reference
#define gen_static_generic_setter_by_con_ref(prefix, suffix) \
static inline const decltype(prefix##_##suffix)& set_##suffix \
	(const decltype(prefix##_##suffix)& to_copy) \
{ \
	prefix##_##suffix = to_copy; \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_static_setter_by_con_ref
// By const reference
#define gen_static_setter_by_con_ref(suffix) \
gen_static_generic_setter_by_con_ref(_, suffix)
#endif



#ifndef gen_static_generic_setter_by_rval_ref
// By rvalue reference
#define gen_static_generic_setter_by_rval_ref(prefix, suffix) \
static inline const decltype(prefix##_##suffix)& set_##suffix \
	(decltype(prefix##_##suffix)&& to_move) \
{ \
	prefix##_##suffix = std::move(to_move); \
	return prefix##_##suffix; \
}
#endif

#ifndef gen_static_setter_by_rval_ref
// By rvalue reference
#define gen_static_setter_by_rval_ref(suffix) \
gen_static_generic_setter_by_rval_ref(_, suffix)
#endif



#define gen_getter_and_setter_by_con_ref(stuff) \
	gen_getter_by_con_ref(stuff) \
	gen_setter_by_con_ref(stuff)


#define gen_getter_and_setter_by_val(stuff) \
	gen_getter_by_val(stuff) \
	gen_setter_by_val(stuff)

#endif		// general_utility_stuff__slash__gen_getter_setter_defines_hpp
