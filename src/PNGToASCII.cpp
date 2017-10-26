#include <iostream>
#include "PNGToASCII.h"
#include "lodePNG/lodepng.h"
#include "ASCIImagicExceptions.hpp"

PNGToASCII::PNGToASCII(const std::string& filename)
        : filename(filename) {}

void PNGToASCII::loadImage() {
    std::vector<unsigned char> png;
    unsigned w, h;
    unsigned error = lodepng::decode(png, w, h, filename);
    if (error) {
        std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        throw DecoderError();
    }
    image.height = h;
    image.width = w;
    if(!allocateImage()) throw MemoryError();
    size_t idx = 0;
    for (int row = 0; row < image.height; ++row) {
        for (int col = 0; col < image.width; ++col) {
            image.image[row][col].red = png[idx];
            image.image[row][col].green = png[idx + 1];
            image.image[row][col].blue = png[idx + 2];
            image.image[row][col].alpha = png[idx + 3];
            idx += 4;
        }
    }
}
