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


#include "generic_funcptr_stuff.hpp"


extern "C"
{

void generic_binary_func_shared_backend( void* a, void* b,
	generic_void_2arg_fp the_fp )
{
	(*the_fp)( a, b );
}

u32 generic_u32_func_shared_backend( void* a, void* b,
	generic_u32_2arg_fp the_fp )
{
	return (*the_fp)( a, b );
}

}
