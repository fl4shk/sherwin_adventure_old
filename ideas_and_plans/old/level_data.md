Level Data
==========

New Class Names
---------------
1.  The *level* class will be renamed *sublevel*.
2.  The *level_pointer* class will be renamed *sublevel_pointer*.


Class Information
-----------------
1.  The reason for the existence of the *sublevel_pointer* class is that
the *sublevel* class is a template class; it is not possible to have an
**array** of **normal** pointers to instances of template classes unless
all the instances have the same template parameters.
2.  A class for a group of *sublevel_pointer*'s, called a *level*, will be
created.  
  1.  A *level* will contain an array of *sublevel_pointer*'s, but there
  will be a max number of *sublevel_pointer*'s per *level*, which would be
  equal to the number of arrays in the *active_level* class that represent
  persistent block data.
  2.  The *level*'s array of *sublevel_pointer*'s will be used so that
  **warping** between *sublevel*'s will only be done among the *sublevel*'s
  represented by the array of *sublevel_pointer*'s.  This will make it
  easier to manage the **warping** between *sublevel*'s within my GBA code.
  3.  My Tiled level converter will be modified to generate a *level* on
  every run of the program, even if there is only one Tiled level file
  given as input to the Tiled level converter.  Also, the Tiled level
  converter will need to be modified to allow more than one Tiled level
  file to be used as input for one run of the program.  This should not be
  too hard to implement.
