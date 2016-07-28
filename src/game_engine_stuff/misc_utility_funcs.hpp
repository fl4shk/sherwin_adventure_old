// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
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


#ifndef misc_utility_funcs_hpp
#define misc_utility_funcs_hpp

template< typename type >
inline const type& max2( const type& arg_0, const type& arg_1 )
{
	if ( arg_0 >= arg_1 )
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template< typename type >
inline const type& max3( const type& arg_0, const type& arg_1, 
	const type& arg_2 )
{
	if ( arg_0 >= arg_1 && arg_0 >= arg_2 )
	{
		return arg_0;
	}
	else if ( arg_1 >= arg_2 )
	{
		return arg_1;
	}
	else
	{
		return arg_2;
	}
}


// Don't use weird things with this.
template< typename first_type, typename second_type >
first_type max_va( const first_type& arg_0, const second_type& arg_1 )
{
	if ( arg_0 >= arg_1 )
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template< typename first_type, typename second_type, 
	typename... remaining_types >
inline first_type max_va( const first_type& arg_0, 
	const second_type& arg_1, remaining_types... remaining_args  )
{
	return max_va( max_va( arg_0, arg_1 ), remaining_args... );
}


template< typename first_type, typename second_type >
inline first_type min_va( const first_type& arg_0, 
	const second_type& arg_1 )
{
	if ( arg_0 <= arg_1 )
	{
		return arg_0;
	}
	else
	{
		return arg_1;
	}
}

template< typename first_type, typename second_type, 
	typename... remaining_types >
inline first_type min_va( const first_type& arg_0, 
	const second_type& arg_1, remaining_types... remaining_args  )
{
	return min_va( min_va( arg_0, arg_1 ), remaining_args... );
}


template< typename type >
inline type custom_abs( const type& val )
{
	if ( val < static_cast<type>(0) )
	{
		return -val;
	}
	else
	{
		return val;
	}
}


void halt();


#endif		// misc_utility_funcs_hpp
