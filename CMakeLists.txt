cmake_minimum_required(VERSION 3.5)
project(ascii_magic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        src/EasyBMP/EasyBMP.cpp
        src/lodePNG/lodepng.cpp
        src/nanoJPEG/nanojpeg.c
        src/main.cpp
        src/BMPToASCII.cpp
        src/ImageToASCII.cpp
        src/PNGToASCII.cpp
        )
add_executable(ascii_magic ${SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
