
//{{BLOCK(title_screen)

//======================================================================
//
//	title_screen, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 145 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (flat), lz77 compressed, 32x32 
//	Total size: 32 + 1008 + 584 = 1624
//
//	Time-stamp: 2015-08-04, 13:42:06
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	(http://www.coranac.com/projects/#grit)
//
//======================================================================

#ifndef GRIT_TITLE_SCREEN_H
#define GRIT_TITLE_SCREEN_H

#define title_screenTilesLen 1008
extern const unsigned short title_screenTiles[504];

#define title_screenMapLen 584
extern const unsigned short title_screenMap[292];

#define title_screenPalLen 32
extern const unsigned short title_screenPal[16];

#endif // GRIT_TITLE_SCREEN_H

//}}BLOCK(title_screen)
