# Graphics System (including palettes)


## Tilesets and Palettes
1. A tileset will have a set of palettes that it's tied to.  It can be just
one palette.
2. Uncompressed graphics will be used to save RAM instead of ROM.  
  1. This also allows only using VRAM for blocks that are being used in the
  current level.
  2. Also, this permits simply loading a level's **necessary** graphics
  into VRAM.
3. Some types of blocks will have space allocated (in VRAM, RAM, etc.)
regardless of sublevel.
  1. A sublevel will specify which **extra** blocks it uses, and which
  **extra** tilesets it uses.  This will be automated by use of the level
  editor.


## Blocks and Sprites
1. A block/sprite will specify which tileset(s) it uses, as well as what
palette(s).
2. Block palettes/tiles can only change when all blocks of that type change
their graphic (essentially changing the metatile used in VRAM at **one**
location).  
  1. To simulate blocks of the same type having different graphics at the
  same time, it will be **necessary** to implement multiple block types and
  just change the type of a block.
