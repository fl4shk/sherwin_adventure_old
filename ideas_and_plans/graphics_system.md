# Graphics System (including palettes)


## Tilesets and Palettes
A tileset will have a set of palettes that it's tied to.  It can be just
one palette.

Uncompressed graphics will be used to save RAM instead of ROM.  This will
permit simply loading graphics directly into VRAM without needing to
use a buffer in RAM.

A sublevel will specify which tilesets it uses.  This will be partially
automated by use of the level editor.

## Blocks and Sprites
A block/sprite will specify which tileset(s) it uses, as well as what
palette(s).

Block palettes/tiles can only change when (A) something happens to that
block (such as when it gets strongly hit, for example), (B) all blocks of
that type change their graphic (essentially changing the metatile used in
VRAM at **one** location).  

Getting strongly hit may cause a block to change what type of block it is,
however.
