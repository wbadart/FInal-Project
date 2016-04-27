# Final-Project
A 3D maze simulation.

Cat Badart,
Will Badart,
Mara Staines,
Dan Wilborn


*Project log can be found at*: https://docs.google.com/spreadsheets/d/1GxqNj7XqEiN0hS3hg-xIgdq8dVjda9YKXLhBy6NUcfU/edit#gid=0


*Git repository can be found at*: https://github.com/wbadart/Final-Project


SOFTWARE MANUAL
===============

**Overview** 

To work with openGL, we used the panda3D engine. This engine is open source and has been used in large-scale online games (such as Disney's ToonTown and Pirates of the Caribbean). To use panda3D, we had to install numerous libraries before installing the panda3D software itself. There are a large number of libraries and header files that are accessed when using panda3D, so we will only touch on the major ones. By default, panda3D files are written in python, but we obviously worked in C++. Other than the overall lack of documentation on panda3D in C++, we did not run into too many problems.


**How We Did It - From the Programmer's Perspective**

The major difficulty when working with panda3D was learning much of the syntax/formatting when using panda3D. Line-by-line the panda3D code was fairly straight-forward, but the vast amount of 'moving parts' could make it difficult at times to register what was happening.

Overarching our code is the main.cpp file. Originally, this file contained a large amount of code, but it is now very basic (as it should be), and instantiates the base class, Game. It also creates a clock object (within panda3D) and camera node. Finally, it closes down the program.

The base class, Game, contains much of the overarching panda3D code. This includes opening the window, bringing in models, moving the dog character, collision detection, and the camera. The Game class also runs the game.

From the base class, we then created an Object class. This is the base class from which all collectable objects would come from. It is fairly simple, containing a points data member, a getPoints() function, and a draw() function.


**Libraries/Header files** :  *within /built/lib and /built/include*

libp3dtool.so.1.9 / libp3dtoolconfig.so.1.9 : The core of panda3D, critical for all panda3D usage.

libp3framework.so.1.9 : Important for panda3D usage with C++, essential when trying to compile.

libp3tinydisplay.so.1.9 : Renders panda3D software.

libpandagl.so : Renders panda3D openGL
 

pandaFramework.h : Similar to the libp3framework library, it is essential for panda3D usage with C++.

texturePool.h : Needed to import and create visual textures we see on screen.

collisionNode.h : Brings in and declares various functions used in collision detection.



**Building Program**

For the ease of the both the programmer and the user, the program is compiled with a simple Makefile. However, the compile it, the computer must have panda3D as well as all of the required libraries installed. When the Makefile is run, the Makefile draws from the required panda3D libraries (which all have been set within our local machines' paths - again for ease). It also draws from the required models (in .egg form). We anticipate that the grader will be unable to compile the program on his/her machine, so our program will be demo-ed accordingly.


**User Manual**

Once the program is up and running, the game is very straight-forward. The user can use either the arrow keys or WASD to move the dog through the maze, collecting bones/chew toys along the way while avoiding vacuums/shampoo. To change the POV, the user can press 'o'. The goal is to reach the end of the maze and both a score and time elapsed are recorded.


**Known Bugs**



**Other**












