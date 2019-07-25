# SDLchip

A simple cross-platform [chip8](https://en.wikipedia.org/wiki/CHIP-8) implementation written in c using the [SDL2](https://www.libsdl.org/) graphics library. 

## Precompiled executables
* check the releases tab

## How to compile
* just use cmake :)

## Controls
* **hexpad mapping**  
1	2	3	C => 1   2   3   4  
4	5	6	D => Q   W   E   R  
7	8	9	E => A   S   D   F  
A	0	B	F => Y   X   C   V

* **misc. controls**  
ESC - close  
P - pause  
O - reset loaded cartridge

## How to run (this doesn't apply to the demo in 0.9)
* get a chip8 cartridge file (.ch8) from the roms folder
* run the executable from terminal with these arguments:  
    * relative path of the rom  
    * emu speed in Hz (optional)
* if you're on windows you can instead drag and drop your rom file on the executable

## Additional features
* a python script to download sdl2 into the appropriate folder (if it seems like it's not doing anything, it's because SDL is quite a big library)
* a python script for converting files to c strings (so they can be compiled as part of the binary) - used for the Tetris demo

## Pictures
* ![running on linux](img/demo.png)