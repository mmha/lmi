#!/bin/sh
for x in $(find include/ test/ -name '*.cpp' -o -name '*.h'); do clang-format -style=file -i $x; done
