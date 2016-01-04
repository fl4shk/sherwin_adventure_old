// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andy Clark (FL4SHK).
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


#include "coll_box_class.hpp"
#include "debug_vars.hpp"


int coll_box_intersects_now( const coll_box& a, const coll_box& b )
{
	//return !( ( b.left().data + 1 ) > ( a.right().data - 1 )
	//	|| ( b.right().data - 1 ) < ( a.left().data + 1 )
	//	|| ( b.top().data + 1 ) > ( a.bot().data - 1 )
	//	|| ( b.bot().data - 1 ) < ( a.top().data + 1 ) );
	
	return !( b.left() > a.right()
		|| b.right() < a.left()
		|| b.top() > a.bot()
		|| b.bot() < a.top() );
}

int coll_box_intersects_now_2( const coll_box& a, const coll_box& b )
{
	return !( ( b.left().data + 1 ) >= ( a.right().data - 1 )
		|| ( b.right().data - 1 ) <= ( a.left().data + 1 )
		|| ( b.top().data + 1 ) >= ( a.bot().data - 1 )
		|| b.bot() <= a.top() );
}

