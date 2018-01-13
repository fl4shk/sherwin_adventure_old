// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2018 by Andy Clark (FL4SHK).
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


#ifndef general_utility_stuff__slash__task_stuff_hpp
#define general_utility_stuff__slash__task_stuff_hpp

#include "../general_utility_stuff/misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "misc_utility_funcs.hpp"
#include "range_funcs.hpp"

namespace sherwin_adventure
{

namespace misc_util
{

enum class TaskPriority : s32
{
	tp_0,
	tp_1,
	tp_2,
	tp_3,
	tp_4,
	tp_5,
	tp_6,
	tp_7,

	lim_tp,
} _ALIGNAS_REGULAR;


inline TaskPriority operator - (TaskPriority the_tp, 
	TaskPriority to_sub)
{
	return the_tp - to_sub;
}
inline TaskPriority operator - (TaskPriority the_tp, 
	s32 to_sub)
{
	return the_tp - to_sub;
}

inline TaskPriority clamp_task_prio(TaskPriority to_clamp)
{
	return clamp_to_range<TaskPriority>(TaskPriority::tp_0, 
		TaskPriority::lim_tp, to_clamp);
}

class _alignas_regular Task
{
public:		// typedefs
	typedef void (*task_funcptr)();

protected:		// variables
	TaskPriority the_task_prio = TaskPriority::tp_0;
	task_funcptr func = nullptr;

public:		// functions
	inline Task()
	{
	}
	inline Task(TaskPriority s_the_task_prio, task_funcptr s_func) 
		: the_task_prio(clamp_task_prio(s_the_task_prio)),
		func(s_func)
	{
	}

	inline TaskPriority get_task_prio() const
	{
		return the_task_prio;
	}
	inline void set_task_prio(TaskPriority n_the_task_prio)
	{
		the_task_prio = clamp_task_prio(n_the_task_prio);
	}


	// func stuff
	inline bool has_func() const
	{
		return (func != nullptr);
	}
	inline task_funcptr get_func() const
	{
		return func;
	}
	inline void set_func(task_funcptr s_func)
	{
		func = s_func;
	}
	inline void erase_func()
	{
		func = nullptr;
	}



	inline void operator () ()
	{
		(*func)();
	}


};

}

}

#endif		// general_utility_stuff__slash__task_stuff_hpp
