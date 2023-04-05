# PixelGUI

PixelGUI provides a user interface for any application written in C++.

The main goal is to make PixelGUI function as a basis for creating games with a pixelated/8-bit style, but general purpose features are added too.




## What can you do with PixelGUI
- Draw sprites to a screen
- Handle mouse and keyboard inputs
- Provide interactive elements like buttons

## What PixelGUI can not do (yet)
- Draw lines, simple shapes (TODO)
- Plot data to a figure (TODO)
- More interactive elements like switches, labels etc. (TODO)
- Create a user interface with a UI Editor (TODO)
- Provide Audio output
- Make you a cup of coffee

## How to Compile PixelGUI
```
git clone https://github.com/ThijsLuttikhuis/PixelGUI.git
cd PixelGUI
mkdir build
cd build
```

#### Linux (Ubuntu):
```
cmake ..
make
```

#### Windows 10:
```
cmake -G "MinGW Makefiles" ..
make
```
