# Level System

## Sublevels
1. Each level consists of a group of entities referred to as **sublevels**.
  1. These are really just portions of the overall level.
  2. I'm not sure exactly what the maximum number of sublevels **in one
  level** will be, but it will be **at least 8**.  I'll see if I can manage
  to allow more than just 8.  With my new usage of linker overlays, there
  is a good chance I will be able to pull it off.
2. The level will start by placing the player into in a particular
sublevel.  Which sublevel that is will vary by level.
3. Sublevels can be connected to one another (and should!) via some sort of
warp mechanism.  There will likely be more than one warp mechanism.  
  1. An example of such a warp mechanism is just a door.
  2. Unlike in my original attempt, this time, warp mechanisms won't be
  sprites.  The reason it was set up like that before was because sprites
  already had interaction set up between them; it was an easy way
  to do a proof of concept.
4. In addition to the warp mechanism, there will be a method for sublevels
to keep track of some state even when they're not really loaded.  I call
this **persistent sublevel data**.
  1. It persists only while within the particular level.  Upon leaving the
  level, the array will be cleared.
  2. As an example of how this works, let's say some block in sublevel 0
  was hit.  Let's assume that the block in sublevel 0 that was hit became
  **some other type of block** after being hit.  Now, the player goes to
  sublevel 1.  A little while later, the player goes back to sublevel 0.
  Persistent sublevel data permits the game to, during level loading,
  see that the original block had been hit, and thus will make it so that
  the block still has been hit when the player returns to sublevel 0.
  3. **Without doing something like this**, the player could potentially
  hit a block that has an item in it, go to another sublevel, return to the
  previous sublevel, and hit the same block again, which would permit
  getting infinite numbers of that particular item without much effort.
