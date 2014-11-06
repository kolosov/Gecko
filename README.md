Gecko-embedding
===============

This is clone of https://github.com/gistinc/Gecko, code is based on http://hg.mozilla.org/incubator/embedding/ (please read old README file )

Improvenments
------------
  CMake support
  Support latest Firefox ESR 31

Compiling
---------
    mkdir build && cd build
    cmake ../moztester -DGECKO_SDK_PATH=/home/usr/xulrunner-sdk-31
    make

There is very simple gtk-based emedded application gtkskel/gtkskel
