#! /usr/bin/env python3

the_list = []

for i in range( 0x0, 0x100 ) :
	if ( i < 0x20 ) :
		the_list.append(' ')
	elif ( i < 0x80 ) :
		the_list.append(chr(i))
	else :
		the_list.append(' ')

for a in the_list :
	print ( "\'{}\', ".format(a), end="" )

print(len(the_list))
