
@{{BLOCK(sherwin_gfx)

@=======================================================================
@
@	sherwin_gfx, 64x128@4, 
@	+ palette 16 entries, not compressed
@	+ 128 tiles Metatiled by 2x4 not compressed
@	Total size: 32 + 4096 = 4128
@
@	Time-stamp: 2016-01-15, 12:33:07
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global sherwin_gfxTiles		@ 4096 unsigned chars
sherwin_gfxTiles:
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xC443,0x0000,0xC444,0x0000,0x444B
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCBBB,0x0044,0xCCBC,0x0004,0x4CCC,0x0000

	.hword 0xB000,0x99BB,0x9B00,0x9AB9,0x9AB0,0xBBB9,0x9AB0,0x3B99
	.hword 0xAAB0,0x3B9A,0xAB00,0x3BAA,0xB800,0xB5BB,0x6800,0x5555
	.hword 0xBA99,0x0000,0xBAA9,0x0000,0x9ABB,0x00BB,0xAB33,0x0B3B
	.hword 0xAB43,0x0B3B,0xAB44,0x0B4B,0xB5BB,0x00BB,0x5555,0x0008
	.hword 0x6800,0x5555,0x8000,0x5556,0x8000,0x6667,0x8000,0x7777
	.hword 0x0000,0x8888,0x0000,0xAABC,0x0000,0xAABC,0x0000,0xCCCC
	.hword 0x6555,0x0008,0x6568,0x0008,0x8678,0x0000,0x8778,0x0000
	.hword 0x0888,0x0000,0x0CBC,0x0000,0xC2C2,0x0000,0xCCCC,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0xCC00,0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0CCC,0x0000,0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC
	.hword 0xBC00,0xC33B,0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333
	.hword 0x3430,0x1333,0x3330,0xA333,0x4300,0xC443,0x4000,0xC444
	.hword 0xCC3C,0x00C3,0x1231,0x0043,0x1231,0x0043,0x3333,0x0043
	.hword 0x3AAA,0x0044,0xA111,0x0044,0xCBBB,0x0044,0xCCBC,0x0004

	.hword 0xB000,0x4444,0xBB00,0x999B,0x99B0,0x9AAB,0x9AB0,0xBBB9
	.hword 0xAAB0,0x33B9,0xAB00,0x33BA,0xB800,0x43BB,0x5800,0xBBB5
	.hword 0xCCCC,0x0000,0xBB99,0x0000,0xB999,0x000B,0xBAAB,0x00B3
	.hword 0xBAB3,0x00B3,0xBAB4,0x00B4,0xBBB4,0x000B,0x855B,0x0000
	.hword 0x6800,0x5555,0x7800,0x5566,0x7800,0x7667,0x8000,0x8777
	.hword 0xCC00,0x087C,0xBC00,0x00CA,0xBC00,0x0C2A,0xC000,0x0CCC
	.hword 0x6555,0x0008,0x6555,0x0008,0xC678,0x00CC,0xAC80,0x00C2
	.hword 0xABC0,0x00CA,0xBBC0,0x000C,0xCCC0,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0xCC00,0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0CCC,0x0000,0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC
	.hword 0xBC00,0xC33B,0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333
	.hword 0x3430,0x1333,0x3330,0xA333,0x4300,0xC443,0x4000,0xC444
	.hword 0xCC3C,0x00C3,0x1231,0x0043,0x1231,0x0043,0x3333,0x0043
	.hword 0x3AAA,0x0044,0xA111,0x0044,0xCBBB,0x0044,0xCCBC,0x0004

	.hword 0xB000,0x444B,0xBB00,0x999B,0x99B0,0x9AAB,0x9AB0,0xBBB9
	.hword 0xAAB0,0x33B9,0xAB00,0x33BA,0xB800,0x43BA,0x7800,0xBBBB
	.hword 0xCCCC,0x0000,0xBB99,0x0000,0xB9A9,0x000B,0xBAAB,0x00B3
	.hword 0xBAB3,0x00B3,0xBAB4,0x00B4,0xBAB4,0x000B,0xBB5B,0x0000
	.hword 0x8000,0x5556,0x8000,0x5556,0x7800,0x6556,0xCCC0,0x8667
	.hword 0xBBC0,0x087C,0xABC0,0x00CA,0xAC00,0x00C2,0xCC00,0x00CC
	.hword 0x6555,0x0008,0x6655,0x0008,0x7668,0x0CCC,0xC780,0x0C2A
	.hword 0xBC00,0x0CAA,0xBC00,0x0CBB,0xCC00,0x00CC,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xC443,0x0000,0xC444,0x0000,0x444B
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCBBB,0x0044,0xCCBC,0x0004,0x4CCC,0x0000

	.hword 0xBB00,0x9BBB,0x33B0,0xB9B3,0x33B0,0xB9B4,0x43B0,0xB9B4
	.hword 0xBBB0,0xBA9B,0xAB00,0xBBAA,0xB800,0x55BB,0x6800,0x5555
	.hword 0xBA99,0x0000,0xBA99,0x0000,0xAA99,0x00BB,0xAAA9,0x0B3B
	.hword 0xAAAA,0x0B3B,0xAAAA,0x0B4B,0xBBBB,0x00BB,0x5555,0x0008
	.hword 0x6800,0x5555,0x8000,0x5556,0x8000,0x6667,0x8000,0x7777
	.hword 0x0000,0x8888,0x0000,0xAABC,0x0000,0xAABC,0x0000,0xCCCC
	.hword 0x6555,0x0008,0x6568,0x0008,0x8678,0x0000,0x8778,0x0000
	.hword 0x0888,0x0000,0x0CBC,0x0000,0xC2C2,0x0000,0xCCCC,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xBBB3,0x0000,0x333B,0x0000,0x433B
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCBBB,0x0044,0xCCBB,0x0004,0x4CCB,0x0000

	.hword 0xB000,0x443B,0x9B00,0xBBB9,0x9B00,0xA999,0xAB00,0xBA99
	.hword 0xAB00,0x9BAA,0xB800,0xBABB,0x6800,0x5BBB,0x6800,0x5555
	.hword 0xB99B,0x0000,0xBA9B,0x0000,0xAA9B,0x00BB,0xAA99,0x0B3B
	.hword 0xAAA9,0x0B3B,0xAAAA,0x0B4B,0xBBBB,0x00BB,0x5555,0x0008
	.hword 0x6800,0x5555,0x7800,0x5566,0x7800,0x7667,0x8000,0x8777
	.hword 0xCC00,0x087C,0xBC00,0x00CA,0xBC00,0x0C2A,0xC000,0x0CCC
	.hword 0x6555,0x0008,0x6555,0x0008,0xC678,0x00CC,0xAC80,0x00C2
	.hword 0xABC0,0x00CA,0xBBC0,0x000C,0xCCC0,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xC443,0x0000,0xC444,0x0000,0xBBBB
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCCCC,0x0044,0xCBBB,0x0004,0xB333,0x0000

	.hword 0xB000,0xB999,0x9B00,0xB999,0xAB00,0xBA99,0xBB00,0xBBAA
	.hword 0xAB00,0xAABB,0xAB00,0xAAAA,0xB800,0xBBBB,0x6800,0x5555
	.hword 0xB433,0x0000,0xB443,0x0000,0xABBB,0x00BB,0xA99A,0x0B3B
	.hword 0xAAAA,0x0B3B,0xAAAB,0x0B4B,0xBBB5,0x00BB,0x5555,0x0008
	.hword 0x8000,0x5556,0x8000,0x5556,0x7800,0x6556,0xCCC0,0x8667
	.hword 0xBBC0,0x087C,0xABC0,0x00CA,0xAC00,0x00C2,0xCC00,0x00CC
	.hword 0x6555,0x0008,0x6655,0x0008,0x7668,0x0CCC,0xC780,0x0C2A
	.hword 0xBC00,0x0CAA,0xBC00,0x0CBB,0xCC00,0x00CC,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xC443,0x0000,0xC444,0x0000,0x444B
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCBBB,0x0044,0xCCBC,0x0004,0x4CCC,0x0000

	.hword 0xB000,0x9BB9,0x9B00,0xBA99,0x9B00,0xA999,0xAB00,0x9999
	.hword 0xBB00,0xA9AA,0xAB00,0xAABB,0xB800,0xBBBB,0x6800,0x5555
	.hword 0xB999,0x0000,0xBB9B,0x000B,0x33BA,0x00B3,0x33BA,0x00B4
	.hword 0x43BA,0x00B4,0xBBBB,0x000B,0xBBB5,0x000B,0x5555,0x0008
	.hword 0x6800,0x5555,0x8000,0x5556,0x8000,0x6667,0x8000,0x7777
	.hword 0x0000,0x8888,0x0000,0xAABC,0x0000,0xAABC,0x0000,0xCCCC
	.hword 0x6555,0x0008,0x6568,0x0008,0x8678,0x0000,0x8778,0x0000
	.hword 0x0888,0x0000,0x0CBC,0x0000,0xC2C2,0x0000,0xCCCC,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xC443,0x0000,0xC444,0x0000,0x444B
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCBBB,0x0044,0xCCBC,0x0004,0x4CCC,0x0000

	.hword 0xBB00,0x9BBB,0x33B0,0xB9B3,0x33B0,0xB9B4,0x43B0,0xB9B4
	.hword 0xBBB0,0xBA9B,0xAB00,0xBBAA,0xB800,0x55BB,0x6800,0x5555
	.hword 0xBA99,0x0000,0xBA99,0x0000,0xAA99,0x00BB,0xAAA9,0x0B3B
	.hword 0xAAAA,0x0B3B,0xAAAA,0x0B4B,0xBBBB,0x00BB,0x5555,0x0008
	.hword 0x8000,0x5556,0x8000,0x5556,0x7800,0x6556,0xCCC0,0x8667
	.hword 0xBBC0,0x087C,0xABC0,0x00CA,0xAC00,0x00C2,0xCC00,0x00CC
	.hword 0x6555,0x0008,0x6655,0x0008,0x7668,0x0CCC,0xC780,0x0C2A
	.hword 0xBC00,0x0CAA,0xBC00,0x0CBB,0xCC00,0x00CC,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xBBB3,0x0000,0x333B,0x0000,0x433B
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCBBB,0x0044,0xCCBB,0x0004,0x4CCB,0x0000

	.hword 0xB000,0x443B,0x9B00,0xBBB9,0x9B00,0xA999,0xAB00,0xBA99
	.hword 0xAB00,0x9BAA,0xB800,0xBABB,0x6800,0x5BBB,0x6800,0x5555
	.hword 0xB99B,0x0000,0xBA9B,0x0000,0xAA9B,0x00BB,0xAA99,0x0B3B
	.hword 0xAAA9,0x0B3B,0xAAAA,0x0B4B,0xBBBB,0x00BB,0x5555,0x0008
	.hword 0x8000,0x5556,0x8000,0x5556,0x7800,0x6556,0xCCC0,0x8667
	.hword 0xBBC0,0x087C,0xABC0,0x00CA,0xAC00,0x00C2,0xCC00,0x00CC
	.hword 0x6555,0x0008,0x6655,0x0008,0x7668,0x0CCC,0xC780,0x0C2A
	.hword 0xBC00,0x0CAA,0xBC00,0x0CBB,0xCC00,0x00CC,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xC443,0x0000,0xC444,0x0000,0xBBBB
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCCCC,0x0044,0xCBBB,0x0004,0xB333,0x0000

	.hword 0xB000,0xB999,0x9B00,0xB999,0xAB00,0xBA99,0xBB00,0xBBAA
	.hword 0xAB00,0xAABB,0xAB00,0xAAAA,0xB800,0xBBBB,0x6800,0x5555
	.hword 0xB433,0x0000,0xB443,0x0000,0xABBB,0x00BB,0xA99A,0x0B3B
	.hword 0xAAAA,0x0B3B,0xAAAB,0x0B4B,0xBBB5,0x00BB,0x5555,0x0008
	.hword 0x8000,0x5556,0x8000,0x5556,0x7800,0x6556,0xCCC0,0x8667
	.hword 0xBBC0,0x087C,0xABC0,0x00CA,0xAC00,0x00C2,0xCC00,0x00CC
	.hword 0x6555,0x0008,0x6655,0x0008,0x7668,0x0CCC,0xC780,0x0C2A
	.hword 0xBC00,0x0CAA,0xBC00,0x0CBB,0xCC00,0x00CC,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCC00
	.hword 0x0000,0xBBCC,0xC000,0xCBBC,0xBC00,0x33BB,0xBC00,0xC33B
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0CCC,0x0000
	.hword 0xCBBB,0x0000,0xCCCC,0x000C,0x3333,0x00CC,0xCC3C,0x00C3
	.hword 0xBC00,0x233B,0xC330,0x2333,0xC430,0x3333,0x3430,0x1333
	.hword 0x3300,0xA333,0x4000,0xC443,0x0000,0xC444,0x0000,0x444B
	.hword 0x1231,0x0043,0x1231,0x0043,0x3333,0x0043,0x3AAA,0x0044
	.hword 0xA111,0x0044,0xCBBB,0x0044,0xCCBC,0x0004,0x4CCC,0x0000

	.hword 0xB000,0x9BB9,0x9B00,0xBA99,0x9B00,0xA999,0xAB00,0x9999
	.hword 0xBB00,0xA9AA,0xAB00,0xAABB,0xB800,0xBBBB,0x6800,0x5555
	.hword 0xB999,0x0000,0xBB9B,0x000B,0x33BA,0x00B3,0x33BA,0x00B4
	.hword 0x43BA,0x00B4,0xBBBB,0x000B,0xBBB5,0x000B,0x5555,0x0008
	.hword 0x8000,0x5556,0x8000,0x5556,0x7800,0x6556,0xCCC0,0x8667
	.hword 0xBBC0,0x087C,0xABC0,0x00CA,0xAC00,0x00C2,0xCC00,0x00CC
	.hword 0x6555,0x0008,0x6655,0x0008,0x7668,0x0CCC,0xC780,0x0C2A
	.hword 0xBC00,0x0CAA,0xBC00,0x0CBB,0xCC00,0x00CC,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.section .rodata
	.align	2
	.global sherwin_gfxPal		@ 32 unsigned chars
sherwin_gfxPal:
	.hword 0x7FE0,0x0000,0x7FFF,0x533F,0x3658,0x7F00,0x7E00,0x7D00
	.hword 0x6000,0x029F,0x0199,0x0114,0x00D0,0x4210,0x318C,0x2108

@}}BLOCK(sherwin_gfx)
