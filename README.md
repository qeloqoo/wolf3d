# wolf3d
Creation of barebone version of Wolfenstein 3D game engine. Study of ray casting and DDA algorithm.

This project requires School 42 homebrew minilibX library (included) and was only tested in macOS El Capitan / Sierra environment.

Please, compile using Makefile (type 'make' in console while in project folder)
./maps folder provides some examples to test on

**Example. It will launch small one room level with pillar in the middle**
> ./wolf3d /maps/angle.map

Assignment required us to make walls in cardinal directions of different colors.

There is nothing fancy with controls (Arrowkeys for forward/backward movement and rotation) except, unlike in previous graphical projects, they support simultaneous press of 2 keys.
