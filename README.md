# Final-Project
A 3D maze simulation.

Cat Badart,
Will Badart,
Mara Staines,
Dan Wilborn


*Project log can be found at*: https://docs.google.com/spreadsheets/d/1GxqNj7XqEiN0hS3hg-xIgdq8dVjda9YKXLhBy6NUcfU/edit#gid=0

*Team meeting descripts (more detail)*: https://docs.google.com/document/d/16bwAEJMZ0qg0G66HvHHsSY0q0C9MV2ztJ7Bh--Ex8tg/edit


*Git repository can be found at*: https://github.com/wbadart/Final-Project


SOFTWARE MANUAL
===============

**Overview** 

To work with openGL, we used the panda3D engine. This engine is open source and has been used in large-scale online games (such as Disney's ToonTown and Pirates of the Caribbean). To use panda3D, we had to install numerous libraries before installing the panda3D software itself. There are a large number of libraries and header files that are accessed when using panda3D, so we will only touch on the major ones. By default, panda3D files are written in python, but we obviously worked in C++. Other than the overall lack of documentation on panda3D in C++, we did not run into too many problems.


**How We Did It - From the Programmer's Perspective**

The major difficulty when working with panda3D was learning much of the syntax/formatting when using panda3D. Line-by-line the panda3D code was fairly straight-forward, but the vast amount of 'moving parts' could make it difficult at times to register what was happening.

Overarching our code is the main.cpp file. Originally, this file contained a large amount of code, but it is now very basic (as it should be), and instantiates the base class, Game. It also creates a clock object (within panda3D) and camera node. Finally, it closes down the program.

The base class, Game, contains much of the overarching panda3D code. This includes opening the window, bringing in models, moving the dog character, collision detection, and the camera. The Game class also runs the game.

From the base class, we then created an Object class. This is the base class from which all collectable objects would come from. The Object class includes a load function, a set scale function, a set position function, and a function (set_p) for setting the angle of the object. There is also a get points function and set points function. The data members include the points, the path, and the node. 

Interestingly, our Object class and Game class are intertwined in the sense that the Game class is referenced in Object. This allows us to call two of the member functions located in Game from within the Object class. Overall, Object is used within Game in a composition method. We use pointers to Object because Game is referenced in Object, so Game must be created for Object to exist. In a similar way, Object must be created for Game to exist. By using pointers, we do not have to allocate a specific amount of memory for the Object class within Game.

Within the Game class, there is also a vector of Object pointers, this is important for the actual implementation of objects.

The objects are dispersed randomly throughout the game. This was done by adding a function in Game that used the rand function to generate a number between 2 and 8, that determines the number of objects that should be generated. Then a for loop (for both Bone and Shampoo), allocates a new Bone by pushing the Bone class back in the vector of pointers declared in Game. The position/angle are randomized (excluding z - up and down), then the loop iterator is incremented. The same process is then done for Shampoo within the for loop (same loop that contains Bone creation).


**Libraries/Header files** :  *within /built/lib and /built/include*

libp3dtool.so.1.9 / libp3dtoolconfig.so.1.9 : The core of panda3D, critical for all panda3D usage.

libp3framework.so.1.9 : Important for panda3D usage with C++, essential when trying to compile.

libp3tinydisplay.so.1.9 : Renders panda3D software.

libpandagl.so : Renders panda3D, specifcally openGL portion.
 

pandaFramework.h : Similar to the libp3framework library, it is essential for panda3D usage with C++.

texturePool.h : Needed to import and create visual textures we see on screen.

collisionNode.h : Brings in and declares various functions used in collision detection.



**Building Program**

For the ease of the both the programmer and the user, the program is compiled with a simple Makefile. However, the compile it, the computer must have panda3D as well as all of the required libraries installed. When the Makefile is run, the Makefile draws from the required panda3D libraries (which all have been set within our local machines' paths - again for ease). It also draws from the required models (in .egg form). We anticipate that the grader will be unable to compile the program on his/her machine, so our program will be demo-ed accordingly.


**User Manual**

Once the program is up and running, the game is very straight-forward. The user can use either the arrow keys or WASD to move the dog through the maze, collecting bones along the way while avoiding shampoo bottles. To change the POV, the user can press 'o'. To exit the program, the user can press 'Esc'. The goal is to reach the end of the maze and both a score and time elapsed are recorded.


**Known Bugs**

One known bug is that when registering key strokes, the game is 1 stroke behind. Also, the camera does not have collision checking and will tend to go through walls. 



#### A note to evaluators:

For the first several weeks of development, team members Cat, Dan, and Mara didn't have their local git configurations linked to their email addresses. For this reason, many of the Github generated statistics about contributions are inaccurate. Please review the commit log directly if you wish to verify the even distribution of effort across team members.  Thank you!
