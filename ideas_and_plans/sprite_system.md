# Sprite System
1. A basic sprite interaction system will be made to exist.
2. Ye olde sprite allocator/deallocator will be migrated from src\_old/
to the new src/ directory.  It might have to be modified.
3. A *SpriteInitParamGroup* class will exist, but will be called
*SpriteInitParams* instead.
4. Importantly, only one updater function (called *update()*) will be
used this time.  Every sprite gets exactly one of those, and it will be
run **before** testing interaction between sprites.  Interaction with
other sprites will be how a sprite does a second "update" after the
*update()* call.
  1. A sprite will have interaction with blocks, of course, which should
  be run as part of said sprite's *update()* function.
5. Also importantly, only one *init* type member function will be used
per default.  No more will there be the confusing setup of **multiple**
*init* type member functions.
6. Sprites will have a *state* variable.  This can be used for killing a
sprite, and also for, uh, maybe status conditions?  It won't be used for
dealing damage to the sprite, however.
  1. Not every sprite will care about every state.  
  2. **Perhaps** an error should be thrown (and *halt()* called) when a
  sprite gets put into a state it does not expect.  I might not go
  through with this as I might miss this type of bug in testing!  Perhaps
  it could be used **just** for testing, howerver, and disabled in the
  final game.
