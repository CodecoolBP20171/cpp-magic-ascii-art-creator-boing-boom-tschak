#include <ASCIImagicExceptions.hpp>
#include "BMPToASCII.h"

BMPToASCII::BMPToASCII(const std::string& filename)
        : filename(filename) {}

void BMPToASCII::loadImage() {
    SetEasyBMPwarningsOff();
    BMP bmp;
    if(!bmp.ReadFromFile(filename.c_str())) throw DecoderError();
    image.width = bmp.TellWidth();
    image.height = bmp.TellHeight();
    if(!allocateImage()) throw MemoryError();
    for (int row = 0; row < image.height; ++row) {
        for (int col = 0; col < image.width; ++col) {
            image.image[row][col].red = bmp(col, row)->Red;
            image.image[row][col].green = bmp(col, row)->Green;
            image.image[row][col].blue = bmp(col, row)->Blue;
            image.image[row][col].alpha = bmp(col, row)->Alpha;
        }
    }
}
