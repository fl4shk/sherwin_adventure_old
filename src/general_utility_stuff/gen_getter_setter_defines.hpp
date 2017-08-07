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

#ifndef gen_getter_setter_defines_hpp
#define gen_getter_setter_defines_hpp


// Getters

#ifndef GEN_GENERIC_GETTER_BY_VAL
// By value
#define GEN_GENERIC_GETTER_BY_VAL(prefix, suffix) \
inline decltype(prefix##_##suffix) suffix() const \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_GETTER_BY_VAL
// By value
#define GEN_GETTER_BY_VAL(suffix) \
GEN_GENERIC_GETTER_BY_VAL(internal, suffix)
#endif



#ifndef GEN_GENERIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_GENERIC_GETTER_BY_CON_REF(prefix, suffix) \
inline const decltype(prefix##_##suffix)& suffix() const \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_GETTER_BY_CON_REF
// By constant reference
#define GEN_GETTER_BY_CON_REF(suffix) \
GEN_GENERIC_GETTER_BY_CON_REF(internal, suffix)
#endif



#ifndef GEN_GENERIC_GETTER_BY_REF
// By reference
#define GEN_GENERIC_GETTER_BY_REF(prefix, suffix) \
inline decltype(prefix##_##suffix)& suffix() \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_GETTER_BY_REF
// By reference
#define GEN_GETTER_BY_REF(suffix) \
GEN_GENERIC_GETTER_BY_REF(internal, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_VAL
// By value
#define GEN_STATIC_GENERIC_GETTER_BY_VAL(prefix, suffix) \
static inline decltype(prefix##_##suffix) suffix() const \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_VAL
// By value
#define GEN_STATIC_GETTER_BY_VAL(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_VAL(internal, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_STATIC_GENERIC_GETTER_BY_CON_REF(prefix, suffix) \
static inline const decltype(prefix##_##suffix)& suffix() const \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_CON_REF
// By constant reference
#define GEN_STATIC_GETTER_BY_CON_REF(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_CON_REF(internal, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_GETTER_BY_REF
// By reference
#define GEN_STATIC_GENERIC_GETTER_BY_REF(prefix, suffix) \
static inline decltype(prefix##_##suffix)& suffix() \
{ \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_STATIC_GETTER_BY_REF
// By reference
#define GEN_STATIC_GETTER_BY_REF(suffix) \
GEN_STATIC_GENERIC_GETTER_BY_REF(internal, suffix)
#endif


// Setters

#ifndef GEN_GENERIC_SETTER_BY_VAL
// By value
#define GEN_GENERIC_SETTER_BY_VAL(prefix, suffix) \
inline decltype(prefix##_##suffix) set_##suffix(decltype(prefix##_##suffix) to_copy) \
{ \
	prefix##_##suffix = to_copy; \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_SETTER_BY_VAL
// By value
#define GEN_SETTER_BY_VAL(suffix) \
GEN_GENERIC_SETTER_BY_VAL(internal, suffix)
#endif



#ifndef GEN_GENERIC_SETTER_BY_CON_REF
// By const reference
#define GEN_GENERIC_SETTER_BY_CON_REF(prefix, suffix) \
inline const decltype(prefix##_##suffix)& set_##suffix \
	(const decltype(prefix##_##suffix)& to_copy) \
{ \
	prefix##_##suffix = to_copy; \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_SETTER_BY_CON_REF
// By const reference
#define GEN_SETTER_BY_CON_REF(suffix) \
GEN_GENERIC_SETTER_BY_CON_REF(internal, suffix)
#endif



#ifndef GEN_GENERIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_GENERIC_SETTER_BY_RVAL_REF(prefix, suffix) \
inline const decltype(prefix##_##suffix)& set_##suffix \
	(decltype(prefix##_##suffix)&& to_move) \
{ \
	prefix##_##suffix = std::move(to_move); \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_SETTER_BY_RVAL_REF(suffix) \
GEN_GENERIC_SETTER_BY_RVAL_REF(internal, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_SETTER_BY_VAL
// By value
#define GEN_STATIC_GENERIC_SETTER_BY_VAL(prefix, suffix) \
static inline decltype(prefix##_##suffix) set_##suffix(decltype(prefix##_##suffix) to_copy) \
{ \
	prefix##_##suffix = to_copy; \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_VAL
// By value
#define GEN_STATIC_SETTER_BY_VAL(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_VAL(internal, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_SETTER_BY_CON_REF
// By const reference
#define GEN_STATIC_GENERIC_SETTER_BY_CON_REF(prefix, suffix) \
static inline const decltype(prefix##_##suffix)& set_##suffix \
	(const decltype(prefix##_##suffix)& to_copy) \
{ \
	prefix##_##suffix = to_copy; \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_CON_REF
// By const reference
#define GEN_STATIC_SETTER_BY_CON_REF(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_CON_REF(internal, suffix)
#endif



#ifndef GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF(prefix, suffix) \
static inline const decltype(prefix##_##suffix)& set_##suffix \
	(decltype(prefix##_##suffix)&& to_move) \
{ \
	prefix##_##suffix = std::move(to_move); \
	return prefix##_##suffix; \
}
#endif

#ifndef GEN_STATIC_SETTER_BY_RVAL_REF
// By rvalue reference
#define GEN_STATIC_SETTER_BY_RVAL_REF(suffix) \
GEN_STATIC_GENERIC_SETTER_BY_RVAL_REF(internal, suffix)
#endif

#endif		// gen_getter_setter_defines_hpp
