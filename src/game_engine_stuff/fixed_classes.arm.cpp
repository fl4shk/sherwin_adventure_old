// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#include "fixed_classes.hpp"


fixed24p8 fixed24p8::guaranteed_f24p8_by_f8p8_multiplication
	( const fixed8p8& to_mul )
{
	fixed24p8 ret;
	
	s64 ret_data_s64 = (s64)data * (s64)to_mul.data;
	ret_data_s64 >>= fixed24p8::shift;
	
	ret.data = (s32)ret_data_s64;
	
	return ret;
	
}


