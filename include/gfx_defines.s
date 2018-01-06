@ This file is part of Sherwin's Adventure.
@ 
@ Copyright 2015-2018 Andrew Clark (FL4SHK).
@ 
@ Sherwin's Adventure is free software: you can redistribute it and/or
@ modify it under the terms of the GNU General Public License as published
@ by the Free Software Foundation, either version 3 of the License, or (at
@ your option) any later version.
@ 
@ Sherwin's Adventure is distributed in the hope that it will be useful,
@ but WITHOUT ANY WARRANTY; without even the implied warranty of
@ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
@ General Public License for more details.
@ 
@ You should have received a copy of the GNU General Public License along
@ with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


@ Display Register Address Defines
.equ reg_dispcnt, 0x04000000		@ Display Control
.equ reg_dispstat, 0x04000004		@ Display Status
.equ reg_vcount, 0x04000006			@ VCount

@ Display Register Value Defines
@  Bitwise OR these values together

@   Video Mode (Select ONLY ONE)
.equ dcnt_mode0, 0x0000
.equ dcnt_mode1, 0x0001
.equ dcnt_mode2, 0x0002
.equ dcnt_mode3, 0x0003
.equ dcnt_mode4, 0x0004
.equ dcnt_mode5, 0x0005


@   OBJ Character VRAM Mapping (Select ONLY ONE)
.equ dcnt_obj_2d, ( 0x0000 << 0x6 )
.equ dcnt_obj_1d, ( 0x0001 << 0x6 )


@   Forced Blank (Select ONLY ONE)
.equ dcnt_blank_off, ( 0x0000 << 0x7 )
.equ dcnt_blank_on, ( 0x0001 << 0x7 )


@   Screen Display BG0 (Select ONLY ONE)
.equ dcnt_bg0_off, ( 0x0000 << 0x8 )
.equ dcnt_bg0_on, ( 0x0001 << 0x8 )


@   Screen Display BG1 (Select ONLY ONE)
.equ dcnt_bg1_off, ( 0x0000 << 0x9 )
.equ dcnt_bg1_on, ( 0x0001 << 0x9 )


@   Screen Display BG2 (Select ONLY ONE)
.equ dcnt_bg2_off, ( 0x0000 << 0xa )
.equ dcnt_bg2_on, ( 0x0001 << 0xa )


@   Screen Display BG3 (Select ONLY ONE)
.equ dcnt_bg3_off, ( 0x0000 << 0xb )
.equ dcnt_bg3_on, ( 0x0001 << 0xb )


@   Screen Display OBJ (Select ONLY ONE)
.equ dcnt_obj_off, ( 0x0000 << 0xc )
.equ dcnt_obj_on, ( 0x0001 << 0xc )


@   Window 0 Display (Select ONLY ONE)
.equ dcnt_win0_off, ( 0x0000 << 0xd )
.equ dcnt_win0_on, ( 0x0001 << 0xd )


@   Window 1 Display (Select ONLY ONE)
.equ dcnt_win1_off, ( 0x0000 << 0xe )
.equ dcnt_win1_on, ( 0x0001 << 0xe )


@   OBJ Window Display (Select ONLY ONE)
.equ dcnt_winobj_off, ( 0x0000 << 0xf )
.equ dcnt_winobj_on, ( 0x0001 << 0xf )


