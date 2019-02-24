# SdlGrapher
SdlGrapher is a small program to render math functions as Charts built with SDL2 library.
It's goal is also to demonstrate **floating-point precision errors**, that's why i didn't do any border / scaling checks.

## Features
* Horizontal / vertical scrolling.
* Scaling with mouse wheel.
* No rendering if the math function returns `NaN` or `Infinity`.
* Movable axises. Screen => Math, Math => Screen unit converters.
* Automatically calculate scale and axis position based on interval of the math function.