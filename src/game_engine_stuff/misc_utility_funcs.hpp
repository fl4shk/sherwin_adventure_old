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
first_type max_va( first_type arg_0, second_type arg_1, 
	remaining_types... remaining_args  )
{
	return max_va( max_va( arg_0, arg_1 ), remaining_args... );
}


template< typename first_type, typename second_type >
first_type min_va( const first_type& arg_0, const second_type& arg_1 )
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
first_type min_va( first_type arg_0, second_type arg_1, 
	remaining_types... remaining_args  )
{
	return min_va( min_va( arg_0, arg_1 ), remaining_args... );
}


#endif		// misc_utility_funcs_hpp
