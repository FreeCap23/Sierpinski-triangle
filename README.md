# Sierpinski triangle
Sierpinski triangle generator using randomness. Built in C++ and SFML.

![](demo.gif)

### The rules
- Have a triangle with sides A, B and C
- Randomly pick a point inside the triangle and draw it
- Randomly pick a point from A, B or C
- Draw a point in the middle of the two picked points
- Randomly pick a point from A, B or C
- Draw a point at the middle of the randomly chosen point and the last drawn point
- Repeat for `n` steps. This program repeats for 10000 steps

### Features
- Framerate counter on top left
- Number of points on screen is displayed under the framerate

### Building
1) Clone this repository.
2) Inside `src/main.cpp` , change `MAX_POINTS` to any number, or leave it as is. Default is `10000`.
3) Install SFML if not already installed.
4)	Run `make` to compile the program, or `make run` to compile it and run it.