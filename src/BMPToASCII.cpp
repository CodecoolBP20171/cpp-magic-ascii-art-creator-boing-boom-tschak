#include <ASCIImagicExceptions.hpp>
#include "BMPToASCII.h"

BMPToASCII::BMPToASCII(const std::string& filename)
        : filename(filename) {}

void BMPToASCII::loadImage() {
    SetEasyBMPwarningsOff();
    BMP bmp;
    if(!bmp.ReadFromFile(filename.c_str())) throw DecoderError();
    width = bmp.TellWidth();
    height = bmp.TellHeight();
    if(!allocateImage()) throw MemoryError();
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            image[row][col].red = bmp(col, row)->Red;
            image[row][col].green = bmp(col, row)->Green;
            image[row][col].blue = bmp(col, row)->Blue;
            image[row][col].alpha = bmp(col, row)->Alpha;
        }
    }
}
