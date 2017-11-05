# Graphics System (including palettes)


## Tilesets and Palettes
1. A tileset will have a set of palettes that it's tied to.  It can be just
one palette.
2. Uncompressed graphics will be used to save RAM instead of ROM.  This will
permit simply loading graphics directly into VRAM without needing to
use a buffer in RAM.
3. A sublevel will specify which tilesets it uses.  This will be partially
automated by use of the level editor.

## Blocks and Sprites
1. A block/sprite will specify which tileset(s) it uses, as well as what
palette(s).
2. Block palettes/tiles can only change when all blocks of that type change
their graphic (essentially changing the metatile used in VRAM at **one**
location).  
  1. To simulate blocks of the same type having different graphics at the
  same time, it will be **necessary** to implement multiple block types and
  just change the type of a block.
