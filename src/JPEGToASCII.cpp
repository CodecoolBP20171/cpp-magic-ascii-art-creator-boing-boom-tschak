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
    image.width = njGetWidth();
    image.height = njGetHeight();
    if (!allocateImage()) throw MemoryError();
    auto jpg = njGetImage();
    size_t idx = 0;
    for (int row = 0; row < image.height; ++row) {
        for (int col = 0; col < image.width; ++col) {
            image.image[row][col].red = jpg[idx];
            image.image[row][col].green = jpg[idx + 1];
            image.image[row][col].blue = jpg[idx + 2];
            image.image[row][col].alpha = 255;
            idx += 3;
        }
    }
    njDone();
    delete[] buffer;
}
