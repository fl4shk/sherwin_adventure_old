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


#include "profiling_stuff.hpp"
#include "../general_utility_stuff/debug_vars.hpp"
//#include "../borrowed_stuff/nano-mallocr.hpp"

#include <stdlib.h>


namespace sherwin_adventure
{

namespace gba
{

//template<typename Type>
//void allocate_arr_with_malloc(Type*& ret, size_t num_elems) 
//	[[gnu::noinline]];


template<typename Type>
inline void allocate_arr_with_malloc(Type*& to_allocate, 
	size_t num_elems) 
{
	to_allocate = static_cast<Type*>(malloc(num_elems * sizeof(Type)));
}
template<typename Type>
inline void deallocate_arr_with_free(Type*& to_deallocate)
{
	free(to_deallocate);
}

//template<typename Type>
//inline void allocate_arr_with_nano_malloc(Type*& to_allocate, 
//	size_t num_elems) 
//{
//	to_allocate = static_cast<Type*>(nano_malloc(num_elems 
//		* sizeof(Type)));
//}
//template<typename Type>
//inline void deallocate_arr_with_nano_free(Type*& to_deallocate)
//{
//	nano_free(to_deallocate);
//}

//static const size_t temp_debug_arr_size = 2000;
//u32 temp_debug_arr_for_new[temp_debug_arr_size];
//u32 temp_debug_arr_for_delete[temp_debug_arr_size];
//u32 temp_debug_arr_for_malloc[temp_debug_arr_size];
//u32 temp_debug_arr_for_free[temp_debug_arr_size];
//u32 temp_debug_arr_for_nano_malloc[temp_debug_arr_size];
//u32 temp_debug_arr_for_nano_free[temp_debug_arr_size];
//int* temp_debug_arr_of_pointers[temp_debug_arr_size];

//int* temp_debug_pointer;

void profile_dynamic_allocations(size_t num_elems)
{
	//for (u32 i=0; i<temp_debug_arr_size; ++i)
	//{
	//	profile_start();

	//	temp_debug_arr_of_pointers[i] = new int[num_elems];

	//	temp_debug_arr_for_new[i] = profile_stop();
	//}

	//for (u32 i=0; i<temp_debug_arr_size; ++i)
	//{
	//	profile_start();

	//	delete[] temp_debug_arr_of_pointers[i];

	//	temp_debug_arr_for_delete[i] = profile_stop();
	//}


	//for (u32 i=0; i<temp_debug_arr_size; ++i)
	//{
	//	profile_start();

	//	allocate_arr_with_malloc(temp_debug_arr_of_pointers[i], 
	//		num_elems);

	//	temp_debug_arr_for_malloc[i] = profile_stop();
	//}

	//for (u32 i=0; i<temp_debug_arr_size; ++i)
	//{
	//	profile_start();

	//	deallocate_arr_with_free(temp_debug_arr_of_pointers[i]);

	//	temp_debug_arr_for_free[i] = profile_stop();
	//}

	////for (u32 i=0; i<temp_debug_arr_size; ++i)
	////{
	////	profile_start();
	////
	////	allocate_arr_with_nano_malloc(temp_debug_arr_of_pointers[i], 
	////		num_elems);
	////
	////	temp_debug_arr_for_nano_malloc[i] = profile_stop();
	////}
	////
	////for (u32 i=0; i<temp_debug_arr_size; ++i)
	////{
	////	profile_start();
	////
	////	deallocate_arr_with_nano_free(temp_debug_arr_of_pointers[i]);
	////
	////	temp_debug_arr_for_nano_free[i] = profile_stop();
	////}
}

}

}

