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


#ifndef general_utility_stuff__slash__free_list_allocator_base_class_hpp
#define general_utility_stuff__slash__free_list_allocator_base_class_hpp

#include "../misc_includes.hpp"
#include "stack_classes.hpp"
#include "../game_engine_stuff/error_handler_stuff.hpp"
#include "debug_vars.hpp"

namespace sherwin_adventure
{
namespace containers
{

template<typename Allocator>
class FreeListAllocContainedBase
{
public:		// variables
	static constexpr s32 blank_index = -1;

protected:		// variables
	//s32 __arr_index = blank_index;
	s32 __arr_index;

public:		// functions
	// The following commented-out constructor was the source of a bug that
	// lead to the array index being set back to blank_index despite what
	// the allocator did.
	//inline FreeListAllocContainedBase()
	//	: __arr_index(blank_index)
	//{
	//}
	inline FreeListAllocContainedBase()
	{
	}
	inline FreeListAllocContainedBase(s32 s_arr_index)
		: __arr_index(s_arr_index)
	{
	}

	virtual ~FreeListAllocContainedBase()
	{
	}

	//inline void* operator new (size_t size, Allocator& allocator)
	//{
	//	return allocator.allocate();
	//}

	gen_getter_and_setter_by_val(arr_index);
};

// Base class for a one-object-at-a-time allocator using an
// ExtAllocFreeList.
// 
// This is primarily intended for allocating fixed-size objects from a
// fixed-size array.  It isn't recommended as a general-purpose allocator.
// 
// The intended types of objects to be allocated this way are things like
// Sprite's and SaListNode's.
//
// 
// With this method, it is possible to have the array of objects be an
// array of Base class instances, which is useful if one wants to use C++
// polymorphism and actually allocate classes derived from Base using this
// method.  C++'s placement new feature is used for this purpose.
// 
// However, this won't work for polymorphic types where derived classes are
// supposed to be a different size from the Base class.  This is of
// particular importance for Sprite's, which will need to have every
// variable used by derived types be put into the Base class.
// 
// I like to put a few small general-purpose arrays of data (perhaps with
// word-sized elements) that derived types can use into the Base class.
// These arrays are useful for holding object state that must be kept
// around across multiple frames.  The catch is that objects that don't use
// these arrays, or only use parts of them, will still have space allocated
// for those arrays.  This is not a huge deal for Sprite's in particular
// because the array(s) to allocate Sprite's from is (are) not very large.
template<typename Type>
class _alignas_regular FreeListAllocatorBase : public ArrayHelper<Type>
{
public:		// typedefs
	typedef ArrayHelper<Type> Base;

protected:		// variables
	ExtAllocFreeList __free_list;

public:		// functions
	inline FreeListAllocatorBase()
	{
	}

	inline FreeListAllocatorBase(Type* s_arr, s16* s_free_list_arr, 
		size_t s_size)
	{
		init(s_arr, s_free_list_arr, s_size);
	}
	inline void init(Type* s_arr, s16* s_free_list_arr, size_t s_size)
	{
		Base::init(s_arr, s_size);
		__free_list.init(s_free_list_arr, s_size);
	}

	[[gnu::noinline]]
	Type* attempt_allocate()
	{
		//ASM_COMMENT("if (can_pop_index()");
		//if (can_pop_index())
		if (free_list().can_pop())
		{
			//int n_arr_index = the_sa_free_list_backend.peek_top();
			const int n_arr_index = free_list().peek_top();
			//Sprite& ret = at(n_arr_index);
			auto* ret = &Base::at(n_arr_index);


			//ret.the_arr_index = n_arr_index;
			__set_instance_arr_index(ret, n_arr_index);

			//the_sa_free_list_backend.pop();
			free_list().pop();

			//if (ret.the_sprite_type != StDefault)
			if (__alloc_test_bad(ret))
			{
				//ASM_COMMENT("BadSprite");
				//DebugArrGroup::write_str_and_inc("BadSprite");

				//DebugArrGroup::write_str_and_inc(__bad_alloc_str());
				//game_engine::halt();
				game_engine::err(__bad_alloc_str());
			}

			//return (void*)(ret);
			return ret;
		}

		////DebugArrGroup::write_str_and_inc("NoFreeSprite");
		////DebugArrGroup::write_str_and_inc(__none_free_str());
		////game_engine::halt();
		//game_engine::err(__none_free_str());

		////return nullptr;
		//for (;;)
		//{
		//}
		//game_engine::warn(__none_free_str());
		return nullptr;
	}

