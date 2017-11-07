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


#ifndef free_list_allocator_base_class_hpp
#define free_list_allocator_base_class_hpp

#include "../misc_includes.hpp"
#include "stack_classes.hpp"
#include "../game_engine_stuff/halt_stuff.hpp"
#include "debug_vars.hpp"

namespace sherwin_adventure
{
namespace containers
{

class FreeListAllocContainedBase
{
public:		// variables
	static constexpr s32 blank_index = -1;

protected:		// variables

	s32 __arr_index = blank_index;

public:		// functions
	inline FreeListAllocContainedBase()
		: __arr_index(blank_index)
	{
	}
	inline FreeListAllocContainedBase(s32 s_arr_index)
		: __arr_index(s_arr_index)
	{
	}

	virtual ~FreeListAllocContainedBase()
	{
	}

	//void* operator new (size_t size, Allocator& allocator);

	gen_getter_and_setter_by_val(arr_index);
};


// Base class for an allocator using a ExtFreeList
template<typename Type>
class FreeListAllocatorBase : public ArrayHelper<Type>
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
		: Base(s_arr, s_size), __free_list(s_free_list_arr, s_size)
	{
	}


	// Derived classes can override these in case there's special stuff to
	// be done (like for sprite allocation/deallocation)
	void* allocate() __attribute__((noinline))
	{
		ASM_COMMENT("if (can_pop_index()");
		//if (can_pop_index())
		if (free_list().can_pop())
		{
			//int n_arr_index = the_sa_free_list_backend.peek_top();
			int n_arr_index = free_list().peek_top();
			//Sprite& ret = at(n_arr_index);
			auto& ret = Base::at(n_arr_index);


			//ret.the_arr_index = n_arr_index;
			__set_instance_arr_index(ret, n_arr_index);

			//the_sa_free_list_backend.pop();
			free_list().pop();

			//if (ret.the_sprite_type != StDefault)
			if (__alloc_test_bad(ret))
			{
				//ASM_COMMENT("BadSprite");
				//DebugArrGroup::write_str_and_inc("BadSprite");
				DebugArrGroup::write_str_and_inc(__bad_alloc_str());
				game_engine::halt();
			}

			return (void*)(&ret);
		}

		//DebugArrGroup::write_str_and_inc("NoFreeSprite");
		DebugArrGroup::write_str_and_inc(__none_free_str());
		game_engine::halt();

		//return NULL;
		for (;;)
		{
		}
	}
	void deallocate(Type& to_dealloc) __attribute__((noinline))
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
			DebugArrGroup::write_str_and_inc(__cant_push_str());
			game_engine::halt();
		}


		//the_sa_free_list_backend.push(the_sprite.the_arr_index);
		//the_sprite.the_arr_index = -1;

		free_list().push(__get_instance_arr_index(to_dealloc));
		__set_instance_arr_index(to_dealloc, 
			__get_instance_blank_arr_index(to_dealloc));
	}

protected:		// functions
	gen_getter_by_ref(free_list);

	virtual inline void __set_instance_arr_index(Type& instance, 
		int some_arr_index)
	{
		//instance.arr_index = some_arr_index;
		instance.set_arr_index(some_arr_index);
	}
	virtual inline int __get_instance_arr_index(const Type& instance) const
	{
		return instance.arr_index();
	}
	virtual inline s32 __get_instance_blank_arr_index(const Type& instance)
		const
	{
		return instance.blank_index;
	}



	// Things for derived classes to implement
	virtual bool __alloc_test_bad(Type& ret)
	{
		//return (the_sprite.the_sprite_type != StDefault);
		return false;
	}
	virtual bool __dealloc_test_bad(Type& to_dealloc)
	{
		//return (the_sprite.the_sprite_type == StDefault);
		return false;
	}
	virtual void __dealloc_middle_part(Type& to_dealloc)
	{
	}
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
	//		the_sprite.the_sprite_ipg = NULL;
	//	}

	//	//u32 old_vram_chunk_index = the_sprite.get_vram_chunk_index();
	//	//
	//	//*the_sprite = Sprite();
	//	//the_sprite.shared_constructor_code();
	//	//*the_sprite = Sprite(the_sprite.get_vram_chunk_index());
	//}

	virtual const char* __bad_alloc_str() const
	{
		static const char ret[] = "BadAlloc";
		return ret;
	}

	virtual const char* __none_free_str() const
	{
		static const char ret[] = "NoneFree";
		return ret;
	}

	virtual const char* __cant_push_str() const
	{
		static const char ret[] = "Can'tPush";
		return ret;
	}

} __attribute__((_align4));

}
}


#endif		// free_list_allocator_base_class_hpp
