General Mechanics Brainstorming
===============================
1.  I am *not* going to allow damaging enemies by *jumping* on them, as it
allows me to differentiate the game from Mario ones significantly.  
2.  I'm *not* having bottomless pits either, for that matter.  
3.  The game will still have an emphasis on platforming, but it will also
have an emphasis on combat.  Combat will be more important than in Mario
games.  In that sense, the game could be considered more like Kirby and
Mega Man games, without the bottomless pits.
  1.  One indicator of the heavier combat focus in this game is that
  Sherwin has a lot more HP than Mario does (except in Super Mario 64 and
  Super Mario Sunshine, where Sherwin doesn't have THAT much more HP as of
  this writing (8 HP for Mario in SM64 and SMS, 10 HP for Sherwin)).
4.  Sherwin's powerups will provide him with multiple ways to attack.  As
of this writing, no powerup system exists.  That will be changed once more
graphics and sprites are added that would be usable for this purpose.
5.  I *was* thinking I wouldn't have any kind of invincibility frames for
Sherwin, but perhaps I'll drop that.  If I *don't* drop that plan, I'll
need to find a way to prevent Sherwin from getting "stuck" between, for
example, two sprites.  I'm considering also having knockback for ALL
sprites when they get hit.
  1.  Speaking of getting hit, I am thinking of making it so that the
  coll\_box class contains a "strength" value, which would be used for
  coll\_box's that are actually hit\_box's.  I don't see the need for
  another class called "hit\_box" that just inherits from coll\_box and
  only adds a "strength" member variable.  Of course, if the "strength"
  member variable is 0, then the coll\_box is actually supposed to be a
  hit\_box.
6.  I don't think I'll allow most types of enemies to damage Sherwin *just*
by contacting him, at least not without an attacking animation of some
sort.  All enemies will need to be able to do something other than just
walk around.  This is *very* different from Mario games and nearly every
other platform game.



Block System Mechanics Brainstorming
====================================
1.  Categories of blocks could be set up so that different blocks could
share similar properties.  An **enum** would likely be used by this, and
the different block\_base\_stuff class instances would have their own way
to specify this (likely similar to how they currently specify their type).
**Examples** (but maybe not all the ones that will ever exist) of block
categories would include the following:
  1.  Air
  2.  Completely Solid (most blocks seem to fit into this category)
    1.  Perhaps blocks with contents would also be considered completely
    solid, or they may have their own category.  For your information,
    blocks with contents are things like most types of wooden blocks
    (except the default one that currently just disappears when strongly
    hit), and all eyes blocks.
  3.  Slopes, with all their varieties.
    1.  Perhaps some slopes would have the same physics applied to them,
    but just have different graphics.  This would matter when it comes to
    different level themes, which I will probably eventually have.
  4.  Maybe ladders?  I could pull a Mario and make it so that ladders can
  come out of blocks, perhaps.
  5.  Blocks that can be jumped through to land on top.  
  6.  Similarly, blocks that can be jumped through to land on top, but also
  that Sherwin could "jump" through to go underneath.
  6.  One thing I **DON'T** think I'll have is **invisible** blocks.  In
  Mario games, I think that those are just annoying, *especially* when they
  are necessary to progress in the level.
  7.  Water, if I end up wanting to have swimming mechanics.  If I did that
  I could have more variety in the environments.
2.  Some blocks will be programmatically the same, but have *different
graphics*.  This would be used for different level *themes*, like in Super
Mario Bros. 3.  Here are some ways I might implement this system:  
  1.  Multiple block tilesets.
  2.  One tileset with multiple block types.
    1.  This method would allow mixing themes in a level (or even a
    sublevel), and would probably reduce the size of the graphics in ROM,
    especially considering that I don't currently compress graphics in ROM.
    2.  Also, it would eat up more slots in the block\_type enum, but I
    already use 32-bits for that enum, anyway.
    3.  The main thing with this method is that more code space would be
    used due to needing multiple class instances that are virtually the
    same.  Because of the shared code, I will probably just use shared base
    classes that are derived from block\_base\_stuff.