	Type* allocate_or_err()
	{
		auto ret = attempt_allocate();

		if (ret == nullptr)
		{
			game_engine::err(__none_free_str());
		}

		return ret;
	}


	// Useful for Sprite's, sometimes
	[[gnu::noinline]]
	Type* allocate_forcefully(void* condition)
	{
		auto ret = attempt_allocate();

		if (ret == nullptr)
		{
			auto other = find_lesser(condition);

			if (other == nullptr)
			{
				game_engine::err("FreeListAllocatorBase"
					"::allocate_forcefully():  Eek!");
			}

			deallocate(other);

			return attempt_allocate();
		}

		return ret;
	}

	[[gnu::noinline]]
	void deallocate(Type* to_dealloc)
	{
		//if (the_sprite.the_sprite_type == StDefault)
		if (__dealloc_test_bad(to_dealloc))
		{
			//DebugArrGroup::write_str_and_inc("SadsSprStDefault");
			//game_engine::halt();
			return;
		}

		//if (!can_push_index())
		if (!free_list().can_push())
		{
			//DebugArrGroup::write_str_and_inc("SadsCan'tPush");
			//DebugArrGroup::write_str_and_inc(__cant_push_str());
			//game_engine::halt();
			game_engine::err(__cant_push_str());
		}

		__dealloc_middle_part(to_dealloc);

		//the_sa_free_list_backend.push(the_sprite.the_arr_index);
		//the_sprite.the_arr_index = -1;

		free_list().push(__get_instance_arr_index(to_dealloc));
		__set_instance_arr_index(to_dealloc, 
			__get_instance_blank_arr_index(to_dealloc));

		to_dealloc->~Type();
	}

protected:		// functions
	gen_getter_by_ref(free_list);

	virtual inline void __set_instance_arr_index(Type* instance, 
		int some_arr_index)
	{
		//instance.arr_index = some_arr_index;
		instance->set_arr_index(some_arr_index);
	}
	virtual inline int __get_instance_arr_index(Type* instance) const
	{
		return instance->arr_index();
	}
	virtual inline s32 __get_instance_blank_arr_index(Type* instance) const
	{
		return instance->blank_index;
	}



	// Things for derived classes to implement
	virtual bool __alloc_test_bad(Type* ret)
	{
		//return (the_sprite.the_sprite_type != StDefault);
		return false;
	}
	virtual bool __dealloc_test_bad(Type* to_dealloc)
	{
		//return (the_sprite.the_sprite_type == StDefault);
		return false;
	}
	virtual void __dealloc_middle_part(Type* to_dealloc)
	{
	}

	// Derived classes that use allocate_forcefully() **should** override
	// this function!
	virtual Type* find_lesser(void* condition)
	{
		return nullptr;
	}

	//virtual void __dealloc_middle_part(Type& to_dealloc)
	//{
	//	the_sprite.the_sprite_type = StDefault;

	//	// Some sprites are spawned in from something other than the Level
	//	// data and DON'T HAVE a the_sprite_ipg
	//	if (the_sprite.the_sprite_ipg)
	//	{
	//		if (the_sprite.the_sprite_ipg->spawn_state == sss_active)
	//		{
	//			the_sprite.the_sprite_ipg->spawn_state = sss_not_active;
	//		}
	//		the_sprite.the_sprite_ipg = nullptr;
	//	}

	//	//u32 old_vram_chunk_index = the_sprite.get_vram_chunk_index();
	//	//
	//	//*the_sprite = Sprite();
	//	//the_sprite.shared_constructor_code();
	//	//*the_sprite = Sprite(the_sprite.get_vram_chunk_index());
	//}

	virtual const char* __bad_alloc_str() const
	{
		static const char ret[] = "FreeListAllocatorBase:  BadAlloc Eek!";
		return ret;
	}

	virtual const char* __none_free_str() const
	{
		static const char ret[] = "FreeListAllocatorBase:  NoneFree Eek!";
		return ret;
	}

	virtual const char* __cant_push_str() const
	{
		static const char ret[] = "FreeListAllocatorBase:  Can'tPush Eek!";
		return ret;
	}

};

}
}


#endif		// general_utility_stuff__slash__free_list_allocator_base_class_hpp
