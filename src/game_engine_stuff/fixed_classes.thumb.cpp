#include "fixed_classes.hpp"


fixed24p8 f24p8_div_by_f8p8( const fixed24p8& num, const fixed8p8& den )
{
	if ( den.data == 0 || den.data == 1 )
	{
		return { num.data };
	}
	
	s32 ret_data;
	
	bool numerator_is_negative = ( num.data < 0 );
	bool denominator_is_negative = ( den.data < 0 );
	
	s32 temp1, temp2;
	
	if ( numerator_is_negative )
	{
		temp1 = -num.data;
	}
	else
	{
		temp1 = num.data;
	}
	
	if ( denominator_is_negative )
	{
		temp2 = -den.data;
	}
	else
	{
		temp2 = den.data;
	}
	
	u64 udiv_output = lut_udiv( temp1, temp2 );
	
	//ret_data = ( udiv_output >> 24 ) * ( numerator_is_negative ? -1 : 1 )
	//	* ( denominator_is_negative ? -1 : 1 );
	
	ret_data = ( udiv_output >> 24 ) * ( numerator_is_negative ? -1 : 1 )
		* ( denominator_is_negative ? -1 : 1 );
	
	return { ret_data };
}





