sherwin_adventure
=================

This is a GBA homebrew platformer game that is not yet finished.  There is
a series of video games off of which this project is very obviously based,
which the author will not mention by name.

The name of this project is supposed to be **Sherwin's Adventure**.

#Dependencies for Building
1.  **DevKitARM** (though the makefile and linker script used are
*custom*). The default makefile uses DevKitARM to build this project.
  1.  Alternatively, a more up-to-date version of **arm-none-eabi-**
  prefixed GCC and Binutils can be used; its location just has to be
  specified in the host OS's **PATH** environment variable.  To build this
  project with updated arm-none-eabi- prefixed GCC and Binutils, use
  **makefile_for_updated_gcc.mk** as the makefile.
2.  **gbafix**, which is *part of DevKitARM*.
3.  **mmutil**, which is *included in DevKitARM*.
5.  **bin2s**, which is *included in DevKitARM*.


#Notes for Building
When using the makefile called **makefile**, this project **won't build**
without having ARM GCC and Binutils available through the host OS's $PATH
variable.

When using the makefile called **makefile_devkitARM.mk**, devkitARM is used
to build Sherwin's Adventure instead of what the author uses.

The author uses a **more up-to-date version** of ARM GCC and Binutils than
that provided by DevKitARM, though **gbafix** and **mmutil** *from
DevKitARM* are still used by this project.

#Optional Dependencies
1.  The [Tiled map editor](https://github.com/bjorn/tiled)
2.  [The author's Tiled level converter tool](https://github.com/fl4shk/tiled_level_converter)
3.  **Usenti** (used for graphics creation/editing), run in Wine by the author.

