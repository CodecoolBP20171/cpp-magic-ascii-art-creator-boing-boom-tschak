extern "C" {
#include <nanoJPEG/nanoJPEG.h>
}

#include "JPEGToASCII.h"
#include <iostream>
#include <fstream>
#include <ASCIImagicExceptions.hpp>

JPEGToASCII::JPEGToASCII(const std::string& filename)
        : filename(filename) {}

void JPEGToASCII::loadImage() {
    njInit();
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    auto buffer = new char[size];
    if (!file.read(buffer, size)) throw DecoderError();
    if (njDecode(buffer, size)) throw DecoderError();
    width = njGetWidth();
    height = njGetHeight();
    if (!allocateImage()) throw MemoryError();
    auto jpg = njGetImage();
    size_t idx = 0;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            image[row][col].red = jpg[idx];
            image[row][col].green = jpg[idx + 1];
            image[row][col].blue = jpg[idx + 2];
            image[row][col].alpha = 255;
            idx += 3;
        }
    }
    njDone();
}
