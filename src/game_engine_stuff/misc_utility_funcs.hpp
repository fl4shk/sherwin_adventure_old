#ifndef misc_utility_funcs_hpp
#define misc_utility_funcs_hpp


template< typename type >
inline const type& max3( const type& a, const type& b, const type& c )
{
	if ( a >= b && a >= c )
	{
		return a;
	}
	else if ( b >= c )
	{
		return b;
	}
	else
	{
		return c;
	}
}


#endif		// misc_utility_funcs_hpp
