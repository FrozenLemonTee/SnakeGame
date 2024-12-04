# C++ Snake Game, Developing by Zhouzhou Zhang
This is a command line Snake Game currenly under development. The libaray we are using is PDcurses, which is the Windows version of Ncurses, while the functions should be compatible with each other, hence using Ncurses on Linux/Mac while using PDcurses on Windows shall be able to write a cross-platform version.

# 1.Framework
This game is developed by MVC (Model-View-Controller). In the Model file we write the basic implentation of the game object and we write how these objects interact with each other in Controller file. Finally in the View file we draw the graph according to the game objects in Model or Controller. 
  -start.cpp: is where we run the main program and it can also be the controller.
  -arena.cpp: is where we write the game object such as the arena and snake
  -view.cpp: is where we draw the graph
  -data.cpp: is where we store the data of this game
