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

