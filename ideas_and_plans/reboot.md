# Plans
1. Graphics system
2. Rudimentary level system (just for testing physics), no compression.
 1. Will just be a block tilemap and a sprite tilemap.
 2. Only one sublevel for now.
 3. Will not include ye olde complicated sprite spawning system based upon
 player x position.  That will come later, once I feel that physics and
 camera systems are good enough.  Instead, sprites will just always be
 active (unless despawned).  
 4. No sprite despawning based upon player x position yet. That'll come
 later.  I have to start out a bit smaller.
3. Start of block system. 
4. Start of sprite system
  1. Will include a few simplistic sprites for testing purposes.  
  2. No secondary sprites yet.
  3. Will include an initial version of *SpriteInitParams*, at least.
5. Physics (including slope stuff)
6. Camera system
  1. Start with a simple "center on the player" method.
  2. Later convert it to a better thing akin to how I had it before.

Those are my plans for now.
Some code will be copied from src\_old/
