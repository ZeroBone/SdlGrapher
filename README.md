# SdlGrapher
SdlGrapher is a small program to render math functions as Charts built with SDL2 library.
The goal is also to demonstrate **floating-point precision errors**, that's why i didn't do any border / scaling checks.

## Features
* Horizontal / vertical scrolling.
* Scaling with mouse wheel.
* No rendering if the math function returns `NaN` or `Infinity`.
* Movable axises. Screen => Math, Math => Screen unit converters.
* Automatically calculate scale and axis position based on interval of the math function.
* Pixel perfect rendering.

## Screenshots
#### f(x) = x ^ 2
![Parabola demo](/screenshots/xx.png)
#### f(x) = 1 / x
![Log demo](/screenshots/1divx.png)
#### f(x) = log(x)
![Log demo](/screenshots/log.png)
#### f(x) = sqrt(x)
![Log demo](/screenshots/sqrt.png)
#### f(x) = sin(x)
![Sin demo](/screenshots/sin.png)
#### f(x) = sqrt(x) * sin(x)
![Sin demo](/screenshots/sqrtsin.png)
#### f(x) = 3 * sin(x / 4) - 2 / sin(2 * x)
![Sin2 demo](/screenshots/sin2.png)