lmi
===

lmi is a simple heady only library for C++ mainly intended for computer graphics applications and tries to resemble GLSL syntax.
### Main Features:
* Good CMake Integration
* `constexpr` where possible - Run linear algebra computations at runtime
* Completely generic, you can create integer vector types or use `__float128`, boost.multiprecision or boost.units
* No heap allocations - Easy to integrate in software running in a freestanding enviroment
* IO is compatible with MATLAB

### What lmi is not:
* Useful for high dimensional problems: Again, no heap allocations. You will likely run into a stack overflow or get bad performance because of excessive copies.
* Well tested. Take a look at [glm](http://glm.g-truc.net/) for that.

### Requirements
* Any C++14 Compiler that supports anonymous structs, however this has only been tested on gcc 6.1 and clang 3.9

Installation
============
### Quick and dirty
None required. Copy the contents of the `include` directory in your project. Or take a look at the [How to import](#How to import) Example

### Arch Linux
There is a PKGBUILD in this repository. Clone it, then `makepkg -si`.

### Other

```bash
cd clonedRepository
mkdir build
cd build
cmake .. && make && sudo make install
```

How to import
=============
```cmake
cmake_minimum_required(VERSION 3.6)
project(sharklasercontrol)

find_package(lmi REQUIRED)
# Or, if you just copied the entire repository
add_subdirectory(lmi)

add_executable(sharklasercontrol main.cpp)
target_link_libraries(sharklasercontrol lmi::lmi)
```

Usage
=====
Quick Start
-----------
```cpp
#include <lmi/lmi.h>
#include <lmi/iostream_support.h>
#include <iostream>

auto main() -> int
{
	lmi::vec3 a(1, 2, 3), b(4, 5, 6);
	auto c = lmi::cross(a, b);

	lmi::mat3 scale = lmi::scale(2.0f, 2.0f, 2.0f);
	lmi::mat3 rotate = lmi::rotateAngles(90.0f, 0.0f, 0.0f);

	std::cout << scale * rotate * c << std::endl;
	// [2.68844        -5.36398        0]'
}
```