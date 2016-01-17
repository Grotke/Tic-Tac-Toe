Tic-Tac-Toe
===========

Graphical Tic Tac Toe in C++ using the Simple DirectMedia Layer library.

![Screenshot of game in action](http://www.josephcmontgomery.com/uploads/4/5/8/3/45834621/5675625_orig.png)
![Screenshot of win](http://www.josephcmontgomery.com/uploads/4/5/8/3/45834621/7515633_orig.png)

Watch of short video of Tic-Tac-Toe in action at: https://www.youtube.com/watch?v=PUGUkTR6evg

## Description and Background
This is a completed project with a tree-based AI, sounds and animations. I made it to learn about creating and structuring a project from scratch. SDL is a barebones cross-platform hardware managing library so it handled putting images on the screen and playing sounds. Everything else - the game loop, the rendering cycle, animation, timing and AI - was handled by me. 

I chose Tic-Tac-Toe so I could concentrate on the project itself without thinking too hard about the game mechanics. Even so it was surprisingly difficult just figuring out where to start.

Go to http://www.josephcmontgomery.com/projects.html#tic-tac-toe for more info about the development process.

## Build Instructions
I don't remember much about building this but I think you'd need the SDL2, SDL2 TTF, SDL2 Mixer and SDL2 Image libraries. It was made on Ubuntu but I imagine it'd work without much change on many other Linux systems. It should technically also work on Windows but I haven't tried it.

Typing `make` in the "make" folder should build it if it can find the libraries. Then `./Tic-Tac-Toe` should run it and `make clean` should remove the executable. 

