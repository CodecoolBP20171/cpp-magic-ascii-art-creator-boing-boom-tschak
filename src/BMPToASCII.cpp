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
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j].red = bmp(j, i)->Red;
            image[i][j].green = bmp(j, i)->Green;
            image[i][j].blue = bmp(j, i)->Blue;
            image[i][j].alpha = bmp(j, i)->Alpha;
        }
    }
}
