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


#ifndef general_utility_stuff__slash__misc_utility_funcs_hpp
#define general_utility_stuff__slash__misc_utility_funcs_hpp

namespace sherwin_adventure
{

namespace misc_util
{

// Don't use weird things with this.
template<typename FirstType, typename SecondType>
FirstType max_va(const FirstType& arg_0, const SecondType& arg_1)
{
	if (arg_0 >= arg_1)
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template<typename FirstType, typename SecondType, 
	typename... RemainingTypes>
inline FirstType max_va(const FirstType& arg_0, 
	const SecondType& arg_1, RemainingTypes... remaining_args )
{
	return max_va(max_va(arg_0, arg_1), remaining_args...);
}


template<typename FirstType, typename SecondType>
inline FirstType min_va(const FirstType& arg_0, 
	const SecondType& arg_1)
{
	if (arg_0 <= arg_1)
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template<typename FirstType, typename SecondType, 
	typename... RemainingTypes>
inline FirstType min_va(const FirstType& arg_0, 
	const SecondType& arg_1, RemainingTypes... remaining_args )
{
	return min_va(min_va(arg_0, arg_1), remaining_args...);
}


template<typename Type>
inline Type custom_abs(const Type& val)
{
	if (val < static_cast<Type>(0))
	{
		return -val;
	}
	else
	{
		return val;
	}
}


template<typename Type, size_t index>
inline void __init_array_backend(Type* all_values_arr, 
	const Type& to_copy)
{
	//asm_comment("__init_array_backend() single value");
	all_values_arr[index] = to_copy;
}

template<typename Type, size_t index, typename... RemainingTypes>
inline void __init_array_backend(Type* all_values_arr, 
	const Type& first_value, const RemainingTypes&... remaining_values)
{
	__init_array_backend<Type, index>(all_values_arr, first_value);

	__init_array_backend<Type, index + 1>(all_values_arr, 
		remaining_values...);
}

template<typename Type, typename... AllTheTypes>
inline void init_array(Type* all_values_arr, 
	const AllTheTypes&...  all_the_values)
{
	__init_array_backend<Type, 0>(all_values_arr,
		all_the_values...);
}


// This has no real reason to exist
template<typename Type>
constexpr inline bool type_is_signed()
{
	return ((Type)(-1) < (Type)(0));
}


template<typename FirstType, typename SecondType>
[[gnu::noinline]]
bool cmpeq_array(FirstType* first_arr, SecondType* second_arr, 
	size_t size)
{
	if (size == 0)
	{
		return false;
	}

	for (size_t i=0; i<size; ++i)
	{
		if (first_arr[i] != second_arr[i])
		{
			return false;
		}
	}

	return true;
}


template<typename FirstType>
bool anything_matches(const FirstType& first_val)
{
	return false;
}

template<typename FirstType, typename SecondType, typename... RemArgTypes>
bool anything_matches(const FirstType& first_val, const SecondType& next, 
	RemArgTypes&&... rem_args)
{
	if (sizeof...(rem_args) == 0)
	{
		return (first_val == next);
	}
	else if (first_val == next)
	{
		return true;
	}
	else
	{
		return anything_matches(first_val, rem_args...);
	}
}


}

}



#endif		// general_utility_stuff__slash__misc_utility_funcs_hpp
