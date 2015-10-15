sherwin_adventure
=================

This is a GBA homebrew platformer game that is not yet finished.  There is
a series of video games off of which this project is very obviously based,
which the author will not mention by name.

The name of this project is supposed to be **Sherwin's Adventure**.

#Dependencies for Building
1.  DevKitARM (though the makefile and linker script used are *custom*)

  **and/or**

2.  A more up-to-date version of **arm-none-eabi-** prefixed GCC and
Binutils.  (This is what the author uses for compilation).
3.  **gbafix**, which is *part of DevKitARM*.
4.  **mmutil**, which is *included in DevKitARM*.

#Notes for Building
This project **won't build** without having ARM GCC and Binutils available
through the host OS's $PATH variable.

The author uses a **more up-to-date version** of ARM GCC and Binutils than
that provided by DevKitARM, though **gbafix** *from DevKitARM* is still
used by this project.


#Optional "Dependencies"
1.  The **Tiled map editor**.
2.  [The author's Tiled level converter tool](https://github.com/fl4shk/tiled_level_converter)
3.  **Usenti** (used for graphics creation/editing), run in Wine by the author.

