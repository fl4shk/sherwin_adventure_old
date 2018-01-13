# Graphics System (including palettes)


## Tilesets and Palettes
1. A palette contains 16 colors, with color at index zero being
transparent.
2. Also, a tileset will have a set of palettes that it's tied to.  The set
can contain just one palette.
  1. The set of palettes will count towards the maximum number of block or
  sprite palettes that can be used in a particular sublevel.
  2. I am leaning towards 12 palettes for in-level, "gameplay" sprites,
  such as the player, enemies, other interactable sprite-based objects.
  3. I'm not sure how many palettes will be allocated for in-level,
  "gameplay" blocks, but the number might just be 12 again for simplicity.
  It might not, however, given that there is less of a need for a lot of
  block palettes than a lot of sprite palettes.
  4. For at least blocks, there will be some palette "sections", perhaps
  one "section" for "gameplay" blocks (ones that can be interacted with),
  which is how most of the block palettes will be used.  Another "section"
  could be allocated for the "status bar", which displays, for example,
  information such as how much HP the player has left and what powerups the
  player currently has available to them.  If there were a time limit, then
  the amount of time left to complete the level would go into the "status
  bar" as well, but I don't think I'll be having those.
3. Uncompressed graphics will be used to save RAM instead of ROM.  This
means that one can just memcpy32() over the tiles from a particular tileset
when a specific block changes its constituent tiles.
  1. This also allows only using VRAM for blocks that are being used in the
  current level.
  2. Also, this permits simply loading a level's **necessary** graphics
  into VRAM.
4. A sublevel will specify which sprites and blocks it uses, and which
tilesets it uses.  This will be automated by use of the level editor.
  1. The level editor will spit out an error if too many block palettes or
  too many sprite palettes are in use for any particular sublevel.
  2. The palette "sections" will be known to the level editor.  Level
  editing will mostly concern itself with "gameplay" sprites and "gameplay"
  blocks, but there will definitely need to also be at least one background
  (not just a solid color).  The level editor will allow selecting a
  background image.  The background image will, of course, use a tileset of
  some sort.
5. The level editor will automatically figure out a mapping from tileset to
palette number(s).
6. Here is an example.
  1. If a tileset specifies that it uses eight palettes, and only one at a
  time, then only one palette slot will be allocated for that tileset.
7. Here is another example.
  1. If a tileset specifies that it uses four palettes, and possibly more
  than one at a time, then four palettes will be allocated for that
  tileset.

## Blocks and Sprites
1. A block/sprite will specify which tileset(s) it uses, as well as what
palette(s).
2. To simplify things, at run time, block palettes/tiles can only change
when all blocks of that type change their palette/tiles (essentially
changing the palettes/tiles of a metatile used in VRAM at **one**
location).
  1. To simulate blocks of the same type having different graphics at the
  same time, it will be **necessary** to implement multiple block types and
  just change the type of a block.