Sprite System Mechanics Brainstorming
=====================================
1.  Multiple categories of sprites will exist.  They can be identified by
how the sprites are spawned using the sprite\_manager class, as well as
which array (or non-array variable in Sherwin's case)
  1.  Secondary sprites that can be spawned by Sherwin.
    1. These include his projectiles (once they exist), and his melee
    weapons.
  2.  Secondary sprites that are spawned by "regular" sprites.
    1.  This would include
  3.  Sherwin is considered special, and is basically a category of sprites
  in and of himself.
  4.  "Regular" sprites, which as of this writing are mostly just spawned
  from the level data, though it *is* true that powerups can be spawned out
  of "eyes" blocks.
2.  Sprites spawned from level data spawn in whole *columns* at a time, and
only one sprite instance in the level data is allowed per block coordinate.

Graphics Brainstorming
----------------------
1.  Currently, sprite graphics can use up a lot of space when repeated
tiles are used in multiple frames.  This is *especially* evident in the
case of Sherwin.  It may be of interest to make it so that sprites can
choose to have a more complicated way of uploading their graphics to their
32x32 VRAM chunks, which would consist of uploading their tiles from
**non-contiguous** locations.  
  1.  Of note is that I believe that my existing sprite system *would work
  for this purpose*, since sprites already provide their own graphics data
  to other functions.  




Enemy Ideas Brainstorming
=========================


Bowling-themed enemies
----------------------
1.  Large (using a 16x32 sprite) bowling pin enemies.  I will need to make
a smaller bowling pin graphic so that it isn't as tall.
  1.  Version with no arms that just hops around to move, or perhaps slides
  along the ground if in a tight spot.  It will need some kind of attack to
  be able to damage Sherwin.
  2.  Version with (stubby) arms and that can throw bowling balls that roll
  along the ground.  It *might* be stationary, but if not, it will only hop
  around.  A **limited number** of bowling balls could be active at a
  time, perhaps limited more than the number of permitted enemy-spawned
  secondary sprites.  Also, the bowling 
2.  Small (using an 8x16 sprite) bowling pin enemy
  1.  It might be spawned by some variety of the 16x32 bowling pin sprite,
  or something else.
  2.  It might be like Micro Goombas are to Mario in NSMB and be unable to
  damage Sherwin.
3.  (**Rejected because it required rotated collision boxes for handling
slopes**) Large (using a 32x16 or maybe 32x32 sprite) bowling pin shaped
"car", with wheels that look like bowling balls, but that are still
wheel-shaped.
4.  Bowling Ball that can walk around (so it has appendages), but can
"pull" its legs/feet/etc. inside and then roll itself towards Sherwin to
attack.  Its attack might also be able to activate the "strongly hit
response" function of blocks it hits.  


Snowmen, Golems, and other similar things
-----------------------------------------
Various elemental golems, which are all shaped similarly to snowmen.
1.  Snow Golem (basically a snowman)
  1.  (**Rejected due to being a derpy animation**) It "shoots" snowballs (see the animation it does).  
  2.  (**This is what will actually be used**) Actually, it needs a new
  snowball launching animation that actually makes it look like it's
  *throwing* the snowball, though the snowball will *probably* still just
  move horizontally.  Alternatively, it may have gravity applied to it, but
  it'd still start with y velocity = 0.
  3.  Also, the snowball would need to have a separate graphic for when
  it's being held/thrown by the Snow Golem, due to the fact that the hand
  of the Snow Golem needs to **appear** to be holding the snowball.
2.  Ice Golem (two cuboid parts)
  1.  It spawns an ice cube, then launches it.  The ice cube would increase
  in size during the animation, to a max size of 8x8 pixels.  Perhaps the
  ice cube would reach max size *before* it is actually launched.
  2.  Also, the ice cube would need to have a separate graphic for when
  it's being held/thrown by the Ice Golem, due to the fact that the hand
  of the Ice Golem needs to **appear** to be holding the ice cube.
3.  Lava Golem
4.  Spark Golem
5.  Water Golem
6.  Sand Golem
7.  Stone Golem
8.  Bowling Ball Golem
  1.  Uh, I guess this enemy might be possible to split into two of the
  bowling balls that can walk around and roll themselves to attack.
  2.  Alternatively, this enemy could *spawn* the bowling balls that walk
  around and roll themselves to attack.



Food Themed Enemies
-------------------
1.  Living muffin that walks around.  It will need some kind of attack
because **most** enemies won't be permitted to damage Sherwin just by
contacting him.
  1.  No, Sherwin won't be able to eat these after they're defeated.  Mario
  can't eat Goombas, after all.
  2.  There could be different varieties (identified by foot color or
  something like that) of the muffin, such that some of them DON'T walk off
  ledges.
  3.  Also, similar to how there are flying goombas, there could be a
  flying variation.
2.  Perhaps make the waffles be an enemy instead of a powerup?  After all,
they DO levitate (at least for now).  If I do that, I'll need to come up
with another health restoring powerup.


