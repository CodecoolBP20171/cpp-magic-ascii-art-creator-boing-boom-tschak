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
    height = h;
    width = w;
    image = new pixel* [height];
    for (int i = 0; i < height; ++i) {
        image[i] = new pixel[width];
    }
    size_t idx = 0;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            image[row][col].red = png[idx];
            image[row][col].green = png[idx + 1];
            image[row][col].blue = png[idx + 2];
            image[row][col].alpha = png[idx + 3];
            idx += 4;
        }
    }
}
