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


#ifndef subsystem_stuff_hpp
#define subsystem_stuff_hpp

#include <array>
#include <memory>

#include "../misc_includes.hpp"
#include "overlay_loader_stuff.hpp"
#include "../general_utility_stuff/free_list_allocator_base_class.hpp"
#include <experimental/propagate_const>

namespace sherwin_adventure
{
namespace game_engine
{

class SubsystemAllocator;

// Abstract base class for a so-called "subsystem" which is an
// organizational tool to allow connecting together pieces of the game
// engine.
class SubsystemBase : public FreeListAllocContainedBase
{
protected:		// variables
	// Pointer to implementation
	void* __pimpl;

	//std::experimental::propagate_const<std::unique_ptr<ImplName>> __pimpl;

public:		// functions
	SubsystemBase()
	{
		//init_pimpl();
	}

	SubsystemBase(s32 s_arr_index)
		: FreeListAllocContainedBase(s_arr_index)
	{
		//init_pimpl();
	}

	virtual ~SubsystemBase()
	{
		//erase_pimpl();
	}

	inline void* operator new (size_t size, 
		SubsystemAllocator& subsystem_allocator);


	// Derived classes should create their own implementation of the
	// iterate() virtual member function
	virtual void iterate()
	{
	}

protected:		// functions
	//template<typename Type>
	//inline std::unique_ptr<Type>* impl_uptr()
	//{
	//	return reinterpret_cast<std::unique_ptr<Type>*>(__pimpl);
	//}
	template<typename Type>
	inline Type* get_pimpl_as()
	{
		return reinterpret_cast<Type*>(__pimpl);
	}

	template<typename Type>
	void init_pimpl()
	{
		//__pimpl = new Type();
		//__pimpl = new std::unique_ptr<Type>();
		__pimpl = new Type();
	}

	template<typename Type>
	void erase_pimpl()
	{
		delete get_pimpl_as<Type>();
	}
	

} __attribute__((_align4));

template<typename ImplType>
class Subsystem : public SubsystemBase
{
public:		// classes
	//class ImplType
	//{
	//public:		// variables
	//	static constexpr size_t arr_size = 8;
	//	u32 arr[arr_size];
	//} __attribute__((_align4));


public:		// functions
	inline Subsystem()
	{
	}
	inline Subsystem(s32 s_arr_index)
		: SubsystemBase(s_arr_index)
	{
		init_pimpl<ImplType>();
	}
	virtual inline ~Subsystem()
	{
		erase_pimpl<ImplType>();
	}

	virtual void iterate()
	{
	}

protected:		// functions
	inline auto& pimpl()
	{
		return *get_pimpl_as<ImplType>();
	}

} __attribute__((_align4));



class SubsystemAllocator : public FreeListAllocatorBase<SubsystemBase>
{
public:		// functions
	SubsystemAllocator(SubsystemBase* s_arr, s16* s_free_list_arr, 
		size_t s_size);

protected:		// functions
	const char* __bad_alloc_str() const
	{
		static const char ret[] = "BadAllocSubsys";
		return ret;
	}
	const char* __none_free_str() const
	{
		static const char ret[] = "SubsysNoneFree";
		return ret;
	}
	const char* __cant_push_str() const
	{
		static const char ret[] = "Can'tPushSubsys";
		return ret;
	}

} __attribute__((_align4));


void* SubsystemBase::operator new (size_t size, 
	SubsystemAllocator& subsystem_allocator)
{
	return subsystem_allocator.allocate();
}


}
}

 
//class HasPimpl
//{
//public:		// classes
//	class Impl;
//
//protected:		// variables
//	std::experimental::propagate_const<std::unique_ptr<Impl>> __pimpl;
//
//public:		// functions
//	HasPimpl();
//	virtual ~HasPimpl();
//
//	gen_getter_by_ref(pimpl);
//
//
//} __attribute__((_align4));

#endif		// subsystem_stuff_hpp
