Sherwin's Adventure
===================

This is a GBA homebrew platformer game that is not yet finished.


#Dependencies for Building
1.  **devkitARM** (though the makefile and linker script used are
*custom*). The default makefile uses devkitARM to build this project.
  1.  Alternatively, any other **arm-none-eabi-** prefixed GCC and Binutils
  can be used; its location just has to be specified in the host OS's
  **PATH** environment variable.  To build this project with some other
  arm-none-eabi- prefixed GCC and Binutils, use
  **makefile_for_non_dka_gcc.mk** as the makefile.
2.  **gbafix**, which is *part of devkitARM*.
3.  **mmutil**, which is *included in devkitARM*.
4.  **bin2s**, which is *included in devkitARM*.


#Notes for Building
When using the makefile called **makefile_for_non_dka_gcc**, this project
**won't build** without having ARM GCC and Binutils available through the
host OS's $PATH variable.

When using the makefile called **makefile_devkitARM.mk**, devkitARM is used
to build Sherwin's Adventure instead of what the author uses.

**gbafix** and **mmutil** *from devkitARM* are still used by this project
even when non-devkitARM GCC is used.


#Optional Dependencies
1.  The [Tiled map editor](https://github.com/bjorn/tiled)
2.  [The author's Tiled level converter tool](https://github.com/fl4shk/tiled_level_converter)
3.  **Usenti** (used for graphics creation/editing), run in Wine by the
author.
4.  GPP - Generic Preprocessor (**VERY optional**, only used to generate
the two makefiles)

