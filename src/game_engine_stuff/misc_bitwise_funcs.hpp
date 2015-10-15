#ifndef misc_bitwise_funcs_hpp
#define misc_bitwise_funcs_hpp

#include "misc_types.hpp"



template< typename type >
inline void clear_bits( type& to_clear, u32 mask )
{
	to_clear &= ~mask;
}

template< typename type >
inline void set_bits( type& to_set, u32 mask )
{
	to_set |= mask;
}

template< typename type >
inline constexpr type get_bits( type to_get_from, u32 mask, u32 shift=0 )
{
	return ( ( to_get_from & mask ) >> shift );
}

template< typename type >
inline void clear_and_set_bits( type& to_change, u32 clear_mask,
	u32 set_mask )
{
	to_change &= ~clear_mask;
	to_change |= set_mask;
}




#endif		// misc_bitwise_funcs_hpp
