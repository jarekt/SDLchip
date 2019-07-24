# SDLchip

A simple cross-platform chip8 implementation written in c using the [SDL2](https://www.libsdl.org/) graphics library. 

## precompiled executables
* will be available in an upcoming release
* the source is almost finished (just needs some polish), but should compile without any problems
* !! check the releases tab for a static demo with preloaded Tetris.ch8 cartridge !!

## How to compile
* just use cmake :)

## controls
* **hexpad mapping**  
1	2	3	C => 1   2   3   4  
4	5	6	D => Q   W   E   R  
7	8	9	E => A   S   D   F  
A	0	B	F => Y   X   C   V

* **misc. controls**  
ESC - close  
P - pause  
O - reset loaded cartridge

* **terminal arguments**  
aren't a part of the demo so will be here with the full release

## additional features
* a python script to download sdl2 into the appropriate folder (if it seems like it's not doing anything, it's because SDL is quite a big library)
* a python script for converting files to c strings (so they can be compiled as part of the binary) - used for the Tetris demo

## pictures
* coming soon